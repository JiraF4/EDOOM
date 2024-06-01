class PS_DAssets
{
	PS_DWAD m_DWad;
	ref array<ref PS_DPalette> m_aPalletes = {};
	ref array<ref PS_DColorMap> m_aColorMaps = {};
	ref map<string, ref PS_DPatch> m_mPatches = new map<string, ref PS_DPatch>();
	ref array<string> m_aPatchNames = {};
	ref array<ref PS_DTextureHeader> m_aTextureHeaders = {};
	ref map<string, ref PS_DTextureMap> m_mTextures = new map<string, ref PS_DTextureMap>();
	ref map<string, ref PS_DTextureFlat> m_mFlatTextures = new map<string, ref PS_DTextureFlat>();
	ref array<ref PS_DSprite> m_aSprites = {};
	ref array<ref array<ref PS_DPalette>> m_aColoredPalletes = {};
	
	// Sorted patches
	ref array<PS_DPatch> m_aSTCFN = {}; // ASCII chars
	
	//------------------------------------------------------------------------------------------------
	void Init()
	{
		foreach (PS_DTextureHeader textureHeader : m_aTextureHeaders)
		{
			foreach (PS_DTextureMap textureMap : textureHeader.m_aTextures)
			{
				// Predraw textures from patches
				PS_DTexturePixels texturePixels = new PS_DTexturePixels();
				texturePixels.m_aPixels.Resize(textureMap.m_iWidth * textureMap.m_iHeight);
				
				for (int x = 0; x < textureMap.m_iWidth; x++)
				{
					for (int y = 0; y < textureMap.m_iHeight; y++)
					{
						int pixelPosition = x + y * textureMap.m_iWidth;
						texturePixels.m_aPixels[pixelPosition] = 256;
					}
				}
				
				for (int p = 0; p < textureMap.m_iPatchCount; p++)
				{
					PS_DPatchMap patchMap = textureMap.m_aPatches[p];
					string patchName = m_aPatchNames[patchMap.m_iPatch];
					patchName.ToUpper();
					PS_DPatch patch = m_mPatches[patchName];
					
					// Skip offborders
					int xOff  = Math.Max(0, -patchMap.m_iOriginX);
					int yOff  = Math.Max(0, -patchMap.m_iOriginY);
					int xPart = Math.Clamp(patch.m_DPatchHeader.m_iWidth, -patchMap.m_iOriginX, textureMap.m_iWidth - patchMap.m_iOriginX);
					int yPart = Math.Clamp(patch.m_DPatchHeader.m_iHeight, -patchMap.m_iOriginY, textureMap.m_iHeight - patchMap.m_iOriginY);
					for (int x = xOff; x < xPart; x++)
					{
						for (int y = yOff; y < yPart; y++)
						{
							int palleteColor = patch.m_DTexture.m_aPixels[x + y * patch.m_DPatchHeader.m_iWidth];
							
							if (palleteColor == 256)
								continue;
							
							int pixelX = (x + patchMap.m_iOriginX);
							int pixelY = (y + patchMap.m_iOriginY);
							int pixelPosition = pixelX + pixelY * textureMap.m_iWidth;
							texturePixels.m_aPixels[pixelPosition] = palleteColor;
						}
					}
				}
					
				textureMap.m_TexturePixels = texturePixels;
			}
		}
		
		InitPatches();
		InitSprites();
	}
	
	void SwitchPallet(bool sRGB)
	{
		foreach (PS_DPalette pallete : m_aPalletes)
		{
			if (sRGB)
				StaticArray.Copy(pallete.m_aColors, pallete.m_aColorsSRGB);
			else
				StaticArray.Copy(pallete.m_aColors, pallete.m_aColorsLinear);
		}
		
		BakePallets();
	}
	
	void BakePallets()
	{
		// Prebake every pallet variant
		m_aColoredPalletes = {};
		PS_DColorMap colorMap = m_aColorMaps[0];
		foreach (PS_DPalette pallete : m_aPalletes)
		{
			array<ref PS_DPalette> coloredPalletes = new array<ref PS_DPalette>();
			for (int i = 0; i < 34; i++)
			{
				PS_DPalette remapedPallete = new PS_DPalette();
				
				for (int p = 0; p < 256; p++)
				{
					int c = i;
					if (c < 32)
						c = 31 - c;
					int color = colorMap.m_aColors[p + c * 256];
					remapedPallete.m_aColors[p] = pallete.m_aColors[color];
				}
				
				coloredPalletes.Insert(remapedPallete);
			}
			m_aColoredPalletes.Insert(coloredPalletes);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void InitPatches()
	{
		m_aSTCFN.Resize(122);
		for (int i = 33; i < 122; i++)
		{
			if (m_mPatches.Contains("STCFN" + i.ToString(3)))
				m_aSTCFN[i] = m_mPatches["STCFN" + i.ToString(3)];
		}
	}
	
	void FillBox(int xs, int ys, int w, int h, int color)
	{
		w += xs;
		h += ys;
		for (int x = xs; x < w; x++)
		{
			for (int y = ys; y < h; y++)
			{
				int pixelIndex = x + y * PS_DConst.SCREEN_WIDTH;
				PS_DEddsTexture.m_aPixels[pixelIndex] = color;
			}
		}
	}
	
	void DrawText(int x, int y, string text, int light = 0)
	{
		text.ToUpper();
		for (int i = 0; i < text.Length(); i++)
		{
			int char = text.ToAscii(i);
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
	
	void DrawPatch(int x, int y, PS_DPatch patch, int light = 31)
	{
		PS_DPalette pallete = m_aColoredPalletes[0][light];
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
					if (pixelIndex < PS_DEddsTexture.SCREEN_SIZE)
						PS_DEddsTexture.m_aPixels[pixelIndex] = color;
				}
				yp++;
			}
			xp++;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void InitSprites()
	{
		for (int spriteNum = 0; spriteNum < PS_DMobjSpriteNum.NUMSPRITES; spriteNum++)
		{
			PS_DSprite sprite = new PS_DSprite();
			string sriteName = PS_DInfo.SPRITE_NAMES[spriteNum];
			int frameNum = -1;
			while (true)
			{
				frameNum++;
				// One way
				string frameChar = SCR_StringHelper.UPPERCASE[frameNum];
				string frameName = sriteName + frameChar + "0";
				if (m_mPatches.Contains(frameName))
				{
					PS_DPatch patch = m_mPatches[frameName];
					array<PS_DPatch> patches = {};
					array<bool> flips = {};
					for (int i = 0; i < 8; i++) // Fill all 8 ways
					{
						patches.Insert(patch);
						flips.Insert(false);
					}
					sprite.m_aFrames.Insert(patches);
					sprite.m_aFlips.Insert(flips);
					continue;
				}
				
				// 8 way
				array<PS_DPatch> patches = {};
				array<bool> flips = {};
				
				for (int i = 1; i <= 8; i++)
				{
					bool founded = false;
					frameName = sriteName + frameChar + i;
					if (m_mPatches.Contains(frameName))
					{
						PS_DPatch patch = m_mPatches[frameName];
						patches.Insert(patch);
						flips.Insert(false);
						continue;
					}
					for (int r = 1; r <= 8; r++)
					{
						frameName = sriteName + frameChar + i + frameChar + r;
						if (m_mPatches.Contains(frameName))
						{
							PS_DPatch patch = m_mPatches[frameName];
							patches.Insert(patch);
							flips.Insert(false);
							founded = true;
							break;
						}
					}
					if (founded)
						continue;
					for (int r = 1; r <= 8; r++)
					{
						frameName = sriteName + frameChar + r + frameChar + i;
						if (m_mPatches.Contains(frameName))
						{
							PS_DPatch patch = m_mPatches[frameName];
							patches.Insert(patch);
							flips.Insert(true);
							break;
						}
					}
				}
				
				if (patches.Count() == 0)
					break;
				
				sprite.m_aFrames.Insert(patches);
				sprite.m_aFlips.Insert(flips);
				
				/*
				frameName = sriteName + SCR_StringHelper.UPPERCASE[frameNum] + "1";
				if (m_mPatches.Contains(frameName))
				{
					array<PS_DPatch> patches = {};
					array<bool> flips = {};
					
					for (int i = 1; i <= 8; i++) // Fill all 8 ways
					{
						frameName = sriteName + SCR_StringHelper.UPPERCASE[frameNum] + i.ToString();
						if (m_mPatches.Contains(frameName))
						{
							PS_DPatch patch = m_mPatches[frameName];
							patches.Insert(patch);
							flips.Insert(false);
						}
						frameName = sriteName + SCR_StringHelper.UPPERCASE[frameNum] + i.ToString() + SCR_StringHelper.UPPERCASE[frameNum] + (10 - i).ToString();
						if (m_mPatches.Contains(frameName))
						{
							PS_DPatch patch = m_mPatches[frameName];
							patches.Insert(patch);
							flips.Insert(false);
						}
					}
					
					// reversed
					for (int i = 6; i <= 8; i++)
					{
						frameName = sriteName + SCR_StringHelper.UPPERCASE[frameNum] + (10 - i).ToString() + SCR_StringHelper.UPPERCASE[frameNum] + i.ToString();
						if (m_mPatches.Contains(frameName))
						{
							patches.Insert(m_mPatches[frameName]);
							flips.Insert(true);
						}
					}
					
					sprite.m_aFrames.Insert(patches);
					sprite.m_aFlips.Insert(flips);
					continue;
				}
				*/
			}
			
			m_aSprites.Insert(sprite);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadLump(FileHandle wadFile, PS_DLump lump, PS_EDLump lumpType, int size)
	{
		wadFile.Seek(lump.m_iFilepos);
		int count = lump.m_iSize / size;
		for (int i = 0; i < count; i++)
		{
			switch (lumpType)
			{
				case PS_EDLump.PS_DPalette:
					ReadPalettes(wadFile);
					break;
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadPalettes(FileHandle wadFile)
	{
		PS_DPalette palette = new PS_DPalette();
		for (int i = 0; i < 256; i++)
		{
			int r, g, b, a = 255;
			wadFile.Read(r, 1);
			wadFile.Read(g, 1);
			wadFile.Read(b, 1);
			int rgba = (a << 24) | (r << 16) | (g << 8) | (b << 0);
			
			palette.m_aColors[i] = rgba;
			palette.m_aColorsSRGB[i] = rgba;
			
			Color color = Color.FromInt(rgba);
			color.SRGBToLinear();
			palette.m_aColorsLinear[i] = color.PackToInt();
		}
		m_aPalletes.Insert(palette);
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadColorMap(FileHandle wadFile)
	{
		PS_DColorMap colorMap = new PS_DColorMap();
		for (int i = 0; i < PS_DColorMap.COLORMAPS_LENGTH; i++)
		{
			int data;
			wadFile.Read(data, 1);
			colorMap.m_aColors[i] = data;
		}
		m_aColorMaps.Insert(colorMap);
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadPatchNames(FileHandle wadFile, PS_DLump lump)
	{
		wadFile.Seek(lump.m_iFilepos);
		
		int count;
		wadFile.Read(count, 4);
		m_aPatchNames.Resize(count);
		for (int i = 0; i < count; i++)
		{
			m_aPatchNames[i] = PS_DWAD.ReadASCIIString(wadFile, 8);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadPatch(FileHandle wadFile, PS_DLump lump)
	{
		wadFile.Seek(lump.m_iFilepos);
		
		PS_DPatch patch = new PS_DPatch();
		PS_DPatchHeader patchHeader = new PS_DPatchHeader();
		PS_DPatchPixels texture = new PS_DPatchPixels();
		patch.m_DPatchHeader = patchHeader;
		patch.m_DTexture = texture;
		
		patchHeader.m_iWidth = PS_DWAD.ReadShort(wadFile);
		patchHeader.m_iHeight = PS_DWAD.ReadShort(wadFile);
		patchHeader.m_iLeftOffset = PS_DWAD.ReadShort(wadFile);
		patchHeader.m_iTopOffset = PS_DWAD.ReadShort(wadFile);
		patchHeader.m_iColumnInfo = {};
		for (int i = 0; i < patchHeader.m_iWidth; i++)
		{
			int offset;
			wadFile.Read(offset, 4);
			patchHeader.m_iColumnInfo.Insert(offset);
		}
		
		texture.m_aPixels.Resize(patchHeader.m_iWidth * patchHeader.m_iHeight);
		for (int i = 0; i < patchHeader.m_iWidth * patchHeader.m_iHeight; i++)
		{
			texture.m_aPixels[i] = 256;
		}
		for (int i = 0; i < patchHeader.m_iWidth; i++)
		{
			wadFile.Seek(lump.m_iFilepos + patchHeader.m_iColumnInfo[i]);
			
			int topDelta;
			wadFile.Read(topDelta, 1);
			while (topDelta != 255) // Column with gap
			{
				PS_DPatchColumn patchColumn = new PS_DPatchColumn();
				patchColumn.m_iTopDelta = topDelta;
				wadFile.Read(patchColumn.m_iLength, 1);
				wadFile.Read(patchColumn.m_iPaddingByte, 1);
				patchColumn.m_iData.Resize(patchColumn.m_iLength);
				for (int l = 0; l < patchColumn.m_iLength; l++)
				{
					int c;
					wadFile.Read(c, 1);
					int pixelI = i + (l + patchColumn.m_iTopDelta) * patchHeader.m_iWidth;
					texture.m_aPixels[pixelI] = c;
					patchColumn.m_iData[l] = c;
				}
				wadFile.Read(patchColumn.m_iPaddingByte2, 1);
				patch.m_aDPatchColumns.Insert(patchColumn);
				
				wadFile.Read(topDelta, 1);
			}
		}
		
		//Print(lump.m_sName);
		m_mPatches.Insert(lump.m_sName.Trim(), patch);
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadTextures(FileHandle wadFile, PS_DLump lump)
	{
		wadFile.Seek(lump.m_iFilepos);
		
		PS_DTextureHeader dTextureHeader = new PS_DTextureHeader();
		
		wadFile.Read(dTextureHeader.m_iNumTextures, 4);
		dTextureHeader.m_aTextureOffsets.Resize(dTextureHeader.m_iNumTextures);
		for (int i = 0; i < dTextureHeader.m_iNumTextures; i++)
		{
			int offset;
			wadFile.Read(offset, 4);
			dTextureHeader.m_aTextureOffsets[i] = offset;
		}
		
		dTextureHeader.m_aTextures.Resize(dTextureHeader.m_iNumTextures);
		for (int i = 0; i < dTextureHeader.m_iNumTextures; i++)
		{
			wadFile.Seek(lump.m_iFilepos + dTextureHeader.m_aTextureOffsets[i]);
			PS_DTextureMap dTextureMap = new PS_DTextureMap();
			
			dTextureMap.m_sName = PS_DWAD.ReadASCIIString(wadFile, 8);
			wadFile.Read(dTextureMap.m_iMasked, 4);
			dTextureMap.m_iWidth = PS_DWAD.ReadShort(wadFile);
			dTextureMap.m_iHeight = PS_DWAD.ReadShort(wadFile);
			wadFile.Read(dTextureMap.m_iColumnDirectory, 4);
			dTextureMap.m_iPatchCount = PS_DWAD.ReadShort(wadFile);
			dTextureMap.m_aPatches.Resize(dTextureMap.m_iPatchCount);
			for (int p = 0; p < dTextureMap.m_iPatchCount; p++)
			{
				PS_DPatchMap dPatchMap = new PS_DPatchMap();
				
				dPatchMap.m_iOriginX = PS_DWAD.ReadShort(wadFile);
				dPatchMap.m_iOriginY = PS_DWAD.ReadShort(wadFile);
				dPatchMap.m_iPatch = PS_DWAD.ReadShort(wadFile);
				dPatchMap.m_iStepDir = PS_DWAD.ReadShort(wadFile);
				dPatchMap.m_iColorMap = PS_DWAD.ReadShort(wadFile);
				
				dTextureMap.m_aPatches[p] = dPatchMap;
			}
			
			dTextureHeader.m_aTextures[i] = dTextureMap;
			dTextureMap.m_sName.ToUpper();
			m_mTextures.Insert(dTextureMap.m_sName, dTextureMap);
		}
		
		m_aTextureHeaders.Insert(dTextureHeader);
	}
	
	//------------------------------------------------------------------------------------------------
	void ReadFlat(FileHandle wadFile, PS_DLump lump)
	{
		wadFile.Seek(lump.m_iFilepos);
		
		PS_DTextureFlat textureFlat = new PS_DTextureFlat();
		textureFlat.m_sName = lump.m_sName;
		for (int i = 0; i < 4096; i++)
		{
			int color;
			wadFile.Read(color, 1);
			textureFlat.m_Pixels.m_aPixels[i] = color;
		}
		
		m_mFlatTextures.Insert(lump.m_sName, textureFlat);
	}
	
	//------------------------------------------------------------------------------------------------
	void PS_DAssets(PS_DWAD dWad)
	{
		m_DWad = dWad;
	}
}

class PS_DSprite
{
	ref array<ref array<PS_DPatch>> m_aFrames = {};
	ref array<ref array<bool>> m_aFlips = {};
}

modded enum PS_EDLump
{
	PS_DPalette,
	PS_DPatch,
	PS_DFlat,
}

class PS_DTextureHeader
{
	int m_iNumTextures;
	ref array<int> m_aTextureOffsets = {};
	ref array<ref PS_DTextureMap> m_aTextures = {};
}

// ---
class PS_DTextureFlat
{
	string m_sName;
	ref PS_DTextureFlatPixels m_Pixels = new PS_DTextureFlatPixels();;
	
}

class PS_DTextureFlatPixels
{
	int m_aPixels[4096];
}

// ---
class PS_DTexturePixels
{
	ref array<int> m_aPixels = {};
}

class PS_DTextureMap
{
	string m_sName;
	int m_iMasked;
	int m_iWidth;
	int m_iHeight;
	int m_iColumnDirectory;
	int m_iPatchCount;
	ref array<ref PS_DPatchMap> m_aPatches = {};
	
	// Cache
	ref PS_DTexturePixels m_TexturePixels;
}

class PS_DPatchMap
{
	int m_iOriginX;
	int m_iOriginY;
	int m_iPatch;
	int m_iStepDir;
	int m_iColorMap;
}

// ---
class PS_DPatchPixels
{
	ref array<int> m_aPixels = {};
}

class PS_DPalette
{
	int m_aColors[256];
	int m_aColorsSRGB[256];
	int m_aColorsLinear[256];
}

class PS_DColorMap
{
	static const int COLORMAPS_LENGTH = 256 * 34;
	int m_aColors[COLORMAPS_LENGTH];
}

class PS_DPatch
{
	ref PS_DPatchHeader m_DPatchHeader;
	ref PS_DPatchPixels m_DTexture;
	ref array<ref PS_DPatchColumn> m_aDPatchColumns = {};
}

class PS_DPatchHeader
{
	int m_iWidth;
	int m_iHeight;
	int m_iLeftOffset;
	int m_iTopOffset;
	ref array<int> m_iColumnInfo;
}

class PS_DPatchColumn
{
	int m_iTopDelta;
	int m_iLength;
	int m_iPaddingByte;
	ref array<int> m_iData = {};
	int m_iPaddingByte2;
}




