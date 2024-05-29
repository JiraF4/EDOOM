class PS_DConst
{
	static const float FRACUNIT = 1;
	
	static const int TICRATE = 35;
	
	static const int SCREEN_WIDTH = 320;
	static const int SCREEN_HEIGHT = 200;
	static const int SCREEN_INTERFACE_HEIGHT = 32;
	static const int SCREEN_HEIGHT_VIEW = SCREEN_HEIGHT - SCREEN_INTERFACE_HEIGHT;
	static const int SCREEN_WIDTH_HALF = SCREEN_WIDTH/2;
	static const int SCREEN_HEIGHT_O = SCREEN_HEIGHT-1;
	static const int SCREEN_HEIGHT_HALF = SCREEN_HEIGHT/2;
	
	static const float HORIZONTAL_FOV = 90*Math.DEG2RAD;
	static const float HORIZONTAL_FOV_EXT = 180*Math.DEG2RAD;
	static const float HORIZONTAL_FOV_HALF = HORIZONTAL_FOV/2;
	static const float Z_FAR = 512.0;
	static const float CAMERA_HEIGHT = 42;
	
	static const int SUB_SECTOR_IDENTIFIER = 2 << 14;
	
	static const float SCREEN_Z = SCREEN_WIDTH_HALF / Math.Tan(HORIZONTAL_FOV_HALF);
	
	static const float MAX_SCALE = 64.0;
	static const float MIN_SCALE = 0.00390625;
	
	static const int MAX_LIGHT_LEVEL = 31;
	static const int LIGHT_Z_MAX = 16;
	static const float LIGHT_Z_SCALE = 0.08;
	static const float LIGHT_WORLD_SCALE = 4;
	static const float LIGHT_WORLD_SCALE_SPRITE = 4;
	
	static const int SAVE_PREVIEW_WIDTH = 143;
	static const int SAVE_PREVIEW_HEIGHT = 88;
	static const int SAVE_PREVIEW_SIZE = SAVE_PREVIEW_WIDTH * SAVE_PREVIEW_HEIGHT;
}

enum PS_EDLineDefsFlags
{
	BLOCKING = 1,
	BLOCK_MONSTERS = 2,
	TWO_SIDED = 4,
	DONT_PEG_TOP = 8,
	DONT_PEG_BOTTOM = 16,
	SECRET = 32,
	SOUND_BLOCK = 64,
	DONT_DRAW = 128,
	MAPPED = 256
}

enum PS_EDThingFlag
{
	MTF_EASY = 1,
	MTF_NORMAL = 2,
	MTF_HARD = 4,
	MTF_AMBUSH = 8,
	MTF_MULTIPLAYERONLY = 16
}

enum PS_EDMobjFlag
{
	 // Call P_SpecialThing when touched.
    MF_SPECIAL		= 1,
    // Blocks.
    MF_SOLID		= 2,
    // Can be hit.
    MF_SHOOTABLE	= 4,
    // Don't use the sector links (invisible but touchable).
    MF_NOSECTOR		= 8,
    // Don't use the blocklinks (inert but displayable)
    MF_NOBLOCKMAP	= 16,                    

    // Not to be activated by sound, deaf monster.
    MF_AMBUSH		= 32,
    // Will try to attack right back.
    MF_JUSTHIT		= 64,
    // Will take at least one step before attacking.
    MF_JUSTATTACKED	= 128,
    // On level spawning (initial position),
    //  hang from ceiling instead of stand on floor.
    MF_SPAWNCEILING	= 256,
    // Don't apply gravity (every tic),
    //  that is, object will float, keeping current height
    //  or changing it actively.
    MF_NOGRAVITY	= 512,

    // Movement flags.
    // This allows jumps from high places.
    MF_DROPOFF		= 0x400,
    // For players, will pick up items.
    MF_PICKUP		= 0x800,
    // Player cheat. ???
    MF_NOCLIP		= 0x1000,
    // Player: keep info about sliding along walls.
    MF_SLIDE		= 0x2000,
    // Allow moves to any height, no gravity.
    // For active floaters, e.g. cacodemons, pain elementals.
    MF_FLOAT		= 0x4000,
    // Don't cross lines
    //   ??? or look at heights on teleport.
    MF_TELEPORT		= 0x8000,
    // Don't hit same species, explode on block.
    // Player missiles as well as fireballs of various kinds.
    MF_MISSILE		= 0x10000,	
    // Dropped by a demon, not level spawned.
    // E.g. ammo clips dropped by dying former humans.
    MF_DROPPED		= 0x20000,
    // Use fuzzy draw (shadow demons or spectres),
    //  temporary player invisibility powerup.
    MF_SHADOW		= 0x40000,
    // Flag: don't bleed when shot (use puff),
    //  barrels and shootable furniture shall not bleed.
    MF_NOBLOOD		= 0x80000,
    // Don't stop moving halfway off a step,
    //  that is, have dead bodies slide down all the way.
    MF_CORPSE		= 0x100000,
    // Floating to a height for a move, ???
    //  don't auto float to target's height.
    MF_INFLOAT		= 0x200000,

    // On kill, count this enemy object
    //  towards intermission kill total.
    // Happy gathering.
    MF_COUNTKILL	= 0x400000,
    
    // On picking up, count this item object
    //  towards intermission item total.
    MF_COUNTITEM	= 0x800000,

    // Special handling: skull in flight.
    // Neither a cacodemon nor a missile.
    MF_SKULLFLY		= 0x1000000,

    // Don't spawn this object
    //  in death match mode (e.g. key cards).
    MF_NOTDMATCH    	= 0x2000000,

    // Player sprites in multiplayer modes are modified
    //  using an internal color lookup table for re-indexing.
    // If 0x4 0x8 or 0xc,
    //  use a translation table for player colormaps
    MF_TRANSLATION  	= 0xc000000,
    // Hmm ???.
    MF_TRANSSHIFT	= 26
}