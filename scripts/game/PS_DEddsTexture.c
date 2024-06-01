class PS_DEddsTexture
{
	static PS_DEddsTexture s_DEddsTexture;
	
	// texture size
	static const int SCREEN_WIDTH = PS_DConst.SCREEN_WIDTH;
	static const int SCREEN_HEIGHT = PS_DConst.SCREEN_HEIGHT;
	static const int SCREEN_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT;
	
	// Widgets
	static Widget m_wDRoot;           // Root of canvas
	static ImageWidget m_wEddsCanvas; // Image for displaying our render result
	static CanvasWidget m_w2DCanvas;  // 2D stuff mostly debug (TODO: 2d map)
	static CanvasWidget m_w3DCanvas;  // 3D slow, but disc friendly
	
	// "Engine" of our game
	ref PS_DMain m_DMain;
	
	ref array<int> m_aEddsHeader = {};           // Cached edds file header
	static int m_aPixels[SCREEN_SIZE];           // Can be memcopyed
	static ref array<int> m_aPixelsForFile = {}; // Can't be memcopyed, but can be fast written to file
	
	ref array<ref LineDrawCommand> m_aLineCommands;
	ref array<ref CanvasWidgetCommand> m_aDrawCommands;
	
	int m_iFrameNum; // OUR frame num
	
	static bool s_bEddsMode = false;
	
	static void SwitchDrawMode()
	{
		s_bEddsMode = !s_bEddsMode;
		PS_DMain.s_DMain.m_DWAD.m_DAssets.SwitchPallet(s_bEddsMode);
		if (!s_bEddsMode)
			s_DEddsTexture.m_w3DCanvas.SetDrawCommands(s_DEddsTexture.m_aDrawCommands);
		else
			s_DEddsTexture.m_w3DCanvas.SetDrawCommands(null);
		s_DEddsTexture.m_DMain.m_DInterface.m_CurrentPallete = null;
	}
	
	//------------------------------------------------------------------------------------------------
	// Write byte array to file, and load as texture
	void FlushScreen()
	{
		if (s_bEddsMode)
			FlushScreenEdds();
		else
			FlushScreenCanvas();
		
		m_iFrameNum++;
	}
	
	void FlushScreenEdds()
	{
		FileHandle fileHandleW = FileIO.OpenFile("$profile:EddsCanvas/f" + (m_iFrameNum&1) + ".edds", FileMode.WRITE);
		fileHandleW.WriteArray(m_aEddsHeader);
		m_aPixelsForFile.Init(m_aPixels);
		fileHandleW.WriteArray(m_aPixelsForFile);
		fileHandleW.Close();
		m_wEddsCanvas.LoadImageTexture(0, "$profile:EddsCanvas/f" + (((m_iFrameNum)&1)^1) + ".edds", true, true);
	}
	
	void FlushScreenCanvas()
	{
		if (!m_aLineCommands)
			return;
		
		for (int p = 0; p < SCREEN_SIZE;)
		{
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
			m_aLineCommands[p].m_iColor = m_aPixels[p]; p++;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	// Need to be called from outer scope
	static const float TICK_DELAY = 28;
	float m_fTickTime;
	void Update(float timeSlice)
	{
		s_DEddsTexture = this;
		
		m_fTickTime += timeSlice * 1000;
		if (m_fTickTime < TICK_DELAY) // Skip, same frame
			return;
		m_fTickTime = Math.Repeat(m_fTickTime, TICK_DELAY);
		
		m_DMain.Update(timeSlice);
		FlushScreen();
	}
	
	//------------------------------------------------------------------------------------------------
	void PS_DEddsTexture(Widget dRoot)
	{
		m_wDRoot = dRoot;
		m_wEddsCanvas = ImageWidget.Cast(dRoot.FindAnyWidget("EddsCanvas"));
		m_w2DCanvas = CanvasWidget.Cast(dRoot.FindAnyWidget("2DCanvas"));
		m_w3DCanvas = CanvasWidget.Cast(dRoot.FindAnyWidget("3DCanvas"));
	}
	
	//------------------------------------------------------------------------------------------------
	void EOnInit(IEntity owner)
	{
		// Create engine instance
		m_DMain = new PS_DMain();
		m_DMain.m_DWAD.m_DAssets.SwitchPallet(s_bEddsMode);
		
		// read edds header (TODO: prebake)
		FileHandle fileHandleR = FileIO.OpenFile("$profile:EddsCanvas/0000-0000.edds", FileMode.READ);
		fileHandleR.ReadArray(m_aEddsHeader, 4, 39);
		
		GetGame().GetCallqueue().Call(InitCanvas);
		
		// Init flush, skip old buffered frame
		FlushScreen();
	}
	
	void InitCanvas()
	{
		float pixelWidth, pixelHeight;
		m_wEddsCanvas.GetScreenSize(pixelWidth, pixelHeight);
		if (pixelWidth == 0)
		{
			GetGame().GetCallqueue().Call(InitCanvas);
			return;
		}
		m_aLineCommands = {};
		m_aDrawCommands = {};
		
		pixelWidth /= (float)PS_DConst.SCREEN_WIDTH;
		pixelHeight /= (float)PS_DConst.SCREEN_HEIGHT;
		for (int y = 0; y < PS_DConst.SCREEN_HEIGHT; y++)
		{
			for (int x = 0; x < PS_DConst.SCREEN_WIDTH; x++)
			{
				LineDrawCommand lineDrawCommand = new LineDrawCommand();
				
				lineDrawCommand.m_Vertices = {
					pixelWidth * x, pixelHeight * y + pixelWidth/2,
					pixelWidth * x + pixelWidth, pixelHeight * y + pixelWidth/2
				};
				lineDrawCommand.m_fWidth = pixelWidth;
				lineDrawCommand.m_iColor = Color.RED;
				
				m_aLineCommands.Insert(lineDrawCommand);
				m_aDrawCommands.Insert(lineDrawCommand);
			}
		}
		if (!s_bEddsMode)
			m_w3DCanvas.SetDrawCommands(m_aDrawCommands);
	}
}