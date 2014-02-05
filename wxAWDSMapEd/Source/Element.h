#pragma once


#define ELEMENT_UNIT_EMPTY			0xFFFF
#define ELEMENT_UNIT_DELETE			0xFFFE
#define ELEMENT_TERRAIN_BLANK		0xFFFD

#define ELEMENT_TERRAIN_START		0
#define ELEMENT_TERRAIN_END			299
#define ELEMENT_BUILDING_START		300
#define ELEMENT_BUILDING_END		499
#define ELEMENT_UNIT_START			500
#define ELEMENT_UNIT_END			899
#define ELEMENT_EXTRA_START			900
#define ELEMENT_EXTRA_END			1299

#define ELEMENT_TERRAIN_COLUMNS		30
#define ELEMENT_BUILDING_COLUMNS	10
#define ELEMENT_UNIT_COLUMNS		20
#define ELEMENT_EXTRA_COLUMNS		20

#define ARMY_ORANGE_STAR	0
#define ARMY_BLUE_MOON		1
#define ARMY_GREEN_EARTH	2
#define ARMY_YELLOW_COMET	3
#define ARMY_BLACK_HOLE		4
#define ARMY_NEUTRAL		5

#define SPRITESHEETS_COUNT		5
#define SPRITESHEETS_TERRAIN	0
#define SPRITESHEETS_BUILDING	1
#define SPRITESHEETS_UNIT		2
#define SPRITESHEETS_EXTRA		3
#define SPRITESHEETS_MISC		4 // Cursors and etc.

#define TILESET_NORMAL		0
#define TILESET_SNOW		1
#define TILESET_DESERT		2
#define TILESET_WASTELAND	3
#define TILESET_AW1			4
#define TILESET_AW2			5
#define TILESET_LIMIT		6

#define MAKE_TERRAIN(x, y)	x + (y * ELEMENT_TERRAIN_COLUMNS) + ELEMENT_TERRAIN_START
#define MAKE_BUILDING(x, y)	x + (y * ELEMENT_BUILDING_COLUMNS) + ELEMENT_BUILDING_START
#define MAKE_UNIT(x, y)		x + (y * ELEMENT_UNIT_COLUMNS) + ELEMENT_UNIT_START
#define MAKE_EXTRA(x, y)	x + (y * ELEMENT_EXTRA_COLUMNS) + ELEMENT_EXTRA_START

#define MAPTYPE_UNKNOWN 1
#define MAPTYPE_AW1		2
#define MAPTYPE_AW2		3
#define MAPTYPE_AWDS	4
#define MAPTYPE_AWS001	5
//#define MAPTYPE_AW2ROM	6
//#define MAPTYPE_CWBETA9	7
#define MAPTYPE_DEFAULT	MAPTYPE_AWS001


#include "Element_Defaults.h"

class Element
{
protected:
	int m_value;

public:
	Element(int value = 0, int maptype = MAPTYPE_DEFAULT);
	bool operator==(int value);
	bool operator==(Element element);
	bool operator!=(int value);
	bool operator!=(Element element);

	int GetValue();
	bool SetValue(int value);
	int GetX(bool drawvalue = false);
	int GetY(bool drawvalue = false);

	bool IsTerrain();
	bool IsBuilding();
	bool IsUnit();
	bool IsExtra();

	bool IsBackground();
	bool IsForeground();
	bool IsUnitNonEmpty();
	bool DoubleHeight();

	int GetSpritesheet();
	int GetDrawX();
	int GetDrawY();
	bool Drawable();

	int GetSize();
	int GetTopLeft();
	bool GetLargeOffset(int& x, int& y);
	Element MakeFromLargeOffset(int x, int y);

	int GetArmy();
	bool ChangeArmy(int newarmy);
	int ChangeArmy(int newarmy, int return_int);
	Element ChangeArmy(int newarmy, Element return_element);

	Element Simplify();
	Element GetBase();
	Element GetNext();

	bool IsLand();
	bool IsSea();
	bool IsPipe();
	bool IsRoad();
	bool IsRiver();

	bool IsCompatible(int maptype);
	int ConvertFrom(int value, int maptype);
	int ConvertTo(int maptype);

	static int HeaderToMaptype(wxString header);
};

typedef Element Background;
typedef Element Foreground;
