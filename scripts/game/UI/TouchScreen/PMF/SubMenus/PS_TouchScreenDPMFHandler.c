class PS_TouchScreenDPMFHandler : RHS_TouchScreenMenuPMFSubHandler
{
	protected RHS_VehiclePMFScreenComponent m_VehiclePMFScreenComponent;
	
	protected ref PS_EddsTextureCanvasComponent m_EddsTextureCanvasComponent;
	RHS_TouchScreenMenuPMFDrongOSHandler m_DrongOSHandler;
	SCR_CharacterCameraHandlerComponent m_CharacterCameraHandler;
	RHS_CustomCameraPointInfo m_CustomCameraPointInfo;
	
	protected ref array<string> m_aBootText = {};
	protected int m_iBootTextCount;
	
	override void HandlerAttached(Widget w)
	{
		super.HandlerAttached(w);
	}
	
	void InitPMF(RHS_VehiclePMFScreenComponent VehiclePMFScreenComponent)
	{
		m_VehiclePMFScreenComponent = VehiclePMFScreenComponent;
		m_EddsTextureCanvasComponent = new PS_EddsTextureCanvasComponent(m_wRoot);
		m_EddsTextureCanvasComponent.EOnInit(VehiclePMFScreenComponent.GetOwner());
		
		IEntity character = SCR_PlayerController.GetLocalMainEntity();
		if (character)
		{
			m_CharacterCameraHandler = SCR_CharacterCameraHandlerComponent.Cast(character.FindComponent(SCR_CharacterCameraHandlerComponent));
			m_CustomCameraPointInfo = m_CharacterCameraHandler.RHS_GetCustomPointInfo();
		}
	}
	
	
	override void OnWidgetUpdate(float timeSlice)
	{
		super.OnWidgetUpdate(timeSlice);
		
		RHS_CustomCameraPointInfo customCameraPointInfo = m_CharacterCameraHandler.RHS_GetCustomPointInfo();
		if (!m_CustomCameraPointInfo)
			m_CustomCameraPointInfo = customCameraPointInfo;
		else if (customCameraPointInfo == m_CustomCameraPointInfo)
			GetGame().GetInputManager().ActivateContext("DContext");
		
		if (m_EddsTextureCanvasComponent.m_DMain.m_bClose)
		{
			m_EddsTextureCanvasComponent = null;
			
			m_DrongOSHandler.CloseD();
		}
		
		if (m_EddsTextureCanvasComponent)
		{
			m_EddsTextureCanvasComponent.EOnFrame(m_VehiclePMFScreenComponent.GetOwner(), timeSlice);
		}
	}
}
