		#pragma once

#include <vector>
#include "Element.h"
#include "Map.h"
#include "DrawPanel.h"
#include "Page.h"

#define PAGE_TERRAIN	0
#define PAGE_UNIT		1
#define PAGE_EXTRA		2

class FrameMain: public wxFrame
{
public:
    FrameMain(wxWindow* parent, int id, const wxPoint& pos = wxDefaultPosition);


	Map m_map;
	std::vector<Map> m_undo;
	std::vector<Map> m_redo;

	wxFileName m_filename;


	wxMenuBar* o_menubarMain;
		wxMenu* o_menuFile;
			wxMenuItem* o_menuitemFileNew;
			wxMenuItem* o_menuitemFileOpen;
			wxMenuItem* o_menuitemFileSave;
			wxMenuItem* o_menuitemFileSaveAs;
			wxMenuItem* o_menuitemFileScreenshot;
			wxMenuItem* o_menuitemFilePreferences;
			wxMenuItem* o_menuitemFileExit;
		wxMenu* o_menuMap;
			wxMenuItem* o_menuitemMapInformation;
			wxMenuItem* o_menuitemMapSettings;
			wxMenuItem* o_menuitemMapStatus;
			wxMenuItem* o_menuitemMapFill;
				wxMenu* o_menuMapFill;
				wxMenuItem* o_menuitemMapFillSea;
				wxMenuItem* o_menuitemMapFillPlain;
				wxMenuItem* o_menuitemMapFillWood;
				wxMenuItem* o_menuitemMapFillMountain;
				wxMenuItem* o_menuitemMapFillRoad;
		wxMenu* o_menuEdit;
			wxMenuItem* o_menuitemEditUndo;
			wxMenuItem* o_menuitemEditRedo;
			wxMenuItem* o_menuitemEditCut;
			wxMenuItem* o_menuitemEditCopy;
			wxMenuItem* o_menuitemEditPaste;
			wxMenuItem* o_menuitemEditPasteTerrain;
			wxMenuItem* o_menuitemEditPasteUnits;
			wxMenuItem* o_menuitemEditSelectAll;
			wxMenuItem* o_menuitemEditCancelSelection;
			wxMenuItem* o_menuitemEditRemoveSelection;
			wxMenuItem* o_menuitemEditFlipHorizontally;
			wxMenuItem* o_menuitemEditFlipVertically;
			wxMenuItem* o_menuitemEditRotateClockwise;
			wxMenuItem* o_menuitemEditRotateCounterclockwise;
			wxMenuItem* o_menuitemEditDeleteUnits;
			wxMenuItem* o_menuitemEditDeleteAllUnits;
		wxMenu* o_menuHelp;
			wxMenuItem* o_menuitemHelpAbout;

	wxToolBar* o_toolbarMain;
		wxToolBarToolBase* o_toolNew;
		wxToolBarToolBase* o_toolOpen;
		wxToolBarToolBase* o_toolSave;
		wxToolBarToolBase* o_toolCut;
		wxToolBarToolBase* o_toolCopy;
		wxToolBarToolBase* o_toolPaste;
		wxToolBarToolBase* o_toolUndo;
		wxToolBarToolBase* o_toolRedo;
		wxToolBarToolBase* o_toolPencil;
		wxToolBarToolBase* o_toolLine;
		wxToolBarToolBase* o_toolSquare;
		wxToolBarToolBase* o_toolSquarefill;
		wxToolBarToolBase* o_toolBucket;
		wxToolBarToolBase* o_toolSelector;

	wxStatusBar* o_statusMain;
	wxPanel* o_panelBackground;
	DrawPanel* o_panelDraw;

	wxNotebook* o_notebookMain;
		Page* o_notepageTerrain;
		Page* o_notepageUnit;
		Page* o_notepageExtra;

#ifndef __WXGTK__
	wxTimer* o_timerMedia;
	wxTimer* o_timerMediaLoaded;

	wxMediaCtrl* o_mediaMain;
#endif


	//Event handling: MenuClick & ToolClick
	void EvMenuClick_FileNew(wxCommandEvent& event);
	void EvMenuClick_FileOpen(wxCommandEvent& event);
	void EvMenuClick_FileSave(wxCommandEvent& event);
	void EvMenuClick_FileSaveAs(wxCommandEvent& event);
	void EvMenuClick_FileScreenshot(wxCommandEvent& event);
	void EvMenuClick_FilePreferences(wxCommandEvent& event);
	void EvMenuClick_FileExit(wxCommandEvent& event);
	void EvMenuClick_MapFill(wxCommandEvent& event);
	void EvMenuClick_MapInformation(wxCommandEvent& event);
	void EvMenuClick_MapSettings(wxCommandEvent& event);
	void EvMenuClick_MapStatus(wxCommandEvent& event);
	void EvMenuClick_EditUndo(wxCommandEvent& event);
	void EvMenuClick_EditRedo(wxCommandEvent& event);
	void EvMenuClick_EditCutCopy(wxCommandEvent& event);
	void EvMenuClick_EditPaste(wxCommandEvent& event);
	void EvMenuClick_EditSelectAll(wxCommandEvent& event);
	void EvMenuClick_EditCancelSelection(wxCommandEvent& event);
	void EvMenuClick_EditFlip(wxCommandEvent& event);
	void EvMenuClick_EditRotate(wxCommandEvent& event);
	void EvMenuClick_EditDeleteUnits(wxCommandEvent& event);
	void EvMenuClick_EditDeleteAllUnits(wxCommandEvent& event);
	void EvMenuClick_HelpAbout(wxCommandEvent& event);
	void EvMenuClick_ToolMode(wxCommandEvent& event);


	//Event handling: UpdateUI
	void EvUpdateUI_Undo(wxUpdateUIEvent& event);
	void EvUpdateUI_Redo(wxUpdateUIEvent& event);
	void EvUpdateUI_SelectionDependent(wxUpdateUIEvent& event);
	void EvUpdateUI_Paste(wxUpdateUIEvent& event);


	//Event handling: Others
	void EvClose(wxCloseEvent& event);
	void EvToolbarEnter(wxCommandEvent& event);
#ifndef __WXGTK__
	void EvTimer_Media(wxTimerEvent& event);
	void EvTimer_MediaLoaded(wxTimerEvent& event);
	void EvMedia_Loaded(wxMediaEvent& event);
	void EvMedia_Play(wxMediaEvent& event);
#endif

	//Other misc methods.
	bool FillPages();
	bool UpdateFrameSize();
	bool UpdateStatusName();
	bool UpdateMouseCoordinates();
	bool UpdateMouseCoordinates(long x, long y);

	bool AddUndoPoint();
	bool CheckSave();

	bool DoNew();
	bool DoOpen();
	bool DoSave();
	bool DoSaveAs();
	bool DoScreenshot();

	bool DoNewReset();
	bool DoOpenRead(wxFileName filename);
	bool DoSaveWrite(wxFileName filename);
	bool DoScreenshotWrite(wxFileName filename, int divide = 1);



	enum enumIDs
	{
		ID_FILE_SCREENSHOT,
		ID_MAP_FILL,
		ID_MAP_FILL_SEA,
		ID_MAP_FILL_PLAIN,
		ID_MAP_FILL_WOOD,
		ID_MAP_FILL_MOUNTAIN,
		ID_MAP_FILL_ROAD,
		ID_MAP_INFORMATION,
		ID_MAP_SETTINGS,
		ID_MAP_STATUS,
		ID_EDIT_PASTETERRAIN,
		ID_EDIT_PASTEUNITS,
		ID_EDIT_CANCELSELECTION,
		ID_EDIT_REMOVESELECTION,
		ID_EDIT_FLIPHORIZONTALLY,
		ID_EDIT_FLIPVERTICALLY,
		ID_EDIT_ROTATECLOCKWISE,
		ID_EDIT_ROTATECOUNTERCLOCKWISE,
		ID_EDIT_DELETEUNITS,
		ID_EDIT_DELETEALLUNITS,
		ID_TOOLBAR_MAIN,
		ID_TOOL_PENCIL,
		ID_TOOL_LINE,
		ID_TOOL_SQUARE,
		ID_TOOL_SQUAREFILL,
		ID_TOOL_BUCKET,
		ID_TOOL_SELECTOR,
		ID_STATUSBAR_MAIN,
		ID_NOTEBOOK_MAIN,
		ID_NOTEPAGE_TERRAIN,
		ID_NOTEPAGE_UNIT,
		ID_NOTEPAGE_EXTRA,
		ID_TIMER_MOUSE,
		ID_TIMER_MEDIA,
		ID_TIMER_MEDIALOADED,
		ID_MEDIA_MAIN
	};

private:
    DECLARE_EVENT_TABLE()
};
