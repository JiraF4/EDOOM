[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class PS_DFullScreenComponentClass : ScriptComponentClass
{
}


class PS_DFullScreenComponent : ScriptComponent
{
	ref PS_DEddsTexture m_DEddsTexture;
	
	Widget m_wDRoot;
	
	//------------------------------------------------------------------------------------------------
	override void EOnFrame(IEntity owner, float timeSlice)
	{
		GetGame().GetInputManager().ActivateContext("DContext");
		if (m_DEddsTexture.m_DMain.m_bClose)
		{
			m_DEddsTexture = null;
			m_wDRoot.RemoveFromHierarchy();
			ClearEventMask(owner, EntityEvent.FRAME | EntityEvent.INIT);
		}
		else
			m_DEddsTexture.Update(timeSlice);
	}
	
	override void EOnInit(IEntity owner)
	{
		if (!GetGame().InPlayMode())
			return;
		
		m_wDRoot = GetGame().GetWorkspace().CreateWidgets("{87B9FB9C5D2593F4}UI/DScreen.layout");
		
		m_DEddsTexture = new PS_DEddsTexture(m_wDRoot);
		m_DEddsTexture.EOnInit(owner);
		for (int i = 0; i < PS_DConst.SCREEN_WIDTH; i++)
			m_DEddsTexture.m_DMain.m_aPixelsOffset[i] = PS_DConst.SCREEN_HEIGHT;
		
		m_DEddsTexture.m_DMain.m_iDifficulty = 2;
		m_DEddsTexture.m_DMain.m_iCurrentLevel = 0;
		m_DEddsTexture.m_DMain.LoadLevel("E1M1");
		m_DEddsTexture.m_DMain.m_CurrentGameState = PS_DGameState.GS_LEVEL;
		for (int i = 0; i < PS_DConst.SCREEN_WIDTH; i++)
			m_DEddsTexture.m_DMain.m_aPixelsOffset[i] = PS_DConst.SCREEN_HEIGHT;
		
		/*
		m_DEddsTexture.m_DMain.m_EntityPlayer.m_iHealth = 999999;
		
		m_DEddsTexture.m_DMain.m_EntityPlayer.m_aAmmo[0] = 500;
		m_DEddsTexture.m_DMain.m_EntityPlayer.m_aAmmo[1] = 500;
		m_DEddsTexture.m_DMain.m_EntityPlayer.m_aAmmo[2] = 500;
		m_DEddsTexture.m_DMain.m_EntityPlayer.m_aAmmo[3] = 500;
		
		m_DEddsTexture.m_DMain.m_EntityPlayer.m_aWeapons[2] = true;
		m_DEddsTexture.m_DMain.m_EntityPlayer.m_aWeapons[3] = true;
		m_DEddsTexture.m_DMain.m_EntityPlayer.m_aWeapons[4] = true;
		m_DEddsTexture.m_DMain.m_EntityPlayer.m_aWeapons[7] = true;
		
		m_DEddsTexture.m_DMain.m_EntityPlayer.m_iFlags |= PS_EDMobjFlag.MF_NOCLIP;
		*/
		
		//m_DEddsTexture.m_DMain.m_DInput.ResetDemo();
		//m_DEddsTexture.m_DMain.m_DInput.PlayDemo();
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.FRAME | EntityEvent.INIT);
	}
}