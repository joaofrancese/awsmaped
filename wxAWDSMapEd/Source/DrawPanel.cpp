#include "precomp.h"
#include "DrawPanel.h"

#include <set>
#include "FrameMain.h"
#include "Page.h"

BEGIN_EVENT_TABLE(DrawPanel, wxPanel)

	// Event handling: Others
	EVT_PAINT(			DrawPanel::EvPaint)
	EVT_MOUSE_EVENTS(	DrawPanel::EvMouse)
	EVT_KILL_FOCUS(		DrawPanel::EvFocus_Kill)

END_EVENT_TABLE()



DrawPanel::DrawPanel(wxWindow* parent, wxWindow* frameMain, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxScrolledWindow(parent, id, pos, size, style, name)
{
	m_frameMain = frameMain;

	#include "DrawPanel_spritesheets.h"
	wxImage spritesheetImage[SPRITESHEETS_COUNT][TILESETS_NUMBER];
	wxBitmap spritesheetBitmap[SPRITESHEETS_COUNT][TILESETS_NUMBER];
	int i, j;
	for (i = 0; i < SPRITESHEETS_COUNT; i++)
		for (j = 0; j < TILESETS_NUMBER; j++)
		{
			spritesheetImage[i][j] = wxImage(spritesheetdata[i][j]);
			spritesheetImage[i][j].SetMaskFromImage(wxImage(spritesheetmask[i][j]), 255, 255, 255);
			spritesheetBitmap[i][j] = wxBitmap(spritesheetImage[i][j]);
			m_spritesheetDC[i][j].SelectObject(spritesheetBitmap[i][j]);
		}

	if (g_infoDrawCursor)
	{
		wxImage blankimage(1, 1, true);
		blankimage.SetMaskColour(0, 0, 0);
		blankimage.SetMask(true);
		SetCursor(blankimage);
	}
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);

	m_prevx = 0;
	m_prevy = 0;
	m_prevsize = 1;
	m_mode = FrameMain::ID_TOOL_PENCIL;
	m_startx = 0;
	m_starty = 0;
	m_endx = 0;
	m_endy = 0;
	m_leftdown = false;
}


//////////////////////////////////////////////////////////
//                                                      //
//  EVENT HANDLING:  Others                             //
//                                                      //
//////////////////////////////////////////////////////////

void DrawPanel::EvPaint(wxPaintEvent& event)
{
	wxPaintDC paintDC(this);
	DoPrepareDC(paintDC);

	// Find out where the window is scrolled to.
	int vbX,vbY;					// Top left corner of client
	GetViewStart(&vbX,&vbY);
	int vX,vY,vW,vH;				// Dimensions of client area in pixels
	wxRegionIterator upd;			// Get the update rect list.
	
	upd = GetUpdateRegion();
 	while (upd)
	{
		CalcUnscrolledPosition(upd.GetX(), upd.GetY(), &vX, &vY);
	    vW = upd.GetW();
	    vH = upd.GetH();
		paintDC.DestroyClippingRegion();
		paintDC.SetClippingRegion(vX, vY, vW, vH);
		DrawMap(paintDC);

		if (m_selected)
		{
			int i, j;
			int xtemp, ytemp;
			for (i = 0; i < m_selectw; i++)
				for (j = 0; j < m_selecth; j++)
				{
					if (wxRect(vX - 16, vY - 16, vW + 32, vH + 32).Inside((m_selectx + i) * 16, (m_selecty + j) * 16))
					{
						xtemp = (m_selectx + i) * 16;
						ytemp = (m_selecty + j) * 16;
						DrawElement(paintDC, xtemp, ytemp, ((FrameMain*)m_frameMain)->m_map.GetTileset(), m_selectmap.GetBackgroundDraw(i, j), true, true);
						DrawElement(paintDC, xtemp, ytemp, ((FrameMain*)m_frameMain)->m_map.GetTileset(), m_selectmap.GetForeground(i, j));
					}
				}
			paintDC.SetBrush(*wxTRANSPARENT_BRUSH);
			paintDC.SetPen(wxPen("BLACK", 1, wxDOT));
			paintDC.DrawRectangle(m_selectx * 16, m_selecty * 16, m_selectw * 16, m_selecth * 16);
		}
		upd++;
	}
}

void DrawPanel::EvMouse(wxMouseEvent& event)
{
	
	//// Prepare variables. ////

	FrameMain* frameMain = (FrameMain*)m_frameMain;
	Page* currentPage = (Page*)(frameMain->o_notebookMain->GetCurrentPage());
	Element currentElement = currentPage->GetCurrent();
	int x, y, xpx, ypx, xscroll, yscroll;
	int xincr, yincr;
	xscroll = event.GetX();
	yscroll = event.GetY();
	CalcUnscrolledPosition(xscroll, yscroll, &xpx, &ypx);
	x = xpx / 16;
	y = ypx / 16;
	xscroll /= 16;
	yscroll /= 16;

	
	//// Update FrameMain's statusbar with mouse coordinates. ////

	if (event.Leaving())
		frameMain->UpdateMouseCoordinates();
	else
		frameMain->UpdateMouseCoordinates(x, y);


	//// Keep the focus in this window, so wheel scroll will work as soon as the user hovers the mouse over the panel. ////

	if (event.Entering())
		SetFocus();


	//// Erase previous cursor. ////

	if (g_infoDrawCursor && (GetRect().Inside(event.GetX(), event.GetY()) || event.Leaving()))
	{
		int evx = event.GetX();
		int evy = event.GetY();

		// AW1 Delete/Forbidden icon has 48-width. That's why those widths marked with /**/ are 16px bigger than they should be.
		if (m_prevsize == 3)
			RefreshRect(wxRect(((m_prevx / 16) * 16) - 16, ((m_prevy / 16) * 16) - 16, 64/**/, 48));
		else if (m_prevsize == 4)
			RefreshRect(wxRect(((m_prevx / 16) * 16) - 16, ((m_prevy / 16) * 16) - 16, 64, 64));
		else
			RefreshRect(wxRect(((m_prevx / 16) * 16) - 1, ((m_prevy / 16) * 16) - 1, 49/**/, 33));
		Update();
	}


	//// Left button pressed. ////

	if (event.LeftDown())
	{
		m_leftdown = true;
		m_startx = xpx;
		m_starty = ypx;
		m_mousepoints.clear();

		if (GetMode() == FrameMain::ID_TOOL_LINE || GetMode() == FrameMain::ID_TOOL_SQUARE ||
			GetMode() == FrameMain::ID_TOOL_SQUAREFILL || GetMode() == FrameMain::ID_TOOL_BUCKET)
		{
			if (currentElement.GetSize() > 1)
			{
				m_leftdown = false;
				wxBell();
			}
		}

		if (GetMode() == FrameMain::ID_TOOL_PENCIL && m_leftdown)
			frameMain->AddUndoPoint();

		if (GetMode() == FrameMain::ID_TOOL_BUCKET && m_leftdown)
		{
			frameMain->AddUndoPoint();
			Point<int> curpoint;
			PointSet pointset;
			PointSet::iterator pointiter;
			FillPoint(x, y, frameMain->m_map.GetBackground(x, y), DIR_NONE, pointset);
			for (pointiter = pointset.begin(); pointiter != pointset.end(); pointiter++)
				SetElement((*pointiter).GetX(), (*pointiter).GetY(), currentElement);
			Update();
		}

		if (GetMode() == FrameMain::ID_TOOL_SELECTOR && m_leftdown)
		{
			if (m_selected)
			{
				if (m_startx / 16 >= m_selectx && m_startx / 16 < m_selectx + m_selectw &&
					m_starty / 16 >= m_selecty && m_starty / 16 < m_selecty + m_selecth)
				{
					m_selectx_former = m_selectx;
					m_selecty_former = m_selecty;
					
					if (event.ControlDown())
					{
						SetSelection();
						if (m_selectEraseOnChange)
							m_selectEraseOnChange = false;
					}
				}
				else
					CancelSelection();
			}
		}
	}


	//// Leaving the map area while the button is down. Cancel activities. ////
	
	if (event.LeftIsDown() && event.Leaving() && m_leftdown)
	{
		if (GetMode() == FrameMain::ID_TOOL_LINE || GetMode() == FrameMain::ID_TOOL_SQUARE ||
			GetMode() == FrameMain::ID_TOOL_SQUAREFILL || GetMode() == FrameMain::ID_TOOL_SELECTOR)
		{
			wxBell();
			m_leftdown = false;

			PointSet::iterator pointiter;
			int rectx, recty;
			for (pointiter = m_mousepoints.begin(); pointiter != m_mousepoints.end(); pointiter++)
			{
				CalcScrolledPosition((*pointiter).GetX() * 16, (*pointiter).GetY() * 16, &rectx, &recty);
				RefreshRect(wxRect(rectx, recty - 16, 16, 32));
			}
			Update();
		}
	}


	//// This is a safeguard for the problem of Leaving not being registered if the mouse is moved out too fast.
	if (!event.LeftIsDown() && !event.LeftUp() && m_leftdown)
	{
		wxBell();
		m_leftdown = false;
		Refresh();
		Update();
	}


	//// Left button is down (or was just released). ////

	if ((event.LeftIsDown() || event.LeftUp()) && m_leftdown)
	{
		m_endx = xpx;
		m_endy = ypx;

		if (m_startx > m_endx)
			xincr = -1;
		else
			xincr = +1;

		if (m_starty > m_endy)
			yincr = -1;
		else
			yincr = +1;


		int prevx, prevy;
		CalcUnscrolledPosition(m_prevx, m_prevy, &prevx, &prevy);

		if (GetMode() == FrameMain::ID_TOOL_PENCIL && event.LeftIsDown())
			SetElement(x, y, currentElement, event.ControlDown(), event.ShiftDown());

		if (GetMode() == FrameMain::ID_TOOL_LINE || GetMode() == FrameMain::ID_TOOL_SQUARE ||
			GetMode() == FrameMain::ID_TOOL_SQUAREFILL || GetMode() == FrameMain::ID_TOOL_SELECTOR)
		{
			int i, j;
			int rectx, recty, rectw, recth;
			int lenx = m_endx - m_startx;
			int leny = m_endy - m_starty;
			Point<int> curpoint;
			PointSet oldpoints = m_mousepoints;
			PointSet extraerasedpoints;
			PointSet::iterator pointiter;

			if (x != prevx / 16 || y != prevy / 16 || event.LeftUp())
			{
				m_mousepoints.clear();

				if (GetMode() == FrameMain::ID_TOOL_LINE)
				{
					for (i = m_startx; (i <= m_endx && xincr > 0) || (i >= m_endx && xincr < 0); i += xincr)
					{
						j = i - m_startx;
						j = (((float)j) / lenx) * leny;
						j = j + m_starty;
						curpoint.SetX(i / 16);
						curpoint.SetY(j / 16);
						m_mousepoints.insert(curpoint);
					}
					for (i = m_starty; (i <= m_endy && yincr > 0) || (i >= m_endy && yincr < 0); i += yincr)
					{
						j = i - m_starty;
						j = (((float)j) / leny) * lenx;
						j = j + m_startx;
						curpoint.SetX(j / 16);
						curpoint.SetY(i / 16);
						m_mousepoints.insert(curpoint);
					}
				}

				if (GetMode() == FrameMain::ID_TOOL_SQUARE)
				{
					for (i = m_startx / 16; (i <= m_endx / 16 && xincr > 0) || (i >= m_endx / 16 && xincr < 0); i += xincr)
					{
						curpoint.SetX(i);
						curpoint.SetY(m_starty / 16);
						m_mousepoints.insert(curpoint);
						curpoint.SetY(m_endy / 16);
						m_mousepoints.insert(curpoint);
					}
					for (i = m_starty / 16; (i <= m_endy / 16 && yincr > 0) || (i >= m_endy / 16 && yincr < 0); i += yincr)
					{
						curpoint.SetY(i);
						curpoint.SetX(m_startx / 16);
						m_mousepoints.insert(curpoint);
						curpoint.SetX(m_endx / 16);
						m_mousepoints.insert(curpoint);
					}
				}

				if (GetMode() == FrameMain::ID_TOOL_SQUAREFILL)
				{
					for (i = m_startx / 16; (i <= m_endx / 16 && xincr > 0) || (i >= m_endx / 16 && xincr < 0); i += xincr)
						for (j = m_starty / 16; (j <= m_endy / 16 && yincr > 0) || (j >= m_endy / 16 && yincr < 0); j += yincr)
						{
							curpoint.SetX(i);
							curpoint.SetY(j);
							m_mousepoints.insert(curpoint);
						}
				}

				if (GetMode() == FrameMain::ID_TOOL_SELECTOR)
				{
					if ((m_startx == m_endx && m_starty == m_endy && m_mousepoints.empty()) || m_selected)
						DoNothing();
					else
					{
						for (i = m_startx / 16; (i <= m_endx / 16 && xincr > 0) || (i >= m_endx / 16 && xincr < 0); i += xincr)
						{
							curpoint.SetX(i);
							curpoint.SetY(m_starty / 16);
							m_mousepoints.insert(curpoint);
							curpoint.SetY(m_endy / 16);
							m_mousepoints.insert(curpoint);
						}
						for (i = m_starty / 16; (i <= m_endy / 16 && yincr > 0) || (i >= m_endy / 16 && yincr < 0); i += yincr)
						{
							curpoint.SetY(i);
							curpoint.SetX(m_startx / 16);
							m_mousepoints.insert(curpoint);
							curpoint.SetX(m_endx / 16);
							m_mousepoints.insert(curpoint);
						}
					}
				}

				for (pointiter = oldpoints.begin(); pointiter != oldpoints.end(); pointiter++)
				{
					if (m_mousepoints.find((*pointiter)) == m_mousepoints.end() ||
						event.LeftUp() || GetMode() == FrameMain::ID_TOOL_SELECTOR)
					{
						curpoint = (*pointiter);
						CalcScrolledPosition(curpoint.GetX() * 16, curpoint.GetY() * 16, &rectx, &recty);
						RefreshRect(wxRect(rectx, recty - 16, 16, 32));

						curpoint.SetY(curpoint.GetY() - 1);
						extraerasedpoints.insert(curpoint);
					}
				}
				Update();
			}

			if (event.LeftIsDown() && GetMode() == FrameMain::ID_TOOL_SELECTOR)
			{
				if (m_mousepoints.empty())
					DoNothing();
				else
				{
					wxClientDC clientDC(this);
					clientDC.SetBrush(*wxTRANSPARENT_BRUSH);
					clientDC.SetPen(wxPen("BLACK", 1, wxDOT));

					rectx = (*(m_mousepoints.begin())).GetX();
					recty = (*(m_mousepoints.begin())).GetY();
					rectw = 0;
					recth = 0;
					for (pointiter = m_mousepoints.begin(); pointiter != m_mousepoints.end(); pointiter++)
					{
						if ((*pointiter).GetX() < rectx)				rectx = (*pointiter).GetX();
						if ((*pointiter).GetY() < recty)				recty = (*pointiter).GetY();
						if ((*pointiter).GetX() - rectx + 1 > rectw)	rectw = (*pointiter).GetX() - rectx + 1;
						if ((*pointiter).GetY() - recty + 1 > recth)	recth = (*pointiter).GetY() - recty + 1;
					}

					rectx *= 16;
					recty *= 16;
					rectw *= 16;
					recth *= 16;
					CalcScrolledPosition(rectx, recty, &rectx, &recty);

					clientDC.DrawRectangle(rectx, recty, rectw, recth);
					Update();
				}
			}
			else if (event.LeftIsDown())
			{
				wxClientDC clientDC(this);
				for (pointiter = m_mousepoints.begin(); pointiter != m_mousepoints.end(); pointiter++)
					if (oldpoints.find((*pointiter)) == oldpoints.end() || extraerasedpoints.find((*pointiter)) != extraerasedpoints.end() ||
						((*pointiter).GetX() * 16 >= prevx - 32 && (*pointiter).GetX() * 16 <= prevx + 64) ||
						((*pointiter).GetY() * 16 >= prevx - 32 && (*pointiter).GetY() * 16 <= prevy + 64))
					{
						rectx = (*pointiter).GetX() * 16;
						recty = (*pointiter).GetY() * 16;
						CalcScrolledPosition(rectx, recty, &rectx, &recty);
						DrawElement(clientDC, rectx, recty, frameMain->m_map.GetTileset(), currentElement);
					}
				Update();
			}

		}

		if (GetMode() == FrameMain::ID_TOOL_SELECTOR && m_selected)
		{
			if (m_startx / 16 != m_endx / 16 || m_starty / 16 != m_endy / 16)
				EraseSelectionOnChange();

			m_selectx = m_selectx_former + (m_endx / 16) - (m_startx / 16);
			m_selecty = m_selecty_former + (m_endy / 16) - (m_starty / 16);

			int prevx, prevy;
			CalcUnscrolledPosition(m_prevx, m_prevy, &prevx, &prevy);
			if (x != prevx / 16 || y != prevy / 16)
			{
				int refreshx, refreshy;

				CalcScrolledPosition((m_selectx_previous - 2) * 16, (m_selecty_previous - 2) * 16, &refreshx, &refreshy);
				RefreshRect(wxRect(refreshx, refreshy, (m_selectw + 4) * 16, (m_selecth + 4) * 16));
				m_selectx_previous = m_selectx;
				m_selecty_previous = m_selecty;

				RefreshSelection();
				Update();
			}

		}
	}


	//// Left button released. ////

	if (event.LeftUp() && m_leftdown)
	{
		m_leftdown = false;

		if (GetMode() == FrameMain::ID_TOOL_LINE || GetMode() == FrameMain::ID_TOOL_SQUARE ||
			GetMode() == FrameMain::ID_TOOL_SQUAREFILL)
		{
			frameMain->AddUndoPoint();
			Point<int> curpoint;
			PointSet::iterator pointiter;
			for (pointiter = m_mousepoints.begin(); pointiter != m_mousepoints.end(); pointiter++)
			{
				curpoint = *pointiter;
				SetElement(curpoint.GetX(), curpoint.GetY(), currentElement, event.ControlDown(), event.ShiftDown());
			}
		}

		if (GetMode() == FrameMain::ID_TOOL_SELECTOR && !m_selected)
		{
			if (m_startx == m_endx && m_starty == m_endy)
				m_selected = false;
			else
			{
				m_selected = true;

				int rectx = (*(m_mousepoints.begin())).GetX();
				int recty = (*(m_mousepoints.begin())).GetY();
				int rectw = 0;
				int recth = 0;
				PointSet::iterator pointiter;
				for (pointiter = m_mousepoints.begin(); pointiter != m_mousepoints.end(); pointiter++)
				{
					if ((*pointiter).GetX() < rectx)				rectx = (*pointiter).GetX();
					if ((*pointiter).GetY() < recty)				recty = (*pointiter).GetY();
					if ((*pointiter).GetX() - rectx + 1 > rectw)	rectw = (*pointiter).GetX() - rectx + 1;
					if ((*pointiter).GetY() - recty + 1 > recth)	recth = (*pointiter).GetY() - recty + 1;
				}

				Select(rectx, recty, rectw, recth);
				Update();
			}
		}
	}


	//// Middle button click. Switch active tab. ////

	if (event.MiddleDown())
	{
		frameMain->o_notebookMain->AdvanceSelection();
	}


	//// Right button click. Pick selected terrain/unit. ////

	if (event.RightDown())
	{
		Element background = frameMain->m_map.GetBackground(x, y);
		Element foreground = frameMain->m_map.GetForeground(x, y);
		if (currentElement.IsBackground())
		{
			if (background.IsTerrain() || background.IsBuilding())
			{
				frameMain->o_notepageTerrain->SetCurrent(background);
				frameMain->o_notebookMain->SetSelection(PAGE_TERRAIN);
			}
			if (background.IsExtra())
			{
				frameMain->o_notepageExtra->SetCurrent(background);
				frameMain->o_notebookMain->SetSelection(PAGE_EXTRA);
			}
		}
		else
		{
			if (foreground.IsUnit())
			{
				frameMain->o_notepageUnit->SetCurrent(foreground);
				frameMain->o_notebookMain->SetSelection(PAGE_UNIT);
			}
		}
	}


	//// Mouse wheel rotation. Change army, if applicable. ////

	if (event.GetWheelRotation() < 0 || event.GetWheelRotation() > 0)
	{
		int change;
		if (event.GetWheelRotation() < 0)
			change = -1;
		else
			change = 1;
		if (currentElement.IsBuilding() && currentElement != BUILDING_SILO)
		{
			int army = currentElement.GetArmy() - change;
			if (army < 0)
				army = ARMY_NEUTRAL;
			if (army > ARMY_NEUTRAL)
				army = 0;
			if (army == ARMY_NEUTRAL && currentElement.Simplify() == BUILDING_HQ)
				army = 0;
			frameMain->o_notepageTerrain->SetCurrent(currentElement.ChangeArmy(army, Element()));
		}
		if (currentElement.IsUnitNonEmpty())
		{
			int army = currentElement.GetArmy() - change;
			if (army < 0)
				army = ARMY_NEUTRAL - 1;
			if (army == ARMY_NEUTRAL)
				army = 0;
			frameMain->o_notepageUnit->SetCurrent(currentElement.ChangeArmy(army, Element()));
		}
	}


	//// Update cursor position. Redraw. ////

	if (g_infoDrawCursor && GetRect().Inside(event.GetX(), event.GetY()) && !event.Leaving())
	{
		Update();
		int evx = event.GetX();
		int evy = event.GetY();
		Map& map = frameMain->m_map;
		m_prevsize = currentElement.GetSize();

		wxClientDC clientDC(this);
		if (m_prevsize == 3 && GetMode() == FrameMain::ID_TOOL_PENCIL)
			clientDC.Blit((xscroll * 16) - 16, (yscroll * 16) - 16, 48, 48, &m_spritesheetDC[SPRITESHEETS_MISC][map.GetTileset()], 18, 16, wxCOPY, true);
		else if (m_prevsize == 4 && GetMode() == FrameMain::ID_TOOL_PENCIL)
			clientDC.Blit((xscroll * 16) - 16, (yscroll * 16) - 16, 64, 64, &m_spritesheetDC[SPRITESHEETS_MISC][map.GetTileset()], 0, 64, wxCOPY, true);
		else
			clientDC.Blit((xscroll * 16) - 1, (yscroll * 16) - 1, 18, 18, &m_spritesheetDC[SPRITESHEETS_MISC][map.GetTileset()], 0, 16, wxCOPY, true);

		if (currentElement == ELEMENT_UNIT_DELETE || currentElement == ELEMENT_UNIT_EMPTY)
			clientDC.Blit(evx, evy, 32, 16, &m_spritesheetDC[SPRITESHEETS_MISC][map.GetTileset()], 48, 0, wxCOPY, true);
		else if ((!map.AllowPlacement(x, y, currentElement) && GetMode() == FrameMain::ID_TOOL_PENCIL)||
				(currentElement.GetSize() > 1 && (GetMode() == FrameMain::ID_TOOL_LINE ||
													GetMode() == FrameMain::ID_TOOL_SQUARE ||
													GetMode() == FrameMain::ID_TOOL_SQUAREFILL ||
													GetMode() == FrameMain::ID_TOOL_BUCKET)))
			clientDC.Blit(evx, evy, 32, 16, &m_spritesheetDC[SPRITESHEETS_MISC][map.GetTileset()], 16, 0, wxCOPY, true);
		else
			clientDC.Blit(evx, evy, 16, 16, &m_spritesheetDC[SPRITESHEETS_MISC][map.GetTileset()], 0, 0, wxCOPY, true);
	}

	m_prevx = event.GetX();
	m_prevy = event.GetY();

	// Rotating the wheel in a map over 20tl height causes problem, so let's just disable it altogether.
	if (event.GetWheelRotation() == 0)
		event.Skip();
}


void DrawPanel::EvFocus_Kill(wxFocusEvent& event)
{
	if (m_leftdown)
	{
		m_leftdown = false;

		PointSet::iterator pointiter;
		int rectx, recty;
		for (pointiter = m_mousepoints.begin(); pointiter != m_mousepoints.end(); pointiter++)
		{
			CalcScrolledPosition((*pointiter).GetX() * 16, (*pointiter).GetY() * 16, &rectx, &recty);
			RefreshRect(wxRect(rectx, recty - 16, 16, 32));
		}
		Update();
	}
}


//////////////////////////////////////////////////////////
//                                                      //
//  OTHER MISC FUNCTIONS.                               //
//                                                      //
//////////////////////////////////////////////////////////

bool DrawPanel::DrawMap(wxDC& drawDC)
{
	FrameMain* frameMain = (FrameMain*)m_frameMain;
	Map& map = frameMain->m_map;
	int tileset = map.GetTileset();

	int x, y, width, height;
	drawDC.GetClippingBox(&x, &y, &width, &height);

	int x0, y0, x1, y1;
	x0 = (x / 16) - 1;
	y0 = (y / 16) - 1;
	x1 = ((x + width) / 16) + 3;
	y1 = ((y + height) / 16) + 3;
	if (x0 < 0)
		x0 = 0;
	if (y0 < 0)
		y0 = 0;
	if (x1 > map.GetWidth() || width == 0)
		x1 = map.GetWidth();
	if (y1 > map.GetHeight() || height == 0)
		y1 = map.GetHeight();

	int i, j;
	for (i = x0; i < x1; i++)
		for (j = y0; j < y1; j++)
		{
			DrawElement(drawDC, i * 16, j * 16, tileset, map.GetBackgroundDraw(i, j), true);
			DrawElement(drawDC, i * 16, j * 16, tileset, map.GetForeground(i, j));
		}
	return true;
}

bool DrawPanel::DrawElement(wxDC& drawDC, int x, int y, int tileset, Element element, bool composeSea, bool sourceFromSelection)
{
	if (element.Drawable())
	{
		wxMemoryDC* spritesheet = &m_spritesheetDC[element.GetSpritesheet()][tileset];
		if (element.DoubleHeight())
			drawDC.Blit(x, y - 16, 16, 32, spritesheet, element.GetDrawX() * 16, element.GetDrawY() * 16, wxCOPY, true);
		else
			drawDC.Blit(x, y, 16, 16, spritesheet, element.GetDrawX() * 16, element.GetDrawY() * 16, wxCOPY, true);

		if (composeSea && element == TERRAIN_SEA)
		{
			FrameMain* frameMain = (FrameMain*)m_frameMain;
			Map* map;
			int mapx, mapy;

			if (sourceFromSelection)
			{
				map = &m_selectmap;
				mapx = x / 16 - m_selectx;
				mapy = y / 16 - m_selecty;
			}
			else
			{
				map = &(frameMain->m_map);
				mapx = x / 16;
				mapy = y / 16;
			}
			Element up = map->GetBackground(mapx, mapy - 1);
			Element down = map->GetBackground(mapx, mapy + 1);
			Element left = map->GetBackground(mapx - 1, mapy);
			Element right = map->GetBackground(mapx + 1, mapy);

			if (map->GetBackground(mapx - 1, mapy - 1).IsLand() && !up.IsLand() && !left.IsLand())		// Up-left.
				drawDC.Blit(x, y, 16, 16, spritesheet, Element(MAKE_TERRAIN(6, 3)).GetDrawX() * 16, Element(MAKE_TERRAIN(6, 3)).GetDrawY() * 16, wxCOPY, true);
			if (map->GetBackground(mapx + 1, mapy - 1).IsLand() && !up.IsLand() && !right.IsLand())		// Up-right.
				drawDC.Blit(x, y, 16, 16, spritesheet, Element(MAKE_TERRAIN(5, 3)).GetDrawX() * 16, Element(MAKE_TERRAIN(5, 3)).GetDrawY() * 16, wxCOPY, true);
			if (map->GetBackground(mapx + 1, mapy + 1).IsLand() && !down.IsLand() && !left.IsLand())		// Down-right.
				drawDC.Blit(x, y, 16, 16, spritesheet, Element(MAKE_TERRAIN(5, 2)).GetDrawX() * 16, Element(MAKE_TERRAIN(5, 2)).GetDrawY() * 16, wxCOPY, true);
			if (map->GetBackground(mapx - 1, mapy + 1).IsLand() && !down.IsLand() && !right.IsLand())	// Down-left.
				drawDC.Blit(x, y, 16, 16, spritesheet, Element(MAKE_TERRAIN(6, 2)).GetDrawX() * 16, Element(MAKE_TERRAIN(6, 2)).GetDrawY() * 16, wxCOPY, true);

			if (left.IsLand())	// Left.
				drawDC.Blit(x, y, 16, 16, spritesheet, Element(MAKE_TERRAIN(5, 4)).GetDrawX() * 16, Element(MAKE_TERRAIN(5, 4)).GetDrawY() * 16, wxCOPY, true);
			if (up.IsLand())	// Up.
				drawDC.Blit(x, y, 16, 16, spritesheet, Element(MAKE_TERRAIN(5, 5)).GetDrawX() * 16, Element(MAKE_TERRAIN(5, 5)).GetDrawY() * 16, wxCOPY, true);
			if (right.IsLand())	// Right.
				drawDC.Blit(x, y, 16, 16, spritesheet, Element(MAKE_TERRAIN(6, 4)).GetDrawX() * 16, Element(MAKE_TERRAIN(6, 4)).GetDrawY() * 16, wxCOPY, true);
			if (down.IsLand())	// Down.
				drawDC.Blit(x, y, 16, 16, spritesheet, Element(MAKE_TERRAIN(6, 5)).GetDrawX() * 16, Element(MAKE_TERRAIN(6, 5)).GetDrawY() * 16, wxCOPY, true);

			if (up.IsLand() && left.IsLand())		// Corner up & left.
				drawDC.Blit(x, y, 16, 16, spritesheet, Element(MAKE_TERRAIN(5, 0)).GetDrawX() * 16, Element(MAKE_TERRAIN(5, 0)).GetDrawY() * 16, wxCOPY, true);
			if (up.IsLand() && right.IsLand())		// Corner up & right.
				drawDC.Blit(x, y, 16, 16, spritesheet, Element(MAKE_TERRAIN(6, 0)).GetDrawX() * 16, Element(MAKE_TERRAIN(6, 0)).GetDrawY() * 16, wxCOPY, true);
			if (down.IsLand() && left.IsLand())		// Corner down & left.
				drawDC.Blit(x, y, 16, 16, spritesheet, Element(MAKE_TERRAIN(5, 1)).GetDrawX() * 16, Element(MAKE_TERRAIN(5, 1)).GetDrawY() * 16, wxCOPY, true);
			if (down.IsLand() && right.IsLand())	// Corner down & right.
				drawDC.Blit(x, y, 16, 16, spritesheet, Element(MAKE_TERRAIN(6, 1)).GetDrawX() * 16, Element(MAKE_TERRAIN(6, 1)).GetDrawY() * 16, wxCOPY, true);
		}
	}
	return true;
}

bool DrawPanel::SetElement(int x, int y, Element element, bool nextSprite, bool multiHQ)
{
	FrameMain* frameMain = (FrameMain*)m_frameMain;
	Map* map = &(frameMain->m_map);
	int xdraw, ydraw;
	CalcScrolledPosition(x * 16, y * 16, &xdraw, &ydraw);
	Element previousbg = map->GetBackground(x, y);
	Element previousfg = map->GetForeground(x, y);

	if (element.IsBackground())
	{
		if (element != previousbg || nextSprite)
		{
			// Check for sprite-forcing.
			if (nextSprite  && element.Simplify() == previousbg.Simplify() && element.IsTerrain())
				element = previousbg.GetNext();

			if (map->SetBackground(x, y, element))
			{
				RefreshRect(wxRect(xdraw - 32, ydraw - 32, 80, 80));

				if (!map->AllowPlacement(x, y, map->GetForeground(x, y), true))
					SetElement(x, y, Element(ELEMENT_UNIT_EMPTY));

	
				// Prepare for nearby terrain tiles checking.
				std::vector<int> xarray, yarray;
				int i, j;

				// BEGIN Bridges.
				if (element == TERRAIN_BRIDGE)
				{
					Element up = map->GetBackground(x, y - 1);
					Element down = map->GetBackground(x, y + 1);
					Element left = map->GetBackground(x - 1, y);
					Element right = map->GetBackground(x + 1, y);
					if (previousbg.Simplify() == TERRAIN_RIVER)
					{
						map->SetBackground(x, y, Element(TERRAIN_RIVER));
						if (up.IsRiver() || down.IsRiver())
							map->SetBackground(x, y, Element(TERRAIN_BRIDGEH));	// Horizontal.
						else
							map->SetBackground(x, y, Element(TERRAIN_BRIDGEV));	// Vertical.
					}
					else
					{
						map->SetBackground(x, y, Element(TERRAIN_SEA));
						if (up.IsLand() || down.IsLand())
							map->SetBackground(x, y, Element(TERRAIN_BRIDGEV));	// Vertical.
						else if (left.IsLand() || right.IsLand())
							map->SetBackground(x, y, Element(TERRAIN_BRIDGEH));	// Horizontal.
						else if (up == TERRAIN_BRIDGEV || down == TERRAIN_BRIDGEV)
							map->SetBackground(x, y, Element(TERRAIN_BRIDGEV));	// Vertical.
						else if (left == TERRAIN_BRIDGEH || right == TERRAIN_BRIDGEH)
							map->SetBackground(x, y, Element(TERRAIN_BRIDGEH));	// Horizontal.
						else if (up.Simplify() == TERRAIN_BRIDGE || down.Simplify() == TERRAIN_BRIDGE)
							map->SetBackground(x, y, Element(TERRAIN_BRIDGEV));	// Vertical.
						else
							map->SetBackground(x, y, Element(TERRAIN_BRIDGEH));	// Horizontal.
					}
				}
				// END Bridges.
				
				// BEGIN Road-into-bridges.
				if (element.Simplify() == TERRAIN_ROAD)
				{
					if (previousbg.Simplify() == TERRAIN_RIVER || previousbg.Simplify() == TERRAIN_BRIDGE)
					{
						map->SetBackground(x, y, Element(TERRAIN_RIVER));
						SetElement(x, y, Element(TERRAIN_BRIDGE));
					}
				}
				// END Road-into-bridges.

				// BEGIN Pipe seams.
				if (previousbg.IsPipe())
				{
					xarray.resize(4);	yarray.resize(4);
					xarray[0] = x - 1;	yarray[0] = y;
					xarray[1] = x + 1;	yarray[1] = y;
					xarray[2] = x;		yarray[2] = y - 1;
					xarray[3] = x;		yarray[3] = y + 1;
					Element simple;
					for (i = 0; i < xarray.size(); i++)
					{
						simple = map->GetBackground(xarray[i], yarray[i]).Simplify();
						if (simple == TERRAIN_SEAM)
							if (!map->AllowPlacement(xarray[i], yarray[i], simple, true))
								SetElement(xarray[i], yarray[i], Element(TERRAIN_PIPE));
					}
				}
				// END Pipe seams.

				// BEGIN Shoals.
				{
					xarray.resize(8);	yarray.resize(8);
					xarray[0] = x - 1;	yarray[0] = y;
					xarray[1] = x - 1;	yarray[1] = y - 1;
					xarray[2] = x;		yarray[2] = y - 1;
					xarray[3] = x + 1;	yarray[3] = y - 1;
					xarray[4] = x + 1;	yarray[4] = y;
					xarray[5] = x + 1;	yarray[5] = y + 1;
					xarray[6] = x;		yarray[6] = y + 1;
					xarray[7] = x - 1;	yarray[7] = y + 1;
					Element simple;
					for (i = 0; i < xarray.size(); i++)
						{
							simple = map->GetBackground(xarray[i], yarray[i]).Simplify();
							if (simple == TERRAIN_SHOAL)
								if (!map->AllowPlacement(xarray[i], yarray[i], simple, true))
									SetElement(xarray[i], yarray[i], Element(TERRAIN_SEA));
						}
				}
				// END Shoals.

				// BEGIN Placing reefs, remove land tiles.
				if (element.Simplify() == TERRAIN_REEF)
				{
					for (i = 0; i < 3; i++)
						for (j = 0; j < 3; j++)
							if (map->GetBackground(x + i - 1, y + j - 1).IsLand())
								SetElement(x + i - 1, y + j - 1, Element(TERRAIN_SEA));
				}
				// END Placing reefs, remove land tiles.

				// BEGIN Placing land tiles, remove reefs.
				if (element.IsLand())
				{
					for (i = 0; i < 3; i++)
						for (j = 0; j < 3; j++)
							if (map->GetBackground(x + i - 1, y + j - 1).Simplify() == TERRAIN_REEF)
								SetElement(x + i - 1, y + j - 1, Element(TERRAIN_SEA));
				}
				// END Placing land tiles, remove reefs..

				// BEGIN HQs and Labs. 
				if ((element.Simplify() == BUILDING_HQ || element.Simplify() == BUILDING_LAB) && !multiHQ)
				{
					for (i = 0; i < map->GetWidth(); i++)
						for (j = 0; j < map->GetHeight(); j++)
						{
							if (i == x && j == y)
								continue;
							if (map->GetBackground(i, j).Simplify() == Element(BUILDING_HQ) || map->GetBackground(i, j).Simplify() == Element(BUILDING_LAB))
								if (map->GetBackground(i, j).GetArmy() == element.GetArmy())
									SetElement(i, j, Element(TERRAIN_PLAIN));
						}

				}
				// END HQs and Labs.

				// BEGIN Could be placing land tiles (or whatever makes Sea Arcs illegally placed), transform Sea Arcs.
				for (i = 0; i < 3; i++)
					for (j = 0; j < 3; j++)
						if (map->GetBackground(x + i - 1, y + j - 1).Simplify() == EXTRA_SEAARC)
							if (!map->AllowPlacement(x + i - 1, y + j - 1, map->GetBackground(x + i - 1, y + j - 1), true))
							{
								int xoffset, yoffset;
								map->GetBackground(x + i - 1, y + j - 1).GetLargeOffset(xoffset, yoffset);
								SetElement(x + i - xoffset, y + j - yoffset, Element(EXTRA_BLACKARC));
							}
				// END Could be placing land tiles (or whatever makes Sea Arcs illegally placed), transform Sea Arcs.

				// BEGIN Removal of large tiles.
				if (previousbg.IsExtra() && previousbg.GetSize() > 1 && previousbg != previousbg.Simplify())
				{
					int xoffset, yoffset;
					Element newelement = previousbg.GetBase();
					previousbg.GetLargeOffset(xoffset, yoffset);
					for (i = 0 - xoffset; i < previousbg.GetSize() - xoffset; i++)
						for (j = 0 - yoffset; j < previousbg.GetSize() - yoffset; j++)
							map->SetBackground(x + i, y + j, newelement);
					map->SetBackground(x, y, element);
					RefreshRect(wxRect(xdraw - (xoffset * 16), ydraw - (yoffset * 16), 16 * previousbg.GetSize(), 16 * previousbg.GetSize()));
				}
				// END Removal of large tiles.

				// BEGIN Placement of large tiles.
				if (element.IsExtra() && element.GetSize() > 1 && element == element.Simplify())
				{
					for (i = 0; i < element.GetSize(); i++)
						for (j = 0; j < element.GetSize(); j++)
							SetElement(x + i - 1, y + j - 1, Element(element.GetTopLeft() + (ELEMENT_EXTRA_COLUMNS * j) + i));
				}
				// END Placement of large tiles.

				return true;
			}
		}
	}

	if (element.IsForeground())
		if (element != previousfg)
			if (map->SetForeground(x, y, element))
			{
				RefreshRect(wxRect(xdraw, ydraw, 16, 16));
				return true;
			}

	return false;
}

bool DrawPanel::FillPoint(int x, int y, Element element, Direction direction, PointSet& tofill)
{
	Point<int> point(x, y);
	if (tofill.find(point) != tofill.end())
		return false;

	FrameMain* frameMain = (FrameMain*)m_frameMain;
	Map* map = &(frameMain->m_map);

	// OBS: Even though it checks for foreground or background here, in the MouseEvent function it will
	//      pass the background for this function no matter what.
	if (x < 0 || x > map->GetWidth() || y < 0 || y > map->GetHeight())
		return false;
	if (element.IsBackground() && map->GetBackground(x, y) != element)
		return false;
	if (element.IsForeground() && map->GetForeground(x, y) != element)
		return false;

	tofill.insert(point);

	if (direction != DIR_UP)
		FillPoint(x, y - 1, element, DIR_DOWN, tofill);
	if (direction != DIR_DOWN)
		FillPoint(x, y + 1, element, DIR_UP, tofill);
	if (direction != DIR_LEFT)
		FillPoint(x - 1, y, element, DIR_RIGHT, tofill);
	if (direction != DIR_RIGHT)
		FillPoint(x + 1, y, element, DIR_LEFT, tofill);

	return true;
}

bool DrawPanel::Select(int x, int y, int width, int height)
{
	FrameMain* frameMain = (FrameMain*)m_frameMain;

	m_selectx = x;
	m_selecty = y;
	m_selectw = width;
	m_selecth = height;

	int i, j;
	m_selectmap.SetSize(m_selectw, m_selecth);
	for (i = 0; i < m_selectw; i++)
		for (j = 0; j < m_selecth; j++)
		{
			if (frameMain->m_map.GetBackground(m_selectx + i, m_selecty + j).GetSize() == 1)
				m_selectmap.SetBackground(i, j, frameMain->m_map.GetBackground(m_selectx + i, m_selecty + j), false);
			else
			{
				int offsetx, offsety, elemsize;
				elemsize = frameMain->m_map.GetBackground(m_selectx + i, m_selecty + j).GetSize();
				frameMain->m_map.GetBackground(m_selectx + i, m_selecty + j).GetLargeOffset(offsetx, offsety);
				if (i - offsetx < 0 || i - offsetx + elemsize > m_selectw ||
					j - offsety < 0 || j - offsety + elemsize > m_selecth)
					m_selectmap.SetBackground(i, j, frameMain->m_map.GetBackground(m_selectx + i, m_selecty + j).GetBase(), false);
				else
					m_selectmap.SetBackground(i, j, frameMain->m_map.GetBackground(m_selectx + i, m_selecty + j), false);
			}
			m_selectmap.SetForeground(i, j, frameMain->m_map.GetForeground(m_selectx + i, m_selecty + j));
		}

	for (i = 0; i < m_selectw; i++)
		for (j = 0; j < m_selecth; j++)
			if (frameMain->m_map.GetBackground(m_selectx + i, m_selecty + j).GetSize() == 1)
				m_selectmap.SetBackgroundDraw(i, j, frameMain->m_map.GetBackgroundDraw(m_selectx + i, m_selecty + j));

	RefreshSelection();
	m_selectEraseOnChange = true;
	return true;
}

bool DrawPanel::EraseSelection()
{
	((FrameMain*)m_frameMain)->AddUndoPoint();
	int i, j;
	for (i = 0; i < m_selectw; i++)
		for (j = 0; j < m_selecth; j++)
		{
			SetElement(m_selectx + i, m_selecty + j, g_infoDefaultTerrain);
			SetElement(m_selectx + i, m_selecty + j, ELEMENT_UNIT_EMPTY);
		}
	m_selectEraseOnChange = false;
	return true;
}

bool DrawPanel::EraseSelectionOnChange()
{
	if (m_selectEraseOnChange)
		return EraseSelection();
	else
		return true;
}

bool DrawPanel::SetSelection()
{
	((FrameMain*)m_frameMain)->AddUndoPoint();
	bool shiftpressed = wxGetMouseState().ShiftDown();	// If shift is down, allow multiple HQs.

	// Do it twice, since some terrains may not be able to be placed in the first time.
	int i, j;
	for (i = 0; i < m_selectw; i++)
		for (j = 0; j < m_selecth; j++)
		{
			// In the first time, do some preparations so terrain dependent on the underlying terrain can be placed.

			if (m_selectmap.GetBackground(i, j).IsSea())
				SetElement(m_selectx + i, m_selecty + j, Element(TERRAIN_SEA));

			if (m_selectmap.GetBackground(i, j).Simplify() == TERRAIN_SEAM)
				SetElement(m_selectx + i, m_selecty + j, Element(TERRAIN_PIPE));

			if (m_selectmap.GetBackground(i, j).Simplify() == TERRAIN_BRIDGE)
				SetElement(m_selectx + i, m_selecty + j, Element(TERRAIN_RIVER));

			SetElement(m_selectx + i, m_selecty + j, m_selectmap.GetBackground(i, j), false, shiftpressed);
			SetElement(m_selectx + i, m_selecty + j, m_selectmap.GetForeground(i, j));
		}
	for (i = 0; i < m_selectw; i++)
		for (j = 0; j < m_selecth; j++)
		{
			SetElement(m_selectx + i, m_selecty + j, m_selectmap.GetBackground(i, j), false, shiftpressed);
			SetElement(m_selectx + i, m_selecty + j, m_selectmap.GetForeground(i, j));
		}

	((FrameMain*)m_frameMain)->m_map.UpdateDraw(m_selectx - 2, m_selecty - 2, m_selectw + 4, m_selecth + 4);
	RefreshSelection(2);
	return true;
}

bool DrawPanel::CancelSelection(bool set, bool erase)
{
	if (!m_selected)
		return false;

	if (set)
	{
		if (!m_selectEraseOnChange)	// If it's true, then it means we haven't changed the selection yet; setting it
			SetSelection();			// would be pointless and we would get an undesired AddUndoPoint.
	}
	else if (erase)
		EraseSelectionOnChange();

	m_selected = false;
	m_selectEraseOnChange = false;
	RefreshSelection(2);

	return true;
}

bool DrawPanel::RefreshSelection(int border)
{
	int refreshx, refreshy;
	refreshx = (m_selectx - border) * 16;
	refreshy = (m_selecty - border) * 16;
	CalcScrolledPosition(refreshx, refreshy, &refreshx, &refreshy);
	RefreshRect(wxRect(refreshx, refreshy, (m_selectw + border * 2) * 16, (m_selecth + border * 2) * 16));
	return true;
}

int DrawPanel::GetMode()
{
	return m_mode;
}

bool DrawPanel::SetMode(int mode)
{
	m_mode = mode;
	CancelSelection();
	if (!(((FrameMain*)m_frameMain)->o_toolbarMain->GetToolState(mode)))
		((FrameMain*)m_frameMain)->o_toolbarMain->ToggleTool(mode, true);
	return true;
}

bool DrawPanel::CutCopy(int actionId)
{
	if (!m_selected)
		return false;

	if (wxTheClipboard->Open())
	{
		wxCustomDataObject* data = new wxCustomDataObject;
		data->SetFormat(wxDataFormat(g_clipboardstring));

		int bufsize;
		char* buffer;
		int bufint;
		Element bufelem;
		int i, j;
		
		bufsize = sizeof(int) * 2 + m_selectmap.GetWidth() * m_selectmap.GetHeight() * 3 * sizeof(Element) + 10000;
		buffer = new char[bufsize];
		
		bufint = m_selectmap.GetWidth();
		memcpy(buffer, &bufint, sizeof(int));
		bufint = m_selectmap.GetHeight();
		memcpy(buffer + sizeof(int), &bufint, sizeof(int));

		for (i = 0; i < m_selectmap.GetWidth(); i++)
		{
			for (j = 0; j < m_selectmap.GetHeight(); j++)
			{
				bufelem = m_selectmap.GetBackground(i, j);
				memcpy(buffer + sizeof(int) * 2 + sizeof(Element) * ((m_selectmap.GetHeight() * i + j) * 3 + 0), &bufelem, sizeof(Element));
				bufelem = m_selectmap.GetBackgroundDraw(i, j);
				memcpy(buffer + sizeof(int) * 2 + sizeof(Element) * ((m_selectmap.GetHeight() * i + j) * 3 + 1), &bufelem, sizeof(Element));
				bufelem = m_selectmap.GetForeground(i, j);
				memcpy(buffer + sizeof(int) * 2 + sizeof(Element) * ((m_selectmap.GetHeight() * i + j) * 3 + 2), &bufelem, sizeof(Element));
			}
		}

		data->SetData(bufsize, buffer);
		delete [] buffer;
		wxTheClipboard->SetData(data);
		wxTheClipboard->Flush();
		wxTheClipboard->Close();

		if (actionId == wxID_CUT)
			CancelSelection(false, true);

		return true;
	}
	return false;
}

bool DrawPanel::Paste(int actionId)
{
	if (wxTheClipboard->Open())
	{
		wxCustomDataObject data;
		data.SetFormat(wxDataFormat(g_clipboardstring));
		if (wxTheClipboard->GetData(data))
		{
			CancelSelection();

			int bufsize;
			char* buffer;
			int bufint;
			Element bufelem;
			int i, j;
			
			bufsize = data.GetSize();
			buffer = new char[bufsize];
			memcpy(buffer, data.GetData(), bufsize);
			wxTheClipboard->Close();

			memcpy(&bufint, buffer, sizeof(int));
			m_selectw = bufint;
			memcpy(&bufint, buffer + sizeof(int), sizeof(int));
			m_selecth = bufint;
			
			SetMode(FrameMain::ID_TOOL_SELECTOR);
			m_selected = true;
			CalcUnscrolledPosition(0, 0, &i, &j);
			m_selectx = i / 16;
			m_selecty = j / 16;
			m_selectmap.SetSize(m_selectw, m_selecth);

			for (i = 0; i < m_selectmap.GetWidth(); i++)
			{
				for (j = 0; j < m_selectmap.GetHeight(); j++)
				{
					memcpy(&bufelem, buffer + sizeof(int) * 2 + sizeof(Element) * ((m_selectmap.GetHeight() * i + j) * 3 + 0), sizeof(Element));
					m_selectmap.SetBackground(i, j, bufelem, false);
					memcpy(&bufelem, buffer + sizeof(int) * 2 + sizeof(Element) * ((m_selectmap.GetHeight() * i + j) * 3 + 1), sizeof(Element));
					m_selectmap.SetBackgroundDraw(i, j, bufelem);
					memcpy(&bufelem, buffer + sizeof(int) * 2 + sizeof(Element) * ((m_selectmap.GetHeight() * i + j) * 3 + 2), sizeof(Element));
					m_selectmap.SetForeground(i, j, bufelem);

					if (actionId == FrameMain::ID_EDIT_PASTETERRAIN)
						m_selectmap.SetForeground(i, j, ELEMENT_UNIT_EMPTY);
					if (actionId == FrameMain::ID_EDIT_PASTEUNITS)
						m_selectmap.SetBackground(i, j, ELEMENT_TERRAIN_BLANK, false);
				}
			}
			RefreshSelection();
			return true;
		}
	}
	return false;
}

bool DrawPanel::SelectAll(int actionId)
{
	SetMode(FrameMain::ID_TOOL_SELECTOR);
	m_selected = true;
	return Select(0, 0, ((FrameMain*)m_frameMain)->m_map.GetWidth(), ((FrameMain*)m_frameMain)->m_map.GetHeight());
}

bool DrawPanel::Flip(int actionId)
{
	if (!m_selected)
		return false;

	EraseSelectionOnChange();
	int i, j, x ,y;
	Map map = m_selectmap;
	for (i = 0; i < m_selectw; i++)
		for (j = 0; j < m_selecth; j++)
		{
			x = i;
			y = j;
			if (actionId == FrameMain::ID_EDIT_FLIPHORIZONTALLY)
				x = m_selectw - i - 1;
			if (actionId == FrameMain::ID_EDIT_FLIPVERTICALLY)
				y = m_selecth - j - 1;
			
			if (map.GetBackground(i, j).GetSize() == 1)
				m_selectmap.SetBackground(x, y, map.GetBackground(i, j), false);
			else
			{
				int xoff, yoff, elemsize;
				map.GetBackground(i, j).GetLargeOffset(xoff, yoff);
				elemsize = map.GetBackground(i, j).GetSize();
				if (actionId == FrameMain::ID_EDIT_FLIPHORIZONTALLY)
					m_selectmap.SetBackground(x + 2 * xoff - elemsize + 1, y, map.GetBackground(i, j), false);
				if (actionId == FrameMain::ID_EDIT_FLIPVERTICALLY)
					m_selectmap.SetBackground(x, y + 2 * yoff - elemsize + 1, map.GetBackground(i, j), false);
			}
			m_selectmap.SetForeground(x, y, map.GetForeground(i, j));
		}
	RefreshSelection();
	return true;
}

bool DrawPanel::Rotate(int actionId)
{
	if (!m_selected)
		return false;

	EraseSelectionOnChange();
	m_selected = false;
	RefreshSelection(2);
	m_selected = true;

	int i, j;
	i = m_selecth;
	j = m_selectw;
	m_selectw = i;
	m_selecth = j;

	Map map = m_selectmap;
	m_selectmap.SetSize(m_selectw, m_selecth);
	for (i = 0; i < m_selectw; i++)
	{
		for (j = 0; j < m_selecth; j++)
		{
			if (map.GetBackground(j, i).GetSize() == 1)
				m_selectmap.SetBackground(i, j, map.GetBackground(j, i), false);
			else
			{
				int xoff, yoff;
				map.GetBackground(j, i).GetLargeOffset(xoff, yoff);
				m_selectmap.SetBackground(i, j, map.GetBackground(j, i).MakeFromLargeOffset(yoff, xoff), false);
			}
			m_selectmap.SetForeground(i, j, map.GetForeground(j, i));

		}
	}
	
	if (actionId == FrameMain::ID_EDIT_ROTATECLOCKWISE)
		return Flip(FrameMain::ID_EDIT_FLIPHORIZONTALLY);

	if (actionId == FrameMain::ID_EDIT_ROTATECOUNTERCLOCKWISE)
		return Flip(FrameMain::ID_EDIT_FLIPVERTICALLY);

	RefreshSelection();
	return false;
}

bool DrawPanel::DeleteUnits(int actionId)
{
	if (!m_selected)
		return false;

	EraseSelectionOnChange();
	int i, j;
	for (i = 0; i < m_selectw; i++)
		for (j = 0; j < m_selecth; j++)
			m_selectmap.SetForeground(i, j, Element(ELEMENT_UNIT_EMPTY));
	RefreshSelection();
	return true;
}
