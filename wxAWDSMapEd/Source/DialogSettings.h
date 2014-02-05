#pragma once

#include "Map.h"


class DialogSettings: public wxDialog
{
public:
	DialogSettings(wxWindow* parent, Map* map, int id = wxID_ANY, const wxPoint& pos = wxDefaultPosition);

	Map* m_map;

	wxSpinCtrl* o_spinWidth;
	wxSpinCtrl* o_spinHeight;
	wxRadioButton* o_radioTileset[TILESET_LIMIT];
	wxButton* o_buttonOK;
	wxButton* o_buttonCancel;



	//Event handling: ButtonClick
	void EvButton_OK(wxCommandEvent& event);
	void EvButton_Cancel(wxCommandEvent& event);


	enum enumIDs
	{
		ID_SPIN_WIDTH,
		ID_SPIN_HEIGHT,
		ID_RADIO_TILESET
	};


private:
	DECLARE_EVENT_TABLE()
};
