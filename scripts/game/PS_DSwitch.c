class PS_DSwitch
{
	string m_OffTexture;
	string m_OnTexture;
	int m_iNum;
	
	void PS_DSwitch(
		string offTexture,
		string onTexture,
		int num
	)
	{
		m_OffTexture = offTexture;
		m_OnTexture = onTexture;
		m_iNum = num;
	}
	
	static void ChangeSwitch(PS_DLineDef lineDef, int canBeReused)
	{
		if (!canBeReused)
		{
			lineDef.m_iSpecialType = 0;
			lineDef.m_Special = null;
		}
		
		// Texture lookup
		PS_DSideDef dSideDef = lineDef.m_FrontSideDef;
		foreach (PS_DSwitch dSwitch : DSWITCHES)
		{
			if (dSideDef.m_sLowerTextureName == dSwitch.m_OnTexture)
			{
				dSideDef.m_sLowerTextureName = dSwitch.m_OffTexture;
				lineDef.m_iTextureChanged = 1;
				return;
			}
			if (dSideDef.m_sLowerTextureName == dSwitch.m_OffTexture)
			{
				dSideDef.m_sLowerTextureName = dSwitch.m_OnTexture;
				lineDef.m_iTextureChanged = 1;
				return;
			}
			
			if (dSideDef.m_sMiddleTextureName == dSwitch.m_OnTexture)
			{
				dSideDef.m_sMiddleTextureName = dSwitch.m_OffTexture;
				lineDef.m_iTextureChanged = 1;
				return;
			}
			if (dSideDef.m_sMiddleTextureName == dSwitch.m_OffTexture)
			{
				dSideDef.m_sMiddleTextureName = dSwitch.m_OnTexture;
				lineDef.m_iTextureChanged = 1;
				return;
			}
			
			if (dSideDef.m_sUpperTextureName == dSwitch.m_OnTexture)
			{
				dSideDef.m_sUpperTextureName = dSwitch.m_OffTexture;
				lineDef.m_iTextureChanged = 1;
				return;
			}
			if (dSideDef.m_sUpperTextureName == dSwitch.m_OffTexture)
			{
				dSideDef.m_sUpperTextureName = dSwitch.m_OnTexture;
				lineDef.m_iTextureChanged = 1;
				return;
			}
		}
	}
	
	static const ref array<ref PS_DSwitch> DSWITCHES = {
		// Doom shareware episode 1 switches
	    new PS_DSwitch("SW1BRCOM",	"SW2BRCOM",	1),
	    new PS_DSwitch("SW1BRN1",	"SW2BRN1",	1),
	    new PS_DSwitch("SW1BRN2",	"SW2BRN2",	1),
	    new PS_DSwitch("SW1BRNGN",	"SW2BRNGN",	1),
	    new PS_DSwitch("SW1BROWN",	"SW2BROWN",	1),
	    new PS_DSwitch("SW1COMM",	"SW2COMM",	1),
	    new PS_DSwitch("SW1COMP",	"SW2COMP",	1),
	    new PS_DSwitch("SW1DIRT",	"SW2DIRT",	1),
	    new PS_DSwitch("SW1EXIT",	"SW2EXIT",	1),
	    new PS_DSwitch("SW1GRAY",	"SW2GRAY",	1),
	    new PS_DSwitch("SW1GRAY1",	"SW2GRAY1",	1),
	    new PS_DSwitch("SW1METAL",	"SW2METAL",	1),
	    new PS_DSwitch("SW1PIPE",	"SW2PIPE",	1),
	    new PS_DSwitch("SW1SLAD",	"SW2SLAD",	1),
	    new PS_DSwitch("SW1STARG",	"SW2STARG",	1),
	    new PS_DSwitch("SW1STON1",	"SW2STON1",	1),
	    new PS_DSwitch("SW1STON2",	"SW2STON2",	1),
	    new PS_DSwitch("SW1STONE",	"SW2STONE",	1),
	    new PS_DSwitch("SW1STRTN",	"SW2STRTN",	1),
	    
	    // Doom registered episodes 2&3 switches
	    new PS_DSwitch("SW1BLUE",	"SW2BLUE",	2),
	    new PS_DSwitch("SW1CMT",		"SW2CMT",	2),
	    new PS_DSwitch("SW1GARG",	"SW2GARG",	2),
	    new PS_DSwitch("SW1GSTON",	"SW2GSTON",	2),
	    new PS_DSwitch("SW1HOT",		"SW2HOT",	2),
	    new PS_DSwitch("SW1LION",	"SW2LION",	2),
	    new PS_DSwitch("SW1SATYR",	"SW2SATYR",	2),
	    new PS_DSwitch("SW1SKIN",	"SW2SKIN",	2),
	    new PS_DSwitch("SW1VINE",	"SW2VINE",	2),
	    new PS_DSwitch("SW1WOOD",	"SW2WOOD",	2),
	    
	    // Doom II switches
	    new PS_DSwitch("SW1PANEL",	"SW2PANEL",	3),
	    new PS_DSwitch("SW1ROCK",	"SW2ROCK",	3),
	    new PS_DSwitch("SW1MET2",	"SW2MET2",	3),
	    new PS_DSwitch("SW1WDMET",	"SW2WDMET",	3),
	    new PS_DSwitch("SW1BRIK",	"SW2BRIK",	3),
	    new PS_DSwitch("SW1MOD1",	"SW2MOD1",	3),
	    new PS_DSwitch("SW1ZIM",		"SW2ZIM",	3),
	    new PS_DSwitch("SW1STON6",	"SW2STON6",	3),
	    new PS_DSwitch("SW1TEK",		"SW2TEK",	3),
	    new PS_DSwitch("SW1MARB",	"SW2MARB",	3),
	    new PS_DSwitch("SW1SKULL",	"SW2SKULL",	3),
		
	    new PS_DSwitch("\0",		"\0",		0)
	}
}