class PS_Math2D
{
	static const float PI_QUAT = Math.PI/4;
	
	//------------------------------------------------------------------------------------------------
	static float BAMAngleToRad(int BAMAngle)
	{
		BAMAngle = BAMAngle << 16;
		return Math.Repeat(BAMAngle * 0.0000000838190317 * Math.DEG2RAD, Math.PI2);
	}
	
	//------------------------------------------------------------------------------------------------
	static float RadToX(float angle)
	{
		if (angle > 0)
			return PS_DConst.SCREEN_Z - Math.Tan(angle) * PS_DConst.SCREEN_WIDTH_HALF;
		else
			return -Math.Tan(angle) * PS_DConst.SCREEN_WIDTH_HALF + PS_DConst.SCREEN_Z;
	}
	
	//------------------------------------------------------------------------------------------------
	static float AngleTo(vector from, vector to)
	{
		vector fromTo = to - from;
		return Math.Atan2(fromTo[1], fromTo[0]);
	}
	
	//------------------------------------------------------------------------------------------------
	static float Dot2D(vector a, vector b) 
	{  
		// I don't known how that happen :/
		// Well, since it work, let it as is
		return a[0] * b[1] - a[1] * b[0]; 
   }
	static float Dot(vector a, vector b) 
	{  
		return a[0] * b[0] + a[1] * b[1];
   }
	
	//------------------------------------------------------------------------------------------------
	// Give side of point p relativ to line a-b
	static int PointSide(vector p, vector a, vector b) 
	{  
		// Fancy dot
		return -(((p[0] - a[0]) * (b[1] - a[1])) - ((p[1] - a[1]) * (b[0] - a[0])));
   }
	
	//------------------------------------------------------------------------------------------------
	// Check line BBOX collision
	static bool IsBBOXIntersect(vector a0, vector a1, vector position, vector offsets[4])
	{
		vector from = position + offsets[0];
		vector to   = position + offsets[2];
		
		// Both points outside
		if (a0[0] < from[0] && a1[0] < from[0]) return false;
		if (a0[1] < from[1] && a1[1] < from[1]) return false;
		if (a0[0] > to[0] && a1[0] > to[0]) return false;
		if (a0[1] > to[1] && a1[1] > to[1]) return false;
		
		// Point inside
		if (a0[0] > from[0] && a0[0] < to[0] && a0[1] > from[1] && a0[1] < to[1]) return true;
		if (a1[0] > from[0] && a1[0] < to[0] && a1[1] > from[1] && a1[1] < to[1]) return true;
		
		vector intersect;
		intersect = PS_Math2D.linesIntersect(position + offsets[0], position + offsets[1], a0, a1);
		if (intersect != "inf inf inf")
		{
			return true;
		}
		intersect = PS_Math2D.linesIntersect(position + offsets[1], position + offsets[2], a0, a1);
		if (intersect != "inf inf inf")
		{
			return true;
		}
		intersect = PS_Math2D.linesIntersect(position + offsets[2], position + offsets[3], a0, a1);
		if (intersect != "inf inf inf")
		{
			return true;
		}
		intersect = PS_Math2D.linesIntersect(position + offsets[3], position + offsets[0], a0, a1);
		if (intersect != "inf inf inf")
		{
			return true;
		}
		return false;
	}
	
	//------------------------------------------------------------------------------------------------
	// Calculate intersection line between two lines
	static vector linesIntersect(vector a0, vector a1, vector b0, vector b1)
	{
		// WTF HAPPENING HERE? 
		// Just stolen, don't blame me, ima too stupid for that rocket science...
		
		if (a0[0] == float.INFINITY)
			return "inf inf inf";
		
		float d =
			((a0[0] - a1[0]) * (b0[1] - b1[1]))
			- ((a0[1] - a1[1]) * (b0[0] - b1[0]));
		
		if (Math.AbsFloat(d) < 0.0000000001) 
			return "inf inf inf"; // nan hard to compare
		
		float t = (((a0[0] - b0[0]) * (b0[1] - b1[1]))
			- ((a0[1] - b0[1]) * (b0[0] - b1[0]))) / d;
		float u = (((a0[0] - b0[0]) * (a0[1] - a1[1]))
			- ((a0[1] - b0[1]) * (a0[0] - a1[0]))) / d;
		if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
			return Vector(a0[0] + (t * (a1[0] - a0[0])), a0[1] + (t * (a1[1] - a0[1])), a0[2]);
		
		return "inf inf inf"; // nan hard to compare
	}
	
	//------------------------------------------------------------------------------------------------
	// Rotate vector position BY angle in rad
	static vector Rotate(vector position, float angle)
	{
		// OFP teach me this stuff
		return Vector(
			position[0] * Math.Cos(angle) - position[1] * Math.Sin(angle),
			position[0] * Math.Sin(angle) + position[1] * Math.Cos(angle),
			position[2]
		);
	}
	
	//------------------------------------------------------------------------------------------------
	static float NormalizeAngle(float angle)
	{
		// A little bit hard to think when it in rads
		return angle - (Math.PI2 * Math.Floor((angle + Math.PI) / Math.PI2));
	}
}