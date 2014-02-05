#pragma once

#include "Element.h"


#define PAGE_WIDTH 7
#define PAGE_HEIGHT 9

#define PAGE_SPACE_WIDTH 15
#define PAGE_SPACE_HEIGHT 15

#define PAGE_OFFSET_WIDTH 5
#define PAGE_OFFSET_HEIGHT 6  //Top offset is doubled.

#define PAGE_CALCULATED_WIDTH (PAGE_WIDTH * 16) + ((PAGE_WIDTH - 1) * PAGE_SPACE_WIDTH) + (2 * PAGE_OFFSET_WIDTH)
#define PAGE_CALCULATED_HEIGHT (PAGE_HEIGHT * 16) + ((PAGE_HEIGHT - 1) * PAGE_SPACE_HEIGHT) + (3 * PAGE_OFFSET_HEIGHT)

class Page: public wxNotebookPage
{
private:
    DECLARE_EVENT_TABLE()

	Element m_elements[PAGE_WIDTH][PAGE_HEIGHT];
	bool m_hasElements[PAGE_WIDTH][PAGE_HEIGHT];
	int m_currentX;
	int m_currentY;

	wxWindow* m_frameMain;

	wxMemoryDC m_selected;



public:
	Page(wxWindow* parent, wxWindow* frameMain, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
		long style = 0, const wxString& name = wxPanelNameStr);



	//Event Handling: Others
	void EvPaint(wxPaintEvent& event);
	void EvMouse_LeftDown(wxMouseEvent& event);


	//Other misc methods.
	Element GetCurrent();
	bool SetCurrent(Element element);
	bool UpdateCurrent(int x, int y);
	bool ChangeArmy(int newarmy);

	bool SetElement(int x, int y); // Clears element.
	bool SetElement(int x, int y, Element element);

};
