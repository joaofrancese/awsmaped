#pragma once

#include "Map.h"

#define STATUS_COLS	6


class DialogStatus: public wxDialog
{
public:
	DialogStatus(wxWindow* parent, Map* map, int id = wxID_ANY, const wxPoint& pos = wxDefaultPosition);

	Map* m_map;

	wxStaticText* o_labelArmies[ARMY_NEUTRAL + 1];
	wxStaticText* o_labelColumns[STATUS_COLS];
	wxStaticText* o_labelNumbers[STATUS_COLS][ARMY_NEUTRAL + 1];
	wxStaticText* o_labelNoHQ;
	wxStaticText* o_labelSeams;
	wxStaticText* o_labelSilos;
	wxStaticText* o_labelTotalProperties;
	wxStaticText* o_labelWarnings;
	wxButton* o_buttonClose;



	//Event handling: ButtonClick
	void EvButton_Close(wxCommandEvent& event);



	//Other misc methods.
	int Calculate(Element element, int army = -1);


private:
	DECLARE_EVENT_TABLE()
};
