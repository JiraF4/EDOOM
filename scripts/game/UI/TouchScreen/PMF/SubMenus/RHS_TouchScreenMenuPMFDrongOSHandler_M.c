/*
modded class RHS_TouchScreenMenuPMFDrongOSHandler
{
	protected FrameWidget m_wDFrame;
	protected ImageWidget m_wImage;
	protected FrameWidget m_wFrame;
	PS_TouchScreenDPMFHandler m_TouchScreenDPMFHandler;
	
	override void HandlerAttached(Widget w)
	{
		m_wDFrame = FrameWidget.Cast(w.FindAnyWidget("DRoot"));
		m_wImage = ImageWidget.Cast(w.FindAnyWidget("Image"));
		m_wFrame = FrameWidget.Cast(w.FindAnyWidget("Frame"));
		
		m_TouchScreenDPMFHandler = PS_TouchScreenDPMFHandler.Cast(m_wDFrame.FindHandler(PS_TouchScreenDPMFHandler));
		
		super.HandlerAttached(w);

		RegistrateButton("ButtonD").GetOnDoubleClick().Insert(ButtonD);
	}
	
	override void OnWidgetUpdate(float timeSlice)
	{
		super.OnWidgetUpdate(timeSlice);
		if (m_wDFrame.IsVisible())
			m_TouchScreenDPMFHandler.OnWidgetUpdate(timeSlice);
	}

	void ButtonD(Widget widget, RHS_TouchScreenWidgetHandler handler)
	{
		m_RpcManager.AskAuthorityToSyncPMFCurrentDrongOSMenu(m_VehiclePMFScreenComponent, 5);
	}
	
	override void SetDrongOSMenu(int num)
	{
		m_wDFrame.SetVisible(false);
		
		if (num == 5)
		{
			m_wRoot.GetParent().FindAnyWidget("Cursor").SetVisible(false);
			m_wRoot.GetParent().FindAnyWidget("PMFCursor").SetVisible(false);
			
			m_wWordWindow.SetVisible(false);
			m_wFloppyTOverlay.SetVisible(false);
			m_wFrame.SetVisible(false);
			
			m_TouchScreenDPMFHandler.InitPMF(m_VehiclePMFScreenComponent);
			m_TouchScreenDPMFHandler.m_DrongOSHandler = this;
			
			m_wDFrame.SetVisible(true);
			m_wImage.SetVisible(false);
			return;
		}
		
		super.SetDrongOSMenu(num);
	}
	
	void CloseD()
	{
		m_wRoot.GetParent().FindAnyWidget("Cursor").SetVisible(true);
		m_wRoot.GetParent().FindAnyWidget("PMFCursor").SetVisible(true);
		m_wWordWindow.SetVisible(true);
		m_wFloppyTOverlay.SetVisible(true);
		m_wFrame.SetVisible(true);
		m_wDFrame.SetVisible(false);
		m_wImage.SetVisible(true);
		m_RpcManager.AskAuthorityToSyncPMFCurrentDrongOSMenu(m_VehiclePMFScreenComponent, 0)
	}
}
*/
