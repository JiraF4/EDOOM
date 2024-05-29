class PS_DMap
{
	string m_sName;
	
	// WAD data
	ref array<vector> m_aVertexes = {};
	ref array<ref PS_DLineDef> m_aLineDefs = {};
	ref array<ref PS_DThing> m_aThings = {};
	ref array<ref PS_DSeg> m_aSegs = {};
	ref array<ref PS_DSubSector> m_aSubSectors = {};
	ref array<ref PS_DNode> m_aNodes = {};
	ref array<ref PS_DSector> m_aSectors = {};
	ref array<ref PS_DSideDef> m_aSideDefs = {};
	ref PS_DBlockMap m_DBlockMap;
	ref array<ref array<PS_DSector>> m_aSpecialSectors = {};
	ref array<PS_DSpecial> m_aSpecials = {};
	ref array<PS_DSpecialAction> m_aSpecialActions = {};
	ref array<int> m_aReject = {};
	
	ref PS_DSpecial m_DieSpecial;
	
	// Global data
	int m_iRootNodeId;
	PS_DNode m_RootNode;
	PS_DWAD m_DWad;
	PS_DMain m_DMain;
	
	// Dynamic data
	ref array<ref PS_DEntity> m_aEntities = {};
	
	// Ticks
	int m_iTickNum;
	static const float TICK_DELAY = 28;
	float m_fLastTickTime;
	
	// Statistic
	int m_iItemsCount;
	int m_iItemsCollected;
	int m_iKillsCount;
	int m_iKillsCollected;
	int m_iSecretsCount;
	int m_iSecretsCollected;
	
	//------------------------------------------------------------------------------------------------
	PS_DSubSector GetPositionSubSector(vector position)
	{
		PS_DNode node = m_RootNode;
		PS_DSubSector subSector;
		while (!subSector)
		{
			vector toPos = position - node.m_vPartition;
			float side = PS_Math2D.Dot2D(node.m_vPartitionDelta, toPos);
			if (side < 0)
				if (node.m_LeftNode)
					node = node.m_LeftNode;
				else
					subSector = node.m_LeftSubSector;
			else
				if (node.m_RightNode)
					node = node.m_RightNode;
				else
					subSector = node.m_RightSubSector;
		}
		return subSector;
	}
	
	//------------------------------------------------------------------------------------------------
	PS_DSector GetPositionSector(vector position)
	{
		PS_DNode node = m_RootNode;
		PS_DSubSector subSector;
		while (!subSector)
		{
			vector toPos = position - node.m_vPartition;
			float side = PS_Math2D.Dot2D(node.m_vPartitionDelta, toPos);
			if (side < 0)
				if (node.m_LeftNode)
					node = node.m_LeftNode;
				else
					subSector = node.m_LeftSubSector;
			else
				if (node.m_RightNode)
					node = node.m_RightNode;
				else
					subSector = node.m_RightSubSector;
		}
		return m_aSegs[subSector.m_iFirstSegNum].m_FrontSector;
	}
	
	//------------------------------------------------------------------------------------------------
	// 100% time player
	void SoundSource(PS_DEntity entity)
	{
		PS_DSector sector = GetPositionSector(entity.m_vPosition);
		PS_DSector.s_iFlag++;
		SoundSourceRec(sector, entity);
	}
	void SoundSourceRec(PS_DSector sector, PS_DEntity entity)
	{
		if (!sector)
			return;
		if (sector.m_iFlag == sector.s_iFlag)
			return;
		sector.m_iFlag = sector.s_iFlag;
		
		sector.m_SoundSource = entity;
		foreach (PS_DSideDef sideDef : sector.m_aSideDefs)
		{
			PS_DLineDef lineDef = sideDef.m_LineDef;
			if (!lineDef.m_BackSideDef)
				continue;
			if (lineDef.m_iFlags & PS_EDLineDefsFlags.SOUND_BLOCK)
				continue;
			if (lineDef.m_FrontSideDef.m_Sector.m_iFloorHeight < lineDef.m_FrontSideDef.m_Sector.m_iCeilingHeight
				 && lineDef.m_FrontSideDef.m_Sector.m_iFloorHeight < lineDef.m_BackSideDef.m_Sector.m_iCeilingHeight
				 && lineDef.m_BackSideDef.m_Sector.m_iFloorHeight < lineDef.m_BackSideDef.m_Sector.m_iCeilingHeight
				 && lineDef.m_BackSideDef.m_Sector.m_iFloorHeight < lineDef.m_FrontSideDef.m_Sector.m_iCeilingHeight
			)
			{
				SoundSourceRec(lineDef.m_FrontSideDef.m_Sector, entity);
				SoundSourceRec(lineDef.m_BackSideDef.m_Sector, entity);
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void Init()
	{
		m_DieSpecial = new PS_DSpecial(this);
		
		m_iRootNodeId = m_aNodes.Count() - 1;
		m_RootNode = m_aNodes[m_iRootNodeId];
		
		// link nodes
		foreach (PS_DNode node : m_aNodes)
		{
			if (node.m_iLeftChild < PS_DConst.SUB_SECTOR_IDENTIFIER)
				node.m_LeftNode      = m_aNodes[node.m_iLeftChild];
			else
				node.m_LeftSubSector = m_aSubSectors[node.m_iLeftChild - PS_DConst.SUB_SECTOR_IDENTIFIER];
			
			if (node.m_iRightChild < PS_DConst.SUB_SECTOR_IDENTIFIER)
				node.m_RightNode      = m_aNodes[node.m_iRightChild];
			else
				node.m_RightSubSector = m_aSubSectors[node.m_iRightChild - PS_DConst.SUB_SECTOR_IDENTIFIER];
		}
		
		// link segments
		foreach (PS_DSubSector subSector : m_aSubSectors)
		{
			subSector.m_aSegments.Resize(subSector.m_iSegCount);
			for (int i = 0; i < subSector.m_iSegCount; i++)
			{
				subSector.m_aSegments[i] = m_aSegs[subSector.m_iFirstSegNum + i];
			}
		}
		
		// link sectors
		foreach (PS_DSideDef sideDef : m_aSideDefs)
		{
			sideDef.m_Sector = m_aSectors[sideDef.m_iSectorId];
			sideDef.m_Sector.m_aSideDefs.Insert(sideDef);
		}
		
		// link side defs
		foreach (PS_DLineDef lineDef : m_aLineDefs)
		{
			lineDef.m_vStartingVertex = m_aVertexes[lineDef.m_iStartVertex];
			lineDef.m_vEndVertex = m_aVertexes[lineDef.m_iEndVertex];
			
			if (lineDef.m_iFrontSide >= 0)
			{
				lineDef.m_FrontSideDef = m_aSideDefs[lineDef.m_iFrontSide];
				lineDef.m_FrontSideDef.m_LineDef = lineDef;
			}
			if (lineDef.m_iBackSide >= 0)
			{
				lineDef.m_BackSideDef = m_aSideDefs[lineDef.m_iBackSide];
				lineDef.m_BackSideDef.m_LineDef = lineDef;
			}
			
			vector wallNormal = lineDef.m_vEndVertex - lineDef.m_vStartingVertex;
			wallNormal = PS_Math2D.Rotate(wallNormal, -Math.PI_HALF).Normalized();
			lineDef.m_vNormal = wallNormal;
		}
		
		// link vertexes, lines, sectors
		foreach (PS_DSeg seg : m_aSegs)
		{
			seg.m_vStartingVertex = m_aVertexes[seg.m_iStartingVertex];
			seg.m_vEndingVertex = m_aVertexes[seg.m_iEndingVertex];
			
			seg.m_LineDef = m_aLineDefs[seg.m_iLinedefNumber];
			
			
			if (seg.m_iDirection) // Reverse sides
			{
				seg.m_BackSideDef = seg.m_LineDef.m_FrontSideDef;
				seg.m_FrontSideDef = seg.m_LineDef.m_BackSideDef;
			} else {
				seg.m_FrontSideDef = seg.m_LineDef.m_FrontSideDef;
				seg.m_BackSideDef = seg.m_LineDef.m_BackSideDef;
			}
			
			seg.m_FrontSector = seg.m_FrontSideDef.m_Sector;
			if (PS_EDLineDefsFlags.TWO_SIDED & seg.m_LineDef.m_iFlags)
				seg.m_BackSector = seg.m_BackSideDef.m_Sector
		}
		
		// link textures
		int id = 0;
		foreach (PS_DSector sector : m_aSectors)
		{
			sector.m_DMap = this;
			
			sector.m_iId = id;
			id++;
			
			if (sector.m_sFloorTextureName != "-")
				sector.m_FloorTexture = m_DWad.m_DAssets.m_mFlatTextures[sector.m_sFloorTextureName];
			if (sector.m_sCeilingTextureName != "-")
				sector.m_CeilingTexture = m_DWad.m_DAssets.m_mFlatTextures[sector.m_sCeilingTextureName];
		}
		
		foreach (PS_DBlockMapCell cell : m_DBlockMap.m_aCells)
		{
			//m_aNeighbours;
			foreach (int lineDefId : cell.m_aLineDefIds)
			{
				cell.m_aLineDefs.Insert(m_aLineDefs[lineDefId]);
			}
		}
		
		array<vector> offsets = {
			"-1 -1 0",
			" 0 -1 0",
			" 1 -1 0",
			"-1  0 0",
			" 0  0 0",
			" 1  0 0",
			"-1  1 0",
			" 0  1 0",
			" 1  1 0",
			" 0  0 0"
		};
		for (int x = 0; x < m_DBlockMap.m_iGridColumns; x++)
		{
			for (int y = 0; y < m_DBlockMap.m_iGridRows; y++)
			{
				int index = x + y * m_DBlockMap.m_iGridColumns;
				PS_DBlockMapCell cell = m_DBlockMap.m_aCells[index];
				cell.m_iX = x;
				cell.m_iY = y;
				foreach (vector offset : offsets)
				{
					int indexOther = x + offset[0] + (y + offset[1]) * m_DBlockMap.m_iGridColumns;
					if (m_DBlockMap.m_aCells.Count() > indexOther && indexOther > 0)
						cell.m_aNeighbours.Insert(m_DBlockMap.m_aCells[indexOther]);
				}
			}
		}
		
		// Create dynamic staff
		foreach (PS_DThing thing : m_aThings)
		{
			// Skip not normal
			int difficulty = PS_EDThingFlag.MTF_EASY;
			if (m_DMain.m_iDifficulty == 2)
				difficulty = PS_EDThingFlag.MTF_NORMAL;
			if (m_DMain.m_iDifficulty > 2)
				difficulty = PS_EDThingFlag.MTF_HARD;
			
			if (!(thing.m_iFlags & difficulty))
				continue;
			if (thing.m_iFlags & PS_EDThingFlag.MTF_MULTIPLAYERONLY)
				continue;
			
			PS_DEntity entity = new PS_DEntity(this);
			
			vector position = Vector(thing.m_iXPos, thing.m_iYPos, 0);
			PS_DSector sector = GetPositionSector(position);
			position[2] = sector.m_iFloorHeight;
			entity.m_vPosition = position;
			entity.m_fAngle = (float)(-thing.m_iAngle + 180) * Math.DEG2RAD;
			
			if (thing.m_iType == 14)
			{
				sector.m_vTeleportTarget = position;
			}
			
			entity.m_MobjInfo = PS_DInfo.m_mMobjInfo[thing.m_iType];
			if (entity.m_MobjInfo)
			{
				entity.m_MobjState = PS_DInfo.m_aMobjStates[entity.m_MobjInfo.m_iSpawnState];
				entity.m_iFlags = entity.m_MobjInfo.m_iFlags;
				if (thing.m_iFlags & PS_EDThingFlag.MTF_AMBUSH)
					entity.m_iFlags = entity.m_iFlags | PS_EDMobjFlag.MF_AMBUSH;
				entity.m_iHealth = entity.m_MobjInfo.m_iSpawnHealth;
				entity.m_iStateTics = entity.m_MobjState.m_iTics - m_DMain.m_RandomGenerator.RandIntInclusive(0, entity.m_MobjState.m_iTics);
				entity.m_BBOX = new PS_DEntityBBox(entity.m_MobjInfo);
				
				if (entity.m_MobjInfo.m_iFlags & PS_EDMobjFlag.MF_COUNTKILL)
				{
					m_iKillsCount++;
				}
				if (entity.m_MobjInfo.m_iFlags & PS_EDMobjFlag.MF_COUNTITEM)
				{
					m_iItemsCount++;
				}
			}
			
			m_aEntities.Insert(entity);
		}
		
		// Specials
		foreach (PS_DSector sector : m_aSectors)
		{
			sector.InitPolygon();
			
			if (sector.m_iTagNumber > 0)
			{
				if (m_aSpecialSectors.Count() <= sector.m_iTagNumber)
					m_aSpecialSectors.Resize(sector.m_iTagNumber + 1);
				if (!m_aSpecialSectors[sector.m_iTagNumber])
					m_aSpecialSectors[sector.m_iTagNumber] = new array<PS_DSector>();
				m_aSpecialSectors[sector.m_iTagNumber].Insert(sector);
			}
			
			if (sector.m_iSpecialType > 0)
			{
				PS_DSpecial special = new PS_DSpecial(this);
				
				special.m_iSpecialType = sector.m_iSpecialType;
				
				sector.m_Special = special;
				m_aSpecials.Insert(special);
				
				if (sector.m_iSpecialType == 9)
					m_iSecretsCount++;
				
				// spawn action for active specials
				special.Spawn(sector);
			}
		}
		foreach (PS_DLineDef lineDef : m_aLineDefs)
		{
			if (lineDef.m_iSpecialType > 0)
			{
				PS_DSpecial special = new PS_DSpecial(this);
				special.m_iSpecialType = lineDef.m_iSpecialType;
				lineDef.m_Special = special;
				m_aSpecials.Insert(special);
			}
		}
		
		m_fLastTickTime = GetGame().GetWorld().GetWorldTime();
	}
	
	//------------------------------------------------------------------------------------------------
	void Update()
	{
		float updateTime = GetGame().GetWorld().GetWorldTime();
		
		while (updateTime - TICK_DELAY > m_fLastTickTime)
		{
			m_iTickNum++;
			FixedUpdate(TICK_DELAY);
			m_fLastTickTime += TICK_DELAY;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void FixedUpdate(float tickTime)
	{
		m_DMain.m_DInput.Update();
		if (!m_DMain.m_EntityPlayer.m_bDead)
		{
			float esc = GetGame().GetInputManager().GetActionValue("DESC");
			if (esc)
			{
				m_DMain.m_bInMenu = true;
				m_DMain.m_DMainMenu.Reset(true);
				m_DMain.m_DMainMenu.m_iTitleTicks = 0;
			}
			
			vector moveVector = Vector(
				m_DMain.m_DInput.m_fRight,
				m_DMain.m_DInput.m_fForward,
				0
			);
			float rotation = m_DMain.m_DInput.m_fAim;
			m_DMain.m_EntityPlayer.Rotate(rotation);
			moveVector = PS_Math2D.Rotate(moveVector, -m_DMain.m_EntityPlayer.m_fAngle).Normalized() * 3.0;
			m_DMain.m_EntityPlayer.Accelerate(moveVector);
		} else {
			if (m_DMain.m_EntityPlayer.m_iDamageTicks <= 0)
			{
				float action = GetGame().GetInputManager().GetActionValue("DAction");
				if (action > 0)
				{
					m_DMain.Restart();
				}
			}
		}
			
		for (int i = 0; i < m_aEntities.Count(); i++)
		{
			PS_DEntity entity = m_aEntities[i];
			if (entity == null)
				continue;
			
			entity.Update();
		}
		
		for (int i = 0; i < m_aSpecialActions.Count(); i++)
		{
			PS_DSpecialAction specialAction = m_aSpecialActions[i];
			if (!specialAction)
			{
				m_aSpecialActions.Remove(i);
				i--;
				continue;
			}
			specialAction.Update();
		}
		
		PS_DAnimatedTexture.Update();
	}
	
	//------------------------------------------------------------------------------------------------
	void RemoveEntity(PS_DEntity entity)
	{
		int i = m_aEntities.Find(entity);
		
		if (entity.m_SubSector)
			entity.m_SubSector.m_sEntities.RemoveItem(entity);
		if (entity.m_BlockMapCell)
			entity.m_BlockMapCell.m_sEntities.RemoveItem(entity);
		
		m_aEntities[i] = null;
	}
	
	//------------------------------------------------------------------------------------------------
	void PrintContent()
	{
		foreach (vector vertex : m_aVertexes)
		{
			//Print(vertex);
		}
		foreach (PS_DLineDef linedef : m_aLineDefs)
		{
			//linedef.PrintContent();
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadLump(FileHandle wadFile, PS_DLump lump, PS_EDLump lumpType, int size)
	{
		wadFile.Seek(lump.m_iFilepos);
		int count = lump.m_iSize / size;
		for (int i = 0; i < count; i++)
		{
			switch (lumpType)
			{
				case PS_EDLump.PS_DVertex:
					ReadVertexe(wadFile);
					break;
				case PS_EDLump.PS_DLinedef:
					ReadLinedef(wadFile);
					break;
				case PS_EDLump.PS_DThing:
					ReadThing(wadFile);
					break;
				case PS_EDLump.PS_DSeg:
					ReadSeg(wadFile);
					break;
				case PS_EDLump.PS_DSubSector:
					ReadSubSector(wadFile);
					break;
				case PS_EDLump.PS_DNode:
					ReadNode(wadFile);
					break;
				case PS_EDLump.PS_DSector:
					ReadSector(wadFile);
					break;
				case PS_EDLump.PS_DSideDef:
					ReadSideDef(wadFile);
					break;
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadVertexe(FileHandle wadFile)
	{
		int x, y;
		x = PS_DWAD.ReadShort(wadFile);
		y = PS_DWAD.ReadShort(wadFile);
		m_aVertexes.Insert(Vector(x, y, 0));
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadLinedef(FileHandle wadFile)
	{
		PS_DLineDef lineDef    = new PS_DLineDef();
		lineDef.m_iStartVertex = PS_DWAD.ReadShort(wadFile);
		lineDef.m_iEndVertex   = PS_DWAD.ReadShort(wadFile);
		lineDef.m_iFlags       = PS_DWAD.ReadShort(wadFile);
		lineDef.m_iSpecialType = PS_DWAD.ReadShort(wadFile);
		lineDef.m_iSectorTag   = PS_DWAD.ReadShort(wadFile);
		lineDef.m_iFrontSide   = PS_DWAD.ReadShort(wadFile);
		lineDef.m_iBackSide    = PS_DWAD.ReadShort(wadFile);
		m_aLineDefs.Insert(lineDef);
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadThing(FileHandle wadFile)
	{
		PS_DThing thing   = new PS_DThing();
		thing.m_iXPos   = PS_DWAD.ReadShort(wadFile);
		thing.m_iYPos   = PS_DWAD.ReadShort(wadFile);
		thing.m_iAngle  = PS_DWAD.ReadShort(wadFile);
		thing.m_iType   = PS_DWAD.ReadShort(wadFile);
		thing.m_iFlags  = PS_DWAD.ReadShort(wadFile);
		m_aThings.Insert(thing);
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadSeg(FileHandle wadFile)
	{
		PS_DSeg seg = new PS_DSeg();
		seg.m_iStartingVertex = PS_DWAD.ReadShort(wadFile);
		seg.m_iEndingVertex   = PS_DWAD.ReadShort(wadFile);
		seg.m_iAngle          = PS_DWAD.ReadShort(wadFile);
		seg.m_iLinedefNumber  = PS_DWAD.ReadShort(wadFile);
		seg.m_iDirection      = PS_DWAD.ReadShort(wadFile);
		seg.m_iOffset         = PS_DWAD.ReadShort(wadFile);
		
		seg.m_fAngle = PS_Math2D.BAMAngleToRad(seg.m_iAngle);
		seg.m_fDirection = PS_Math2D.BAMAngleToRad(seg.m_iDirection);
		
		m_aSegs.Insert(seg);
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadSubSector(FileHandle wadFile)
	{
		PS_DSubSector subSector = new PS_DSubSector();
		subSector.m_iSegCount    = PS_DWAD.ReadShort(wadFile);
		subSector.m_iFirstSegNum = PS_DWAD.ReadShort(wadFile);
		
		subSector.m_iColor = Color.FromRGBA(Math.RandomInt(0, 255), Math.RandomInt(0, 255), Math.RandomInt(0, 255), 255).PackToInt();
		
		m_aSubSectors.Insert(subSector);
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadNode(FileHandle wadFile)
	{
		PS_DNode node              = new PS_DNode();
		node.m_iXPartition      = PS_DWAD.ReadShort(wadFile);
		node.m_iYPartition      = PS_DWAD.ReadShort(wadFile);
		node.m_iXDeltaPartition = PS_DWAD.ReadShort(wadFile);
		node.m_iYDeltaPartition = PS_DWAD.ReadShort(wadFile);
		int tr, br, lr, rr;
		tr = PS_DWAD.ReadShort(wadFile);
		br = PS_DWAD.ReadShort(wadFile);
		lr = PS_DWAD.ReadShort(wadFile);
		rr = PS_DWAD.ReadShort(wadFile);
		int tl, bl, ll, rl;
		tl = PS_DWAD.ReadShort(wadFile);
		bl = PS_DWAD.ReadShort(wadFile);
		ll = PS_DWAD.ReadShort(wadFile);
		rl = PS_DWAD.ReadShort(wadFile);
		wadFile.Read(node.m_iLeftChild, 2);
		wadFile.Read(node.m_iRightChild, 2);
		
		// sub
		node.m_vPartition = Vector(node.m_iXPartition, node.m_iYPartition, 0);
		node.m_vPartitionDelta = Vector(node.m_iXDeltaPartition, node.m_iYDeltaPartition, 0);
		node.m_RightBBox = new PS_DBBox(tr, br, lr, rr);
		node.m_LeftBBox  = new PS_DBBox(tl, bl, ll, rl);
		
		m_aNodes.Insert(node);
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadSector(FileHandle wadFile)
	{
		PS_DSector sector = new PS_DSector();
		sector.m_iFloorHeight = PS_DWAD.ReadShort(wadFile);
		sector.m_iCeilingHeight = PS_DWAD.ReadShort(wadFile);
		sector.m_sFloorTextureName = PS_DWAD.ReadASCIIString(wadFile, 8);
		sector.m_sCeilingTextureName = PS_DWAD.ReadASCIIString(wadFile, 8);
		sector.m_iLightLevel = PS_DWAD.ReadShort(wadFile);
		sector.m_iLightLevel = sector.m_iLightLevel >> 3;
		sector.m_iSpecialType = PS_DWAD.ReadShort(wadFile);
		sector.m_iTagNumber = PS_DWAD.ReadShort(wadFile);
		
		m_aSectors.Insert(sector);
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadSideDef(FileHandle wadFile)
	{
		PS_DSideDef sideDef = new PS_DSideDef();
		sideDef.m_xOffset = PS_DWAD.ReadShort(wadFile);
		sideDef.m_yOffset = PS_DWAD.ReadShort(wadFile);
		
		sideDef.m_sUpperTextureName = PS_DWAD.ReadASCIIString(wadFile, 8);
		sideDef.m_sLowerTextureName = PS_DWAD.ReadASCIIString(wadFile, 8);
		sideDef.m_sMiddleTextureName = PS_DWAD.ReadASCIIString(wadFile, 8);
		
		sideDef.m_sUpperTextureName.ToUpper();
		sideDef.m_sLowerTextureName.ToUpper();
		sideDef.m_sMiddleTextureName.ToUpper();
		
		sideDef.m_iSectorId = PS_DWAD.ReadShort(wadFile);
		
		m_aSideDefs.Insert(sideDef);
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadBlockMap(FileHandle wadFile, PS_DLump lump)
	{
		wadFile.Seek(lump.m_iFilepos);
		
		PS_DBlockMap blockMap = new PS_DBlockMap(this);
		blockMap.m_iGridOriginX = PS_DWAD.ReadShort(wadFile);
		blockMap.m_iGridOriginY = PS_DWAD.ReadShort(wadFile);
		blockMap.m_iGridColumns = PS_DWAD.ReadShort(wadFile);
		blockMap.m_iGridRows = PS_DWAD.ReadShort(wadFile);
		int size = blockMap.m_iGridColumns * blockMap.m_iGridRows;
		blockMap.m_aOffsets.Resize(size);
		for (int i = 0; i < size; i++)
		{
			int offset = PS_DWAD.ReadShort(wadFile);
			blockMap.m_aOffsets[i] = offset;
		}
		
		for (int i = 0; i < size; i++)
		{
			int offset = blockMap.m_aOffsets[i];
			wadFile.Seek(lump.m_iFilepos + offset * 2);
			
			PS_DBlockMapCell cell = new PS_DBlockMapCell();
			int lineDefId = PS_DWAD.ReadShort(wadFile);
			while (lineDefId != -1)
			{
				cell.m_aLineDefIds.Insert(lineDefId);
				lineDefId = PS_DWAD.ReadShort(wadFile);
			}
			blockMap.m_aCells.Insert(cell);
		}
		
		m_DBlockMap = blockMap;
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadReject(FileHandle wadFile, PS_DLump lump)
	{
		wadFile.Seek(lump.m_iFilepos);
		
		//string line = "";
		int size = Math.Ceil((float)(m_aSectors.Count() * m_aSectors.Count()) / 8.0);
		
		//Print(m_aSectors.Count());
		int pos;
		int data;
		for (int i = 0; i < size; i++)
		{
			wadFile.Read(data, 1);
			for (int s = 0; s < 8; s++)
			{
				/*
				if (data & (1 << s))
					line = line + "1";
				else
					line = line + "0";
				*/
				
				m_aReject.Insert(data & (1 << s));
				
				pos++;
				if (pos == m_aSectors.Count())
				{
					pos = 0;
					//PrintFormat(line);
					//line = "";
				}
			}
		}
		
		//PrintFormat(line);
	}
	
	//------------------------------------------------------------------------------------------------
	bool IsRejected(int sector1, int sector2)
	{
		return m_aReject[sector1 + sector2*m_aSectors.Count()] > 0;
	}
	
	//------------------------------------------------------------------------------------------------
	void PS_DMap(PS_DWAD dWad, PS_DMain dMain, string name)
	{
		m_DWad = dWad;
		m_DMain = dMain;
		m_sName = name;
	}
	
	//------------------------------------------------------------------------------------------------
	void WriteSave(FileHandle saveFile)
	{
		// Specials
		saveFile.Write(m_iTickNum, 4);
		foreach (PS_DSector sector : m_aSectors)
		{
			saveFile.Write(sector.m_iSpecialType, 4);
			saveFile.Write(sector.m_iFloorHeight, 4);
			saveFile.Write(sector.m_iCeilingHeight, 4);
			saveFile.Write(sector.m_iLightLevel, 4);
			
			if (sector.m_sFloorTextureName != sector.m_FloorTexture.m_sName)
			{
				int length = sector.m_FloorTexture.m_sName.Length();
				saveFile.Write(length, 1);
				saveFile.Write(sector.m_FloorTexture.m_sName, length);
			}
			else
				saveFile.Write(0, 1);
			
			PS_FileHelper.WriteVector(saveFile, sector.m_vTeleportTarget);
			
			if (sector.m_SpecialAction)
				sector.m_SpecialAction.WriteSave(saveFile);
			else
				saveFile.Write(0, 1);
		}
		foreach (PS_DLineDef lineDef : m_aLineDefs)
		{
			saveFile.Write(lineDef.m_iSpecialType, 2);
			if (lineDef.m_Special)
			{
				saveFile.Write(1, 1);
			}
			else
				saveFile.Write(0, 1);
			
			saveFile.Write(lineDef.m_iTextureChanged, 1);
			if (lineDef.m_iTextureChanged != 0)
			{
				int length = lineDef.m_FrontSideDef.m_sMiddleTextureName.Length();
				saveFile.Write(length, 1);
				saveFile.Write(lineDef.m_FrontSideDef.m_sMiddleTextureName, length);
				
				length = lineDef.m_FrontSideDef.m_sUpperTextureName.Length();
				saveFile.Write(length, 1);
				saveFile.Write(lineDef.m_FrontSideDef.m_sUpperTextureName, length);
			}
		}
		
		// Clear nulls
		for (int i = 0; i < m_aEntities.Count(); i++)
		{
			PS_DEntity entity = m_aEntities[i];
			if (!entity)
			{
				m_aEntities.Remove(i);
				i--;
			}
		}
		
		// Write all entities, but player first
		int count = m_aEntities.Count();
		saveFile.Write(count, 2);
		foreach (PS_DEntity entity : m_aEntities)
		{
			if (entity.IsInherited(PS_DEntityPlayer))
				entity.WriteSave(saveFile);
		}
		foreach (PS_DEntity entity : m_aEntities)
		{
			if (!entity.IsInherited(PS_DEntityPlayer))
				entity.WriteSave(saveFile);
		}
	}
	
	void ReadSave(FileHandle saveFile)
	{
		// Specials
		saveFile.Read(m_iTickNum, 4);
		foreach (PS_DSector sector : m_aSectors)
		{
			saveFile.Read(sector.m_iSpecialType, 4);
			saveFile.Read(sector.m_iFloorHeight, 4);
			saveFile.Read(sector.m_iCeilingHeight, 4);
			saveFile.Read(sector.m_iLightLevel, 4);
			
			int length;
			saveFile.Read(length, 1);
			if (length != 0)
			{
				string name;
				saveFile.Read(name, length);
				sector.m_FloorTexture = m_DWad.m_DAssets.m_mFlatTextures[name];
			}
			
			sector.m_vTeleportTarget = PS_FileHelper.ReadVector(saveFile);
			
			PS_EDSpecialAction specialActionType;
			saveFile.Read(specialActionType, 1);
			if (specialActionType == 0)
				sector.m_SpecialAction = null;
			else
			{
				PS_DSpecialAction action;
				switch (specialActionType)
				{
					case PS_EDSpecialAction.PS_DSpecialActionLift:
						action = new PS_DSpecialActionLift();
						break;
					case PS_EDSpecialAction.PS_DSpecialActionDoor:
						action = new PS_DSpecialActionDoor();
						break;
					case PS_EDSpecialAction.PS_DSpecialGlowingLight:
						action = new PS_DSpecialGlowingLight();
						break;
					case PS_EDSpecialAction.PS_DSpecialStrobingLight:
						action = new PS_DSpecialStrobingLight();
						break;
				}
				action.ReadSave(saveFile);
				action.m_Sector = sector;
				m_aSpecialActions.Insert(action);
				sector.m_SpecialAction = action;
			}
		}
		foreach (PS_DLineDef lineDef : m_aLineDefs)
		{
			saveFile.Read(lineDef.m_iSpecialType, 2);
			int hasSpecial;
			saveFile.Read(hasSpecial, 1);
			if (hasSpecial == 0)
				lineDef.m_Special = null;
			
			saveFile.Read(lineDef.m_iTextureChanged, 1);
			if (lineDef.m_iTextureChanged != 0)
			{
				int length;
				saveFile.Read(length, 1);
				saveFile.Read(lineDef.m_FrontSideDef.m_sMiddleTextureName, length);
				saveFile.Read(length, 1);
				saveFile.Read(lineDef.m_FrontSideDef.m_sUpperTextureName, length);
			}
		}
		
		// Clear spawned
		foreach (PS_DEntity entity : m_aEntities)
			RemoveEntity(entity);
		
		// Entities
		int count;
		saveFile.Read(count, 2);
		
		// Read player
		m_DMain.m_EntityPlayer.ReadSave(saveFile);
		m_aEntities.Insert(m_DMain.m_EntityPlayer);
		m_DMain.m_EntityPlayer.Rotate(0);
		
		count--;
		for (; count > 0; count--)
		{
			PS_DEntity entity = new PS_DEntity(this);
			entity.ReadSave(saveFile);
			m_aEntities.Insert(entity);
		}
		
		// Reset timer
		m_fLastTickTime = GetGame().GetWorld().GetWorldTime();
	}
}


















