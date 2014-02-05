#include "precomp.h"
#include "DialogSettings.h"


BEGIN_EVENT_TABLE(DialogSettings, wxDialog)

	// Event handling: ButtonClick
	EVT_BUTTON(wxID_OK,				DialogSettings::EvButton_OK)
	EVT_BUTTON(wxID_CANCEL,			DialogSettings::EvButton_Cancel)

END_EVENT_TABLE()



DialogSettings::DialogSettings(wxWindow* parent, Map* map, int id, const wxPoint& pos)
	: wxDialog(parent, id, "", pos, wxDefaultSize, wxCAPTION | wxCLOSE_BOX | wxSYSTEM_MENU)
{
	int width = PLATSPEC(200, 210, 200);
	int height = PLATSPEC(200, 210, 200);
	
	SetClientSize(width, height);
	SetTitle("Map Settings");
	m_map = map;

	new wxStaticText(this, wxID_ANY, "Width:", wxPoint(10, 10));
		o_spinWidth = new wxSpinCtrl(this, ID_SPIN_WIDTH, "", wxPoint(70, 7), wxSize(60, -1), wxSP_ARROW_KEYS, MAP_MIN_WIDTH, MAP_MAX_WIDTH);
	new wxStaticText(this, wxID_ANY, "Height:", wxPoint(10, 35));
		o_spinHeight = new wxSpinCtrl(this, ID_SPIN_HEIGHT, "", wxPoint(70, 32), wxSize(60, -1), wxSP_ARROW_KEYS, MAP_MIN_HEIGHT, MAP_MAX_HEIGHT);
	new wxStaticLine(this, wxID_ANY, wxPoint(5, 65), wxSize(width - 10, 1));
	new wxStaticText(this, wxID_ANY, "Tileset:", wxPoint(10, 80));
		o_radioTileset[TILESET_NORMAL] = new wxRadioButton(this, ID_RADIO_TILESET, "Normal", wxPoint(30, 100));
		o_radioTileset[TILESET_SNOW] = new wxRadioButton(this, ID_RADIO_TILESET, "Snow", wxPoint(PLATSPEC(100, 110, 100), 100));
		o_radioTileset[TILESET_DESERT] = new wxRadioButton(this, ID_RADIO_TILESET, "Desert", wxPoint(30, 120));
		o_radioTileset[TILESET_WASTELAND] = new wxRadioButton(this, ID_RADIO_TILESET, "Wasteland", wxPoint(PLATSPEC(100, 110, 100), 120));
		o_radioTileset[TILESET_AW1] = new wxRadioButton(this, ID_RADIO_TILESET, "AW1", wxPoint(30, 140));
		o_radioTileset[TILESET_AW2] = new wxRadioButton(this, ID_RADIO_TILESET, "AW2", wxPoint(PLATSPEC(100, 110, 100), 140));
	o_buttonOK = new wxButton(this, wxID_OK, "&OK", wxPoint(width - PLATSPEC(160, 180, 160), height - 35), wxSize(PLATSPEC(70, 70, 70), 25));
	o_buttonCancel = new wxButton(this, wxID_CANCEL, "&Cancel", wxPoint(width - PLATSPEC(80, 100, 80), height - 35), wxSize(PLATSPEC(70, 90, 70), 25));

	o_spinWidth->SetValue(m_map->GetWidth());
	o_spinHeight->SetValue(m_map->GetHeight());
	o_radioTileset[m_map->GetTileset()]->SetValue(true);
    o_buttonOK->SetDefault();
}



//////////////////////////////////////////////////////////
//                                                      //
//  EVENT HANDLING:  ButtonClick                        //
//                                                      //
//////////////////////////////////////////////////////////

void DialogSettings::EvButton_OK(wxCommandEvent& event)
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

	int i;
	m_map->SetWidth(o_spinWidth->GetValue());
	m_map->SetHeight(o_spinHeight->GetValue());
	for (i = 0; i < TILESET_LIMIT; i++)
		if (o_radioTileset[i]->GetValue())
			m_map->SetTileset(i);

	EndModal(wxID_OK);
	Destroy();
}

void DialogSettings::EvButton_Cancel(wxCommandEvent& event)
{
	EndModal(wxID_CANCEL);
	Destroy();
}
