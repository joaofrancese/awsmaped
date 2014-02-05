#pragma once
#pragma warning(disable: 4786)	// Identifier name too long.
#pragma warning(disable: 4018)	// Signed/unsigned mismatch.
// This is the precompiled header file.
// Put here includes to files that are used frequently,
// but are rarely changed. It will speed up the compilation.



// Standard way of including the wxWidgets files.
// Uses precompiled headers if possible.
#include "wx/wxprec.h"
#ifdef __BORLANDC__
	#pragma hdrstop
#endif
#ifndef WX_PRECOMP
	#include "wx/wx.h"
#endif

// Other wxWidgets includes.
#include "wx/aboutdlg.h"
#include "wx/clipbrd.h"
#include "wx/file.h"
#include "wx/fileconf.h"
#include "wx/fs_mem.h"
#include "wx/image.h"
#ifndef __WXGTK
    #include "wx/mediactrl.h"
#endif
#include "wx/notebook.h"
#include "wx/spinctrl.h"
#include "wx/statline.h"
#include "wx/utils.h"
#include "wx/wfstream.h"


// Other default includes.



// Default defines.
#define BACKGROUND	0;
#define FOREGROUND	1;

#define TERRAIN		0;
#define UNIT		1;
#define EXTRA		2;

#define ENABLE_TIME_ACTIVATION	false
#define BGM_FILENAME			"bgm.mp3"

#ifdef _DEBUG
	#define DEBUGMESSAGE(message)	wxMessageBox(message);
#else
	#define DEBUGMESSAGE(message)
#endif


// Defines for making platform-specific contents easy.

#define IFWIN(contents)				contents
#define IFGTK(contents)
#define IFMAC(contents)

#ifdef __WXGTK__
	#undef IFWIN
	#undef IFGTK
	#define IFWIN(contents)
	#define IFGTK(contents)			contents
#endif

#ifdef __WXMAC__
	#undef IFWIN
	#undef IFMAC
	#define IFWIN(contents)
	#define IFMAC(contents)			contents
#endif

#define PLATSPEC(win, gtk, mac)		IFWIN(win) IFGTK(gtk) IFMAC(mac)


// Global variables. See also precomp.cpp.
extern wxString g_messageboxTitle;
extern wxString g_version;
extern wxString g_appname;
extern wxString g_clipboardstring;

extern bool g_infoVolumeEnable;
extern int g_infoVolume;
extern int g_infoDefaultWidth;
extern int g_infoDefaultHeight;
extern int g_infoDefaultTerrain;
extern int g_infoDefaultTileset;
extern wxString g_infoDefaultAuthor;
extern int g_infoUndoLimit;
extern bool g_infoDrawCursor;



// Global enums.
enum Direction
{
	DIR_NONE = 0,
	DIR_UP = 1,
	DIR_DOWN = 2,
	DIR_LEFT = 3,
	DIR_RIGHT = 4,
	DIR_NORTH = 1,
	DIR_SOUTH = 2,
	DIR_WEST = 3,
	DIR_EAST = 4,
	DIR_NW = 5,
	DIR_NE = 6,
	DIR_SW = 7,
	DIR_SE = 8,
	DIR_CENTER = 9
};



// Global functions.
wxString ConvertToString(long number);
long ConvertToNumber(wxString string);
long power(long a, long b);
bool DoNothing();



// Global classes.
template <class type>
class Point
{
	private:
		type m_x;
		type m_y;
	public:
		Point()
			{};
		Point(type x, type y)
			{ SetX(x); SetY(y); };
		type GetX() const
			{ return m_x; };
		type GetY() const
			{ return m_y; };
		type SetX(const type x)
			{ m_x = x; return x; };
		type SetY(const type y)
			{ m_y = y; return y; };
		bool operator<(const Point& point) const
			{ if (GetX() != point.GetX()) return GetX() < point.GetX(); else return GetY() < point.GetY(); };
		bool operator>(const Point& point) const
			{ if (GetX() != point.GetX()) return GetX() > point.GetX(); else return GetY() > point.GetY(); };
		bool operator<=(const Point& point) const
			{ if (GetX() != point.GetX()) return GetX() <= point.GetX(); else return GetY() <= point.GetY(); };
		bool operator>=(const Point& point) const
			{ if (GetX() != point.GetX()) return GetX() >= point.GetX(); else return GetY() >= point.GetY(); };
		bool operator==(const Point& point) const
			{ return (GetX() == point.GetX()) && (GetY() == point.GetY()); };
		bool operator!=(const Point& point) const
			{ return (GetX() != point.GetX()) || (GetY() != point.GetY()); };
};
