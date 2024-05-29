class PS_DEndingScreen
{
	PS_DMain m_DMain;
	PS_DAssets m_DAssets;
	
	// Ticks
	int m_iTickNum;
	static const float TICK_DELAY = 28;
	float m_fLastTickTime;
	
	PS_DPalette m_Pallete;
	PS_DTextureFlat m_BackgroundFlat;
	
	ref array<PS_DPatch> m_aSTCFN = {}; // ASCII chars
	
	int m_iLastChar = 0;
	
	void Draw()
	{
		FillScreen();
		DrawText();
	}
	
	void FillScreen()
	{
		for (int x = 0; x < PS_DConst.SCREEN_WIDTH; x++)
		{
			for (int y = 0; y < PS_DConst.SCREEN_HEIGHT; y++)
			{
				int indexTexture = (x & 63) + (y & 63) * 64;
				int indexScreen = x + y * PS_DConst.SCREEN_WIDTH;
				int colorIndex = m_BackgroundFlat.m_Pixels.m_aPixels[indexTexture];
				PS_EddsTextureCanvasComponent.m_aPixels[indexScreen] = m_Pallete.m_aColors[colorIndex];
			}
		}
	}
	
	void DrawText()
	{
		int x = 4;
		int y = 32;
		
		string text = PS_DMessages.E1TEXT;
		text.ToUpper();
		int length = Math.Min(m_iLastChar, text.Length());
		for (int i = 0; i < length; i++)
		{
			int char = text.ToAscii(i);
			if (char == 10)
			{
				x = 4;
				y += 8;
				continue;
			}
			
			PS_DPatch charPatch = m_aSTCFN[char];
			if (charPatch)
			{
				DrawPatch(x, y, charPatch);
				x += charPatch.m_DPatchHeader.m_iWidth;
			}
			if (char == 32)
				x += 6;
		}
	}
	
	void DrawPatch(int x, int y, PS_DPatch patch)
	{
		PS_DPalette pallete = m_DAssets.m_aPalletes[0];
		x -= patch.m_DPatchHeader.m_iLeftOffset;
		y -= patch.m_DPatchHeader.m_iTopOffset;
		int width = patch.m_DPatchHeader.m_iWidth;
		int height = patch.m_DPatchHeader.m_iHeight;
		int x2 = x + width;
		int y1 = y;
		int y2 = y + height;
		int xp = 0;
		for (x; x < x2; x++)
		{
			int yp = 0;
			for (y = y1; y < y2; y++)
			{
				int colorIndex = patch.m_DTexture.m_aPixels[xp + yp * width];
				if (colorIndex != 256)
				{
					int color = pallete.m_aColors[colorIndex];
					int pixelIndex = x + y * PS_DConst.SCREEN_WIDTH;
					if (pixelIndex < PS_EddsTextureCanvasComponent.SCREEN_SIZE)
						PS_EddsTextureCanvasComponent.m_aPixels[pixelIndex] = color;
				}
				yp++;
			}
			xp++;
		}
	}
	
	void Update()
	{
		float updateTime = GetGame().GetWorld().GetWorldTime();
		
		while (updateTime - TICK_DELAY > m_fLastTickTime)
		{
			m_iTickNum++;
			FixedUpdate(TICK_DELAY);
			m_fLastTickTime += TICK_DELAY;
		}
	}
	
	void FixedUpdate(float timeSlice)
	{
		if ((m_iTickNum & 3) == 0)
			m_iLastChar++;
		if (m_iLastChar > PS_DMessages.E1TEXT.Length() + 20)
		{
			m_DMain.Restart();
		}
	}
	
	void PS_DEndingScreen(PS_DMain dMain, PS_DAssets dAssets)
	{
		m_DMain = dMain;
		m_DAssets = dAssets;
		
		m_Pallete = m_DAssets.m_aPalletes[0];
		m_BackgroundFlat = m_DAssets.m_mFlatTextures["FLOOR4_8"];
		
		m_aSTCFN.Resize(122);
		for (int i = 33; i < 122; i++)
		{
			if (m_DAssets.m_mPatches.Contains("STCFN" + i.ToString(3)))
				m_aSTCFN[i] = m_DAssets.m_mPatches["STCFN" + i.ToString(3)];
		}
	}
}