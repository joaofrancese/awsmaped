// To be used ONLY in DrawPanel.cpp in DrawPanel's constructor!

char** spritesheetdata[SPRITESHEETS_COUNT][TILESETS_NUMBER];
char** spritesheetmask[SPRITESHEETS_COUNT][TILESETS_NUMBER];

#include "../Resource/spritesheets/building_00.xpm"
#include "../Resource/spritesheets/building_00m.xpm"
#include "../Resource/spritesheets/building_01.xpm"
#include "../Resource/spritesheets/building_02.xpm"
#include "../Resource/spritesheets/building_04.xpm"
#include "../Resource/spritesheets/building_04m.xpm"
#include "../Resource/spritesheets/building_05.xpm"
#include "../Resource/spritesheets/building_05m.xpm"

#include "../Resource/spritesheets/extra_00.xpm"
#include "../Resource/spritesheets/extra_00m.xpm"
#include "../Resource/spritesheets/extra_01.xpm"
#include "../Resource/spritesheets/extra_02.xpm"
#include "../Resource/spritesheets/extra_03.xpm"
#include "../Resource/spritesheets/extra_04.xpm"

#include "../Resource/spritesheets/misc_00.xpm"
#include "../Resource/spritesheets/misc_00m.xpm"
#include "../Resource/spritesheets/misc_04.xpm"
#include "../Resource/spritesheets/misc_04m.xpm"
#include "../Resource/spritesheets/misc_05.xpm"
#include "../Resource/spritesheets/misc_05m.xpm"

#include "../Resource/spritesheets/terrain_00.xpm"
#include "../Resource/spritesheets/terrain_00m.xpm"
#include "../Resource/spritesheets/terrain_01.xpm"
#include "../Resource/spritesheets/terrain_02.xpm"
#include "../Resource/spritesheets/terrain_03.xpm"
#include "../Resource/spritesheets/terrain_04.xpm"
#include "../Resource/spritesheets/terrain_04m.xpm"
#include "../Resource/spritesheets/terrain_05.xpm"

#include "../Resource/spritesheets/unit_00.xpm"
#include "../Resource/spritesheets/unit_00m.xpm"
#include "../Resource/spritesheets/unit_04.xpm"
#include "../Resource/spritesheets/unit_04m.xpm"

spritesheetdata[SPRITESHEETS_TERRAIN][00]	= terrain_00_xpm;
spritesheetdata[SPRITESHEETS_BUILDING][00]	= building_00_xpm;
spritesheetdata[SPRITESHEETS_UNIT][00]		= unit_00_xpm;
spritesheetdata[SPRITESHEETS_EXTRA][00]		= extra_00_xpm;
spritesheetdata[SPRITESHEETS_MISC][00]		= misc_00_xpm;

spritesheetdata[SPRITESHEETS_TERRAIN][01]	= terrain_01_xpm;
spritesheetdata[SPRITESHEETS_BUILDING][01]	= building_01_xpm;
spritesheetdata[SPRITESHEETS_UNIT][01]		= unit_00_xpm;		// Copy.
spritesheetdata[SPRITESHEETS_EXTRA][01]		= extra_01_xpm;
spritesheetdata[SPRITESHEETS_MISC][01]		= misc_00_xpm;		// Copy.

spritesheetdata[SPRITESHEETS_TERRAIN][02]	= terrain_02_xpm;
spritesheetdata[SPRITESHEETS_BUILDING][02]	= building_02_xpm;
spritesheetdata[SPRITESHEETS_UNIT][02]		= unit_00_xpm;		// Copy.
spritesheetdata[SPRITESHEETS_EXTRA][02]		= extra_02_xpm;
spritesheetdata[SPRITESHEETS_MISC][02]		= misc_00_xpm;		// Copy.

spritesheetdata[SPRITESHEETS_TERRAIN][03]	= terrain_03_xpm;
spritesheetdata[SPRITESHEETS_BUILDING][03]	= building_02_xpm;	// Copy.
spritesheetdata[SPRITESHEETS_UNIT][03]		= unit_00_xpm;		// Copy.
spritesheetdata[SPRITESHEETS_EXTRA][03]		= extra_03_xpm;
spritesheetdata[SPRITESHEETS_MISC][03]		= misc_00_xpm;		// Copy.

spritesheetdata[SPRITESHEETS_TERRAIN][04]	= terrain_04_xpm;
spritesheetdata[SPRITESHEETS_BUILDING][04]	= building_04_xpm;
spritesheetdata[SPRITESHEETS_UNIT][04]		= unit_04_xpm;
spritesheetdata[SPRITESHEETS_EXTRA][04]		= extra_04_xpm;
spritesheetdata[SPRITESHEETS_MISC][04]		= misc_04_xpm;

spritesheetdata[SPRITESHEETS_TERRAIN][05]	= terrain_05_xpm;
spritesheetdata[SPRITESHEETS_BUILDING][05]	= building_05_xpm;
spritesheetdata[SPRITESHEETS_UNIT][05]		= unit_04_xpm;		// Copy.
spritesheetdata[SPRITESHEETS_EXTRA][05]		= extra_04_xpm;		// Copy
spritesheetdata[SPRITESHEETS_MISC][05]		= misc_05_xpm;




spritesheetmask[SPRITESHEETS_TERRAIN][00]	= terrain_00m_xpm;
spritesheetmask[SPRITESHEETS_BUILDING][00]	= building_00m_xpm;
spritesheetmask[SPRITESHEETS_UNIT][00]		= unit_00m_xpm;
spritesheetmask[SPRITESHEETS_EXTRA][00]		= extra_00m_xpm;
spritesheetmask[SPRITESHEETS_MISC][00]		= misc_00m_xpm;

spritesheetmask[SPRITESHEETS_TERRAIN][01]	= terrain_00m_xpm;	// Copy
spritesheetmask[SPRITESHEETS_BUILDING][01]	= building_00m_xpm;	// Copy
spritesheetmask[SPRITESHEETS_UNIT][01]		= unit_00m_xpm;		// Copy
spritesheetmask[SPRITESHEETS_EXTRA][01]		= extra_00m_xpm;	// Copy
spritesheetmask[SPRITESHEETS_MISC][01]		= misc_00m_xpm;		// Copy

spritesheetmask[SPRITESHEETS_TERRAIN][02]	= terrain_00m_xpm;	// Copy
spritesheetmask[SPRITESHEETS_BUILDING][02]	= building_00m_xpm;	// Copy
spritesheetmask[SPRITESHEETS_UNIT][02]		= unit_00m_xpm;		// Copy
spritesheetmask[SPRITESHEETS_EXTRA][02]		= extra_00m_xpm;	// Copy
spritesheetmask[SPRITESHEETS_MISC][02]		= misc_00m_xpm;		// Copy

spritesheetmask[SPRITESHEETS_TERRAIN][03]	= terrain_00m_xpm;	// Copy
spritesheetmask[SPRITESHEETS_BUILDING][03]	= building_00m_xpm;	// Copy
spritesheetmask[SPRITESHEETS_UNIT][03]		= unit_00m_xpm;		// Copy
spritesheetmask[SPRITESHEETS_EXTRA][03]		= extra_00m_xpm;	// Copy
spritesheetmask[SPRITESHEETS_MISC][03]		= misc_00m_xpm;		// Copy

spritesheetmask[SPRITESHEETS_TERRAIN][04]	= terrain_04m_xpm;
spritesheetmask[SPRITESHEETS_BUILDING][04]	= building_04m_xpm;
spritesheetmask[SPRITESHEETS_UNIT][04]		= unit_04m_xpm;
spritesheetmask[SPRITESHEETS_EXTRA][04]		= extra_00m_xpm;	// Copy
spritesheetmask[SPRITESHEETS_MISC][04]		= misc_04m_xpm;

spritesheetmask[SPRITESHEETS_TERRAIN][05]	= terrain_04m_xpm;	// Copy
spritesheetmask[SPRITESHEETS_BUILDING][05]	= building_05m_xpm;
spritesheetmask[SPRITESHEETS_UNIT][05]		= unit_04m_xpm;		// Copy
spritesheetmask[SPRITESHEETS_EXTRA][05]		= extra_00m_xpm;	// Copy
spritesheetmask[SPRITESHEETS_MISC][05]		= misc_05m_xpm;

