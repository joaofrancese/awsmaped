#include "precomp.h"
#include "Page.h"

#include "Element.h"
#include "FrameMain.h"
#include "DrawPanel.h"

#include "../Resource/xpmNotebookSelected.xpm"


BEGIN_EVENT_TABLE(Page, wxNotebookPage)

	// Event handling: Others
	EVT_PAINT(				Page::EvPaint)
	EVT_LEFT_DOWN(			Page::EvMouse_LeftDown)

END_EVENT_TABLE()




Page::Page(wxWindow* parent, wxWindow* frameMain, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxNotebookPage(parent, id, pos, size, style, name)
{
	m_frameMain = frameMain;

	wxImage imageSelected(xpmNotebookSelected);
	wxBitmap bitmapSelected(imageSelected);
	m_selected.SelectObject(bitmapSelected);

	m_currentX = 0;
	m_currentY = 0;

	int i, j;
	for (i = 0; i < PAGE_WIDTH; i++)
		for (j = 0; j < PAGE_HEIGHT; j++)
			m_hasElements[i][j] = false;
}



//////////////////////////////////////////////////////////
//                                                      //
//  EVENT HANDLING:  Others                             //
//                                                      //
//////////////////////////////////////////////////////////

void Page::EvPaint(wxPaintEvent& event)
{
	wxPaintDC paintDC(this);
	FrameMain* frameMain = (FrameMain*)m_frameMain;
	DrawPanel* drawPanel = frameMain->o_panelDraw;
	Map& map = frameMain->m_map;
	int tileset = map.GetTileset();
	Element element;

	paintDC.Blit(m_currentX * (16 + PAGE_SPACE_WIDTH) + PAGE_OFFSET_WIDTH - 4, m_currentY * (16 + PAGE_SPACE_HEIGHT) + (2 * PAGE_OFFSET_HEIGHT) - 4, 23, 23, &m_selected, 0, 0);
	int i, j;
	for (i = 0; i < PAGE_WIDTH; i++)
		for (j = 0; j < PAGE_HEIGHT; j++)
			if (m_hasElements[i][j])
				drawPanel->DrawElement(paintDC, i * (16 + PAGE_SPACE_WIDTH) + PAGE_OFFSET_WIDTH,  j * (16 + PAGE_SPACE_HEIGHT) + (2 * PAGE_OFFSET_HEIGHT), tileset, m_elements[i][j]); 	
}

void Page::EvMouse_LeftDown(wxMouseEvent& event)
{
	FrameMain* frameMain = (FrameMain*)m_frameMain;
	int x = event.GetX() - PAGE_OFFSET_WIDTH;
	int y = event.GetY() - (2 * PAGE_OFFSET_HEIGHT);

	if (x % (16 + PAGE_SPACE_WIDTH) < 16 && y % (16 + PAGE_SPACE_HEIGHT) < 16)
	{
		x /= (16 + PAGE_SPACE_WIDTH);
		y /= (16 + PAGE_SPACE_HEIGHT);
		if (GetCurrent().IsForeground() && m_elements[x][y].IsBuilding())
			ChangeArmy(m_elements[x][y].GetArmy());
		else
			UpdateCurrent(x, y);

		if (frameMain->o_panelDraw->GetMode() == FrameMain::ID_TOOL_SELECTOR)
			frameMain->o_panelDraw->SetMode(FrameMain::ID_TOOL_PENCIL);
	}

	event.Skip();
}



//////////////////////////////////////////////////////////
//                                                      //
//  OTHER MISC FUNCTIONS.                               //
//                                                      //
//////////////////////////////////////////////////////////

Element Page::GetCurrent()
{
	Element current = m_elements[m_currentX][m_currentY];
	if (current == Foreground(ELEMENT_UNIT_DELETE))
		return Foreground(ELEMENT_UNIT_EMPTY);
	else
		return current;
}

bool Page::SetCurrent(Element element)
{
	if (element == Foreground(ELEMENT_UNIT_EMPTY))
		element = Foreground(ELEMENT_UNIT_DELETE);

	if (element.IsUnitNonEmpty())
		ChangeArmy(element.GetArmy());

	if (element.IsTerrain() || element.IsExtra())
		element = element.Simplify();


	int i, j;
	for (i = 0; i < PAGE_WIDTH; i++)
		for (j = 0; j < PAGE_HEIGHT; j++)
		{
			if (m_elements[i][j] == element)
			{
				UpdateCurrent(i, j);
				return true;
			}
		}
	return false;
}

bool Page::UpdateCurrent(int x, int y)
{
	if (m_hasElements[x][y])
	{
		RefreshRect(wxRect(m_currentX * (16 + PAGE_SPACE_WIDTH) + PAGE_OFFSET_WIDTH - 4, m_currentY * (16 + PAGE_SPACE_HEIGHT) + (2 * PAGE_OFFSET_HEIGHT) - 4, 23, 23));
		m_currentX = x;
		m_currentY = y;
		RefreshRect(wxRect(m_currentX * (16 + PAGE_SPACE_WIDTH) + PAGE_OFFSET_WIDTH - 4, m_currentY * (16 + PAGE_SPACE_HEIGHT) + (2 * PAGE_OFFSET_HEIGHT) - 4, 23, 23));
		return true;
	}
	return false;
}

bool Page::ChangeArmy(int newarmy)
{
	int i, j;
	for (i = 0; i < PAGE_WIDTH; i++)
		for (j = 0; j < PAGE_HEIGHT; j++)
			if (m_elements[i][j].IsUnitNonEmpty())
				m_elements[i][j].ChangeArmy(newarmy);
	Refresh();
	return true;
}

bool Page::SetElement(int x, int y)
{
	if (x >= 0 && x < PAGE_WIDTH && y >= 0 && y < PAGE_HEIGHT && m_currentX != x && m_currentY != y)
	{
		m_hasElements[x][y] = false;
		return true;
	}
	else
		return false;
}

bool Page::SetElement(int x, int y, Element element)
{
	if (x >= 0 && x < PAGE_WIDTH && y >= 0 && y < PAGE_HEIGHT)
	{
		m_elements[x][y] = element;
		m_hasElements[x][y] = true;
		if (!m_hasElements[m_currentX][m_currentY])
		{
			m_currentX = x;
			m_currentY = y;
		}
		return true;
	}
	else
		return false;
}
