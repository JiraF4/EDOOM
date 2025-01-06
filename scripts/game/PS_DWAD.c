class PS_DWAD
{
	PS_DMain m_DMain;
	
	string m_sType;
	int m_iNumLumps;
	int m_iInfobleofs;
	
	int m_iCurrentLump;
	ref array<ref PS_DLump> m_aLumps = {};
	
	ref PS_DAssets m_DAssets;
	ref PS_DInterface m_DInterface;
	ref PS_DMap m_dMap;
	
	string m_sWadPath;
	
	void PS_DWAD(PS_DMain dMain, string wadPath)
	{
		m_sWadPath = wadPath;
		
		m_DMain = dMain;
		FileHandle wadFile = FileIO.OpenFile(wadPath, FileMode.READ);
		
		ReadHeader(wadFile);
		ReadLumps(wadFile);
		
		wadFile.Close();
		wadFile = FileIO.OpenFile(wadPath, FileMode.READ);
		
		m_DAssets = new PS_DAssets(this);
		SeekLump("PLAYPAL");
		m_DAssets.ReadLump(wadFile, m_aLumps[m_iCurrentLump], PS_EDLump.PS_DPalette, 256 * 3);
		
		SeekLump("COLORMAP");
		m_DAssets.ReadColorMap(wadFile);
		
		SeekLump("TEXTURE1");
		PS_DLump lump = m_aLumps[m_iCurrentLump];
		m_DAssets.ReadTextures(wadFile, m_aLumps[m_iCurrentLump]);
		if (SeekLump("TEXTURE2"))
		{
			lump = m_aLumps[m_iCurrentLump];
			m_DAssets.ReadTextures(wadFile, m_aLumps[m_iCurrentLump]);
		}
		
		SeekLump("PNAMES");
		lump = m_aLumps[m_iCurrentLump];
		m_DAssets.ReadPatchNames(wadFile, m_aLumps[m_iCurrentLump]);
		
		
		wadFile.Close();
		wadFile = FileIO.OpenFile(wadPath, FileMode.READ);
		SeekLump("D_INTROA"); // Interface staff, need normal way...
		m_iCurrentLump++;
		lump = m_aLumps[m_iCurrentLump];
		while (lump.m_sName != "S_START")
		{
			m_DAssets.ReadPatch(wadFile, m_aLumps[m_iCurrentLump]);
			m_iCurrentLump++;
			lump = m_aLumps[m_iCurrentLump];
		}
		
		wadFile.Close();
		wadFile = FileIO.OpenFile(wadPath, FileMode.READ);
		SeekLump("S_START");
		m_iCurrentLump++;
		lump = m_aLumps[m_iCurrentLump];
		while (lump.m_sName != "S_END")
		{
			m_DAssets.ReadPatch(wadFile, m_aLumps[m_iCurrentLump]);
			m_iCurrentLump++;
			lump = m_aLumps[m_iCurrentLump];
		}
		
		wadFile.Close();
		wadFile = FileIO.OpenFile(wadPath, FileMode.READ);
		SeekLump("P_START");
		m_iCurrentLump++;
		lump = m_aLumps[m_iCurrentLump];
		while (lump.m_sName != "P_END")
		{
			if (lump.m_sName != "P1_START" && lump.m_sName != "P1_END")
				m_DAssets.ReadPatch(wadFile, m_aLumps[m_iCurrentLump]);
			m_iCurrentLump++;
			lump = m_aLumps[m_iCurrentLump];
		}
		
		wadFile.Close();
		wadFile = FileIO.OpenFile(wadPath, FileMode.READ);
		SeekLump("F_START");
		m_iCurrentLump++;
		lump = m_aLumps[m_iCurrentLump];
		while (lump.m_sName != "F_END")
		{
			m_DAssets.ReadFlat(wadFile, m_aLumps[m_iCurrentLump]);
			m_iCurrentLump++;
			lump = m_aLumps[m_iCurrentLump];
		}
		
		m_DAssets.Init();
		
		wadFile.Close();
	}
	
	//------------------------------------------------------------------------------------------------
	void LoadMap(string mapName)
	{
		FileHandle wadFile = FileIO.OpenFile(m_sWadPath, FileMode.READ);
		
		m_dMap = new PS_DMap(this, m_DMain, mapName);
		SeekLump(mapName);
		SeekLump("THINGS");
		m_dMap.ReadLump(wadFile, m_aLumps[m_iCurrentLump], PS_EDLump.PS_DThing, 10);
		SeekLump("LINEDEFS");
		m_dMap.ReadLump(wadFile, m_aLumps[m_iCurrentLump], PS_EDLump.PS_DLinedef, 14);
		SeekLump("SIDEDEFS");
		m_dMap.ReadLump(wadFile, m_aLumps[m_iCurrentLump], PS_EDLump.PS_DSideDef, 30);
		SeekLump("VERTEXES");
		m_dMap.ReadLump(wadFile, m_aLumps[m_iCurrentLump], PS_EDLump.PS_DVertex, 4);
		SeekLump("SEGS");
		m_dMap.ReadLump(wadFile, m_aLumps[m_iCurrentLump], PS_EDLump.PS_DSeg, 12);
		SeekLump("SSECTORS");
		m_dMap.ReadLump(wadFile, m_aLumps[m_iCurrentLump], PS_EDLump.PS_DSubSector, 4);
		SeekLump("NODES");
		m_dMap.ReadLump(wadFile, m_aLumps[m_iCurrentLump], PS_EDLump.PS_DNode, 28);
		SeekLump("SECTORS");
		m_dMap.ReadLump(wadFile, m_aLumps[m_iCurrentLump], PS_EDLump.PS_DSector, 26);
		SeekLump("REJECT");
		m_dMap.ReadReject(wadFile, m_aLumps[m_iCurrentLump]);
		SeekLump("BLOCKMAP");
		m_dMap.ReadBlockMap(wadFile, m_aLumps[m_iCurrentLump]);
		m_dMap.Init();
		
		wadFile.Close();
	}
	
	//------------------------------------------------------------------------------------------------
	bool SeekLump(string lumpName)
	{
		int i = m_iCurrentLump;
		int c;
		while (1)
		{
			PS_DLump lump = m_aLumps[i];
			if (lump.m_sName == lumpName)
			{
				m_iCurrentLump = i;
				break;
			}
			c++;
			i++;
			if (i >= m_iNumLumps)
				i = 0;
			if (c > m_iNumLumps)
			{
				Print("INVALIDE LUMP - " + lumpName);
				return false;
			}
		}
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadHeader(FileHandle wadFile)
	{
		m_sType = ReadASCIIString(wadFile, 4);
		wadFile.Read(m_iNumLumps, 4);
		wadFile.Read(m_iInfobleofs, 4);
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadLumps(FileHandle wadFile)
	{
		wadFile.Seek(m_iInfobleofs);
		for (int i = 0; i < m_iNumLumps; i++)
		{
			ReadLump(wadFile);
		}
	}
	
	void ReadLump(FileHandle wadFile)
	{
		PS_DLump lump = new PS_DLump();
		
		wadFile.Read(lump.m_iFilepos, 4);
		wadFile.Read(lump.m_iSize, 4);
		lump.m_sName = ReadASCIIString(wadFile, 8);
		
		m_aLumps.Insert(lump);
	}
	
	//------------------------------------------------------------------------------------------------
	static string ReadASCIIString(FileHandle wadFile, int length)
	{
		string result;
		while (length > 0)
		{
			int data;
			wadFile.Read(data, 1);
			result += data.AsciiToString();
			length--;
		}
		return result;
	}
	
	//------------------------------------------------------------------------------------------------
	static int ReadShort(FileHandle wadFile)
	{
		int data;
		wadFile.Read(data, 2);
		if (data & 32768)
			data = data-65536;
		return data;
	}
	
	//------------------------------------------------------------------------------------------------
	void PrintContent()
	{
		/*
		PrintFormat("%1 %2 %3", m_sType, m_iNumLumps, m_iInfobleofs);
		foreach (PS_DLump lump : m_aLumps)
		{
			PrintFormat("%1 %2 %3", lump.m_sName, lump.m_iFilepos, lump.m_iSize);
		}
		*/
		/*
		foreach (PS_DMap dmap : m_aMaps)
		{
			//dmap.PrintContent();
		}
		*/
	}
}

