enum PS_EDSpecialAction
{
	NONE,
	PS_DSpecialGlowingLight,
	PS_DSpecialStrobingLight,
	PS_DSpecialActionDoor,
	PS_DSpecialActionLift
}


class PS_DSpecialAction
{
	PS_DSector m_Sector;
	
	void Update()
	{
		
	}
	
	void PlayerPresent(PS_DEntityPlayer player)
	{
		
	}
	
	void WriteSave(FileHandle saveFile);
	void ReadSave(FileHandle saveFile);
}

class PS_DSpecialGlowingLight : PS_DSpecialAction
{
	int m_iMaxLightLevel;
	int m_iMinLightLevel;
	int m_iSpeed;
	int m_iDirection;
	
	override void Update()
	{
		int lightLevel = m_Sector.m_iLightLevel;
		if (m_iDirection > 0)
		{
			lightLevel += m_iSpeed;
			if (lightLevel > m_iMaxLightLevel)
				m_iDirection = -1;
		} else {
			lightLevel -= m_iSpeed;
			if (lightLevel < m_iMinLightLevel)
				m_iDirection = 1;
		}
		m_Sector.m_iLightLevel = lightLevel;
	}
	
	override void WriteSave(FileHandle saveFile)
	{
		saveFile.Write(PS_EDSpecialAction.PS_DSpecialGlowingLight, 1);
		
		saveFile.Write(m_iMaxLightLevel, 1);
		saveFile.Write(m_iMinLightLevel, 1);
		saveFile.Write(m_iSpeed, 1);
		saveFile.Write(m_iDirection, 1);
	}
	override void ReadSave(FileHandle saveFile)
	{
		saveFile.Read(m_iMaxLightLevel, 1);
		saveFile.Read(m_iMinLightLevel, 1);
		saveFile.Read(m_iSpeed, 1);
		saveFile.Read(m_iDirection, 1);
	}
}

class PS_DSpecialStrobingLight : PS_DSpecialAction
{
	int m_iMaxLightLevel;
	int m_iMinLightLevel;
	int m_iBrightTime;
	int m_iDarkTime;
	
	int m_iTics;
	
	override void Update()
	{
		m_iTics--;
		if (m_iTics > 0)
			return;
		
		int lightLevel = m_Sector.m_iLightLevel;
		if (lightLevel == m_iMaxLightLevel)
		{
			m_Sector.m_iLightLevel = m_iMinLightLevel;
			m_iTics = m_iDarkTime;
		} else {
			m_Sector.m_iLightLevel = m_iMaxLightLevel;
			m_iTics = m_iBrightTime;
		}
	}
	
	override void WriteSave(FileHandle saveFile)
	{
		saveFile.Write(PS_EDSpecialAction.PS_DSpecialStrobingLight, 1);
		
		saveFile.Write(m_iMaxLightLevel, 1);
		saveFile.Write(m_iMinLightLevel, 1);
		saveFile.Write(m_iBrightTime, 2);
		saveFile.Write(m_iDarkTime, 2);
		saveFile.Write(m_iTics, 1);
		
	}
	override void ReadSave(FileHandle saveFile)
	{
		saveFile.Read(m_iMaxLightLevel, 1);
		saveFile.Read(m_iMinLightLevel, 1);
		saveFile.Read(m_iBrightTime, 2);
		saveFile.Read(m_iDarkTime, 2);
		saveFile.Read(m_iTics, 1);
	}
}

class PS_DSpecialActionDoor : PS_DSpecialAction
{
	int m_iStartHeight;
	int m_iTargetHeight;
	int m_iSpeed;
	int m_iTopTimeTemp;
	int m_iTopTime;
	bool m_bCanBeReversed;
	
	bool m_bOnTop;
	
	void Reverse()
	{
		if (m_iTopTimeTemp != 0)
		{
			m_bOnTop = true;
			m_iTopTimeTemp = 0;
		} else {
			m_bOnTop = false;
			m_iTopTimeTemp = m_iTopTime;
		}
	}
	
	override void Update()
	{
		if (m_bOnTop) {
			if (m_iTopTimeTemp != 0)
			{
				m_iTopTimeTemp--;
				if (m_iTopTimeTemp == 0)
					PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_dorcls, "0 0 0");
			}
			else {
				int height = m_Sector.m_iCeilingHeight;
				int deltaHeight = height - m_iStartHeight;
				if (deltaHeight == 0)
				{
					m_Sector.m_SpecialAction = null;
					return;
				}
				
				if (CheckIntersection())
				{
					Reverse();
					return;
				}
				
				int change = m_iSpeed;
				if (change > deltaHeight)
					change = deltaHeight;
				m_Sector.m_iCeilingHeight -= change;
			}
		}
		else {
			if (m_iStartHeight == m_Sector.m_iCeilingHeight)
				PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_doropn, "0 0 0");
			int height = m_Sector.m_iCeilingHeight;
			int deltaHeight = m_iTargetHeight - height;
			if (deltaHeight == 0)
			{
				m_bOnTop = true;
				return;
			}
			int change = m_iSpeed;
			if (change > deltaHeight)
				change = deltaHeight;
			m_Sector.m_iCeilingHeight += change;
		}
	}
	
	bool CheckIntersection()
	{
		array<PS_DEntity> entities = m_Sector.GetEntitiesInside();
		
		foreach (PS_DEntity entity : entities)
		{
			float height = entity.m_vPosition[2] + entity.m_MobjInfo.m_iHeight;
			if (height > m_Sector.m_iCeilingHeight)
				return true;
		}
		
		return false;
	}
	
	override void WriteSave(FileHandle saveFile)
	{
		saveFile.Write(PS_EDSpecialAction.PS_DSpecialActionDoor, 1);
		
		saveFile.Write(m_iStartHeight, 4);
		saveFile.Write(m_iTargetHeight, 4);
		saveFile.Write(m_iSpeed, 4);
		saveFile.Write(m_iTopTimeTemp, 2);
		saveFile.Write(m_iTopTime, 2);
		saveFile.Write(m_bCanBeReversed, 1);
		saveFile.Write(m_bOnTop, 1);
	}
	override void ReadSave(FileHandle saveFile)
	{
		saveFile.Read(m_iStartHeight, 4);
		saveFile.Read(m_iTargetHeight, 4);
		saveFile.Read(m_iSpeed, 4);
		saveFile.Read(m_iTopTimeTemp, 2);
		saveFile.Read(m_iTopTime, 2);
		saveFile.Read(m_bCanBeReversed, 1);
		saveFile.Read(m_bOnTop, 1);
	}
}

class PS_DSpecialActionLift : PS_DSpecialAction
{
	int m_iStartHeight;
	int m_iTargetHeight;
	int m_iDownTime;
	int m_iDownTimeTemp;
	int m_iSpeed;
	int m_iDirection = 1;
	PS_DTextureFlat m_NextTexture;
	bool m_bOnDown;
	
	int m_iTicks;
	
	void Reverse()
	{
		if (m_iDownTimeTemp != 0)
		{
			m_bOnDown = true;
			m_iDownTimeTemp = 0;
		} else {
			m_bOnDown = false;
			m_iDownTimeTemp = m_iDownTime;
		}
	}
	
	override void Update()
	{
		m_iTicks++;
		if (m_bOnDown) {
			if (m_iDownTimeTemp != 0)
			{
				m_iDownTimeTemp--;
				if (m_iDownTimeTemp == 0)
				{
					PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_pstart, "0 0 0");
				}
			}
			else {
				if ((m_iTicks & 7) == 0)
					PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_stnmov, "0 0 0");
				
				int height = m_Sector.m_iFloorHeight;
				int deltaHeight = (m_iStartHeight - height) * m_iDirection;
				if (deltaHeight == 0)
				{
					m_Sector.m_SpecialAction = null;
					return;
				}
				if (CheckIntersection(-m_iDirection))
					Reverse();
				int change = m_iSpeed;
				if (change > deltaHeight)
					change = deltaHeight;
				m_Sector.m_iFloorHeight += change * m_iDirection;
			}
		} else {
			if (m_iStartHeight == m_Sector.m_iFloorHeight)
				PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_pstart, "0 0 0");
			if ((m_iTicks & 7) == 0)
				PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_stnmov, "0 0 0");
			int height = m_Sector.m_iFloorHeight;
			int deltaHeight = (height - m_iTargetHeight) * m_iDirection;
			if (m_iDirection == -1)
				if (m_NextTexture)
				{
					m_Sector.m_FloorTexture = m_NextTexture;
					m_Sector.m_iSpecialType = 0;
				}
			if (deltaHeight == 0)
			{
				if (m_NextTexture)
				{
					m_Sector.m_FloorTexture = m_NextTexture;
					m_Sector.m_iSpecialType = 0;
				}
				m_bOnDown = true;
				PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_pstop, "0 0 0");
				return;
			}
			if (CheckIntersection(m_iDirection))
				Reverse();
			int change = m_iSpeed;
			if (change > deltaHeight)
				change = deltaHeight;
			m_Sector.m_iFloorHeight -= change * m_iDirection;
		}
	}
	
	bool CheckIntersection(int direction)
	{
		if (direction == 1)
			return false;
		
		array<PS_DEntity> entities = m_Sector.GetEntitiesInside();
		foreach (PS_DEntity entity : entities)
		{
			float height = entity.m_MobjInfo.m_iHeight;
			vector offsets[4] = entity.m_BBOX.m_aOffsets;
			foreach (vector offset : offsets)
			{
				PS_DSector sectorOther = entity.m_DMap.GetPositionSector(entity.m_vPosition + offset);
				float heightDiff = sectorOther.m_iCeilingHeight - m_Sector.m_iFloorHeight;
				if (heightDiff < height)
					return true;
			}
		}
		
		return false;
	}
	
	override void WriteSave(FileHandle saveFile)
	{
		saveFile.Write(PS_EDSpecialAction.PS_DSpecialActionLift, 1);
		
		saveFile.Write(m_iStartHeight, 4);
		saveFile.Write(m_iTargetHeight, 4);
		saveFile.Write(m_iDownTime, 2);
		saveFile.Write(m_iDownTimeTemp, 2);
		saveFile.Write(m_iSpeed, 4);
		saveFile.Write(m_iDirection, 4);
		
		if (m_NextTexture)
		{
			int length = m_NextTexture.m_sName.Length();
			saveFile.Write(length, 1);
			saveFile.Write(m_NextTexture.m_sName, length);
		}
		else
			saveFile.Write(0, 1);
		
		saveFile.Write(m_bOnDown, 1);
		saveFile.Write(m_iTicks, 2);
	}
	override void ReadSave(FileHandle saveFile)
	{
		saveFile.Read(m_iStartHeight, 4);
		saveFile.Read(m_iTargetHeight, 4);
		saveFile.Read(m_iDownTime, 2);
		saveFile.Read(m_iDownTimeTemp, 2);
		saveFile.Read(m_iSpeed, 4);
		saveFile.Read(m_iDirection, 4);
		
		int length;
		saveFile.Read(length, 1);
		if (length > 0)
		{
			string name;
			saveFile.Read(name, length);
			m_NextTexture = PS_DMain.s_DMain.m_DWAD.m_DAssets.m_mFlatTextures[name];
		}
		
		saveFile.Read(m_bOnDown, 1);
		saveFile.Read(m_iTicks, 2);
	}
}