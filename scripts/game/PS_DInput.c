class PS_DInput
{
	InputManager m_InputManager;
	
	float m_fAim;
	float m_fForward;
	float m_fRight;
	int m_iWeaponSlot = -1;
	float m_fAction;
	float m_fFire;
	float m_fMap;
	float m_fESC;
	float m_fQS;
	float m_fQL;
	float m_fBack;
	float m_fENT;
	
	bool m_bPlayDemo;
	bool m_bWriteDemo;
	int m_iDemoPos;
	
	void UpdateValues()
	{
		m_fAim = m_InputManager.GetActionValue("DAim") * 0.05 + m_InputManager.GetActionValue("DAimGamepade") * 0.1;
		m_fForward = m_InputManager.GetActionValue("DForward");
		m_fRight = m_InputManager.GetActionValue("DRight");
	}
	
	void UpdateDemo()
	{
		if (m_bPlayDemo)
		{
			FileHandle demoFile = FileIO.OpenFile("$profile:DE/demo.dsm", FileMode.READ);
			demoFile.Seek(m_iDemoPos);
			
			demoFile.Read(m_fAim, 4);
			demoFile.Read(m_fForward, 4);
			demoFile.Read(m_fRight, 4);
			demoFile.Read(m_iWeaponSlot, 4);
			demoFile.Read(m_fAction, 4);
			demoFile.Read(m_fFire, 4);
			
			m_iDemoPos += 24;
		} else {
			if (m_bWriteDemo)
			{
				FileHandle demoFile = FileIO.OpenFile("$profile:DE/demo.dsm", FileMode.APPEND);
				demoFile.Write(m_fAim, 4);
				demoFile.Write(m_fForward, 4);
				demoFile.Write(m_fRight, 4);
				demoFile.Write(m_iWeaponSlot, 4);
				demoFile.Write(m_fAction, 4);
				demoFile.Write(m_fFire, 4);
			}
		}
	}
	
	void PlayDemo()
	{
		m_bPlayDemo = true;
	}
	
	void ResetDemo()
	{
		FileIO.OpenFile("$profile:DE/demo.dsm", FileMode.WRITE);
		m_bWriteDemo = true;
	}
	
	void ResetInput()
	{
		m_fAction = 0;
		if (!m_InputManager.GetActionValue("DFire"))
			m_fFire = 0;
		m_iWeaponSlot = -1;
		m_fQS = 0;
		m_fQL = 0;
		if (!m_InputManager.GetActionValue("DMap"))
			m_fMap = 0;
		m_fESC = 0;
		m_fBack = 0;
		m_fENT = 0;
	}
	
	void Init()
	{
		m_InputManager = GetGame().GetInputManager();
		
		m_InputManager.AddActionListener("DAction", EActionTrigger.DOWN, DAction);
		m_InputManager.AddActionListener("DFire", EActionTrigger.DOWN, DFire);
		m_InputManager.AddActionListener("DW1", EActionTrigger.DOWN, DW1);
		m_InputManager.AddActionListener("DW2", EActionTrigger.DOWN, DW2);
		m_InputManager.AddActionListener("DW3", EActionTrigger.DOWN, DW3);
		m_InputManager.AddActionListener("DW4", EActionTrigger.DOWN, DW4);
		m_InputManager.AddActionListener("DW5", EActionTrigger.DOWN, DW5);
		m_InputManager.AddActionListener("DW6", EActionTrigger.DOWN, DW6);
		m_InputManager.AddActionListener("DW7", EActionTrigger.DOWN, DW7);
		m_InputManager.AddActionListener("DMap", EActionTrigger.DOWN, DMap);
		m_InputManager.AddActionListener("DESC", EActionTrigger.DOWN, DESC);
		m_InputManager.AddActionListener("DQL", EActionTrigger.DOWN, DQL);
		m_InputManager.AddActionListener("DBACK", EActionTrigger.DOWN, DBACK);
		m_InputManager.AddActionListener("DENT", EActionTrigger.DOWN, DENT);
	}
	
	void DAction()
	{
		m_fAction = 1;
	}
	void DFire()
	{
		m_fFire = 1;
	}
	void DW1()
	{
		m_iWeaponSlot = 0;
	}
	void DW2()
	{
		m_iWeaponSlot = 1;
	}
	void DW3()
	{
		m_iWeaponSlot = 2;
	}
	void DW4()
	{
		m_iWeaponSlot = 3;
	}
	void DW5()
	{
		m_iWeaponSlot = 4;
	}
	void DW6()
	{
		m_iWeaponSlot = 5;
	}
	void DW7()
	{
		m_iWeaponSlot = 6;
	}
	void DMap()
	{
		m_fMap = 1;
	}
	void DESC()
	{
		m_fESC = 1;
	}
	void DQS()
	{
		m_fQS = 1;
	}
	void DQL()
	{
		m_fQL = 1;
	}
	void DBACK()
	{
		m_fBack = 1;
	}
	void DENT()
	{
		m_fENT = 1;
	}
}