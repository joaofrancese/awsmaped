#pragma once

#include "Element.h"
#include "Map.h"
#include <set>

typedef std::set< Point <int> > PointSet;

#define TILESETS_NUMBER 6


class DrawPanel: public wxScrolledWindow
{
public:
	DrawPanel(wxWindow* parent, wxWindow* frameMain, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxSUNKEN_BORDER, const wxString& name = "drawpanel");


	wxMemoryDC m_spritesheetDC[SPRITESHEETS_COUNT][TILESETS_NUMBER];

	int m_prevx;
	int m_prevy;
	int m_prevsize;

	int m_mode;
	bool m_leftdown;
	int m_startx;
	int m_starty;
	int m_endx;
	int m_endy;
	PointSet m_mousepoints;

	bool m_selected;
	bool m_selectEraseOnChange;
	int m_selectx;
	int m_selecty;
	int m_selectw;
	int m_selecth;
	int m_selectx_former;
	int m_selecty_former;
	int m_selectx_previous;
	int m_selecty_previous;
	Map m_selectmap;



	//Event Handling: Others
	void EvPaint(wxPaintEvent& event);
	void EvMouse(wxMouseEvent& event);
	void EvFocus_Kill(wxFocusEvent& event);


	//Other misc methods.
	bool DrawMap(wxDC& drawDC);
	bool DrawElement(wxDC& drawDC, int x, int y, int tileset, Element element, bool composeSea = false, bool sourceFromSelection = false);
	bool SetElement(int x, int y, Element element, bool nextSprite = false, bool multiHQ = false);
	bool FillPoint(int x, int y, Element element, Direction direction, PointSet& tofill);

	bool Select(int x, int y, int width, int height);
	bool EraseSelection();
	bool EraseSelectionOnChange();
	bool SetSelection();
	bool CancelSelection(bool set = true, bool erase = false);
	bool RefreshSelection(int border = 1);

	int GetMode();
	bool SetMode(int mode);

	bool CutCopy(int actionId);
	bool Paste(int actionId);
	bool SelectAll(int actionId);
	bool Flip(int actionId);
	bool Rotate(int actionId);
	bool DeleteUnits(int actionId);


private:
	wxWindow* m_frameMain;	// To be converted to FrameMain pointer inside the methods.

    DECLARE_EVENT_TABLE()
};
