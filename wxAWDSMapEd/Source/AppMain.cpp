#include "precomp.h"
#include "AppMain.h"

#include "Element.h"
#include "Map.h"
#include "FrameMain.h"


IMPLEMENT_APP(AppMain)

bool AppMain::OnInit()
{
	// Initialize global variables.
	g_messageboxTitle = "Advance Wars Series Map Editor";
	g_version = "1.0";
	g_appname = "AWSMapEditor";
	g_clipboardstring = g_appname + "-v" + g_version + "-map-part";
	LoadPreferences();


	// Test the activation date. To turn off time lock-down, edit precomp.h.
	if (!TimeActivation())
		return false;


	// Image handlers that will be used in the program.
	wxImage::AddHandler(new wxPNGHandler);
	wxImage::AddHandler(new wxBMPHandler);
	wxImage::AddHandler(new wxJPEGHandler);
	wxImage::AddHandler(new wxXPMHandler);
	wxImage::AddHandler(new wxICOHandler);


	// Create new FrameMain object.
 	FrameMain* frameMain = new FrameMain(NULL, -1, wxPoint(-1,-1));
    frameMain->Show(true);
    SetTopWindow(frameMain);


	// Load a map from the command line.
	if (argc > 1)
		frameMain->DoOpenRead(wxFileName(argv[1]));
	

	// Tell the program that the program should keep running.
	// Return false to end the program execution before it enters the main loop.
    return true;
}

bool AppMain::TimeActivation()
{
	if (!ENABLE_TIME_ACTIVATION)
		return true;

	wxDateTime today = wxDateTime::Now();
	if (today.GetYear() == 2007 && today.GetMonth() == 03 && today.GetDay() >= 05 && today.GetDay() <= 06)
		return true;				// 05/APR/2007 to 06/APR/2007

	wxMessageBox("This program is not valid. Please try downloading the latest version of the editor from http://mapeditor.hopto.org or http://eciportalip.no-ip.info:90/maped.", g_messageboxTitle, wxICON_INFORMATION);
	return false;
}

bool AppMain::LoadPreferences()
{
	wxFileConfig config(g_appname, wxEmptyString, wxString("./") + g_appname + wxString(".ini"), wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	int version = config.Read("ConfigVersion", (long)0);
	if (version == 1)
	{
		g_infoVolume = config.Read("Volume", 50);
		if (g_infoVolume < 0 || g_infoVolume > 100)
			g_infoVolume = 50;
		config.Read("VolumeEnable", &g_infoVolumeEnable, true);
		g_infoDefaultWidth = config.Read("DefaultWidth", MAP_DEF_WIDTH);
		if (g_infoDefaultWidth < MAP_MIN_WIDTH || g_infoDefaultWidth > MAP_MAX_WIDTH)
				g_infoDefaultWidth = MAP_DEF_WIDTH;
		g_infoDefaultHeight = config.Read("DefaultHeight", MAP_DEF_HEIGHT);
		if (g_infoDefaultHeight < MAP_MIN_HEIGHT || g_infoDefaultHeight > MAP_MAX_HEIGHT)
				g_infoDefaultHeight = MAP_DEF_HEIGHT;
		g_infoDefaultTerrain = config.Read("DefaultTerrain", TERRAIN_SEA);
		if (g_infoDefaultTerrain != TERRAIN_PLAIN && g_infoDefaultTerrain != TERRAIN_WOOD && g_infoDefaultTerrain != TERRAIN_MOUNTAIN && g_infoDefaultTerrain != TERRAIN_ROAD && g_infoDefaultTerrain != TERRAIN_SEA)
			g_infoDefaultTerrain = TERRAIN_SEA;
		g_infoDefaultTileset = config.Read("DefaultTileset", (long)TILESET_NORMAL);
		if (g_infoDefaultTileset >= TILESET_LIMIT)
			g_infoDefaultTileset = TILESET_NORMAL;
		g_infoDefaultAuthor = config.Read("DefaultAuthor", "[unknown]");
		if (g_infoDefaultAuthor.Length() > AUTHOR_MAX_LEN)
			g_infoDefaultAuthor = "[unknown]";
		g_infoUndoLimit = config.Read("UndoLimit", 30);
		if (g_infoUndoLimit != 10 && g_infoUndoLimit != 20 && g_infoUndoLimit != 30 && g_infoUndoLimit != 40 && g_infoUndoLimit != 50 && g_infoUndoLimit != 100)
			g_infoUndoLimit = 30;
		config.Read("DrawCursor", &g_infoDrawCursor, true);
	}
	else
	{
		g_infoVolume = 50;
		g_infoVolumeEnable = true;
		g_infoDefaultWidth = MAP_DEF_WIDTH;
		g_infoDefaultHeight = MAP_DEF_HEIGHT;
		g_infoDefaultTerrain = TERRAIN_SEA;
		g_infoDefaultTileset = TILESET_NORMAL;
		g_infoDefaultAuthor = "[unknown]";
		g_infoUndoLimit = 30;
		g_infoDrawCursor = true;
	}
	return true;
}
