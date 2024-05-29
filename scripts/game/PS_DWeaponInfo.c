enum PS_EDAmmoType
{
	 am_clip,	// Pistol / chaingun ammo.
    am_shell,	// Shotgun / double barreled shotgun.
    am_cell,	// Plasma rifle, BFG.
    am_misl,	// Missile launcher.
    NUMAMMO,
    am_noammo	// Unlimited for chainsaw / fist.	
}

enum PS_EDWeaponType
{
	 wp_fist,
    wp_pistol,
    wp_shotgun,
    wp_chaingun,
    wp_missile,
    wp_plasma,
    wp_bfg,
    wp_chainsaw,
    wp_supershotgun,

    NUMWEAPONS,
    
    // No pending weapon change.
    wp_nochange
}

class PS_DWeaponInfo
{
	static int s_iId;
	int m_iId;
	
	PS_EDAmmoType m_iAmmoType;
	PS_DMobjStateNum m_iUpState;
	PS_DMobjStateNum m_iDownState;
	PS_DMobjStateNum m_iReadyState;
	PS_DMobjStateNum m_iAtkState;
	PS_DMobjStateNum m_iFlashState;
	
	ref array<PS_DPatch> m_FramePatches = {};
	
	void PS_DWeaponInfo(
		PS_EDAmmoType ammoType,
		PS_DMobjStateNum upstate,
		PS_DMobjStateNum downstate,
		PS_DMobjStateNum readystate,
		PS_DMobjStateNum atkstate,
		PS_DMobjStateNum flashstate,
	)
	{
		m_iAmmoType = ammoType;
		m_iUpState = upstate;
		m_iDownState = downstate;
		m_iReadyState = readystate;
		m_iAtkState = atkstate;
		m_iFlashState = flashstate;
	}
	
	static ref array<ref PS_DWeaponInfo> m_aWeaponInfo;
	
	static void Init(PS_DAssets dAssets)
	{
		s_iId = 0;
		
		SetWeapons();
		
		foreach (PS_DWeaponInfo weaponInfo : m_aWeaponInfo)
		{
			weaponInfo.m_iId = s_iId;
			s_iId++;
			PS_DMobjState state = PS_DInfo.m_aMobjStates[weaponInfo.m_iUpState];
			string spryteName = PS_DInfo.SPRITE_NAMES[state.m_SpriteNum];
			string spryteNameNum = spryteName + "A0";
			int i = 1;
			while (dAssets.m_mPatches.Contains(spryteNameNum))
			{
				PS_DPatch patch = dAssets.m_mPatches[spryteNameNum];
				weaponInfo.m_FramePatches.Insert(patch);
				spryteNameNum = spryteName + SCR_StringHelper.UPPERCASE[i] + "0";
				i++;
			}
		}
	}
	
	static void SetWeapons()
	{
	 	m_aWeaponInfo = {
	    new PS_DWeaponInfo(
		// fist
		  PS_EDAmmoType.am_noammo,
		PS_DMobjStateNum.S_PUNCHUP,
		PS_DMobjStateNum.S_PUNCHDOWN,
		PS_DMobjStateNum.S_PUNCH,
		PS_DMobjStateNum.S_PUNCH1,
		PS_DMobjStateNum.S_NULL
	    ),	
	    new PS_DWeaponInfo(
		// pistol
		  PS_EDAmmoType.am_clip,
		PS_DMobjStateNum.S_PISTOLUP,
		PS_DMobjStateNum.S_PISTOLDOWN,
		PS_DMobjStateNum.S_PISTOL,
		PS_DMobjStateNum.S_PISTOL1,
		PS_DMobjStateNum.S_PISTOLFLASH
	    ),	
	    new PS_DWeaponInfo(
		// shotgun
		  PS_EDAmmoType.am_shell,
		PS_DMobjStateNum.S_SGUNUP,
		PS_DMobjStateNum.S_SGUNDOWN,
		PS_DMobjStateNum.S_SGUN,
		PS_DMobjStateNum.S_SGUN1,
		PS_DMobjStateNum.S_SGUNFLASH1
	    ),
	    new PS_DWeaponInfo(
		// chaingun
		  PS_EDAmmoType.am_clip,
		PS_DMobjStateNum.S_CHAINUP,
		PS_DMobjStateNum.S_CHAINDOWN,
		PS_DMobjStateNum.S_CHAIN,
		PS_DMobjStateNum.S_CHAIN1,
		PS_DMobjStateNum.S_CHAINFLASH1
	    ),
	    new PS_DWeaponInfo(
		// missile launcher
		  PS_EDAmmoType.am_misl,
		PS_DMobjStateNum.S_MISSILEUP,
		PS_DMobjStateNum.S_MISSILEDOWN,
		PS_DMobjStateNum.S_MISSILE,
		PS_DMobjStateNum.S_MISSILE1,
		PS_DMobjStateNum.S_MISSILEFLASH1
	    ),
	    new PS_DWeaponInfo(
		// plasma rifle
		  PS_EDAmmoType.am_cell,
		PS_DMobjStateNum.S_PLASMAUP,
		PS_DMobjStateNum.S_PLASMADOWN,
		PS_DMobjStateNum.S_PLASMA,
		PS_DMobjStateNum.S_PLASMA1,
		PS_DMobjStateNum.S_PLASMAFLASH1
	    ),
	    new PS_DWeaponInfo(
		// bfg 9000
		  PS_EDAmmoType.am_cell,
		PS_DMobjStateNum.S_BFGUP,
		PS_DMobjStateNum.S_BFGDOWN,
		PS_DMobjStateNum.S_BFG,
		PS_DMobjStateNum.S_BFG1,
		PS_DMobjStateNum.S_BFGFLASH1
	    ),
	    new PS_DWeaponInfo(
		// chainsaw
		  PS_EDAmmoType.am_noammo,
		PS_DMobjStateNum.S_SAWUP,
		PS_DMobjStateNum.S_SAWDOWN,
		PS_DMobjStateNum.S_SAW,
		PS_DMobjStateNum.S_SAW1,
		PS_DMobjStateNum.S_NULL
	    ),
	    new PS_DWeaponInfo(
		// super shotgun
		  PS_EDAmmoType.am_shell,
		PS_DMobjStateNum.S_DSGUNUP,
		PS_DMobjStateNum.S_DSGUNDOWN,
		PS_DMobjStateNum.S_DSGUN,
		PS_DMobjStateNum.S_DSGUN1,
		PS_DMobjStateNum.S_DSGUNFLASH1
	    )
		};
	}
}

