#pragma once

#include <vector>
#include "Element.h"

#define MAP_MIN_WIDTH 1
#define MAP_MIN_HEIGHT 1
#define MAP_DEF_WIDTH 30
#define MAP_DEF_HEIGHT 20
#define MAP_MAX_WIDTH 10000
#define MAP_MAX_HEIGHT 10000

#define NAME_MAX_LEN		50
#define AUTHOR_MAX_LEN		50
#define DESCRIPTION_MAX_LEN	1024 * 100

#define PROPERTIES_LIMIT	60

#define COMPAT_IMPOSSIBLE	0
#define COMPAT_OK			1
#define COMPAT_TRUNCATE		2

typedef std::vector< std::vector<Background> > BackgroundArray;
typedef std::vector< std::vector<Foreground> > ForegroundArray;

class Map
{
private:
	bool m_dirty;

	BackgroundArray m_bg;
	BackgroundArray m_bgdraw;
	ForegroundArray m_fg;

	wxString m_name;
	wxString m_author;
	wxString m_description;

	int m_tileset;
	int m_width;
	int m_height;

public:
	Map(int width = -1, int height = -1);

	bool SetDirty(bool dirty = true);
	bool IsDirty();

	BackgroundArray* GetBackground();
	Background GetBackground(int x, int y);
	BackgroundArray* GetBackgroundDraw();
	Background GetBackgroundDraw(int x, int y);
	ForegroundArray* GetForeground();
	Foreground GetForeground(int x, int y);
	bool SetBackground(BackgroundArray* background);
	bool SetBackground(int x, int y, Background background, bool check = true);
	bool SetBackgroundDraw(BackgroundArray* background);
	bool SetBackgroundDraw(int x, int y, Background background);
	bool SetForeground(ForegroundArray* foreground);
	bool SetForeground(int x, int y, Foreground foreground);
	bool AllowPlacement(int x, int y, Element element, bool recheck = false);

	wxString GetName();
	wxString GetAuthor();
	wxString GetDescription();
	bool SetName(wxString name);
	bool SetAuthor(wxString author);
	bool SetDescription(wxString description);

	int GetTileset();
	int GetWidth();
	int GetHeight();
	bool SetTileset(int tileset);
	bool SetWidth(int width);
	bool SetHeight(int height);
	bool SetSize(int width, int height);
	bool Fill(Element element);

	int IsCompatibleSize(int maptype);
	int IsCompatibleElements(int maptype);

	bool UpdateDraw();
	bool UpdateDraw(int x, int y, int width, int height);
	bool UpdateDrawElement(int x, int y);
	bool IsPipeForDrawing(int x, int y);
};
