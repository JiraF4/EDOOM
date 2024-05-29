enum PS_EDSoundFX
{
    sfx_None,
    sfx_pistol,
    sfx_shotgn,
    sfx_sgcock,
    sfx_dshtgn,
    sfx_dbopn,
    sfx_dbcls,
    sfx_dbload,
    sfx_plasma,
    sfx_bfg,
    sfx_sawup,
    sfx_sawidl,
    sfx_sawful,
    sfx_sawhit,
    sfx_rlaunc,
    sfx_rxplod,
    sfx_firsht,
    sfx_firxpl,
    sfx_pstart,
    sfx_pstop,
    sfx_doropn,
    sfx_dorcls,
    sfx_stnmov,
    sfx_swtchn,
    sfx_swtchx,
    sfx_plpain,
    sfx_dmpain,
    sfx_popain,
    sfx_vipain,
    sfx_mnpain,
    sfx_pepain,
    sfx_slop,
    sfx_itemup,
    sfx_wpnup,
    sfx_oof,
    sfx_telept,
    sfx_posit1,
    sfx_posit2,
    sfx_posit3,
    sfx_bgsit1,
    sfx_bgsit2,
    sfx_sgtsit,
    sfx_cacsit,
    sfx_brssit,
    sfx_cybsit,
    sfx_spisit,
    sfx_bspsit,
    sfx_kntsit,
    sfx_vilsit,
    sfx_mansit,
    sfx_pesit,
    sfx_sklatk,
    sfx_sgtatk,
    sfx_skepch,
    sfx_vilatk,
    sfx_claw,
    sfx_skeswg,
    sfx_pldeth,
    sfx_pdiehi,
    sfx_podth1,
    sfx_podth2,
    sfx_podth3,
    sfx_bgdth1,
    sfx_bgdth2,
    sfx_sgtdth,
    sfx_cacdth,
    sfx_skldth,
    sfx_brsdth,
    sfx_cybdth,
    sfx_spidth,
    sfx_bspdth,
    sfx_vildth,
    sfx_kntdth,
    sfx_pedth,
    sfx_skedth,
    sfx_posact,
    sfx_bgact,
    sfx_dmact,
    sfx_bspact,
    sfx_bspwlk,
    sfx_vilact,
    sfx_noway,
    sfx_barexp,
    sfx_punch,
    sfx_hoof,
    sfx_metal,
    sfx_chgun,
    sfx_tink,
    sfx_bdopn,
    sfx_bdcls,
    sfx_itmbk,
    sfx_flame,
    sfx_flamst,
    sfx_getpow,
    sfx_bospit,
    sfx_boscub,
    sfx_bossit,
    sfx_bospn,
    sfx_bosdth,
    sfx_manatk,
    sfx_mandth,
    sfx_sssit,
    sfx_ssdth,
    sfx_keenpn,
    sfx_keendt,
    sfx_skeact,
    sfx_skesit,
    sfx_skeatk,
    sfx_radio,
    NUMSFX
};

class PS_DMusicEffect
{
	static AudioHandle m_MusicAudioHandle;
	static bool m_bRepeat;
	static string m_sName;
	static float m_fDelay;
	
	static ref array<float> m_aTimes = {
		95,
		154,
		274,
		169,
		163,
		84,
		149,
		151,
		135
	};
	
	static void Reset()
	{
		AudioSystem.TerminateSound(m_MusicAudioHandle);
		m_sName = "";
		m_bRepeat = false;
	}
	
	static void Update(float timeSlice)
	{
		if (m_bRepeat)
		{
			m_fDelay -= timeSlice;
			if (m_fDelay <= 0)
			{
				Play(m_sName, m_bRepeat);
			}
		}
	}
	
	static void Play(string name, int time = -1)
	{
		m_sName = name;
		
		if (time >= 0)
		{
			m_fDelay = m_aTimes[time];
			m_bRepeat = true;
		}
		else
			m_bRepeat = false;
		AudioSystem.TerminateSound(m_MusicAudioHandle);
		string filePath = "$profile:DE/Music/D_" + m_sName + ".wav";
		m_MusicAudioHandle = AudioSystem.PlaySound(filePath);
	}
}

class PS_DSoundEffect
{
	string m_sName;
	int m_iSingularity;
	int m_iPriority;
	int m_iLink; // ...
	int m_iPitch;
	int m_iVolume;
	string m_sSoundFile;
	AudioHandle m_AudioHandle;
	
	static PS_DEntityPlayer s_Player;
	
	void PS_DSoundEffect(
		string name,
		int singularity,
		int priority,
		int link,
		int pitch,
		int volume,
		int data
	)
	{
		m_sName = name;
		m_sSoundFile = "$profile:DE/Sounds/DS" + name + ".wav";
		m_iSingularity = singularity;
	}
	
	static void PlaySound(PS_EDSoundFX sfx, vector position)
	{
		vector vectorToPlayer = s_Player.m_vPosition - position;
		vectorToPlayer = PS_Math2D.Rotate(vectorToPlayer, -s_Player.m_fAngle);
		
		PS_DSoundEffect soundEffect = PS_DSoundEffect.SOUND_EFFECTS[sfx];
		soundEffect.Play(vectorToPlayer);
	}
	
	void Play(vector vectorToPlayer)
	{
		// Always doesn't played...
		if (m_iSingularity && AudioSystem.IsSoundPlayed(m_AudioHandle))
			return;
		
		m_AudioHandle = AudioSystem.PlaySound(m_sSoundFile);
		/* impossible to use
		AudioHandle audioHandle = AudioSystem.PlaySound(m_sSoundFile);
		vector mat[4];
		mat[0] = "0 0 0";
		mat[1] = "0 0 0";
		mat[2] = "0 0 0";
		mat[3] = "0 0 0";
		AudioSystem.SetSoundTransformation(audioHandle, mat);
		AudioSystem.SetBoundingVolumeParams(audioHandle, AudioSystem.BV_Cylinder, 10, 10, 0);
		*/
	}
	
	static const ref array<ref PS_DSoundEffect> SOUND_EFFECTS = {
		// S_sfx[0] needs to be a dummy for odd reasons.
	  new PS_DSoundEffect( "none", false,  0, 0, -1, -1, 0 ),
	
	  new PS_DSoundEffect( "pistol", false, 64, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "shotgn", false, 64, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "sgcock", false, 64, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "dshtgn", false, 64, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "dbopn", false, 64, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "dbcls", false, 64, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "dbload", false, 64, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "plasma", false, 64, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "bfg", false, 64, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "sawup", false, 64, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "sawidl", false, 118, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "sawful", false, 64, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "sawhit", false, 64, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "rlaunc", false, 64, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "rxplod", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "firsht", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "firxpl", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "pstart", false, 100, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "pstop", false, 100, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "doropn", false, 100, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "dorcls", false, 100, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "stnmov", false, 119, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "swtchn", false, 78, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "swtchx", false, 78, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "plpain", false, 96, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "dmpain", false, 96, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "popain", false, 96, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "vipain", false, 96, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "mnpain", false, 96, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "pepain", false, 96, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "slop", false, 78, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "itemup", true, 78, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "wpnup", true, 78, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "oof", false, 96, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "telept", false, 32, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "posit1", true, 98, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "posit2", true, 98, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "posit3", true, 98, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "bgsit1", true, 98, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "bgsit2", true, 98, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "sgtsit", true, 98, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "cacsit", true, 98, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "brssit", true, 94, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "cybsit", true, 92, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "spisit", true, 90, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "bspsit", true, 90, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "kntsit", true, 90, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "vilsit", true, 90, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "mansit", true, 90, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "pesit", true, 90, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "sklatk", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "sgtatk", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "skepch", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "vilatk", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "claw", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "skeswg", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "pldeth", false, 32, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "pdiehi", false, 32, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "podth1", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "podth2", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "podth3", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "bgdth1", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "bgdth2", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "sgtdth", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "cacdth", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "skldth", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "brsdth", false, 32, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "cybdth", false, 32, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "spidth", false, 32, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "bspdth", false, 32, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "vildth", false, 32, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "kntdth", false, 32, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "pedth", false, 32, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "skedth", false, 32, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "posact", true, 120, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "bgact", true, 120, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "dmact", true, 120, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "bspact", true, 100, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "bspwlk", true, 100, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "vilact", true, 100, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "noway", false, 78, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "barexp", false, 60, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "punch", false, 64, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "hoof", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "metal", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "chgun", false, 64, 0, 150, 0, 0 ),
	  new PS_DSoundEffect( "tink", false, 60, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "bdopn", false, 100, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "bdcls", false, 100, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "itmbk", false, 100, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "flame", false, 32, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "flamst", false, 32, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "getpow", false, 60, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "bospit", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "boscub", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "bossit", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "bospn", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "bosdth", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "manatk", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "mandth", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "sssit", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "ssdth", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "keenpn", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "keendt", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "skeact", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "skesit", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "skeatk", false, 70, 0, -1, -1, 0 ),
	  new PS_DSoundEffect( "radio", false, 60, 0, -1, -1, 0 ) 
	}
}

















