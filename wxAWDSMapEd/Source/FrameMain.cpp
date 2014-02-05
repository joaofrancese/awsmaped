#include "precomp.h"
#include "FrameMain.h"

#include "DialogPreferences.h"
#include "DialogInformation.h"
#include "DialogSettings.h"
#include "DialogStatus.h"

#ifndef wxHIDE_READONLY
    #define wxHIDE_READONLY 0
#endif


BEGIN_EVENT_TABLE(FrameMain, wxFrame)

	// Event handling: MenuClick & ToolClick
	EVT_MENU(wxID_NEW,									FrameMain::EvMenuClick_FileNew)
	EVT_MENU(wxID_OPEN,									FrameMain::EvMenuClick_FileOpen)
	EVT_MENU(wxID_SAVE,									FrameMain::EvMenuClick_FileSave)
	EVT_MENU(wxID_SAVEAS,								FrameMain::EvMenuClick_FileSaveAs)
	EVT_MENU(ID_FILE_SCREENSHOT,						FrameMain::EvMenuClick_FileScreenshot)
	EVT_MENU(wxID_PREFERENCES,							FrameMain::EvMenuClick_FilePreferences)
	EVT_MENU(wxID_EXIT,									FrameMain::EvMenuClick_FileExit)
	EVT_MENU(ID_MAP_FILL_SEA,							FrameMain::EvMenuClick_MapFill)
	EVT_MENU(ID_MAP_FILL_PLAIN,							FrameMain::EvMenuClick_MapFill)
	EVT_MENU(ID_MAP_FILL_WOOD,							FrameMain::EvMenuClick_MapFill)
	EVT_MENU(ID_MAP_FILL_MOUNTAIN,						FrameMain::EvMenuClick_MapFill)
	EVT_MENU(ID_MAP_FILL_ROAD,							FrameMain::EvMenuClick_MapFill)
	EVT_MENU(ID_MAP_INFORMATION,						FrameMain::EvMenuClick_MapInformation)
	EVT_MENU(ID_MAP_SETTINGS,							FrameMain::EvMenuClick_MapSettings)
	EVT_MENU(ID_MAP_STATUS,								FrameMain::EvMenuClick_MapStatus)
	EVT_MENU(wxID_UNDO,									FrameMain::EvMenuClick_EditUndo)
	EVT_MENU(wxID_REDO,									FrameMain::EvMenuClick_EditRedo)
	EVT_MENU(wxID_CUT,									FrameMain::EvMenuClick_EditCutCopy)
	EVT_MENU(wxID_COPY,									FrameMain::EvMenuClick_EditCutCopy)
	EVT_MENU(wxID_PASTE,								FrameMain::EvMenuClick_EditPaste)
	EVT_MENU(ID_EDIT_PASTETERRAIN,						FrameMain::EvMenuClick_EditPaste)
	EVT_MENU(ID_EDIT_PASTEUNITS,						FrameMain::EvMenuClick_EditPaste)
	EVT_MENU(wxID_SELECTALL,							FrameMain::EvMenuClick_EditSelectAll)
	EVT_MENU(ID_EDIT_CANCELSELECTION,					FrameMain::EvMenuClick_EditCancelSelection)
	EVT_MENU(ID_EDIT_REMOVESELECTION,					FrameMain::EvMenuClick_EditCancelSelection)
	EVT_MENU(ID_EDIT_FLIPHORIZONTALLY,					FrameMain::EvMenuClick_EditFlip)
	EVT_MENU(ID_EDIT_FLIPVERTICALLY,					FrameMain::EvMenuClick_EditFlip)
	EVT_MENU(ID_EDIT_ROTATECLOCKWISE,					FrameMain::EvMenuClick_EditRotate)
	EVT_MENU(ID_EDIT_ROTATECOUNTERCLOCKWISE,			FrameMain::EvMenuClick_EditRotate)
	EVT_MENU(ID_EDIT_DELETEUNITS,						FrameMain::EvMenuClick_EditDeleteUnits)
	EVT_MENU(ID_EDIT_DELETEALLUNITS,					FrameMain::EvMenuClick_EditDeleteAllUnits)
	EVT_MENU(wxID_ABOUT,								FrameMain::EvMenuClick_HelpAbout)
	EVT_MENU(ID_TOOL_PENCIL,							FrameMain::EvMenuClick_ToolMode)
	EVT_MENU(ID_TOOL_LINE,								FrameMain::EvMenuClick_ToolMode)
	EVT_MENU(ID_TOOL_SQUARE,							FrameMain::EvMenuClick_ToolMode)
	EVT_MENU(ID_TOOL_SQUAREFILL,						FrameMain::EvMenuClick_ToolMode)
	EVT_MENU(ID_TOOL_BUCKET,							FrameMain::EvMenuClick_ToolMode)
	EVT_MENU(ID_TOOL_SELECTOR,							FrameMain::EvMenuClick_ToolMode)

	// Event handling: UpdateUI
	EVT_UPDATE_UI(wxID_UNDO,							FrameMain::EvUpdateUI_Undo)
	EVT_UPDATE_UI(wxID_REDO,							FrameMain::EvUpdateUI_Redo)
	EVT_UPDATE_UI(wxID_CUT,								FrameMain::EvUpdateUI_SelectionDependent)
	EVT_UPDATE_UI(wxID_COPY,							FrameMain::EvUpdateUI_SelectionDependent)
	EVT_UPDATE_UI(wxID_PASTE,							FrameMain::EvUpdateUI_Paste)
	EVT_UPDATE_UI(ID_EDIT_PASTETERRAIN,					FrameMain::EvUpdateUI_Paste)
	EVT_UPDATE_UI(ID_EDIT_PASTEUNITS,					FrameMain::EvUpdateUI_Paste)
	EVT_UPDATE_UI(ID_EDIT_CANCELSELECTION,				FrameMain::EvUpdateUI_SelectionDependent)
	EVT_UPDATE_UI(ID_EDIT_REMOVESELECTION,				FrameMain::EvUpdateUI_SelectionDependent)
	EVT_UPDATE_UI(ID_EDIT_DELETEUNITS,					FrameMain::EvUpdateUI_SelectionDependent)
	EVT_UPDATE_UI(ID_EDIT_FLIPHORIZONTALLY,				FrameMain::EvUpdateUI_SelectionDependent)
	EVT_UPDATE_UI(ID_EDIT_FLIPVERTICALLY,				FrameMain::EvUpdateUI_SelectionDependent)
	EVT_UPDATE_UI(ID_EDIT_ROTATECLOCKWISE,				FrameMain::EvUpdateUI_SelectionDependent)
	EVT_UPDATE_UI(ID_EDIT_ROTATECOUNTERCLOCKWISE,		FrameMain::EvUpdateUI_SelectionDependent)

	// Event handling: Others
	EVT_CLOSE(								FrameMain::EvClose)
	EVT_TOOL_ENTER(ID_TOOLBAR_MAIN,			FrameMain::EvToolbarEnter)
#ifndef __WXGTK__
	EVT_TIMER(ID_TIMER_MEDIA,				FrameMain::EvTimer_Media)
	EVT_TIMER(ID_TIMER_MEDIALOADED,			FrameMain::EvTimer_MediaLoaded)
	EVT_MEDIA_LOADED(ID_MEDIA_MAIN,			FrameMain::EvMedia_Loaded)
	EVT_MEDIA_FINISHED(ID_MEDIA_MAIN,		FrameMain::EvMedia_Play)
#endif

END_EVENT_TABLE()


#if !defined(__WXMSW__)
	#include "../Resource/wxAWDSMapEd-16.xpm"
	#include "../Resource/wxAWDSMapEd-32.xpm"
	#include "../Resource/wxAWDSMapEd-48.xpm"
#endif

#include "../Resource/toolbar/new.xpm"
#include "../Resource/toolbar/open.xpm"
#include "../Resource/toolbar/save.xpm"
#include "../Resource/toolbar/cut.xpm"
#include "../Resource/toolbar/copy.xpm"
#include "../Resource/toolbar/paste.xpm"
#include "../Resource/toolbar/undo.xpm"
#include "../Resource/toolbar/redo.xpm"
#include "../Resource/toolbar/pencil.xpm"
#include "../Resource/toolbar/line.xpm"
#include "../Resource/toolbar/square.xpm"
#include "../Resource/toolbar/squarefill.xpm"
#include "../Resource/toolbar/bucket.xpm"
#include "../Resource/toolbar/selector.xpm"


FrameMain::FrameMain(wxWindow* parent, int id, const wxPoint& pos)
	: wxFrame(parent, id, "", pos, wxDefaultSize, wxCAPTION | wxMINIMIZE_BOX | wxCLOSE_BOX | wxSYSTEM_MENU)
{
	o_menubarMain = new wxMenuBar();
		o_menuFile = new wxMenu(0);
		o_menubarMain->Append(o_menuFile, "&File");
			o_menuitemFileNew = o_menuFile->Append(wxID_NEW, "&New\tCtrl+N", "Create a new map.");
			o_menuFile->Append(wxID_SEPARATOR, "");
			o_menuitemFileOpen = o_menuFile->Append(wxID_OPEN, "&Open...\tCtrl+O", "Open a saved map.");
			o_menuitemFileSave = o_menuFile->Append(wxID_SAVE, "&Save\tCtrl+S", "Save the current map.");
			o_menuitemFileSaveAs = o_menuFile->Append(wxID_SAVEAS, "Save &As...", "Save the current map with a new file name.");
			o_menuitemFileScreenshot = o_menuFile->Append(ID_FILE_SCREENSHOT, "S&creenshot\tF12", "Save a screenshot of the current map.");
			o_menuFile->Append(wxID_SEPARATOR, "");
			o_menuitemFilePreferences = o_menuFile->Append(wxID_PREFERENCES, "&Preferences...", "Choose the editor preferences such as background music volume and default map size.");
			o_menuFile->Append(wxID_SEPARATOR, "");
			o_menuitemFileExit = o_menuFile->Append(wxID_EXIT, "E&xit\tAlt+F4", "Close the map editor.");
		o_menuMap = new wxMenu(0);
		o_menubarMain->Append(o_menuMap, "&Map");
			o_menuMapFill = new wxMenu(0);
				o_menuitemMapFillSea = o_menuMapFill->Append(ID_MAP_FILL_SEA, "&Sea", "Fill the whole map with sea tiles.");
				o_menuitemMapFillPlain = o_menuMapFill->Append(ID_MAP_FILL_PLAIN, "&Plains", "Fill the whole map with plain tiles.");
				o_menuitemMapFillWood = o_menuMapFill->Append(ID_MAP_FILL_WOOD, "&Woods", "Fill the whole map with wood tiles.");
				o_menuitemMapFillMountain = o_menuMapFill->Append(ID_MAP_FILL_MOUNTAIN, "&Mountains", "Fill the whole map with mountain tiles.");
				o_menuitemMapFillRoad = o_menuMapFill->Append(ID_MAP_FILL_ROAD, "&Roads", "Fill the whole map with road tiles.");
			o_menuitemMapFill = o_menuMap->Append(ID_MAP_FILL, "&Fill", o_menuMapFill);
			o_menuMap->Append(wxID_SEPARATOR, "");
			o_menuitemMapInformation = o_menuMap->Append(ID_MAP_INFORMATION, "&Information...\tCtrl+I", "View and edit map information, such as name and description.");
			o_menuitemMapSettings = o_menuMap->Append(ID_MAP_SETTINGS, "&Settings...\tF10", "View and edit map settings, such as tileset and size.");
			o_menuMap->Append(wxID_SEPARATOR, "");
			o_menuitemMapStatus = o_menuMap->Append(ID_MAP_STATUS, "S&tatus...\tF8", "View the map status, such as number of buildings and units.");
		o_menuEdit = new wxMenu(0);
		o_menubarMain->Append(o_menuEdit, "&Edit");
			o_menuitemEditUndo = o_menuEdit->Append(wxID_UNDO, "&Undo\tCtrl+Z", "Undo the latest action.");
			o_menuitemEditRedo = o_menuEdit->Append(wxID_REDO, "&Redo\tCtrl+Y", "Redo the latest undone action.");
			o_menuEdit->Append(wxID_SEPARATOR, "");
			o_menuitemEditCut = o_menuEdit->Append(wxID_CUT, "&Cu&t\tCtrl+X", "Cut the selected map area to the clipboard. The empty area will be filled with the currently selected tile.");
			o_menuitemEditCopy = o_menuEdit->Append(wxID_COPY, "&Copy\tCtrl+C", "Copy the selected map area to the clipboard.");
			o_menuitemEditPaste = o_menuEdit->Append(wxID_PASTE, "&Paste\tCtrl+V", "Paste the map area from the clipboard to the current map.");
			o_menuitemEditPasteTerrain = o_menuEdit->Append(ID_EDIT_PASTETERRAIN, "Paste T&errain", "Paste only the terrain from the clipboard to the current map.");
			o_menuitemEditPasteUnits = o_menuEdit->Append(ID_EDIT_PASTEUNITS, "Paste Un&its", "Paste only the units from the clipboard to the current map.");
			o_menuEdit->Append(wxID_SEPARATOR, "");
			o_menuitemEditSelectAll = o_menuEdit->Append(wxID_SELECTALL, "Select &All\tCtrl+A", "Select the entire map.");
			o_menuitemEditCancelSelection = o_menuEdit->Append(ID_EDIT_CANCELSELECTION, "Cancel &Selection\tEsc", "Cancel the current selection.");
			o_menuitemEditRemoveSelection = o_menuEdit->Append(ID_EDIT_REMOVESELECTION, "Re&move Selection\tDelete", "Remove the current selection.");
			o_menuEdit->Append(wxID_SEPARATOR, "");
			o_menuitemEditFlipHorizontally = o_menuEdit->Append(ID_EDIT_FLIPHORIZONTALLY, "Flip &Horizontally", "Flip the selected area horizontally.");
			o_menuitemEditFlipVertically = o_menuEdit->Append(ID_EDIT_FLIPVERTICALLY, "Flip &Vertically", "Flip the selected area vertically.");
			o_menuitemEditRotateClockwise = o_menuEdit->Append(ID_EDIT_ROTATECLOCKWISE, "R&otate 90. Clockwise", "Rotate the selected area 90 degrees clockwise.");
			o_menuitemEditRotateCounterclockwise = o_menuEdit->Append(ID_EDIT_ROTATECOUNTERCLOCKWISE, "Rotate 90. Cou&nter-clockwise", "Rotate the selected area 90 degrees counter-clockwise.");
			o_menuEdit->Append(wxID_SEPARATOR, "");
			o_menuitemEditDeleteUnits = o_menuEdit->Append(ID_EDIT_DELETEUNITS, "&Delete Units", "Delete all units from the selected map area.");
			o_menuitemEditDeleteAllUnits = o_menuEdit->Append(ID_EDIT_DELETEALLUNITS, "De&lete All Units", "Delete all units from the map.");
		o_menuHelp = new wxMenu(0);
		o_menubarMain->Append(o_menuHelp, "&Help");
			o_menuitemHelpAbout = o_menuHelp->Append(wxID_ABOUT, "&About...\tF1", "Show information about the map editor.");
	SetMenuBar(o_menubarMain);

	o_toolbarMain = new wxToolBar(this, ID_TOOLBAR_MAIN);
		o_toolNew = o_toolbarMain->AddTool(wxID_NEW, "New", wxBitmap(xpmNew), wxNullBitmap, wxITEM_NORMAL, "New", "Create a new map.");
		o_toolOpen = o_toolbarMain->AddTool(wxID_OPEN, "Open...", wxBitmap(xpmOpen), wxNullBitmap, wxITEM_NORMAL, "Open...", "Open a saved map.");
		o_toolSave = o_toolbarMain->AddTool(wxID_SAVE, "Save", wxBitmap(xpmSave), wxNullBitmap, wxITEM_NORMAL, "Save", "Save the current map.");
		o_toolbarMain->AddSeparator();
		o_toolCut = o_toolbarMain->AddTool(wxID_CUT, "Cut", wxBitmap(xpmCut), wxNullBitmap, wxITEM_NORMAL, "Cut", "Cut the selected map area to the clipboard. The empty area will be filled with the currently selected tile.");
		o_toolCopy = o_toolbarMain->AddTool(wxID_COPY, "Copy", wxBitmap(xpmCopy), wxNullBitmap, wxITEM_NORMAL, "Copy", "Copy the selected map area to the clipboard.");
		o_toolPaste = o_toolbarMain->AddTool(wxID_PASTE, "Paste", wxBitmap(xpmPaste), wxNullBitmap, wxITEM_NORMAL, "Paste", "Paste the map area from the clipboard to the current map.");
		o_toolbarMain->AddSeparator();
		o_toolUndo = o_toolbarMain->AddTool(wxID_UNDO, "Undo", wxBitmap(xpmUndo), wxNullBitmap, wxITEM_NORMAL, "Undo", "Undo the latest action.");
		o_toolRedo = o_toolbarMain->AddTool(wxID_REDO, "Redo", wxBitmap(xpmRedo), wxNullBitmap, wxITEM_NORMAL, "Redo", "Redo the latest undone action.");
		o_toolbarMain->AddSeparator();
		o_toolPencil = o_toolbarMain->AddTool(ID_TOOL_PENCIL, "Pencil", wxBitmap(xpmPencil), wxNullBitmap, wxITEM_RADIO, "Pencil", "Allows you to draw tiles individually while holding down the mouse button.");
		o_toolLine = o_toolbarMain->AddTool(ID_TOOL_LINE, "Line", wxBitmap(xpmLine), wxNullBitmap, wxITEM_RADIO, "Line", "Allows you to draw lines.");
		o_toolSquare = o_toolbarMain->AddTool(ID_TOOL_SQUARE, "Square", wxBitmap(xpmSquare), wxNullBitmap, wxITEM_RADIO, "Square", "Allows you to draw square and rectangle outlines.");
		o_toolSquarefill = o_toolbarMain->AddTool(ID_TOOL_SQUAREFILL, "Filled Square", wxBitmap(xpmSquarefill), wxNullBitmap, wxITEM_RADIO, "Filled Square", "Allows you to draw filled squares and rectangles.");
		o_toolBucket = o_toolbarMain->AddTool(ID_TOOL_BUCKET, "Paint Bucket", wxBitmap(xpmBucket), wxNullBitmap, wxITEM_RADIO, "Paint Bucket", "Allows you to change a mass of tiles instantly.");
		o_toolSelector = o_toolbarMain->AddTool(ID_TOOL_SELECTOR, "Selection Tool", wxBitmap(xpmSelector), wxNullBitmap, wxITEM_RADIO, "Selection Tool", "Allows you to select a part of the map to cut, copy and move.");
	o_toolbarMain->Realize();
	SetToolBar(o_toolbarMain);

	o_statusMain = new wxStatusBar(this, ID_STATUSBAR_MAIN, 0);
		o_statusMain->SetFieldsCount(2);
		int* statuswidths = new int[2];
			statuswidths[0] = -1;
			statuswidths[1] = PLATSPEC(80, 90, 80);
			o_statusMain->SetStatusWidths(2, statuswidths);
		SetStatusBar(o_statusMain);
		SetStatusBarPane(0);
		UpdateStatusName();
		UpdateMouseCoordinates();




	o_panelBackground = new wxPanel(this, wxID_ANY);

	o_panelDraw = new DrawPanel(o_panelBackground, this, wxID_ANY, wxPoint(4, 0));

	o_notebookMain = new wxNotebook(o_panelBackground, ID_NOTEBOOK_MAIN);
		o_notepageTerrain = new Page(o_notebookMain, this, ID_NOTEPAGE_TERRAIN, wxPoint(0, 0), wxSize(PAGE_CALCULATED_WIDTH + 10, PAGE_CALCULATED_HEIGHT + 28));
		o_notepageUnit = new Page(o_notebookMain, this, ID_NOTEPAGE_UNIT);
		o_notepageExtra = new Page(o_notebookMain, this, ID_NOTEPAGE_EXTRA);
		o_notebookMain->AddPage(o_notepageTerrain, "Terrain");
		o_notebookMain->AddPage(o_notepageUnit, "Unit");
		o_notebookMain->AddPage(o_notepageExtra, "Extra");
		o_notebookMain->SetSize(wxSize(o_notepageTerrain->GetSize().GetWidth(), o_notepageTerrain->GetSize().GetHeight()));
        #if defined(__WXGTK__)
            o_notebookMain->SetSize(wxSize(o_notebookMain->GetSize().GetWidth(), o_notebookMain->GetSize().GetHeight() + 10));;
        #endif
		FillPages();

#ifndef __WXGTK__
	o_timerMediaLoaded = new wxTimer(this, ID_TIMER_MEDIALOADED);
	o_timerMedia = new wxTimer(this, ID_TIMER_MEDIA);
		o_timerMedia->Start(200, wxTIMER_ONE_SHOT);
#endif


	wxIconBundle appicons;
	#if defined(__WXMSW__)
		appicons.AddIcon(wxIcon("icon_01_main", wxBITMAP_TYPE_ICO_RESOURCE, 16, 16));
		appicons.AddIcon(wxIcon("icon_01_main", wxBITMAP_TYPE_ICO_RESOURCE, 32, 32));
		appicons.AddIcon(wxIcon("icon_01_main", wxBITMAP_TYPE_ICO_RESOURCE, 48, 48));
	#else
		appicons.AddIcon(wxIcon(wxAWDSMapEd_16_xpm));
		appicons.AddIcon(wxIcon(wxAWDSMapEd_32_xpm));
		appicons.AddIcon(wxIcon(wxAWDSMapEd_48_xpm));
	#endif
	SetIcons(appicons);

	DoNewReset();
	UpdateFrameSize();
	SetTitle(g_messageboxTitle);// + " - Alpha v" + g_version);
}



//////////////////////////////////////////////////////////
//                                                      //
//  EVENT HANDLING:  MenuClick & ToolClick              //
//                                                      //
//////////////////////////////////////////////////////////

void FrameMain::EvMenuClick_FileNew(wxCommandEvent& event)
{
	DoNew();
}

void FrameMain::EvMenuClick_FileOpen(wxCommandEvent& event)
{
	DoOpen();
}

void FrameMain::EvMenuClick_FileSave(wxCommandEvent& event)
{
	DoSave();
}

void FrameMain::EvMenuClick_FileSaveAs(wxCommandEvent& event)
{
	DoSaveAs();
}

void FrameMain::EvMenuClick_FileScreenshot(wxCommandEvent& event)
{
	DoScreenshot();
}

void FrameMain::EvMenuClick_FilePreferences(wxCommandEvent& event)
{
	DialogPreferences* dialog = new DialogPreferences(this);
	if (dialog->ShowModal() == wxID_OK)
	{
        #ifndef __WXGTK__
            if (wxFileExists(BGM_FILENAME))
            {
                if (g_infoVolumeEnable && o_mediaMain->GetState() != wxMEDIASTATE_PLAYING)
                    o_mediaMain->Play();
                if (!g_infoVolumeEnable && o_mediaMain->GetState() != wxMEDIASTATE_STOPPED)
                    o_mediaMain->Stop();
                o_mediaMain->SetVolume(((float)g_infoVolume) / 100);
            }
        #endif
		m_map.UpdateDraw();
		Refresh();
	}

}

void FrameMain::EvMenuClick_FileExit(wxCommandEvent& event)
{
	Close();
}

void FrameMain::EvMenuClick_MapFill(wxCommandEvent& event)
{
	AddUndoPoint();
	Element element;
	switch (event.GetId())
	{
	case ID_MAP_FILL_PLAIN:
		element = Element(TERRAIN_PLAIN);
		break;
	case ID_MAP_FILL_WOOD:
		element = Element(TERRAIN_WOOD);
		break;
	case ID_MAP_FILL_MOUNTAIN:
		element = Element(TERRAIN_MOUNTAIN);
		break;
	case ID_MAP_FILL_ROAD:
		element = Element(TERRAIN_ROAD);
		break;
	case ID_MAP_FILL_SEA:
	default:
		element = Element(TERRAIN_SEA);
		break;
	}
	if (m_map.Fill(element))
		o_panelDraw->Refresh();
}

void FrameMain::EvMenuClick_MapInformation(wxCommandEvent& event)
{
	Map map(m_map);
	DialogInformation* dialog = new DialogInformation(this, &map);
	if (dialog->ShowModal() == wxID_OK)
	{
		AddUndoPoint();
		m_map = map;
		UpdateStatusName();
	}
}

void FrameMain::EvMenuClick_MapSettings(wxCommandEvent& event)
{
	int x, y;
	o_panelDraw->GetViewStart(&x, &y);

	Map map(m_map);
	DialogSettings* dialog = new DialogSettings(this, &map);
	if (dialog->ShowModal() == wxID_OK)
	{
		AddUndoPoint();
		m_map = map;
		UpdateFrameSize();
		Refresh();
		o_panelDraw->Scroll(x, y);
	}
}

void FrameMain::EvMenuClick_MapStatus(wxCommandEvent& event)
{
	Map map(m_map);
	DialogStatus* dialog = new DialogStatus(this, &map);
	dialog->ShowModal();
}

void FrameMain::EvMenuClick_EditUndo(wxCommandEvent& event)
{
	int x, y;
	o_panelDraw->GetViewStart(&x, &y);

	m_redo.push_back(m_map);
	m_map = m_undo[m_undo.size() - 1];
	m_undo.pop_back();

	o_toolbarMain->UpdateWindowUI();
	o_panelDraw->CancelSelection(false);
	UpdateFrameSize();
	Refresh();
	o_panelDraw->Scroll(x, y);
}

void FrameMain::EvMenuClick_EditRedo(wxCommandEvent& event)
{
	int x, y;
	o_panelDraw->GetViewStart(&x, &y);

	m_undo.push_back(m_map);
	m_map = m_redo[m_redo.size() - 1];
	m_redo.pop_back();

	o_toolbarMain->UpdateWindowUI();
	o_panelDraw->CancelSelection(false);
	UpdateFrameSize();
	Refresh();
	o_panelDraw->Scroll(x, y);
}

void FrameMain::EvMenuClick_EditCutCopy(wxCommandEvent& event)
{
	o_panelDraw->CutCopy(event.GetId());
}

void FrameMain::EvMenuClick_EditPaste(wxCommandEvent& event)
{
	o_panelDraw->Paste(event.GetId());
}

void FrameMain::EvMenuClick_EditSelectAll(wxCommandEvent& event)
{
	o_panelDraw->SelectAll(event.GetId());
}

void FrameMain::EvMenuClick_EditCancelSelection(wxCommandEvent& event)
{
	// If the comparision result is False, then it's Remove Selection, and the selected area should not be set in the map, and it
	o_panelDraw->CancelSelection(event.GetId() == ID_EDIT_CANCELSELECTION, true);	// should be deleted if it was from the map.
}

void FrameMain::EvMenuClick_EditFlip(wxCommandEvent& event)
{
	o_panelDraw->Flip(event.GetId());
}

void FrameMain::EvMenuClick_EditRotate(wxCommandEvent& event)
{
	o_panelDraw->Rotate(event.GetId());
}

void FrameMain::EvMenuClick_EditDeleteUnits(wxCommandEvent& event)
{
	o_panelDraw->DeleteUnits(event.GetId());
}

void FrameMain::EvMenuClick_EditDeleteAllUnits(wxCommandEvent& event)
{
	AddUndoPoint();
	int i, j;
	for (i = 0; i < m_map.GetWidth(); i++)
		for (j = 0; j < m_map.GetHeight(); j++)
			m_map.SetForeground(i, j, Element(ELEMENT_UNIT_EMPTY));
	Refresh();
}


void FrameMain::EvMenuClick_HelpAbout(wxCommandEvent& event)
{
	wxAboutDialogInfo info;
	info.SetCopyright("Copyright (c) 2007 Joao Pedro S. Francese (Roma_emu)");
	info.SetDescription(wxString("") + "The Advance Wars Series Map Editor is a multi-platform program" + PLATSPEC("\n", " ", "\n") +
						"that allows you to create and share custom maps for the Advance Wars series" + PLATSPEC("\n", " ", "\n") +
						"of games in any computer easily and quickly. See the ReadMe file for details." +
						"\n\nCheck for updates at the editor website." +
						"\nFeel free to send comments or questions to joaofrancese@gmail.com.");
	info.SetName("Advance Wars Series Map Editor");
	info.SetVersion(g_version);
	info.SetWebSite("http://mapeditor.hopto.org");
	wxAboutBox(info);
	//wxMessageBox(g_messageboxTitle + "\nVersion " + g_version + ".\n\nBy Joao Pedro S. Francese (Roma_emu)\njoaofrancese@gmail.com or roma.emu@gmail.com\n\nGet the latest alpha version at http://mapeditor.hopto.org.", g_messageboxTitle, wxICON_INFORMATION);
}

void FrameMain::EvMenuClick_ToolMode(wxCommandEvent& event)
{
	o_panelDraw->SetMode(event.GetId());
}



//////////////////////////////////////////////////////////
//                                                      //
//  EVENT HANDLING:  UpdateUI                           //
//                                                      //
//////////////////////////////////////////////////////////

void FrameMain::EvUpdateUI_Undo(wxUpdateUIEvent& event)
{
	event.Enable(!m_undo.empty());
}

void FrameMain::EvUpdateUI_Redo(wxUpdateUIEvent& event)
{
	event.Enable(!m_redo.empty());
}

void FrameMain::EvUpdateUI_SelectionDependent(wxUpdateUIEvent& event)
{
	event.Enable(o_panelDraw->m_selected);
}

void FrameMain::EvUpdateUI_Paste(wxUpdateUIEvent& event)
{
	if (wxTheClipboard->Open())
	{
		event.Enable(wxTheClipboard->IsSupported(wxDataFormat(g_clipboardstring)));
		wxTheClipboard->Close();
	}
	else
		event.Enable(false);
}



//////////////////////////////////////////////////////////
//                                                      //
//  EVENT HANDLING:  Others                             //
//                                                      //
//////////////////////////////////////////////////////////

void FrameMain::EvClose(wxCloseEvent& event)
{
	if (!event.CanVeto())
		Destroy();
	else
	{
		if (CheckSave())
			Destroy();
		else
			event.Veto();
	}
}

void FrameMain::EvToolbarEnter(wxCommandEvent& event)
{
	if (event.GetSelection() == -1)
		UpdateStatusName();
}


#ifndef __WXGTK__
void FrameMain::EvTimer_Media(wxTimerEvent& event)
{
	if (wxFileExists(BGM_FILENAME))
	{
		o_mediaMain = new wxMediaCtrl(o_panelBackground, ID_MEDIA_MAIN, "", wxPoint(0, 0), wxSize(0, 0));
		o_mediaMain->Show(false);
		o_mediaMain->Load(BGM_FILENAME);
		o_mediaMain->SetVolume(((float)g_infoVolume) / 100);
		o_timerMediaLoaded->Start(1000, wxTIMER_ONE_SHOT);
	}
}

void FrameMain::EvTimer_MediaLoaded(wxTimerEvent& event)
{
	wxMediaEvent medev;
	EvMedia_Play(medev);
}

void FrameMain::EvMedia_Loaded(wxMediaEvent& event)
{
	o_timerMediaLoaded->Start(100, wxTIMER_ONE_SHOT);
}

void FrameMain::EvMedia_Play(wxMediaEvent& event)
{
	if (g_infoVolumeEnable)
		o_mediaMain->Play();
}
#endif

//////////////////////////////////////////////////////////
//                                                      //
//  OTHER MISC FUNCTIONS.                               //
//                                                      //
//////////////////////////////////////////////////////////

bool FrameMain::FillPages()
{
	o_notepageTerrain->SetElement(0, 0, Background(TERRAIN_PLAIN));
	o_notepageTerrain->SetElement(1, 0, Background(TERRAIN_PLAIND));
	o_notepageTerrain->SetElement(2, 0, Background(TERRAIN_WOOD));
	o_notepageTerrain->SetElement(3, 0, Background(TERRAIN_MOUNTAIN));
	o_notepageTerrain->SetElement(4, 0, Background(TERRAIN_ROAD));
	o_notepageTerrain->SetElement(5, 0, Background(TERRAIN_BRIDGE));
	o_notepageTerrain->SetElement(0, 1, Background(TERRAIN_SEA));
	o_notepageTerrain->SetElement(1, 1, Background(TERRAIN_REEF));
	o_notepageTerrain->SetElement(2, 1, Background(TERRAIN_SHOAL));
	o_notepageTerrain->SetElement(3, 1, Background(TERRAIN_RIVER));
	o_notepageTerrain->SetElement(4, 1, Background(TERRAIN_PIPE));
	o_notepageTerrain->SetElement(5, 1, Background(TERRAIN_SEAM));

	o_notepageTerrain->SetElement(0, 3, Background(ELEMENT_BUILDING_COLUMNS * 0 + BUILDING_HQ));
	o_notepageTerrain->SetElement(1, 3, Background(ELEMENT_BUILDING_COLUMNS * 0 + BUILDING_CITY));
	o_notepageTerrain->SetElement(2, 3, Background(ELEMENT_BUILDING_COLUMNS * 0 + BUILDING_BASE));
	o_notepageTerrain->SetElement(3, 3, Background(ELEMENT_BUILDING_COLUMNS * 0 + BUILDING_AIRPORT));
	o_notepageTerrain->SetElement(4, 3, Background(ELEMENT_BUILDING_COLUMNS * 0 + BUILDING_PORT));
	o_notepageTerrain->SetElement(5, 3, Background(ELEMENT_BUILDING_COLUMNS * 0 + BUILDING_TOWER));
	o_notepageTerrain->SetElement(6, 3, Background(ELEMENT_BUILDING_COLUMNS * 0 + BUILDING_LAB));
	o_notepageTerrain->SetElement(0, 4, Background(ELEMENT_BUILDING_COLUMNS * 1 + BUILDING_HQ));
	o_notepageTerrain->SetElement(1, 4, Background(ELEMENT_BUILDING_COLUMNS * 1 + BUILDING_CITY));
	o_notepageTerrain->SetElement(2, 4, Background(ELEMENT_BUILDING_COLUMNS * 1 + BUILDING_BASE));
	o_notepageTerrain->SetElement(3, 4, Background(ELEMENT_BUILDING_COLUMNS * 1 + BUILDING_AIRPORT));
	o_notepageTerrain->SetElement(4, 4, Background(ELEMENT_BUILDING_COLUMNS * 1 + BUILDING_PORT));
	o_notepageTerrain->SetElement(5, 4, Background(ELEMENT_BUILDING_COLUMNS * 1 + BUILDING_TOWER));
	o_notepageTerrain->SetElement(6, 4, Background(ELEMENT_BUILDING_COLUMNS * 1 + BUILDING_LAB));
	o_notepageTerrain->SetElement(0, 5, Background(ELEMENT_BUILDING_COLUMNS * 2 + BUILDING_HQ));
	o_notepageTerrain->SetElement(1, 5, Background(ELEMENT_BUILDING_COLUMNS * 2 + BUILDING_CITY));
	o_notepageTerrain->SetElement(2, 5, Background(ELEMENT_BUILDING_COLUMNS * 2 + BUILDING_BASE));
	o_notepageTerrain->SetElement(3, 5, Background(ELEMENT_BUILDING_COLUMNS * 2 + BUILDING_AIRPORT));
	o_notepageTerrain->SetElement(4, 5, Background(ELEMENT_BUILDING_COLUMNS * 2 + BUILDING_PORT));
	o_notepageTerrain->SetElement(5, 5, Background(ELEMENT_BUILDING_COLUMNS * 2 + BUILDING_TOWER));
	o_notepageTerrain->SetElement(6, 5, Background(ELEMENT_BUILDING_COLUMNS * 2 + BUILDING_LAB));
	o_notepageTerrain->SetElement(0, 6, Background(ELEMENT_BUILDING_COLUMNS * 3 + BUILDING_HQ));
	o_notepageTerrain->SetElement(1, 6, Background(ELEMENT_BUILDING_COLUMNS * 3 + BUILDING_CITY));
	o_notepageTerrain->SetElement(2, 6, Background(ELEMENT_BUILDING_COLUMNS * 3 + BUILDING_BASE));
	o_notepageTerrain->SetElement(3, 6, Background(ELEMENT_BUILDING_COLUMNS * 3 + BUILDING_AIRPORT));
	o_notepageTerrain->SetElement(4, 6, Background(ELEMENT_BUILDING_COLUMNS * 3 + BUILDING_PORT));
	o_notepageTerrain->SetElement(5, 6, Background(ELEMENT_BUILDING_COLUMNS * 3 + BUILDING_TOWER));
	o_notepageTerrain->SetElement(6, 6, Background(ELEMENT_BUILDING_COLUMNS * 3 + BUILDING_LAB));
	o_notepageTerrain->SetElement(0, 7, Background(ELEMENT_BUILDING_COLUMNS * 4 + BUILDING_HQ));
	o_notepageTerrain->SetElement(1, 7, Background(ELEMENT_BUILDING_COLUMNS * 4 + BUILDING_CITY));
	o_notepageTerrain->SetElement(2, 7, Background(ELEMENT_BUILDING_COLUMNS * 4 + BUILDING_BASE));
	o_notepageTerrain->SetElement(3, 7, Background(ELEMENT_BUILDING_COLUMNS * 4 + BUILDING_AIRPORT));
	o_notepageTerrain->SetElement(4, 7, Background(ELEMENT_BUILDING_COLUMNS * 4 + BUILDING_PORT));
	o_notepageTerrain->SetElement(5, 7, Background(ELEMENT_BUILDING_COLUMNS * 4 + BUILDING_TOWER));
	o_notepageTerrain->SetElement(6, 7, Background(ELEMENT_BUILDING_COLUMNS * 4 + BUILDING_LAB));
	o_notepageTerrain->SetElement(0, 8, Background(BUILDING_SILO));
	o_notepageTerrain->SetElement(1, 8, Background(ELEMENT_BUILDING_COLUMNS * 5 + BUILDING_CITY));
	o_notepageTerrain->SetElement(2, 8, Background(ELEMENT_BUILDING_COLUMNS * 5 + BUILDING_BASE));
	o_notepageTerrain->SetElement(3, 8, Background(ELEMENT_BUILDING_COLUMNS * 5 + BUILDING_AIRPORT));
	o_notepageTerrain->SetElement(4, 8, Background(ELEMENT_BUILDING_COLUMNS * 5 + BUILDING_PORT));
	o_notepageTerrain->SetElement(5, 8, Background(ELEMENT_BUILDING_COLUMNS * 5 + BUILDING_TOWER));
	o_notepageTerrain->SetElement(6, 8, Background(ELEMENT_BUILDING_COLUMNS * 5 + BUILDING_LAB));

	o_notepageUnit->SetElement(4, 2, Foreground(ELEMENT_UNIT_DELETE));
	o_notepageUnit->SetElement(0, 0, Background(ELEMENT_BUILDING_COLUMNS * 0 + BUILDING_CITY));
	o_notepageUnit->SetElement(1, 0, Background(ELEMENT_BUILDING_COLUMNS * 1 + BUILDING_CITY));
	o_notepageUnit->SetElement(2, 0, Background(ELEMENT_BUILDING_COLUMNS * 2 + BUILDING_CITY));
	o_notepageUnit->SetElement(3, 0, Background(ELEMENT_BUILDING_COLUMNS * 3 + BUILDING_CITY));
	o_notepageUnit->SetElement(4, 0, Background(ELEMENT_BUILDING_COLUMNS * 4 + BUILDING_CITY));

	o_notepageUnit->SetElement(0, 2, Foreground(UNIT_INFANTRY));
	o_notepageUnit->SetElement(1, 2, Foreground(UNIT_MECH));
	o_notepageUnit->SetElement(2, 2, Foreground(UNIT_APC));
	o_notepageUnit->SetElement(3, 2, Foreground(UNIT_OOZIUM));
	o_notepageUnit->SetElement(0, 3, Foreground(UNIT_RECON));
	o_notepageUnit->SetElement(1, 3, Foreground(UNIT_TANK));
	o_notepageUnit->SetElement(2, 3, Foreground(UNIT_MDTANK));
	o_notepageUnit->SetElement(3, 3, Foreground(UNIT_NEOTANK));
	o_notepageUnit->SetElement(4, 3, Foreground(UNIT_MEGATANK));
	o_notepageUnit->SetElement(0, 4, Foreground(UNIT_ARTILLERY));
	o_notepageUnit->SetElement(1, 4, Foreground(UNIT_ROCKET));
	o_notepageUnit->SetElement(2, 4, Foreground(UNIT_PIPERUNNER));
	o_notepageUnit->SetElement(3, 4, Foreground(UNIT_MISSILE));
	o_notepageUnit->SetElement(4, 4, Foreground(UNIT_ANTIAIR));
	o_notepageUnit->SetElement(0, 5, Foreground(UNIT_TCOPTER));
	o_notepageUnit->SetElement(1, 5, Foreground(UNIT_BCOPTER));
	o_notepageUnit->SetElement(2, 5, Foreground(UNIT_FIGHTER));
	o_notepageUnit->SetElement(3, 5, Foreground(UNIT_BOMBER));
	o_notepageUnit->SetElement(4, 5, Foreground(UNIT_STEALTH));
	o_notepageUnit->SetElement(5, 5, Foreground(UNIT_BLACKBOMB));
	o_notepageUnit->SetElement(0, 6, Foreground(UNIT_BLACKBOAT));
	o_notepageUnit->SetElement(1, 6, Foreground(UNIT_LANDER));
	o_notepageUnit->SetElement(2, 6, Foreground(UNIT_CRUISER));
	o_notepageUnit->SetElement(3, 6, Foreground(UNIT_SUB));
	o_notepageUnit->SetElement(4, 6, Foreground(UNIT_BATTLESHIP));
	o_notepageUnit->SetElement(5, 6, Foreground(UNIT_CARRIER));

	o_notepageExtra->SetElement(0, 0, Background(EXTRA_MCANNONW));
	o_notepageExtra->SetElement(1, 0, Background(EXTRA_MCANNONN));
	o_notepageExtra->SetElement(2, 0, Background(EXTRA_MCANNONE));
	o_notepageExtra->SetElement(3, 0, Background(EXTRA_MCANNONS));
	o_notepageExtra->SetElement(4, 0, Background(EXTRA_LCANNON));
	o_notepageExtra->SetElement(0, 1, Background(EXTRA_BCANNONN));
	o_notepageExtra->SetElement(1, 1, Background(EXTRA_BCANNONS));
	o_notepageExtra->SetElement(2, 1, Background(EXTRA_DEATHRAY));
	o_notepageExtra->SetElement(3, 1, Background(EXTRA_BCRYSTAL));
	o_notepageExtra->SetElement(4, 1, Background(EXTRA_BOBELISK));
	o_notepageExtra->SetElement(0, 3, Background(EXTRA_VOLCANO));
	o_notepageExtra->SetElement(1, 3, Background(EXTRA_BLACKARC));
	o_notepageExtra->SetElement(2, 3, Background(EXTRA_SEAARC));
	o_notepageExtra->SetElement(3, 3, Background(EXTRA_FORTRESS));
	o_notepageExtra->SetElement(4, 3, Background(EXTRA_GSILO));

	return true;
}

bool FrameMain::UpdateFrameSize()
{
	wxRect maxrect = wxGetClientDisplayRect();
	int maxx = maxrect.GetWidth() - 15 - 18 - o_panelDraw->GetPosition().x
															- wxSystemSettings::GetMetric(wxSYS_FRAMESIZE_X, this)
															- o_notebookMain->GetSize().GetWidth();
	int maxy = maxrect.GetHeight() - 10 - 18 - o_panelDraw->GetPosition().y
															- wxSystemSettings::GetMetric(wxSYS_FRAMESIZE_Y, this)
															- wxSystemSettings::GetMetric(wxSYS_CAPTION_Y, this)
															- wxSystemSettings::GetMetric(wxSYS_MENU_Y, this)
															- o_toolbarMain->GetSize().GetHeight()
															- o_statusMain->GetSize().GetHeight();
	maxx = (maxx / 16) * 16;
	maxy = (maxy / 16) * 16;

	int mapwidth = m_map.GetWidth() * 16;
	int mapheight = m_map.GetHeight() * 16;

	int drawwidth = mapwidth;
	int drawheight = mapheight;

	if (drawwidth > maxx)
		drawwidth = maxx;
	if (drawheight > maxy)
		drawheight = maxy;

	int scrollwidth = 0;
	int scrollheight = 0;
	if (mapwidth > drawwidth)
		scrollheight = 18;
	if (mapheight > drawheight)
		scrollwidth = 18;

	int drawposx = o_panelDraw->GetPosition().x;
	int drawposy = o_panelDraw->GetPosition().y;

	int notewidth = o_notebookMain->GetSize().GetWidth();
	int noteheight = o_notebookMain->GetSize().GetHeight();

	int noteposx = drawposx + drawwidth + 10 + scrollwidth;
	if (noteposx + notewidth < o_toolbarMain->GetBestSize().GetWidth())
		noteposx = o_toolbarMain->GetBestSize().GetWidth() - notewidth;
	int noteposy = drawposy;

	o_panelDraw->SetVirtualSize(mapwidth, mapheight);
	o_panelDraw->SetClientSize(drawwidth, drawheight);
	if (mapwidth > drawwidth || mapheight > drawheight)
		o_panelDraw->SetScrollbars(1, 1, mapwidth, mapheight);
	else
		o_panelDraw->SetScrollRate(0, 0);

	o_notebookMain->Move(noteposx, noteposy);

	if (drawheight + scrollheight < noteheight)
		SetClientSize(noteposx + notewidth + 5, noteheight + 10);
	else
		SetClientSize(noteposx + notewidth + 5, drawheight + 10 + scrollheight);

	return true;
}

bool FrameMain::UpdateStatusName()
{
	SetStatusText(m_map.GetName() + wxT(" (by ") + m_map.GetAuthor() + wxT(")"), 0);
	return true;
}

bool FrameMain::UpdateMouseCoordinates()
{
	SetStatusText("", 1);
	return true;
}

bool FrameMain::UpdateMouseCoordinates(long x, long y)
{
	x += 1;
	y += 1;
	wxString statustext;
	statustext << "X: " << x << ", Y: " << y;
	SetStatusText(statustext, 1);
	return true;
}

bool FrameMain::AddUndoPoint()
{
	m_redo.clear();
	m_undo.push_back(m_map);
	if (m_undo.size() > g_infoUndoLimit)
		m_undo.erase(m_undo.begin());
	o_toolbarMain->UpdateWindowUI();
	return true;
}

bool FrameMain::CheckSave()
{
	if (!m_map.IsDirty())
		return true;

	int answer = wxMessageBox("The map has been modified. Would you like to save the changes?", g_messageboxTitle, wxYES_NO | wxCANCEL | wxICON_QUESTION);
	switch (answer)
	{
	case wxNO:
		return true;
	case wxYES:
		return DoSave();
	case wxCANCEL:
	default:
		return false;
	}
}

bool FrameMain::DoNew()
{
	if (!CheckSave())
		return false;

	return DoNewReset();
}

bool FrameMain::DoOpen()
{
	if (!CheckSave())
		return false;

	wxFileDialog dialog(this, "Open Map...", "", m_filename.GetName(),
						"All Supported Map Files|*.awm;*.aw2;*.awd;*.aws|Advance Wars Maps (*.awm)|*.awm|Advance Wars 2 Maps (*.aw2)|*.aw2|Advance Wars DS v1 Maps (*.awd)|*.awd|Advance Wars Series Maps (*.aws)|*.aws",
						wxOPEN | wxFILE_MUST_EXIST | wxHIDE_READONLY);
	if (dialog.ShowModal() == wxID_CANCEL)
		return false;

	return DoOpenRead(wxFileName(dialog.GetPath()));
}

bool FrameMain::DoSave()
{
	if (!m_filename.IsOk())
		return DoSaveAs();
	else
		return DoSaveWrite(m_filename);
}

bool FrameMain::DoSaveAs()
{
	wxFileDialog dialog(this, "Save Map...", "", m_filename.GetName(),
						"Advance Wars Series Maps (*.aws)|*.aws|Advance Wars Maps (*.awm)|*.awm|Advance Wars 2 Maps (*.aw2)|*.aw2|Advance Wars DS Maps (*.awd)|*.awd",
						wxSAVE | wxOVERWRITE_PROMPT | wxHIDE_READONLY);
	if (dialog.ShowModal() == wxID_CANCEL)
		return false;
	
	wxFileName filename(dialog.GetPath());
	if (!filename.HasExt())
		filename.SetExt("aws");

	return DoSaveWrite(filename);
}

bool FrameMain::DoScreenshot()
{
	wxFileDialog dialog(this, "Save Screenshot...", "", m_filename.GetName(),
						"Portable Network Graphics (*.png)|*.png|Half-Sized PNG (*.png)|*.png|Windows Bitmap (*.bmp)|*.bmp|Joint Photographic Experts Group (*.jpg)|*.jpg|X PixMap (*.xpm)|*.xpm|Miniature-Sized Windows Icon (*.ico)|*.ico",
						wxSAVE | wxOVERWRITE_PROMPT | wxHIDE_READONLY);
	if (dialog.ShowModal() == wxID_CANCEL)
		return false;

	int divide;
	if (dialog.GetFilterIndex() == 5)
		divide = -1;
	else if (dialog.GetFilterIndex() == 1)
		divide = 2;
	else
		divide = 1;

	return DoScreenshotWrite(wxFileName(dialog.GetPath()), divide);
}

bool FrameMain::DoNewReset()
{
	m_undo.clear();
	m_redo.clear();
	m_filename.Clear();
	m_map = Map();
	UpdateFrameSize();
	o_panelDraw->CancelSelection(false);
	o_panelDraw->SetMode(ID_TOOL_PENCIL);
	Refresh();
	return true;
}

bool FrameMain::DoOpenRead(wxFileName filename)
{
	wxFile file;
	if (!file.Open(filename.GetFullPath(), wxFile::read))
	{
		wxMessageBox("Failed to open the selected file.", g_messageboxTitle, wxICON_ERROR);
		return false;
	}

	try
	{
		unsigned char buffer[5000];
		file.Read(buffer, 10);
		wxString string_header;
		buffer[10] = 0;
		string_header << buffer;

		if (string_header == "AWMap 001" || string_header == "AW2Map001" || string_header == "AWDMap001" || string_header == "AWSMap001")
		{
			int maptype = Element::HeaderToMaptype(string_header);

			if (string_header == "AWSMap001")
			{
				file.Read(buffer, 2);
				m_map = Map(buffer[0], buffer[1]);
			}
			else
				m_map = Map(30, 20);
			
			if (string_header == "AWMap 001")
				m_map.SetTileset(TILESET_AW1);
			else if (string_header == "AW2Map001")
				m_map.SetTileset(TILESET_AW2);
			else if (string_header == "AWDMap001")
			{
				file.Read(buffer, 1);
				m_map.SetTileset(buffer[0] - 1);
			}
			else if (string_header == "AWSMap001")
			{
				file.Read(buffer, 1);
				m_map.SetTileset(buffer[0]);
			}
			int i, j;
			for (i = 0; i < m_map.GetWidth(); i++)
				for (j = 0; j < m_map.GetHeight(); j++)
				{
					file.Read(buffer, 2);
					m_map.SetBackground(i, j, Element((int)(buffer[1]) * 256 + (int)(buffer[0]), maptype), false);
				}
			for (i = 0; i < m_map.GetWidth(); i++)
				for (j = 0; j < m_map.GetHeight(); j++)
				{
					file.Read(buffer, 2);
					m_map.SetForeground(i, j, Element((int)(buffer[1]) * 256 + (int)(buffer[0]), maptype));
				}

			if (!file.Eof())
			{
				unsigned long fieldsize;

				fieldsize = 0;
				file.Read(buffer, sizeof(unsigned long));
				for (i = 0; i < sizeof(unsigned long); i++)
					fieldsize += buffer[i] * power(256, i);
				if (fieldsize >= sizeof(buffer))
					fieldsize = sizeof(buffer) - 1;
				if (fieldsize)
				{
					file.Read(buffer, fieldsize);
					buffer[fieldsize] = 0;
					m_map.SetName(buffer);
				}

				fieldsize = 0;
				file.Read(buffer, sizeof(unsigned long));
				for (i = 0; i < sizeof(unsigned long); i++)
					fieldsize += buffer[i] * power(256, i);
				if (fieldsize >= sizeof(buffer))
					fieldsize = sizeof(buffer) - 1;
				if (fieldsize)
				{
					file.Read(buffer, fieldsize);
					buffer[fieldsize] = 0;
					m_map.SetAuthor(buffer);
				}

				fieldsize = 0;
				file.Read(buffer, sizeof(unsigned long));
				for (i = 0; i < sizeof(unsigned long); i++)
					fieldsize += buffer[i] * power(256, i);
				if (fieldsize >= sizeof(buffer))
					fieldsize = sizeof(buffer) - 1;
				if (fieldsize)
				{
					file.Read(buffer, fieldsize);
					buffer[fieldsize] = 0;
					m_map.SetDescription(buffer);
				}
			}
		}

		else
		{
			wxMessageBox("The selected file could not be identified.", g_messageboxTitle, wxICON_ERROR);
			return false;
		}

		m_filename = filename;
		m_map.SetDirty(false); 
		m_undo.clear();
		m_redo.clear();
		UpdateStatusName();
		UpdateFrameSize();
		o_panelDraw->CancelSelection(false);
		o_panelDraw->SetMode(ID_TOOL_PENCIL);
		Refresh();
		return true;
	}
	catch (...)
	{
		wxMessageBox("An error ocurred while reading the file.", g_messageboxTitle, wxICON_ERROR);
		DoNewReset();
		return false;
	}
}

bool FrameMain::DoSaveWrite(wxFileName filename)
{
	wxFile file;
	if (!file.Open(filename.GetFullPath(), wxFile::write))
	{
		wxMessageBox("Failed to open the selected file.", g_messageboxTitle, wxICON_ERROR);
		return false;
	}
	try
	{
		unsigned char buffer[5000];
		wxString string_header;
		int i, j;

		if (filename.GetExt().Lower() == "awm")
			string_header = "AWMap 001";
		else if (filename.GetExt().Lower() == "aw2")
			string_header = "AW2Map001";
		else if (filename.GetExt().Lower() == "awd")
			string_header = "AWDMap001";
		else
			string_header = "AWSMap001";

		int maptype = Element::HeaderToMaptype(string_header);
		int compat;
		compat = m_map.IsCompatibleElements(maptype);
		if (compat == COMPAT_TRUNCATE)
			if (wxMessageBox("Some tiles aren't compatible with the selected map type. Terrains will be transformed into plains or pipes accordingly and incompatible units will be deleted in the saved file.", g_messageboxTitle, wxOK | wxCANCEL | wxICON_INFORMATION) == wxCANCEL)
				return false;

		compat = m_map.IsCompatibleSize(maptype);
		if (compat == COMPAT_IMPOSSIBLE)
		{
			wxMessageBox("The map dimensions are incompatible with old map formats.", g_messageboxTitle, wxICON_ERROR);
			return false;
		}
		else if (compat == COMPAT_TRUNCATE)
		{
			if (wxMessageBox("The map dimensions are larger than 30x20. The saved map will be cropped to fit the required dimensions.", g_messageboxTitle, wxOK | wxCANCEL | wxICON_INFORMATION) == wxCANCEL)
				return false;
		}

		file.Write(string_header.c_str(), 9);
		buffer[0] = 0;
		file.Write(buffer, 1);

		if (maptype == MAPTYPE_AWS001)
		{
			buffer[0] = m_map.GetWidth();
			buffer[1] = m_map.GetHeight();
			file.Write(buffer, 2);
		}

		if (maptype == MAPTYPE_AWDS)
		{
			buffer[0] = m_map.GetTileset() + 1;
			file.Write(buffer, 1);
		}
		else if (maptype == MAPTYPE_AWS001)
		{
			buffer[0] = m_map.GetTileset();
			file.Write(buffer, 1);
		}

		int maxwidth, maxheight;
		if (maptype == MAPTYPE_AW1 || maptype == MAPTYPE_AW2 || maptype == MAPTYPE_AWDS)
		{
			maxwidth = 30;
			maxheight = 20;
		}
		else
		{
			maxwidth = m_map.GetWidth();
			maxheight = m_map.GetHeight();
		}

		for (i = 0; i < maxwidth; i++)
			for (j = 0; j < maxheight; j++)
			{
				buffer[0] = m_map.GetBackground(i, j).ConvertTo(maptype) % 256;
				buffer[1] = m_map.GetBackground(i, j).ConvertTo(maptype) / 256;
				file.Write(buffer, 2);
			}
		for (i = 0; i < maxwidth; i++)
			for (j = 0; j < maxheight; j++)
			{
				buffer[0] = m_map.GetForeground(i, j).ConvertTo(maptype) % 256;
				buffer[1] = m_map.GetForeground(i, j).ConvertTo(maptype) / 256;
				file.Write(buffer, 2);
			}

		unsigned long fieldsize;

		fieldsize = m_map.GetName().Len();
		for (i = 0; i < sizeof(unsigned long); i++)
			buffer[i] = (fieldsize / power(256, i)) % 256;
		file.Write(buffer, sizeof(unsigned long));
		file.Write(m_map.GetName().c_str(), fieldsize);

		fieldsize = m_map.GetAuthor().Len();
		for (i = 0; i < sizeof(unsigned long); i++)
			buffer[i] = (fieldsize / power(256, i)) % 256;
		file.Write(buffer, sizeof(unsigned long));
		file.Write(m_map.GetAuthor().c_str(), fieldsize);

		fieldsize = m_map.GetDescription().Len();
		for (i = 0; i < sizeof(unsigned long); i++)
			buffer[i] = (fieldsize / power(256, i)) % 256;
		file.Write(buffer, sizeof(unsigned long));
		file.Write(m_map.GetDescription().c_str(), fieldsize);

		m_filename = filename;
		std::vector<Map>::iterator it;
		for (it = m_undo.begin(); it != m_undo.end(); it++)
			it->SetDirty(true);
		for (it = m_redo.begin(); it != m_redo.end(); it++)
			it->SetDirty(true);
		m_map.SetDirty(false);
		return true;
	}
	catch (...)
	{
		wxMessageBox("An error ocurred while writing to the file.", g_messageboxTitle, wxICON_ERROR);
		return false;
	}
}

bool FrameMain::DoScreenshotWrite(wxFileName filename, int divide)
{
	wxFile file;
	if (!file.Open(filename.GetFullPath(), wxFile::write))
	{
		wxMessageBox("Failed to open the selected file.", g_messageboxTitle, wxICON_ERROR);
		return false;
	}
	try
	{
		wxBitmap bitmap(m_map.GetWidth() * 16, m_map.GetHeight() * 16);
		wxMemoryDC dc;
		dc.SelectObject(bitmap);
		if (!o_panelDraw->DrawMap(dc))
		{
			wxMessageBox("An error ocurred while drawing the map.", g_messageboxTitle, wxICON_ERROR);
			return false;
		}
		dc.SelectObject(wxNullBitmap);

		wxImage image = bitmap.ConvertToImage();
		if (divide > 1)
			image.Rescale(image.GetWidth() / divide, image.GetHeight() / divide);
		else if (divide == -1)
		{
			double x = image.GetWidth();
			double y = image.GetHeight();
			if (x / 255 > y / 127)
				image.Rescale(255, y * 255 / x);
			else
				image.Rescale(x * 127 / y, 127);
		}

		int type;
		if (filename.GetExt() == "bmp")
			type = wxBITMAP_TYPE_BMP;
		else if (filename.GetExt().Lower() == "jpg")
			type = wxBITMAP_TYPE_JPEG;
		else if (filename.GetExt().Lower() == "xpm")
			type = wxBITMAP_TYPE_XPM;
		else if (filename.GetExt().Lower() == "ico")
			type = wxBITMAP_TYPE_ICO;
		else
			type = wxBITMAP_TYPE_PNG;

        wxFileOutputStream osfile(file);
		if (!image.SaveFile(osfile, type))
			throw 0;

		return true;
	}
	catch (...)
	{
		wxMessageBox("An error ocurred while writing to the file.", g_messageboxTitle, wxICON_ERROR);
		return false;
	}
}
