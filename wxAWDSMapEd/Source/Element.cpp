#include "precomp.h"
#include "Element.h"

Element::Element(int value, int maptype)
{
	m_value = value;
	m_value = ConvertFrom(value, maptype);
}

bool Element::operator==(int value)
{
	return (*this == Element(value));
}

bool Element::operator==(Element element)
{
	return m_value == element.GetValue();
}

bool Element::operator!=(int value)
{
	return (*this != Element(value));
}

bool Element::operator!=(Element element)
{
	return m_value != element.GetValue();
}

int Element::GetValue()
{
	return m_value;
}


bool Element::SetValue(int value)
{
	m_value = value;
	return true;
}

int Element::GetX(bool drawvalue)
{
	if (GetValue() == ELEMENT_UNIT_DELETE)
		return 0;
	if (IsTerrain())
		return (GetValue() - ELEMENT_TERRAIN_START) % ELEMENT_TERRAIN_COLUMNS;
	if (IsBuilding())
		return (GetValue() - ELEMENT_BUILDING_START) % ELEMENT_BUILDING_COLUMNS;
	if (IsUnit())
		return (GetValue() - ELEMENT_UNIT_START) % ELEMENT_UNIT_COLUMNS;
	if (IsExtra())
		return (GetValue() - ELEMENT_EXTRA_START) % ELEMENT_EXTRA_COLUMNS;
	return 0;
}

int Element::GetY(bool drawvalue)
{
	if (GetValue() == ELEMENT_UNIT_DELETE)
		return 4;
	if (!DoubleHeight() || !drawvalue)
	{
		if (IsTerrain())
			return (GetValue() - ELEMENT_TERRAIN_START) / ELEMENT_TERRAIN_COLUMNS;
		if (IsBuilding())
			return (GetValue() - ELEMENT_BUILDING_START) / ELEMENT_BUILDING_COLUMNS;
		if (IsUnit())
			return (GetValue() - ELEMENT_UNIT_START) / ELEMENT_UNIT_COLUMNS;
		if (IsExtra())
			return (GetValue() - ELEMENT_EXTRA_START) / ELEMENT_EXTRA_COLUMNS;
	}
	else
	{
		if (IsTerrain())
			return ((GetValue() - ELEMENT_TERRAIN_START) / ELEMENT_TERRAIN_COLUMNS) - 1;
		if (IsBuilding())
			return ((GetValue() - ELEMENT_BUILDING_START) / ELEMENT_BUILDING_COLUMNS) * 2;
		if (IsUnit())
			return ((GetValue() - ELEMENT_UNIT_START) / ELEMENT_UNIT_COLUMNS) - 1;
		if (IsExtra())
			return ((GetValue() - ELEMENT_EXTRA_START) / ELEMENT_EXTRA_COLUMNS) - 1;
	}
	return 0;
}

bool Element::IsTerrain()
{
	if (m_value >= ELEMENT_TERRAIN_START && m_value <= ELEMENT_TERRAIN_END)
		return true;
	if (m_value == ELEMENT_TERRAIN_BLANK)
		return true;
	return false;
}

bool Element::IsBuilding()
{
	if (m_value >= ELEMENT_BUILDING_START && m_value <= ELEMENT_BUILDING_END)
		return true;
	return false;
}

bool Element::IsUnit()
{
	if (m_value >= ELEMENT_UNIT_START && m_value <= ELEMENT_UNIT_END)
		return true;
	if (m_value == ELEMENT_UNIT_EMPTY)
		return true;
	if (m_value == ELEMENT_UNIT_DELETE)
		return true;
	return false;
}

bool Element::IsExtra()
{
	if (m_value >= ELEMENT_EXTRA_START && m_value <= ELEMENT_EXTRA_END)
		return true;
	return false;
}

bool Element::IsBackground()
{
	if (IsTerrain() || IsBuilding() || IsExtra())
		return true;
	return false;
}

bool Element::IsForeground()
{
	if (IsUnit())
		return true;
	return false;
}

bool Element::IsUnitNonEmpty()
{
	if (m_value >= ELEMENT_UNIT_START && m_value <= ELEMENT_UNIT_END)
		return true;
	return false;
}

bool Element::DoubleHeight()
{
	if (IsBuilding())
		return true;
	if (GetValue() == MAKE_TERRAIN(0, 7))	// Tall mountain.
		return true;
	if (GetValue() == EXTRA_BCRYSTAL)
		return true;
	if (GetValue() == EXTRA_DEATHRAY)	// The palette mini-icon.
		return true;
	if (GetValue() == EXTRA_GSILO)		// The palette mini-icon.
		return true;
	return false;
}

int Element::GetSpritesheet()
{
	if (IsTerrain() || GetValue() == ELEMENT_UNIT_DELETE)
		return SPRITESHEETS_TERRAIN;
	if (IsBuilding())
		return SPRITESHEETS_BUILDING;
	if (IsUnit())
		return SPRITESHEETS_UNIT;
	if (IsExtra())
		return SPRITESHEETS_EXTRA;
	return 0;
}

int Element::GetDrawX()
{
	return GetX(true);
}

int Element::GetDrawY()
{
	return GetY(true);
}

bool Element::Drawable()
{
	if (GetValue() == ELEMENT_TERRAIN_BLANK)
		return false;
	if (IsTerrain() || IsBuilding() || IsExtra() || IsUnitNonEmpty() || GetValue() == ELEMENT_UNIT_DELETE)
		return true;
	return false;
}

int Element::GetSize()
{
	if (IsExtra())
	{
		int value = Simplify().GetValue();
		if (value == EXTRA_BCANNONN || value == EXTRA_BCANNONS || value == EXTRA_DEATHRAY || value == EXTRA_BOBELISK)
			return 3;
		else if (value == EXTRA_VOLCANO || value == EXTRA_FORTRESS || value == EXTRA_GSILO || value == EXTRA_BLACKARC || value == EXTRA_SEAARC)
			return 4;
		else
			return 1;
	}
	else
		return 1;
}

int Element::GetTopLeft()
{
	if (GetSize() == 1)
		return GetValue();

	switch (Simplify().GetValue())
	{
	case EXTRA_BCANNONS:
		return MAKE_EXTRA(0, 2);
	case EXTRA_BCANNONN:
		return MAKE_EXTRA(3, 2);
	case EXTRA_DEATHRAY:
		return MAKE_EXTRA(0, 5);
	case EXTRA_BOBELISK:
		return MAKE_EXTRA(3, 5);
	case EXTRA_VOLCANO:
		return MAKE_EXTRA(7, 0);
	case EXTRA_GSILO:
		return MAKE_EXTRA(11, 0);
	case EXTRA_FORTRESS:
		return MAKE_EXTRA(7, 4);
	case EXTRA_BLACKARC:
		return MAKE_EXTRA(11, 4);
	case EXTRA_SEAARC:
		return MAKE_EXTRA(15, 4);
	default:
		return GetValue();
	}
}

bool Element::GetLargeOffset(int& x, int& y)
{
	if (GetSize() == 1 || *this == Simplify())
		return false;

	int value = GetValue() - GetTopLeft();
	x = value % ELEMENT_EXTRA_COLUMNS;
	y = value / ELEMENT_EXTRA_COLUMNS;
	return true;
}

Element Element::MakeFromLargeOffset(int x, int y)
{
	if (GetSize() == 1 || *this == Simplify())
		return Element(GetValue());

	int basevalue = Element(GetTopLeft()).GetValue() - ELEMENT_EXTRA_START;
	x += basevalue % ELEMENT_EXTRA_COLUMNS;
	y += basevalue / ELEMENT_EXTRA_COLUMNS;
	return Element(MAKE_EXTRA(x, y));
}

int Element::GetArmy()
{
	if (IsUnitNonEmpty())
		return ((m_value - ELEMENT_UNIT_START) / ELEMENT_UNIT_COLUMNS) / 2;
	if (IsBuilding())
		return (m_value - ELEMENT_BUILDING_START) / ELEMENT_BUILDING_COLUMNS;
	return 0;
}

bool Element::ChangeArmy(int newarmy)
{
	if (IsUnitNonEmpty())
	{
		if (newarmy < 0 || newarmy >= ARMY_NEUTRAL)
			return false;
		m_value = Simplify().GetValue() + (newarmy * ELEMENT_UNIT_COLUMNS * 2);
		return true;
	}
	if (IsBuilding())
	{
		if (newarmy < 0 || newarmy > ARMY_NEUTRAL)
			return false;
		m_value = Simplify().GetValue() + (newarmy * ELEMENT_BUILDING_COLUMNS);
		return true;
	}
	return false;
}

int Element::ChangeArmy(int newarmy, int return_int)
{
	Element element = *this;
	element.ChangeArmy(newarmy);
	return element.GetValue();
}

Element Element::ChangeArmy(int newarmy, Element return_element)
{
	Element element = *this;
	element.ChangeArmy(newarmy);
	return element;
}

Element Element::Simplify()
{
	if (IsTerrain() || IsExtra())
	{
		switch (m_value)
		{
		case MAKE_TERRAIN( 0, 0):
			return Element(TERRAIN_PLAIN);
		case MAKE_TERRAIN(17, 5):
		case MAKE_TERRAIN(17, 6):
		case MAKE_TERRAIN(17, 7):
			return Element(TERRAIN_PLAIND);
		case MAKE_TERRAIN( 0, 3):
		case MAKE_TERRAIN(15, 6):
			return Element(TERRAIN_WOOD);
		case MAKE_TERRAIN( 0, 5):
		case MAKE_TERRAIN( 0, 7):
			return Element(TERRAIN_MOUNTAIN);
		case MAKE_TERRAIN( 1, 0):
		case MAKE_TERRAIN( 1, 1):
		case MAKE_TERRAIN( 1, 2):
		case MAKE_TERRAIN( 1, 4):
		case MAKE_TERRAIN( 1, 5):
		case MAKE_TERRAIN( 1, 6):
		case MAKE_TERRAIN( 1, 7):
		case MAKE_TERRAIN( 2, 4):
		case MAKE_TERRAIN( 2, 5):
		case MAKE_TERRAIN( 2, 6):
		case MAKE_TERRAIN( 2, 7):
		case MAKE_TERRAIN(15, 2):
		case MAKE_TERRAIN(15, 3):
			return Element(TERRAIN_ROAD);
		case MAKE_TERRAIN( 2, 0):
		case MAKE_TERRAIN( 2, 1):
			return Element(TERRAIN_BRIDGE);
		case MAKE_TERRAIN( 3, 0):
		case MAKE_TERRAIN( 3, 1):
		case MAKE_TERRAIN( 3, 2):
		case MAKE_TERRAIN( 3, 4):
		case MAKE_TERRAIN( 3, 5):
		case MAKE_TERRAIN( 3, 6):
		case MAKE_TERRAIN( 3, 7):
		case MAKE_TERRAIN( 4, 0):
		case MAKE_TERRAIN( 4, 1):
		case MAKE_TERRAIN( 4, 2):
		case MAKE_TERRAIN( 4, 3):
		case MAKE_TERRAIN( 4, 4):
		case MAKE_TERRAIN( 4, 5):
		case MAKE_TERRAIN( 4, 6):
		case MAKE_TERRAIN( 4, 7):
			return Element(TERRAIN_RIVER);
		case MAKE_TERRAIN(16, 0):
		case MAKE_TERRAIN(16, 1):
		case MAKE_TERRAIN(16, 2):
		case MAKE_TERRAIN(16, 3):
		case MAKE_TERRAIN(16, 4):
		case MAKE_TERRAIN(16, 5):
		case MAKE_TERRAIN(17, 0):
		case MAKE_TERRAIN(17, 1):
		case MAKE_TERRAIN(17, 2):
		case MAKE_TERRAIN(17, 3):
			return Element(TERRAIN_PIPE);
		case MAKE_TERRAIN(16, 6):
		case MAKE_TERRAIN(16, 7):
			return Element(TERRAIN_SEAM);
		case MAKE_TERRAIN( 9, 0):
		case MAKE_TERRAIN( 9, 1):
		case MAKE_TERRAIN( 9, 2):
		case MAKE_TERRAIN( 9, 3):
		case MAKE_TERRAIN( 9, 4):
		case MAKE_TERRAIN( 9, 5):
		case MAKE_TERRAIN( 9, 6):
		case MAKE_TERRAIN( 9, 7):
		case MAKE_TERRAIN(10, 0):
		case MAKE_TERRAIN(10, 1):
		case MAKE_TERRAIN(10, 2):
		case MAKE_TERRAIN(10, 3):
		case MAKE_TERRAIN(11, 0):
		case MAKE_TERRAIN(11, 1):
		case MAKE_TERRAIN(11, 2):
		case MAKE_TERRAIN(11, 3):
		case MAKE_TERRAIN(11, 4):
		case MAKE_TERRAIN(11, 5):
		case MAKE_TERRAIN(11, 6):
		case MAKE_TERRAIN(11, 7):
		case MAKE_TERRAIN(12, 0):
		case MAKE_TERRAIN(12, 1):
		case MAKE_TERRAIN(12, 2):
		case MAKE_TERRAIN(12, 3):
		case MAKE_TERRAIN(12, 4):
		case MAKE_TERRAIN(12, 5):
		case MAKE_TERRAIN(12, 6):
		case MAKE_TERRAIN(12, 7):
		case MAKE_TERRAIN(13, 0):
		case MAKE_TERRAIN(13, 1):
		case MAKE_TERRAIN(13, 2):
		case MAKE_TERRAIN(13, 3):
		case MAKE_TERRAIN(14, 0):
		case MAKE_TERRAIN(14, 1):
		case MAKE_TERRAIN(14, 2):
		case MAKE_TERRAIN(14, 3):
			return Element(TERRAIN_SHOAL);
		case MAKE_TERRAIN( 0, 2):
		case MAKE_TERRAIN( 7, 0):
		case MAKE_TERRAIN( 7, 1):
		case MAKE_TERRAIN( 7, 2):
		case MAKE_TERRAIN( 7, 3):
		case MAKE_TERRAIN( 7, 4):
			return Element(TERRAIN_SEA);
		case MAKE_TERRAIN(0, 1):
			return Element(TERRAIN_REEF);
		case MAKE_EXTRA( 0, 2):
		case MAKE_EXTRA( 0, 3):
		case MAKE_EXTRA( 0, 4):
		case MAKE_EXTRA( 1, 2):
		case MAKE_EXTRA( 1, 3):
		case MAKE_EXTRA( 1, 4):
		case MAKE_EXTRA( 2, 2):
		case MAKE_EXTRA( 2, 3):
		case MAKE_EXTRA( 2, 4):
			return Element(EXTRA_BCANNONS);
		case MAKE_EXTRA( 3, 2):
		case MAKE_EXTRA( 3, 3):
		case MAKE_EXTRA( 3, 4):
		case MAKE_EXTRA( 4, 2):
		case MAKE_EXTRA( 4, 3):
		case MAKE_EXTRA( 4, 4):
		case MAKE_EXTRA( 5, 2):
		case MAKE_EXTRA( 5, 3):
		case MAKE_EXTRA( 5, 4):
			return Element(EXTRA_BCANNONN);
		case MAKE_EXTRA( 0, 5):
		case MAKE_EXTRA( 0, 6):
		case MAKE_EXTRA( 0, 7):
		case MAKE_EXTRA( 1, 5):
		case MAKE_EXTRA( 1, 6):
		case MAKE_EXTRA( 1, 7):
		case MAKE_EXTRA( 2, 5):
		case MAKE_EXTRA( 2, 6):
		case MAKE_EXTRA( 2, 7):
			return Element(EXTRA_DEATHRAY);
		case MAKE_EXTRA( 3, 5):
		case MAKE_EXTRA( 3, 6):
		case MAKE_EXTRA( 3, 7):
		case MAKE_EXTRA( 4, 5):
		case MAKE_EXTRA( 4, 6):
		case MAKE_EXTRA( 4, 7):
		case MAKE_EXTRA( 5, 5):
		case MAKE_EXTRA( 5, 6):
		case MAKE_EXTRA( 5, 7):
			return Element(EXTRA_BOBELISK);
		case MAKE_EXTRA( 7, 0):
		case MAKE_EXTRA( 7, 1):
		case MAKE_EXTRA( 7, 2):
		case MAKE_EXTRA( 7, 3):
		case MAKE_EXTRA( 8, 0):
		case MAKE_EXTRA( 8, 1):
		case MAKE_EXTRA( 8, 2):
		case MAKE_EXTRA( 8, 3):
		case MAKE_EXTRA( 9, 0):
		case MAKE_EXTRA( 9, 1):
		case MAKE_EXTRA( 9, 2):
		case MAKE_EXTRA( 9, 3):
		case MAKE_EXTRA(10, 0):
		case MAKE_EXTRA(10, 1):
		case MAKE_EXTRA(10, 2):
		case MAKE_EXTRA(10, 3):
			return Element(EXTRA_VOLCANO);
		case MAKE_EXTRA( 7, 4):
		case MAKE_EXTRA( 7, 5):
		case MAKE_EXTRA( 7, 6):
		case MAKE_EXTRA( 7, 7):
		case MAKE_EXTRA( 8, 4):
		case MAKE_EXTRA( 8, 5):
		case MAKE_EXTRA( 8, 6):
		case MAKE_EXTRA( 8, 7):
		case MAKE_EXTRA( 9, 4):
		case MAKE_EXTRA( 9, 5):
		case MAKE_EXTRA( 9, 6):
		case MAKE_EXTRA( 9, 7):
		case MAKE_EXTRA(10, 4):
		case MAKE_EXTRA(10, 5):
		case MAKE_EXTRA(10, 6):
		case MAKE_EXTRA(10, 7):
			return Element(EXTRA_FORTRESS);
		case MAKE_EXTRA(11, 0):
		case MAKE_EXTRA(11, 1):
		case MAKE_EXTRA(11, 2):
		case MAKE_EXTRA(11, 3):
		case MAKE_EXTRA(12, 0):
		case MAKE_EXTRA(12, 1):
		case MAKE_EXTRA(12, 2):
		case MAKE_EXTRA(12, 3):
		case MAKE_EXTRA(13, 0):
		case MAKE_EXTRA(13, 1):
		case MAKE_EXTRA(13, 2):
		case MAKE_EXTRA(13, 3):
		case MAKE_EXTRA(14, 0):
		case MAKE_EXTRA(14, 1):
		case MAKE_EXTRA(14, 2):
		case MAKE_EXTRA(14, 3):
			return Element(EXTRA_GSILO);
		case MAKE_EXTRA(11, 4):
		case MAKE_EXTRA(11, 5):
		case MAKE_EXTRA(11, 6):
		case MAKE_EXTRA(11, 7):
		case MAKE_EXTRA(12, 4):
		case MAKE_EXTRA(12, 5):
		case MAKE_EXTRA(12, 6):
		case MAKE_EXTRA(12, 7):
		case MAKE_EXTRA(13, 4):
		case MAKE_EXTRA(13, 5):
		case MAKE_EXTRA(13, 6):
		case MAKE_EXTRA(13, 7):
		case MAKE_EXTRA(14, 4):
		case MAKE_EXTRA(14, 5):
		case MAKE_EXTRA(14, 6):
		case MAKE_EXTRA(14, 7):
			return Element(EXTRA_BLACKARC);
		case MAKE_EXTRA(15, 4):
		case MAKE_EXTRA(15, 5):
		case MAKE_EXTRA(15, 6):
		case MAKE_EXTRA(15, 7):
		case MAKE_EXTRA(16, 4):
		case MAKE_EXTRA(16, 5):
		case MAKE_EXTRA(16, 6):
		case MAKE_EXTRA(16, 7):
		case MAKE_EXTRA(17, 4):
		case MAKE_EXTRA(17, 5):
		case MAKE_EXTRA(17, 6):
		case MAKE_EXTRA(17, 7):
		case MAKE_EXTRA(18, 4):
		case MAKE_EXTRA(18, 5):
		case MAKE_EXTRA(18, 6):
		case MAKE_EXTRA(18, 7):
			return Element(EXTRA_SEAARC);
		default:
			return Element(m_value);
		}
	}

	if (IsBuilding())
	{
		if (m_value == BUILDING_SILO)
			return Element(m_value);
		else
			return Element(((m_value - ELEMENT_BUILDING_START) % ELEMENT_BUILDING_COLUMNS) + ELEMENT_BUILDING_START);
	}
		
	if (IsUnitNonEmpty())
		return Element(((m_value - ELEMENT_UNIT_START) % (ELEMENT_UNIT_COLUMNS * 2)) + ELEMENT_UNIT_START);

	return Element(m_value);
}

Element Element::GetBase()
{
	if (IsSea())
		return Element(TERRAIN_SEA);
	else
		return Element(TERRAIN_PLAIN);
}

Element Element::GetNext()
{
	if (!IsTerrain())
		return Element(GetValue());

	Element nextelem(m_value);
	Element simple = Simplify();

	while (true)
	{
		nextelem.SetValue(nextelem.GetValue() + 1);
		if (nextelem.GetValue() > ELEMENT_TERRAIN_END)
			nextelem.SetValue(ELEMENT_TERRAIN_START);
		if (nextelem.Simplify() == simple || nextelem == *this)
			break;
	}
	return nextelem;
}

bool Element::IsLand()
{
	if (!IsBackground())
		return false;

	switch (Simplify().GetValue())
	{
	case TERRAIN_BRIDGE:
	case TERRAIN_SEA:
	case TERRAIN_SHOAL:
	case TERRAIN_REEF:
	case EXTRA_SEAARC:
		return false;
	default:
		return true;
	}
}

bool Element::IsSea()
{
	if (!IsBackground())
		return false;

	switch (Simplify().GetValue())
	{
	case TERRAIN_BRIDGE:
	case TERRAIN_SEA:
	case TERRAIN_SHOAL:
	case TERRAIN_REEF:
	case EXTRA_SEAARC:
		return true;
	default:
		return false;
	}
}

bool Element::IsPipe()
{
	if (!IsTerrain())
		return false;
	Element simplified = Simplify();
	return simplified == TERRAIN_PIPE || simplified == TERRAIN_SEAM;
}

bool Element::IsRoad()
{
	if (!IsTerrain())
		return false;
	Element simplified = Simplify();
	return simplified == TERRAIN_ROAD || simplified == TERRAIN_BRIDGE;
}

bool Element::IsRiver()
{
	if (!IsTerrain())
		return false;
	Element simplified = Simplify();
	return simplified == TERRAIN_RIVER || simplified == TERRAIN_BRIDGE;
}

bool Element::IsCompatible(int maptype)
{
	Element simplified = Simplify();

	if (maptype == MAPTYPE_AW1 || maptype == MAPTYPE_AW2 || maptype == MAPTYPE_AWDS)
	{
		if (IsTerrain())
		{
			if (simplified == TERRAIN_PLAIN)								return true;
			if (simplified == TERRAIN_PLAIND && maptype == MAPTYPE_AWDS)	return true;
			if (simplified == TERRAIN_WOOD)									return true;
			if (simplified == TERRAIN_MOUNTAIN)								return true;
			if (simplified == TERRAIN_ROAD)									return true;
			if (simplified == TERRAIN_BRIDGE)								return true;
			if (simplified == TERRAIN_RIVER)								return true;
			if (simplified == TERRAIN_PIPE && maptype == MAPTYPE_AW2)		return true;
			if (simplified == TERRAIN_PIPE && maptype == MAPTYPE_AWDS)		return true;
			if (simplified == TERRAIN_SEAM && maptype == MAPTYPE_AW2)		return true;
			if (simplified == TERRAIN_SEAM && maptype == MAPTYPE_AWDS)		return true;
			if (simplified == TERRAIN_SEA)									return true;
			if (simplified == TERRAIN_SHOAL)								return true;
			if (simplified == TERRAIN_REEF)									return true;
			return false;
		}

		else if (IsBuilding())
		{
			if (GetArmy() != ARMY_ORANGE_STAR &&
				GetArmy() != ARMY_BLUE_MOON &&
				GetArmy() != ARMY_GREEN_EARTH &&
				GetArmy() != ARMY_YELLOW_COMET &&
				GetArmy() != ARMY_BLACK_HOLE &&
				GetArmy() != ARMY_NEUTRAL)									return false;
			if (GetArmy() == ARMY_BLACK_HOLE && maptype == MAPTYPE_AW1)		return false;

			if (simplified == BUILDING_HQ)									return true;
			if (simplified == BUILDING_CITY)								return true;
			if (simplified == BUILDING_BASE)								return true;
			if (simplified == BUILDING_AIRPORT)								return true;
			if (simplified == BUILDING_PORT)								return true;
			if (simplified == BUILDING_TOWER && maptype == MAPTYPE_AWDS)	return true;
			if (simplified == BUILDING_LAB && maptype == MAPTYPE_AWDS)		return true;
			if (simplified == BUILDING_SILO && maptype == MAPTYPE_AW2)		return true;
			if (simplified == BUILDING_SILO && maptype == MAPTYPE_AWDS)		return true;
			return false;
		}

		else if (IsExtra())
		{
			if (maptype == MAPTYPE_AW1)			return false;
			if (maptype == MAPTYPE_AW2)			return false;

			if (simplified == EXTRA_MCANNONN)	return true;
			if (simplified == EXTRA_MCANNONS)	return true;
			if (simplified == EXTRA_MCANNONW)	return true;
			if (simplified == EXTRA_MCANNONE)	return true;
			if (simplified == EXTRA_LCANNON)	return true;
			if (simplified == EXTRA_BCANNONS)	return true;
			if (simplified == EXTRA_BCANNONN)	return true;
			if (simplified == EXTRA_DEATHRAY)	return true;
			if (simplified == EXTRA_BCRYSTAL)	return true;
			if (simplified == EXTRA_BOBELISK)	return true;
			if (simplified == EXTRA_VOLCANO)	return true;
			if (simplified == EXTRA_FORTRESS)	return true;
			if (simplified == EXTRA_BLACKARC)	return true;
			if (simplified == EXTRA_GSILO)		return true;
			if (simplified == EXTRA_SEAARC)		return true;
			return false;
		}

		else if (IsUnit())
		{
			if (GetArmy() != ARMY_ORANGE_STAR &&
				GetArmy() != ARMY_BLUE_MOON &&
				GetArmy() != ARMY_GREEN_EARTH &&
				GetArmy() != ARMY_YELLOW_COMET &&
				GetArmy() != ARMY_BLACK_HOLE)								return false;
			if (GetArmy() == ARMY_BLACK_HOLE && maptype == MAPTYPE_AW1)		return false;

			if (simplified == UNIT_INFANTRY)								return true;
			if (simplified == UNIT_MECH)									return true;
			if (simplified == UNIT_TANK)									return true;
			if (simplified == UNIT_MDTANK)									return true;
			if (simplified == UNIT_NEOTANK && maptype == MAPTYPE_AW2)		return true;
			if (simplified == UNIT_NEOTANK && maptype == MAPTYPE_AWDS)		return true;
			if (simplified == UNIT_MEGATANK && maptype == MAPTYPE_AWDS)		return true;
			if (simplified == UNIT_RECON)									return true;
			if (simplified == UNIT_ANTIAIR)									return true;
			if (simplified == UNIT_MISSILE)									return true;
			if (simplified == UNIT_ARTILLERY)								return true;
			if (simplified == UNIT_ROCKET)									return true;
			if (simplified == UNIT_APC)										return true;
			if (simplified == UNIT_PIPERUNNER && maptype == MAPTYPE_AWDS)	return true;
			if (simplified == UNIT_OOZIUM && maptype == MAPTYPE_AWDS)		return true;
			if (simplified == UNIT_BLACKBOAT && maptype == MAPTYPE_AWDS)	return true;
			if (simplified == UNIT_LANDER)									return true;
			if (simplified == UNIT_CRUISER)									return true;
			if (simplified == UNIT_SUB)										return true;
			if (simplified == UNIT_BATTLESHIP)								return true;
			if (simplified == UNIT_CARRIER && maptype == MAPTYPE_AWDS)		return true;
			if (simplified == UNIT_TCOPTER)									return true;
			if (simplified == UNIT_BCOPTER)									return true;
			if (simplified == UNIT_FIGHTER)									return true;
			if (simplified == UNIT_BOMBER)									return true;
			if (simplified == UNIT_STEALTH && maptype == MAPTYPE_AWDS)		return true;
			if (simplified == UNIT_BLACKBOMB && maptype == MAPTYPE_AWDS)	return true;
			return false;
		}

		else
			return false;
	}

	return true;
}

int Element::ConvertFrom(int value, int maptype)
{
	if (maptype == MAPTYPE_DEFAULT)
		return value;

	if (maptype == MAPTYPE_AW1 || maptype == MAPTYPE_AW2 || maptype == MAPTYPE_AWDS)
	{
		int OLD_ELEMENT_TERRAIN_START = 0;
		int OLD_ELEMENT_TERRAIN_END = 299;
		int OLD_ELEMENT_BUILDING_START = 300;
		int OLD_ELEMENT_BUILDING_END = 499;
		int OLD_ELEMENT_UNIT_START = 500;
		int OLD_ELEMENT_UNIT_END = 899;
		int OLD_ELEMENT_EXTRA_START = 900;
		int OLD_ELEMENT_EXTRA_END = 1299;

		int OLD_ELEMENT_TERRAIN_COLUMNS = 30;
		int OLD_ELEMENT_BUILDING_COLUMNS = 10;
		int OLD_ELEMENT_UNIT_COLUMNS = 20;
		int OLD_ELEMENT_EXTRA_COLUMNS = 20;
		int OLD_ELEMENT_UNIT_EMPTY = 0xFFFF;
		int AW1_ARMY_NEUTRAL = 4;
		int AW2_ARMY_NEUTRAL = 5;
		int AWDS_ARMY_NEUTRAL = 5;

		int offvalue;

		if (value >= OLD_ELEMENT_TERRAIN_START && value <= OLD_ELEMENT_TERRAIN_END)
		{
			offvalue = value - OLD_ELEMENT_TERRAIN_START;
			return MAKE_TERRAIN(offvalue % OLD_ELEMENT_TERRAIN_COLUMNS, offvalue / OLD_ELEMENT_TERRAIN_COLUMNS);
		}

		if (value >= OLD_ELEMENT_BUILDING_START && value <= OLD_ELEMENT_BUILDING_END)
		{
			offvalue = value - OLD_ELEMENT_BUILDING_START;
			int y = offvalue / OLD_ELEMENT_BUILDING_COLUMNS;
			if (y == AW1_ARMY_NEUTRAL && maptype == MAPTYPE_AW1)
				y = ARMY_NEUTRAL;
			else if (y == AW2_ARMY_NEUTRAL && maptype == MAPTYPE_AW2)
				y = ARMY_NEUTRAL;
			else if (y == AWDS_ARMY_NEUTRAL && maptype == MAPTYPE_AWDS)
				y = ARMY_NEUTRAL;
			return MAKE_BUILDING(offvalue % OLD_ELEMENT_BUILDING_COLUMNS, y);
		}

		if (value >= OLD_ELEMENT_EXTRA_START && value <= OLD_ELEMENT_EXTRA_END)
		{
			offvalue = value - OLD_ELEMENT_EXTRA_START;
			return MAKE_EXTRA(offvalue % OLD_ELEMENT_EXTRA_COLUMNS, offvalue / OLD_ELEMENT_EXTRA_COLUMNS);
		}

		if (value >= OLD_ELEMENT_UNIT_START && value <= OLD_ELEMENT_UNIT_END)
		{

			offvalue = value - OLD_ELEMENT_UNIT_START;
			return MAKE_UNIT(offvalue % OLD_ELEMENT_UNIT_COLUMNS, offvalue / OLD_ELEMENT_UNIT_COLUMNS);
		}

		if (value == OLD_ELEMENT_UNIT_EMPTY)
			return ELEMENT_UNIT_EMPTY;

		return 0;
	}

	return value;
}

int Element::ConvertTo(int maptype)
{
	if (maptype == MAPTYPE_DEFAULT)
		return GetValue();

	if (maptype == MAPTYPE_AW1 || maptype == MAPTYPE_AW2 || maptype == MAPTYPE_AWDS)
	{
		Element simplified = Simplify();

		int OLD_ELEMENT_TERRAIN_START = 0;
		int OLD_ELEMENT_BUILDING_START = 300;
		int OLD_ELEMENT_UNIT_START = 500;
		int OLD_ELEMENT_EXTRA_START = 900;
		int OLD_ELEMENT_TERRAIN_COLUMNS = 30;
		int OLD_ELEMENT_BUILDING_COLUMNS = 10;
		int OLD_ELEMENT_UNIT_COLUMNS = 20;
		int OLD_ELEMENT_EXTRA_COLUMNS = 20;
		int OLD_ELEMENT_UNIT_EMPTY = 0xFFFF;
		int AW1_ARMY_NEUTRAL = 4;
		int AW2_ARMY_NEUTRAL = 5;
		int AWDS_ARMY_NEUTRAL = 5;

		if (IsTerrain())
		{
			if (simplified.IsCompatible(maptype))
				return OLD_ELEMENT_TERRAIN_START + simplified.GetX() +
				(simplified.GetY() * OLD_ELEMENT_TERRAIN_COLUMNS);

			if (simplified.IsSea())
				return OLD_ELEMENT_TERRAIN_START + Element(TERRAIN_SEA).GetX() +
				(Element(TERRAIN_SEA).GetY() * OLD_ELEMENT_TERRAIN_COLUMNS);

			if (simplified.IsPipe() && maptype != MAPTYPE_AW1)
				return OLD_ELEMENT_TERRAIN_START + Element(TERRAIN_PIPE).GetX() +
				(Element(TERRAIN_PIPE).GetY() * OLD_ELEMENT_TERRAIN_COLUMNS);

			if (simplified.IsRiver())
				return OLD_ELEMENT_TERRAIN_START + Element(TERRAIN_RIVER).GetX() +
				(Element(TERRAIN_RIVER).GetY() * OLD_ELEMENT_TERRAIN_COLUMNS);

			if (simplified.IsRoad())
				return OLD_ELEMENT_TERRAIN_START + Element(TERRAIN_ROAD).GetX() +
				(Element(TERRAIN_ROAD).GetY() * OLD_ELEMENT_TERRAIN_COLUMNS);

			return OLD_ELEMENT_TERRAIN_START + Element(TERRAIN_PLAIN).GetX() +
			(Element(TERRAIN_PLAIN).GetY() * OLD_ELEMENT_TERRAIN_COLUMNS);

		}

		if (IsBuilding())
		{
			int y;
			if (IsCompatible(maptype))	// Full compatibility.
			{
				if (GetArmy() == ARMY_NEUTRAL && maptype == MAPTYPE_AW1)
					y = AW1_ARMY_NEUTRAL;
				else if (GetArmy() == ARMY_NEUTRAL && maptype == MAPTYPE_AW2)
					y = AW2_ARMY_NEUTRAL;
				else if (GetArmy() == ARMY_NEUTRAL && maptype == MAPTYPE_AWDS)
					y = AWDS_ARMY_NEUTRAL;
				else
					y = GetY();
				return OLD_ELEMENT_BUILDING_START + GetX() + (y * OLD_ELEMENT_BUILDING_COLUMNS);
			}

			if (simplified.IsCompatible(maptype))	// Army not compatible, building ok.
			{
				if (simplified == BUILDING_HQ)
					return OLD_ELEMENT_TERRAIN_START + Element(TERRAIN_PLAIN).GetX() +
					(Element(TERRAIN_PLAIN).GetY() * OLD_ELEMENT_TERRAIN_COLUMNS);
				else
				{
					if (simplified.GetArmy() == ARMY_NEUTRAL && maptype == MAPTYPE_AW1)
						y = AW1_ARMY_NEUTRAL;
					else if (simplified.GetArmy() == ARMY_NEUTRAL && maptype == MAPTYPE_AW2)
						y = AW2_ARMY_NEUTRAL;
					else if (simplified.GetArmy() == ARMY_NEUTRAL && maptype == MAPTYPE_AWDS)
						y = AWDS_ARMY_NEUTRAL;
					else
						y = simplified.GetY();
					return OLD_ELEMENT_BUILDING_START + simplified.GetX() +	(y * OLD_ELEMENT_BUILDING_COLUMNS);
				}
			}

			int army = GetArmy();
			if (army != ARMY_ORANGE_STAR &&
				army != ARMY_BLUE_MOON &&
				army != ARMY_GREEN_EARTH &&
				army != ARMY_YELLOW_COMET &&
				army != ARMY_BLACK_HOLE &&
				army != ARMY_NEUTRAL)								army = ARMY_NEUTRAL;
			if (army == ARMY_BLACK_HOLE && maptype == MAPTYPE_AW1)	army = ARMY_NEUTRAL;

			Element city(BUILDING_CITY);
			city.ChangeArmy(army);
			if (army == ARMY_NEUTRAL && maptype == MAPTYPE_AW1)
				y = AW1_ARMY_NEUTRAL;
			else if (army == ARMY_NEUTRAL && maptype == MAPTYPE_AW2)
				y = AW2_ARMY_NEUTRAL;
			else if (army == ARMY_NEUTRAL && maptype == MAPTYPE_AWDS)
				y = AWDS_ARMY_NEUTRAL;
			else
				y = city.GetY();
			return OLD_ELEMENT_BUILDING_START + city.GetX() + (y * OLD_ELEMENT_BUILDING_COLUMNS);
		}

		if (IsExtra())
		{
			if (IsCompatible(maptype))
				return OLD_ELEMENT_EXTRA_START + GetX() + (GetY() * OLD_ELEMENT_EXTRA_COLUMNS);
			else if (maptype == MAPTYPE_AW1)
				return OLD_ELEMENT_TERRAIN_START + Element(TERRAIN_PLAIN).GetX() +
				(Element(TERRAIN_PLAIN).GetY() * OLD_ELEMENT_TERRAIN_COLUMNS);
			else
				return OLD_ELEMENT_TERRAIN_START + Element(TERRAIN_PIPE).GetX() +
				(Element(TERRAIN_PIPE).GetY() * OLD_ELEMENT_TERRAIN_COLUMNS);
		}

		if (IsUnit())
		{
			if (*this == ELEMENT_UNIT_EMPTY)
				return OLD_ELEMENT_UNIT_EMPTY;

			if (IsCompatible(maptype))
				return OLD_ELEMENT_UNIT_START + GetX() + (GetY() * OLD_ELEMENT_UNIT_COLUMNS);
			else
				return OLD_ELEMENT_UNIT_EMPTY;
		}

		return GetValue();
	}

	return GetValue();
}

int Element::HeaderToMaptype(wxString header)
{
	if (header == "AWMap 001")
		return MAPTYPE_AW1;
	if (header == "AW2Map001")
		return MAPTYPE_AW2;
	if (header == "AWDMap001")
		return MAPTYPE_AWDS;
	if (header == "AWSMap001")
		return MAPTYPE_AWS001;
	return MAPTYPE_UNKNOWN;
}