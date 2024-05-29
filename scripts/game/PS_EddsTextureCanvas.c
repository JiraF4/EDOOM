class PS_EddsTextureCanvasComponent
{
	static Widget m_wDRoot;
	static ImageWidget m_wEddsCanvas;
	static CanvasWidget m_w2DCanvas;
	
	ref array<int> m_aEddsHeader = {};
	
	ref PS_DMain m_DMain;
	
	static const int SCREEN_WIDTH = PS_DConst.SCREEN_WIDTH;
	const static int SCREEN_HEIGHT = PS_DConst.SCREEN_HEIGHT;
	const static int SCREEN_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT;
	static int m_aPixels[SCREEN_SIZE]; 
	static ref array<int> m_aPixelsForFile = {};
	
	bool m_bSkipFirst;
	
	//------------------------------------------------------------------------------------------------
	void FlushScreen()
	{
		int frame = GetGame().GetWorld().GetFrameNumber();
		FileHandle fileHandleW = FileIO.OpenFile("$profile:EddsCanvas/f" + Math.Mod(frame, 2) + ".edds", FileMode.WRITE);
		fileHandleW.WriteArray(m_aEddsHeader);
		m_aPixelsForFile.Init(m_aPixels);
		fileHandleW.WriteArray(m_aPixelsForFile);
		fileHandleW.Close();
		if (m_bSkipFirst)
			m_wEddsCanvas.LoadImageTexture(0, "$profile:EddsCanvas/f" + Math.Mod(frame+1, 2) + ".edds", true, true);
		m_bSkipFirst = true;
	}
	
	//------------------------------------------------------------------------------------------------
	void EOnFrame(IEntity owner, float timeSlice)
	{
		m_DMain.Update(timeSlice);
		FlushScreen();
	}
	
	//------------------------------------------------------------------------------------------------
	void PS_EddsTextureCanvasComponent(Widget dRoot)
	{
		m_wDRoot = dRoot;
		m_wEddsCanvas = ImageWidget.Cast(dRoot.FindAnyWidget("EddsCanvas"));
		m_w2DCanvas = CanvasWidget.Cast(dRoot.FindAnyWidget("2DCanvas"));
	}
	
	//------------------------------------------------------------------------------------------------
	void EOnInit(IEntity owner)
	{
		m_DMain = new PS_DMain();
		
		/*
		m_wImage = ImageWidget.Cast(GetGame().GetWorkspace().CreateWidget(WidgetType.ImageWidgetTypeID,  WidgetFlags.VISIBLE | WidgetFlags.STRETCH | WidgetFlags.NOFILTER, Color.White, 0));
		FrameSlot.SetSize(m_wImage, 1920, 1200);
		m_wImage.SetSize(SCREEN_HEIGHT,SCREEN_WIDTH);
		*/
		
		FileHandle fileHandleR = FileIO.OpenFile("$profile:EddsCanvas/0000-0000.edds", FileMode.READ);
		fileHandleR.ReadArray(m_aEddsHeader, 4, 39);
	}
}