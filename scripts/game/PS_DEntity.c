// All dynamic things, and some static
class PS_DEntity
{
	PS_DMap m_DMap;             // Reference to current map
	vector m_vPosition;         // Current position include z (world height)
	vector m_vPositionTeleport; // Since teleportation happen in movement, this "workaround" exist FIXME
	vector m_vVelocity;         // Current velocity
	float m_fAngle;             // Current angle in radians
	
	bool m_bDead;  // Dead flag
	int m_iHealth; // Current health
	
	PS_DSubSector m_SubSector;       // Current SubSector for rendering
	PS_DBlockMapCell m_BlockMapCell; // Current block map cell for collision checking
	PS_DSector m_Sector;             // Current sector for special actions and height checking
	
	PS_DMobjInfo m_MobjInfo;   // static entity parameters
	PS_DMobjState m_MobjState; // Current state
	int m_iStateTics;          // Remaining state ticks
	
	// Processing flag, well... bad naming
	// TODO: rename it
	static int s_iFlag;
	int m_iFlag;
	
	int m_iFlags; // PS_EDMobjFlag flags
	
	
	// BBOX of entity, it doesn't change during time
	// TODO: mave it to MobjInfo
	ref PS_DEntityBBox m_BBOX;
	
	// Collision data
	// Dynamic data - update every physic query
	bool m_bCollideEntity;         // Is coillide entity
	PS_DEntity m_CollidedEntity;   // Last collided entity
	PS_DLineDef m_CollidedLineDef; // Last collided LineDef
	vector m_vIntersect;           // Last intersection
	vector m_vIntersectNormal;     // Last intersection normal
	float m_fIntersectDistance;    // Last intersection distance
	
	
	// Last render frame (Can be removed?)
	int m_iRenderFrame;
	
	// "AI" data
	float m_fRotationDirection;    // Direction and speed of rotation in radians, Used for enimies Brownian motion
	PS_DEntity m_InstigatorEntity; // Last entity that attack this entity
	PS_DEntity m_AttackerEntity;   // Attacker for missiles
	PS_DEntity m_TargetEntity;     // Which entity this entity try attack
	int m_iMoveTics;               // Ticks before direction change
	int m_iMoveCount;              // Ticks before attack
	int m_iReactionTime;           // Ticks before doing anything
	
	// BBOX normals
	static const vector BBOX_NORMALS[4] = {
		" 0  1 0",
		" 1  0 0",
		" 0 -1 0",
		"-1  0 0"
	};
	
	//------------------------------------------------------------------------------------------------
	// Movement with collision checking, current SubSector/BlockMapCell update.
	// Every movement processed by this function.
	void Move()
	{
		// Clear last collision data
		m_CollidedEntity = null;
		m_CollidedLineDef = null;
		
		// Don't process if no BBOX
		if (!m_BBOX) // TODO: doesn't spawn, whatever it is
			return;
		
		// Force update entities on lifts
		// TODO: Current sector height check
		bool OnLift;
		if (m_Sector)
			OnLift = m_Sector.m_SpecialAction && m_Sector.m_SpecialAction.IsInherited(PS_DSpecialActionLift);
		
		// Clear telepot "workaround"
		m_vPositionTeleport = "0 0 0";
		
		// Doesn't update sleeping entities
		if (m_iFlags & PS_EDMobjFlag.MF_MISSILE || !m_Sector || OnLift || !float.AlmostEqual(m_vVelocity[0], 0, 0.01) || !float.AlmostEqual(m_vVelocity[1], 0, 0.01))
		{
			
			// Update current SubSector
			if (!(m_iFlags & PS_EDMobjFlag.MF_NOSECTOR))
			{
				PS_DSubSector subSector = m_DMap.GetPositionSubSector(m_vPosition);
				PS_DSubSector subSectorOld = m_SubSector;
				if (subSectorOld != subSector)
				{
					// Remove from old and add to new
					if (subSectorOld)
						subSectorOld.m_sEntities.RemoveItem(this);
					subSector.m_sEntities.Insert(this);
					m_SubSector = subSector;
				}
			}
			
			// Update current CollisionBlock
			if (!(m_iFlags & PS_EDMobjFlag.MF_NOBLOCKMAP))
			{
				PS_DBlockMapCell blockMapCell = m_DMap.m_DBlockMap.GetCell(m_vPosition);
				PS_DBlockMapCell blockMapCellOld = m_BlockMapCell;
				if (blockMapCellOld != blockMapCell)
				{
					// Remove from old and add to new
					if (blockMapCellOld)
						blockMapCellOld.m_sEntities.RemoveItem(this);
					blockMapCell.m_sEntities.Insert(this);
					m_BlockMapCell = blockMapCell;
				}
			}
			
			// Apply gravity
			if (!(m_iFlags & PS_EDMobjFlag.MF_NOGRAVITY))
				m_vVelocity[2] = m_vVelocity[2] - 1.8;
			
			// Trace movement
			float height = m_vPosition[2];
			vector newPosition = m_vPosition + m_vVelocity;
			m_vPosition = TracePathBBOX(m_vPosition, newPosition, m_vPosition[2]);
			m_vPosition[2] = height + m_vVelocity[2];
			
			// If teleported move to new position
			if (m_vPositionTeleport != "0 0 0")
				m_vPosition = m_vPositionTeleport;
			
			// Missile collision
			if (m_MobjInfo.m_iFlags & PS_EDMobjFlag.MF_MISSILE && !m_bDead)
			{
				bool collided = m_CollidedEntity || m_CollidedLineDef;
				if (m_Sector && !collided) // Check floor/ceiling
					collided = m_Sector.m_iFloorHeight >= m_vPosition[2] || m_Sector.m_iCeilingHeight <= m_vPosition[2];
				if (collided) // Do boom
				{
					PS_DSoundEffect.PlaySound(m_MobjInfo.m_iDeathSound, m_vPosition);
					PS_DMobjState deathState = PS_DInfo.m_aMobjStates[m_MobjInfo.m_iDeathState];
					m_MobjState = deathState;
					m_iStateTics = deathState.m_iTics;
					PS_DStateMachine.s_ActionEntity = this;
					PS_DStateMachine.Action(deathState.m_MobjActions);	
					m_vVelocity = "0 0 0";
					m_bDead = true;
					if (m_CollidedEntity)
						m_CollidedEntity.ApplyDamage(m_DMap.m_DMain.m_RandomGenerator.RandIntInclusive(3, 24), m_AttackerEntity);
					return;
				}
			}
			
			// Update sector
			m_Sector = m_DMap.GetPositionSector(m_vPosition);
			if (!(m_iFlags & PS_EDMobjFlag.MF_NOGRAVITY))
			{
				vector offsets[4];
				offsets = m_BBOX.m_aOffsetsHalf;
				if (this.IsInherited(PS_DEntityPlayer))
					offsets = m_BBOX.m_aOffsets_1;
				
				// Query all sectors by our BBOX
				PS_DSector maxSector;
				for (int i = 0; i < 4; i++)
				{
					PS_DSector sector = m_DMap.GetPositionSector(m_vPosition + offsets[i]);
					if (!maxSector || maxSector.m_iFloorHeight < sector.m_iFloorHeight)
						maxSector = sector;
				}
				if (maxSector)
				{
					if (maxSector.m_iFloorHeight >= m_vPosition[2])
					{
						m_vPosition[2] = maxSector.m_iFloorHeight;
						m_vVelocity[2] = 0;
					}
				}
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	// Every damage applyed by this function
	void ApplyDamage(int damage, PS_DEntity instigator)
	{
		// Attacked by same entity type
		if (instigator && instigator.m_MobjInfo == m_MobjInfo)
			return;
		
		// Already dead
		if (m_iHealth <= 0)
			return;
		
		// Save attacker data
		m_InstigatorEntity = instigator;
		if (instigator != this)
			m_TargetEntity = instigator; // Try attack back
		
		m_iHealth -= damage;
		if (m_iHealth <= 0) // Die (If need)
		{
			m_bDead = true;
			
			// "Kill" player face for 16 ticks
			if (instigator == m_DMap.m_DMain.m_EntityPlayer)
			{
				m_DMap.m_DMain.m_EntityPlayer.m_iAttackTicks = 16;
			}
			
			if (m_iHealth > -m_MobjInfo.m_iSpawnHealth || m_MobjInfo.m_iXDeathState == PS_DMobjStateNum.S_NULL)
			{
				// Just die
				PS_DMobjState deathState = PS_DInfo.m_aMobjStates[m_MobjInfo.m_iDeathState];
				m_MobjState = deathState;
				m_iStateTics = deathState.m_iTics;
				PS_DStateMachine.Action(deathState.m_MobjActions);
			} else {
				// Meaty explosion
				PS_DMobjState deathState = PS_DInfo.m_aMobjStates[m_MobjInfo.m_iXDeathState];
				m_MobjState = deathState;
				m_iStateTics = deathState.m_iTics;
				PS_DStateMachine.Action(deathState.m_MobjActions);
			}
			
			// Kills counter
			if (m_MobjInfo.m_iFlags & PS_EDMobjFlag.MF_COUNTKILL)
			{
				m_DMap.m_iKillsCollected++;
			}
			
			// Remove negative health
			m_iHealth = 0;
			
			// Boss counter
			m_DMap.m_DieSpecial.Die(this);
			
			// We died, no more pain...
			return;
		}
		
		// Pain simulation
		int painChance = m_MobjInfo.m_iPainChance;
		if (m_MobjInfo.m_iPainState != PS_DMobjStateNum.S_NULL && m_DMap.m_DMain.m_RandomGenerator.RandInt(0, 256) < painChance)
		{
			PS_DMobjState painState = PS_DInfo.m_aMobjStates[m_MobjInfo.m_iPainState];
			if (m_MobjState != painState)
				PS_DSoundEffect.PlaySound(m_MobjInfo.m_iPainSound, m_vPosition);
			m_MobjState = painState;
			m_iStateTics = painState.m_iTics;
			m_vVelocity = "0 0 0";
			PS_DStateMachine.Action(painState.m_MobjActions);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	// Trace movement path
	// For not player only check it to position empty
	vector TracePathBBOX(vector from, vector to, float height)
	{
		/* 
			There is continously collision detection before, but it's too costly for every entity...
		*/
		
		// Check of to position interset any "solid" LineDef or entity
		if (CheckPosition(to, height, m_BBOX.m_aOffsetsHalf))
			return from;
		
		return to;
	}
	
	//------------------------------------------------------------------------------------------------
	// Get first entity intersection by line from-to
	vector TracePathEntities(vector from, vector to, float height)
	{
		vector nearestIntersect = "inf inf inf";
		
		// Check current and neighbour cells
		PS_DBlockMapCell blockCell = m_DMap.m_DBlockMap.GetCell(from);
		foreach (PS_DBlockMapCell blockCell2 : blockCell.m_aNeighbours)
		{
			// Check all entities in cell
			foreach (PS_DEntity entity : blockCell2.m_sEntities)
			{
				if (entity != this &&                         // Not self
					 entity != m_AttackerEntity &&             // Not attacker for (for missiles)
					 entity.m_iFlags & PS_EDMobjFlag.MF_SOLID) // Solid thing
				{
					// Calculate intersection with BBOX
					vector intersect = GetBBOXIntersect(from, to, entity);
					if (intersect != "inf inf inf") // If intersected stop
					{
						// Can do false positive, but good enough
						m_bCollideEntity = true;
						m_CollidedEntity = entity;
						nearestIntersect = intersect;
						break;
					}
				}
			}
			
			// Intersection founded
			if (nearestIntersect != "inf inf inf")
				break;
		}
		
		if (nearestIntersect == "inf inf inf")
			nearestIntersect = to;
		nearestIntersect[2] = height;
		return nearestIntersect;
	}
	
	//------------------------------------------------------------------------------------------------
	// return intersection position with BBOX
	// "inf inf inf" is non
	vector GetBBOXIntersect(vector from, vector to)
	{
		if (!m_BBOX) // Hmm...
			return "inf inf inf";
		
		vector mergedSize = (m_BBOX.m_vSize) / 2;
		vector intersects[4];
		
		// Get intersection with all sides
		intersects[0] = PS_Math2D.linesIntersect(from, to, m_vPosition + Vector(-mergedSize[0],  mergedSize[1], 0), m_vPosition + Vector( mergedSize[0],  mergedSize[1], 0));
		intersects[1] = PS_Math2D.linesIntersect(from, to, m_vPosition + Vector( mergedSize[0],  mergedSize[1], 0), m_vPosition + Vector( mergedSize[0], -mergedSize[1], 0));
		intersects[2] = PS_Math2D.linesIntersect(from, to, m_vPosition + Vector( mergedSize[0], -mergedSize[1], 0), m_vPosition + Vector(-mergedSize[0], -mergedSize[1], 0));
		intersects[3] = PS_Math2D.linesIntersect(from, to, m_vPosition + Vector(-mergedSize[0], -mergedSize[1], 0), m_vPosition + Vector(-mergedSize[0],  mergedSize[1], 0));
		
		// Search first intersection
		float minDistance = float.MAX;
		vector minIntersect = "inf inf inf";
		for (int i = 0; i < 4; i++)
		{
			vector vectorIntersect = intersects[i] - from;
			float distance = vectorIntersect.Length();
			if (minDistance > distance)
			{
				minDistance = distance;
				m_vIntersectNormal = BBOX_NORMALS[i];
				minIntersect = intersects[i] + BBOX_NORMALS[i];
			}
		}
		return minIntersect;
	}
	
	//------------------------------------------------------------------------------------------------
	// return intersection position with other entity BBOX
	// Used sum of bboxes size
	// "inf inf inf" is non
	vector GetBBOXIntersect(vector from, vector to, PS_DEntity entity)
	{
		// merged BBOX
		vector mergedSize = (entity.m_BBOX.m_vSize + m_BBOX.m_vSize) / 2;
		
		// Get intersection with all sides
		vector intersects[4];
		intersects[0] = PS_Math2D.linesIntersect(from, to, entity.m_vPosition + Vector(-mergedSize[0],  mergedSize[1], 0), entity.m_vPosition + Vector( mergedSize[0],  mergedSize[1], 0));
		intersects[1] = PS_Math2D.linesIntersect(from, to, entity.m_vPosition + Vector( mergedSize[0],  mergedSize[1], 0), entity.m_vPosition + Vector( mergedSize[0], -mergedSize[1], 0));
		intersects[2] = PS_Math2D.linesIntersect(from, to, entity.m_vPosition + Vector( mergedSize[0], -mergedSize[1], 0), entity.m_vPosition + Vector(-mergedSize[0], -mergedSize[1], 0));
		intersects[3] = PS_Math2D.linesIntersect(from, to, entity.m_vPosition + Vector(-mergedSize[0], -mergedSize[1], 0), entity.m_vPosition + Vector(-mergedSize[0],  mergedSize[1], 0));
		
		// Search first intersection
		float minDistance = float.MAX;
		vector minIntersect = "inf inf inf";
		for (int i = 0; i < 4; i++)
		{
			vector vectorIntersect = intersects[i] - from;
			float distance = vectorIntersect.Length();
			if (minDistance > distance)
			{
				minDistance = distance;
				m_vIntersectNormal = BBOX_NORMALS[i];
				minIntersect = intersects[i] + BBOX_NORMALS[i];
			}
		}
		return minIntersect;
	}
	
	//------------------------------------------------------------------------------------------------
	// Fast bboxes intersection check
	bool IsBBOXesIntersect(vector position, PS_DEntity entity)
	{
		// Calculate size
		vector mergedSize = (entity.m_BBOX.m_vSize + m_BBOX.m_vSize);       
		// Get relative position
		vector bboxVector = (entity.m_vPosition - position) + mergedSize/2; 
		// Is position inside bbox
		return (bboxVector[0] > 0) && (bboxVector[1] > 0) && (bboxVector[0] < mergedSize[0]) && (bboxVector[1] < mergedSize[1]); 
	}
	
	//------------------------------------------------------------------------------------------------
	// Check is our BBOX intersect wall or entity
	bool CheckPosition(vector position, float height, vector offsets[4])
	{
		// Clrear collision flag
		m_bCollideEntity = false;
		
		// Update processing flags
		PS_DBlockMapCell.s_iFlag++;
		PS_DLineDef.s_iFlag++;
		for (int i = 0; i < 4; i++) // Check all intersected with BBOX block map cells
		{
			// Get cell by BBOX offset
			PS_DBlockMapCell blockCell = m_DMap.m_DBlockMap.GetCell(position + m_BBOX.m_aOffsets[i]);
			if (blockCell.m_iFlag == PS_DBlockMapCell.s_iFlag) // Skip if already processed
				continue;
			blockCell.m_iFlag = PS_DBlockMapCell.s_iFlag;
			
			// All line defs in block
			foreach (PS_DLineDef lineDef : blockCell.m_aLineDefs)
			{
				if (lineDef.m_iFlag == PS_DLineDef.s_iFlag) // Sikp if already processed
					continue;
				lineDef.m_iFlag = PS_DLineDef.s_iFlag;
				
				// Is LineDef solid?
				if (GetLineDefNormal(lineDef, height) != "0 0 0")
				{	
					// Is BBOX intersect?
					if (PS_Math2D.IsBBOXIntersect(lineDef.m_vStartingVertex, lineDef.m_vEndVertex, position, offsets))
					{
						// Collision founded
						m_CollidedLineDef = lineDef;
						return true;
					}
				}
			}
			foreach (PS_DEntity entity : blockCell.m_sEntities)
			{
				// Huh?
				if (!entity.m_BBOX)
					continue;
				// Don't collide with self
				if (entity == this)
					continue;
				// Skip missile attacker
				if (entity == m_AttackerEntity)
					continue;
				// Check is entity solid
				if (!(entity.m_iFlags & PS_EDMobjFlag.MF_SOLID))
					continue;
				
				// Is bboxes intersect?
				if (IsBBOXesIntersect(position, entity))
				{
					m_CollidedEntity = entity;
					return true;
				}
			}
		}
		
		// doesn't collide
		return false;
	}
	
	//------------------------------------------------------------------------------------------------
	// Get normal for solid LineDefs
	// "0 0 0" for not solid
	vector GetLineDefNormal(PS_DLineDef lineDef, float height)
	{
		if (!lineDef.m_BackSideDef) // Solid wall
			return lineDef.m_vNormal;
		if ((lineDef.m_iFlags & PS_EDLineDefsFlags.BLOCKING) && !(m_iFlags & PS_EDMobjFlag.MF_MISSILE)) // Solid two sided wall
			return lineDef.m_vNormal;
		if ((lineDef.m_iFlags & PS_EDLineDefsFlags.BLOCK_MONSTERS) && !(this.IsInherited(PS_DEntityPlayer))) // Solid two sided wall
			return lineDef.m_vNormal;
		
		// Get other side sector
		PS_DSector backSector;
		int side = PS_Math2D.PointSide(m_vPosition, lineDef.m_vStartingVertex, lineDef.m_vEndVertex);
		if (side < 0) // Reverse if on back side
			backSector = lineDef.m_BackSideDef.m_Sector;
		else
			backSector = lineDef.m_FrontSideDef.m_Sector;
		
		// Check other sector height
		// Too height
		if (backSector.m_iFloorHeight - height > 24) 
			return lineDef.m_vNormal;
		// Other sector floor too low (If can't dropoff)
		if (!(m_MobjInfo.m_iFlags & PS_EDMobjFlag.MF_DROPOFF) && (height - backSector.m_iFloorHeight > 24)) 
			return -lineDef.m_vNormal;
		// Ceiling too low
		if (backSector.m_iCeilingHeight - height < m_MobjInfo.m_iHeight) 
			return lineDef.m_vNormal;
		// Sector height too low
		if (backSector.m_iCeilingHeight - backSector.m_iFloorHeight < m_MobjInfo.m_iHeight) 
			return lineDef.m_vNormal;
		
		// Line def isn't solid
		return "0 0 0";
	}
	
	
	//------------------------------------------------------------------------------------------------
	vector TracePath(vector from, vector to, float height, bool activateSpecial)
	{
		vector nearestIntersect = "inf inf inf";
		vector cellPos = from;
		from[2] = 0;
		to[2] = 0;
		vector fromTo = to - from;
		float steps = fromTo.Length() / 128;
		fromTo.Normalize();
		fromTo *= 128;
		
		while (true)
		{
			PS_DBlockMapCell blockCell = m_DMap.m_DBlockMap.GetCell(cellPos);
			array<PS_DLineDef> intersectedLineDefs = {};
			foreach (PS_DLineDef lineDef : blockCell.m_aLineDefs)
			{
				vector intersect = PS_Math2D.linesIntersect(from, to, lineDef.m_vStartingVertex, lineDef.m_vEndVertex);
				if (intersect != "inf inf inf")
				{
					if (activateSpecial && lineDef.m_Special)
						lineDef.m_Special.Cross(lineDef, this);
					
					lineDef.m_vIntersection = intersect;
					vector toIntersection = intersect - from;
					lineDef.m_fIntersectionDistance = toIntersection.Length();
					
					bool inserted;
					for (int i = 0; i < intersectedLineDefs.Count(); i++)
					{
						PS_DLineDef lineDefOther = intersectedLineDefs[i];
						if (lineDefOther.m_fIntersectionDistance > lineDef.m_fIntersectionDistance)
						{
							inserted = true;
							intersectedLineDefs.InsertAt(lineDef, i);
							break;
						}
					}
					if (!inserted)
						intersectedLineDefs.Insert(lineDef);
				}
			}
			
			foreach (PS_DLineDef lineDef : intersectedLineDefs)
			{
				vector intersect = lineDef.m_vIntersection;
				vector normal = GetLineDefNormal(lineDef, height);
				if (normal != "0 0 0")
				{				
					int side = PS_Math2D.PointSide(m_vPosition, lineDef.m_vStartingVertex, lineDef.m_vEndVertex);
					vector wallNormal = normal;
					m_vIntersectNormal = wallNormal;
					intersect += wallNormal * 0.1;
					intersect[2] = height;
					nearestIntersect = intersect;
					m_CollidedLineDef = lineDef;
					break;
				}
			}
			
			// Line founded
			if (nearestIntersect != "inf inf inf")
				break;
			
			if (steps <= 0)
				break;
			
			if (steps > 1)
			{
				cellPos += fromTo;
				steps--;
			} else
			{
				cellPos += fromTo * steps;
				steps = 0;
			}
		}
		
		if (nearestIntersect == "inf inf inf")
			nearestIntersect = to;
		nearestIntersect[2] = height;
		return nearestIntersect;
	}
	// Really bad written collision checking END
	
	//------------------------------------------------------------------------------------------------
	void Accelerate(vector accVector)
	{
		m_vVelocity += accVector;
	}
	
	//------------------------------------------------------------------------------------------------
	void Rotate(float rotation)
	{
		m_fAngle += rotation;
	}
	
	//------------------------------------------------------------------------------------------------
	void PS_DEntity(PS_DMap dMap)
	{
		m_DMap = dMap;
	}
	
	//------------------------------------------------------------------------------------------------
	void Update()
	{
		if (m_MobjState)
			UpdateState();
		Move();
	}
	
	//------------------------------------------------------------------------------------------------
	void UpdateState()
	{
		if (m_iStateTics == 0)
		{
			if (m_MobjState.m_NextStateNum == PS_DMobjStateNum.S_NULL)
			{
				m_DMap.RemoveEntity(this);
				return;
			}
			
			PS_DStateMachine.s_ActionEntity = this;
			m_MobjState = PS_DInfo.m_aMobjStates[m_MobjState.m_NextStateNum];
			m_iStateTics = m_MobjState.m_iTics;
			PS_DStateMachine.Action(m_MobjState.m_MobjActions);
		} else {
			m_iStateTics--;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	bool IsBBOXIntersect(PS_DEntity other)
	{
		vector mergedSize = m_BBOX.m_vSize + other.m_BBOX.m_vSize;
		vector vectorBBOX = other.m_vPosition - m_vPosition + mergedSize*0.5;
		return vectorBBOX[0] > 0 && vectorBBOX[1] > 0 && vectorBBOX[0] < mergedSize[0] && vectorBBOX[1] < mergedSize[1];
	}
	
	//------------------------------------------------------------------------------------------------
	void WriteSave(FileHandle saveFile)
	{
		if (!m_MobjInfo)
			saveFile.Write(0, 4);
		else
			saveFile.Write(m_MobjInfo.m_iDoomedNum, 4);
		if (!m_MobjState)
			saveFile.Write(0, 2);
		else
			saveFile.Write(m_MobjState.m_iId, 2);
		
		saveFile.Write(m_iHealth, 2);
		saveFile.Write(m_iStateTics, 4);
		saveFile.Write(m_iReactionTime, 4);
		saveFile.Write(m_iMoveTics, 4);
		saveFile.Write(m_iMoveCount, 4);
		saveFile.Write(m_iFlags, 4);
		saveFile.Write(m_fAngle, 4);
		PS_FileHelper.WriteVector(saveFile, m_vPosition);
		PS_FileHelper.WriteVector(saveFile, m_vVelocity);
		saveFile.Write(m_bDead, 1);
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadSave(FileHandle saveFile)
	{
		int doomedNum;
		saveFile.Read(doomedNum, 4);
		if (doomedNum != 0)
		{
			m_MobjInfo = PS_DInfo.m_mMobjInfo[doomedNum];
			m_BBOX = new PS_DEntityBBox(m_MobjInfo);
		}
		int stateId;
		saveFile.Read(stateId, 2);
		if (stateId != 0)
			m_MobjState = PS_DInfo.m_aMobjStates[stateId];
		
		saveFile.Read(m_iHealth, 2);
		saveFile.Read(m_iStateTics, 4);
		saveFile.Read(m_iReactionTime, 4);
		saveFile.Read(m_iMoveTics, 4);
		saveFile.Read(m_iMoveCount, 4);
		saveFile.Read(m_iFlags, 4);
		saveFile.Read(m_fAngle, 4);
		m_vPosition = PS_FileHelper.ReadVector(saveFile);
		m_vVelocity = PS_FileHelper.ReadVector(saveFile);
		saveFile.Read(m_bDead, 1);
	}
}

class PS_DEntityBBox
{
	vector m_aOffsets[4];
	vector m_aOffsets_1[4];
	vector m_aOffsetsHalf[4];
	vector m_vSize;
	
	vector m_aOffsetsCenter[5];
	
	void PS_DEntityBBox(PS_DMobjInfo mobjInfo)
	{
		m_vSize = Vector(mobjInfo.m_iRadius * 2, mobjInfo.m_iRadius * 2, 0);
		m_aOffsets[0] = Vector(-mobjInfo.m_iRadius, -mobjInfo.m_iRadius, 0);
		m_aOffsets[1] = Vector( mobjInfo.m_iRadius, -mobjInfo.m_iRadius, 0);
		m_aOffsets[2] = Vector( mobjInfo.m_iRadius,  mobjInfo.m_iRadius, 0);
		m_aOffsets[3] = Vector(-mobjInfo.m_iRadius,  mobjInfo.m_iRadius, 0);
		
		m_aOffsets_1[0] = Vector(-mobjInfo.m_iRadius + 1, -mobjInfo.m_iRadius + 1, 0);
		m_aOffsets_1[1] = Vector( mobjInfo.m_iRadius - 1, -mobjInfo.m_iRadius + 1, 0);
		m_aOffsets_1[2] = Vector( mobjInfo.m_iRadius - 1,  mobjInfo.m_iRadius - 1, 0);
		m_aOffsets_1[3] = Vector(-mobjInfo.m_iRadius + 1,  mobjInfo.m_iRadius - 1, 0);
		
		m_aOffsetsHalf[0] = Vector(-mobjInfo.m_iRadius / 2, -mobjInfo.m_iRadius / 2, 0);
		m_aOffsetsHalf[1] = Vector( mobjInfo.m_iRadius / 2, -mobjInfo.m_iRadius / 2, 0);
		m_aOffsetsHalf[2] = Vector( mobjInfo.m_iRadius / 2,  mobjInfo.m_iRadius / 2, 0);
		m_aOffsetsHalf[3] = Vector(-mobjInfo.m_iRadius / 2,  mobjInfo.m_iRadius / 2, 0);
		
		m_aOffsetsCenter[0] = Vector(0, 0, 0);
		m_aOffsetsCenter[1] = Vector(-mobjInfo.m_iRadius, -mobjInfo.m_iRadius, 0);
		m_aOffsetsCenter[2] = Vector( mobjInfo.m_iRadius, -mobjInfo.m_iRadius, 0);
		m_aOffsetsCenter[3] = Vector( mobjInfo.m_iRadius,  mobjInfo.m_iRadius, 0);
		m_aOffsetsCenter[4] = Vector(-mobjInfo.m_iRadius,  mobjInfo.m_iRadius, 0);
	}
}









