// all entities, and transperent walls
class PS_DVisSprite
{
	static const int SCREEN_WIDTH = PS_DConst.SCREEN_WIDTH;
	float m_fDistance;
	int m_iMobjFlags;
	float m_fScale;
	float m_fScaleStep;
	vector m_vPosition;
	float m_fTop;
	float m_fTextureMiddle;
	float m_iX1;
	float m_iX2;
	
	float m_fStartFrac;
	float m_fXInversedScale;
	float m_fWorldCenterAngle;
	
	PS_DPatch m_Patch;
	PS_DTextureMap m_TextureMap;
	int m_iLightLevel;
	
	int m_iUpperClip[SCREEN_WIDTH];
	int m_iLowerClip[SCREEN_WIDTH];
	int m_iWallClip[SCREEN_WIDTH];
	
	ref PS_DVisSprite m_PrevVisSprite;
}
