class PS_DMainMenu
{
	PS_DMain m_DMain;
	PS_DAssets m_DAssets;
	
	PS_DPatch m_TITLEPIC;
	
	PS_DPatch m_SKULL1;
	
	int m_iTitleTicks = 60;
	
	int m_iCurrentMenu = 0;
	int m_iItemChanged;
	
	ref PS_DSubMenu m_MainMenu;
	ref PS_DSubMenu m_InGameMenu;
	ref PS_DReadMeSubMenu m_ReadMeMenu;
	ref PS_DSubMenu m_EpisodeMenu;
	ref PS_DSkillSubMenu m_SkillMenu;
	ref PS_DSaveSubMenu m_SaveMenu;
	
	ref array<ref PS_DSubMenu> m_aSubMenus;
	ref PS_DSubMenu m_CurrentSubMenu;
	
	bool m_bAction;
	bool m_bDirection;
	bool m_bESC;
	bool m_bENT;
	
	ref array<PS_DSubMenu> m_aPrevMenu = {};
	
	void PS_DMainMenu(PS_DMain dMain, PS_DAssets dAssets)
	{
		m_DMain = dMain;
		m_DAssets = dAssets;
		
		m_MainMenu = new PS_DSubMenu(this, dMain);
		m_InGameMenu = new PS_DSubMenu(this, dMain);
		m_ReadMeMenu = new PS_DReadMeSubMenu(this, dMain);
		m_EpisodeMenu = new PS_DSubMenu(this, dMain);
		m_SkillMenu = new PS_DSkillSubMenu(this, dMain);
		m_SaveMenu = new PS_DSaveSubMenu(this, dMain);
		
		m_CurrentSubMenu = m_MainMenu;
		
		m_SKULL1 = dAssets.m_mPatches["M_SKULL1"];
		m_TITLEPIC = dAssets.m_mPatches["TITLEPIC"];
		
		m_MainMenu.m_aMenuItems =
		{
			new PS_DMenuItem(this, dAssets, "M_DOOM"),
			new PS_DMenuItem(this, dAssets, "M_NGAME", m_EpisodeMenu),
			new PS_DMenuItem(this, dAssets, "M_OPTION"),
			new PS_DLoadMenuItem(this, dAssets, "M_LOADG", m_SaveMenu),
			new PS_DMenuItem(this, dAssets, "M_RDTHIS", m_ReadMeMenu),
			new PS_DExitMenuItem(this, dAssets, "M_ENDGAM")
		};
		
		m_InGameMenu.m_aMenuItems =
		{
			new PS_DMenuItem(this, dAssets, "M_DOOM"),
			new PS_DMenuItem(this, dAssets, "M_NGAME", m_EpisodeMenu),
			new PS_DMenuItem(this, dAssets, "M_OPTION"),
			new PS_DSaveMenuItem(this, dAssets, "M_SGTTL", m_SaveMenu),
			new PS_DLoadMenuItem(this, dAssets, "M_LOADG", m_SaveMenu),
			new PS_DMenuItem(this, dAssets, "M_RDTHIS", m_ReadMeMenu),
			new PS_DExitMenuItem(this, dAssets, "M_ENDGAM")
		};
		
		m_EpisodeMenu.m_aMenuItems =
		{
			new PS_DMenuItem(this, dAssets, "M_EPISOD"),
			new PS_DMenuItem(this, dAssets, "M_EPI1", m_SkillMenu),
			new PS_DMenuItem(this, dAssets, "M_EPI2"),
			new PS_DMenuItem(this, dAssets, "M_EPI3")
		};
		
		m_SkillMenu.m_aMenuItems = 
		{
			new PS_DMenuItem(this, dAssets, "M_SKILL"),
			new PS_DMenuItem(this, dAssets, "M_JKILL"),
			new PS_DMenuItem(this, dAssets, "M_ROUGH"),
			new PS_DMenuItem(this, dAssets, "M_HURT"),
			new PS_DMenuItem(this, dAssets, "M_ULTRA"),
			new PS_DMenuItem(this, dAssets, "M_NMARE")
		};
	}
	
	void Reset(bool inGame)
	{
		m_iTitleTicks = 60;
		if (!inGame)
			m_CurrentSubMenu = m_MainMenu;
		else
			m_CurrentSubMenu = m_InGameMenu;
		m_aPrevMenu = {};
		
		m_bESC = true;
		m_bAction = true;
		m_bDirection = true;
		m_bENT = true;
	}
	
	void Draw()
	{
		if (m_DMain.m_DMap == null)
		{
			if (m_iTitleTicks == 60)
				PS_DMusicEffect.Play("INTER", false);
			
			if (m_iTitleTicks > 0)
			{
				DrawPatch(0, 0, m_TITLEPIC);
				m_iTitleTicks--;
				return;
			}
			DrawPatch(0, 0, m_TITLEPIC, 12);
		}
		
		m_CurrentSubMenu.Draw();
	}
	
	void Update()
	{
		if (m_iTitleTicks > 0)
		{
			m_iTitleTicks--;
			if (m_iTitleTicks == 0)
				PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_swtchn, "0 0 0");
			return;
		}
		
		m_CurrentSubMenu.Update();
		
		float direction = GetGame().GetInputManager().GetActionValue("DForward");
		if (GetGame().GetInputManager().GetActionTriggered("DW1"))
			direction++;
		if (GetGame().GetInputManager().GetActionTriggered("DW3"))
			direction--;
		if (direction != 0)
		{
			if (m_bDirection)
				return;
			m_bDirection = true;
			
			m_CurrentSubMenu.UpdateDirection(direction.Sign());
		}
		else
			m_bDirection = false;
		
		
		float ent = GetGame().GetInputManager().GetActionValue("DENT");
		if (ent)
		{
			if (m_bENT)
				return;
			m_bENT = true;
			m_CurrentSubMenu.Return();
		}
		else
			m_bENT = false;
		
		
		float esc = GetGame().GetInputManager().GetActionValue("DESC");
		if (GetGame().GetInputManager().GetActionValue("DBACK"))
			esc++;
		if (esc)
		{
			if (m_bESC)
				return;
			m_bESC = true;
			
			if (!m_CurrentSubMenu.Back())
				return;
			
			if (m_aPrevMenu.Count() > 0)
			{
				m_CurrentSubMenu = m_aPrevMenu[m_aPrevMenu.Count() - 1];
				m_aPrevMenu.Remove(m_aPrevMenu.Count() - 1);
				PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_swtchx, "0 0 0");
				return;
			}
			else
			{
				m_DMain.m_bInMenu = false;
				return;
			}
		}
		else
			m_bESC = false;
		
		float action = GetGame().GetInputManager().GetActionValue("DAction");
		if (action)
		{
			if (m_bAction)
				return;
			m_bAction = true;
			m_CurrentSubMenu.Activate();
		}
		else
			m_bAction = false;
	}
	
	void DrawPatch(int x, int y, PS_DPatch patch, int light = 31)
	{
		PS_DPalette pallete = m_DAssets.m_aColoredPalletes[0][light];
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



