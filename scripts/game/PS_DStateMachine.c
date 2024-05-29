class PS_DStateMachine
{
	static PS_DMap m_DMap;
	static PS_DEntityPlayer m_Player;
	static PS_DEntity s_ActionEntity;
	
	static void Action(PS_DMobjActions action)
	{
		switch (action)
		{
			// Player
			case PS_DMobjActions.A_ReFire:
				A_Refire();
				break;
			case PS_DMobjActions.A_WeaponReady:
				A_WeaponReady();
				break;
			case PS_DMobjActions.A_Lower:
				A_Lower();
				break;
			case PS_DMobjActions.A_Raise:
				A_Raise();
				break;
			case PS_DMobjActions.A_Saw:
				A_Saw();
				break;
			case PS_DMobjActions.A_Punch:
				A_Punch();
				break;
			case PS_DMobjActions.A_FirePistol:
				A_FirePistol();
				break;
			case PS_DMobjActions.A_FireShotgun:
				A_FireShotgun();
				break;
			case PS_DMobjActions.A_FireCGun:
				A_FireCGun();
				break;
			case PS_DMobjActions.A_FireMissile:
				A_FireMissile();
				break;
			case PS_DMobjActions.A_Light0:
				A_Light0();
				break;
			case PS_DMobjActions.A_Light1:
				A_Light1();
				break;
			case PS_DMobjActions.A_Light2:
				A_Light2();
				break;
			
			// Other
			case PS_DMobjActions.A_Explode:
				A_Explode();
				break;
			
			// Monsters
			case PS_DMobjActions.A_Look:
				A_Look();
				break;
			case PS_DMobjActions.A_Chase:
				A_Chase();
				break;
			case PS_DMobjActions.A_Scream:
				A_Scream();
				break;
			case PS_DMobjActions.A_Fall:
				A_Fall();
				break;
			case PS_DMobjActions.A_FaceTarget:
				A_FaceTarget();
				break;
			case PS_DMobjActions.A_TroopAttack:
				A_TroopAttack();
				break;
			case PS_DMobjActions.A_SPosAttack:
				A_SPosAttack();
				break;
			case PS_DMobjActions.A_SargAttack:
				A_SargAttack();
				break;
			case PS_DMobjActions.A_PosAttack:
				A_PosAttack();
				break;
			case PS_DMobjActions.A_BruisAttack:
				A_BruisAttack();
				break;
		}
	}
	
	// Boom
	static void A_Explode()
	{
		PS_DBlockMap blockMap = s_ActionEntity.m_DMap.m_DBlockMap;
		PS_DBlockMapCell cell = blockMap.GetCell(s_ActionEntity.m_vPosition);
		
		foreach (PS_DBlockMapCell cellNeighbour : cell.m_aNeighbours)
		{
			foreach (PS_DEntity entity : cellNeighbour.m_sEntities)
			{
				if (!(entity.m_iFlags & PS_EDMobjFlag.MF_SHOOTABLE))
					continue;
				
				m_DMap.m_DBlockMap.TraceShoot(
					s_ActionEntity.m_vPosition + Vector(0, 0, s_ActionEntity.m_MobjInfo.m_iHeight/2), 
					entity.m_vPosition + Vector(0, 0, entity.m_MobjInfo.m_iHeight/2),
					entity, true
				);
				
				if (PS_DBlockMap.s_Entity != entity)
					continue;
				
				vector toTarget = entity.m_vPosition - s_ActionEntity.m_vPosition;
				toTarget[2] = 0;
				float distance = toTarget.Length() - 64;
				if (distance < 32)
					distance = 32;
				float damage = 128 / (distance/32);
				entity.ApplyDamage(damage, s_ActionEntity.m_AttackerEntity);
			}
		}
	}
	
	static void A_SargAttack()
	{
		vector from = s_ActionEntity.m_vPosition;
		vector target = s_ActionEntity.m_TargetEntity.m_vPosition;
		
		from[2] = from[2] + s_ActionEntity.m_MobjInfo.m_iHeight / 2;
		target[2] = target[2] + s_ActionEntity.m_TargetEntity.m_MobjInfo.m_iHeight / 2;
		
		vector toTarget = target - from;
		
		if (toTarget.Length() < 96)
		{
			PS_DSoundEffect.PlaySound(s_ActionEntity.m_MobjInfo.m_iAttackSound, s_ActionEntity.m_vPosition);
			s_ActionEntity.m_TargetEntity.ApplyDamage(Math.RandomIntInclusive(4, 40), s_ActionEntity);
		}
	}
	
	static void A_BruisAttack()
	{
		vector from = s_ActionEntity.m_vPosition;
		vector target = s_ActionEntity.m_TargetEntity.m_vPosition;
		
		from[2] = from[2] + s_ActionEntity.m_MobjInfo.m_iHeight / 2;
		target[2] = target[2] + s_ActionEntity.m_TargetEntity.m_MobjInfo.m_iHeight / 2;
		
		vector toTarget = target - from;
		
		if (toTarget.Length() < 96)
		{
			PS_DSoundEffect.PlaySound(s_ActionEntity.m_MobjInfo.m_iAttackSound, s_ActionEntity.m_vPosition);
			s_ActionEntity.m_TargetEntity.ApplyDamage(Math.RandomIntInclusive(10, 80), s_ActionEntity);
		} else {
			PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_firsht, s_ActionEntity.m_vPosition);
			SpawnMissile(s_ActionEntity, from, toTarget, PS_DMobjType.MT_BRUISERSHOT)
		}
	}
	
	// Trooper shoot
	static void A_TroopAttack()
	{
		vector from = s_ActionEntity.m_vPosition;
		vector target = s_ActionEntity.m_TargetEntity.m_vPosition;
		
		from[2] = from[2] + s_ActionEntity.m_MobjInfo.m_iHeight / 2;
		target[2] = target[2] + s_ActionEntity.m_TargetEntity.m_MobjInfo.m_iHeight / 2;
		
		vector toTarget = target - from;
		
		if (toTarget.Length() < 96)
		{
			PS_DSoundEffect.PlaySound(s_ActionEntity.m_MobjInfo.m_iAttackSound, s_ActionEntity.m_vPosition);
			s_ActionEntity.m_TargetEntity.ApplyDamage(Math.RandomIntInclusive(3, 24), s_ActionEntity);
		} else {
			PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_firsht, s_ActionEntity.m_vPosition);
			SpawnMissile(s_ActionEntity, from, toTarget, PS_DMobjType.MT_TROOPSHOT)
		}
	}
	
	static void SpawnMissile(PS_DEntity attacker, vector from, vector direction, PS_DMobjType type)
	{
		PS_DMap dMap = s_ActionEntity.m_DMap;
		
		PS_DEntity entity = new PS_DEntity(dMap);
		entity.m_vPosition = from;
		
		float angleToTarget = -Math.Atan2(direction[1], direction[0]);
		entity.m_fAngle = angleToTarget + Math.PI;
		
		entity.m_MobjInfo = PS_DInfo.m_aMobjInfo[type];
		entity.m_MobjState = PS_DInfo.m_aMobjStates[entity.m_MobjInfo.m_iSpawnState];
		entity.m_vVelocity = direction.Normalized() * (float) entity.m_MobjInfo.m_iSpeed;
		entity.m_AttackerEntity = attacker;
		entity.m_iFlags = entity.m_MobjInfo.m_iFlags;
		entity.m_iStateTics = entity.m_MobjState.m_iTics;
		entity.m_BBOX = new PS_DEntityBBox(entity.m_MobjInfo);
		dMap.m_aEntities.Insert(entity);
	}
	
	// Sergant
	static void A_SPosAttack()
	{
		vector from = s_ActionEntity.m_vPosition;
		vector target = s_ActionEntity.m_TargetEntity.m_vPosition;
		
		from[2] = from[2] + s_ActionEntity.m_MobjInfo.m_iHeight / 2;
		target[2] = target[2] + s_ActionEntity.m_TargetEntity.m_MobjInfo.m_iHeight / 2;
		
		PS_DSoundEffect.PlaySound(s_ActionEntity.m_MobjInfo.m_iAttackSound, s_ActionEntity.m_vPosition);
		
		// Spread
		vector toTarget = target - from;
		toTarget = toTarget.Normalized() * 3000;
		
		for (int i = 0; i < 3; i++)
		{
			vector toTargetShoot = PS_Math2D.Rotate(toTarget, Math.RandomFloat(-1, 1) * 7.5 * Math.DEG2RAD);
			vector to = from + toTargetShoot;
			PS_DEntity targetEntity = Shoot(s_ActionEntity, from, to);
			if (targetEntity)
				targetEntity.ApplyDamage(Math.RandomIntInclusive(3, 15), s_ActionEntity);
		}
	}
	
	// Possesed shoot
	static void A_PosAttack()
	{
		vector from = s_ActionEntity.m_vPosition;
		vector target = s_ActionEntity.m_TargetEntity.m_vPosition;
		
		from[2] = from[2] + s_ActionEntity.m_MobjInfo.m_iHeight / 2;
		target[2] = target[2] + s_ActionEntity.m_TargetEntity.m_MobjInfo.m_iHeight / 2;
		
		PS_DSoundEffect.PlaySound(s_ActionEntity.m_MobjInfo.m_iAttackSound, s_ActionEntity.m_vPosition);
		
		// Spread
		vector toTarget = target - from;
		toTarget = toTarget.Normalized() * 3000;
		toTarget = PS_Math2D.Rotate(toTarget, m_DMap.m_DMain.m_RandomGenerator.RandFloatXY(-1, 1) * 7.5 * Math.DEG2RAD);
		vector to = from + toTarget;
		
		PS_DEntity targetEntity = Shoot(s_ActionEntity, from, to);
		if (targetEntity)
			targetEntity.ApplyDamage(m_DMap.m_DMain.m_RandomGenerator.RandIntInclusive(3, 15), s_ActionEntity);
	}
	
	// Rotate to current target
	static void A_FaceTarget()
	{
		if (!s_ActionEntity.m_TargetEntity)
			return;
		
		vector toTarget = s_ActionEntity.m_vPosition - s_ActionEntity.m_TargetEntity.m_vPosition;
		float angleToTarget = -Math.Atan2(toTarget[1], toTarget[0]);
		s_ActionEntity.m_fAngle = angleToTarget;
	}
	
	static void A_Scream()
	{
		PS_DSoundEffect.PlaySound(s_ActionEntity.m_MobjInfo.m_iDeathSound, s_ActionEntity.m_vPosition);
	}
	
	// Move and try attack
	static void A_Chase()
	{
		if (!s_ActionEntity.m_TargetEntity)
		{
			PS_DMobjState lookState = PS_DInfo.m_aMobjStates[s_ActionEntity.m_MobjInfo.m_iSpawnState];
			s_ActionEntity.m_MobjState = lookState;
			s_ActionEntity.m_iStateTics = lookState.m_iTics;
			return;
		}
		
		if (s_ActionEntity.m_TargetEntity.m_bDead)
		{
			s_ActionEntity.m_TargetEntity = null;
			return;
		}
		
		s_ActionEntity.m_iReactionTime--;
		if (s_ActionEntity.m_iReactionTime > 0)
		{
			s_ActionEntity.m_fAngle += m_DMap.m_DMain.m_RandomGenerator.RandFloatXY(-0.1, 0.1);
			return;
		}
		
		if (IsSeeTarget(s_ActionEntity.m_TargetEntity))
		{
			if (s_ActionEntity.m_MobjInfo.m_iMissileState && s_ActionEntity.m_iMoveCount < 0)
			{
				PS_DMobjState lookState = PS_DInfo.m_aMobjStates[s_ActionEntity.m_MobjInfo.m_iMissileState];
				s_ActionEntity.m_MobjState = lookState;
				s_ActionEntity.m_iStateTics = lookState.m_iTics;
				s_ActionEntity.m_iMoveCount = 6;
				s_ActionEntity.m_iMoveTics = 0;
				s_ActionEntity.m_vVelocity = "0 0 0";
				PS_DStateMachine.Action(lookState.m_MobjActions);	
				return;
			}
			if (s_ActionEntity.m_MobjInfo.m_iMeleeState && vector.Distance(s_ActionEntity.m_vPosition, s_ActionEntity.m_TargetEntity.m_vPosition) < 96)
			{
				PS_DMobjState lookState = PS_DInfo.m_aMobjStates[s_ActionEntity.m_MobjInfo.m_iMeleeState];
				s_ActionEntity.m_MobjState = lookState;
				s_ActionEntity.m_iStateTics = lookState.m_iTics;
				s_ActionEntity.m_iMoveCount = 6;
				s_ActionEntity.m_iMoveTics = 0;
				s_ActionEntity.m_vVelocity = "0 0 0";
				PS_DStateMachine.Action(lookState.m_MobjActions);	
				return;
			}
		}
		
		if (s_ActionEntity.m_CollidedLineDef || s_ActionEntity.m_CollidedEntity)
		{
			s_ActionEntity.m_fAngle += s_ActionEntity.m_fRotationDirection;
		}
		
		if (s_ActionEntity.m_iMoveTics <= 0)
		{
			s_ActionEntity.m_fRotationDirection = PS_Math2D.PI_QUAT;
			if (m_DMap.m_DMain.m_RandomGenerator.RandIntInclusive(0, 1) == 0)
				s_ActionEntity.m_fRotationDirection *= -1;
			vector toTarget = s_ActionEntity.m_vPosition - s_ActionEntity.m_TargetEntity.m_vPosition;
			float angleToTarget = -Math.Atan2(toTarget[1], toTarget[0]);
			angleToTarget += PS_Math2D.PI_QUAT * (float) m_DMap.m_DMain.m_RandomGenerator.RandIntInclusive(-1, 1);
			s_ActionEntity.m_fAngle = angleToTarget;
			
			s_ActionEntity.m_iMoveTics = 8;
		}
		
		s_ActionEntity.m_vVelocity = Vector(Math.Sin(s_ActionEntity.m_fAngle - Math.PI_HALF), Math.Cos(s_ActionEntity.m_fAngle - Math.PI_HALF), 0);
		s_ActionEntity.m_vVelocity *= (float) s_ActionEntity.m_MobjInfo.m_iSpeed * 0.5;
		s_ActionEntity.m_iMoveTics--;
		s_ActionEntity.m_iMoveCount--;
	}
	
	// Look for player
	static void A_Look()
	{
		if (m_Player.m_bDead)
			return;
		
		PS_DMap dMap = m_Player.m_DMap;
		PS_DEntity lookEntity;
		
		if (s_ActionEntity.m_Sector && !(s_ActionEntity.m_iFlags & PS_EDMobjFlag.MF_AMBUSH))
		{
			lookEntity = s_ActionEntity.m_Sector.m_SoundSource;
		}
		
		if (!lookEntity)
		{
			lookEntity = IsSeeTarget(m_Player, !(s_ActionEntity.m_iFlags & PS_EDMobjFlag.MF_AMBUSH));
			if (lookEntity == m_Player)
				PS_DSoundEffect.PlaySound(s_ActionEntity.m_MobjInfo.m_iSeeSound, s_ActionEntity.m_vPosition);
		}
		
		if (lookEntity == m_Player)
		{
			PS_DMobjState chaseState = PS_DInfo.m_aMobjStates[s_ActionEntity.m_MobjInfo.m_iSeeState];
			s_ActionEntity.m_MobjState = chaseState;
			s_ActionEntity.m_iStateTics = chaseState.m_iTics;
			s_ActionEntity.m_iReactionTime = s_ActionEntity.m_MobjInfo.m_iReactionTime;
			s_ActionEntity.m_TargetEntity = m_Player;
			s_ActionEntity.m_iMoveCount = 8;
			//PS_DStateMachine.Action(s_ActionEntity.ChaseState.m_MobjActions);
		}
	}
	
	static PS_DEntity IsSeeTarget(PS_DEntity target, bool angleCheck = true)
	{
		vector toTarget = s_ActionEntity.m_vPosition - target.m_vPosition;
		
		/*
		float angleToTarget = -Math.Atan2(toTarget[1], toTarget[0]) - s_ActionEntity.m_fAngle;
		angleToTarget = Math.Repeat(angleToTarget + PS_Math2D.PI_QUAT, Math.PI2);
		if (angleCheck && angleToTarget > Math.PI_HALF)
			return null;
		*/
		
		PS_DMap dMap = target.m_DMap;
		vector lookFrom = s_ActionEntity.m_vPosition + Vector(0, 0, s_ActionEntity.m_MobjInfo.m_iHeight * 0.5);
		vector lookTo = target.m_vPosition + Vector(0, 0, target.m_MobjInfo.m_iHeight * 0.5);
		if (vector.Distance(lookFrom, lookTo) < 5000)
		{
			dMap.m_DBlockMap.TraceShoot(lookFrom, lookTo, s_ActionEntity);
			if (target == dMap.m_DBlockMap.s_Entity)
				return target;
		}
		return null;
	}
	
	// Die
	static void A_Fall()
	{
		int flags = s_ActionEntity.m_iFlags;
		flags = flags & ~PS_EDMobjFlag.MF_SOLID;
		s_ActionEntity.m_iFlags = flags;
		s_ActionEntity.m_vVelocity = "0 0 0";
	}
	
	// Weapon flash
	static void A_Light0()
	{
		m_Player.m_iExtraLight = 0;
	}
	static void A_Light1()
	{
		m_Player.m_iExtraLight = 4;
	}
	static void A_Light2()
	{
		m_Player.m_iExtraLight = 8;
	}
	
	static PS_DEntity Shoot(PS_DEntity attacker, vector from, vector to)
	{
		// Shoot
		PS_DMap dMap = attacker.m_DMap;
		dMap.m_DBlockMap.TraceShoot(from, to, attacker);
		
		PS_DEntity targetEntity;
		
		// Create puff
		PS_DMobjInfo mobjInfo = PS_DInfo.m_aMobjInfo[PS_DMobjType.MT_PUFF];
		if (dMap.m_DBlockMap.s_Entity)
		{
			targetEntity = dMap.m_DBlockMap.s_Entity;
			if (!(dMap.m_DBlockMap.s_Entity.m_iFlags & PS_EDMobjFlag.MF_NOBLOOD))
				mobjInfo = PS_DInfo.m_aMobjInfo[PS_DMobjType.MT_BLOOD];
		}
		
		if (dMap.m_DBlockMap.s_Entity || dMap.m_DBlockMap.s_LineDef)
		{
			if (dMap.m_DBlockMap.s_LineDef && dMap.m_DBlockMap.s_LineDef.m_Special)
				dMap.m_DBlockMap.s_LineDef.m_Special.Impact(dMap.m_DBlockMap.s_LineDef, s_ActionEntity);
			PS_DEntity entity = new PS_DEntity(dMap);
			vector normal;
			entity.m_vPosition = dMap.m_DBlockMap.s_vIntersect + dMap.m_DBlockMap.s_vNormal * 2;
			entity.m_fAngle = 0;
			entity.m_MobjInfo = mobjInfo;
			entity.m_MobjState = PS_DInfo.m_aMobjStates[mobjInfo.m_iSpawnState];
			entity.m_iFlags = entity.m_MobjInfo.m_iFlags;
			entity.m_iStateTics = entity.m_MobjState.m_iTics;
			entity.m_BBOX = new PS_DEntityBBox(entity.m_MobjInfo);
			dMap.m_aEntities.Insert(entity);
		}
		
		return targetEntity;
	}
	
	// Weapon
	static void A_Saw()
	{
		// "Sound"
		PS_DMap dMap = m_Player.m_DMap;
		dMap.SoundSource(m_Player);
		
		PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_sawhit, m_Player.m_vPosition);
		if (MeleePlayer())
			if ((m_DMap.m_iTickNum & 7) == 0)
				PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_sawhit, m_Player.m_vPosition);
		else
			if ((m_DMap.m_iTickNum & 7) == 0)
				PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_sawful, m_Player.m_vPosition);
	}
	
	static void A_Punch()
	{
		// "Sound" Power of DOOM punch!
		PS_DMap dMap = m_Player.m_DMap;
		dMap.SoundSource(m_Player);
		
		if (m_Player.m_TargetEntity)
		{
			vector toTarget = m_Player.m_vPosition - m_Player.m_TargetEntity.m_vPosition;
			float angleToTarget = -Math.Atan2(toTarget[1], toTarget[0]) - Math.PI_HALF;
			m_Player.m_fAngle = angleToTarget;
		}
			
		
		if (MeleePlayer())
			PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_punch, m_Player.m_vPosition);
	}
	
	static bool MeleePlayer()
	{
		// Trace shoot
		vector lookVector = Vector(m_Player.m_fAngleSin * 128, m_Player.m_fAngleCos * 128, 0);
		vector to = m_Player.m_vCameraPosition + lookVector;
		PS_DEntity targetEntity;
		if (m_Player.m_TargetEntity && vector.Distance(m_Player.m_TargetEntity.m_vPosition, m_Player.m_vPosition) < 128)
			targetEntity = m_Player.m_TargetEntity;
		else
			targetEntity = Shoot(m_Player, m_Player.m_vCameraPosition, to);
		if (targetEntity)
		{
			targetEntity.ApplyDamage(Math.RandomIntInclusive(2, 20), m_Player);
			return true;
		}
		return false;
	}
	
	static void A_FireShotgun()
	{
		PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_shotgn, m_Player.m_vPosition);
		WeaponFlash();
		
		// "Sound"
		PS_DMap dMap = m_Player.m_DMap;
		dMap.SoundSource(m_Player);
		
		// 5 pellets
		for (int i = 0; i < 5; i++)
		{
			// spread
			vector lookVector = PS_Math2D.Rotate(m_Player.m_vToTargetVector, m_DMap.m_DMain.m_RandomGenerator.RandFloatXY(-1, 1) * 3.25 * Math.DEG2RAD);
			
			vector to = m_Player.m_vCameraPosition + lookVector;
			
			PS_DEntity targetEntity = Shoot(m_Player, m_Player.m_vCameraPosition, to);
			if (targetEntity)
				targetEntity.ApplyDamage(m_DMap.m_DMain.m_RandomGenerator.RandIntInclusive(7, 21), m_Player);
		}
	}
	
	static void A_FireMissile()
	{
		WeaponFlash();
		
		// "Sound"
		PS_DMap dMap = m_Player.m_DMap;
		dMap.SoundSource(m_Player);
		
		vector lookVector = m_Player.m_vToTargetVector;
		
		vector from = m_Player.m_vCameraPosition;
		vector target = from + lookVector;
		
		if (m_Player.m_TargetEntity)
		{
			target = m_Player.m_TargetEntity.m_vPosition;
			target[2] = target[2] + Math.Min(PS_DConst.CAMERA_HEIGHT, m_Player.m_TargetEntity.m_MobjInfo.m_iHeight * 0.5);
		}
			
		vector toTarget = target - from;
		SpawnMissile(m_Player, from, toTarget, PS_DMobjType.MT_ROCKET)
	}
	
	static void A_FireCGun()
	{
		A_FirePistol();
	}
	
	static void A_FirePistol()
	{
		PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_pistol, m_Player.m_vPosition);
		WeaponFlash();
		
		// "Sound"
		PS_DMap dMap = m_Player.m_DMap;
		dMap.SoundSource(m_Player);
		
		// spread
		vector lookVector = PS_Math2D.Rotate(m_Player.m_vToTargetVector, m_DMap.m_DMain.m_RandomGenerator.RandFloatXY(-1, 1) * 3.25 * Math.DEG2RAD);
		
		vector to = m_Player.m_vCameraPosition + lookVector;
		
		PS_DEntity targetEntity = Shoot(m_Player, m_Player.m_vCameraPosition, to);
		if (targetEntity)
			targetEntity.ApplyDamage(m_DMap.m_DMain.m_RandomGenerator.RandIntInclusive(5, 15), m_Player);
	}
	
	static void WeaponFlash()
	{
		// Flash effect
		PS_DWeaponInfo weapon = m_Player.m_CurrentWeapon;
		m_Player.m_CurrentFlashState = PS_DInfo.m_aMobjStates[weapon.m_iFlashState];
		m_Player.m_iFlashTicks = m_Player.m_CurrentFlashState.m_iTics - 1;
		PS_DStateMachine.Action(m_Player.m_CurrentFlashState.m_MobjActions);
	}
	
	static void A_Refire()
	{
		float fire = m_DMap.m_DMain.m_DInput.m_fFire;
		if (fire == 0)
			return;
		
		PS_DWeaponInfo weapon = m_Player.m_CurrentWeapon;
		if (weapon.m_iAmmoType != PS_EDAmmoType.am_noammo)
		{
			int ammo = m_Player.m_aAmmo[weapon.m_iAmmoType];
			if (ammo == 0)
				return;
			ammo--;
			m_Player.m_aAmmo[weapon.m_iAmmoType] = ammo;
		}
		
		PS_DMobjState fireState = PS_DInfo.m_aMobjStates[weapon.m_iAtkState];
		m_Player.m_CurrentWeaponState = fireState;
	}
	
	static void A_WeaponReady()
	{
		PS_DWeaponInfo weapon = m_Player.m_CurrentWeapon;
		
		if (weapon.m_iAtkState == PS_DMobjStateNum.S_SAW1 && (m_DMap.m_iTickNum & 3) == 0)
			PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_sawidl, m_Player.m_vPosition);
		
		if (m_Player.m_bDead)
		{
			PS_DMobjState downState = PS_DInfo.m_aMobjStates[weapon.m_iDownState];
			m_Player.m_CurrentWeaponState = downState;
			return;
		}
		
		if (m_Player.m_iCurrentWeaponType != m_Player.m_iNextWeaponType)
		{
			PS_DMobjState downState = PS_DInfo.m_aMobjStates[weapon.m_iDownState];
			m_Player.m_CurrentWeaponState = downState;
			return;
		}
		
		float fire = m_DMap.m_DMain.m_DInput.m_fFire;
		if (fire == 0)
		{
			m_Player.m_iWeaponReady = 5;
			return;
		}
		m_Player.m_iWeaponReady = 0;
		
		if (weapon.m_iAmmoType != PS_EDAmmoType.am_noammo)
		{
			int ammo = m_Player.m_aAmmo[weapon.m_iAmmoType];
			if (ammo == 0)
				return;
			ammo--;
			m_Player.m_aAmmo[weapon.m_iAmmoType] = ammo;
		}
		
		PS_DMobjState fireState = PS_DInfo.m_aMobjStates[weapon.m_iAtkState];
		m_Player.m_CurrentWeaponState = fireState;
	}
	static void A_Raise()
	{
		m_Player.m_iWeaponY -= 4;
		if (m_Player.m_iWeaponY <= 0)
		{
			m_Player.m_iWeaponY = 0;
			PS_DWeaponInfo weapon = m_Player.m_CurrentWeapon;
			PS_DMobjState readyState = PS_DInfo.m_aMobjStates[weapon.m_iReadyState];
			m_Player.m_CurrentWeaponState = readyState;
		}
	}
	static void A_Lower()
	{
		m_Player.m_iWeaponY += 4;
		if (m_Player.m_iWeaponY >= 32 && !m_Player.m_bDead)
		{
			m_Player.m_iCurrentWeaponType = m_Player.m_iNextWeaponType;
			m_Player.m_CurrentWeapon = PS_DWeaponInfo.m_aWeaponInfo[m_Player.m_iCurrentWeaponType];
			PS_DMobjState raiseState = PS_DInfo.m_aMobjStates[m_Player.m_CurrentWeapon.m_iUpState];
			m_Player.m_CurrentWeaponState = raiseState;
		}
	}
}