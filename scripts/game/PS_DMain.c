// Spaggetty kingdom of our image drawing software
class PS_DMain
{
	static PS_DMain s_DMain; // FIXME: remove static reference
	
	// Systems
	ref PS_DWAD m_DWAD;             // WAD file (Game resources)
	ref PS_DMap m_DMap;             // Current loaded map
	ref PS_DRenderer m_DRenderer;   // 3D renderer (Also fill 2D canvas)
	ref PS_DInterface m_DInterface; // All in game interface stuff
	ref PS_DInput m_DInput;         // In game input, menus read it directly (FIXME?)
	
	ref PS_DMainMenu m_DMainMenu;         // All menus, not main (FIXME: Bad naming)
	ref PS_DIntermission m_DIntermission; // Intermission screen renderer
	ref PS_DEndingScreen m_DEndingScreen; // Ending screen renderer
	
	ref PS_DEntityPlayer m_EntityPlayer; // Save player data between levels
		
	// Dynamic stuff
	int m_iFrameNum;   // Current engine frame num
	bool m_bSecret;    // Secret exit used
	bool m_bDidSecret; // Player did secret
	bool m_bClose;     // Need to be closed by outer scope flag
	bool m_bInMenu;    // Render menu flag
	
	int m_iDifficulty; // Selected skill level
	PS_DGameState m_CurrentGameState = PS_DGameState.GS_MAINMENU; // Current state for renderer selection
	
	ref RandomGenerator m_RandomGenerator; // All random need to be predictable for demos (Broken?)
	
	static const int SCREEN_WIDTH = PS_DEddsTexture.SCREEN_WIDTH;
	const static int SCREEN_HEIGHT = PS_DEddsTexture.SCREEN_HEIGHT;
	const static int SCREEN_SIZE = PS_DEddsTexture.SCREEN_SIZE;
	
	// Melt effect
	static int m_aPixelsBuffer[SCREEN_SIZE];  // Melting screen pixels copy
	static int m_aPixelsOffset[SCREEN_WIDTH]; // Offsets for each pixel column
	int m_iMeltEffect = 1;                    // Screen melting flag, booleans a little funky
	
	int m_iCurrentLevel = 0;        // Current level num
	int m_iNextLevel = 0;           // Level to be loaded
	ref array<string> m_aLevels = { // Level names in WAD (TODO: move somewere else)
		"E1M1",
		"E1M2",
		"E1M3",
		"E1M4",
		"E1M5",
		"E1M6",
		"E1M7",
		"E1M8",
		"E1M9"
	};
	
	//------------------------------------------------------------------------------------------------
	// Debug rendering function (Remove?)
	static ref map<string, ref map<int, int>> m_mColorsMap = new map<string, ref map<int, int>>();
	static int m_iLastColor;
	int GetUniqueColorForTexture(string textureName, int lightLevel)
	{
		map<int, int> lightLevels;
		if (!m_mColorsMap.Contains(textureName))
		{
			lightLevels = new map<int, int>();
			m_mColorsMap.Insert(textureName, lightLevels);
		}
		else
			lightLevels = m_mColorsMap[textureName];
		int color;
		if (!lightLevels.Contains(lightLevel))
		{
			color = m_DWAD.m_DAssets.m_aPalletes[0].m_aColors[m_iLastColor];
			m_iLastColor++;
			if (m_iLastColor > 255)
				m_iLastColor = 0;
			lightLevels.Insert(lightLevel, color)
		}
		else
			color = lightLevels[lightLevel];
		return color;
	}
	
	//------------------------------------------------------------------------------------------------
	// Launch end game sequence
	void EndGame()
	{
		PS_DMusicEffect.Play("INTROA");
		
		MeltScreen();
		m_DEndingScreen.m_iLastChar = 0;
		m_CurrentGameState = PS_DGameState.GS_END;
	}
	
	//------------------------------------------------------------------------------------------------
	// Restart game
	void Restart()
	{
		MeltScreen();
		m_CurrentGameState = PS_DGameState.GS_MAINMENU;
		m_iCurrentLevel = 0;
		m_iNextLevel = 0;
		m_DMainMenu.Reset(false);
		m_DMap = null;
		ResetPlayer();
	}
	
	//------------------------------------------------------------------------------------------------
	// Launch intermission sequence
	void Intermission(bool secret = false)
	{
		PS_DMusicEffect.Play("VICTOR");
		
		m_bSecret = secret;
		m_iNextLevel = m_iCurrentLevel + 1;
		if (m_iCurrentLevel == 8)
		{
			m_bDidSecret = true;
			m_iNextLevel = 3;
		}
		if (m_bSecret)
			m_iNextLevel = 8;
		MeltScreen();
		m_CurrentGameState = PS_DGameState.GS_INTERMISSION;
		m_DIntermission.m_DMap = m_DMap;
		m_DIntermission.CalculatePercent(m_DMap);
	}
	
	//------------------------------------------------------------------------------------------------
	// Load next level, and start game
	void NextLevel()
	{
		// Secret check
		if (m_bSecret)
		{
			m_bSecret = false;
			m_iCurrentLevel = 8;
		}
		else if (m_iCurrentLevel == 8)
			m_iCurrentLevel = 3;
		else
			m_iCurrentLevel++;
		
		// Lavel music
		PS_DMusicEffect.Play(m_aLevels[m_iCurrentLevel], m_iCurrentLevel);
		
		LoadLevel(m_aLevels[m_iCurrentLevel]);       // Actually load level from WAD
		MeltScreen();                                // Melt effect
		m_CurrentGameState = PS_DGameState.GS_LEVEL; // Switch state
	}
	
	//------------------------------------------------------------------------------------------------
	// Start screen melting effect
	void MeltScreen()
	{
		// Set random columns offsets
		int yOffset = -64;
		for (int i = 0; i < SCREEN_WIDTH; i++)
		{
			yOffset += Math.RandomIntInclusive(-8, 8);
			yOffset = Math.Min(yOffset, 0);
			m_aPixelsOffset[i] = yOffset;
		}
		m_iMeltEffect = 1; // Set flag
		StaticArray.Copy(m_aPixelsBuffer, PS_DEddsTexture.m_aPixels); // Copy current screen state
	}
	
	//------------------------------------------------------------------------------------------------
	void Update(float timeSlice)
	{
		PS_DMusicEffect.Update(timeSlice); // Update sound timer
		
		float updateTime = GetGame().GetWorld().GetWorldTime();
		
		m_iFrameNum++;
		
		// TODO: proper QuickSaves
		if (GetGame().GetInputManager().GetActionTriggered("DQS"))
		{
			PS_DSave.Save(this, "$profile:DE/Saves/QuickSave.dsv")
		}
		if (GetGame().GetInputManager().GetActionTriggered("DQL"))
		{
			PS_DSave.Load(this, "$profile:DE/Saves/QuickSave.dsv")
		}
		
		m_DInput.UpdateValues();
		switch (m_CurrentGameState)
		{
			case PS_DGameState.GS_MAINMENU:
				m_DMainMenu.Draw();
				m_DMainMenu.Update();
				m_DInput.ResetInput();
				break;
			case PS_DGameState.GS_LEVEL:
				if (m_iMeltEffect <= 0 && !m_bInMenu) // Skip logic while melting
					m_DMap.Update();
				else
					m_DMap.m_fLastTickTime = GetGame().GetWorld().GetWorldTime();
				m_DRenderer.DrawFrame();
				m_DInterface.Draw();
			
				if (m_bInMenu)
				{
					m_DMainMenu.Draw();
					m_DMainMenu.Update();
					m_DInput.ResetInput();
				}
			
				break;
			case PS_DGameState.GS_INTERMISSION:
				if (m_iMeltEffect <= 0) // Skip logic while melting
					m_DIntermission.Update();
				else
					m_DIntermission.m_fLastTickTime = GetGame().GetWorld().GetWorldTime();
				m_DIntermission.Draw();
				break;
			case PS_DGameState.GS_END:
				if (m_iMeltEffect <= 0) // Skip logic while melting
					m_DEndingScreen.Update();
				else
					m_DEndingScreen.m_fLastTickTime = GetGame().GetWorld().GetWorldTime();
				m_DEndingScreen.Draw();
				break;
		}
		if (m_iMeltEffect > 0) // Draw melt effect
		{
			MeltEffect();
		}
	}
	
	void MeltEffect()
	{
		m_iMeltEffect = 0;
		
		for (int x = 0; x < PS_DConst.SCREEN_WIDTH; x++)
		{
			if (m_aPixelsOffset[x] < SCREEN_HEIGHT)
			{
				m_aPixelsOffset[x] = m_aPixelsOffset[x] + 8;
				m_iMeltEffect = 1;
			}
			for (int y = 0; y < PS_DConst.SCREEN_HEIGHT; y++)
			{
				int index = x + y * PS_DConst.SCREEN_WIDTH;
				int color = m_aPixelsBuffer[index];
				
				int offsetY = Math.Max(m_aPixelsOffset[x], 0);
				int indexScreen = x + (y + offsetY) * PS_DConst.SCREEN_WIDTH;
				if (indexScreen < SCREEN_SIZE)
					PS_DEddsTexture.m_aPixels[indexScreen] = m_aPixelsBuffer[index];
			}
		}
	}
	
	void LoadLevel(string levelName)
	{
		m_RandomGenerator.SetSeed(0);
		
		m_DWAD.LoadMap(levelName);
		
		m_DMap = m_DWAD.m_dMap;
		
		PS_DThing playerThing = m_DMap.m_aThings[0];
		m_EntityPlayer.m_vPosition = Vector(playerThing.m_iXPos, playerThing.m_iYPos, 0);
		m_EntityPlayer.m_fAngle = (float)(-playerThing.m_iAngle + 180) * Math.DEG2RAD - Math.PI_HALF;
		m_DMap.m_aEntities.Insert(m_EntityPlayer);
		PS_DStateMachine.m_DMap = m_DMap;
		PS_DStateMachine.m_Player = m_EntityPlayer;
		m_EntityPlayer.m_vVelocity = "0 0 0";
		
		m_EntityPlayer.m_DMap = m_DMap;
		m_DRenderer.m_DMap = m_DMap;
		
		m_EntityPlayer.Update();
		m_DMap.FixedUpdate(0);
		
		for (int i = 0; i < 3; i++)
			m_EntityPlayer.m_aKeys[i] = 0;
		
		if (m_EntityPlayer.m_iBackpack == 1)
		{
			m_EntityPlayer.m_iBackpack = 0;
			for (int i = 0; i < 4; i++)
			{
				m_EntityPlayer.m_aAmmoMax[i] = m_EntityPlayer.m_aAmmoMax[i] / 2;
				m_EntityPlayer.m_aAmmo[i] = Math.Min(m_EntityPlayer.m_aAmmo[i], m_EntityPlayer.m_aAmmoMax[i]);
			}
		}
		
		m_EntityPlayer.m_vCameraPosition = m_EntityPlayer.m_vPosition;
		m_EntityPlayer.m_vCameraPosition[2] = m_EntityPlayer.m_vCameraPosition[2] + PS_DConst.CAMERA_HEIGHT;
	}
	
	void PS_DMain()
	{
		m_RandomGenerator = new RandomGenerator();
		
		m_DInput = new PS_DInput();
		m_DInput.Init();
		
		s_DMain = this;
		
		// Preload all crazy state tables
		PS_DInfo.Init();
		PS_DInfo.Init3(); // Too big for enf
		
		m_DWAD = PS_DWAD(this, "$profile:DE/doom1.wad");
		PS_DWeaponInfo.Init(m_DWAD.m_DAssets);
		m_DRenderer = PS_DRenderer(this, null, m_DWAD.m_DAssets);
		PS_DAnimatedTexture.Init(m_DWAD.m_DAssets);
		
		ResetPlayer();
		
		m_DMainMenu = new PS_DMainMenu(this, m_DWAD.m_DAssets);
		m_DIntermission = new PS_DIntermission(this, m_DWAD.m_DAssets);
		m_DEndingScreen = new PS_DEndingScreen(this, m_DWAD.m_DAssets);
	}
	
	void ResetPlayer()
	{
		m_EntityPlayer = new PS_DEntityPlayer(null);
		m_EntityPlayer.m_MobjInfo = PS_DInfo.m_aMobjInfo[0];
		m_EntityPlayer.m_BBOX = new PS_DEntityBBox(m_EntityPlayer.m_MobjInfo);
		m_EntityPlayer.m_iHealth = 100;
		m_EntityPlayer.m_iFlags = m_EntityPlayer.m_MobjInfo.m_iFlags;
		m_DInterface = new PS_DInterface(m_EntityPlayer, m_DWAD, m_DWAD.m_DAssets);
		PS_DSoundEffect.s_Player = m_EntityPlayer;
	}
	
	void Close()
	{
		m_bClose = true;
	}
	
	void ~PS_DMain()
	{
		PS_DMusicEffect.Reset();
	}
	
	// Save
	void WriteSave(FileHandle saveFile)
	{
		float xStep = (float) 272 / (float)PS_DConst.SAVE_PREVIEW_WIDTH;
		float yStep = (float) 168 / (float)PS_DConst.SAVE_PREVIEW_HEIGHT;
		float yTexture = 0;
		float xTexture = 24;
		for (int y = 0; y < PS_DConst.SAVE_PREVIEW_HEIGHT; y++)
		{
			xTexture = 24;
			for (int x = 0; x < PS_DConst.SAVE_PREVIEW_WIDTH; x++)
			{
				int pixelIndex = ((int) xTexture) + (((int) yTexture) * PS_DConst.SCREEN_WIDTH);
				int pixel = PS_DEddsTexture.m_aPixels[pixelIndex];
				saveFile.Write(pixel, 4);
				xTexture += xStep;
			}
			yTexture += yStep;
		}
		
		saveFile.Write(m_iCurrentLevel, 1);
		saveFile.Write(m_iDifficulty, 1);
		saveFile.Write(m_bDidSecret, 1);
		if (m_DMap)
			m_DMap.WriteSave(saveFile);
	}
	
	void ReadSave(FileHandle saveFile)
	{
		// Skip preview
		int pixel;
		for (int i = 0; i < PS_DConst.SAVE_PREVIEW_SIZE; i++)
			saveFile.Read(pixel, 4);
		
		saveFile.Read(m_iCurrentLevel, 1);
		saveFile.Read(m_iDifficulty, 1);
		saveFile.Read(m_bDidSecret, 1);
		
		LoadLevel(m_aLevels[m_iCurrentLevel]);
		if (m_DMap)
			m_DMap.ReadSave(saveFile);
	}
}

enum PS_DGameState
{
	GS_MAINMENU,
	GS_LEVEL,
	GS_INTERMISSION,
	GS_END
}