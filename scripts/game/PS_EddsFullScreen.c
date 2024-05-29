[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class PS_DFullScreenComponentClass : ScriptComponentClass
{
}


class PS_DFullScreenComponent : ScriptComponent
{
	ref PS_EddsTextureCanvasComponent m_EddsTextureCanvasComponent;
	
	Widget m_wDRoot;
	
	//------------------------------------------------------------------------------------------------
	override void EOnFrame(IEntity owner, float timeSlice)
	{
		GetGame().GetInputManager().ActivateContext("DContext");
		if (m_EddsTextureCanvasComponent.m_DMain.m_bClose)
		{
			m_EddsTextureCanvasComponent = null;
			m_wDRoot.RemoveFromHierarchy();
			ClearEventMask(owner, EntityEvent.FRAME | EntityEvent.INIT);
		}
		else
			m_EddsTextureCanvasComponent.EOnFrame(owner, timeSlice);
	}
	
	override void EOnInit(IEntity owner)
	{
		if (!GetGame().InPlayMode())
			return;
		
		m_wDRoot = GetGame().GetWorkspace().CreateWidgets("{87B9FB9C5D2593F4}UI/DScreen.layout");
		
		m_EddsTextureCanvasComponent = new PS_EddsTextureCanvasComponent(m_wDRoot);
		m_EddsTextureCanvasComponent.EOnInit(owner);
		for (int i = 0; i < PS_DConst.SCREEN_WIDTH; i++)
			m_EddsTextureCanvasComponent.m_DMain.m_aPixelsOffset[i] = PS_DConst.SCREEN_HEIGHT;
		
		m_EddsTextureCanvasComponent.m_DMain.m_iDifficulty = 2;
		m_EddsTextureCanvasComponent.m_DMain.m_iCurrentLevel = 0;
		m_EddsTextureCanvasComponent.m_DMain.LoadLevel("E1M2");
		m_EddsTextureCanvasComponent.m_DMain.m_CurrentGameState = PS_DGameState.GS_LEVEL;
		for (int i = 0; i < PS_DConst.SCREEN_WIDTH; i++)
			m_EddsTextureCanvasComponent.m_DMain.m_aPixelsOffset[i] = PS_DConst.SCREEN_HEIGHT;
		
		/*
		m_EddsTextureCanvasComponent.m_DMain.m_EntityPlayer.m_iHealth = 999999;
		
		m_EddsTextureCanvasComponent.m_DMain.m_EntityPlayer.m_aAmmo[0] = 500;
		m_EddsTextureCanvasComponent.m_DMain.m_EntityPlayer.m_aAmmo[1] = 500;
		m_EddsTextureCanvasComponent.m_DMain.m_EntityPlayer.m_aAmmo[2] = 500;
		m_EddsTextureCanvasComponent.m_DMain.m_EntityPlayer.m_aAmmo[3] = 500;
		
		m_EddsTextureCanvasComponent.m_DMain.m_EntityPlayer.m_aWeapons[2] = true;
		m_EddsTextureCanvasComponent.m_DMain.m_EntityPlayer.m_aWeapons[3] = true;
		m_EddsTextureCanvasComponent.m_DMain.m_EntityPlayer.m_aWeapons[4] = true;
		m_EddsTextureCanvasComponent.m_DMain.m_EntityPlayer.m_aWeapons[7] = true;
		
		m_EddsTextureCanvasComponent.m_DMain.m_EntityPlayer.m_iFlags |= PS_EDMobjFlag.MF_NOCLIP;
		*/
		
		//m_EddsTextureCanvasComponent.m_DMain.m_DInput.ResetDemo();
		//m_EddsTextureCanvasComponent.m_DMain.m_DInput.PlayDemo();
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.FRAME | EntityEvent.INIT);
	}
}