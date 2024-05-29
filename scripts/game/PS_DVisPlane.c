// Floors and ceilings
class PS_DVisPlane
{
	static const int SCREEN_WIDTH = PS_DConst.SCREEN_WIDTH;
	static const int SCREEN_WIDTH_2 = SCREEN_WIDTH+2;
	
	float m_fHeight;
	PS_DTextureFlat m_TextureFlat;
	int m_iLightLevel;
	int m_iMinX;
	int m_iMaxX;
	int m_aTop[SCREEN_WIDTH_2];
	int m_aBottom[SCREEN_WIDTH_2];
	
	int m_iColor;
}