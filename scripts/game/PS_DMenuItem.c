class PS_DMenuItem
{
	PS_DMainMenu m_DMainMenu;
	PS_DAssets m_DAssets;
	PS_DPatch m_DPatch;
	
	PS_DSubMenu m_NextMenu;
	
	string m_sPatchName;
	
	void Activate()
	{
		
	}
	
	void PS_DMenuItem(PS_DMainMenu dMainMenu, PS_DAssets dAssets, string patchName, PS_DSubMenu nextMenu = null)
	{
		m_DMainMenu = dMainMenu;
		m_DAssets = dAssets;
		m_NextMenu = nextMenu;
		
		m_sPatchName = patchName;
		m_DPatch = dAssets.m_mPatches[patchName];
	}
}

class PS_DLoadMenuItem : PS_DMenuItem
{
	override void Activate()
	{
		m_DMainMenu.m_SaveMenu.m_bSaveMode = false;
	}
}

class PS_DSaveMenuItem : PS_DMenuItem
{
	override void Activate()
	{
		m_DMainMenu.m_SaveMenu.m_bSaveMode = true;
	}
}

class PS_DExitMenuItem : PS_DMenuItem
{
	override void Activate()
	{
		m_DMainMenu.m_DMain.Close();
	}
}