// Collision grid, contains cells with contains intersected lines
// Contains functions for "physic" tracing, used for shoots and look
// Movement inside entity logic
class PS_DBlockMap
{
	// Doesn't really  needed here
	PS_DMap m_DMap;
	void PS_DBlockMap(PS_DMap dMap)
	{
		m_DMap = dMap;
	}
	
	int m_iGridOriginX; // Maps translated to random coords
	int m_iGridOriginY; // For making your life harder I think...
	int m_iGridColumns; // Size of map in 128x128 units chanks
	int m_iGridRows;    // One unit = 1, with is not true for original...
	ref array<int> m_aOffsets = {}; // WAD file seek offsets
	ref array<ref PS_DBlockMapCell> m_aCells = {}; // m_iGridColumns * m_iGridRows grid
	
	// Static fields for collision checking
	static vector s_vIntersect;   // First intersected position, "inf inf inf" is non
	static vector s_vNormal;      // Normal of first intersection
	static vector s_fHeight;      // Height of first intersection
	static PS_DEntity s_Entity;   // First intersected entity
	static PS_DLineDef s_LineDef; // First intersected LineDef
	static ref array<PS_DLineDef> s_aIntersectedLineDefs = {}; // All intersected by trace LineDefs
	static ref array<PS_DEntity> s_aIntersectedEntities = {};  // and entities
	
	//------------------------------------------------------------------------------------------------
	// Query first intersected lineDef/Entity
	void TraceShoot(vector from, vector to, PS_DEntity shooter, bool ignoreOther = false)
	{
		// Query all intersected
		TraceAll(from, to, PS_EDMobjFlag.MF_SOLID);
		// Search first in result
		CheckTarget(from, to, shooter, ignoreOther);
		
		// It's more efficient do two in one...
		// Ok, TODO: merge check with trace
		// And wait for someone eventually made it
	}
	
	//------------------------------------------------------------------------------------------------
	// Just get cell by grid coord: x + y * m_iGridColumns
	PS_DBlockMapCell GetCellXY(int x, int y)
	{
		int cellIndex = x + y * m_iGridColumns;
		return m_aCells[cellIndex];
	}
	
	//------------------------------------------------------------------------------------------------
	// Get cell by world coords
	PS_DBlockMapCell GetCell(vector position)
	{
		position -= Vector(m_iGridOriginX, m_iGridOriginY, 0);
		position /= 128;
		int cellIndex = ((int)position[0]) + ((int)position[1]) * m_iGridColumns;
		if (cellIndex >= m_aCells.Count() || cellIndex < 0) // FIXME
			return m_aCells[0];
		return m_aCells[cellIndex];
	}
	
	//------------------------------------------------------------------------------------------------
	// Search in trace result first intersection
	// Include height check
	void CheckTarget(vector from, vector to, PS_DEntity excluded = null, bool ignoreOther = false)
	{
		s_Entity = null;
		s_LineDef = null;
		
		float maxDistance = float.MAX;
		vector fromTo = to - from;
		float length = fromTo.Length();
		
		// Find first height intersected LineDef
		foreach (PS_DLineDef lineDef : s_aIntersectedLineDefs)
		{
			// Calculate height and save intersection data
			// TODO: copy "copy" to break branches
			maxDistance = lineDef.m_fIntersectionDistance;
			float pathTraveled = maxDistance / length;
			float currentHeight = from[2] * (1.0 - pathTraveled) + to[2] * pathTraveled;
			s_vIntersect = lineDef.m_vIntersection;
			s_vIntersect[2] = currentHeight;
			s_vNormal = lineDef.m_vIntersectNormal;
			
			// Solid wall
			if (!lineDef.m_BackSideDef)
			{
				s_LineDef = lineDef;
				break;
			}
			
			// Floor
			if (lineDef.m_BackSideDef.m_Sector.m_iFloorHeight > currentHeight)
			{
				s_LineDef = lineDef;
				break;
			}
			if (lineDef.m_FrontSideDef.m_Sector.m_iFloorHeight > currentHeight)
			{
				s_LineDef = lineDef;
				break;
			}
			
			// Ceil
			if (lineDef.m_BackSideDef.m_Sector.m_iCeilingHeight < currentHeight)
			{
				s_LineDef = lineDef;
				break;
			}
			if (lineDef.m_FrontSideDef.m_Sector.m_iCeilingHeight < currentHeight)
			{
				s_LineDef = lineDef;
				break;
			}
		}
		
		// All LineDef excluded by height
		// Clear intersection result
		if (!s_LineDef)
		{
			s_vNormal = "0 0 0";
			s_vIntersect = "inf inf inf";
			maxDistance = length;
		}
				
		// Find first entity before wall
		foreach (PS_DEntity entity : s_aIntersectedEntities)
		{
			if (ignoreOther) // Is excluded obstructed by line def
			{
				if (excluded != entity)
					continue;
			}
			else // Get first entity
			{
				if (excluded == entity)
					continue;
			}
			
			// Behind wall, stop, next entities farrest
			if (maxDistance < entity.m_fIntersectDistance)
				break;
			
			// Calculate height
			float pathTraveled = entity.m_fIntersectDistance / length;
			float currentHeight = from[2] * (1.0 - pathTraveled) + to[2] * pathTraveled;
			
			// Height check
			if (currentHeight > entity.m_vPosition[2] && currentHeight < entity.m_vPosition[2] + entity.m_MobjInfo.m_iHeight)
			{
				// Save intrsection data
				s_vNormal = entity.m_vIntersectNormal;
				s_vIntersect = entity.m_vIntersect;
				s_vIntersect[2] = currentHeight;
				s_Entity = entity;
				return;
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	// Search first not obstructed entity, ignore height
	PS_DEntity GetFirstNotObstructedEntity(PS_DEntity excluded = null)
	{
		foreach (PS_DEntity entity : s_aIntersectedEntities)
		{
			if (!(entity.m_iFlags & PS_EDMobjFlag.MF_SHOOTABLE))
				continue;
			
			if (entity != null && entity != excluded)
			{
				foreach (PS_DLineDef lineDef : s_aIntersectedLineDefs)
				{
					if (lineDef.m_BackSideDef)
						continue;
					if (lineDef.m_fIntersectionDistance < entity.m_fIntersectDistance)
						return null;
					else
						return entity;
				}
				return entity;
			}
		}
		return null;
	}
	
	//------------------------------------------------------------------------------------------------
	// Trace all lineDefs/Entities intersected by line from-to before first solid wall
	// Overkill, maybe fix it latter
	void TraceAll(vector from, vector to, int entityFlags)
	{
		// Clear out
		s_LineDef = null;
		s_vIntersect = "0 0 0";
		s_aIntersectedLineDefs.Clear();
		s_aIntersectedEntities.Clear();
		
		// Calculate grid steps TODO: fixed step
		vector fromTo = to - from;
		float steps = fromTo.Length() / 128;
		fromTo = fromTo.Normalized() * 128;
		vector cellTo = from;
		
		// Update flags
		PS_DBlockMapCell.s_iFlag++;
		PS_DLineDef.s_iFlag++;
		PS_DEntity.s_iFlag++;
		while (true)
		{
			PS_DBlockMapCell blockCell = GetCell(cellTo);
			if (blockCell.m_iFlag != blockCell.s_iFlag) // Skip if already processed. 
			{
				blockCell.m_iFlag = blockCell.s_iFlag;
				
				// get all intersected lines
				foreach (PS_DLineDef lineDef : blockCell.m_aLineDefs)
				{
					if (lineDef.m_iFlag == PS_DLineDef.s_iFlag) // Skip if already processed. 
						continue;
					lineDef.m_iFlag = PS_DLineDef.s_iFlag;
					
					// Calculate intersection by power of math
					vector intersect = PS_Math2D.linesIntersect(from, to, lineDef.m_vStartingVertex, lineDef.m_vEndVertex);
					if (intersect != "inf inf inf")
					{
						// If intersected save result
						lineDef.m_vIntersection = intersect;
						vector vectorTo = (intersect - from);
						vectorTo[2] = 0; // Maybe make custom functuion... (Too many bugs with z coord)
						lineDef.m_fIntersectionDistance = vectorTo.Length();
						lineDef.m_vIntersectNormal = lineDef.m_vNormal; //  Huh... FIXME
						
						// If solid wall stop cycle
						if (!lineDef.m_BackSideDef)
							steps = 0;
						
						// Sorted insert
						// All LineDefs need to be sorted by distance
						bool inserted;
						for (int i = 0; i < s_aIntersectedLineDefs.Count(); i++)
						{
							PS_DLineDef lineDefOther = s_aIntersectedLineDefs[i];
							if (lineDefOther.m_fIntersectionDistance > lineDef.m_fIntersectionDistance)
							{
								inserted = true;
								s_aIntersectedLineDefs.InsertAt(lineDef, i);
								break;
							}
						}
						if (!inserted)
							s_aIntersectedLineDefs.Insert(lineDef);
					};
				}
				
				// get all intersected entities
				foreach (PS_DEntity entity : blockCell.m_sEntities)
				{
					if (!entity) // Deleted entity, skip
						continue;
					if (entity.m_iFlag == PS_DEntity.s_iFlag) // Already processed, skip
						continue;
					entity.m_iFlag = PS_DEntity.s_iFlag;
					
					// Check flags filter
					// SOLID, SHOOTABLE, and other.
					if ((entity.m_iFlags & entityFlags) != entityFlags)
						continue;
					
					// Calculate intersection
					entity.m_vIntersect = entity.GetBBOXIntersect(from, to);
					vector vectorTo = (entity.m_vIntersect - from);
					vectorTo[2] = 0;
					entity.m_fIntersectDistance = vectorTo.Length();
					
					// If intersected
					if (entity.m_vIntersect != "inf inf inf")
					{
						// Sorted insert
						bool inserted;
						for (int i = 0; i < s_aIntersectedEntities.Count(); i++)
						{
							PS_DEntity entityOther = s_aIntersectedEntities[i];
							if (entityOther.m_fIntersectDistance > entity.m_fIntersectDistance)
							{
								inserted = true;
								s_aIntersectedEntities.InsertAt(entity, i);
								break;
							}
						}
						if (!inserted)
							s_aIntersectedEntities.Insert(entity);
					}
				}
			}
			
			// Next block
			if (steps <= 0)
				break;
			if (steps > 0.1)
			{
				cellTo += fromTo * 0.1;
				steps -= 0.1;
			} else
			{
				cellTo += fromTo * steps;
				steps = 0;
			}
		}
	}
}

// Part of block map
class PS_DBlockMapCell
{
	// Processing flag
	static int s_iFlag;
	int m_iFlag;
	
	// Grid coords
	int m_iX;
	int m_iY;
	
	// Intersected line defs
	ref array<int> m_aLineDefIds = {};
	ref array<PS_DLineDef> m_aLineDefs = {};
	
	// Neighbours INCLUDE self
	ref array<PS_DBlockMapCell> m_aNeighbours = {};
	
	// All entities in cell
	ref set<PS_DEntity> m_sEntities = new set<PS_DEntity>();
}