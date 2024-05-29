class PS_DInput
{
	InputManager m_InputManager;
	
	float m_fAim;
	float m_fForward;
	float m_fRight;
	int m_iWeaponSlot = -1;
	float m_fAction;
	float m_fFire;
	
	bool m_bPlayDemo;
	bool m_bWriteDemo;
	int m_iDemoPos;
	
	void Update()
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
			m_fAim = m_InputManager.GetActionValue("DAim") * 0.00005 + m_InputManager.GetActionValue("DAimGamepade") * 0.1;
			m_fForward = m_InputManager.GetActionValue("DForward");
			m_fRight = m_InputManager.GetActionValue("DRight");
			m_fAction = m_InputManager.GetActionValue("DAction");
			m_fFire = m_InputManager.GetActionValue("DFire");
			
			if (m_InputManager.GetActionTriggered("DW7"))
				m_iWeaponSlot = 6;
			else if (m_InputManager.GetActionTriggered("DW6"))
				m_iWeaponSlot = 5;
			else if (m_InputManager.GetActionTriggered("DW5"))
				m_iWeaponSlot = 4;
			else if (m_InputManager.GetActionTriggered("DW4"))
				m_iWeaponSlot = 3;
			else if (m_InputManager.GetActionTriggered("DW3"))
				m_iWeaponSlot = 2;
			else if (m_InputManager.GetActionTriggered("DW2"))
				m_iWeaponSlot = 1;
			else if (m_InputManager.GetActionTriggered("DW1"))
				m_iWeaponSlot = 0;
			else
				m_iWeaponSlot = -1;
			
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
	
	void Init()
	{
		m_InputManager = GetGame().GetInputManager();
	}
}