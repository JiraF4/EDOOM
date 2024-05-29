class PS_DPickUp
{
	static bool TryHealth(PS_DEntityPlayer player, int health)
	{
		if (player.m_iHealth < 100)
		{
			player.m_iHealth += health;
			if (player.m_iHealth > 100)
				player.m_iHealth = 100;
			return true;
		}
		return false;
	}
	
	static bool TryAmmo(PS_DEntityPlayer player, int count, PS_EDAmmoType type)
	{
		if (player.m_aAmmo[type] < player.m_aAmmoMax[type])
		{
			player.m_aAmmo[type] = player.m_aAmmo[type] + count;
			if (player.m_aAmmo[type] > player.m_aAmmoMax[type])
				player.m_aAmmo[type] = player.m_aAmmoMax[type];
			return true;
		}
		return false;
	}
	
	static bool TryKey(PS_DEntityPlayer player, int keyNum, int keyType)
	{
		player.m_aKeys[keyNum] = keyType;
		return true;
	}
	
	static bool TryWeapon(PS_DEntityPlayer player, PS_EDWeaponType type)
	{
		if (player.m_aWeapons[type] == 0)
		{
			player.m_aWeapons[type] = 1;
			player.m_iWeaponPickupTicks = 16;
		}
		
		switch (type)
		{
			case PS_EDWeaponType.wp_shotgun:
				TryAmmo(player, 20, PS_EDAmmoType.am_shell);
				break;
			case PS_EDWeaponType.wp_chaingun:
				TryAmmo(player, 50, PS_EDAmmoType.am_clip);
				break;
			case PS_EDWeaponType.wp_missile:
				TryAmmo(player, 5, PS_EDAmmoType.am_misl);
				break;
		}
		
		return true;
	}
	
	static bool TryPickUp(PS_DEntityPlayer player, PS_DEntity pickup, out PS_EDSoundFX sound)
	{
		switch (pickup.m_MobjState.m_SpriteNum)
    	{
			// Heath / Armour
			case PS_DMobjSpriteNum.SPR_SUIT: // Hazard suit
				player.m_iHazardTicks = 35 * 30;
				player.AddMessage(PS_DMessages.GOTSUIT);
				sound = PS_EDSoundFX.sfx_getpow;
				return true;
				break;
			case PS_DMobjSpriteNum.SPR_ARM1: // Green armour - 100
				if (player.m_iArmour < 100)
				{
					player.AddMessage(PS_DMessages.GOTARMOR);
					player.m_iArmour = 100;
					return true;
				}
				break;
			case PS_DMobjSpriteNum.SPR_ARM2: // Blue armour - 200
				if (player.m_iArmour < 200)
				{
					player.AddMessage(PS_DMessages.GOTMEGA);
					player.m_iArmour = 200;
					return true;
				}
				break;
			case PS_DMobjSpriteNum.SPR_SOUL: // Blue soul orb
				player.m_iHealth += 100;
				if (player.m_iHealth > 200)
				    player.m_iHealth = 200;
				player.AddMessage(PS_DMessages.GOTSUPER);
				sound = PS_EDSoundFX.sfx_getpow;
				return true; // Pickup anyway
				break;
	      case PS_DMobjSpriteNum.SPR_BPAK:
				if (player.m_iBackpack == 0)
				{
					player.m_aAmmoMax[0] = player.m_aAmmoMax[0] * 2;
					player.m_aAmmoMax[1] = player.m_aAmmoMax[1] * 2;
					player.m_aAmmoMax[2] = player.m_aAmmoMax[2] * 2;
					player.m_aAmmoMax[3] = player.m_aAmmoMax[3] * 2;
					player.m_iBackpack = 1;
				}
				TryAmmo(player, 10, PS_EDAmmoType.am_clip);
				TryAmmo(player, 1, PS_EDAmmoType.am_misl);
				TryAmmo(player, 20, PS_EDAmmoType.am_cell);
				TryAmmo(player, 4, PS_EDAmmoType.am_shell);
				player.AddMessage(PS_DMessages.GOTBACKPACK);
				return true; // Pickup anyway
				break;
			case PS_DMobjSpriteNum.SPR_BON1: // Blue brew
				player.AddMessage(PS_DMessages.GOTHTHBONUS);
				if (player.m_iHealth < 200)
					player.m_iHealth++;
				return true; // Pickup anyway
				break;
			case PS_DMobjSpriteNum.SPR_BON2: // Helmet
				player.AddMessage(PS_DMessages.GOTARMBONUS);
				if (player.m_iArmour < 200)
					player.m_iArmour++;
				return true; // Pickup anyway
				break;
			case PS_DMobjSpriteNum.SPR_STIM: // Small medkit
				if (TryHealth(player, 10))
				{
					player.AddMessage(PS_DMessages.GOTSTIM);
					return true;
				}
				break;
			case PS_DMobjSpriteNum.SPR_MEDI: // Big medkit
				if (TryHealth(player, 25))
				{
					if (player.m_iHealth > 50)
						player.AddMessage(PS_DMessages.GOTMEDIKIT);
					else
						player.AddMessage(PS_DMessages.GOTMEDINEED);
					return true;
				}
				break;
			
			// int	clipammo[NUMAMMO] = {10, 4, 20, 1}; - A? Why that needed at all?
			// Ammo
			case PS_DMobjSpriteNum.SPR_CLIP: // One pistol clip
				if (TryAmmo(player, 10, PS_EDAmmoType.am_clip))
				{
					player.AddMessage(PS_DMessages.GOTCLIP);
					return true;
				};
				break;
			case PS_DMobjSpriteNum.SPR_AMMO: // Box of clips
				if (TryAmmo(player, 50, PS_EDAmmoType.am_clip))
				{
					player.AddMessage(PS_DMessages.GOTCLIPBOX);
					return true;
				};
				break;
			case PS_DMobjSpriteNum.SPR_ROCK: // One rocket
				if (TryAmmo(player, 1, PS_EDAmmoType.am_misl))
				{
					player.AddMessage(PS_DMessages.GOTROCKET);
					return true;
				};
				break;
			case PS_DMobjSpriteNum.SPR_BROK: // Rockets box
				if (TryAmmo(player, 5, PS_EDAmmoType.am_misl))
				{
					player.AddMessage(PS_DMessages.GOTROCKBOX);
					return true;
				};
				break;
			case PS_DMobjSpriteNum.SPR_CELL: // 4V battery
				if (TryAmmo(player, 20, PS_EDAmmoType.am_cell))
				{
					player.AddMessage(PS_DMessages.GOTCELL);
					return true;
				};
				break;
			case PS_DMobjSpriteNum.SPR_CELP: // 20V battery
				if (TryAmmo(player, 100, PS_EDAmmoType.am_cell))
				{
					player.AddMessage(PS_DMessages.GOTCELLBOX);
					return true;
				};
				break;
			case PS_DMobjSpriteNum.SPR_SHEL: // Shell
				if (TryAmmo(player, 4, PS_EDAmmoType.am_shell))
				{
					player.AddMessage(PS_DMessages.GOTSHELLS);
					return true;
				};
				break;
			case PS_DMobjSpriteNum.SPR_SBOX: // Shell s
				if (TryAmmo(player, 20, PS_EDAmmoType.am_shell))
				{
					player.AddMessage(PS_DMessages.GOTSHELLBOX);
					return true;
				};
				break;
			// Weapons
			case PS_DMobjSpriteNum.SPR_CSAW: // Saw
				if (TryWeapon(player, PS_EDWeaponType.wp_chainsaw))
				{
					sound = PS_EDSoundFX.sfx_wpnup;
					player.AddMessage(PS_DMessages.GOTCHAINSAW);
					return true;
				};
			case PS_DMobjSpriteNum.SPR_SHOT: // Shotgun
				if (TryWeapon(player, PS_EDWeaponType.wp_shotgun))
				{
					sound = PS_EDSoundFX.sfx_wpnup;
					player.AddMessage(PS_DMessages.GOTSHOTGUN);
					return true;
				};
				break;
			case PS_DMobjSpriteNum.SPR_MGUN: // Chaingun
				if (TryWeapon(player, PS_EDWeaponType.wp_chaingun))
				{
					sound = PS_EDSoundFX.sfx_wpnup;
					player.AddMessage(PS_DMessages.GOTCHAINGUN);
					return true;
				};
				break;
			case PS_DMobjSpriteNum.SPR_LAUN: // Launcher
				if (TryWeapon(player, PS_EDWeaponType.wp_missile))
				{
					sound = PS_EDSoundFX.sfx_wpnup;
					player.AddMessage(PS_DMessages.GOTLAUNCHER);
					return true;
				};
				break;
			
			// Keys
			case PS_DMobjSpriteNum.SPR_BKEY:
				if (TryKey(player, 0, 1))
				{
					player.AddMessage(PS_DMessages.GOTBLUECARD);
					return true;
				};
				break;
		    
			case PS_DMobjSpriteNum.SPR_YKEY:
				if (TryKey(player, 1, 1))
				{
					player.AddMessage(PS_DMessages.GOTYELWCARD);
					return true;
				};
				break;

			case PS_DMobjSpriteNum.SPR_RKEY:
				if (TryKey(player, 2, 1))
				{
					player.AddMessage(PS_DMessages.GOTREDCARD);
					return true;
				};
				break;

			case PS_DMobjSpriteNum.SPR_BSKU:
				if (TryKey(player, 0, 2))
				{
					player.AddMessage(PS_DMessages.GOTBLUESKUL);
					return true;
				};
				break;
			
			case PS_DMobjSpriteNum.SPR_YSKU:
				if (TryKey(player, 1, 2))
				{
					player.AddMessage(PS_DMessages.GOTYELWSKUL);
					return true;
				};
				break;
			
			case PS_DMobjSpriteNum.SPR_RSKU:
				if (TryKey(player, 2, 2))
				{
					player.AddMessage(PS_DMessages.GOTREDSKULL);
					return true;
				};
				break;
		}
		
		return false;
	}
}