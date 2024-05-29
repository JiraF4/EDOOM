class PS_DIntermission
{
	PS_DMain m_DMain;
	PS_DAssets m_DAssets;
	PS_DMap m_DMap;
	
	PS_DPatch m_WINMAP;
	
	static const ref array<ref array<ref array<int>>> LOCATIONS =
	{
	    // Episode 0 World Map
	    {
		{ 185, 164 },	// location of level 0 (CJ)
		{ 148, 143 },	// location of level 1 (CJ)
		{ 69, 122 },	// location of level 2 (CJ)
		{ 209, 102 },	// location of level 3 (CJ)
		{ 116, 89 },	// location of level 4 (CJ)
		{ 166, 55 },	// location of level 5 (CJ)
		{ 71, 56 },	// location of level 6 (CJ)
		{ 135, 29 },	// location of level 7 (CJ)
		{ 71, 24 }	// location of level 8 (CJ)
	    },
	
	    // Episode 1 World Map should go here
	    {
		{ 254, 25 },	// location of level 0 (CJ)
		{ 97, 50 },	// location of level 1 (CJ)
		{ 188, 64 },	// location of level 2 (CJ)
		{ 128, 78 },	// location of level 3 (CJ)
		{ 214, 92 },	// location of level 4 (CJ)
		{ 133, 130 },	// location of level 5 (CJ)
		{ 208, 136 },	// location of level 6 (CJ)
		{ 148, 140 },	// location of level 7 (CJ)
		{ 235, 158 }	// location of level 8 (CJ)
	    },
	
	    // Episode 2 World Map should go here
	    {
		{ 156, 168 },	// location of level 0 (CJ)
		{ 48, 154 },	// location of level 1 (CJ)
		{ 174, 95 },	// location of level 2 (CJ)
		{ 265, 75 },	// location of level 3 (CJ)
		{ 130, 48 },	// location of level 4 (CJ)
		{ 279, 23 },	// location of level 5 (CJ)
		{ 198, 48 },	// location of level 6 (CJ)
		{ 140, 25 },	// location of level 7 (CJ)
		{ 281, 136 }	// location of level 8 (CJ)
	    }
	};
	
	ref array<PS_DPatch> m_aLevelPatches = {};
	
	static const bool ANIM_ALWAYS = true;
	const static ref array<ref PS_DIntermissionAnimation> EP0AMIS =
	{
	    new PS_DIntermissionAnimation( ANIM_ALWAYS, PS_DConst.TICRATE/3, 3, { 224, 104 } ),
	    new PS_DIntermissionAnimation( ANIM_ALWAYS, PS_DConst.TICRATE/3, 3, { 184, 160 } ),
	    new PS_DIntermissionAnimation( ANIM_ALWAYS, PS_DConst.TICRATE/3, 3, { 112, 136 } ),
	    new PS_DIntermissionAnimation( ANIM_ALWAYS, PS_DConst.TICRATE/3, 3, { 72, 112 } ),
	    new PS_DIntermissionAnimation( ANIM_ALWAYS, PS_DConst.TICRATE/3, 3, { 88, 96 } ),
	    new PS_DIntermissionAnimation( ANIM_ALWAYS, PS_DConst.TICRATE/3, 3, { 64, 48 } ),
	    new PS_DIntermissionAnimation( ANIM_ALWAYS, PS_DConst.TICRATE/3, 3, { 192, 40 } ),
	    new PS_DIntermissionAnimation( ANIM_ALWAYS, PS_DConst.TICRATE/3, 3, { 136, 16 } ),
	    new PS_DIntermissionAnimation( ANIM_ALWAYS, PS_DConst.TICRATE/3, 3, { 80, 16 } ),
	    new PS_DIntermissionAnimation( ANIM_ALWAYS, PS_DConst.TICRATE/3, 3, { 64, 24 } )
	};
	
	PS_DPatch m_WIF;
	PS_DPatch m_WISPLAT;
	PS_DPatch m_WIOSTK;
	PS_DPatch m_WIOSTI;
	PS_DPatch m_WIMSTT;
	PS_DPatch m_WISCRT2;
	PS_DPatch m_WITIME;
	PS_DPatch m_WIENTER;
	ref array<PS_DPatch> m_aWINUMs = {};
	
	PS_DPatch m_WIURH0;
	PS_DPatch m_WIURH1;
	
	void PS_DIntermission(PS_DMain dMain, PS_DAssets dAssets)
	{
		m_DMain = dMain;
		m_DAssets = dAssets;
		
		m_WINMAP = dAssets.m_mPatches["WIMAP0"];
		
		// Link animations
		int i = 0;
		foreach (PS_DIntermissionAnimation animation : EP0AMIS)
		{
			animation.m_aPatches = {};
			int f = 0;
			string patchName = "WIA" + i.ToString(3) + f.ToString(2);
			while (m_DAssets.m_mPatches.Contains(patchName))
			{
				animation.m_aPatches.Insert(m_DAssets.m_mPatches[patchName]);
				f++;
				patchName = "WIA" + i.ToString(3) + f.ToString(2);
			}
			i++;
		}
		
		// Link level names
		i = 0;
		string patchName = "WILV" + i.ToString(2);
		while (m_DAssets.m_mPatches.Contains(patchName))
		{
			m_aLevelPatches.Insert(m_DAssets.m_mPatches[patchName]);
			i++;
			patchName = "WILV" + i.ToString(2);
		}
		
		// Nums
		for (i = 0; i < 10; i++)
		{
			m_aWINUMs.Insert(m_DAssets.m_mPatches["WINUM" + i.ToString()]);
		} 
		m_aWINUMs.Insert(m_DAssets.m_mPatches["WIPCNT"]);
		m_aWINUMs.Insert(m_DAssets.m_mPatches["WIMINUS"]);
		m_aWINUMs.Insert(m_DAssets.m_mPatches["WICOLON"]);
		
		// Words
		m_WIF = m_DAssets.m_mPatches["WIF"];
		m_WISPLAT = m_DAssets.m_mPatches["WISPLAT"];
		m_WIOSTK = m_DAssets.m_mPatches["WIOSTK"];
		m_WIOSTI = m_DAssets.m_mPatches["WIOSTI"];
		m_WIMSTT = m_DAssets.m_mPatches["WIMSTT"];
		m_WISCRT2 = m_DAssets.m_mPatches["WISCRT2"];
		m_WITIME = m_DAssets.m_mPatches["WITIME"];
		m_WIENTER = m_DAssets.m_mPatches["WIENTER"];
		m_WIURH0 = m_DAssets.m_mPatches["WIURH0"];
		m_WIURH1 = m_DAssets.m_mPatches["WIURH1"];
	}
	
	const static int WI_TITLEY = 2;
	const static int WI_SPACINGY = 33;
	const static int SP_STATSX = 50;
	const static int SP_STATSY = 50;
	const static int SP_TIMEX = 16;
	const static int SP_TIMEY = 168;

	// Ticks
	int m_iTickNum;
	static const float TICK_DELAY = 28;
	float m_fLastTickTime;
	
	// current stat
	int m_iNeedKills = 0;
	int m_iNeedItems = 0;
	int m_iNeedSecrets = 0;
	int m_iNeedTime = 0;
	int m_iNeedTimeTotal = 0;
	
	int m_iCurrentKills = -1;
	int m_iCurrentItems = -1;
	int m_iCurrentSecrets = -1;
	int m_iCurrentTime      = -1;
	int m_iCurrentTimeTotal = -1;
	
	int m_iPause = 0;
	int m_iState;
	
	bool m_bClick;
	
	void CalculatePercent(PS_DMap dMap)
	{
		m_iNeedKills = 0;
		if (dMap.m_iKillsCount > 0)
		{
			m_iNeedKills = (dMap.m_iKillsCollected * 100) / dMap.m_iKillsCount;
		}
		
		m_iNeedItems = 0;
		if (dMap.m_iItemsCount > 0)
		{
			m_iNeedItems = (dMap.m_iItemsCollected * 100) / dMap.m_iItemsCount;
		}
		
		m_iNeedSecrets = 0;
		if (dMap.m_iSecretsCount > 0)
		{
			m_iNeedSecrets = (dMap.m_iSecretsCollected * 100) / dMap.m_iSecretsCount;
		}
		
		m_iNeedTime = dMap.m_iTickNum / TICK_DELAY;
		m_iNeedTimeTotal = m_iNeedTimeTotal + m_iNeedTime;
		
		m_iCurrentKills = -1;
		m_iCurrentItems = -1;
		m_iCurrentSecrets = -1;
		m_iCurrentTime = -1;
		
		m_iPause = 0;
		m_iState = 0;
		
		m_bClick = false;
	}
	
	void Draw()
	{
		DrawPatch(0, 0, m_WINMAP);
		
		foreach (PS_DIntermissionAnimation animation : EP0AMIS)
		{
			DrawPatch(animation.m_aLocation[0], animation.m_aLocation[1], animation.GetPatch());
		}
		
		if (m_iState < 2)
		{
			DrawStatistic();
			DrawLevelFinished();
		} else {
			if ((m_iTickNum & 31) < 16)
				DrawYou();
			DrawSplats();
			DrawLevelEntering();
		}
	}
	
	void Update()
	{
		float updateTime = GetGame().GetWorld().GetWorldTime();
		
		while (updateTime - TICK_DELAY > m_fLastTickTime)
		{
			m_iTickNum++;
			FixedUpdate(TICK_DELAY);
			m_fLastTickTime += TICK_DELAY;
		}
	}
	
	void FixedUpdate(float timeSlice)
	{
		foreach (PS_DIntermissionAnimation animation : EP0AMIS)
		{
			animation.Update();
		}
		
		// Statees skip
		if (
			GetGame().GetInputManager().GetActionValue("DFire") ||
			GetGame().GetInputManager().GetActionValue("DAction")
		) {
			if (!m_bClick)
			{
				m_bClick = true;
				
				if (m_iState == 0)
				{
					PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_sgcock, "0 0 0");
					m_iCurrentKills = m_iNeedKills;
					m_iCurrentItems = m_iNeedItems;
					m_iCurrentSecrets = m_iNeedSecrets;
					m_iCurrentTime = m_iNeedTime;
					m_iCurrentTimeTotal = m_iNeedTimeTotal;
					m_iState = 1;
					m_iPause = 0;
				} else if (m_iState == 1) {
					PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_sgcock, "0 0 0");
					m_iState = 2;
				} else if (m_iState == 2) {
					PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_sgcock, "0 0 0");
					m_DMain.NextLevel();
				}
			}
		}
		else
			m_bClick = false;
		
		if (m_iPause > 0)
		{
			m_iPause--;
			return;
		}
		
		if (m_iCurrentKills < m_iNeedKills)
		{
			if ((m_iTickNum & 3) == 0)
				PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_pistol, "0 0 0");
			m_iCurrentKills += 2;
			if (m_iCurrentKills >= m_iNeedKills)
			{
				m_iCurrentKills = m_iNeedKills;
				m_iPause = 35;
				PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_barexp, "0 0 0");
			}
		} else if (m_iCurrentItems < m_iNeedItems)
		{
			if ((m_iTickNum & 3) == 0)
				PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_pistol, "0 0 0");
			m_iCurrentItems += 2;
			if (m_iCurrentItems >= m_iNeedItems)
			{
				m_iCurrentItems = m_iNeedItems;
				m_iPause = 35;
				PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_barexp, "0 0 0");
			}
		} else if (m_iCurrentSecrets < m_iNeedSecrets)
		{
			if ((m_iTickNum & 3) == 0)
				PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_pistol, "0 0 0");
			m_iCurrentSecrets += 2;
			if (m_iCurrentSecrets > m_iNeedSecrets)
			{
				m_iCurrentSecrets = m_iNeedSecrets;
				m_iPause = 35;
				PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_barexp, "0 0 0");
			}
		} else if (m_iCurrentTime < m_iNeedTime || m_iCurrentTimeTotal < m_iNeedTimeTotal)
		{
			if ((m_iTickNum & 3) == 0)
				PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_pistol, "0 0 0");
			m_iCurrentTime += 3;
			if (m_iCurrentTime > m_iNeedTime)
				m_iCurrentTime = m_iNeedTime;
			
			m_iCurrentTimeTotal += 3;
			if (m_iCurrentTimeTotal > m_iNeedTimeTotal)
				m_iCurrentTimeTotal = m_iNeedTimeTotal;
			
			if (m_iCurrentTime == m_iNeedTime && m_iCurrentTimeTotal == m_iNeedTimeTotal)
			{
				m_iState = 1;
				PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_barexp, "0 0 0");
			}
		}
	}
	
	void DrawStatistic()
	{
		DrawPatch(SP_STATSX, SP_STATSY     , m_WIOSTK);
		DrawPatch(SP_STATSX, SP_STATSY + 16, m_WIOSTI);
		DrawPatch(SP_STATSX, SP_STATSY + 32, m_WISCRT2);
		
		DrawPercent(PS_DConst.SCREEN_WIDTH - SP_STATSX, SP_STATSY     , m_iCurrentKills);
		DrawPercent(PS_DConst.SCREEN_WIDTH - SP_STATSX, SP_STATSY + 16, m_iCurrentItems);
		DrawPercent(PS_DConst.SCREEN_WIDTH - SP_STATSX, SP_STATSY + 32, m_iCurrentSecrets);
		
		DrawPatch(SP_TIMEX, SP_TIMEY, m_WITIME);
		DrawPatch(SP_TIMEX, SP_TIMEY + 16, m_WIMSTT);
		
		DrawTime(PS_DConst.SCREEN_WIDTH_HALF - SP_TIMEX, SP_TIMEY, m_iCurrentTime);
		DrawTime(PS_DConst.SCREEN_WIDTH_HALF - SP_TIMEX, SP_TIMEY + 16, m_iCurrentTimeTotal);
	}
	
	void DrawTime(int x, int y, int seconds)
	{
		if (seconds == -1)
			return;
		
		int minutes = seconds / 60;
		seconds = Math.Mod(seconds, 60);
		
		x -= 13;
		DrawNum(x, y, seconds);
		if (minutes > 0)
		{
			PS_DPatch columnPatch = m_aWINUMs[12];
			x -= 26;
			DrawPatch(x, y, columnPatch);
			x -= 13;
			DrawNum(x, y, minutes);
		}
	}
	
	void DrawPercent(int x, int y, int percent)
	{
		if (percent == -1)
			return;
		
		PS_DPatch percentPatch = m_aWINUMs[10];
		x -= 13;
		DrawPatch(x, y, percentPatch);
		x -= 13;
		DrawNum(x, y, percent);
	}
	
	int DrawNum(int x, int y, int num)
	{
		bool firstDraw = true;
		while (num > 0 || firstDraw)
		{
			firstDraw = false;
			PS_DPatch patch = m_aWINUMs[Math.Mod(num, 10)];
			DrawPatch(x, y, patch);
			x -= 13;
			num = num / 10;
		}
		return x;
	}
	
	void DrawLevelEntering()
	{
		int x = PS_DConst.SCREEN_WIDTH_HALF - m_WIENTER.m_DPatchHeader.m_iWidth/2;
		DrawPatch(x, WI_TITLEY, m_WIENTER);
		
		PS_DPatch nextLevel = m_aLevelPatches[m_DMain.m_iNextLevel];
		x = PS_DConst.SCREEN_WIDTH_HALF - nextLevel.m_DPatchHeader.m_iWidth/2;
		DrawPatch(x, WI_TITLEY*2 + m_WIENTER.m_DPatchHeader.m_iHeight, nextLevel);
	}
	
	void DrawLevelFinished()
	{
		PS_DPatch currentLevel = m_aLevelPatches[m_DMain.m_iCurrentLevel];
		int x = PS_DConst.SCREEN_WIDTH_HALF - currentLevel.m_DPatchHeader.m_iWidth/2;
		DrawPatch(x, WI_TITLEY, currentLevel);
		
		x = PS_DConst.SCREEN_WIDTH_HALF - m_WIF.m_DPatchHeader.m_iWidth/2;
		DrawPatch(x, WI_TITLEY*2 + currentLevel.m_DPatchHeader.m_iHeight, m_WIF);
	}
	
	void DrawSplats()
	{
		int splatsCount = m_DMain.m_iCurrentLevel;
		if (splatsCount == 8)
			splatsCount = 3;
		for (int i = 0; i <= splatsCount; i++)
		{
			DrawSplat(i);
		}
		if (m_DMain.m_bDidSecret)
			DrawSplat(8);
	}
	
	void DrawSplat(int num)
	{
		array<int> location = LOCATIONS[0][num];
		int x = location[0];
		int y = location[1];
		x -= m_WISPLAT.m_DPatchHeader.m_iWidth/2;
		y -= m_WISPLAT.m_DPatchHeader.m_iHeight/2;
		DrawPatch(location[0], location[1], m_WISPLAT);
	}
	
	void DrawYou()
	{
		array<int> location = LOCATIONS[0][m_DMain.m_iNextLevel];
		int x = location[0];
		int y = location[1];
		
		PS_DPatch you = m_WIURH0;
		if (x > PS_DConst.SCREEN_WIDTH_HALF)
		{
			you = m_WIURH1;
			x -= m_WIURH1.m_DPatchHeader.m_iWidth;
		}
		
		DrawPatch(x, y, you);
	}
	
	void DrawPatch(int x, int y, PS_DPatch patch)
	{
		PS_DPalette pallete = m_DAssets.m_aPalletes[0];
		x -= patch.m_DPatchHeader.m_iLeftOffset;
		y -= patch.m_DPatchHeader.m_iTopOffset;
		int width = patch.m_DPatchHeader.m_iWidth;
		int height = patch.m_DPatchHeader.m_iHeight;
		int x2 = x + width;
		int y1 = y;
		int y2 = y + height;
		int xp = 0;
		for (x; x < x2; x++)
		{
			int yp = 0;
			for (y = y1; y < y2; y++)
			{
				int colorIndex = patch.m_DTexture.m_aPixels[xp + yp * width];
				if (colorIndex != 256)
				{
					int color = pallete.m_aColors[colorIndex];
					int pixelIndex = x + y * PS_DConst.SCREEN_WIDTH;
					if (pixelIndex < PS_EddsTextureCanvasComponent.SCREEN_SIZE)
						PS_EddsTextureCanvasComponent.m_aPixels[pixelIndex] = color;
				}
				yp++;
			}
			xp++;
		}
	}
}

class PS_DIntermissionAnimation
{
	bool m_bAnimAlways;
	int m_iTickRate;
	int m_iFramesNum;
	ref array<int> m_aLocation;
	
	int m_iTicks;
	int m_iCurrentFrame;
	ref array<PS_DPatch> m_aPatches = {};
	
	void Update()
	{
		m_iTicks--;
		if (m_iTicks <= 0)
		{
			m_iCurrentFrame++;
			if (m_iCurrentFrame >= m_iFramesNum)
				m_iCurrentFrame = 0;
			m_iTicks = m_iTickRate;
		}
	}
	
	PS_DPatch GetPatch()
	{
		return m_aPatches[m_iCurrentFrame];
	}
	
	void PS_DIntermissionAnimation(
		bool animAlways,
		int tickRate,
		int framesNum,
		array<int> location
	)
	{
		m_bAnimAlways = animAlways;
		m_iTickRate = tickRate;
		m_iFramesNum = framesNum;
		m_aLocation = location;
	}
}




