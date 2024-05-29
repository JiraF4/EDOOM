modded class PS_DInfo
{
	static ref array<ref PS_DMobjInfo> m_aMobjInfo;
	static ref map<int, ref PS_DMobjInfo> m_mMobjInfo;

	static void Init3()
	{
		m_aMobjInfo = {};
		m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_PLAYER
	-1,		// doomednum
	PS_DMobjStateNum.S_PLAY,		// spawnstate
	100,		// spawnhealth
	PS_DMobjStateNum.S_PLAY_RUN1,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	0,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_PLAY_PAIN,		// painstate
	255,		// painchance
	PS_EDSoundFX.sfx_plpain,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_PLAY_ATK1,		// missilestate
	PS_DMobjStateNum.S_PLAY_DIE1,		// deathstate
	PS_DMobjStateNum.S_PLAY_XDIE1,		// xdeathstate
	PS_EDSoundFX.sfx_pldeth,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	56 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_DROPOFF|PS_EDMobjFlag.MF_PICKUP|PS_EDMobjFlag.MF_NOTDMATCH,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_POSSESSED
	3004,		// doomednum
	PS_DMobjStateNum.S_POSS_STND,		// spawnstate
	20,		// spawnhealth
	PS_DMobjStateNum.S_POSS_RUN1,		// seestate
	PS_EDSoundFX.sfx_posit1,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_pistol,		// attacksound
	PS_DMobjStateNum.S_POSS_PAIN,		// painstate
	200,		// painchance
	PS_EDSoundFX.sfx_popain,		// painsound
	0,		// meleestate
	PS_DMobjStateNum.S_POSS_ATK1,		// missilestate
	PS_DMobjStateNum.S_POSS_DIE1,		// deathstate
	PS_DMobjStateNum.S_POSS_XDIE1,		// xdeathstate
	PS_EDSoundFX.sfx_podth1,		// deathsound
	8,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	56 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_posact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_POSS_RAISE1		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_SHOTGUY
	9,		// doomednum
	PS_DMobjStateNum.S_SPOS_STND,		// spawnstate
	30,		// spawnhealth
	PS_DMobjStateNum.S_SPOS_RUN1,		// seestate
	PS_EDSoundFX.sfx_posit2,		// seesound
	8,		// reactiontime
	0,		// attacksound
	PS_DMobjStateNum.S_SPOS_PAIN,		// painstate
	170,		// painchance
	PS_EDSoundFX.sfx_popain,		// painsound
	0,		// meleestate
	PS_DMobjStateNum.S_SPOS_ATK1,		// missilestate
	PS_DMobjStateNum.S_SPOS_DIE1,		// deathstate
	PS_DMobjStateNum.S_SPOS_XDIE1,		// xdeathstate
	PS_EDSoundFX.sfx_podth2,		// deathsound
	8,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	56 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_posact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_SPOS_RAISE1		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_VILE
	64,		// doomednum
	PS_DMobjStateNum.S_VILE_STND,		// spawnstate
	700,		// spawnhealth
	PS_DMobjStateNum.S_VILE_RUN1,		// seestate
	PS_EDSoundFX.sfx_vilsit,		// seesound
	8,		// reactiontime
	0,		// attacksound
	PS_DMobjStateNum.S_VILE_PAIN,		// painstate
	10,		// painchance
	PS_EDSoundFX.sfx_vipain,		// painsound
	0,		// meleestate
	PS_DMobjStateNum.S_VILE_ATK1,		// missilestate
	PS_DMobjStateNum.S_VILE_DIE1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_vildth,		// deathsound
	15,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	56 *PS_DConst.FRACUNIT,		// height
	500,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_vilact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_FIRE
	-1,		// doomednum
	PS_DMobjStateNum.S_FIRE1,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_UNDEAD
	66,		// doomednum
	PS_DMobjStateNum.S_SKEL_STND,		// spawnstate
	300,		// spawnhealth
	PS_DMobjStateNum.S_SKEL_RUN1,		// seestate
	PS_EDSoundFX.sfx_skesit,		// seesound
	8,		// reactiontime
	0,		// attacksound
	PS_DMobjStateNum.S_SKEL_PAIN,		// painstate
	100,		// painchance
	PS_EDSoundFX.sfx_popain,		// painsound
	PS_DMobjStateNum.S_SKEL_FIST1,		// meleestate
	PS_DMobjStateNum.S_SKEL_MISS1,		// missilestate
	PS_DMobjStateNum.S_SKEL_DIE1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_skedth,		// deathsound
	10,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	56 *PS_DConst.FRACUNIT,		// height
	500,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_skeact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_SKEL_RAISE1		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_TRACER
	-1,		// doomednum
	PS_DMobjStateNum.S_TRACER,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_skeatk,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_TRACEEXP1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_barexp,		// deathsound
	10 *PS_DConst.FRACUNIT,		// speed
	11 *PS_DConst.FRACUNIT,		// radius
	8 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	10,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_MISSILE|PS_EDMobjFlag.MF_DROPOFF|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_SMOKE
	-1,		// doomednum
	PS_DMobjStateNum.S_SMOKE1,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_FATSO
	67,		// doomednum
	PS_DMobjStateNum.S_FATT_STND,		// spawnstate
	600,		// spawnhealth
	PS_DMobjStateNum.S_FATT_RUN1,		// seestate
	PS_EDSoundFX.sfx_mansit,		// seesound
	8,		// reactiontime
	0,		// attacksound
	PS_DMobjStateNum.S_FATT_PAIN,		// painstate
	80,		// painchance
	PS_EDSoundFX.sfx_mnpain,		// painsound
	0,		// meleestate
	PS_DMobjStateNum.S_FATT_ATK1,		// missilestate
	PS_DMobjStateNum.S_FATT_DIE1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_mandth,		// deathsound
	8,		// speed
	48 *PS_DConst.FRACUNIT,		// radius
	64 *PS_DConst.FRACUNIT,		// height
	1000,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_posact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_FATT_RAISE1		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_FATSHOT
	-1,		// doomednum
	PS_DMobjStateNum.S_FATSHOT1,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_firsht,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_FATSHOTX1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_firxpl,		// deathsound
	20 *PS_DConst.FRACUNIT,		// speed
	6 *PS_DConst.FRACUNIT,		// radius
	8 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	8,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_MISSILE|PS_EDMobjFlag.MF_DROPOFF|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_CHAINGUY
	65,		// doomednum
	PS_DMobjStateNum.S_CPOS_STND,		// spawnstate
	70,		// spawnhealth
	PS_DMobjStateNum.S_CPOS_RUN1,		// seestate
	PS_EDSoundFX.sfx_posit2,		// seesound
	8,		// reactiontime
	0,		// attacksound
	PS_DMobjStateNum.S_CPOS_PAIN,		// painstate
	170,		// painchance
	PS_EDSoundFX.sfx_popain,		// painsound
	0,		// meleestate
	PS_DMobjStateNum.S_CPOS_ATK1,		// missilestate
	PS_DMobjStateNum.S_CPOS_DIE1,		// deathstate
	PS_DMobjStateNum.S_CPOS_XDIE1,		// xdeathstate
	PS_EDSoundFX.sfx_podth2,		// deathsound
	8,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	56 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_posact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_CPOS_RAISE1		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_TROOP
	3001,		// doomednum
	PS_DMobjStateNum.S_TROO_STND,		// spawnstate
	60,		// spawnhealth
	PS_DMobjStateNum.S_TROO_RUN1,		// seestate
	PS_EDSoundFX.sfx_bgsit1,		// seesound
	8,		// reactiontime
	0,		// attacksound
	PS_DMobjStateNum.S_TROO_PAIN,		// painstate
	200,		// painchance
	PS_EDSoundFX.sfx_popain,		// painsound
	PS_DMobjStateNum.S_TROO_ATK1,		// meleestate
	PS_DMobjStateNum.S_TROO_ATK1,		// missilestate
	PS_DMobjStateNum.S_TROO_DIE1,		// deathstate
	PS_DMobjStateNum.S_TROO_XDIE1,		// xdeathstate
	PS_EDSoundFX.sfx_bgdth1,		// deathsound
	8,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	56 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_bgact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_TROO_RAISE1		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_SERGEANT
	3002,		// doomednum
	PS_DMobjStateNum.S_SARG_STND,		// spawnstate
	150,		// spawnhealth
	PS_DMobjStateNum.S_SARG_RUN1,		// seestate
	PS_EDSoundFX.sfx_sgtsit,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_sgtatk,		// attacksound
	PS_DMobjStateNum.S_SARG_PAIN,		// painstate
	180,		// painchance
	PS_EDSoundFX.sfx_dmpain,		// painsound
	PS_DMobjStateNum.S_SARG_ATK1,		// meleestate
	0,		// missilestate
	PS_DMobjStateNum.S_SARG_DIE1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_sgtdth,		// deathsound
	10,		// speed
	30 *PS_DConst.FRACUNIT,		// radius
	56 *PS_DConst.FRACUNIT,		// height
	400,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_dmact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_SARG_RAISE1		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_SHADOWS
	58,		// doomednum
	PS_DMobjStateNum.S_SARG_STND,		// spawnstate
	150,		// spawnhealth
	PS_DMobjStateNum.S_SARG_RUN1,		// seestate
	PS_EDSoundFX.sfx_sgtsit,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_sgtatk,		// attacksound
	PS_DMobjStateNum.S_SARG_PAIN,		// painstate
	180,		// painchance
	PS_EDSoundFX.sfx_dmpain,		// painsound
	PS_DMobjStateNum.S_SARG_ATK1,		// meleestate
	0,		// missilestate
	PS_DMobjStateNum.S_SARG_DIE1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_sgtdth,		// deathsound
	10,		// speed
	30 *PS_DConst.FRACUNIT,		// radius
	56 *PS_DConst.FRACUNIT,		// height
	400,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_dmact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_SHADOW|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_SARG_RAISE1		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_HEAD
	3005,		// doomednum
	PS_DMobjStateNum.S_HEAD_STND,		// spawnstate
	400,		// spawnhealth
	PS_DMobjStateNum.S_HEAD_RUN1,		// seestate
	PS_EDSoundFX.sfx_cacsit,		// seesound
	8,		// reactiontime
	0,		// attacksound
	PS_DMobjStateNum.S_HEAD_PAIN,		// painstate
	128,		// painchance
	PS_EDSoundFX.sfx_dmpain,		// painsound
	0,		// meleestate
	PS_DMobjStateNum.S_HEAD_ATK1,		// missilestate
	PS_DMobjStateNum.S_HEAD_DIE1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_cacdth,		// deathsound
	8,		// speed
	31 *PS_DConst.FRACUNIT,		// radius
	56 *PS_DConst.FRACUNIT,		// height
	400,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_dmact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_FLOAT|PS_EDMobjFlag.MF_NOGRAVITY|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_HEAD_RAISE1		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_BRUISER
	3003,		// doomednum
	PS_DMobjStateNum.S_BOSS_STND,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_BOSS_RUN1,		// seestate
	PS_EDSoundFX.sfx_brssit,		// seesound
	8,		// reactiontime
	0,		// attacksound
	PS_DMobjStateNum.S_BOSS_PAIN,		// painstate
	50,		// painchance
	PS_EDSoundFX.sfx_dmpain,		// painsound
	PS_DMobjStateNum.S_BOSS_ATK1,		// meleestate
	PS_DMobjStateNum.S_BOSS_ATK1,		// missilestate
	PS_DMobjStateNum.S_BOSS_DIE1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_brsdth,		// deathsound
	8,		// speed
	24 *PS_DConst.FRACUNIT,		// radius
	64 *PS_DConst.FRACUNIT,		// height
	1000,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_dmact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_BOSS_RAISE1		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_BRUISERSHOT
	-1,		// doomednum
	PS_DMobjStateNum.S_BRBALL1,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_firsht,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_BRBALLX1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_firxpl,		// deathsound
	15 *PS_DConst.FRACUNIT,		// speed
	6 *PS_DConst.FRACUNIT,		// radius
	8 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	8,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_MISSILE|PS_EDMobjFlag.MF_DROPOFF|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_KNIGHT
	69,		// doomednum
	PS_DMobjStateNum.S_BOS2_STND,		// spawnstate
	500,		// spawnhealth
	PS_DMobjStateNum.S_BOS2_RUN1,		// seestate
	PS_EDSoundFX.sfx_kntsit,		// seesound
	8,		// reactiontime
	0,		// attacksound
	PS_DMobjStateNum.S_BOS2_PAIN,		// painstate
	50,		// painchance
	PS_EDSoundFX.sfx_dmpain,		// painsound
	PS_DMobjStateNum.S_BOS2_ATK1,		// meleestate
	PS_DMobjStateNum.S_BOS2_ATK1,		// missilestate
	PS_DMobjStateNum.S_BOS2_DIE1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_kntdth,		// deathsound
	8,		// speed
	24 *PS_DConst.FRACUNIT,		// radius
	64 *PS_DConst.FRACUNIT,		// height
	1000,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_dmact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_BOS2_RAISE1		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_SKULL
	3006,		// doomednum
	PS_DMobjStateNum.S_SKULL_STND,		// spawnstate
	100,		// spawnhealth
	PS_DMobjStateNum.S_SKULL_RUN1,		// seestate
	0,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_sklatk,		// attacksound
	PS_DMobjStateNum.S_SKULL_PAIN,		// painstate
	256,		// painchance
	PS_EDSoundFX.sfx_dmpain,		// painsound
	0,		// meleestate
	PS_DMobjStateNum.S_SKULL_ATK1,		// missilestate
	PS_DMobjStateNum.S_SKULL_DIE1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_firxpl,		// deathsound
	8,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	56 *PS_DConst.FRACUNIT,		// height
	50,		// mass
	3,		// damage
	PS_EDSoundFX.sfx_dmact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_FLOAT|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_SPIDER
	7,		// doomednum
	PS_DMobjStateNum.S_SPID_STND,		// spawnstate
	3000,		// spawnhealth
	PS_DMobjStateNum.S_SPID_RUN1,		// seestate
	PS_EDSoundFX.sfx_spisit,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_shotgn,		// attacksound
	PS_DMobjStateNum.S_SPID_PAIN,		// painstate
	40,		// painchance
	PS_EDSoundFX.sfx_dmpain,		// painsound
	0,		// meleestate
	PS_DMobjStateNum.S_SPID_ATK1,		// missilestate
	PS_DMobjStateNum.S_SPID_DIE1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_spidth,		// deathsound
	12,		// speed
	128 *PS_DConst.FRACUNIT,		// radius
	100 *PS_DConst.FRACUNIT,		// height
	1000,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_dmact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_BABY
	68,		// doomednum
	PS_DMobjStateNum.S_BSPI_STND,		// spawnstate
	500,		// spawnhealth
	PS_DMobjStateNum.S_BSPI_SIGHT,		// seestate
	PS_EDSoundFX.sfx_bspsit,		// seesound
	8,		// reactiontime
	0,		// attacksound
	PS_DMobjStateNum.S_BSPI_PAIN,		// painstate
	128,		// painchance
	PS_EDSoundFX.sfx_dmpain,		// painsound
	0,		// meleestate
	PS_DMobjStateNum.S_BSPI_ATK1,		// missilestate
	PS_DMobjStateNum.S_BSPI_DIE1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_bspdth,		// deathsound
	12,		// speed
	64 *PS_DConst.FRACUNIT,		// radius
	64 *PS_DConst.FRACUNIT,		// height
	600,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_bspact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_BSPI_RAISE1		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_CYBORG
	16,		// doomednum
	PS_DMobjStateNum.S_CYBER_STND,		// spawnstate
	4000,		// spawnhealth
	PS_DMobjStateNum.S_CYBER_RUN1,		// seestate
	PS_EDSoundFX.sfx_cybsit,		// seesound
	8,		// reactiontime
	0,		// attacksound
	PS_DMobjStateNum.S_CYBER_PAIN,		// painstate
	20,		// painchance
	PS_EDSoundFX.sfx_dmpain,		// painsound
	0,		// meleestate
	PS_DMobjStateNum.S_CYBER_ATK1,		// missilestate
	PS_DMobjStateNum.S_CYBER_DIE1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_cybdth,		// deathsound
	16,		// speed
	40 *PS_DConst.FRACUNIT,		// radius
	110 *PS_DConst.FRACUNIT,		// height
	1000,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_dmact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_PAIN
	71,		// doomednum
	PS_DMobjStateNum.S_PAIN_STND,		// spawnstate
	400,		// spawnhealth
	PS_DMobjStateNum.S_PAIN_RUN1,		// seestate
	PS_EDSoundFX.sfx_pesit,		// seesound
	8,		// reactiontime
	0,		// attacksound
	PS_DMobjStateNum.S_PAIN_PAIN,		// painstate
	128,		// painchance
	PS_EDSoundFX.sfx_pepain,		// painsound
	0,		// meleestate
	PS_DMobjStateNum.S_PAIN_ATK1,		// missilestate
	PS_DMobjStateNum.S_PAIN_DIE1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_pedth,		// deathsound
	8,		// speed
	31 *PS_DConst.FRACUNIT,		// radius
	56 *PS_DConst.FRACUNIT,		// height
	400,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_dmact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_FLOAT|PS_EDMobjFlag.MF_NOGRAVITY|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_PAIN_RAISE1		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_WOLFSS
	84,		// doomednum
	PS_DMobjStateNum.S_SSWV_STND,		// spawnstate
	50,		// spawnhealth
	PS_DMobjStateNum.S_SSWV_RUN1,		// seestate
	PS_EDSoundFX.sfx_sssit,		// seesound
	8,		// reactiontime
	0,		// attacksound
	PS_DMobjStateNum.S_SSWV_PAIN,		// painstate
	170,		// painchance
	PS_EDSoundFX.sfx_popain,		// painsound
	0,		// meleestate
	PS_DMobjStateNum.S_SSWV_ATK1,		// missilestate
	PS_DMobjStateNum.S_SSWV_DIE1,		// deathstate
	PS_DMobjStateNum.S_SSWV_XDIE1,		// xdeathstate
	PS_EDSoundFX.sfx_ssdth,		// deathsound
	8,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	56 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_posact,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_SSWV_RAISE1		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_KEEN
	72,		// doomednum
	PS_DMobjStateNum.S_KEENSTND,		// spawnstate
	100,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_KEENPAIN,		// painstate
	256,		// painchance
	PS_EDSoundFX.sfx_keenpn,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_COMMKEEN,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_keendt,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	72 *PS_DConst.FRACUNIT,		// height
	10000000,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_COUNTKILL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_BOSSBRAIN
	88,		// doomednum
	PS_DMobjStateNum.S_BRAIN,		// spawnstate
	250,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_BRAIN_PAIN,		// painstate
	255,		// painchance
	PS_EDSoundFX.sfx_bospn,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_BRAIN_DIE1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_bosdth,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	10000000,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_BOSSSPIT
	89,		// doomednum
	PS_DMobjStateNum.S_BRAINEYE,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_BRAINEYESEE,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	32 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_NOSECTOR,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_BOSSTARGET
	87,		// doomednum
	PS_DMobjStateNum.S_NULL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	32 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_NOSECTOR,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_SPAWNSHOT
	-1,		// doomednum
	PS_DMobjStateNum.S_SPAWN1,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_bospit,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_firxpl,		// deathsound
	10 *PS_DConst.FRACUNIT,		// speed
	6 *PS_DConst.FRACUNIT,		// radius
	32 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	3,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_MISSILE|PS_EDMobjFlag.MF_DROPOFF|PS_EDMobjFlag.MF_NOGRAVITY|PS_EDMobjFlag.MF_NOCLIP,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_SPAWNFIRE
	-1,		// doomednum
	PS_DMobjStateNum.S_SPAWNFIRE1,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_BARREL
	2035,		// doomednum
	PS_DMobjStateNum.S_BAR1,		// spawnstate
	20,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_BEXP,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_barexp,		// deathsound
	0,		// speed
	10 *PS_DConst.FRACUNIT,		// radius
	42 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SHOOTABLE|PS_EDMobjFlag.MF_NOBLOOD,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_TROOPSHOT
	-1,		// doomednum
	PS_DMobjStateNum.S_TBALL1,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_firsht,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_TBALLX1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_firxpl,		// deathsound
	10 *PS_DConst.FRACUNIT,		// speed
	6 *PS_DConst.FRACUNIT,		// radius
	8 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	3,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_MISSILE|PS_EDMobjFlag.MF_DROPOFF|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_HEADSHOT
	-1,		// doomednum
	PS_DMobjStateNum.S_RBALL1,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_firsht,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_RBALLX1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_firxpl,		// deathsound
	10 *PS_DConst.FRACUNIT,		// speed
	6 *PS_DConst.FRACUNIT,		// radius
	8 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	5,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_MISSILE|PS_EDMobjFlag.MF_DROPOFF|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_ROCKET
	-1,		// doomednum
	PS_DMobjStateNum.S_ROCKET,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_rlaunc,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_EXPLODE1,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_barexp,		// deathsound
	20 *PS_DConst.FRACUNIT,		// speed
	11 *PS_DConst.FRACUNIT,		// radius
	8 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	20,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_MISSILE|PS_EDMobjFlag.MF_DROPOFF|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_PLASMA
	-1,		// doomednum
	PS_DMobjStateNum.S_PLASBALL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_plasma,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_PLASEXP,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_firxpl,		// deathsound
	25 *PS_DConst.FRACUNIT,		// speed
	13 *PS_DConst.FRACUNIT,		// radius
	8 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	5,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_MISSILE|PS_EDMobjFlag.MF_DROPOFF|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_BFG
	-1,		// doomednum
	PS_DMobjStateNum.S_BFGSHOT,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	0,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_BFGLAND,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_rxplod,		// deathsound
	25 *PS_DConst.FRACUNIT,		// speed
	13 *PS_DConst.FRACUNIT,		// radius
	8 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	100,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_MISSILE|PS_EDMobjFlag.MF_DROPOFF|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_ARACHPLAZ
	-1,		// doomednum
	PS_DMobjStateNum.S_ARACH_PLAZ,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_plasma,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_ARACH_PLEX,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_firxpl,		// deathsound
	25 *PS_DConst.FRACUNIT,		// speed
	13 *PS_DConst.FRACUNIT,		// radius
	8 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	5,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_MISSILE|PS_EDMobjFlag.MF_DROPOFF|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_PUFF
	-1,		// doomednum
	PS_DMobjStateNum.S_PUFF1,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_BLOOD
	-1,		// doomednum
	PS_DMobjStateNum.S_BLOOD1,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_TFOG
	-1,		// doomednum
	PS_DMobjStateNum.S_TFOG,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_IFOG
	-1,		// doomednum
	PS_DMobjStateNum.S_IFOG,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_TELEPORTMAN
	14,		// doomednum
	PS_DMobjStateNum.S_NULL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_NOSECTOR,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_EXTRABFG
	-1,		// doomednum
	PS_DMobjStateNum.S_BFGEXP,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC0
	2018,		// doomednum
	PS_DMobjStateNum.S_ARM1,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC1
	2019,		// doomednum
	PS_DMobjStateNum.S_ARM2,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC2
	2014,		// doomednum
	PS_DMobjStateNum.S_BON1,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL|PS_EDMobjFlag.MF_COUNTITEM,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC3
	2015,		// doomednum
	PS_DMobjStateNum.S_BON2,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL|PS_EDMobjFlag.MF_COUNTITEM,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC4
	5,		// doomednum
	PS_DMobjStateNum.S_BKEY,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL|PS_EDMobjFlag.MF_NOTDMATCH,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC5
	13,		// doomednum
	PS_DMobjStateNum.S_RKEY,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL|PS_EDMobjFlag.MF_NOTDMATCH,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC6
	6,		// doomednum
	PS_DMobjStateNum.S_YKEY,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL|PS_EDMobjFlag.MF_NOTDMATCH,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC7
	39,		// doomednum
	PS_DMobjStateNum.S_YSKULL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL|PS_EDMobjFlag.MF_NOTDMATCH,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC8
	38,		// doomednum
	PS_DMobjStateNum.S_RSKULL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL|PS_EDMobjFlag.MF_NOTDMATCH,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC9
	40,		// doomednum
	PS_DMobjStateNum.S_BSKULL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL|PS_EDMobjFlag.MF_NOTDMATCH,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC10
	2011,		// doomednum
	PS_DMobjStateNum.S_STIM,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC11
	2012,		// doomednum
	PS_DMobjStateNum.S_MEDI,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC12
	2013,		// doomednum
	PS_DMobjStateNum.S_SOUL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL|PS_EDMobjFlag.MF_COUNTITEM,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_INV
	2022,		// doomednum
	PS_DMobjStateNum.S_PINV,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL|PS_EDMobjFlag.MF_COUNTITEM,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC13
	2023,		// doomednum
	PS_DMobjStateNum.S_PSTR,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL|PS_EDMobjFlag.MF_COUNTITEM,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_INS
	2024,		// doomednum
	PS_DMobjStateNum.S_PINS,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL|PS_EDMobjFlag.MF_COUNTITEM,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC14
	2025,		// doomednum
	PS_DMobjStateNum.S_SUIT,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC15
	2026,		// doomednum
	PS_DMobjStateNum.S_PMAP,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL|PS_EDMobjFlag.MF_COUNTITEM,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

		Init4();
	}

	// Another crush
	static void Init4()
	{
	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC16
	2045,		// doomednum
	PS_DMobjStateNum.S_PVIS,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL|PS_EDMobjFlag.MF_COUNTITEM,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MEGA
	83,		// doomednum
	PS_DMobjStateNum.S_MEGA,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL|PS_EDMobjFlag.MF_COUNTITEM,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_CLIP
	2007,		// doomednum
	PS_DMobjStateNum.S_CLIP,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC17
	2048,		// doomednum
	PS_DMobjStateNum.S_AMMO,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC18
	2010,		// doomednum
	PS_DMobjStateNum.S_ROCK,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC19
	2046,		// doomednum
	PS_DMobjStateNum.S_BROK,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC20
	2047,		// doomednum
	PS_DMobjStateNum.S_CELL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC21
	17,		// doomednum
	PS_DMobjStateNum.S_CELP,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC22
	2008,		// doomednum
	PS_DMobjStateNum.S_SHEL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC23
	2049,		// doomednum
	PS_DMobjStateNum.S_SBOX,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC24
	8,		// doomednum
	PS_DMobjStateNum.S_BPAK,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC25
	2006,		// doomednum
	PS_DMobjStateNum.S_BFUG,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_CHAINGUN
	2002,		// doomednum
	PS_DMobjStateNum.S_MGUN,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC26
	2005,		// doomednum
	PS_DMobjStateNum.S_CSAW,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC27
	2003,		// doomednum
	PS_DMobjStateNum.S_LAUN,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC28
	2004,		// doomednum
	PS_DMobjStateNum.S_PLAS,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_SHOTGUN
	2001,		// doomednum
	PS_DMobjStateNum.S_SHOT,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_SUPERSHOTGUN
	82,		// doomednum
	PS_DMobjStateNum.S_SHOT2,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPECIAL,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC29
	85,		// doomednum
	PS_DMobjStateNum.S_TECHLAMP,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC30
	86,		// doomednum
	PS_DMobjStateNum.S_TECH2LAMP,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC31
	2028,		// doomednum
	PS_DMobjStateNum.S_COLU,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC32
	30,		// doomednum
	PS_DMobjStateNum.S_TALLGRNCOL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC33
	31,		// doomednum
	PS_DMobjStateNum.S_SHRTGRNCOL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC34
	32,		// doomednum
	PS_DMobjStateNum.S_TALLREDCOL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC35
	33,		// doomednum
	PS_DMobjStateNum.S_SHRTREDCOL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC36
	37,		// doomednum
	PS_DMobjStateNum.S_SKULLCOL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC37
	36,		// doomednum
	PS_DMobjStateNum.S_HEARTCOL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC38
	41,		// doomednum
	PS_DMobjStateNum.S_EVILEYE,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC39
	42,		// doomednum
	PS_DMobjStateNum.S_FLOATSKULL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC40
	43,		// doomednum
	PS_DMobjStateNum.S_TORCHTREE,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC41
	44,		// doomednum
	PS_DMobjStateNum.S_BLUETORCH,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC42
	45,		// doomednum
	PS_DMobjStateNum.S_GREENTORCH,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC43
	46,		// doomednum
	PS_DMobjStateNum.S_REDTORCH,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC44
	55,		// doomednum
	PS_DMobjStateNum.S_BTORCHSHRT,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC45
	56,		// doomednum
	PS_DMobjStateNum.S_GTORCHSHRT,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC46
	57,		// doomednum
	PS_DMobjStateNum.S_RTORCHSHRT,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC47
	47,		// doomednum
	PS_DMobjStateNum.S_STALAGTITE,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC48
	48,		// doomednum
	PS_DMobjStateNum.S_TECHPILLAR,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC49
	34,		// doomednum
	PS_DMobjStateNum.S_CANDLESTIK,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	0,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC50
	35,		// doomednum
	PS_DMobjStateNum.S_CANDELABRA,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC51
	49,		// doomednum
	PS_DMobjStateNum.S_BLOODYTWITCH,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	68 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC52
	50,		// doomednum
	PS_DMobjStateNum.S_MEAT2,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	84 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC53
	51,		// doomednum
	PS_DMobjStateNum.S_MEAT3,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	84 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC54
	52,		// doomednum
	PS_DMobjStateNum.S_MEAT4,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	68 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC55
	53,		// doomednum
	PS_DMobjStateNum.S_MEAT5,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	52 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC56
	59,		// doomednum
	PS_DMobjStateNum.S_MEAT2,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	84 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC57
	60,		// doomednum
	PS_DMobjStateNum.S_MEAT4,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	68 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC58
	61,		// doomednum
	PS_DMobjStateNum.S_MEAT3,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	52 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC59
	62,		// doomednum
	PS_DMobjStateNum.S_MEAT5,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	52 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC60
	63,		// doomednum
	PS_DMobjStateNum.S_BLOODYTWITCH,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	68 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC61
	22,		// doomednum
	PS_DMobjStateNum.S_HEAD_DIE6,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	0,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC62
	15,		// doomednum
	PS_DMobjStateNum.S_PLAY_DIE7,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	0,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC63
	18,		// doomednum
	PS_DMobjStateNum.S_POSS_DIE5,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	0,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC64
	21,		// doomednum
	PS_DMobjStateNum.S_SARG_DIE6,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	0,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC65
	23,		// doomednum
	PS_DMobjStateNum.S_SKULL_DIE6,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	0,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC66
	20,		// doomednum
	PS_DMobjStateNum.S_TROO_DIE5,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	0,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC67
	19,		// doomednum
	PS_DMobjStateNum.S_SPOS_DIE5,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	0,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC68
	10,		// doomednum
	PS_DMobjStateNum.S_PLAY_XDIE9,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	0,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC69
	12,		// doomednum
	PS_DMobjStateNum.S_PLAY_XDIE9,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	0,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC70
	28,		// doomednum
	PS_DMobjStateNum.S_HEADSONSTICK,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC71
	24,		// doomednum
	PS_DMobjStateNum.S_GIBS,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	0,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC72
	27,		// doomednum
	PS_DMobjStateNum.S_HEADONASTICK,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC73
	29,		// doomednum
	PS_DMobjStateNum.S_HEADCANDLES,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC74
	25,		// doomednum
	PS_DMobjStateNum.S_DEADSTICK,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC75
	26,		// doomednum
	PS_DMobjStateNum.S_LIVESTICK,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC76
	54,		// doomednum
	PS_DMobjStateNum.S_BIGTREE,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	32 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC77
	70,		// doomednum
	PS_DMobjStateNum.S_BBAR1,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC78
	73,		// doomednum
	PS_DMobjStateNum.S_HANGNOGUTS,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	88 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC79
	74,		// doomednum
	PS_DMobjStateNum.S_HANGBNOBRAIN,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	88 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC80
	75,		// doomednum
	PS_DMobjStateNum.S_HANGTLOOKDN,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	64 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC81
	76,		// doomednum
	PS_DMobjStateNum.S_HANGTSKULL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	64 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC82
	77,		// doomednum
	PS_DMobjStateNum.S_HANGTLOOKUP,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	64 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC83
	78,		// doomednum
	PS_DMobjStateNum.S_HANGTNOBRAIN,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	16 *PS_DConst.FRACUNIT,		// radius
	64 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_SOLID|PS_EDMobjFlag.MF_SPAWNCEILING|PS_EDMobjFlag.MF_NOGRAVITY,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC84
	79,		// doomednum
	PS_DMobjStateNum.S_COLONGIBS,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC85
	80,		// doomednum
	PS_DMobjStateNum.S_SMALLPOOL,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));

	m_aMobjInfo.Insert(new PS_DMobjInfo({	// MT_MISC86
	81,		// doomednum
	PS_DMobjStateNum.S_BRAINSTEM,		// spawnstate
	1000,		// spawnhealth
	PS_DMobjStateNum.S_NULL,		// seestate
	PS_EDSoundFX.sfx_None,		// seesound
	8,		// reactiontime
	PS_EDSoundFX.sfx_None,		// attacksound
	PS_DMobjStateNum.S_NULL,		// painstate
	0,		// painchance
	PS_EDSoundFX.sfx_None,		// painsound
	PS_DMobjStateNum.S_NULL,		// meleestate
	PS_DMobjStateNum.S_NULL,		// missilestate
	PS_DMobjStateNum.S_NULL,		// deathstate
	PS_DMobjStateNum.S_NULL,		// xdeathstate
	PS_EDSoundFX.sfx_None,		// deathsound
	0,		// speed
	20 *PS_DConst.FRACUNIT,		// radius
	16 *PS_DConst.FRACUNIT,		// height
	100,		// mass
	0,		// damage
	PS_EDSoundFX.sfx_None,		// activesound
	PS_EDMobjFlag.MF_NOBLOCKMAP,		// flags
	PS_DMobjStateNum.S_NULL		// raisestate
	}));
		InitMap();
	};
	
	static void InitMap()
	{
		m_mMobjInfo = new map<int, ref PS_DMobjInfo>();
		foreach (PS_DMobjInfo info : m_aMobjInfo)
		{
			m_mMobjInfo.Insert(info.m_iDoomedNum, info);
		}
	}
	
}
