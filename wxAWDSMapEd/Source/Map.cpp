#include "precomp.h"
#include "Map.h"

#pragma warning (disable:4172)

Map::Map(int width, int height)
{

	SetName("[untitled]");
	SetAuthor(g_infoDefaultAuthor);
	SetDescription("");

	if (width == -1 || width < MAP_MIN_WIDTH || width > MAP_MAX_WIDTH)
		width = g_infoDefaultWidth;
	if (height == -1 || height < MAP_MIN_HEIGHT || height > MAP_MAX_HEIGHT)
		height = g_infoDefaultHeight;
	m_width = width;
	m_height = height;
	m_tileset = g_infoDefaultTileset;

	int i, j;
	m_bg.resize(m_width);
	m_bgdraw.resize(m_width);
	m_fg.resize(m_width);
	for (i = 0; i < m_width; i++)
	{
		m_bg[i].resize(m_height);
		m_bgdraw[i].resize(m_height);
		m_fg[i].resize(m_height);
		for (j = 0; j < m_height; j++)
		{
			m_bg[i][j] = Background(g_infoDefaultTerrain);
			m_fg[i][j] = Foreground(ELEMENT_UNIT_EMPTY);
		}
	}
	SetSize(width, height);
	//UpdateDraw(); //SetSize already does this.

	SetDirty(false);
	
}

bool Map::SetDirty(bool dirty)
{
	m_dirty = dirty;
	return true;
}

bool Map::IsDirty()
{
	return m_dirty;
}

BackgroundArray* Map::GetBackground()
{
	return &m_bg;
}

Background Map::GetBackground(int x, int y)
{
	if (x >= 0 && x < GetWidth() && y >= 0 && y < GetHeight())
		return m_bg[x][y];
	else
		return Background(TERRAIN_SEA);
}

BackgroundArray* Map::GetBackgroundDraw()
{
	return &m_bgdraw;
}

Background Map::GetBackgroundDraw(int x, int y)
{
	if (x >= 0 && x < GetWidth() && y >= 0 && y < GetHeight())
		return m_bgdraw[x][y];
	else
		return Background(TERRAIN_SEA);
}

ForegroundArray* Map::GetForeground()
{
	return &m_fg;
}

Foreground Map::GetForeground(int x, int y)
{
	if (x >= 0 && x < GetWidth() && y >= 0 && y < GetHeight())
		return m_fg[x][y];
	else
		return Foreground(ELEMENT_UNIT_EMPTY);
}

bool Map::SetBackground(BackgroundArray* background)
{
	if (background->size() == GetWidth() && (*background)[0].size() == GetHeight())
	{
		m_bg = *background;
		UpdateDraw();
		SetDirty();
		return true;
	}
	return false;
}

bool Map::SetBackground(int x, int y, Background background, bool check)
{
	if (x >= 0 && x < GetWidth() && y >= 0 && y < GetHeight())
		if (AllowPlacement(x, y, background) || !check)
		{
			m_bg[x][y] = background;
			UpdateDraw(x - 2, y - 2, 5, 5);
			SetDirty();
			return true;
		}
	return false;
}


bool Map::SetBackgroundDraw(BackgroundArray* background)
{
	if (background->size() == GetWidth() && (*background)[0].size() == GetHeight())
	{
		m_bgdraw = *background;
		return true;
	}
	return false;
}

bool Map::SetBackgroundDraw(int x, int y, Background background)
{
	if (x >= 0 && x < GetWidth() && y >= 0 && y < GetHeight())
	{
		m_bgdraw[x][y] = background;
		return true;
	}
	return false;
}


bool Map::SetForeground(ForegroundArray* foreground)
{
	if (foreground->size() == GetWidth() && (*foreground)[1].size() == GetHeight())
	{
		m_fg = *foreground;
		SetDirty();
		return true;
	}
	return false;
}

bool Map::SetForeground(int x, int y, Foreground foreground)
{
	if (x >= 0 && x < GetWidth() && y >= 0 && y < GetHeight())
		if (AllowPlacement(x, y, foreground))
		{
			m_fg[x][y] = foreground;
			SetDirty();
			return true;
		}
	return false;
}

bool Map::AllowPlacement(int x, int y, Element element, bool recheck)
{
	if (element.IsForeground())
		if ((!recheck && element == GetForeground(x, y)) || element == ELEMENT_UNIT_EMPTY)
			return true;
	if (element.IsBackground())
		if (!recheck && element == GetBackground(x, y))
			return true;

	if (element.IsTerrain())
	{
		switch (element.Simplify().GetValue())
		{
		case TERRAIN_PLAIN:
		case TERRAIN_PLAIND:
		case TERRAIN_WOOD:
		case TERRAIN_MOUNTAIN:
		case TERRAIN_ROAD:
		case TERRAIN_PIPE:
		case TERRAIN_SEA:
			return true;

		case ELEMENT_TERRAIN_BLANK:	// This ensures you can't Set the terrain into the map,
			return false;			// except when check = false is used.

		case TERRAIN_RIVER:
			if (GetBackground(x - 1, y).IsRiver() && GetBackground(x - 1, y - 1).IsRiver() && GetBackground(x, y - 1).IsRiver())
				return false;
			if (GetBackground(x, y - 1).IsRiver() && GetBackground(x + 1, y - 1).IsRiver() && GetBackground(x + 1, y).IsRiver())
				return false;
			if (GetBackground(x + 1, y).IsRiver() && GetBackground(x + 1, y + 1).IsRiver() && GetBackground(x, y + 1).IsRiver())
				return false;
			if (GetBackground(x, y + 1).IsRiver() && GetBackground(x - 1, y + 1).IsRiver() && GetBackground(x - 1, y).IsRiver())
				return false;
			return true;

		case TERRAIN_BRIDGE:
			if (GetBackground(x, y).Simplify() == TERRAIN_RIVER)
				return true;
			if (GetBackground(x, y).IsSea())
			{
				if (GetBackground(x - 1, y).IsLand() && GetBackground(x, y - 1).IsLand())
					return false;
				if (GetBackground(x, y - 1).IsLand() && GetBackground(x + 1, y).IsLand())
					return false;
				if (GetBackground(x + 1, y).IsLand() && GetBackground(x, y + 1).IsLand())
					return false;
				if (GetBackground(x, y + 1).IsLand() && GetBackground(x - 1, y).IsLand())
					return false;
				if (GetBackground(x - 1, y).IsLand() || GetBackground(x - 1, y) == TERRAIN_BRIDGEH)
					return true;
				if (GetBackground(x, y - 1).IsLand() || GetBackground(x, y - 1) == TERRAIN_BRIDGEV)
					return true;
				if (GetBackground(x + 1, y).IsLand() || GetBackground(x + 1, y) == TERRAIN_BRIDGEH)
					return true;
				if (GetBackground(x, y + 1).IsLand() || GetBackground(x, y + 1) == TERRAIN_BRIDGEV)
					return true;
			}
			return false;

		case TERRAIN_REEF:
			return GetBackground(x, y).IsSea();

		case TERRAIN_SHOAL:
			// If all adjacent tiles are sea-type, stop.
			if (GetBackground(x - 1, y).IsSea() && GetBackground(x + 1, y).IsSea() && GetBackground(x, y - 1).IsSea() && GetBackground(x, y + 1).IsSea())
				return false;
			// If all adjacent tiles are land-type, stop.
			if (GetBackground(x - 1, y).IsLand() && GetBackground(x + 1, y).IsLand() && GetBackground(x, y - 1).IsLand() && GetBackground(x, y + 1).IsLand())
				return false;
			// If opposite adjacent tiles are land-type and the other two are sea-type, stop.
			if (GetBackground(x - 1, y).IsLand() && GetBackground(x + 1, y).IsLand() && GetBackground(x, y - 1).IsSea() && GetBackground(x, y + 1).IsSea())
				return false;
			if (GetBackground(x - 1, y).IsSea() && GetBackground(x + 1, y).IsSea() && GetBackground(x, y - 1).IsLand() && GetBackground(x, y + 1).IsLand())
				return false;
			// Final acceptance conditions.
			if (GetBackground(x - 1, y - 1).IsLand() && GetBackground(x - 1, y).IsSea() && GetBackground(x, y - 1).IsSea())
				return false;
			if (GetBackground(x + 1, y - 1).IsLand() && GetBackground(x + 1, y).IsSea() && GetBackground(x, y - 1).IsSea())
				return false;
			if (GetBackground(x + 1, y + 1).IsLand() && GetBackground(x + 1, y).IsSea() && GetBackground(x, y + 1).IsSea())
				return false;
			if (GetBackground(x - 1, y + 1).IsLand() && GetBackground(x - 1, y).IsSea() && GetBackground(x, y + 1).IsSea())
				return false;
			return true;


			// If two adjacent-to-one-of-the-corners tiles are land-type, accept.
			if (GetBackground(x - 1, y).IsLand() && GetBackground(x, y - 1).IsLand())
				return true;
			if (GetBackground(x, y - 1).IsLand() && GetBackground(x + 1, y).IsLand())
				return true;
			if (GetBackground(x + 1, y).IsLand() && GetBackground(x, y + 1).IsLand())
				return true;
			if (GetBackground(x, y + 1).IsLand() && GetBackground(x - 1, y).IsLand())
				return true;
			// If opposite adjacent tiles are land-type, stop.
			if ((GetBackground(x - 1, y).IsLand() && GetBackground(x + 1, y).IsLand()) || (GetBackground(x, y - 1).IsLand() && GetBackground(x, y + 1).IsLand()))
				return false;
			return true;

		case TERRAIN_SEAM:
			// If underlying terrain isn't pipe-type, stop.
			if (!GetBackground(x, y).IsPipe() && GetBackground(x, y).Simplify() != TERRAIN_PLAIND)
				return false;
			// It's okay if this is a single pipe tile not surrounded by other pipes.
			if (!GetBackground(x - 1, y).IsPipe() && !GetBackground(x + 1, y).IsPipe() && !GetBackground(x, y - 1).IsPipe()  && !GetBackground(x, y + 1).IsPipe())
				return true;
			// Continue only if both tiles adjacent either horizontally or vertically are pipe-type.
			if ((!GetBackground(x - 1, y).IsPipe() || !GetBackground(x + 1, y).IsPipe())
				&& (!GetBackground(x, y - 1).IsPipe() || !GetBackground(x, y + 1).IsPipe()))
				return false;
			// Taking the horizontal path.
			if (GetBackground(x - 1, y).Simplify() == TERRAIN_PIPE && GetBackground(x + 1, y).Simplify() == TERRAIN_PIPE)
				return true;
			// Taking the vertical path.
			if (GetBackground(x, y - 1).Simplify() == TERRAIN_PIPE && GetBackground(x, y + 1).Simplify() == TERRAIN_PIPE)
				return true;
			return false;

		default:
			return false;
		}
	}

	if (element.IsBuilding())
		return true;

	if (element.IsUnit())
	{
		if (GetBackground(x, y).IsExtra())
			return false;

		if (GetBackground(x, y) == ELEMENT_TERRAIN_BLANK)	// This terrain is used for Paste Unit Only, so all units should
			return true;									// be allowed on the blank terrain (which is used only in Selections).

		Element underlyingbg = GetBackground(x, y).Simplify();

		switch (element.Simplify().GetValue())
		{
		case UNIT_INFANTRY:
		case UNIT_MECH:
		case UNIT_OOZIUM:
			if (underlyingbg.IsBuilding())
				return true;
			if (underlyingbg == TERRAIN_PLAIN || underlyingbg == TERRAIN_PLAIND || underlyingbg == TERRAIN_WOOD ||
				underlyingbg == TERRAIN_MOUNTAIN || underlyingbg == TERRAIN_ROAD || underlyingbg == TERRAIN_BRIDGE ||
				underlyingbg == TERRAIN_RIVER || underlyingbg == TERRAIN_SHOAL)
				return true;
			return false;

		case UNIT_TANK:
		case UNIT_MDTANK:
		case UNIT_NEOTANK:
		case UNIT_MEGATANK:
		case UNIT_RECON:
		case UNIT_ANTIAIR:
		case UNIT_MISSILE:
		case UNIT_ARTILLERY:
		case UNIT_ROCKET:
		case UNIT_APC:
			if (underlyingbg.IsBuilding())
				return true;
			if (underlyingbg == TERRAIN_PLAIN || underlyingbg == TERRAIN_PLAIND || underlyingbg == TERRAIN_WOOD ||
				underlyingbg == TERRAIN_ROAD || underlyingbg == TERRAIN_BRIDGE || underlyingbg == TERRAIN_SHOAL)
				return true;
			return false;

		case UNIT_PIPERUNNER:
			if (underlyingbg == TERRAIN_PIPE || underlyingbg == TERRAIN_SEAM || underlyingbg == BUILDING_BASE)
				return true;
			return false;

		case UNIT_BLACKBOAT:
		case UNIT_LANDER:
			if (underlyingbg == TERRAIN_SHOAL || underlyingbg == TERRAIN_SEA ||
				underlyingbg == TERRAIN_REEF || underlyingbg == BUILDING_PORT)
				return true;
			return false;

		case UNIT_CRUISER:
		case UNIT_SUB:
		case UNIT_BATTLESHIP:
		case UNIT_CARRIER:
			if (underlyingbg == TERRAIN_SEA || underlyingbg == TERRAIN_REEF || 
				underlyingbg == BUILDING_PORT)
				return true;
			return false;

		case UNIT_TCOPTER:
		case UNIT_BCOPTER:
		case UNIT_FIGHTER:
		case UNIT_BOMBER:
		case UNIT_STEALTH:
		case UNIT_BLACKBOMB:
			if (underlyingbg == TERRAIN_PIPE || underlyingbg == TERRAIN_SEAM)
				return false;	// Warning! Opposite as the other units.
			return true;

		default:
			return false;
		}
	}

	if (element.IsExtra())
	{
		switch (element.Simplify().GetValue())
		{
		case EXTRA_MCANNONN:
		case EXTRA_MCANNONS:
		case EXTRA_MCANNONW:
		case EXTRA_MCANNONE:
		case EXTRA_LCANNON:
		case EXTRA_BCRYSTAL:
			return true;

		case EXTRA_BCANNONN:
		case EXTRA_BCANNONS:
		case EXTRA_DEATHRAY:
		case EXTRA_BOBELISK:
			// The first part is to allow it if it's not the "selectable" terrain.
			// It means this is the DrawPanel->SetElement adding the tiles around the clicked tile.
			return (element.Simplify() != element) || (x >= 1 && y >= 1 && x <= GetWidth() - 2  && y <= GetHeight() - 2);

		case EXTRA_SEAARC:
			// Do all of this in a scope so it doesn't affect other things!
			{
				int xoffset = 1;
				int yoffset = 1;
				// If it's not the "selectable" terrain, the check must be done from the appropriate place.
				if (element.Simplify() != element)
					element.GetLargeOffset(xoffset, yoffset);
				int i, j;
				for (i = (-1) - xoffset; i < 5 - xoffset; i++)
					for (j = (-1) - yoffset; j < 5 - yoffset; j++)
						if (GetBackground(x + i, y + j).IsLand())
							return false;
			}
			// Continue on to the next test.
		case EXTRA_VOLCANO:
		case EXTRA_FORTRESS:
		case EXTRA_BLACKARC:
		case EXTRA_GSILO:
			// The first part is to allow it if it's not the "selectable" terrain.
			// It means this is the DrawPanel->SetElement adding the tiles around the clicked tile.
			return (element.Simplify() != element) || (x >= 1 && y >= 1 && x <= GetWidth() - 3  && y <= GetHeight() - 3);

		default:
			return false;
		}
	}

	return false;
}

wxString Map::GetName()
{
	return m_name;
}

wxString Map::GetAuthor()
{
	return m_author;
}

wxString Map::GetDescription()
{
	return m_description;
}

bool Map::SetName(wxString name)
{
	m_name = name;
	SetDirty();
	return true;
}

bool Map::SetAuthor(wxString author)
{
	m_author = author;
	SetDirty();
	return true;
}

bool Map::SetDescription(wxString description)
{
	m_description = description;
	SetDirty();
	return true;
}

int Map::GetTileset()
{
	return m_tileset;
}

int Map::GetWidth()
{
	return m_width;
}

int Map::GetHeight()
{
	return m_height;
}

bool Map::SetTileset(int tileset)
{
	m_tileset = tileset;
	SetDirty();
	return true;
}

bool Map::SetWidth(int width)
{
	if (width >= MAP_MIN_WIDTH && width <= MAP_MAX_WIDTH)
	{
		int oldwidth = m_width;
		m_width = width;
		m_bg.resize(width);
		m_bgdraw.resize(width);
		m_fg.resize(width);
		if (oldwidth < width)
		{
			int i, j;
			for (i = oldwidth; i < width; i++)
			{
				m_bg[i].resize(m_height);
				m_bgdraw[i].resize(m_height);
				m_fg[i].resize(m_height);
				for (j = 0; j < m_height; j++)
				{ 
					m_bg[i][j] = Element(g_infoDefaultTerrain);
					m_fg[i][j] = Element(ELEMENT_UNIT_EMPTY);
				}
			}
		}
		UpdateDraw();
		SetDirty();
		return true;
	}
	else
		return false;
}

bool Map::SetHeight(int height)
{
	if (height >= MAP_MIN_HEIGHT && height <= MAP_MAX_HEIGHT)
	{
		int oldheight = m_height;
		m_height = height;
		int i, j;
		for (i = 0; i < m_width; i++)
		{
			m_bg[i].resize(height);
			m_bgdraw[i].resize(height);
			m_fg[i].resize(height);
			if (oldheight < height)
				for (j = oldheight; j < height; j++)
				{
					m_bg[i][j] = Element(g_infoDefaultTerrain);
					m_fg[i][j] = Element(ELEMENT_UNIT_EMPTY);
				}
		}
		UpdateDraw();
		SetDirty();
		return true;
	}
	else
		return false;
}

bool Map::SetSize(int width, int height)
{
	bool w = SetWidth(width);
	bool h = SetHeight(height);
	return w && h;
}

bool Map::Fill(Element element)
{
	int i, j;
	for (i = 0; i < GetWidth(); i++)
		for (j = 0; j < GetHeight(); j++)
			SetBackground(i, j, element);
	SetDirty();
	return true;
}

int Map::IsCompatibleSize(int maptype)
{
	if (maptype == MAPTYPE_AW1 || maptype == MAPTYPE_AW2 || maptype == MAPTYPE_AWDS)
	{
		if (GetWidth() < 30 || GetHeight() < 20)
			return COMPAT_IMPOSSIBLE;
		else if (GetWidth() == 30 && GetHeight() == 20)
			return COMPAT_OK;
		else
			return COMPAT_TRUNCATE;
	}
	else
		return true;

}

int Map::IsCompatibleElements(int maptype)
{
	int i, j;
	for (i = 0; i < GetWidth(); i++)
		for (j = 0; j < GetHeight(); j++)
			if (!GetBackground(i, j).IsCompatible(maptype) || !GetForeground(i, j).IsCompatible(maptype))
				return COMPAT_TRUNCATE;
	return COMPAT_OK;
}

bool Map::UpdateDraw()
{
	return UpdateDraw(0, 0, GetWidth(), GetHeight());
}

bool Map::UpdateDraw(int x, int y, int width, int height)
{
	int i, j;
	for (i = x; i < x + width; i++)
		for (j = y; j < y + height; j++)
 			UpdateDrawElement(i, j);
	return true;
}

bool Map::UpdateDrawElement(int x, int y)
{
	Element bg = GetBackground(x, y);
	Element bgdraw = bg;
	if (bg.IsTerrain())
	{
		Element up = GetBackground(x, y - 1);
		Element down = GetBackground(x, y + 1);
		Element left = GetBackground(x - 1, y);
		Element right = GetBackground(x + 1, y);
		switch (bg.GetValue())	// Important: there is no Simplify(). This means that if a non-default value is
		{						// set as the Background, the terrain's graphics won't be adjusted.
								// 
		case TERRAIN_MOUNTAIN:
			//if (up.Simplify() == TERRAIN_PLAIN || up.Simplify() == TERRAIN_MOUNTAIN)
				bgdraw = Element(MAKE_TERRAIN(0, 7));	// Tall mountain. In AWDS, it's always tall.
			break;

		case TERRAIN_ROAD:
			if (up.IsRoad() && down.IsRoad() && left.IsRoad() && right.IsRoad())
				bgdraw = Element(MAKE_TERRAIN(1, 2));	// Four-way +
			else if (up.IsRoad() && down.IsRoad() && right.IsRoad())
				bgdraw = Element(MAKE_TERRAIN(1, 5));	// Three-way |-
			else if (up.IsRoad() && down.IsRoad() && left.IsRoad())
				bgdraw = Element(MAKE_TERRAIN(2, 5));	// Three-way -|
			else if (down.IsRoad() && left.IsRoad() && right.IsRoad())
				bgdraw = Element(MAKE_TERRAIN(1, 6));	// Three-way -,-
			else if (up.IsRoad() && left.IsRoad() && right.IsRoad())
				bgdraw = Element(MAKE_TERRAIN(2, 6));	// Three-way -'-
			else if (down.IsRoad() && right.IsRoad())
				bgdraw = Element(MAKE_TERRAIN(1, 4));	// Two-way ,-
			else if (down.IsRoad() && left.IsRoad())
				bgdraw = Element(MAKE_TERRAIN(2, 4));	// Two-way -,
			else if (up.IsRoad() && right.IsRoad())
				bgdraw = Element(MAKE_TERRAIN(1, 7));	// Two-way '-
			else if (up.IsRoad() && left.IsRoad())
				bgdraw = Element(MAKE_TERRAIN(2, 7));	// Two-way -'
			else if (up.IsRoad() || down.IsRoad())
				bgdraw = Element(MAKE_TERRAIN(1, 1));	// Vertical
			else
				bgdraw = Element(MAKE_TERRAIN(1, 0));	// Horizontal.
			break;

		case TERRAIN_RIVER:
			if (up.IsRiver() && down.IsRiver() && left.IsRiver() && right.IsRiver())
				bgdraw = Element(MAKE_TERRAIN(3, 2));	// Four-way +
			else if (up.IsRiver() && down.IsRiver() && right.IsRiver())
				bgdraw = Element(MAKE_TERRAIN(3, 5));	// Three-way |-
			else if (up.IsRiver() && down.IsRiver() && left.IsRiver())
				bgdraw = Element(MAKE_TERRAIN(4, 5));	// Three-way -|
			else if (down.IsRiver() && left.IsRiver() && right.IsRiver())
				bgdraw = Element(MAKE_TERRAIN(3, 6));	// Three-way -,-
			else if (up.IsRiver() && left.IsRiver() && right.IsRiver())
				bgdraw = Element(MAKE_TERRAIN(4, 6));	// Three-way -'-
			else if (down.IsRiver() && right.IsRiver())
				bgdraw = Element(MAKE_TERRAIN(3, 4));	// Two-way ,-
			else if (down.IsRiver() && left.IsRiver())
				bgdraw = Element(MAKE_TERRAIN(4, 4));	// Two-way -,
			else if (up.IsRiver() && right.IsRiver())
				bgdraw = Element(MAKE_TERRAIN(3, 7));	// Two-way '-
			else if (up.IsRiver() && left.IsRiver())
				bgdraw = Element(MAKE_TERRAIN(4, 7));	// Two-way -'
			else if (up.IsRiver() || down.IsRiver())
				bgdraw = Element(MAKE_TERRAIN(3, 1));	// Vertical
			else
				bgdraw = Element(MAKE_TERRAIN(3, 0));	// Horizontal.
			break;

		case TERRAIN_BRIDGE:
			bgdraw = bg;	// This is set when the terrain is placed.
			break;			// I put it here just to make it clear and show I didn't just forget it.

		case TERRAIN_PIPE:
			if (IsPipeForDrawing(x - 1, y) && IsPipeForDrawing(x + 1, y))
				bgdraw = Element(MAKE_TERRAIN(16, 0));	// Horizontal.
			else if (IsPipeForDrawing(x, y - 1) && IsPipeForDrawing(x, y + 1))
				bgdraw = Element(MAKE_TERRAIN(16, 1));	// Vertical.
			else if (IsPipeForDrawing(x, y - 1) && IsPipeForDrawing(x + 1, y))
				bgdraw = Element(MAKE_TERRAIN(17, 2));	// '-
			else if (IsPipeForDrawing(x, y - 1) && IsPipeForDrawing(x - 1, y))
				bgdraw = Element(MAKE_TERRAIN(17, 3));	// -'
			else if (IsPipeForDrawing(x, y + 1) && IsPipeForDrawing(x + 1, y))
				bgdraw = Element(MAKE_TERRAIN(17, 0));	// ,-
			else if (IsPipeForDrawing(x, y + 1) && IsPipeForDrawing(x - 1, y))
				bgdraw = Element(MAKE_TERRAIN(17, 1));	// -,
			else if (IsPipeForDrawing(x - 1, y))
				bgdraw = Element(MAKE_TERRAIN(16, 3));	// -x
			else if (IsPipeForDrawing(x + 1, y))
				bgdraw = Element(MAKE_TERRAIN(16, 2));	// x-
			else if (IsPipeForDrawing(x, y - 1))
				bgdraw = Element(MAKE_TERRAIN(16, 5));	// '
			else if (IsPipeForDrawing(x, y + 1))
				bgdraw = Element(MAKE_TERRAIN(16, 4));	// ,
			else
				bgdraw = Element(MAKE_TERRAIN(16, 0));	// Horizontal again (default).
			break;

		case TERRAIN_SEAM:
			if (up.Simplify() == TERRAIN_PIPE && down.Simplify() == TERRAIN_PIPE)
				bgdraw = Element(MAKE_TERRAIN(16, 6));
			else
				bgdraw = Element(MAKE_TERRAIN(16, 7));
			break;

		case TERRAIN_PLAIND:
			bgdraw = Element(MAKE_TERRAIN(17, 5));
			if (IsPipeForDrawing(x, y))
			{
				if (up.Simplify() == TERRAIN_PIPE && down.Simplify() == TERRAIN_PIPE)
					bgdraw = Element(MAKE_TERRAIN(17, 6));
				else if (left.Simplify() == TERRAIN_PIPE && right.Simplify() == TERRAIN_PIPE)
					bgdraw = Element(MAKE_TERRAIN(17, 7));
			}
			break;

		case TERRAIN_SEA:
			if (up.IsLand() && down.IsLand() && left.IsLand() && right.IsLand())
				bgdraw = Element(MAKE_TERRAIN(7, 0));	// Surrounded by land in all directions.
			else if (down.IsLand() && left.IsLand() && right.IsLand())
				bgdraw = Element(MAKE_TERRAIN(7, 4));	// Surrounded by land except to the north.
			else if (up.IsLand() && left.IsLand() && right.IsLand())
				bgdraw = Element(MAKE_TERRAIN(7, 3));	// Surrounded by land except to the south.
			else if (up.IsLand() && down.IsLand() && right.IsLand())
				bgdraw = Element(MAKE_TERRAIN(7, 2));	// Surrounded by land except to the west.
			else if (up.IsLand() && down.IsLand() && left.IsLand())
				bgdraw = Element(MAKE_TERRAIN(7, 1));	// Surrounded by land except to the east.
			else if (up.IsSea() && down.IsSea() && left.IsSea() && right.IsRiver()
				&& GetBackground(x - 1, y - 1).IsSea() && GetBackground(x - 1, y + 1).IsSea())
			{
				UpdateDrawElement(x + 1, y);
				if (GetBackgroundDraw(x + 1, y) == MAKE_TERRAIN(3, 0))
					bgdraw = Element(MAKE_TERRAIN(4, 0));	// River mouth: flowing left.
			}
			else if (up.IsSea() && down.IsSea() && left.IsRiver() && right.IsSea()
				&& GetBackground(x + 1, y - 1).IsSea() && GetBackground(x + 1, y + 1).IsSea())
			{
				UpdateDrawElement(x - 1, y);
				if (GetBackgroundDraw(x - 1, y) == MAKE_TERRAIN(3, 0))
					bgdraw = Element(MAKE_TERRAIN(4, 1));	// River mouth: flowing right.
			}
			else if (up.IsSea() && down.IsRiver() && left.IsSea() && right.IsSea()
				&& GetBackground(x - 1, y - 1).IsSea() && GetBackground(x + 1, y - 1).IsSea())
			{
				UpdateDrawElement(x, y + 1);
				if (GetBackgroundDraw(x, y + 1) == MAKE_TERRAIN(3, 1))
					bgdraw = Element(MAKE_TERRAIN(4, 2));	// River mouth: flowing up.
			}
			else if (up.IsRiver() && down.IsSea() && left.IsSea() && right.IsSea()
				&& GetBackground(x - 1, y + 1).IsSea() && GetBackground(x + 1, y + 1).IsSea())
			{
				UpdateDrawElement(x, y - 1);
				if (GetBackgroundDraw(x, y - 1) == MAKE_TERRAIN(3, 1))
					bgdraw = Element(MAKE_TERRAIN(4, 3));	// River mouth: flowing down.
			}
			else
				bgdraw = TERRAIN_SEA;	// Default sea tile. Coast borders get added in DrawPanel::DrawElement.
			break;

		case TERRAIN_SHOAL:
			if (down.IsLand() && left.IsLand() && right.IsLand())
				bgdraw = Element(MAKE_TERRAIN(9, 7));	// Surrounded by land except to the north.
			else if (up.IsLand() && left.IsLand() && right.IsLand())
				bgdraw = Element(MAKE_TERRAIN(9, 6));	// Surrounded by land except to the up.
			else if (up.IsLand() && down.IsLand() && right.IsLand())
				bgdraw = Element(MAKE_TERRAIN(9, 5));	// Surrounded by land except to the left.
			else if (up.IsLand() && down.IsLand() && left.IsLand())
				bgdraw = Element(MAKE_TERRAIN(9, 4));	// Surrounded by land except to the right.
			else if (up.IsLand() && left.IsLand())
			{
				if (down.Simplify() == TERRAIN_SHOAL && right.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(13, 2));	// Land to up and left. Shoal to down and right.
				else if (down.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(11, 2));	// Land to up and left. Shoal to down.
				else if (right.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(13, 0));	// Land to up and left. Shoal to right.
				else
					bgdraw = Element(MAKE_TERRAIN(11, 0));	// Land to up and left. Shoal none.
			}
			else if (up.IsLand() && right.IsLand())
			{
				if (down.Simplify() == TERRAIN_SHOAL && left.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(12, 2));	// Land to up and right. Shoal to down and left.
				else if (down.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(14, 0));	// Land to up and right. Shoal to down.
				else if (left.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(14, 2));	// Land to up and right. Shoal to left.
				else
					bgdraw = Element(MAKE_TERRAIN(12, 0));	// Land to up and right. Shoal none.
			}
			else if (down.IsLand() && left.IsLand())
			{
				if (up.Simplify() == TERRAIN_SHOAL && right.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(11, 3));	// Land to down and left. Shoal to up and right.
				else if (up.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(13, 3));	// Land to down and left. Shoal to up.
				else if (right.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(13, 1));	// Land to down and left. Shoal to right.
				else
					bgdraw = Element(MAKE_TERRAIN(11, 1));	// Land to down and left. Shoal none.
			}
			else if (down.IsLand() && right.IsLand())
			{
				if (up.Simplify() == TERRAIN_SHOAL && left.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(12, 3));	// Land to down and right. Shoal to up and left.
				else if (up.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(14, 3));	// Land to down and right. Shoal to up.
				else if (left.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(14, 1));	// Land to down and right. Shoal to left.
				else
					bgdraw = Element(MAKE_TERRAIN(12, 1));	// Land to down and right. Shoal none.
			}
			else if (up.IsLand())
			{
				if (left.Simplify() == TERRAIN_SHOAL && right.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(9, 1));	// Land to up. Shoal to left and right.
				else if (left.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(11, 4));	// Land to up. Shoal to left.
				else if (right.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(12, 4));	// Land to up. Shoal to right.
				else
					bgdraw = Element(MAKE_TERRAIN(9, 3));	// Land to up. Shoal none.
			}
			else if (down.IsLand())
			{
				if (left.Simplify() == TERRAIN_SHOAL && right.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(10, 1));	// Land to down. Shoal to left and right.
				else if (left.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(11, 5));	// Land to down. Shoal to left.
				else if (right.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(12, 5));	// Land to down. Shoal to right.
				else
					bgdraw = Element(MAKE_TERRAIN(10, 3));	// Land to down. Shoal none.
			}
			else if (left.IsLand())
			{
				if (up.Simplify() == TERRAIN_SHOAL && down.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(9, 0));	// Land to left. Shoal to up and down.
				else if (up.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(11, 6));	// Land to left. Shoal to up.
				else if (down.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(11, 7));	// Land to left. Shoal to down.
				else
					bgdraw = Element(MAKE_TERRAIN(9, 2));	// Land to left. Shoal none.
			}
			else if (right.IsLand())
			{
				if (up.Simplify() == TERRAIN_SHOAL && down.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(10, 0));	// Land to right. Shoal to up and down.
				else if (up.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(12, 6));	// Land to right. Shoal to up.
				else if (down.Simplify() == TERRAIN_SHOAL)
					bgdraw = Element(MAKE_TERRAIN(12, 7));	// Land to right. Shoal to down.
				else
					bgdraw = Element(MAKE_TERRAIN(10, 2));	// Land to right. Shoal none.
			}
			break;
		}
	}

	return SetBackgroundDraw(x, y, bgdraw);
}

bool Map::IsPipeForDrawing(int x, int y)
{
	Element bg = GetBackground(x, y);
	if (bg.IsPipe())
		return true;
	if (bg.Simplify() == TERRAIN_PLAIND)
		return AllowPlacement(x, y, TERRAIN_SEAM);
	return false;
}
