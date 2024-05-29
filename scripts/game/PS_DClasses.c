enum PS_EDLump
{
	PS_DThing,
	PS_DSeg,
	PS_DNode,
	PS_DVertex,
	PS_DLinedef,
	PS_DSubSector,
	PS_DSector,
	PS_DSideDef
}

class PS_DThing
{
	int m_iXPos;          // 2
	int m_iYPos;          // 2
	int m_iAngle;         // 2
	int m_iType;          // 2
	int m_iFlags;         // 2
}

class PS_DSector
{
	PS_DMap m_DMap;
	
	int m_iId;
	
	int m_iFloorHeight;
	int m_iCeilingHeight;
	string m_sFloorTextureName;
	string m_sCeilingTextureName;
	int m_iLightLevel;
	int m_iSpecialType;
	int m_iTagNumber;
	
	PS_DTextureFlat m_FloorTexture;
	PS_DTextureFlat m_CeilingTexture;
	
	ref PS_DSpecial m_Special;
	ref PS_DSpecialAction m_SpecialAction;
	ref PS_DSpecialAction m_SpecialActionLight;
	
	ref array<PS_DSideDef> m_aSideDefs = {};
	
	PS_DEntity m_SoundSource;
	static int s_iFlag;
	int m_iFlag;
	
	int m_iBlockMapX1;
	int m_iBlockMapX2;
	int m_iBlockMapY1;
	int m_iBlockMapY2;
	
	vector m_vTeleportTarget;
	
	void InitPolygon()
	{
		float minX, minY;
		float maxX, maxY;
		maxX = -float.MAX;
		maxY = -float.MAX;
		minX =  float.MAX;
		minY =  float.MAX;
		
		if (m_iId == 4)
			m_iId = 4;
		
		foreach (PS_DSideDef sideDef : m_aSideDefs)
		{
			PS_DLineDef lineDef = sideDef.m_LineDef;
			vector point = lineDef.m_vStartingVertex;
			if (minX > point[0])
				minX = point[0];
			if (maxX < point[0])
				maxX = point[0];
			if (minY > point[1])
				minY = point[1];
			if (maxY < point[1])
				maxY = point[1];
		}
		
		m_iBlockMapX1 = (minX - m_DMap.m_DBlockMap.m_iGridOriginX) / 128 - 1;
		m_iBlockMapX2 = (maxX - m_DMap.m_DBlockMap.m_iGridOriginX) / 128 + 1;
		m_iBlockMapY1 = (minY - m_DMap.m_DBlockMap.m_iGridOriginY) / 128 - 1;
		m_iBlockMapY2 = (maxY - m_DMap.m_DBlockMap.m_iGridOriginY) / 128 + 1;
		
		m_iBlockMapX1 = Math.Clamp(m_iBlockMapX1, 0, m_DMap.m_DBlockMap.m_iGridColumns);
		m_iBlockMapX2 = Math.Clamp(m_iBlockMapX2, 0, m_DMap.m_DBlockMap.m_iGridColumns);
		m_iBlockMapY1 = Math.Clamp(m_iBlockMapY1, 0, m_DMap.m_DBlockMap.m_iGridRows);
		m_iBlockMapY2 = Math.Clamp(m_iBlockMapY2, 0, m_DMap.m_DBlockMap.m_iGridRows);
	}
	
	array<PS_DEntity> GetEntitiesInside()
	{
		array<PS_DEntity> entities = {};
		for (int x = m_iBlockMapX1; x <= m_iBlockMapX2; x++)
		{
			for (int y = m_iBlockMapY1; y <= m_iBlockMapY2; y++)
			{
				PS_DBlockMapCell cell = m_DMap.m_DBlockMap.GetCellXY(x, y);
				foreach (PS_DEntity entity : cell.m_sEntities)
				{
					if (!(entity.m_iFlags & PS_EDMobjFlag.MF_SOLID))
						continue;
					
					vector offsets[5] = entity.m_BBOX.m_aOffsetsCenter;
					foreach (vector offset : offsets)
					{
						PS_DSector sector = m_DMap.GetPositionSector(entity.m_vPosition + offset);
						if (sector == this)
						{
							entities.Insert(entity);
							break;
						}
					}
				}
			}
		}
		return entities;
	}
	
	PS_DSector GetNeighbourMaxFloorHeight()
	{
		int maxFloor = 0;
		PS_DSector maxSector = null;
		foreach (PS_DSideDef sideDef : m_aSideDefs)
		{
			PS_DLineDef lineDef = sideDef.m_LineDef;
			if (lineDef.m_FrontSideDef)
				if (lineDef.m_FrontSideDef.m_Sector != this)
					{
						PS_DSector sector = lineDef.m_FrontSideDef.m_Sector;
						if (sector.m_iFloorHeight > maxFloor)
						{
							maxFloor = sector.m_iFloorHeight;
							maxSector = sector;
						}
					}
			if (lineDef.m_BackSideDef)
				if (lineDef.m_BackSideDef.m_Sector != this)
					{
						PS_DSector sector = lineDef.m_BackSideDef.m_Sector;
						if (sector.m_iFloorHeight > maxFloor)
						{
							maxFloor = sector.m_iFloorHeight;
							maxSector = sector;
						}
					}
		}
		return maxSector;
	}
	
	PS_DSector GetNeighbourMinFloorHeight()
	{
		int minFloor = int.MAX;
		PS_DSector minSector = null;
		foreach (PS_DSideDef sideDef : m_aSideDefs)
		{
			PS_DLineDef lineDef = sideDef.m_LineDef;
			if (lineDef.m_FrontSideDef)
				if (lineDef.m_FrontSideDef.m_Sector != this)
					{
						PS_DSector sector = lineDef.m_FrontSideDef.m_Sector;
						if (sector.m_iFloorHeight < minFloor)
						{
							minFloor = sector.m_iFloorHeight;
							minSector = sector;
						}
					}
			if (lineDef.m_BackSideDef)
				if (lineDef.m_BackSideDef.m_Sector != this)
					{
						PS_DSector sector = lineDef.m_BackSideDef.m_Sector;
						if (sector.m_iFloorHeight < minFloor)
						{
							minFloor = sector.m_iFloorHeight;
							minSector = sector;
						}
					}
		}
		return minSector;
	}
	
	int GetNeighbourLowesCeilingHeight()
	{
		int minCeiling = int.MAX;
		foreach (PS_DSideDef sideDef : m_aSideDefs)
		{
			PS_DLineDef lineDef = sideDef.m_LineDef;
			if (lineDef.m_FrontSideDef)
				if (lineDef.m_FrontSideDef.m_Sector != this)
					minCeiling = Math.Min(lineDef.m_FrontSideDef.m_Sector.m_iCeilingHeight, minCeiling);
			if (lineDef.m_BackSideDef)
				if (lineDef.m_BackSideDef.m_Sector != this)
					minCeiling = Math.Min(lineDef.m_BackSideDef.m_Sector.m_iCeilingHeight, minCeiling);
		}
		return minCeiling;
	}
	
	int GetNeighbourLowestLightLevel()
	{
		int minLight = m_iLightLevel;
		foreach (PS_DSideDef sideDef : m_aSideDefs)
		{
			PS_DLineDef lineDef = sideDef.m_LineDef;
			if (lineDef.m_FrontSideDef)
				minLight = Math.Min(lineDef.m_FrontSideDef.m_Sector.m_iLightLevel, minLight);
			if (lineDef.m_BackSideDef)
				minLight = Math.Min(lineDef.m_BackSideDef.m_Sector.m_iLightLevel, minLight);
		}
		return minLight;
	}
}

class PS_DSideDef
{
	int m_xOffset;
	int m_yOffset;
	string m_sUpperTextureName;
	string m_sLowerTextureName;
	string m_sMiddleTextureName;
	int m_iLightLevel;
	int m_iSectorId;
	
	PS_DSector m_Sector;
	PS_DLineDef m_LineDef;
}

class PS_DSeg
{
	// data
	int m_iStartingVertex;// 2
	int m_iEndingVertex;  // 2
	int m_iAngle;         // 2
	int m_iLinedefNumber; // 2
	int m_iDirection;     // 2
	int m_iOffset;        // 2
	
	float m_fAngle;
	float m_fDirection;
	
	// links
	vector m_vStartingVertex;
	vector m_vEndingVertex;
	
	PS_DLineDef m_LineDef;
	
	PS_DSideDef m_FrontSideDef;
	PS_DSideDef m_BackSideDef;
	
	PS_DSector m_FrontSector;
	PS_DSector m_BackSector;
	
	// temp
	float m_fWorldAngle1;
	
	float m_fAngle1;
	float m_fAngle2;
	
	int m_iX1;
	int m_iX2;
	
	bool CalculateAngles(PS_DEntityPlayer player, int minX, int maxX)
	{
		m_fAngle1 = PS_Math2D.AngleTo(player.m_vPosition, m_vStartingVertex);
		m_fAngle2 = PS_Math2D.AngleTo(player.m_vPosition, m_vEndingVertex);
		
		m_fWorldAngle1 = m_fAngle1;
		
		float span = Math.Repeat(m_fAngle1 - m_fAngle2, Math.PI2);
		if (span >= Math.PI)
			return false;
		
		m_fAngle1 += player.m_fAngle - Math.PI_HALF;
		m_fAngle2 += player.m_fAngle - Math.PI_HALF;
		
		float span1 = Math.Repeat(m_fAngle1 + PS_DConst.HORIZONTAL_FOV_HALF, Math.PI2);
		if (span1 > PS_DConst.HORIZONTAL_FOV)
		{
			if (span1 >= span + PS_DConst.HORIZONTAL_FOV)
				return false;
			m_fAngle1 = PS_DConst.HORIZONTAL_FOV_HALF;
		}	
		
		float span2 = Math.Repeat(PS_DConst.HORIZONTAL_FOV_HALF - m_fAngle2, Math.PI2);
		if (span2 > PS_DConst.HORIZONTAL_FOV)
		{
			if (span2 >= span + PS_DConst.HORIZONTAL_FOV)
				return false;
			m_fAngle2 = -PS_DConst.HORIZONTAL_FOV_HALF;
		}
		
		m_iX1 = Math.Max(PS_Math2D.RadToX(m_fAngle1), minX);
		m_iX2 = Math.Min(PS_Math2D.RadToX(m_fAngle2), maxX);
		
		if (m_iX1 >= m_iX2)
			return false;
		
		return true;
	}
}

class PS_DSubSector
{
	int m_iSegCount;       // 2
	int m_iFirstSegNum;    // 2
	
	ref array<PS_DSeg> m_aSegments = {};
	ref set<PS_DEntity> m_sEntities = new set<PS_DEntity>();
	
	int m_iColor;
}

class PS_DNode
{
	int m_iXPartition;      // 2
	int m_iYPartition;      // 2
	int m_iXDeltaPartition; // 2
	int m_iYDeltaPartition; // 2
	int m_iLeftChild;       // 2
	int m_iRightChild;      // 2
	
	vector m_vPartition, m_vPartitionDelta;
	
	ref PS_DBBox m_LeftBBox;
	ref PS_DBBox m_RightBBox;
	
	PS_DNode m_LeftNode;
	PS_DNode m_RightNode;
	PS_DSubSector m_LeftSubSector;
	PS_DSubSector m_RightSubSector;
}

class PS_DBBox
{
	int m_iTop, m_iBottom, m_iLeft, m_iRight;
	vector m_vTopLeft, m_vTopRight, m_vBottomLeft, m_vBottomRight;
	vector m_aVertexs[4];
	
	void PS_DBBox(int top, int bottom, int left, int right)
	{
		m_iTop = top;
		m_iBottom= bottom;
		m_iLeft = left;
		m_iRight = right;
		
		m_vTopLeft     = Vector(left, top, 0);
		m_vTopRight    = Vector(right, top, 0);
		m_vBottomLeft  = Vector(left, bottom, 0);
		m_vBottomRight = Vector(right, bottom, 0);
		
		m_aVertexs[0] = m_vBottomLeft;
		m_aVertexs[1] = m_vTopLeft;
		m_aVertexs[2] = m_vTopRight;
		m_aVertexs[3] = m_vBottomRight;
	}
	
	bool CheckBBox(PS_DEntityPlayer player)
	{
		float px = player.m_vPosition[0];
		float py = player.m_vPosition[1];
		
		array<ref array<int>> sides;
		if (px < m_iLeft)
		{
			if (py > m_iTop)
			{
				sides = {{1, 0}, {2, 1}};
			} else if (py < m_iBottom)
			{
				sides = {{1, 0}, {0, 3}};
			} else
				sides = {{1, 0}};
		} else if (px > m_iRight)
		{
			if (py > m_iTop)
			{
				sides = {{2, 1}, {3, 2}};
			} else if (py < m_iBottom)
			{
				sides = {{0, 3}, {3, 2}};
			} else 
			{
				sides = {{3, 2}};
			}
		} else {
			if (py > m_iTop)
			{
				sides = {{2, 1}};
			} else if (py < m_iBottom)
			{
				sides = {{0, 3}};
			} else 
			{
				return true;
			}
		}
		
		foreach (array<int> side : sides)
		{
			vector p1 = m_aVertexs[side[0]];
			vector p2 = m_aVertexs[side[1]];
			
			float angleToP1 = PS_Math2D.AngleTo(player.m_vPosition, p1);
			float angleToP2 = PS_Math2D.AngleTo(player.m_vPosition, p2);
			
			float span = Math.Repeat(angleToP1 - angleToP2, Math.PI2);
			
			angleToP1 += player.m_fAngle - Math.PI_HALF;
			float span1 = Math.Repeat(angleToP1 + PS_DConst.HORIZONTAL_FOV_HALF, Math.PI2);
			if (span1 > PS_DConst.HORIZONTAL_FOV_EXT) // Else sprites culling too much
				if (span1 >= span + PS_DConst.HORIZONTAL_FOV_EXT)
					continue;
			return true;
		}
		
		return false;
	}
}

class PS_DLineDef
{
	void PrintContent()
	{
		//PrintFormat("%1 %2 %3 %4 %5 %6 %7", m_iStartVertex, m_iEndVertex, m_iFlags, m_iSpecialType, m_iSectorTag, m_iFrontSide, m_iBackSide);
	}
	
	int m_iStartVertex;
	int m_iEndVertex;
	int m_iFlags;
	int m_iSpecialType;
	int m_iSectorTag;
	int m_iFrontSide;
	int m_iBackSide;
	
	vector m_vNormal;
	
	vector m_vStartingVertex;
	vector m_vEndVertex;
	
	PS_DSideDef m_FrontSideDef;
	PS_DSideDef m_BackSideDef;
	
	vector m_vIntersection;
	vector m_vIntersectNormal;
	float m_fIntersectionDistance;
	
	int m_iTextureChanged;
	
	static int s_iFlag;
	int m_iFlag;
	
	ref PS_DSpecial m_Special;
}

class PS_DLump
{
	int m_iFilepos;
	int m_iSize;
	string m_sName;
}