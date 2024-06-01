class PS_DSave
{
	static void Save(PS_DMain dMain, string path)
	{
		FileHandle saveFile = FileIO.OpenFile(path, FileMode.WRITE);
		string saveHeader = "PSDS";
		saveFile.Write(saveHeader, 4);
		int time = System.GetUnixTime();
		saveFile.Write(time, 4);
		dMain.WriteSave(saveFile);
	}
	
	static void ReadHeader(FileHandle saveFile)
	{
		// TODO
		string saveHeader;
		saveFile.Read(saveHeader, 4);
		int time;
		saveFile.Read(time, 4);
	}
	
	static void LoadTransfer(PS_DMain dMain, string path)
	{
		dMain.MeltScreen();
		Load(dMain, path);
		dMain.m_CurrentGameState = PS_DGameState.GS_LEVEL;
		dMain.m_bInMenu = false;
		dMain.m_DMap.FixedUpdate(0);
	}
	
	static void Load(PS_DMain dMain, string path)
	{
		FileHandle saveFile = FileIO.OpenFile(path, FileMode.READ);
		ReadHeader(saveFile);
		dMain.ReadSave(saveFile);
	}
	
	static void LoadPreview(string path, int[] pixels)
	{
		FileHandle saveFile = FileIO.OpenFile(path, FileMode.READ);
		ReadHeader(saveFile); // Skip header
		int pixel;
		for (int i = 0; i < PS_DConst.SAVE_PREVIEW_SIZE; i++)
		{
			saveFile.Read(pixel, 4);
			pixels[i] = pixel;
		}
	}
}
