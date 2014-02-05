#include "precomp.h"
#include "DialogPreferences.h"

#include "Element.h"
#include "Map.h"


BEGIN_EVENT_TABLE(DialogPreferences, wxDialog)

	// Event handling: ButtonClick
	EVT_BUTTON(wxID_OK,				DialogPreferences::EvButton_OK)
	EVT_BUTTON(wxID_CANCEL,			DialogPreferences::EvButton_Cancel)

	// Event handling: Others
	EVT_CHECKBOX(ID_VOLUME_ENABLE,			DialogPreferences::EvChange_VolumeEnable)
	EVT_COMMAND_SCROLL(ID_VOLUME_SLIDER,	DialogPreferences::EvChange_VolumeSlider)

END_EVENT_TABLE()



DialogPreferences::DialogPreferences(wxWindow* parent, int id, const wxPoint& pos)
	: wxDialog(parent, id, "", pos, wxDefaultSize, wxCAPTION | wxCLOSE_BOX | wxSYSTEM_MENU)
{
	int width = PLATSPEC(300, 400, 300);
	int height = PLATSPEC(390, 400, 390);
	
	int secondtabpos = PLATSPEC(130, 160, 130);

	SetClientSize(width, height);
	SetTitle("Editor Preferences");

	o_boxVolume = new wxStaticBox(this, wxID_ANY, "Background Music", wxPoint(10, 10), wxSize(width - 20, 80));
		o_checkVolume = new wxCheckBox(this, ID_VOLUME_ENABLE, "Enable background music", wxPoint(20, 35));
		o_sliderVolume = new wxSlider(this, ID_VOLUME_SLIDER, 0, 0, 100, wxPoint(20, 55), wxSize(width - PLATSPEC(65, 80, 65), 25));
		o_labelVolume = new wxStaticText(this, wxID_ANY, "%", wxPoint(width - PLATSPEC(45, 55, 45), 58), wxSize(PLATSPEC(30, 40, 30), 20), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	o_boxOthers = new wxStaticBox(this, wxID_ANY, "Other Preferences", wxPoint(10, 100), wxSize(width - 20, 245));
		wxArrayString array;
		new wxStaticText(this, wxID_ANY, "Default width:", wxPoint(20, 125));
			o_spinWidth = new wxSpinCtrl(this, ID_DEFAULT_WIDTH, "", wxPoint(secondtabpos, 122), wxSize(60, -1), wxSP_ARROW_KEYS, MAP_MIN_WIDTH, MAP_MAX_WIDTH);
		new wxStaticText(this, wxID_ANY, "Default height:", wxPoint(20, 150));
			o_spinHeight = new wxSpinCtrl(this, ID_DEFAULT_HEIGHT, "", wxPoint(secondtabpos, 147), wxSize(60, -1), wxSP_ARROW_KEYS, MAP_MIN_HEIGHT, MAP_MAX_HEIGHT);
		new wxStaticLine(this, wxID_ANY, wxPoint(15, 175), wxSize(width - 30, 1));
		new wxStaticText(this, wxID_ANY, "Default terrain:", wxPoint(20, 185));
			array.Clear();
			array.Add("Plains");	array.Add("Woods");		array.Add("Mountains");		array.Add("Roads");		array.Add("Sea");
			o_comboTerrain = new wxComboBox(this, ID_DEFAULT_TERRAIN, "", wxPoint(secondtabpos, 182), wxDefaultSize, array, wxCB_DROPDOWN | wxCB_READONLY);
		new wxStaticText(this, wxID_ANY, "Default tileset:", wxPoint(20, 210));
			array.Clear();
			array.Add("Normal");	array.Add("Snow");		array.Add("Desert");
			array.Add("Wasteland");	array.Add("AW1");		array.Add("AW2");
			o_comboTileset = new wxComboBox(this, ID_DEFAULT_TILESET, "", wxPoint(secondtabpos, 207), wxDefaultSize, array, wxCB_DROPDOWN | wxCB_READONLY);
		new wxStaticLine(this, wxID_ANY, wxPoint(15, 235), wxSize(width - 30, 1));
		new wxStaticText(this, wxID_ANY, "Undo/redo limit:", wxPoint(20, 245));
			array.Clear();
			array.Add("10");	array.Add("20");		array.Add("30");
			array.Add("40");	array.Add("50");		array.Add("100");
			o_comboUndo = new wxComboBox(this, ID_UNDO_LIMIT, "", wxPoint(secondtabpos, 242), wxDefaultSize, array, wxCB_DROPDOWN | wxCB_READONLY);
		new wxStaticLine(this, wxID_ANY, wxPoint(15, 270), wxSize(width - 30, 1));
		new wxStaticText(this, wxID_ANY, "Default author name:", wxPoint(20, 280));
			o_textAuthor = new wxTextCtrl(this, ID_DEFAULT_AUTHOR, "", wxPoint(secondtabpos, 277), wxSize(width - secondtabpos - 20, -1));
			o_textAuthor->SetMaxLength(NAME_MAX_LEN);
		new wxStaticLine(this, wxID_ANY, wxPoint(15, 305), wxSize(width - 30, 1));
		o_checkDrawCursor = new wxCheckBox(this, ID_DRAW_CURSOR, "Draw AW-style cursors (requires restart)", wxPoint(20, 315));
	o_buttonOK = new wxButton(this, wxID_OK, "&OK", wxPoint(width - PLATSPEC(160, 180, 160), height - 35), wxSize(PLATSPEC(70, 70, 70), 25));
	o_buttonCancel = new wxButton(this, wxID_CANCEL, "&Cancel", wxPoint(width - PLATSPEC(80, 100, 80), height - 35), wxSize(PLATSPEC(70, 90, 70), 25));

	o_checkVolume->SetValue(g_infoVolumeEnable);
	o_sliderVolume->SetValue(g_infoVolume);
	o_spinWidth->SetValue(g_infoDefaultWidth);
	o_spinHeight->SetValue(g_infoDefaultHeight);
	switch (g_infoDefaultTerrain)
	{
		case TERRAIN_PLAIN:			o_comboTerrain->SetValue("Plains");		break;
		case TERRAIN_WOOD:			o_comboTerrain->SetValue("Woods");		break;
		case TERRAIN_MOUNTAIN:		o_comboTerrain->SetValue("Mountains");	break;
		case TERRAIN_ROAD:			o_comboTerrain->SetValue("Roads");		break;
		case TERRAIN_SEA: default:	o_comboTerrain->SetValue("Sea");		break;
	}
	switch (g_infoDefaultTileset)
	{
		case TILESET_SNOW:				o_comboTileset->SetValue("Snow");		break;
		case TILESET_DESERT:			o_comboTileset->SetValue("Desert");		break;
		case TILESET_WASTELAND:			o_comboTileset->SetValue("Wasteland");	break;
		case TILESET_AW1:				o_comboTileset->SetValue("AW1");		break;
		case TILESET_AW2:				o_comboTileset->SetValue("AW2");		break;
		case TILESET_NORMAL: default:	o_comboTileset->SetValue("Normal");		break;
	}
	o_comboUndo->SetValue(ConvertToString(g_infoUndoLimit));
	o_textAuthor->SetValue(g_infoDefaultAuthor);
	o_checkDrawCursor->SetValue(g_infoDrawCursor);
    o_buttonOK->SetDefault();

	wxFileConfig config(g_appname, wxEmptyString, wxString("./") + g_appname + wxString(".ini"), wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	int version = config.Read("ConfigVersion", (long)0);
	if (version == 1)
	{
		bool drawcursor;
		config.Read("DrawCursor", &drawcursor, g_infoDrawCursor);
		o_checkDrawCursor->SetValue(drawcursor);
	}

    #ifdef __WXGTK__
        o_boxVolume->Enable(false);
        o_checkVolume->Enable(false);
        o_sliderVolume->Enable(false);
        o_labelVolume->Enable(false);
        o_checkVolume->SetValue(false);
    #endif

	UpdateVolumeValue();
	UpdateVolumeEnable();

}



//////////////////////////////////////////////////////////
//                                                      //
//  EVENT HANDLING:  ButtonClick                        //
//                                                      //
//////////////////////////////////////////////////////////

void DialogPreferences::EvButton_OK(wxCommandEvent& event)
{
	if (o_spinWidth->GetValue() * o_spinHeight->GetValue() >= 100 * 100)
		if (wxMessageBox("The selected values for width and height may cause slowness and excessive memory usage.", g_messageboxTitle, wxOK | wxCANCEL | wxICON_INFORMATION) == wxCANCEL)
			return;
	if (o_spinWidth->GetValue() * o_spinHeight->GetValue() >= 500 * 500)
		if (wxMessageBox("The selected values for width and height will cause slowness and excessive memory usage, and should not be used in old computers.", g_messageboxTitle, wxOK | wxCANCEL | wxICON_INFORMATION) == wxCANCEL)
			return;
	if (o_spinWidth->GetValue() * o_spinHeight->GetValue() >= 1000 * 1000)
		if (wxMessageBox("The selected values for width and height WILL cause slowness and excessive memory usage, and must not be used in old computers.\nThe program may crash and display slow reactions.\n\nPlease make sure you know what you are doing before continuing.", g_messageboxTitle, wxOK | wxCANCEL | wxICON_ERROR) == wxCANCEL)
			return;

	g_infoVolumeEnable = o_checkVolume->GetValue();
	g_infoVolume = o_sliderVolume->GetValue();
	g_infoDefaultWidth = o_spinWidth->GetValue();
	g_infoDefaultHeight = o_spinHeight->GetValue();
	if (o_comboTerrain->GetValue() == "Plains")			g_infoDefaultTerrain = TERRAIN_PLAIN;
	else if (o_comboTerrain->GetValue() == "Woods")		g_infoDefaultTerrain = TERRAIN_WOOD;
	else if (o_comboTerrain->GetValue() == "Mountains")	g_infoDefaultTerrain = TERRAIN_MOUNTAIN;
	else if (o_comboTerrain->GetValue() == "Roads")		g_infoDefaultTerrain = TERRAIN_ROAD;
	else												g_infoDefaultTerrain = TERRAIN_SEA;
	if (o_comboTileset->GetValue() == "Snow")			g_infoDefaultTileset = TILESET_SNOW;
	else if (o_comboTileset->GetValue() == "Desert")	g_infoDefaultTileset = TILESET_DESERT;
	else if (o_comboTileset->GetValue() == "Wasteland")	g_infoDefaultTileset = TILESET_WASTELAND;
	else if (o_comboTileset->GetValue() == "AW1")		g_infoDefaultTileset = TILESET_AW1;
	else if (o_comboTileset->GetValue() == "AW2")		g_infoDefaultTileset = TILESET_AW2;
	else												g_infoDefaultTileset = TILESET_NORMAL;
	g_infoUndoLimit = ConvertToNumber(o_comboUndo->GetValue());
	g_infoDefaultAuthor = o_textAuthor->GetValue();

	wxFileConfig config(g_appname, wxEmptyString, wxString("./") + g_appname + wxString(".ini"), wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	config.Write("ConfigVersion", 1);

	config.Write("Volume", g_infoVolume);
	config.Write("VolumeEnable", g_infoVolumeEnable);
	config.Write("DefaultWidth", g_infoDefaultWidth);
	config.Write("DefaultHeight", g_infoDefaultHeight);
	config.Write("DefaultTerrain", g_infoDefaultTerrain);
	config.Write("DefaultTileset", g_infoDefaultTileset);
	config.Write("DefaultAuthor", g_infoDefaultAuthor);
	config.Write("UndoLimit", g_infoUndoLimit);
	config.Write("DrawCursor", o_checkDrawCursor->GetValue());

	EndModal(wxID_OK);
	Destroy();
}

void DialogPreferences::EvButton_Cancel(wxCommandEvent& event)
{
	EndModal(wxID_CANCEL);
	Destroy();
}



//////////////////////////////////////////////////////////
//                                                      //
//  EVENT HANDLING:  Others                             //
//                                                      //
//////////////////////////////////////////////////////////

void DialogPreferences::EvChange_VolumeSlider(wxScrollEvent& event)
{
	UpdateVolumeValue();
}

void DialogPreferences::EvChange_VolumeEnable(wxCommandEvent& event)
{
	UpdateVolumeEnable();
}



//////////////////////////////////////////////////////////
//                                                      //
//  OTHER MISC FUNCTIONS.                               //
//                                                      //
//////////////////////////////////////////////////////////

bool DialogPreferences::UpdateVolumeEnable()
{
	o_sliderVolume->Enable(o_checkVolume->GetValue());
	o_labelVolume->Enable(o_checkVolume->GetValue());
	return true;
}

bool DialogPreferences::UpdateVolumeValue()
{
	o_labelVolume->SetLabel(ConvertToString(o_sliderVolume->GetValue()) + "%");
	return true;
}
