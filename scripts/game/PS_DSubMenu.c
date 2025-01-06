class PS_DSubMenu
{
	void PS_DSubMenu(PS_DMainMenu dMainMenu, PS_DMain dMain)
	{
		m_DMainMenu = dMainMenu;
		m_DMain = dMain;
	}

	PS_DMainMenu m_DMainMenu;
	PS_DMain m_DMain;
	ref array<ref PS_DMenuItem> m_aMenuItems;
	int m_iCurrentMenuItem = 1;

	void UpdateDirection(int direction)
	{
		m_iCurrentMenuItem -= direction;
		PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_pstop, "0 0 0");
		if (m_iCurrentMenuItem < 1)
			m_iCurrentMenuItem = m_aMenuItems.Count() - 1;
		if (m_iCurrentMenuItem >= m_aMenuItems.Count())
			m_iCurrentMenuItem = 1;
	}

	bool Back()
	{
		return true;
	}

	void Return()
	{
		Activate();
	}

	void Activate()
	{
		PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_swtchn, "0 0 0");

		PS_DMenuItem menuItem = m_aMenuItems[m_iCurrentMenuItem];
		menuItem.Activate();
		PS_DSubMenu nextMenu = menuItem.m_NextMenu;
		if (nextMenu)
		{
			m_DMainMenu.m_aPrevMenu.Insert(this);
			m_DMainMenu.m_CurrentSubMenu = nextMenu;
			m_DMainMenu.m_CurrentSubMenu.Open();
		}
	}

	void Update()
	{

	}

	void Draw()
	{
		int height = 0;
		foreach (PS_DMenuItem dMenuItem : m_aMenuItems)
		{
			height += dMenuItem.m_DPatch.m_DPatchHeader.m_iHeight + 3;
		}

		int y = (200 - height) / 2;
		int x = PS_DConst.SCREEN_WIDTH_HALF;
		int i = 0;
		foreach (PS_DMenuItem dMenuItem : m_aMenuItems)
		{
			m_DMainMenu.DrawPatch(x - dMenuItem.m_DPatch.m_DPatchHeader.m_iWidth/ 2, y, dMenuItem.m_DPatch);

			if (m_iCurrentMenuItem == i)
			{
				m_DMainMenu.DrawPatch(x - dMenuItem.m_DPatch.m_DPatchHeader.m_iWidth/ 2 - 3 - m_DMainMenu.m_SKULL1.m_DPatchHeader.m_iWidth, y - 2, m_DMainMenu.m_SKULL1);
			}

			y += dMenuItem.m_DPatch.m_DPatchHeader.m_iHeight + 3;
			i++;
		}
	}

	void Open()
	{

	}
}

class PS_DReadMeSubMenu : PS_DSubMenu
{
	PS_DPatch m_HELP1;

	void PS_DReadMeSubMenu(PS_DMainMenu dMainMenu, PS_DMain dMain)
	{
		m_HELP1 = dMainMenu.m_DAssets.m_mPatches["HELP1"];
	}

	override void UpdateDirection(int direction)
	{

	}

	override void Activate()
	{

	}

	override void Draw()
	{
		m_DMainMenu.DrawPatch(0, 0, m_HELP1);
	}
}

class PS_DSkillSubMenu : PS_DSubMenu
{
	override void Activate()
	{
		m_DMain.m_bInMenu = false;

		m_DMain.m_iDifficulty = m_iCurrentMenuItem - 1;

		m_DMain.ResetPlayer();
		m_DMain.MeltScreen();
		m_DMain.m_iCurrentLevel = 0;
		m_DMain.LoadLevel("E1M1");
		PS_DMusicEffect.Play("E1M1", 0);
		m_DMain.m_CurrentGameState = PS_DGameState.GS_LEVEL;
		return;
	}
}


class PS_DOptionsSubMenu : PS_DSubMenu
{
	ref array<ref PS_DOption> m_aOptionsList = {};

	override void Activate()
	{
		if (m_iCurrentMenuItem >= m_aOptionsList.Count())
			return;

		m_aOptionsList[m_iCurrentMenuItem].Activate();
	}

	override void Draw()
	{
		PS_DAssets assets = PS_DMain.s_DMain.m_DWAD.m_DAssets;
		int y = 16;
		int i = 0;
		foreach (PS_DOption option : m_aOptionsList)
		{
			if (m_iCurrentMenuItem == i)
			{
				assets.FillBox(166, y, 138, 8, Color.ORANGE);
			}
			assets.DrawText(167, y + 1, option.GetName(), 0);
			y += 8;
			i++;
		}
	}

	override void UpdateDirection(int direction)
	{
		m_iCurrentMenuItem -= direction;
		PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_pstop, "0 0 0");
		if (m_iCurrentMenuItem < 0)
			m_iCurrentMenuItem = m_aOptionsList.Count();
		if (m_iCurrentMenuItem > m_aOptionsList.Count())
			m_iCurrentMenuItem = 0;
	}

	void PS_DOptionsSubMenu(PS_DMainMenu dMainMenu, PS_DMain dMain)
	{
		m_aOptionsList.Insert(new PS_DOptionEddsMode("Edds draw mode"));
	}
}

class PS_DOption
{
	string m_sName;

	void Activate();
	string GetName()
		return m_sName;

	void PS_DOption(string name)
	{
		m_sName = name;
	}
}

class PS_DOptionEddsMode : PS_DOption
{
	override string GetName()
	{
		string name = m_sName;
		if (PS_DEddsTexture.s_bEddsMode)
			name += " +";
		else
			name += " -";
		return name;
	}

	override void Activate()
	{
		PS_DEddsTexture.SwitchDrawMode();
	}
}

class PS_DSaveSubMenu : PS_DSubMenu
{
	ref array<string> m_aSaveFiles;

	static const string SAVES_PATH = "$profile:DE/Saves/";
	static const string SAVES_EXT = ".dsv";

	static const int SAVE_PREVIEW_WIDTH = PS_DConst.SAVE_PREVIEW_WIDTH;
	static const int SAVE_PREVIEW_HEIGHT = PS_DConst.SAVE_PREVIEW_HEIGHT;
	static const int SAVE_PREVIEW_SIZE = PS_DConst.SAVE_PREVIEW_SIZE;

	bool m_bSaveMode;

	int m_aPreviewPixels[SAVE_PREVIEW_SIZE];

	bool m_bEditing;
	EditBoxWidget m_EditBox;

	override bool Back()
	{
		if (m_bEditing)
		{
			m_bEditing = false;
			m_EditBox.RemoveFromHierarchy();
			return false;
		}
		return true;
	}

	override void Return()
	{
		if (m_bEditing)
		{
			m_bEditing = false;

			string saveName = m_EditBox.GetText();
			string saveFile = SAVES_PATH + saveName + SAVES_EXT;

			if (m_iCurrentMenuItem != 1)
			{
				FileIO.DeleteFile(m_aSaveFiles[m_iCurrentMenuItem - 1]);
			}

			m_DMain.m_bInMenu = false;
			m_DMain.m_iFrameNum++;
			m_DMain.m_DRenderer.DrawFrame();
			m_DMain.m_bInMenu = true;
			PS_DSave.Save(m_DMain, saveFile);

			Open();
			m_DMain.Update(0);

			m_EditBox.RemoveFromHierarchy();
		}
		else
			Activate();
	}

	override void Activate()
	{
		if (!m_bSaveMode)
			PS_DSave.LoadTransfer(m_DMain, m_aSaveFiles[m_iCurrentMenuItem - 1]);
		else
		{
			if (m_bEditing)
			{
				return;
			}
			else
			{
				m_bEditing = true;
				if (!m_EditBox)
				{
					m_EditBox = EditBoxWidget.Cast(GetGame().GetWorkspace().CreateWidget(WidgetType.EditBoxWidgetTypeID, WidgetFlags.VISIBLE, Color.White, 10000));
				}
				GetGame().GetWorkspace().SetFocusedWidget(m_EditBox);
				m_EditBox.ActivateWriteMode();

				string saveFile = m_aSaveFiles[m_iCurrentMenuItem - 1];
				string saveName = saveFile.Substring(SAVES_PATH.Length(), saveFile.Length() - SAVES_PATH.Length() - SAVES_EXT.Length());
				if (m_iCurrentMenuItem == 1)
					saveName = "";
				m_EditBox.SetText(saveName);
			}
		}
	}

	override void Open()
	{
		m_bEditing = false;
		m_aSaveFiles = {};
		if (m_bSaveMode)
			m_aSaveFiles.Insert("$profile:DE/Saves/<New save>.dsv");
		FileIO.FindFiles(m_aSaveFiles.Insert, SAVES_PATH, SAVES_EXT);
		UpdatePreview();
	}

	override void UpdateDirection(int direction)
	{
		if (m_bEditing)
			return;

		m_iCurrentMenuItem -= direction;
		PS_DSoundEffect.PlaySound(PS_EDSoundFX.sfx_pstop, "0 0 0");
		if (m_iCurrentMenuItem < 1)
			m_iCurrentMenuItem = m_aSaveFiles.Count() - 1;
		if (m_iCurrentMenuItem > m_aSaveFiles.Count())
			m_iCurrentMenuItem = 1;
		UpdatePreview();
	}

	void UpdatePreview()
	{
		int saveNum = m_iCurrentMenuItem - 1;
		if (m_bSaveMode)
			saveNum--;

		bool saveSelected = saveNum < m_aSaveFiles.Count() && saveNum >= 0;
		if (!saveSelected)
			for (int i = 0; i < SAVE_PREVIEW_SIZE; i++) // TODO memcopy
				m_aPreviewPixels[i] = 0;
		else
		{
			PS_DSave.LoadPreview(m_aSaveFiles[m_iCurrentMenuItem - 1], m_aPreviewPixels);
		}
	}

	override void Draw()
	{
		DrawBox(15, 15, 145, 90, Color.RED); // Preview box
		DrawBox(15, 110, 145, 65, Color.RED); // Description box
		DrawBox(165, 15, 140, 160, Color.RED); // Saves box

		DrawPreview(16, 16);
		DrawSaves();
	}

	void DrawPreview(int xo, int yo)
	{
		for (int x = 0; x < SAVE_PREVIEW_WIDTH; x++)
		{
			for (int y = 0; y < SAVE_PREVIEW_HEIGHT; y++)
			{
				int previewIndex = x + y * SAVE_PREVIEW_WIDTH;
				int pixelIndex = (x + xo) + (y + yo) * PS_DConst.SCREEN_WIDTH;
				PS_DEddsTexture.m_aPixels[pixelIndex] = m_aPreviewPixels[previewIndex];
			}
		}
	}

	void DrawSaves()
	{
		PS_DAssets assets = PS_DMain.s_DMain.m_DWAD.m_DAssets;
		int y = 16;
		int i = 0;
		foreach (string saveFile : m_aSaveFiles)
		{
			if ((m_iCurrentMenuItem - 1) == i)
			{
				assets.FillBox(166, y, 138, 8, Color.ORANGE);
			}

			string saveName = saveFile.Substring(SAVES_PATH.Length(), saveFile.Length() - SAVES_PATH.Length() - SAVES_EXT.Length());
			if (m_bEditing && ((m_iCurrentMenuItem - 1) == i))
			{
				FilterEditBox();
				saveName = m_EditBox.GetText() + "_";
			}
			assets.DrawText(167, y + 1, saveName, 0);
			y += 8;
			i++;
		}
	}

	// FIXME: Another overkill
	void FilterEditBox()
	{
		string text = m_EditBox.GetText();
		if (text.Length() > 20)
			text = text.Substring(0, 20);

		text.ToUpper();
		string filteredText;
		for (int i = 0; i < text.Length(); i++)
		{
			string char = text[i];
			if (SCR_StringHelper.UPPERCASE.Contains(char))
			{
				filteredText += char;
				continue;
			}
			if (" 0123456789_".Contains(char))
			{
				filteredText += char;
				continue;
			}
		}
		m_EditBox.SetText(filteredText);
	}

	void DrawBox(int x, int y, int w, int h, int color)
	{
		int startOffsetY1 = x + y * PS_DConst.SCREEN_WIDTH;
		int startOffsetY2 = x + (y + h - 1) * PS_DConst.SCREEN_WIDTH;
		for (int i = 0; i < w; i++)
		{
			PS_DEddsTexture.m_aPixels[i + startOffsetY1] = color;
			PS_DEddsTexture.m_aPixels[i + startOffsetY2] = color;
		}
		for (int i = 1; i < h; i++)
		{
			PS_DEddsTexture.m_aPixels[(x) + (y + i) * PS_DConst.SCREEN_WIDTH] = color;
			PS_DEddsTexture.m_aPixels[(x + w - 1) + (y + i) * PS_DConst.SCREEN_WIDTH] = color;
		}
	}

	void ~PS_DSaveSubMenu()
	{
		if (m_EditBox)
			m_EditBox.RemoveFromHierarchy();
	}
}
