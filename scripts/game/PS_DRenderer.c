class PS_DRenderer
{
	// Compiler limitation
	static const int SCREEN_WIDTH = PS_DConst.SCREEN_WIDTH;
	static const int SCREEN_HEIGHT = PS_DConst.SCREEN_HEIGHT;
	static const int SCREEN_WIDTH_1 = SCREEN_WIDTH + 1;
	
	// Cache
	static float m_aXToAngle[SCREEN_WIDTH_1]; // screen atan
	static int m_aBottom[SCREEN_WIDTH]; // For mem copy, lack of mem set :/
	static int m_aTop[SCREEN_WIDTH];
	static int m_aSpanZero[SCREEN_HEIGHT];
	static int m_aSpanMax[SCREEN_HEIGHT];
	
	// reinit every drawed frame
	static int m_aYUpperClipX[SCREEN_WIDTH];  // Current y for every x coord
	static int m_aYLowerClipX[SCREEN_WIDTH];
	static int m_aWallX[SCREEN_WIDTH_1]; // solid walls clip, use frame number
	static int m_iWallMinX; // Walls borders clip
	static int m_iWallMaxX;
	static ref array<ref PS_DVisPlane> m_aVisPlanes = {};
	static int m_iLastVisPlane; // Keep track of real visPlanes count
	static bool m_bExitBSP; // Force end bsp draw
	static PS_DVisPlane m_CeilingPlane;
	static PS_DVisPlane m_FloorPlane;
	
	// Floor columns rotation
	static int m_aSpanStart[SCREEN_HEIGHT];
	static int m_aSpanStop[SCREEN_HEIGHT];
	static float m_aYSlope[SCREEN_HEIGHT];
	
	// Sprites
	static ref array<ref PS_DVisSprite> m_aVisSprites = {};
	static int m_iVisSpritesCount; // Keep track of real visSprites count
	ref PS_DVisSprite m_LastVisSprite; // Entry point for sprites draw
	
	// Colors
	PS_DPalette m_CurrentPallete;      // Change globall pallet for special effects
	ref array<ref PS_DPalette> m_CurrentRemapedPallete; // Array of prebaked light levels, for reduce sampling
	PS_DColorMap m_ColorMap;           // Light levels
	int m_iExtraLight;
	
	// Global data
	PS_DMain m_DMain;          // our entry point
	PS_DMap m_DMap;            // Current map
	PS_DAssets m_DAssets;      // Textures and other non map related stuff
	PS_DEntityPlayer m_Player; // Player for camera calculation
	
	// 2d staff, 3d in edds asylum
	bool m_bDrawMap;
	ref array<ref CanvasWidgetCommand> m_aCanvasWidgetCommand;
	CanvasWidget m_wCanvas;
	
	void PS_DRenderer(PS_DMain dMain, PS_DMap dMap, PS_DAssets dAssets)
	{
		m_DMain = dMain;
		m_DMap = dMap;
		m_DAssets = dAssets;
		m_ColorMap = m_DAssets.m_aColorMaps[0];
		
		for (int x = 0; x < SCREEN_WIDTH+1; x++)
		{
			float angle = -Math.Atan2(PS_DConst.SCREEN_WIDTH_HALF - x, PS_DConst.SCREEN_Z);
			m_aXToAngle[x] = angle;
		}
		
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			m_aBottom[x] = 0;
			m_aTop[x] = int.MAX;
		}
		
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			m_aSpanMax[y] = int.MAX;
			
			float deltaY = Math.AbsFloat(y-PS_DConst.SCREEN_HEIGHT_HALF);
			if (deltaY == 0)
				deltaY = 0.00000001;
			m_aYSlope[y] = PS_DConst.SCREEN_WIDTH_HALF/deltaY;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void DrawFrame()
	{
		if (!m_DMain.m_EntityPlayer)
			return;
		m_Player = m_DMain.m_EntityPlayer;
		
		// Lazy canvas init
		if (!m_wCanvas)
			m_wCanvas = PS_EddsTextureCanvasComponent.m_w2DCanvas;
		
		m_bDrawMap = GetGame().GetInputManager().GetActionValue("DMap") != 0;
		
		// Clear 2D canvas
		m_aCanvasWidgetCommand = {};
		
		// draw 3D staff
		DrawBSP();
		StaticArray.Copy(m_aSpanStart, m_aSpanMax);
		StaticArray.Copy(m_aSpanStop, m_aSpanZero);
		DrawVisPlanes(); // Filled while BSP draw
		PS_DVisSprite visSprite = m_LastVisSprite;
		while (visSprite)
		{
			DrawSprite(visSprite);
			visSprite = visSprite.m_PrevVisSprite;
		}
		
		// draw 2D staff
		if (m_bDrawMap)
		{
			foreach (PS_DLineDef line: m_DMap.m_aLineDefs)
			{
				vector vertex1 = m_DMap.m_aVertexes[line.m_iStartVertex];
				vector vertex2 = m_DMap.m_aVertexes[line.m_iEndVertex];
				Draw2DLine(vertex1, vertex2, Color.Orange, 1);
			}
			foreach (vector vertex : m_DMap.m_aVertexes)
			{
				Draw2DPoint(vertex, Color.White, 4);
			}
			
			m_Player = m_DMain.m_EntityPlayer;
			Draw2DPoint(m_Player.m_vPosition, Color.Green, 4);
			vector FoVLeftPos = m_Player.m_vPosition + m_Player.m_vLeftFoV * PS_DConst.SCREEN_Z;
			vector FoVRightPos = m_Player.m_vPosition + m_Player.m_vRightFoV * PS_DConst.SCREEN_Z;
			Draw2DLine(m_Player.m_vPosition, FoVLeftPos, Color.Orange, 1);
			Draw2DLine(m_Player.m_vPosition, FoVRightPos, Color.Orange, 1);
			
			foreach (PS_DEntity entity : m_DMap.m_aEntities)
			{
				if (entity == null)
					continue;
				
				Draw2DPoint(entity.m_vPosition, Color.Yellow, 6);
				
				if (!entity.m_BBOX)
					continue;
				
				LineDrawCommand lineDrawCommand = new LineDrawCommand();
				lineDrawCommand.m_iColor = Color.BLUE;
				lineDrawCommand.m_fWidth = 2;
				lineDrawCommand.m_Vertices = {};
				lineDrawCommand.m_bShouldEnclose = true;
				for (int i = 0; i < 4; i++)
				{
					vector v1 = entity.m_vPosition + entity.m_BBOX.m_aOffsets[i];
					vector s1 = ToScreenSpace2D(v1);
					lineDrawCommand.m_Vertices.Insert(s1[0]);
					lineDrawCommand.m_Vertices.Insert(s1[1]);
				}
				m_aCanvasWidgetCommand.Insert(lineDrawCommand);
			}
			
			PS_DBlockMapCell cell = m_DMap.m_DBlockMap.GetCell(m_Player.m_vCameraPosition);
			/*
			foreach (PS_DLineDef lineDef : cell.m_aLineDefs)
			{
				Draw2DLine(lineDef.m_vStartingVertex, lineDef.m_vEndVertex, Color.Red, 6);
			}
			*/
			
			if (m_Player.m_TargetLineDef)
			{
				Draw2DLine(m_Player.m_TargetLineDef.m_vStartingVertex, m_Player.m_TargetLineDef.m_vEndVertex, Color.Blue, 6);
				Draw2DLine(m_Player.m_vPosition, m_DMap.m_DBlockMap.s_vIntersect, Color.Orange, 2);
			}
			
			foreach (PS_DBlockMapCell cellBlock : m_DMap.m_DBlockMap.m_aCells)
			{
				vector position = Vector(cellBlock.m_iX * 128 + m_DMap.m_DBlockMap.m_iGridOriginX, cellBlock.m_iY * 128 + m_DMap.m_DBlockMap.m_iGridOriginY, 0);
				Draw2DLine(position, position + "128 0 0", Color.Black, 1);
				Draw2DLine(position, position + "0 128 0", Color.Black, 1);
			}
			foreach (PS_DBlockMapCell cellBlock : cell.m_aNeighbours)
			{
				vector position = Vector(cellBlock.m_iX * 128 + m_DMap.m_DBlockMap.m_iGridOriginX, cellBlock.m_iY * 128 + m_DMap.m_DBlockMap.m_iGridOriginY, 0);
				Draw2DLine(position, position + "128 0 0", Color.Red, 1);
				Draw2DLine(position, position + "0 128 0", Color.Red, 1);
			}
			
			/*
			if (m_Player.m_SubSector)
			{
				foreach (PS_DSeg seg : m_Player.m_SubSector.m_aSegments)
				{
					Draw2DLine(seg.m_vStartingVertex, seg.m_vEndingVertex, Color.White, 3);
				}
			}
			*/
			
			Draw2DLine(m_Player.m_vPosition, m_Player.m_vPosition + m_Player.m_vToTargetVector, Color.Red, 3);
			
			
			if (m_Player.m_TargetEntity)
			{
				Draw2DLine(m_Player.m_vPosition, m_Player.m_TargetEntity.m_vPosition, Color.Blue, 2);
			}
			
			/*
			if (m_Player.m_Sector)
			{
				foreach (PS_DSector sector : m_DMap.m_aSectors)
				{
					if (m_DMap.IsRejected(m_Player.m_Sector.m_iId, sector.m_iId))
					{
						foreach (PS_DSideDef sideDef : sector.m_aSideDefs)
						{
							PS_DLineDef lineDef = sideDef.m_LineDef;
							Draw2DLine(lineDef.m_vStartingVertex, lineDef.m_vEndVertex, Color.Yellow, 4);
						}
					}
				}
			}
			*/
		}
		
		// update 2D canvas
		m_wCanvas.SetDrawCommands(m_aCanvasWidgetCommand);
	}
	
	//------------------------------------------------------------------------------------------------
	// Main 3D entry point
	// Start drawing map by BSP
	void DrawBSP()
	{
		m_CurrentPallete = m_DAssets.m_aPalletes[0];
		m_CurrentRemapedPallete = m_DAssets.m_aColoredPalletes[0];
		if (m_Player.m_iHazardTicks > 0)
		{
			m_CurrentPallete = m_DAssets.m_aPalletes[13];
			m_CurrentRemapedPallete = m_DAssets.m_aColoredPalletes[13];
		}
		if (m_Player.m_iPickupTicks > 0)
		{
			m_CurrentPallete = m_DAssets.m_aPalletes[9 + m_Player.m_iPickupTicks];
			m_CurrentRemapedPallete = m_DAssets.m_aColoredPalletes[9 + m_Player.m_iPickupTicks];
		}
		if (m_Player.m_iDamageTicks > 0)
		{
			int damageTicks = Math.Min(m_Player.m_iDamageTicks, 16);
			m_CurrentPallete = m_DAssets.m_aPalletes[damageTicks / 2];
			m_CurrentRemapedPallete = m_DAssets.m_aColoredPalletes[damageTicks / 2];
		}
		m_iExtraLight = m_Player.m_iExtraLight;
		if (m_DMain.m_bInMenu)
			m_iExtraLight -= 6;
		// Reset every frame staff
		m_LastVisSprite = null; // Clear sprites chain
		m_iVisSpritesCount = 0;
		m_bExitBSP = false; // Clear exit flag
		for (int x = 0; x < SCREEN_WIDTH; x++) // Unclip full screen
		{
			m_aYUpperClipX[x] = -1;
			m_aYLowerClipX[x] = PS_DConst.SCREEN_HEIGHT_VIEW; // Remove pixels under status bar
		}
		m_iLastVisPlane = 0; // "Clear" vis planes
		
		m_iWallMinX = 0;
		m_iWallMaxX = PS_DConst.SCREEN_WIDTH - 1;
		
		// Start draw recursion from root
		DrawBSPRec(m_DMap.m_RootNode);
	}
	
	//------------------------------------------------------------------------------------------------
	// Recursive process all BSP leafs
	void DrawBSPRec(PS_DNode node)
	{
		// Screen fully filed, stop drawing recursion
		if (m_bExitBSP)
			return;
		
		// Get BSP leafe side, just dot, it's prebaked
		vector toPos = m_Player.m_vCameraPosition - node.m_vPartition;
		float side = PS_Math2D.Dot2D(node.m_vPartitionDelta, toPos);
		
		// Left (Or right?) side, I don't really known - That work? That work.
		if (side < 0)
		{
			if (node.m_LeftNode)
				DrawBSPRec(node.m_LeftNode); // Next node
			else
				// Nodes end, we are in our convex subSector
				DrawSubSector(node.m_LeftSubSector); 
			//if (node.m_LeftBBox.CheckBBox(m_Player)) // Skip offscreen nodes (Broke sprite rendering?)
				if (node.m_RightNode)
					DrawBSPRec(node.m_RightNode);
				else
					DrawSubSector(node.m_RightSubSector);
		}
		else
		{
			// Like left (Or right) side.
			if (node.m_RightNode)
				DrawBSPRec(node.m_RightNode);
			else
				DrawSubSector(node.m_RightSubSector);
			//if (node.m_RightBBox.CheckBBox(m_Player))
				if (node.m_LeftNode)
					DrawBSPRec(node.m_LeftNode);
				else
					DrawSubSector(node.m_LeftSubSector);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	// Draw all segments
	void DrawSubSector(PS_DSubSector subSector)
	{
		// Create vis sprite for each entity
		foreach (PS_DEntity entity : subSector.m_sEntities)
		{
			AddVisSprite(entity);
		}
		
		foreach (PS_DSeg seg : subSector.m_aSegments)
		{
			// Prepare segment for draw
			// And some visibility cliping
			if (!seg.CalculateAngles(m_Player, m_iWallMinX, m_iWallMaxX + 1))
				continue; // Offscreen skip
			
			// Try find already existed VisPlanes fo ceiling and floor
			PS_DSector frontSector = seg.m_FrontSector;
			if (frontSector.m_iFloorHeight <= m_Player.m_vCameraPosition[2]) // Floor mean to be drawed
				m_FloorPlane = FindVisPlane(frontSector.m_iFloorHeight, frontSector.m_FloorTexture, frontSector.m_iLightLevel);
			else
				m_FloorPlane = null;
			
			// If sky create plane anyway
			bool isSky;
			if (seg.m_FrontSector)
				isSky = (seg.m_FrontSector.m_CeilingTexture.m_sName == "F_SKY1");
			
			if (frontSector.m_iCeilingHeight >= m_Player.m_vCameraPosition[2] || isSky) // Ceiling mean to be drawed
				m_CeilingPlane = FindVisPlane(frontSector.m_iCeilingHeight, frontSector.m_CeilingTexture, frontSector.m_iLightLevel);
			else
				m_CeilingPlane = null;
			
			// Draw wall
			DrawSegment(seg);	
			
			// 2D map draw
			if (m_bDrawMap)
				DrawSegment2D(seg);
			
			// screen fully filed, stop drawing
			if (m_bExitBSP) 
				return;
		}
		
	}
	
	//------------------------------------------------------------------------------------------------
	// Save vis sprite for far to near render
	void AddVisSprite(PS_DEntity entity)
	{
		if (entity.m_iRenderFrame == m_DMain.m_iFrameNum)
		entity.m_iRenderFrame = m_DMain.m_iFrameNum;
		
		// Sprite attached to state, even for static things
		PS_DMobjState state = entity.m_MobjState;
		if (!state)
			return;
		if (entity.m_iFlags & PS_EDMobjFlag.MF_NOSECTOR)
			return;

		// Calculate screen distance
		vector vectorToEntity = entity.m_vPosition - m_Player.m_vCameraPosition;
		float gxt = vectorToEntity[0] * Math.Cos(m_Player.m_fAngle - Math.PI_HALF); 
	   float gyt = vectorToEntity[1] * Math.Sin(m_Player.m_fAngle - Math.PI_HALF);  
	   float tz = gxt-gyt; 
		if (tz <= 0)
			return;
		
		// Calculate screen x
		float xScale = PS_DConst.SCREEN_WIDTH_HALF / tz;
		gxt = vectorToEntity[0] * Math.Sin(m_Player.m_fAngle - Math.PI_HALF);  
	   gyt = vectorToEntity[1] * Math.Cos(m_Player.m_fAngle - Math.PI_HALF); 
	   float tx = -(gyt+gxt);
		if (tx > PS_DConst.SCREEN_WIDTH)
			return;
		
		// Get entity sprite
		int frame = state.m_iFrame;
		bool fullBright;
		if (frame > 32767) // last short bit set, draw 
		{
			fullBright = true;
			frame &= 32767;
		}
		
		float angleToEntity = Math.Atan2(vectorToEntity[1], vectorToEntity[0]);
		int direction = Math.Repeat((entity.m_fAngle + angleToEntity + PS_Math2D.PI_QUAT/2) / PS_Math2D.PI_QUAT, 8);
		PS_DPatch patch = m_DAssets.m_aSprites[state.m_SpriteNum].m_aFrames[frame][direction];
		bool flip = m_DAssets.m_aSprites[state.m_SpriteNum].m_aFlips[frame][direction];
		
		// Calculate x size
		tx -= patch.m_DPatchHeader.m_iLeftOffset;
		int x1 = PS_DConst.SCREEN_WIDTH_HALF + (tx * xScale);
		tx += patch.m_DPatchHeader.m_iWidth;
		int x2 = PS_DConst.SCREEN_WIDTH_HALF + (tx * xScale) - 1;
		
		// Full offscreen skip
		if (x2 < 0)
			return;
		if (x1 > PS_DConst.SCREEN_WIDTH)
			return;
		
		// Save all data to sprite
		PS_DVisSprite sprite = CreateVisSprite();
		sprite.m_fDistance = tz;
		sprite.m_iMobjFlags = entity.m_iFlags;
		sprite.m_fScale = xScale;
		sprite.m_vPosition = entity.m_vPosition;
		sprite.m_fTop = Math.Floor(entity.m_vPosition[2]) + (float) patch.m_DPatchHeader.m_iTopOffset;
		sprite.m_fTextureMiddle = Math.Floor(sprite.m_fTop - m_Player.m_vCameraPosition[2] + 0.5);
		sprite.m_iX1 = Math.Clamp(x1, 0, PS_DConst.SCREEN_WIDTH - 1);
		sprite.m_iX2 = Math.Clamp(x2, 0, PS_DConst.SCREEN_WIDTH - 1);
		sprite.m_Patch = patch;
		if (entity.m_Sector)
		{
			if (fullBright)
				sprite.m_iLightLevel = 31;
			else {
				// Light level shitpost
				int lightIndex = Math.AbsInt(xScale * PS_DConst.LIGHT_WORLD_SCALE_SPRITE);
				if (lightIndex > PS_DConst.LIGHT_Z_MAX)
					lightIndex = PS_DConst.LIGHT_Z_MAX;
				int lightLevel = entity.m_Sector.m_iLightLevel;
				lightLevel += m_iExtraLight;
				lightLevel += lightIndex;
				lightLevel = Math.Clamp(lightLevel, 0, PS_DConst.MAX_LIGHT_LEVEL);
				sprite.m_iLightLevel = lightLevel;
			}
		}
			
		
		// If sprite fliped, inverse draw direction
		float invesedScale = 1 / xScale;
		if (flip)
		{
			sprite.m_fStartFrac = patch.m_DPatchHeader.m_iWidth - 1;
			sprite.m_fXInversedScale = -invesedScale;
		}
		else
		{
			sprite.m_fStartFrac = 0;
			sprite.m_fXInversedScale = invesedScale;
		}
		
		// Skip offscrean part
		if (sprite.m_iX1 > x1)
			sprite.m_fStartFrac += sprite.m_fXInversedScale * (sprite.m_iX1 - x1);
		
		// Copy clipping data
		// DOOM used much more complex method. I don't mind :|
		StaticArray.Copy(sprite.m_iUpperClip, m_aYUpperClipX);
		StaticArray.Copy(sprite.m_iLowerClip, m_aYLowerClipX);
		StaticArray.Copy(sprite.m_iWallClip, m_aWallX);
		
		// For some reason this little sort really hard for me... :/
		// First sprite in chain
		
		if (!m_LastVisSprite)
		{
			sprite.m_PrevVisSprite = null;
			m_LastVisSprite = sprite;
		} else {
			// find neare sprite than new
			PS_DVisSprite spriteOther = m_LastVisSprite;
			PS_DVisSprite spriteOtherNext;
			while (spriteOther)
			{
				// first point than near
				if (spriteOther.m_fDistance < sprite.m_fDistance)
					break;
				
				// next near sprite
				spriteOtherNext = spriteOther;
				spriteOther = spriteOther.m_PrevVisSprite;
			}
			
			// attach before other
			if (spriteOtherNext)
			{
				spriteOtherNext.m_PrevVisSprite = sprite;
				sprite.m_PrevVisSprite = spriteOther;
			} else { // New point farrest
				sprite.m_PrevVisSprite = m_LastVisSprite;
				m_LastVisSprite = sprite;
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	// Front to back drawing
	void DrawSprite(PS_DVisSprite sprite)
	{
		PS_DPatch patch = sprite.m_Patch;
		PS_DTextureMap textureMap = sprite.m_TextureMap;
		
		float textureColumn = sprite.m_fStartFrac;
		
		// Sprite Y bounds
		float spryteYScale = sprite.m_fScale;
		float textureAltitude = Math.Floor(sprite.m_fTextureMiddle);
		int height;
		if (patch)
			height = patch.m_DPatchHeader.m_iHeight;
		else
			height = textureMap.m_iHeight;
		int width;
		if (patch)
			width = patch.m_DPatchHeader.m_iWidth;
		else
			width = textureMap.m_iWidth;
		
		array<int> pixels;
		if (patch)
			pixels = patch.m_DTexture.m_aPixels;
		else
			pixels = textureMap.m_TexturePixels.m_aPixels;
		
		float worldDistance = sprite.m_fDistance;
		float worldCenterAngle = sprite.m_fWorldCenterAngle;
		
		float inversedScaleY = 1 / spryteYScale;
		float spriteTopScreen = Math.Floor(PS_DConst.SCREEN_HEIGHT_HALF - spryteYScale * textureAltitude);
		float spriteBottomScreen = Math.Ceil(PS_DConst.SCREEN_HEIGHT_HALF - spryteYScale * (textureAltitude - height));
		if (sprite) // TODO fix sprites 
			spriteTopScreen += spryteYScale*2;
		
		// foreach columns in sprite
		bool IsPowerOfTwo = (width & (width - 1)) == 0;
		int mask = width - 1;
		for (int x = sprite.m_iX1; x < sprite.m_iX2; x++)
		{
			if (textureMap)
			{
				float angle = worldCenterAngle + m_aXToAngle[x];
				textureColumn = worldDistance * Math.Tan(angle) - sprite.m_fStartFrac;
				inversedScaleY = 1 / spryteYScale;
				spriteTopScreen = PS_DConst.SCREEN_HEIGHT_HALF - spryteYScale * textureAltitude;
				spriteBottomScreen = PS_DConst.SCREEN_HEIGHT_HALF - spryteYScale * (textureAltitude - height);
			}
			
			// skip columns behind solid walls
			if (sprite.m_iWallClip[x] != m_DMain.m_iFrameNum)
			{
				// Clip y to screen size
				int y1 = Math.Max(spriteTopScreen, sprite.m_iUpperClip[x] - 1);
				int y2 = Math.Min(spriteBottomScreen, sprite.m_iLowerClip[x] + 1);
				if (y1 <= y2)
				{
					int textureColumnR;
					if (IsPowerOfTwo)
						textureColumnR = (int) textureColumn & mask;
					else
						textureColumnR = Math.Repeat(textureColumn, width);
					DrawVerticalLineSprite(x, y1, y2, pixels, height, width, textureColumnR, textureAltitude, inversedScaleY, sprite.m_iLightLevel);
				}
			}
			if (sprite)
				textureColumn += sprite.m_fXInversedScale;
			if (textureMap)
				spryteYScale += sprite.m_fScaleStep;
		}
		
		// 2D staff
		if (m_bDrawMap)
		{
			if (sprite.m_PrevVisSprite)
				Draw2DLine(sprite.m_vPosition, sprite.m_PrevVisSprite.m_vPosition, Color.Red, 2);
			Draw2DPoint(sprite.m_vPosition, Color.Red, 8);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	// Reduce allocations
	PS_DVisSprite CreateVisSprite()
	{
		PS_DVisSprite visSprite;
		if (m_aVisSprites.Count() > m_iVisSpritesCount)
		{
			visSprite = m_aVisSprites[m_iVisSpritesCount];
			visSprite.m_PrevVisSprite = null;
			visSprite.m_Patch = null;
			visSprite.m_TextureMap = null;
		} else {
			visSprite = new PS_DVisSprite();
			m_aVisSprites.Insert(visSprite);
		}
		m_iVisSpritesCount++;
		return visSprite;
	}
	
	//------------------------------------------------------------------------------------------------
	void DrawSegment(PS_DSeg segment)
	{
		if (segment.m_iX1 == segment.m_iX2)
			return;
		
		if (!segment.m_BackSector)
		{
			ClipDrawWall(segment, true);
			return;
		}
		
		if (segment.m_FrontSector.m_iCeilingHeight != segment.m_BackSector.m_iCeilingHeight ||
			 segment.m_FrontSector.m_iFloorHeight != segment.m_BackSector.m_iFloorHeight)
		{
			ClipDrawWall(segment);
			return;
		}
		
		if (segment.m_BackSector.m_sCeilingTextureName == segment.m_FrontSector.m_sCeilingTextureName &&
			segment.m_BackSector.m_sFloorTextureName == segment.m_FrontSector.m_sFloorTextureName &&
			segment.m_BackSector.m_iLightLevel == segment.m_FrontSector.m_iLightLevel &&
			segment.m_LineDef.m_FrontSideDef.m_sMiddleTextureName == "-") 
			return;
		
		ClipDrawWall(segment);
	}
	
	//------------------------------------------------------------------------------------------------
	void ClipDrawWall(PS_DSeg segment, bool solid = false)
	{
		bool drawed = false;
		int startX = -1;
		
		int x1 = segment.m_iX1;
		int x2 = segment.m_iX2;
		for (int x = x1; x < x2; x++)
		{
			if (m_aWallX[x] == m_DMain.m_iFrameNum)
			{
				if (startX != -1)
				{
					drawed = true;
					if (solid)
						DrawWallRange(segment, startX, x);
					else
						DrawPortalWallRange(segment, startX, x);
					startX = -1;
				}
			} else {
				if (startX == -1)
					startX = x;
			}
		}
		
		if (startX != -1)
		{
			drawed = true;
			if (solid)
				DrawWallRange(segment, startX, x2);
			else
				DrawPortalWallRange(segment, startX, x2);
			startX = -1;
		}
		
		while (m_aWallX[m_iWallMinX] == m_DMain.m_iFrameNum)
		{
			m_iWallMinX++;
			if (m_iWallMinX > m_iWallMaxX)
			{
				m_bExitBSP = true;
				return;
			}
		}
		
		while (m_aWallX[m_iWallMaxX] == m_DMain.m_iFrameNum)
		{
			m_iWallMaxX--;
			if (m_iWallMinX > m_iWallMaxX)
			{
				m_bExitBSP = true;
				return;
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	// Portals, same as solid, but two in one
	void DrawPortalWallRange(PS_DSeg segment, int x1, int x2)
	{
		// Height
		float worldFrontZ1 = segment.m_FrontSector.m_iCeilingHeight - m_Player.m_vCameraPosition[2];
		float worldBackZ1  = segment.m_BackSector.m_iCeilingHeight  - m_Player.m_vCameraPosition[2];
		float worldFrontZ2 = segment.m_FrontSector.m_iFloorHeight   - m_Player.m_vCameraPosition[2];
		float worldBackZ2  = segment.m_BackSector.m_iFloorHeight    - m_Player.m_vCameraPosition[2];
		
		if (segment.m_FrontSector.m_CeilingTexture.m_sName == "F_SKY1" && segment.m_BackSector.m_CeilingTexture.m_sName == "F_SKY1")
		{
			worldFrontZ1 = worldBackZ1;
		}
		
		// Draw need check
		bool drawUpperWall;
		bool drawLowerWall;
		bool drawFloor;
		bool drawCeil;
		bool drawMiddleWall;
		if (worldFrontZ1 != worldBackZ1 ||
			segment.m_FrontSector.m_iLightLevel != segment.m_BackSector.m_iLightLevel ||
			segment.m_FrontSector.m_sCeilingTextureName != segment.m_BackSector.m_sCeilingTextureName)
		{
			drawUpperWall = segment.m_FrontSideDef.m_sUpperTextureName != "-" && worldBackZ1 < worldFrontZ1;
			drawCeil = worldFrontZ1 >= 0;
		}
		if (worldFrontZ2 != worldBackZ2 ||
			segment.m_FrontSector.m_sFloorTextureName != segment.m_BackSector.m_sFloorTextureName ||
			segment.m_FrontSector.m_iLightLevel != segment.m_BackSector.m_iLightLevel)
		{
			drawLowerWall = segment.m_FrontSideDef.m_sLowerTextureName != "-" && worldBackZ2 > worldFrontZ2;
			drawFloor = worldFrontZ2 <= 0;
		}
		drawMiddleWall = segment.m_FrontSideDef.m_sMiddleTextureName != "-";
		
		if (!drawUpperWall && !drawCeil && !drawLowerWall && !drawFloor && !drawMiddleWall)
			return;
		
		// Calculate scale for perspective correction
		// Most difficult part for me - some angles + distance then Cos and !!!BAM!!! 3D space. frkg magic
		float worldNormalAngle = segment.m_fAngle;
		float offsetAngle = worldNormalAngle - segment.m_fWorldAngle1;
		vector pos2d = m_Player.m_vCameraPosition;
		pos2d[2] = 0;
		float hypotenuse = vector.Distance(pos2d, segment.m_vStartingVertex);
		float worldDistance = hypotenuse * Math.Cos(offsetAngle+Math.PI_HALF);
		float RealWorldScaleStep;
		float worldScale = ScaleFromGlobalAngle(x1, worldNormalAngle, worldDistance);
		if (x1 < x2)
		{
			float scale2 = ScaleFromGlobalAngle(x2, worldNormalAngle, worldDistance);
			RealWorldScaleStep = (scale2 - worldScale) / (x2 - x1);
		}
		else
			RealWorldScaleStep = 0;
		float wallY1 = PS_DConst.SCREEN_HEIGHT_HALF - worldFrontZ1 * worldScale;
		float wallY1Step = -RealWorldScaleStep * worldFrontZ1;
		float wallY2 = PS_DConst.SCREEN_HEIGHT_HALF - worldFrontZ2 * worldScale;
		float wallY2Step = -RealWorldScaleStep * worldFrontZ2;
		
		// Portal walls
		float portalY1;
		float portalY1Step;
		float portalY2;
		float portalY2Step;
		
		// Textures
		bool segmentTextured = drawUpperWall || drawLowerWall || drawMiddleWall;
		PS_DTextureMap upperTexture;
		PS_DTextureMap lowerTexture;
		PS_DTextureMap middleTexture;
		float upperTextureAltitude = worldFrontZ1;
		float lowerTextureAltitude = worldFrontZ1;
		float middleTextureAltitude = worldFrontZ1;
		float worldOffset;
		float worldCenterAngle;
		if (segmentTextured)
		{
			worldOffset = hypotenuse * Math.Sin(offsetAngle+Math.PI_HALF);
			worldOffset += segment.m_iOffset + segment.m_FrontSideDef.m_xOffset;
			worldCenterAngle = worldNormalAngle + m_Player.m_fAngle;
		}
		// Textures END
		
		if (drawUpperWall)
		{
			// texture
			upperTexture = m_DAssets.m_mTextures[segment.m_FrontSideDef.m_sUpperTextureName];
			if (!(segment.m_LineDef.m_iFlags & PS_EDLineDefsFlags.DONT_PEG_TOP))
			{
				upperTextureAltitude = segment.m_BackSector.m_iCeilingHeight + upperTexture.m_iHeight - m_Player.m_vCameraPosition[2];
			}
			upperTextureAltitude += segment.m_FrontSideDef.m_yOffset;
			
			// Height
			if (worldBackZ1 > worldFrontZ2)
			{
				portalY1 = PS_DConst.SCREEN_HEIGHT_HALF - worldBackZ1 * worldScale;
				portalY1Step = -RealWorldScaleStep * worldBackZ1;
			} else {
				portalY1 = wallY2;
				portalY1Step = wallY2Step;
			}
		}
		if (drawLowerWall)
		{
			// texture
			lowerTexture = m_DAssets.m_mTextures[segment.m_FrontSideDef.m_sLowerTextureName];
			if (!(segment.m_LineDef.m_iFlags & PS_EDLineDefsFlags.DONT_PEG_BOTTOM))
			{
				lowerTextureAltitude = worldBackZ2;
			}
			lowerTextureAltitude += segment.m_FrontSideDef.m_yOffset;
			
			// Height
			if (worldBackZ2 < worldFrontZ1)
			{
				portalY2 = PS_DConst.SCREEN_HEIGHT_HALF - worldBackZ2 * worldScale;
				portalY2Step = -RealWorldScaleStep * worldBackZ2;
			} else {
				portalY2 = wallY1;
				portalY2Step = wallY1Step;
			}
		}
		
		// VisPlanes merge check
		if (drawCeil)
			m_CeilingPlane = CheckVisPlane(m_CeilingPlane, x1, x2);
		if (drawFloor)
			m_FloorPlane = CheckVisPlane(m_FloorPlane, x1, x2);
		
		
		// Not actually draw, only save draw visSprite
		PS_DVisSprite sprite;
		if (drawMiddleWall)
		{
			float portalY3;
			float portalY3Step;
			middleTexture = m_DAssets.m_mTextures[segment.m_FrontSideDef.m_sMiddleTextureName];
			
			sprite = CreateVisSprite();
			sprite.m_iX1 = Math.Max(x1-2, 0); // Huh?
			sprite.m_iX2 = x2;
			sprite.m_TextureMap = middleTexture;
			
			// TODO: correct distance
			sprite.m_fDistance = worldDistance;
			
			sprite.m_fStartFrac = worldOffset;
			sprite.m_fXInversedScale = 1.0 / worldScale;
			sprite.m_fWorldCenterAngle = worldCenterAngle;
			sprite.m_fScale = worldScale;
			sprite.m_fScaleStep = RealWorldScaleStep;
			sprite.m_fTop = 0;
			
			if (segment.m_iDirection)
				sprite.m_fTextureMiddle = Math.Floor(worldFrontZ1 + segment.m_FrontSideDef.m_yOffset + 0.5);
			else
				sprite.m_fTextureMiddle = Math.Floor(worldBackZ1 + segment.m_FrontSideDef.m_yOffset + 0.5);
			
			// Light level
			int lightLevel = segment.m_FrontSector.m_iLightLevel;
			lightLevel += m_iExtraLight;
			lightLevel = Math.Clamp(lightLevel, 0, PS_DConst.MAX_LIGHT_LEVEL);
			sprite.m_iLightLevel = lightLevel;
			
			sprite.m_PrevVisSprite = m_LastVisSprite;
			m_LastVisSprite = sprite;
		}
		
		for (int x = x1; x < x2; x++)
		{
			float drawWallY1 = wallY1 - 1;
			float drawWallY2 = wallY2;
			
			float inversedScale;
			int textureColumn;
			if (segmentTextured)
			{
				float angle = worldCenterAngle + m_aXToAngle[x];
				textureColumn = worldDistance * Math.Tan(angle) - worldOffset;
				inversedScale = 1.0 / worldScale;
			}
			
			// Upper
			if (drawUpperWall)
			{
				float drawUpperWallY1 = wallY1 - 1;
				float drawUpperWallY2 = portalY1;
				
				if (drawCeil)
				{
					float top = m_aYUpperClipX[x] + 1;
					float bottom = Math.Min(drawWallY1 - 1, m_aYLowerClipX[x] - 1);
					if (top <= bottom)
					{
						m_CeilingPlane.m_aTop[x] = top;
						m_CeilingPlane.m_aBottom[x] = bottom;
					}
				}
				
				// Wall
				float wy1 = Math.Max(drawUpperWallY1, m_aYUpperClipX[x] + 1);
				float wy2 = Math.Min(drawUpperWallY2, m_aYLowerClipX[x] - 1);
				DrawVerticalLineTextured(x, wy1, wy2
					, upperTexture, textureColumn, upperTextureAltitude, inversedScale
					, segment.m_FrontSector.m_iLightLevel, worldScale);
				
				if (m_aYUpperClipX[x] < wy2)
				{
					m_aYUpperClipX[x] = wy2;
					if (m_aYLowerClipX[x] <= m_aYUpperClipX[x] + 1)
						m_aWallX[x] = m_DMain.m_iFrameNum;
				}
				
				portalY1 += portalY1Step;
			}
			else if (drawCeil)
			{
				float top = m_aYUpperClipX[x] + 1;
				float bottom = Math.Min(drawWallY1 - 1, m_aYLowerClipX[x] - 1);
				if (top <= bottom)
				{
					m_CeilingPlane.m_aTop[x] = top;
					m_CeilingPlane.m_aBottom[x] = bottom;
				}
				
				if (m_aYUpperClipX[x] < bottom)
				{
					m_aYUpperClipX[x] = bottom;
					if (m_aYLowerClipX[x] <= m_aYUpperClipX[x] + 1)
						m_aWallX[x] = m_DMain.m_iFrameNum;
				}
			}
			
			// Lower
			if (drawLowerWall)
			{
				float drawLowerWallY1 = portalY2 - 1;
				float drawLowerWallY2 = wallY2;
				
				if (drawFloor)
				{
					int top = Math.Max(drawWallY2 + 1, m_aYUpperClipX[x] + 1);
					int bottom = m_aYLowerClipX[x] - 1;
					if (top <= bottom)
					{
						m_FloorPlane.m_aTop[x] = top;
						m_FloorPlane.m_aBottom[x] = bottom;
					}
				}
				
				// Wall
				float wy1 = Math.Max(drawLowerWallY1, m_aYUpperClipX[x] + 1);
				float wy2 = Math.Min(drawLowerWallY2, m_aYLowerClipX[x] - 1);
				DrawVerticalLineTextured(x, wy1, wy2
					, lowerTexture, textureColumn, lowerTextureAltitude, inversedScale
					, segment.m_FrontSector.m_iLightLevel, worldScale);
				
				if (m_aYLowerClipX[x] > wy1)
				{
					m_aYLowerClipX[x] = wy1;
					if (m_aYLowerClipX[x] <= m_aYUpperClipX[x] + 1)
						m_aWallX[x] = m_DMain.m_iFrameNum;
				}
				
				portalY2 += portalY2Step;
			}
			else if (drawFloor)
			{
				int top = Math.Max(drawWallY2 + 1, m_aYUpperClipX[x] + 1);
				int bottom = m_aYLowerClipX[x] - 1;
				if (top <= bottom)
				{
					m_FloorPlane.m_aTop[x] = top;
					m_FloorPlane.m_aBottom[x] = bottom;
				}
				
				if (m_aYLowerClipX[x] > top)
				{
					m_aYLowerClipX[x] = top;
					if (m_aYLowerClipX[x] <= m_aYUpperClipX[x] + 1)
						m_aWallX[x] = m_DMain.m_iFrameNum;
				}
			}
			
			worldScale += RealWorldScaleStep;
			wallY1 += wallY1Step;
			wallY2 += wallY2Step;
		}
		
		if (sprite)
		{
			StaticArray.Copy(sprite.m_iUpperClip, m_aYUpperClipX);
			StaticArray.Copy(sprite.m_iLowerClip, m_aYLowerClipX);
			StaticArray.Copy(sprite.m_iWallClip, m_aWallX);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	// Solid walls
	void DrawWallRange(PS_DSeg segment, int x1, int x2)
	{
		for (int x = x1; x < x2; x++)
			m_aWallX[x] = m_DMain.m_iFrameNum;
		
		float worldFrontZ1 = segment.m_FrontSector.m_iCeilingHeight - m_Player.m_vCameraPosition[2];
		float worldFrontZ2 = segment.m_FrontSector.m_iFloorHeight - m_Player.m_vCameraPosition[2];
		
		bool drawWall  = segment.m_FrontSideDef.m_sMiddleTextureName != "-";
		bool drawCeil  = worldFrontZ1 > 0 || segment.m_FrontSector.m_CeilingTexture.m_sName == "F_SKY1";
		bool drawFloor = worldFrontZ2 < 0;
		
		float worldNormalAngle = segment.m_fAngle;
		float offsetAngle = worldNormalAngle - segment.m_fWorldAngle1;
		
		vector pos2d = m_Player.m_vCameraPosition;
		pos2d[2] = 0;
		float hypotenuse = vector.Distance(pos2d, segment.m_vStartingVertex);
		float worldDistance = hypotenuse * Math.Cos(offsetAngle+Math.PI_HALF);
		
		float RealWorldScaleStep;
		float worldScale = ScaleFromGlobalAngle(x1, worldNormalAngle, worldDistance);
		if (x1 < x2)
		{
			float scale2 = ScaleFromGlobalAngle(x2, worldNormalAngle, worldDistance);
			RealWorldScaleStep = (scale2 - worldScale) / (float)(x2 - x1);
		}
		else
			RealWorldScaleStep = 0;
		
		// Textures
		PS_DTextureMap middleTexture = m_DAssets.m_mTextures[segment.m_FrontSideDef.m_sMiddleTextureName];
		float middleTextureAltitude = worldFrontZ1;
		if ((segment.m_LineDef.m_iFlags & PS_EDLineDefsFlags.DONT_PEG_BOTTOM) && middleTexture)
		{
			middleTextureAltitude = segment.m_FrontSector.m_iFloorHeight + middleTexture.m_iHeight - m_Player.m_vCameraPosition[2];
		}
		middleTextureAltitude += segment.m_FrontSideDef.m_yOffset;
		
		float worldOffset = hypotenuse * Math.Sin(offsetAngle+Math.PI_HALF);
		worldOffset += segment.m_iOffset + segment.m_LineDef.m_FrontSideDef.m_xOffset;
		
		float worldCenterAngle = worldNormalAngle + m_Player.m_fAngle;
		// Textures END
		
		float wallY1 = PS_DConst.SCREEN_HEIGHT_HALF - worldFrontZ1 * worldScale;
		float wallY1Step = -RealWorldScaleStep * worldFrontZ1;
		
		float wallY2 = PS_DConst.SCREEN_HEIGHT_HALF - worldFrontZ2 * worldScale;
		float wallY2Step = -RealWorldScaleStep * worldFrontZ2;
		
		// Fast visPlanes merge
		if (drawCeil)
			m_CeilingPlane = CheckVisPlane(m_CeilingPlane, x1, x2);
		if (drawFloor)
			m_FloorPlane = CheckVisPlane(m_FloorPlane, x1, x2);
		
		// main loop
		for (int x = x1; x < x2; x++)
		{
			int drawWallY1 = wallY1 - 1;
			int drawWallY2 = wallY2;
			
			if (drawCeil)
			{
				int top = m_aYUpperClipX[x] + 1;
				int bottom = Math.Min(drawWallY1 - 1, m_aYLowerClipX[x] - 1);
				if (top <= bottom)
				{
					m_CeilingPlane.m_aTop[x] = top;
					m_CeilingPlane.m_aBottom[x] = bottom;
				}
			}
			
			if (drawWall)
			{
				int wy1 = Math.Max(drawWallY1, m_aYUpperClipX[x] + 1);
				int wy2 = Math.Min(drawWallY2, m_aYLowerClipX[x] - 1);
				
				if (wy1 < wy2)
				{
					float angle = worldCenterAngle + m_aXToAngle[x];
					int textureColumn = worldDistance * Math.Tan(angle) - worldOffset;
					float inversedScale = 1.0 / worldScale;
					
					DrawVerticalLineTextured(x, wy1, wy2
					, middleTexture, textureColumn, middleTextureAltitude, inversedScale
					, segment.m_FrontSector.m_iLightLevel, worldScale);
				}
			}
			
			if (drawFloor)
			{
				int top = Math.Max(drawWallY2 + 1, m_aYUpperClipX[x] + 1);
				int bottom = m_aYLowerClipX[x] - 1;
				if (top <= bottom)
				{
					m_FloorPlane.m_aTop[x] = top;
					m_FloorPlane.m_aBottom[x] = bottom;
				}
			}
			
			worldScale += RealWorldScaleStep;
			wallY1 += wallY1Step;
			wallY2 += wallY2Step;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	// floors and ceilings
	void DrawVisPlanes()
	{
		for (int i = 0; i < m_iLastVisPlane; i++)
		{
			PS_DVisPlane visPlane = m_aVisPlanes[i];
			if (visPlane.m_iMinX > visPlane.m_iMaxX)
				continue;
			
			if (visPlane.m_TextureFlat.m_sName == "F_SKY1")
			{
				PS_DTextureMap skyTexture = m_DAssets.m_mTextures["SKY1"];
				for (int x = visPlane.m_iMinX; x < visPlane.m_iMaxX; x++)
				{
					int textureColumn = 2.2 * (m_Player.m_fAngle + m_aXToAngle[x]) * Math.RAD2DEG;
					int wy1 = visPlane.m_aTop[x];
					int wy2 = visPlane.m_aBottom[x];
					
					float sky_inv_scale = 160 / PS_DConst.SCREEN_HEIGHT;
					float sky_tex_alt = 100;
					
					DrawVerticalLineTextured(x, wy1, wy2
					, skyTexture, textureColumn, sky_tex_alt, sky_inv_scale
					, 255, 1000);
				}
				continue;
			}
			
			// floors and ceilings
			visPlane.m_aTop[visPlane.m_iMinX] = int.MAX;
			visPlane.m_aTop[visPlane.m_iMaxX] = int.MAX;
			
			float planeHeight = Math.AbsFloat(visPlane.m_fHeight - m_Player.m_vCameraPosition[2]);
			for (int x = visPlane.m_iMinX; x < visPlane.m_iMaxX; x++)
			{
				MakeSpans(
					x, 
					visPlane.m_aTop[x], 
					visPlane.m_aBottom[x],
					visPlane.m_aTop[x+1], 
					visPlane.m_aBottom[x+1],
					visPlane
				)
			}
		}
	}
	
	// transform top/bottom clamps to horizontal lines
	void MakeSpans(int x, int t1, int b1, int t2, int b2, PS_DVisPlane visPlane)
	{
		while (t1 < t2 && t1 <= b1)
		{
			//DrawHorizontalLine(t1, m_aSpanStart[t1], x, visPlane);
			DrawHorizontalLineTextured(t1, m_aSpanStart[t1], x+1, visPlane);
			t1++;
		}
		while (b1 > b2 && b1 >= t1)
		{
			//DrawHorizontalLine(b1, m_aSpanStart[b1], x, visPlane);
			DrawHorizontalLineTextured(b1, m_aSpanStart[b1], x+1, visPlane);
			b1--;
		}
		
		while (t2 < t1 && t2 <= b2)
		{
			m_aSpanStart[t2] = x;
			t2++;
		}
		while (b2 > b1 && b2 >= t2)
		{
			m_aSpanStart[b2] = x;
			b2--;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	// Try reuse old visPlane if possible
	PS_DVisPlane CheckVisPlane(PS_DVisPlane visPlane, int start, int stop)
	{
		int intrl, intrh, unionl, unionh, x;
		if (start < visPlane.m_iMinX)
		{
			intrl = visPlane.m_iMinX;
			unionl = start;
		} else {
			unionl = visPlane.m_iMinX;
			intrl = start;
		}
		
		if (stop > visPlane.m_iMaxX)
		{
			intrh = visPlane.m_iMaxX;
			unionh = stop;
		} else {
			unionh = visPlane.m_iMaxX;
			intrh = stop;
		}
		
		for (x = intrl; x <= intrh; x++)
			if (visPlane.m_aTop[x] != int.MAX)
				break;
		
		if (x > intrh)
		{
			visPlane.m_iMinX = unionl;
			visPlane.m_iMaxX = unionh;
			return visPlane; // Return old visPlane
		}
		
		// Create new one and copy fields
		PS_DVisPlane newVisPlane = GetNewVisplane();
		newVisPlane.m_fHeight = visPlane.m_fHeight;
		newVisPlane.m_TextureFlat = visPlane.m_TextureFlat;
		newVisPlane.m_iLightLevel = visPlane.m_iLightLevel;
		newVisPlane.m_iMinX = start;
		newVisPlane.m_iMaxX = stop;
		StaticArray.Copy(newVisPlane.m_aTop, m_aTop); // GO GO fast
		StaticArray.Copy(newVisPlane.m_aBottom, m_aBottom);
		
		return newVisPlane;
	}
	
	// Vis plane merge
	PS_DVisPlane FindVisPlane(float height, PS_DTextureFlat texture, int lightLevel)
	{
		PS_DVisPlane mergedVisPlane;
		for (int i = 0; i < m_iLastVisPlane; i++) // Search for mergeable visPlane
		{
			PS_DVisPlane visPlane = m_aVisPlanes[i];
			if (visPlane.m_fHeight == height &&
				visPlane.m_TextureFlat == texture &&
				visPlane.m_iLightLevel == lightLevel)
			{
				mergedVisPlane = visPlane;
				break;
			}
		}
		
		if (!mergedVisPlane) // If there is no mergeable visPlanes, create new one
		{
			mergedVisPlane = GetNewVisplane();
		}
		else
			return mergedVisPlane;
			
		mergedVisPlane.m_fHeight = height;
		mergedVisPlane.m_TextureFlat = texture;
		mergedVisPlane.m_iLightLevel = lightLevel;
		mergedVisPlane.m_iMinX = PS_DConst.SCREEN_WIDTH+2;
		mergedVisPlane.m_iMaxX = -1;
		StaticArray.Copy(mergedVisPlane.m_aTop, m_aTop); // GO GO fast
		StaticArray.Copy(mergedVisPlane.m_aBottom, m_aBottom);
		
		return mergedVisPlane;
	}
	
	// Get free or create ne visPlane
	PS_DVisPlane GetNewVisplane()
	{
		PS_DVisPlane newVisPlane;
		if (m_iLastVisPlane < m_aVisPlanes.Count()) 
		{
			// Reuse old - remove allocation
			newVisPlane = m_aVisPlanes[m_iLastVisPlane];
		} else { 
			// Create new only when need
			newVisPlane = new PS_DVisPlane();
			newVisPlane.m_iColor = m_CurrentPallete.m_aColors[Math.RandomInt(0, 256)]; // Debug
			m_aVisPlanes.Insert(newVisPlane);
		}
		m_iLastVisPlane++;
		return newVisPlane;
	}
	
	//----------------------------------------------Util----------------------------------------------
	// main perspective calculation
	float ScaleFromGlobalAngle(int x, float worldNormalAngle, float worldDistance)
	{
		float xAngle = m_aXToAngle[x];
		float num = PS_DConst.SCREEN_Z * Math.Cos(worldNormalAngle + xAngle + m_Player.m_fAngle);
		float den = worldDistance * Math.Cos(xAngle);
		
		float scale = Math.Clamp(num / den, PS_DConst.MIN_SCALE, PS_DConst.MAX_SCALE);
		return scale;
	}
	
	//-------------------------------------------Framebuffer------------------------------------------
	void DrawVerticalLineSprite(int x, int y1, int y2, array<int> pixels, int tHeight, int tWidth, int textureColumn, int textureAltitude, float inversedScale, int lightLevel)
	{
		if (y1 <= y2)
		{
			y1 = Math.Clamp(y1, 0, PS_DConst.SCREEN_HEIGHT_VIEW);
			y2 = Math.Clamp(y2, 0, PS_DConst.SCREEN_HEIGHT_VIEW);
			
			// Cache - Copy to stack
			int pallete[256];
			StaticArray.Copy(pallete, m_CurrentRemapedPallete[lightLevel].m_aColors);
			int sWidth = PS_DConst.SCREEN_WIDTH;
			
			// Starting texture row
			float textureY = (textureAltitude + (float)(y1 - PS_DConst.SCREEN_HEIGHT_HALF) * inversedScale) + tHeight;
			textureY = Math.Repeat(textureY, tHeight);
			
			y1 *= sWidth;
			y2 *= sWidth;
			y1 += x;
			y2 += x;
			int colorTexture, textureI;
			for (int y = y1 + 1; y < y2; y += sWidth)
			{
				textureI = textureColumn + (int)textureY * tWidth;
				colorTexture = pixels[textureI];
				if (colorTexture != 256)
					PS_EddsTextureCanvasComponent.m_aPixels[y] = pallete[colorTexture];
				textureY += inversedScale;
				if (textureY >= tHeight)
					textureY = Math.Repeat(textureY, tHeight);
			}
		}
	}
	
	// Draw vertical line
	void DrawVerticalLine(int x, int y1, int y2, int color, string textureName, int lightLevel)
	{
		y1 = Math.Clamp(y1, 0, PS_DConst.SCREEN_HEIGHT_O);
		y2 = Math.Clamp(y2, 0, PS_DConst.SCREEN_HEIGHT_O);
		
		int colorTexture = m_DMain.GetUniqueColorForTexture(textureName, lightLevel);
		for (int y = y1; y <= y2; y++)
		{
			PS_EddsTextureCanvasComponent.m_aPixels[x + y * PS_DConst.SCREEN_WIDTH] = colorTexture;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void DrawVerticalLineTextured(int x, int y1, int y2, PS_DTextureMap texture, int textureColumn, float textureAltitude, float inversedScale, int lightLevel, float worldScale)
	{
		if (y1 <= y2)
		{
			y1 = Math.Clamp(y1, 0, PS_DConst.SCREEN_HEIGHT_VIEW);
			y2 = Math.Clamp(y2, 0, PS_DConst.SCREEN_HEIGHT_VIEW);
			
			// Distance light
			int lightIndex = Math.AbsInt(worldScale * PS_DConst.LIGHT_WORLD_SCALE);
			if (lightIndex > PS_DConst.LIGHT_Z_MAX)
				lightIndex = PS_DConst.LIGHT_Z_MAX;
			lightLevel += lightIndex;
			// Extra light by shoot flash or menu
			lightLevel += m_iExtraLight;
			lightLevel = Math.Clamp(lightLevel, 0, PS_DConst.MAX_LIGHT_LEVEL);
			
			// Cache
			int pallete[256]; // Copy to stack, slightly faster
			StaticArray.Copy(pallete, m_CurrentRemapedPallete[lightLevel].m_aColors);
			array<int> pixels = texture.m_TexturePixels.m_aPixels;
			int tHeight = texture.m_iHeight;
			int tWidth = texture.m_iWidth;
			int sWidth = PS_DConst.SCREEN_WIDTH;
			
			int textureX = Math.Repeat(textureColumn, texture.m_iWidth);
			float textureY = textureAltitude + ((float)y1 - PS_DConst.SCREEN_HEIGHT_HALF) * inversedScale;
			float pixelOffset = 1;
			
			int colorTexture;
			int textureI;
			y1 *= sWidth;
			y2 *= sWidth;
			y1 += x;
			y2 += x;
			if ((tHeight & (tHeight - 1)) == 0)
			{
				int mask = tHeight - 1;
				for (int y = y1; y <= y2; y += sWidth)
				{
					textureI = textureX + ((int)textureY & mask) * tWidth;
					colorTexture = pixels[textureI];
					if (colorTexture != 256)
					{
						colorTexture = pallete[colorTexture];
						PS_EddsTextureCanvasComponent.m_aPixels[y] = colorTexture;
					}
					textureY += inversedScale;
				}
			} else {
				for (int y = y1; y <= y2; y += sWidth)
				{
					textureI = textureX + (int)Math.Repeat(textureY, tHeight) * tWidth;
					colorTexture = pixels[textureI];
					if (colorTexture != 256)
					{
						colorTexture = pallete[colorTexture];
						PS_EddsTextureCanvasComponent.m_aPixels[y] = colorTexture;
					}
					textureY += inversedScale;
				}
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	// Debug draw, unique color for each VisPlane
	void DrawHorizontalLine(int y, int x1, int x2, PS_DVisPlane visPlane)
	{
		int colorTexture = m_DMain.GetUniqueColorForTexture(visPlane.m_TextureFlat.m_sName, visPlane.m_iLightLevel);
		for (int x = x1; x <= x2; x++)
		{
			PS_EddsTextureCanvasComponent.m_aPixels[x + y * PS_DConst.SCREEN_WIDTH] = colorTexture;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	// Fill floor and ceiling columns rotated to rows by VisPlane
	void DrawHorizontalLineTextured(int y, int x1, int x2, PS_DVisPlane visPlane)
	{
		// Calculate projection - trapezoid on plane
		// looking big but actually ~200us
		float z;
		float floorHeight = (visPlane.m_fHeight - m_Player.m_vCameraPosition[2]);
		int ty = (PS_DConst.SCREEN_HEIGHT_HALF - y);
		if (ty != 0)
			z = PS_DConst.SCREEN_WIDTH_HALF * floorHeight / ty;
		float offsetY = m_Player.m_fAngleCosReversed * z;
		float offsetX = m_Player.m_fAngleSinReversed * z;
		float worldX =  offsetY + m_Player.m_vCameraPosition[1];
		float worldY =  offsetX - m_Player.m_vCameraPosition[0];
		float leftX  = -offsetX + worldX;
		float leftY  =  offsetY + worldY;
		float rightX =  offsetX + worldX;
		float rightY = -offsetY + worldY;
		float dx = (rightX - leftX) / SCREEN_WIDTH;
		float dy = (rightY - leftY) / SCREEN_WIDTH;
		
		// Light level
		int lightLevel = visPlane.m_iLightLevel;
		// Distance light
		int lightIndex = Math.AbsInt(z * PS_DConst.LIGHT_Z_SCALE);
		if (lightIndex > PS_DConst.LIGHT_Z_MAX)
			lightIndex = PS_DConst.LIGHT_Z_MAX;
		lightIndex = PS_DConst.LIGHT_Z_MAX - lightIndex;
		lightLevel += lightIndex;
		// Extra light by shoot flash or menu
		lightLevel += m_iExtraLight;
		lightLevel = Math.Clamp(lightLevel, 0, PS_DConst.MAX_LIGHT_LEVEL);
		
		// Cache
		int pallete[256]; // Copy to stack, slightly faster
		StaticArray.Copy(pallete, m_CurrentRemapedPallete[lightLevel].m_aColors);
		PS_DTextureFlatPixels pixels = visPlane.m_TextureFlat.m_Pixels;
		
		// Starting texel position
		leftX += dx * x1;
		leftY += dy * x1;
		
		// Move by y
		int screenOffset = y * PS_DConst.SCREEN_WIDTH;
		x1 += screenOffset;
		x2 += screenOffset;
		
		// Outer scope vars - save some time
		int x, uxt, uyt, textureI, color; 
		for (x = x1; x < x2; x++) // Really tight loop
		{
			// Fast modulo of 64
			uxt = (int) leftX & 63;
			uyt = (int) leftY & 63;
			
			textureI = uxt | (uyt << 6);        // x + y * 64 - But funcy, not sure is it really valuable, maybe -0.5ms
			color = pixels.m_aPixels[textureI]; // Pick pallete index
			color = pallete[color];             // Pick actual color
			
			// Write to buffer
			PS_EddsTextureCanvasComponent.m_aPixels[x] = color;
			
			// Sub pixel texture step
			leftX += dx;
			leftY += dy;
		}
	}
	
	// 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D 2D
	
	// 2D draw segment
	void DrawSegment2D(PS_DSeg segment)
	{
		vector v1 = m_DMap.m_aVertexes[segment.m_iStartingVertex];
		vector v2 = m_DMap.m_aVertexes[segment.m_iEndingVertex];
		
		vector v1s = ToScreenSpace2D(v1);
		vector v2s = ToScreenSpace2D(v2);
		
		LineDrawCommand lineDrawCommand = new LineDrawCommand();
		lineDrawCommand.m_iColor = Color.WHITE;
		lineDrawCommand.m_fWidth = 2;
		lineDrawCommand.m_Vertices = {
			v1s[0], v1s[1],
			v2s[0], v2s[1]
		};
		m_aCanvasWidgetCommand.Insert(lineDrawCommand);
	}
	
	// 2D draw node
	void DrawNode(PS_DNode node)
	{
		DrawBBOX(node.m_RightBBox, Color.GREEN, 2);
		DrawBBOX(node.m_LeftBBox, Color.RED, 2);
		
		LineDrawCommand lineDrawCommand = new LineDrawCommand();
		lineDrawCommand.m_iColor = Color.BLUE;
		
		vector partition1 = Vector(node.m_iXPartition, node.m_iYPartition, 0);
		vector partition2 = Vector(node.m_iXPartition + node.m_iXDeltaPartition, node.m_iYPartition + node.m_iYDeltaPartition, 0);
		vector screenPartition1 = ToScreenSpace2D(partition1);
		vector screenPartition2 = ToScreenSpace2D(partition2);
		
		lineDrawCommand.m_Vertices = {
			screenPartition1[0], screenPartition1[1],
			screenPartition2[0], screenPartition2[1]
		};
		lineDrawCommand.m_fWidth = 4;
		
		m_aCanvasWidgetCommand.Insert(lineDrawCommand);
	}
	
	
	// Draw world space canvas()
	void DrawWorldSpaceCanvasAngle(vector v1, float angle, float Distance, int color, float width)
	{
		vector v2 = Vector(v1[0] + Math.Sin(angle) * Distance, v1[1] + Math.Cos(angle) * Distance, 0);
		DrawWorldSpaceCanvas(v1, v2, color, width);
	}
	void DrawWorldSpaceCanvas(vector v1, vector v2, int color, float width)
	{
		LineDrawCommand lineDrawCommand = new LineDrawCommand();
		lineDrawCommand.m_iColor = color;
		vector s1 = ToScreenSpace2D(v1);
		vector s2 = ToScreenSpace2D(v2);
		lineDrawCommand.m_Vertices = {
			s1[0], s1[1],
			s2[0], s2[1]
		};
		lineDrawCommand.m_fWidth = width;
		m_aCanvasWidgetCommand.Insert(lineDrawCommand);
	}
	
	// 2D draw bbox
	void DrawBBOX(PS_DBBox bBox, int color, float width)
	{
		LineDrawCommand lineDrawCommand = new LineDrawCommand();
		lineDrawCommand.m_iColor = color;
		
		vector worldPos1 = Vector(bBox.m_iLeft , bBox.m_iTop   , 0);
		vector worldPos2 = Vector(bBox.m_iRight, bBox.m_iTop   , 0);
		vector worldPos3 = Vector(bBox.m_iRight, bBox.m_iBottom, 0);
		vector worldPos4 = Vector(bBox.m_iLeft , bBox.m_iBottom, 0);
		
		vector screenPos1 = ToScreenSpace2D(worldPos1);
		vector screenPos2 = ToScreenSpace2D(worldPos2);
		vector screenPos3 = ToScreenSpace2D(worldPos3);
		vector screenPos4 = ToScreenSpace2D(worldPos4);
		
		lineDrawCommand.m_Vertices = {
			screenPos1[0], screenPos1[1],
			screenPos2[0], screenPos2[1],
			screenPos3[0], screenPos3[1],
			screenPos4[0], screenPos4[1]
		};
		lineDrawCommand.m_fWidth = width;
		lineDrawCommand.m_bShouldEnclose = true;
		
		m_aCanvasWidgetCommand.Insert(lineDrawCommand);
	}
	
	//------------------------------------------------------------------------------------------------
	void Draw2DLine(vector v1, vector v2, Color color, int width)
	{
		if (!m_bDrawMap)
			return;
		
		LineDrawCommand lineDrawCommand = new LineDrawCommand();
		lineDrawCommand.m_iColor = color.PackToInt();
		lineDrawCommand.m_fWidth = width;
		vector s1 = ToScreenSpace2D(v1);
		vector s2 = ToScreenSpace2D(v2);
		lineDrawCommand.m_Vertices = {s1[0], s1[1], s2[0], s2[1]};
		m_aCanvasWidgetCommand.Insert(lineDrawCommand);
	}
	
	//------------------------------------------------------------------------------------------------
	void Draw2DPoint(vector v1, Color color, int width)
	{
		if (!m_bDrawMap)
			return;
		
		LineDrawCommand lineDrawCommand = new LineDrawCommand();
		lineDrawCommand.m_iColor = color.PackToInt();
		lineDrawCommand.m_fWidth = width;
		vector s1 = ToScreenSpace2D(v1);
		lineDrawCommand.m_Vertices = {s1[0] - width/2, s1[1], s1[0] + width/2, s1[1]};
		m_aCanvasWidgetCommand.Insert(lineDrawCommand);
	}
	
	//------------------------------------------------------------------------------------------------
	vector ToScreenSpace2D(vector dMapPosition)
	{
		float screenX, screenY;
		screenX = GetGame().GetWorkspace().DPIUnscale( dMapPosition[0] / 4) - m_Player.m_vPosition[0] / 4 + 800;//m_DMap.m_DBlockMap.m_iGridOriginX / 10 + 1000;
		screenY = GetGame().GetWorkspace().DPIUnscale(-dMapPosition[1] / 4) + m_Player.m_vPosition[1] / 4 + 400;//m_DMap.m_DBlockMap.m_iGridOriginY / 10 - 500;
		return Vector(screenX, screenY, 0);
	}
}