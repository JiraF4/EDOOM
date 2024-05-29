// I'm a little bit tired
// Spaghetti initiated
class PS_DAnimatedTexture
{
	bool m_bIsTexture;
	string m_sEndName;
	string m_sStartName;
	int m_iSpeed;
	
	ref array<ref PS_DTextureFlat> m_aFlats = {};
	ref array<ref PS_DTextureFlatPixels> m_aPixels = {};
	
	ref array<ref PS_DTextureMap> m_aTextureMaps = {};
	ref array<ref PS_DTexturePixels> m_aMapPixels = {};
	
	int m_iCurrentTexture;
	int m_iAnimateTick = 1;
	
	static void Init(PS_DAssets dAssests)
	{
		foreach (PS_DAnimatedTexture animatedTexture : ANIMATED_TEXTURES)
		{
			if (animatedTexture.m_bIsTexture)
			{
				string textureName = animatedTexture.m_sStartName.Substring(0, animatedTexture.m_sStartName.Length() - 1);
				string textureFrame = textureName + "1";
				int i = 2;
				while (dAssests.m_mTextures.Contains(textureFrame))
				{
					animatedTexture.m_aTextureMaps.Insert(dAssests.m_mTextures[textureFrame]);
					animatedTexture.m_aMapPixels.Insert(dAssests.m_mTextures[textureFrame].m_TexturePixels);
					textureFrame = textureName + i.ToString();
					i++;
				}
			} else {
				string textureName = animatedTexture.m_sStartName.Substring(0, animatedTexture.m_sStartName.Length() - 1);
				string textureFrame = textureName + "1";
				int i = 2;
				while (dAssests.m_mFlatTextures.Contains(textureFrame))
				{
					animatedTexture.m_aFlats.Insert(dAssests.m_mFlatTextures[textureFrame]);
					animatedTexture.m_aPixels.Insert(dAssests.m_mFlatTextures[textureFrame].m_Pixels);
					textureFrame = textureName + i.ToString();
					i++;
				}
			}
		}
	}
	
	static void Update()
	{
		foreach (PS_DAnimatedTexture animatedTexture : ANIMATED_TEXTURES)
		{
			animatedTexture.m_iAnimateTick--;
			if (animatedTexture.m_iAnimateTick == 0)
			{
				animatedTexture.m_iCurrentTexture++;
				if (animatedTexture.m_bIsTexture)
				{
					if (animatedTexture.m_iCurrentTexture >= animatedTexture.m_aMapPixels.Count())
						animatedTexture.m_iCurrentTexture = 0;
					foreach (PS_DTextureMap textureMap : animatedTexture.m_aTextureMaps)
					{
						textureMap.m_TexturePixels = animatedTexture.m_aMapPixels[animatedTexture.m_iCurrentTexture];
					}
				} else {
					if (animatedTexture.m_iCurrentTexture >= animatedTexture.m_aPixels.Count())
						animatedTexture.m_iCurrentTexture = 0;
					foreach (PS_DTextureFlat textureFlat : animatedTexture.m_aFlats)
					{
						textureFlat.m_Pixels = animatedTexture.m_aPixels[animatedTexture.m_iCurrentTexture];
					}
				}
				animatedTexture.m_iAnimateTick = animatedTexture.m_iSpeed;
			}
		}
	}
	
	void PS_DAnimatedTexture(
		bool isTexture,
		string endName,
		string startName,
		int speed
	)
	{
		m_bIsTexture = isTexture;
		m_sEndName = endName;
		m_sStartName = startName;
		m_iSpeed = speed;
	}
	
	static const ref array<ref PS_DAnimatedTexture> ANIMATED_TEXTURES =
	{
		new PS_DAnimatedTexture(false,	"NUKAGE3",	"NUKAGE1",	8),
		new PS_DAnimatedTexture(false,	"FWATER4",	"FWATER1",	8),
		new PS_DAnimatedTexture(false,	"SWATER4",	"SWATER1", 	8),
		new PS_DAnimatedTexture(false,	"LAVA4",	"LAVA1",	8),
		new PS_DAnimatedTexture(false,	"BLOOD3",	"BLOOD1",	8),
		
		// DOOM II flat animations.
		new PS_DAnimatedTexture(false,	"RROCK08",	"RROCK05",	8),		
		new PS_DAnimatedTexture(false,	"SLIME04",	"SLIME01",	8),
		new PS_DAnimatedTexture(false,	"SLIME08",	"SLIME05",	8),
		new PS_DAnimatedTexture(false,	"SLIME12",	"SLIME09",	8),
		
		new PS_DAnimatedTexture(true,	"BLODGR4",	"BLODGR1",	8),
		new PS_DAnimatedTexture(true,	"SLADRIP3",	"SLADRIP1",	8),
		
		new PS_DAnimatedTexture(true,	"BLODRIP4",	"BLODRIP1",	8),
		new PS_DAnimatedTexture(true,	"FIREWALL",	"FIREWALA",	8),
		new PS_DAnimatedTexture(true,	"GSTFONT3",	"GSTFONT1",	8),
		new PS_DAnimatedTexture(true,	"FIRELAVA",	"FIRELAV3",	8),
		new PS_DAnimatedTexture(true,	"FIREMAG3",	"FIREMAG1",	8),
		new PS_DAnimatedTexture(true,	"FIREBLU2",	"FIREBLU1",	8),
		new PS_DAnimatedTexture(true,	"ROCKRED3",	"ROCKRED1",	8),
		
		new PS_DAnimatedTexture(true,	"BFALL4",	"BFALL1",	8),
		new PS_DAnimatedTexture(true,	"SFALL4",	"SFALL1",	8),
		new PS_DAnimatedTexture(true,	"WFALL4",	"WFALL1",	8),
		new PS_DAnimatedTexture(true,	"DBRAIN4",	"DBRAIN1",	8)
	};
}

class PS_DSpecial
{
	static const int GLOWSPEED			= 8;
	static const int STROBEBRIGHT		= 5;
	static const int FASTDARK			= 15;
	static const int SLOWDARK			= 35;
		
	PS_DMap m_DMap;
	int m_iSpecialType;
	
	void PS_DSpecial(PS_DMap dMap)
	{
		m_DMap = dMap;
	}
	
	int m_iBossCounter;
	void Die(PS_DEntity entity)
	{
		if (m_DMap.m_sName != "E1M8")
			return;
		
		if (entity.m_MobjState.m_SpriteNum == PS_DMobjSpriteNum.SPR_BOSS)
		{
			m_iBossCounter++;
			if (m_iBossCounter == 2)
			{
				PS_DLineDef lineDef = new PS_DLineDef();
				lineDef.m_iSectorTag = 666;
				FloorLowerTag(lineDef, 4, -1, 1, 0, 1, 0);
			}
		}
	}
	
	void Cross(PS_DLineDef lineDef, PS_DEntity entity)
	{
		bool canTrigger = entity.IsInherited(PS_DEntityPlayer);
		if (!canTrigger && !(entity.m_iFlags & PS_EDMobjFlag.MF_MISSILE)) // Not player
		{
			switch (lineDef.m_iSpecialType)
			{
				case 97:
					canTrigger = true;
					break;
			}
		}
		
		if (!canTrigger)
			return;
		
		switch (lineDef.m_iSpecialType)
		{
			case 2:
				VerticalDoor(lineDef, entity, lineDef.m_iSectorTag, 2, -1, false);
				break;
			case 5:
				FloorLowerTag(lineDef, 2, 30, -1, 0, 0);
				break;
			case 97:
				Teleport(lineDef, entity);
				break;
			case 98:
				FloorLowerTag(lineDef, 6, 200, 1, 0, 1, 8);
				break;
			case 8:
				BuildStairs(lineDef, entity, 8);
				break;
			case 88: // PlatDownWaitUp
				FloorLowerTag(lineDef, 4, 200);
				break;
			case 35:
				ChangeLight(lineDef, 35 >> 3);
				break;
			case 36: // Lower Floor (TURBO)
				FloorLowerTag(lineDef, 32, -1);
				break;
			case 91:
				FloorLowerTag(lineDef, 2, 30, -1, 0, 0);
				break;
			case 90:
				VerticalDoor(lineDef, entity, lineDef.m_iSectorTag, 2, 60, false);
				break;
			case 22:
				FloorLowerTag(lineDef, 1, -1, -1, 1, 0); // Raise change texture
				break;
			case 86:
				VerticalDoor(lineDef, entity, lineDef.m_iSectorTag, 2, -1, false);
				break;
			case 11:
				break;
			case 48:
				break;
		}
	}
	
	void ChangeLight(PS_DLineDef lineDef, int lightLevel)
	{
		array<PS_DSector> sectors = m_DMap.m_aSpecialSectors[lineDef.m_iSectorTag];
		
		foreach (PS_DSector sector : sectors)
		{
			sector.m_iLightLevel = lightLevel;
		}
	}
	
	void Spawn(PS_DSector sector)
	{
		switch (sector.m_iSpecialType)
		{
			case 1:
				// FLICKERING LIGHTS
				SpawnStrobeFlash(sector,0,0);
				break;
			
			case 2:
				// STROBE FAST
				SpawnStrobeFlash(sector,FASTDARK,0);
				break;
			
			case 3:
				// STROBE SLOW
				SpawnStrobeFlash(sector,SLOWDARK,0);
				break;
			
			case 4:
				// STROBE FAST/DEATH SLIME
				SpawnStrobeFlash(sector,FASTDARK,0);
				break;
			
			case 8:
				// GLOWING LIGHT
				SpawnGlowingLight(sector);
				break;
			
			case 12:
				// SYNC STROBE SLOW
				SpawnStrobeFlash(sector, SLOWDARK, 1);
				break;
			
			case 13:
				// SYNC STROBE FAST
				SpawnStrobeFlash(sector, FASTDARK, 1);
				break;
		}
	}
		
	void SpawnStrobeFlash(PS_DSector sector, int speed, int synced)
	{
		PS_DSpecialStrobingLight specialAction = new PS_DSpecialStrobingLight();
		
		specialAction.m_Sector = sector;
		specialAction.m_iDarkTime = speed;
		specialAction.m_iBrightTime = STROBEBRIGHT;
		specialAction.m_iMaxLightLevel = sector.m_iLightLevel;
		specialAction.m_iMinLightLevel = sector.GetNeighbourLowestLightLevel();
		
		m_DMap.m_aSpecialActions.Insert(specialAction);
		sector.m_SpecialActionLight = specialAction;
	}
	
	void SpawnGlowingLight(PS_DSector sector)
	{
		PS_DSpecialGlowingLight specialAction = new PS_DSpecialGlowingLight();
		
		specialAction.m_Sector = sector;
		specialAction.m_iSpeed = 4;
		specialAction.m_iMaxLightLevel = sector.m_iLightLevel;
		specialAction.m_iMinLightLevel = sector.GetNeighbourLowestLightLevel();
		
		m_DMap.m_aSpecialActions.Insert(specialAction);
		sector.m_SpecialActionLight = specialAction;
	}
	
	void Impact(PS_DLineDef lineDef, PS_DEntity initiator)
	{
		switch (m_iSpecialType)
		{
			case 46:
				VerticalDoor(lineDef, initiator, lineDef.m_iSectorTag, 2, -1);
				PS_DSwitch.ChangeSwitch(lineDef, 1);
				break;
		}
	}
	
	void Activate(PS_DLineDef lineDef, PS_DEntity initiator)
	{
		switch (m_iSpecialType)
		{
			case 63:
				VerticalDoor(lineDef, initiator, 0, 2, 100, true);
				PS_DSwitch.ChangeSwitch(lineDef, 1);
				break;
			
			case 7:
				BuildStairs(lineDef, initiator, 8);
				break;
			// "Donut"
			case 9:
				VerticalDonut(lineDef, initiator);
				PS_DSwitch.ChangeSwitch(lineDef, 0);
				break;
			// Switches
			case 103:
				VerticalDoor(lineDef, initiator, lineDef.m_iSectorTag, 2, -1);
				PS_DSwitch.ChangeSwitch(lineDef, 0);
				break;
			case 62:
				FloorLowerTag(lineDef, 4, 200);
				PS_DSwitch.ChangeSwitch(lineDef, 1);
				break;
			case 20:
				FloorLowerTag(lineDef, 4, -1, 1, 1, 0); // Raise change texture
				PS_DSwitch.ChangeSwitch(lineDef, 0);
				break;
			case 18:
				FloorLowerTag(lineDef, 2, -1, -1, 0, 0);
				PS_DSwitch.ChangeSwitch(lineDef, 0);
				break;
			case 23:
				FloorLowerTag(lineDef, 2, -1, 1, 0, 1);
				PS_DSwitch.ChangeSwitch(lineDef, 0);
				break;
			case 70:
				FloorLowerTag(lineDef, 6, 200, 1, 0, 1, 8);
				PS_DSwitch.ChangeSwitch(lineDef, 1);
				break;
			case 91:
				FloorLowerTag(lineDef, 6, 200, 1, 0, 1, 8);
				break;
			
			// Exit level
			case 51:
				m_DMap.m_DMain.Intermission(true);
				break;
			case 11:
				m_DMap.m_DMain.Intermission();
				break;
			
			// MANUALS
			case 1:		// Vertical Door
				VerticalDoor(lineDef, initiator, 0, 2, 100, true);
				break;
			case 26:		// Blue Door/Locked
				if (m_DMap.m_DMain.m_EntityPlayer.m_aKeys[0] == 0)
					return;
				VerticalDoor(lineDef, initiator, 0, 2, -1);
				break;
			case 27:		// Yellow Door /Locked
				if (m_DMap.m_DMain.m_EntityPlayer.m_aKeys[1] == 0)
					return;
				VerticalDoor(lineDef, initiator, 0, 2, -1);
				break;
			case 28:		// Red Door /Locked
				if (m_DMap.m_DMain.m_EntityPlayer.m_aKeys[2] == 0)
					return;
				VerticalDoor(lineDef, initiator, 0, 2, -1);
				break;
			
			case 31:		// Manual door open
				VerticalDoor(lineDef, initiator, 0, 2, -1);
				break;
			
			case 32:		// Blue locked door open
				if (m_DMap.m_DMain.m_EntityPlayer.m_aKeys[0] == 0)
					return;
				VerticalDoor(lineDef, initiator, 0, 2, 100, true);
				break;
			case 33:		// Red locked door open
				if (m_DMap.m_DMain.m_EntityPlayer.m_aKeys[2] == 0)
					return;
				VerticalDoor(lineDef, initiator, 0, 2, 100, true);
				break;
			case 34:		// Yellow locked door open
				if (m_DMap.m_DMain.m_EntityPlayer.m_aKeys[1] == 0)
					return;
				VerticalDoor(lineDef, initiator, 0, 2, 100, true);
				break;
			
			case 117:		// Blazing door raise
			case 118:		// Blazing door open
				VerticalDoor(lineDef, initiator, 0, 40, 100);
			break;
		}
	}
	
	void Teleport(PS_DLineDef lineDef, PS_DEntity initiator)
	{
		array<PS_DSector> sectors = m_DMap.m_aSpecialSectors[lineDef.m_iSectorTag];
		if (!sectors)
			return;
		
		foreach (PS_DSector sector : sectors)
		{
			vector offsets[4] = initiator.m_BBOX.m_aOffsetsHalf;
			if (initiator.IsInherited(PS_DEntityPlayer))
				offsets = initiator.m_BBOX.m_aOffsets;
			if (initiator.CheckPosition(sector.m_vTeleportTarget, sector.m_vTeleportTarget[2], offsets))
				continue;
			
			initiator.m_vPositionTeleport = sector.m_vTeleportTarget;
			
			PS_DEntity entity = new PS_DEntity(m_DMap);
			entity.m_vPosition = sector.m_vTeleportTarget;
			entity.m_fAngle = entity.m_fAngle;
			entity.m_MobjInfo = PS_DInfo.m_aMobjInfo[PS_DMobjType.MT_TFOG];
			entity.m_MobjState = PS_DInfo.m_aMobjStates[entity.m_MobjInfo.m_iSpawnState];
			entity.m_iFlags = entity.m_MobjInfo.m_iFlags;
			entity.m_iStateTics = entity.m_MobjState.m_iTics;
			entity.m_BBOX = new PS_DEntityBBox(entity.m_MobjInfo);
			m_DMap.m_aEntities.Insert(entity);
		}
	}
	
	void FloorLowerTag(PS_DLineDef lineDef, int speed, int downTime, int direction = 1, int textureChange = 0, int lowest = 1, int offset = 0)
	{
		array<PS_DSector> sectors = m_DMap.m_aSpecialSectors[lineDef.m_iSectorTag];
		if (!sectors)
			return;
		
		foreach (PS_DSector sector : sectors)
		{
			if (sector.m_SpecialAction)
				continue;
			
			PS_DSpecialActionLift specialAction = new PS_DSpecialActionLift();
			
			specialAction.m_iStartHeight = sector.m_iFloorHeight;
			PS_DSector sectorOther;
			if (lowest)
				sectorOther = sector.GetNeighbourMinFloorHeight();
			else
				sectorOther = sector.GetNeighbourMaxFloorHeight();
			specialAction.m_iTargetHeight = sectorOther.m_iFloorHeight + offset;
			if (textureChange)
				specialAction.m_NextTexture = sectorOther.m_FloorTexture;
			specialAction.m_iSpeed = speed;
			specialAction.m_iDownTime = downTime;
			specialAction.m_iDownTimeTemp = downTime;
			specialAction.m_iDirection = 1;
			if (specialAction.m_iTargetHeight > specialAction.m_iStartHeight)
				specialAction.m_iDirection = -1;
			specialAction.m_Sector = sector;
			
			sector.m_SpecialAction = specialAction;
			m_DMap.m_aSpecialActions.Insert(specialAction);
		}
	}
	
	void BuildStairs(PS_DLineDef lineDef, PS_DEntity initiator, int stepSize)
	{
		array<PS_DSector> sectors = m_DMap.m_aSpecialSectors[lineDef.m_iSectorTag];
		if (!sectors)
			return;
		
		foreach (PS_DSector sector : sectors)
		{
			if (sector.m_SpecialAction)
				continue;
			
			int stepHeight = sector.m_iFloorHeight;
			PS_DSector stepSector = sector;
			while (stepSector)
			{
				stepHeight += stepSize;
				PS_DSpecialActionLift specialAction = new PS_DSpecialActionLift();
				specialAction.m_iStartHeight = stepSector.m_iFloorHeight;
				specialAction.m_iTargetHeight = stepHeight;
				specialAction.m_iSpeed = 1;
				specialAction.m_iDownTime = -1;
				specialAction.m_iDownTimeTemp = -1;
				specialAction.m_Sector = stepSector;
				specialAction.m_iDirection = -1;
				stepSector.m_SpecialAction = specialAction;
				m_DMap.m_aSpecialActions.Insert(specialAction);
				
				// Search next
				PS_DSector searchSector;
				foreach (PS_DSideDef sideDef : stepSector.m_aSideDefs)
				{
					PS_DLineDef lineDef3 = sideDef.m_LineDef;
					if (!(lineDef3.m_iFlags & PS_EDLineDefsFlags.TWO_SIDED))
						continue;
					
					PS_DSector nextSector = lineDef3.m_FrontSideDef.m_Sector;
					if (stepSector == nextSector)
						nextSector = lineDef3.m_BackSideDef.m_Sector;
					
					if (stepSector.m_FloorTexture != nextSector.m_FloorTexture)
						continue;
					
					if (nextSector.m_SpecialAction)
						continue;
					
					searchSector = nextSector;
					break;
				}
				
				stepSector = searchSector;
			}
		}
	}
	
	// Donut!
	void VerticalDonut(PS_DLineDef lineDef, PS_DEntity initiator)
	{
		array<PS_DSector> sectors = m_DMap.m_aSpecialSectors[lineDef.m_iSectorTag];
		if (!sectors)
			return;
		
		foreach (PS_DSector sector : sectors)
		{
			if (sector.m_SpecialAction)
				continue;
			
			PS_DLineDef lineDef2 = sector.m_aSideDefs[0].m_LineDef;
			PS_DSector sector2 = lineDef2.m_FrontSideDef.m_Sector;
			if (sector == sector2)
				sector2 = lineDef2.m_BackSideDef.m_Sector;
			
			foreach (PS_DSideDef sideDef : sector2.m_aSideDefs)
			{
				PS_DLineDef lineDef3 = sideDef.m_LineDef;
				if (!(lineDef3.m_iFlags & PS_EDLineDefsFlags.TWO_SIDED))
					continue;
				
				PS_DSector sector3 = lineDef3.m_FrontSideDef.m_Sector;
				if (sector2 == sector3)
					sector3 = lineDef3.m_BackSideDef.m_Sector;
				if (sector3 == sector)
					continue;
				
				// Border up
				PS_DSpecialActionLift specialAction = new PS_DSpecialActionLift();
				specialAction.m_iStartHeight = sector2.m_iFloorHeight;
				specialAction.m_iTargetHeight = sector3.m_iFloorHeight;
				specialAction.m_iSpeed = 1;
				specialAction.m_iDownTime = -1;
				specialAction.m_iDownTimeTemp = -1;
				specialAction.m_Sector = sector2;
				specialAction.m_iDirection = -1;
				specialAction.m_NextTexture = sector3.m_FloorTexture;
				sector2.m_SpecialAction = specialAction;
				m_DMap.m_aSpecialActions.Insert(specialAction);
				
				// Center down
				specialAction = new PS_DSpecialActionLift();
				specialAction.m_iStartHeight = sector.m_iFloorHeight;
				specialAction.m_iTargetHeight = sector3.m_iFloorHeight;
				specialAction.m_iSpeed = 1;
				specialAction.m_iDownTime = -1;
				specialAction.m_iDownTimeTemp = -1;
				specialAction.m_Sector = sector;
				specialAction.m_iDirection = 1;
				sector.m_SpecialAction = specialAction;
				m_DMap.m_aSpecialActions.Insert(specialAction);
			}
		}
	}
	
	void VerticalDoor(PS_DLineDef lineDef, PS_DEntity initiator, int tag = 0, int speed = 2, int topTime = 100, bool canBeReversed = false)
	{
		array<PS_DSector> sectors;
		if (tag == 0)
			sectors = {lineDef.m_BackSideDef.m_Sector};
		else
			sectors = m_DMap.m_aSpecialSectors[lineDef.m_iSectorTag];
		if (!sectors)
			return;
		
		foreach (PS_DSector sector : sectors)
		{			
			if (sector.m_SpecialAction)
			{
				PS_DSpecialActionDoor specialAction = PS_DSpecialActionDoor.Cast(sector.m_SpecialAction);
				if (specialAction.m_bCanBeReversed)
					specialAction.Reverse();
				continue;
			}
			
			PS_DSpecialActionDoor specialAction = new PS_DSpecialActionDoor();
			
			specialAction.m_iStartHeight = sector.m_iCeilingHeight;
			specialAction.m_iTargetHeight = sector.GetNeighbourLowesCeilingHeight() - 8;
			specialAction.m_iSpeed = speed;
			specialAction.m_iTopTime = topTime;
			specialAction.m_iTopTimeTemp = topTime;
			specialAction.m_Sector = sector;
			specialAction.m_bCanBeReversed = canBeReversed;
			
			sector.m_SpecialAction = specialAction;
			
			m_DMap.m_aSpecialActions.Insert(specialAction);
		}
	}
}

