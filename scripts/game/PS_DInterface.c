class PS_DInterface
{
	PS_DEntityPlayer m_Player;
	PS_DWAD m_DWad;
	PS_DAssets m_DAssets;
	
	// FACE
	static const int ST_FACESX = 143;
	static const int ST_FACESY	= 168;
	
	// AMMO number pos.
	static const int ST_AMMOWIDTH = 3;
	static const int ST_AMMOX = 44;
	static const int ST_AMMOY = 171;
	
	// HEALTH number pos.
	static const int ST_HEALTHWIDTH = 3;
	static const int ST_HEALTHX = 90;
	static const int ST_HEALTHY = 171;
	
	// Weapon pos.
	static const int ST_ARMSX = 111;
	static const int ST_ARMSY = 172;
	static const int ST_ARMSBGX = 104;
	static const int ST_ARMSBGY = 168;
	static const int ST_ARMSXSPACE = 12;
	static const int ST_ARMSYSPACE = 10;
	
	// Frags pos.
	static const int ST_FRAGSX = 138;
	static const int ST_FRAGSY = 171;
	static const int ST_FRAGSWIDTH = 2;
	
	// ARMOR number pos.
	static const int ST_ARMORWIDTH = 3;
	static const int ST_ARMORX = 221;
	static const int ST_ARMORY = 171;
	
	// Key icon positions.
	static const int ST_KEY0WIDTH = 8;
	static const int ST_KEY0HEIGHT = 5;
	static const int ST_KEY0X = 239;
	static const int ST_KEY0Y = 171;
	static const int ST_KEY1WIDTH = ST_KEY0WIDTH;
	static const int ST_KEY1X = 239;
	static const int ST_KEY1Y = 181;
	static const int ST_KEY2WIDTH = ST_KEY0WIDTH;
	static const int ST_KEY2X = 239;
	static const int ST_KEY2Y = 191;
	
	// Ammunition counter.
	static const int ST_AMMO0WIDTH = 3;
	static const int ST_AMMO0HEIGHT = 6;
	static const int ST_AMMO0X = 288;
	static const int ST_AMMO0Y = 173;
	static const int ST_AMMO1WIDTH = ST_AMMO0WIDTH;
	static const int ST_AMMO1X = 288;
	static const int ST_AMMO1Y = 179;
	static const int ST_AMMO2WIDTH = ST_AMMO0WIDTH;
	static const int ST_AMMO2X = 288;
	static const int ST_AMMO2Y = 191;
	static const int ST_AMMO3WIDTH = ST_AMMO0WIDTH;
	static const int ST_AMMO3X = 288;
	static const int ST_AMMO3Y = 185;
	
	// Indicate maximum ammunition.
	// Only needed because backpack exists.
	static const int ST_MAXAMMO0WIDTH = 3;
	static const int ST_MAXAMMO0HEIGHT = 5;
	static const int ST_MAXAMMO0X = 314;
	static const int ST_MAXAMMO0Y = 173;
	static const int ST_MAXAMMO1WIDTH = ST_MAXAMMO0WIDTH;
	static const int ST_MAXAMMO1X = 314;
	static const int ST_MAXAMMO1Y = 179;
	static const int ST_MAXAMMO2WIDTH = ST_MAXAMMO0WIDTH;
	static const int ST_MAXAMMO2X = 314;
	static const int ST_MAXAMMO2Y = 191;
	static const int ST_MAXAMMO3WIDTH = ST_MAXAMMO0WIDTH;
	static const int ST_MAXAMMO3X = 314;
	static const int ST_MAXAMMO3Y = 185;
	
	// pistol
	static const int ST_WEAPON0X = 110;
	static const int ST_WEAPON0Y = 172;
	
	// shotgun
	static const int ST_WEAPON1X = 122;
	static const int ST_WEAPON1Y = 172;
	
	// chain gun
	static const int ST_WEAPON2X = 134;
	static const int ST_WEAPON2Y = 172;
	
	// missile launcher
	static const int ST_WEAPON3X = 110;
	static const int ST_WEAPON3Y = 181;
	
	// plasma gun
	static const int ST_WEAPON4X = 122;
	static const int ST_WEAPON4Y = 181;
	
	// bfg
	static const int ST_WEAPON5X = 134;
	static const int ST_WEAPON5Y = 181;
	
	// WPNS title
	static const int ST_WPNSX = 109;
	static const int ST_WPNSY = 191;
	
	// DETH title
	static const int ST_DETHX = 109;
	static const int ST_DETHY = 191;
	
	PS_DPatch m_STBAR; // Main interface block
	static const int STBAR_SIZE = 320*32;
	int m_aSTBARPixels[STBAR_SIZE];
	int m_iInterfaceOffset = PS_DConst.SCREEN_WIDTH * (PS_DConst.SCREEN_HEIGHT - PS_DConst.SCREEN_INTERFACE_HEIGHT);
	PS_DPalette m_CurrentPallete;
	
	PS_DPatch m_STARMS; // Weapon interface block
	
	ref array<PS_DPatch> m_aAMMNUMs = {};
	ref array<PS_DPatch> m_aSTGNUMs = {};
	ref array<PS_DPatch> m_aSTTNUMs = {};
	ref array<PS_DPatch> m_aSTYSNUMs = {};
	ref array<PS_DPatch> m_aSTKEYS = {};
	ref array<PS_DPatch> m_aSTCFN = {}; // ASCII chars
	PS_DPatch m_STFDEAD0; // Dead face
	
	// Faces
	ref array<ref array<PS_DPatch>> m_aSTFST = {};
	
	void PS_DInterface(
	PS_DEntityPlayer player,
	PS_DWAD dWad,
	PS_DAssets dAssets,
	)
	{
		m_Player = player;
		m_DWad = dWad;
		m_DAssets = dAssets;
		
		m_CurrentPallete = m_DWad.m_DMain.m_DRenderer.m_CurrentPallete;
		
		m_STBAR = m_DAssets.m_mPatches["STBAR"];
		m_STARMS = m_DAssets.m_mPatches["STARMS"];
		
		UpdateSTBAR();
		
		for (int i = 0; i < 10; i++)
		{
			m_aAMMNUMs.Insert(m_DAssets.m_mPatches["AMMNUM" + i.ToString()]);
			m_aSTGNUMs.Insert(m_DAssets.m_mPatches["STGNUM" + i.ToString()]);
			m_aSTTNUMs.Insert(m_DAssets.m_mPatches["STTNUM" + i.ToString()]);
			m_aSTYSNUMs.Insert(m_DAssets.m_mPatches["STYSNUM" + i.ToString()]);
		if (i < 6)
			m_aSTKEYS.Insert(m_DAssets.m_mPatches["STKEYS" + i.ToString()]);
		} 
		m_aSTTNUMs.Insert(m_DAssets.m_mPatches["STTPRCNT"]);
		m_aSTTNUMs.Insert(m_DAssets.m_mPatches["STTMINUS"]);
		
		m_aSTCFN.Resize(122);
		for (int i = 33; i < 122; i++)
		{
			if (m_DAssets.m_mPatches.Contains("STCFN" + i.ToString(3)))
				m_aSTCFN[i] = m_DAssets.m_mPatches["STCFN" + i.ToString(3)];
		}
		
		for (int i = 0; i < 5; i++)
		{
			array<PS_DPatch> faces = {};
			faces.Insert(m_DAssets.m_mPatches["STFST" + i.ToString(1) + "1"]);
			faces.Insert(m_DAssets.m_mPatches["STFST" + i.ToString(1) + "0"]);
			faces.Insert(m_DAssets.m_mPatches["STFST" + i.ToString(1) + "2"]);
			faces.Insert(m_DAssets.m_mPatches["STFTL" + i.ToString(1) + "0"]);
			faces.Insert(m_DAssets.m_mPatches["STFTR" + i.ToString(1) + "0"]);
			faces.Insert(m_DAssets.m_mPatches["STFOUCH" + i.ToString(1)]);
			faces.Insert(m_DAssets.m_mPatches["STFEVL" + i.ToString(1)]);
			faces.Insert(m_DAssets.m_mPatches["STFKILL" + i.ToString(1)]);
			m_aSTFST.Insert(faces);
		}
		m_STFDEAD0 = m_DAssets.m_mPatches["STFDEAD0"];
	}
	
	void UpdateSTBAR()
	{
		PS_DPalette pallete = m_CurrentPallete;
		for (int i = 0; i < STBAR_SIZE; i++)
		{
			int colorIndex = m_STBAR.m_DTexture.m_aPixels[i];
			m_aSTBARPixels[i] = pallete.m_aColors[colorIndex];
		}
		
		for (int x = 0; x < 40; x++)
		{
			for (int y = 0; y < 32; y++)
			{
				int colorIndex = m_STARMS.m_DTexture.m_aPixels[x + y * 40];
				int pixelIndex = x + ST_ARMSBGX + y * 320;
				m_aSTBARPixels[pixelIndex] = pallete.m_aColors[colorIndex];
			}
		}
	}
	
	void Draw()
	{
		PS_DPalette pallete = m_DWad.m_DMain.m_DRenderer.m_CurrentPallete;
		if (m_CurrentPallete != pallete)
		{
			m_CurrentPallete = pallete;
			UpdateSTBAR();
		}
		
		int weaponOffset = 24;
		PS_DPatch weaponPatch = m_Player.m_CurrentWeapon.m_FramePatches[m_Player.m_CurrentWeaponState.m_iFrame];
		
		int xBob, yBob;
		if (m_Player.m_iWeaponReady > 0)
		{
			float timeFactor = (float) m_Player.m_DMap.m_iTickNum / 10;
			float speedFactor = m_Player.m_vVelocity.Length();
			xBob = -Math.Cos(timeFactor) * speedFactor * 2;
			yBob = -Math.Cos(timeFactor*2) * speedFactor;
		}
		DrawPatch(xBob, weaponOffset + m_Player.m_iWeaponY + yBob, weaponPatch, true);
		
		// FIXME, at least cache
		if (m_Player.m_CurrentFlashState)
		{
			PS_DMobjState flashState = m_Player.m_CurrentFlashState;
			string flashName = PS_DInfo.SPRITE_NAMES[flashState.m_SpriteNum];
			int frame = flashState.m_iFrame;
			if (frame > 32767) // Light sprites
				frame -= 32768; // TODO: light
			PS_DPatch flashPatch = m_DAssets.m_mPatches[flashName + SCR_StringHelper.UPPERCASE[frame] + "0"];
			DrawPatch(0, weaponOffset, flashPatch);
		}
		
		StaticArray.Copy(PS_EddsTextureCanvasComponent.m_aPixels, m_aSTBARPixels, m_iInterfaceOffset);
		//DrawPatch(0, 168, m_STBAR);
		//DrawPatch(ST_ARMSBGX, ST_ARMSBGY, m_STARMS);
		
		DrawAmmo();
		DrawHealth();
		DrawArmour();
		
		int faceDamageId = 4 - m_Player.m_iHealth / 25;
		if (faceDamageId < 0)
			faceDamageId = 0;
		
		if (m_Player.m_bDead)
			DrawPatch(ST_FACESX, ST_FACESY, m_STFDEAD0);
		else
			DrawPatch(ST_FACESX, ST_FACESY, m_aSTFST[faceDamageId][m_Player.m_iCurrentFace]);
		
		DrawWeapons();
		
		DrawAmmo(ST_AMMO0X, ST_AMMO0Y, m_Player.m_aAmmo[0]);
		DrawAmmo(ST_AMMO1X, ST_AMMO1Y, m_Player.m_aAmmo[1]);
		DrawAmmo(ST_AMMO3X, ST_AMMO3Y, m_Player.m_aAmmo[3]);
		DrawAmmo(ST_AMMO2X, ST_AMMO2Y, m_Player.m_aAmmo[2]);
		
		DrawAmmo(ST_MAXAMMO0X, ST_MAXAMMO0Y, m_Player.m_aAmmoMax[0]);
		DrawAmmo(ST_MAXAMMO1X, ST_MAXAMMO1Y, m_Player.m_aAmmoMax[1]);
		DrawAmmo(ST_MAXAMMO3X, ST_MAXAMMO3Y, m_Player.m_aAmmoMax[3]);
		DrawAmmo(ST_MAXAMMO2X, ST_MAXAMMO2Y, m_Player.m_aAmmoMax[2]);
		
		DrawKeys();
		
		DrawMessages();
	}
	
	void DrawMessages()
	{
		int y = m_Player.m_iMessagesOffset;
		foreach (string message : m_Player.m_aMessages)
		{
			DrawMessage(0, y, message);
			y += 8;
		}
	}
	
	void DrawMessage(int x, int y, string message)
	{
		message.ToUpper();
		for (int i = 0; i < message.Length(); i++)
		{
			int char = message.ToAscii(i);
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
	
	void DrawKeys()
	{
		if (m_Player.m_aKeys[0] > 0)
		{
			if (m_Player.m_aKeys[0] == 1)
				DrawPatch(ST_KEY0X, ST_KEY0Y, m_aSTKEYS[0]);
			else
				DrawPatch(ST_KEY0X, ST_KEY0Y, m_aSTKEYS[3]);
		}
		if (m_Player.m_aKeys[1] > 0)
		{
			if (m_Player.m_aKeys[1] == 1)
				DrawPatch(ST_KEY1X, ST_KEY1Y, m_aSTKEYS[1]);
			else
				DrawPatch(ST_KEY1X, ST_KEY1Y, m_aSTKEYS[4]);
		}
		if (m_Player.m_aKeys[2] > 0)
		{
			if (m_Player.m_aKeys[2] == 1)
				DrawPatch(ST_KEY2X, ST_KEY2Y, m_aSTKEYS[2]);
			else
				DrawPatch(ST_KEY2X, ST_KEY2Y, m_aSTKEYS[5]);
		}
	}
	
	void DrawAmmo(int x, int y, int count)
	{
		for (int i = 0; i < 3; i++)
		{
			PS_DPatch patch = m_aSTYSNUMs[Math.Mod(count, 10)];
			x -= patch.m_DPatchHeader.m_iWidth;
			DrawPatch(x, y, patch);
			count = count / 10;
			if (count == 0)
				break;
		}
	}
	
	void DrawWeapons()
	{
		if (m_Player.m_aWeapons[1] == 1)
			DrawPatch(ST_WEAPON0X, ST_WEAPON0Y, m_aSTYSNUMs[2]);
		else
			DrawPatch(ST_WEAPON0X, ST_WEAPON0Y, m_aSTGNUMs[2]);
		if (m_Player.m_aWeapons[2] == 1)
			DrawPatch(ST_WEAPON1X, ST_WEAPON1Y, m_aSTYSNUMs[3]);
		else
			DrawPatch(ST_WEAPON1X, ST_WEAPON1Y, m_aSTGNUMs[3]);
		if (m_Player.m_aWeapons[3] == 1)
			DrawPatch(ST_WEAPON2X, ST_WEAPON2Y, m_aSTYSNUMs[4]);
		else
			DrawPatch(ST_WEAPON2X, ST_WEAPON2Y, m_aSTGNUMs[4]);
		if (m_Player.m_aWeapons[4] == 1)
			DrawPatch(ST_WEAPON3X, ST_WEAPON3Y, m_aSTYSNUMs[5]);
		else
			DrawPatch(ST_WEAPON3X, ST_WEAPON3Y, m_aSTGNUMs[5]);
		if (m_Player.m_aWeapons[5] == 1)
			DrawPatch(ST_WEAPON4X, ST_WEAPON4Y, m_aSTYSNUMs[6]);
		else
			DrawPatch(ST_WEAPON4X, ST_WEAPON4Y, m_aSTGNUMs[6]);
		if (m_Player.m_aWeapons[6] == 1)
			DrawPatch(ST_WEAPON5X, ST_WEAPON5Y, m_aSTYSNUMs[7]);
		else
			DrawPatch(ST_WEAPON5X, ST_WEAPON5Y, m_aSTGNUMs[7]);
	}
	
	void DrawAmmo()
	{
		if (m_Player.m_CurrentWeapon.m_iAmmoType > 3)
			return;
		
		int ammo = m_Player.m_aAmmo[m_Player.m_CurrentWeapon.m_iAmmoType];
		int x = ST_AMMOX;
		for (int i = 0; i < 3; i++)
		{
			PS_DPatch patch = m_aSTTNUMs[Math.Mod(ammo, 10)];
			x -= patch.m_DPatchHeader.m_iWidth;
			DrawPatch(x, ST_AMMOY, patch);
			ammo = ammo / 10;
			if (ammo == 0)
				break;
		}
	}
	
	void DrawHealth()
	{
		PS_DPatch patch = m_aSTTNUMs[10];
		DrawPatch(ST_HEALTHX, ST_HEALTHY, patch);
		int health = m_Player.m_iHealth;
		int x = ST_HEALTHX - patch.m_DPatchHeader.m_iWidth;
		for (int i = 0; i < 3; i++)
		{
			patch = m_aSTTNUMs[Math.Mod(health, 10)];
			DrawPatch(x, ST_HEALTHY, patch);
			x -= patch.m_DPatchHeader.m_iWidth;
			health = health / 10;
			if (health == 0)
				break;
		}
	}
	
	void DrawArmour()
	{
		PS_DPatch patch = m_aSTTNUMs[10];
		DrawPatch(ST_ARMORX, ST_ARMORY, patch);
		int armour = m_Player.m_iArmour;
		int x = ST_ARMORX - patch.m_DPatchHeader.m_iWidth;
		for (int i = 0; i < 3; i++)
		{
			patch = m_aSTTNUMs[Math.Mod(armour, 10)];
			DrawPatch(x, ST_ARMORY, patch);
			x -= patch.m_DPatchHeader.m_iWidth;
			armour = armour / 10;
			if (armour == 0)
				break;
		}
	}
	void DrawPatch(int x, int y, PS_DPatch patch, bool hide = false)
	{
		PS_DPalette pallete = m_CurrentPallete;
		x -= patch.m_DPatchHeader.m_iLeftOffset;
		y -= patch.m_DPatchHeader.m_iTopOffset;
		int width = patch.m_DPatchHeader.m_iWidth;
		int height = patch.m_DPatchHeader.m_iHeight;
		
		int y1 = y;
		int y2 = y + height;
		y1 *= PS_DConst.SCREEN_WIDTH;
		y2 *= PS_DConst.SCREEN_WIDTH;
		
		int x2 = x + width;
		int xp = 0;
		for (x; x < x2; x++)
		{
			int yp = 0;
			for (y = y1; y < y2; y += PS_DConst.SCREEN_WIDTH)
			{
				if (hide && y > 53760)
					break;
				int colorIndex = patch.m_DTexture.m_aPixels[xp + yp];
				if (colorIndex != 256)
				{
					int color = pallete.m_aColors[colorIndex];
					int pixelIndex = x + y;
					if (pixelIndex < PS_EddsTextureCanvasComponent.SCREEN_SIZE)
						PS_EddsTextureCanvasComponent.m_aPixels[pixelIndex] = color;
				}
				yp += width;
			}
			xp++;
		}
	}
}













