class PS_DEntityPlayer : PS_DEntity
{
	float m_fAngleSin, m_fAngleCos, m_fAngleSinReversed, m_fAngleCosReversed;
	float m_fLeftFoVAngleSin, m_fLeftFoVAngleCos, m_fLeftFoVAngleSinReversed, m_fLeftFoVAngleCosReversed;
	float m_fRightFoVAngleSin, m_fRightFoVAngleCos, m_fRightFoVAngleSinReversed, m_fRightFoVAngleCosReversed;
	vector m_vLeftFoV;
	vector m_vRightFoV;
	
	vector m_vCameraPosition;
	
	vector m_vToTargetVector;
	
	PS_EDWeaponType m_iCurrentWeaponType = PS_EDWeaponType.wp_pistol;
	PS_EDWeaponType m_iNextWeaponType = PS_EDWeaponType.wp_pistol;
	PS_DWeaponInfo m_CurrentWeapon;
	PS_DMobjState m_CurrentWeaponState;
	int m_iWeapontStateTics;
	int m_iArmour;
	int m_aAmmo[4];
	int m_aAmmoMax[4];
	int m_aWeapons[8];
	int m_aKeys[3];
	int m_iWeaponY;
	int m_iFlashTicks;
	PS_DMobjState m_CurrentFlashState;
	
	PS_DLineDef m_TargetLineDef;
	
	int m_iPickupTicks;
	int m_iDamageTicks;
	int m_iAttackTicks;
	int m_iWeaponPickupTicks;
	int m_iCurrentFace;
	int m_iFaceTicks;
	int m_iHazardTicks;
	
	int m_iExtraLight;
	
	int m_iWeaponReady;
	bool m_bActivated = false;
	
	ref array<string> m_aMessages = {};
	int m_iMessagesOffset;
	int m_iMessagesTicks;
	int m_iBackpack;
	
	int m_iTraceRecursion;
	int m_iDeadCamera;
	
	//------------------------------------------------------------------------------------------------
	override void Move()
	{
		m_iTraceRecursion = 5;
		super.Move();
		if (m_vPositionTeleport != "0 0 0")
		{
				m_vCameraPosition[0] = m_vPosition[0];
				m_vCameraPosition[1] = m_vPosition[1];
				m_vCameraPosition[2] = m_vPosition[2] + PS_DConst.CAMERA_HEIGHT;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	override vector TracePathBBOX(vector from, vector to, float height)
	{
		if (m_iFlags & PS_EDMobjFlag.MF_NOCLIP)
		{
			TracePath(from, to, height, true);
			m_vPosition = to;
			return to;
		}
		
		m_iTraceRecursion--;
		if (m_iTraceRecursion <= 0) // Stuck in corner
			return from;
		
		m_vIntersectNormal = "inf inf inf";
		
		// trace and reflect
		vector intersects[5];
		float minDistance = float.MAX;
		int minI;
		intersects[0] = TracePath(from + m_BBOX.m_aOffsets[0], to + m_BBOX.m_aOffsets[0], height, false);
		intersects[1] = TracePath(from + m_BBOX.m_aOffsets[1], to + m_BBOX.m_aOffsets[1], height, false);
		intersects[2] = TracePath(from + m_BBOX.m_aOffsets[2], to + m_BBOX.m_aOffsets[2], height, false);
		intersects[3] = TracePath(from + m_BBOX.m_aOffsets[3], to + m_BBOX.m_aOffsets[3], height, false);
		for (int i = 0; i < 4; i++)
		{
			float distance = vector.Distance(intersects[i], from + m_BBOX.m_aOffsets[i]);
			if (distance < minDistance)
			{
				minDistance = distance;
				minI = i;
			}
		}
		intersects[4] = TracePathEntities(from, to, height);
		float distance = vector.Distance(intersects[4], from);
		if (distance < minDistance)
			minI = 4;
		
		vector newPosition = intersects[minI];
		if (minI < 4)
			newPosition -= m_BBOX.m_aOffsets[minI];
		
		// Trace center for specials
		TracePath(from, newPosition, height, true);
		
		if (CheckPosition(newPosition, height, m_BBOX.m_aOffsets))
			return from;
		
		// try continue along the wall
		if (m_vIntersectNormal != "inf inf inf")
		{
			vector moveVector = to - from;
			moveVector[2] = 0;
			float distanceTraveled = (newPosition - from).Length();
			//vector newMoveVector = (m_CollidedLineDef.m_vEndVertex - m_CollidedLineDef.m_vStartingVertex).Normalized() * (moveVector.Length() - distanceTraveled);
			vector newMoveVector = PS_Math2D.Rotate(m_vIntersectNormal, Math.PI_HALF).Normalized() * (moveVector.Length() - distanceTraveled);
			newMoveVector = newMoveVector * PS_Math2D.Dot(newMoveVector.Normalized(), moveVector.Normalized());
			return TracePathBBOX(newPosition, newPosition + newMoveVector, height);
		}
		
		return newPosition;
	}
	
	void AddMessage(string message)
	{
		if (m_aMessages.Count() == 0)
			m_iMessagesTicks = 30;
		m_aMessages.Insert(message);
	}
	
	override void Rotate(float rotation)
	{
		super.Rotate(rotation);
		
		m_fAngleSin         = Math.Sin(m_fAngle);
		m_fAngleSinReversed = Math.Sin(-m_fAngle);
		m_fAngleCos         = Math.Cos(m_fAngle);
		m_fAngleCosReversed = Math.Cos(-m_fAngle);
		
		float leftAngle = m_fAngle - PS_DConst.HORIZONTAL_FOV_HALF;
		m_fLeftFoVAngleSin         = Math.Sin(leftAngle);
		m_fLeftFoVAngleSinReversed = Math.Sin(-leftAngle);
		m_fLeftFoVAngleCos         = Math.Cos(leftAngle);
		m_fLeftFoVAngleCosReversed = Math.Cos(-leftAngle);
		m_vLeftFoV = Vector(m_fLeftFoVAngleSin, m_fLeftFoVAngleCos, 0);
		
		float rightAngle = m_fAngle + PS_DConst.HORIZONTAL_FOV_HALF;
		m_fRightFoVAngleSin         = Math.Sin(rightAngle);
		m_fRightFoVAngleSinReversed = Math.Sin(-rightAngle);
		m_fRightFoVAngleCos         = Math.Cos(rightAngle);
		m_fRightFoVAngleCosReversed = Math.Cos(-rightAngle);
		m_vRightFoV = Vector(m_fRightFoVAngleSin, m_fRightFoVAngleCos, 0);
	}
	
	override void Update()
	{
		if (m_bDead)
		{
			m_iDeadCamera++;
			if (m_iDeadCamera > 32)
				m_iDeadCamera = 32;
		}
		
		m_vVelocity = m_vVelocity * 0.8;
		
		m_iPickupTicks--;
		m_iDamageTicks--;
		m_iHazardTicks--;
		
		super.Update();
		UpdateWeapon();
		
		if (m_Sector.m_iSpecialType == 9)
		{
			m_Sector.m_iSpecialType = 0;
			m_DMap.m_iSecretsCollected++;
		}
		if (m_Sector.m_iFloorHeight >= m_vPosition[2])
		{
			if (m_Sector.m_iSpecialType == 7)
			{
				if (m_iHazardTicks <= 0)
				{
					if (Math.Mod(m_DMap.m_iTickNum, 30) == 0)
					{
						ApplyDamage(5, null);
					}
				}
			}
			if (m_Sector.m_iSpecialType == 16)
			{
				if (m_iHazardTicks <= 0)
				{
					if (Math.Mod(m_DMap.m_iTickNum, 30) == 0)
					{
						ApplyDamage(20, null);
					}
				}
			}
			if (m_Sector.m_iSpecialType == 11)
			{
				if (Math.Mod(m_DMap.m_iTickNum, 30) == 0)
				{
					ApplyDamage(20, null);
					if (m_iHealth < 10)
						m_DMap.m_DMain.EndGame();
				}
			}
		}
		
		if (m_Sector.m_SpecialAction)
			m_Sector.m_SpecialAction.PlayerPresent(this);
		
		m_vCameraPosition[0] = m_vPosition[0];
		m_vCameraPosition[1] = m_vPosition[1];
		vector velocity2D = m_vVelocity;
		velocity2D[2] = 0;
		if (!m_bDead)
			m_vCameraPosition[2] = m_vCameraPosition[2] + Math.Sin(GetGame().GetWorld().GetWorldTime() / 100) * velocity2D.Length() * 0.2;
		m_vCameraPosition[2] = Math.Lerp(m_vCameraPosition[2], m_vPosition[2] + PS_DConst.CAMERA_HEIGHT - m_iDeadCamera, 0.2);
		
		UpdateTargetEntity();
		UpdateTargetLineDef();
		TouchSpecial();
		if (m_DMap.m_DMain.m_DInput.m_fAction > 0)
		{
			if (!m_bActivated)
				ActivateSpecial();
			m_bActivated = true;
		}
		else
		 	m_bActivated = false;
		
		UpdateFace();
		UpdateMessages();
	}
	
	void UpdateMessages()
	{
		if (m_iMessagesOffset > 0)
			m_iMessagesOffset--;
		m_iMessagesTicks--;
		if (m_iMessagesTicks == 0)
		{
			if (m_aMessages.Count() > 0)
				m_aMessages.RemoveOrdered(0);
			m_iMessagesTicks = 30;
			m_iMessagesOffset = 8;
		}
	}
	
	void UpdateFace()
	{
		if (m_iWeaponPickupTicks > 0)
		{
			m_iCurrentFace = 6;
			m_iWeaponPickupTicks--;
		}
		else if (m_iAttackTicks > 0)
		{
			m_iCurrentFace = 7;
			m_iAttackTicks--;
		}
		else if (m_iFaceTicks <= 0)
		{
			m_iCurrentFace = m_DMap.m_DMain.m_RandomGenerator.RandInt(0, 3);
			m_iFaceTicks = 30;
		}
		m_iFaceTicks--;
	}
	
	void UpdateTargetEntity()
	{
		m_vToTargetVector = Vector(m_fAngleSin * 2560, m_fAngleCos * 2560, 0);
		
		for (float angle = 0; angle <= 15; angle += 5)
		{
			vector lookVectorRotated = PS_Math2D.Rotate(m_vToTargetVector, angle * Math.DEG2RAD);
			m_DMap.m_DBlockMap.TraceAll(m_vPosition, m_vPosition + lookVectorRotated, PS_EDMobjFlag.MF_SOLID);
			m_TargetEntity = m_DMap.m_DBlockMap.GetFirstNotObstructedEntity(this);
			if (m_TargetEntity)
			{
				m_vToTargetVector = lookVectorRotated;
				break;
			}
			lookVectorRotated = PS_Math2D.Rotate(m_vToTargetVector, angle * -Math.DEG2RAD);
			m_DMap.m_DBlockMap.TraceAll(m_vPosition, m_vPosition + lookVectorRotated, PS_EDMobjFlag.MF_SOLID);
			m_TargetEntity = m_DMap.m_DBlockMap.GetFirstNotObstructedEntity(this);
			if (m_TargetEntity)
			{
				m_vToTargetVector = lookVectorRotated;
				break;
			}
		}
		
		if (m_TargetEntity)
		{
			vector vectorToTargetCenter = m_TargetEntity.m_vPosition - m_vCameraPosition;
			vectorToTargetCenter[2] = 0;
			m_vToTargetVector = m_vToTargetVector.Normalized() * vectorToTargetCenter.Length();
			float height = (m_vCameraPosition[2] - m_vPosition[2]);
			height = Math.Min(height, m_TargetEntity.m_MobjInfo.m_iHeight - 1);
			m_vToTargetVector[2] = (m_TargetEntity.m_vPosition[2] + height) - m_vCameraPosition[2];
			m_vToTargetVector = m_vToTargetVector.Normalized() * 2560;
		}
	}
	
	void UpdateTargetLineDef()
	{
		vector lookVector = Vector(m_fAngleSin * 96, m_fAngleCos * 96, 0);
		
		m_DMap.m_DBlockMap.TraceAll(m_vPosition, m_vPosition + lookVector, 0);
		m_TargetLineDef = null;
		foreach (PS_DLineDef lineDef : m_DMap.m_DBlockMap.s_aIntersectedLineDefs)
		{
			if (GetLineDefNormal(lineDef, m_vPosition[2]) != "0 0 0")
			{
				m_TargetLineDef = lineDef;
				return;
			}
		}
	}
	
	void UpdateWeapon()
	{
		m_iWeaponReady--;
		ChangeWeapon();
		if (m_CurrentFlashState)
		{
			if (m_iFlashTicks <= 0)
			{
				m_CurrentFlashState = PS_DInfo.m_aMobjStates[m_CurrentFlashState.m_NextStateNum];
				m_iFlashTicks = m_CurrentFlashState.m_iTics;
				PS_DStateMachine.Action(m_CurrentFlashState.m_MobjActions);
				if (m_CurrentFlashState.m_MobjActions == PS_DMobjActions.A_Light0)
					m_CurrentFlashState = null;
			} else {
				m_iFlashTicks--;
			}
		}
		
		if (m_iWeapontStateTics <= 0)
		{
			m_CurrentWeaponState = PS_DInfo.m_aMobjStates[m_CurrentWeaponState.m_NextStateNum];
			m_iWeapontStateTics = m_CurrentWeaponState.m_iTics;
			PS_DStateMachine.Action(m_CurrentWeaponState.m_MobjActions);
		} else {
			m_iWeapontStateTics--;
		}
	}
	
	override void ApplyDamage(int damage, PS_DEntity instigator)
	{
		if (m_bDead)
			return;
		
		if (m_DMap.m_DMain.m_iDifficulty == 0)
			damage >>= 1;
		if (m_DMap.m_DMain.m_iDifficulty == 4)
			damage <<= 1;
		
		PS_DSoundEffect.PlaySound(m_MobjInfo.m_iPainSound, m_vPosition);
		
		// Damage effect
		int ticks = ((float)damage / 100 * 12) + 6;
		if (ticks > 18)
			ticks = 18;
		if (ticks > m_iDamageTicks)
			m_iDamageTicks = ticks;
		
		// 75% armour
		int armourDamage = damage * 0.75;
		int healthDamage = damage - armourDamage;
		if (armourDamage > m_iArmour)
		{
			armourDamage -= m_iArmour;
			m_iArmour = 0;
			healthDamage += armourDamage;
		}
		else m_iArmour -= armourDamage;
		
		// Health
		m_InstigatorEntity = instigator;
		m_iHealth -= healthDamage;
		if (m_iHealth < 0)
		{
			m_bDead = true;
			m_iDamageTicks = 60;
			m_iHealth = 0;
			PS_DSoundEffect.PlaySound(m_MobjInfo.m_iDeathSound, m_vPosition);
		}
	}
	
	void ChangeWeapon()
	{
		int targetSlot = -1;
		if (m_DMap.m_DMain.m_DInput.m_iWeaponSlot == 0)
		{
			if (m_iCurrentWeaponType == PS_EDWeaponType.wp_fist)
				targetSlot = 7;
			else
				targetSlot = 0;
		}
		else if (m_DMap.m_DMain.m_DInput.m_iWeaponSlot > 0)
		{
			targetSlot = m_DMap.m_DMain.m_DInput.m_iWeaponSlot;
		}
		
		if (targetSlot > -1)
		{
			if (m_aWeapons[targetSlot] == 0)
				return;
			
			m_iNextWeaponType = targetSlot;
		}
	}
	
	// Try activate current targetted lineDef
	void ActivateSpecial()
	{
		if (!m_TargetLineDef)
			return;
		if (m_TargetLineDef.m_Special)
			m_TargetLineDef.m_Special.Activate(m_TargetLineDef, this);
		else
			PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_oof, "0 0 0");
	}
	
	void TouchSpecial()
	{
		// FIXME
		array<vector> offsets = {
			"   0    0 0",
			"-64 -64 0",
			"   0 -64 0",
			" 64 -64 0",
			"-64    0 0",
			"   0    0 0",
			" 64    0 0",
			"-64  64 0",
			"   0  64 0",
			" 64  64 0"
		};
		
		PS_DBlockMapCell.s_iFlag++;
		for (int b = 0; b < 10; b++)
		{
			PS_DBlockMapCell blockCell = m_DMap.m_DBlockMap.GetCell(m_vPosition + offsets[b]);
			if (blockCell.m_iFlag == blockCell.s_iFlag)
				continue;
			blockCell.m_iFlag = blockCell.s_iFlag;
			
			for (int i = 0; i < blockCell.m_sEntities.Count(); i++)
			{
				PS_DEntity entity = blockCell.m_sEntities[i];
				if (entity == null)
					continue;
				
				if (entity != this && entity.m_iFlags & PS_EDMobjFlag.MF_SPECIAL && entity.IsBBOXIntersect(this))
				{
					PS_EDSoundFX sound = PS_EDSoundFX.sfx_itemup;
					if (PS_DPickUp.TryPickUp(this, entity, sound))
					{
						if (entity.m_MobjInfo.m_iFlags & PS_EDMobjFlag.MF_COUNTITEM)
						{
							m_DMap.m_iItemsCollected++;
						}
						
						m_iPickupTicks = 3;
						m_DMap.RemoveEntity(entity);
						PS_DSoundEffect.PlaySound(sound, "0 0 0");
					}
				}
			}
		}
	}
	
	void PS_DEntityPlayer(PS_DMap dMap)
	{
		m_aAmmoMax[PS_EDAmmoType.am_clip] = 200;
		m_aAmmoMax[PS_EDAmmoType.am_shell] = 50;
		m_aAmmoMax[PS_EDAmmoType.am_cell] = 300;
		m_aAmmoMax[PS_EDAmmoType.am_misl] = 50;
		
		m_aWeapons[0] = true;
		m_aWeapons[1] = true;
		
		m_aAmmo[0] = 30;
		m_CurrentWeapon = PS_DWeaponInfo.m_aWeaponInfo[m_iCurrentWeaponType];
		m_CurrentWeaponState = PS_DInfo.m_aMobjStates[m_CurrentWeapon.m_iReadyState];
	}
	
	//------------------------------------------------------------------------------------------------
	override void WriteSave(FileHandle saveFile)
	{
		super.WriteSave(saveFile);
		
		PS_FileHelper.WriteVector(saveFile, m_vCameraPosition);
		PS_FileHelper.WriteStaticArray(saveFile, m_aKeys, 3, 1);
		PS_FileHelper.WriteStaticArray(saveFile, m_aWeapons, 8, 1);
		PS_FileHelper.WriteStaticArray(saveFile, m_aAmmo, 4, 2);
		PS_FileHelper.WriteStaticArray(saveFile, m_aAmmoMax, 4, 2);
		
		saveFile.Write(m_iBackpack, 1);
		saveFile.Write(m_iHazardTicks, 1);
		saveFile.Write(m_iArmour, 1);
		
		saveFile.Write(m_iCurrentWeaponType, 1);
		saveFile.Write(m_iNextWeaponType, 1);
		
		saveFile.Write(m_CurrentWeapon.m_iId, 1);
		saveFile.Write(m_CurrentWeaponState.m_iId, 1);
		
		saveFile.Write(m_iWeapontStateTics, 1);
		saveFile.Write(m_iWeaponY, 1);
	}
	
	//------------------------------------------------------------------------------------------------
	override void ReadSave(FileHandle saveFile)
	{
		super.ReadSave(saveFile);
		m_vCameraPosition = PS_FileHelper.ReadVector(saveFile);
		PS_FileHelper.ReadStaticArray(saveFile, m_aKeys, 3, 1);
		PS_FileHelper.ReadStaticArray(saveFile, m_aWeapons, 8, 1);
		PS_FileHelper.ReadStaticArray(saveFile, m_aAmmo, 4, 2);
		PS_FileHelper.ReadStaticArray(saveFile, m_aAmmoMax, 4, 2);
		
		saveFile.Read(m_iBackpack, 1);
		saveFile.Read(m_iHazardTicks, 1);
		saveFile.Read(m_iArmour, 1);
		
		saveFile.Read(m_iCurrentWeaponType, 1);
		saveFile.Read(m_iNextWeaponType, 1);
		
		int weaponId, weaponStateId;
		saveFile.Read(weaponId, 1);
		saveFile.Read(weaponStateId, 1);
		m_CurrentWeapon = PS_DWeaponInfo.m_aWeaponInfo[weaponId];
		m_CurrentWeaponState = PS_DInfo.m_aMobjStates[weaponStateId];
		
		saveFile.Read(m_iWeapontStateTics, 1);
		saveFile.Read(m_iWeaponY, 1);
	}
}