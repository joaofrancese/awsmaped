#pragma once

#include "Map.h"


class DialogInformation: public wxDialog
{
public:
	DialogInformation(wxWindow* parent, Map* map, int id = wxID_ANY, const wxPoint& pos = wxDefaultPosition);

	Map* m_map;

	wxTextCtrl* o_textName;
	wxTextCtrl* o_textAuthor;
	wxTextCtrl* o_textDescription;
	wxButton* o_buttonOK;
	wxButton* o_buttonCancel;



	//Event handling: ButtonClick
	void EvButton_OK(wxCommandEvent& event);
	void EvButton_Cancel(wxCommandEvent& event);


	enum enumIDs
	{
		ID_TEXT_NAME,
		ID_TEXT_AUTHOR,
		ID_TEXT_DESCRIPTION
	};


private:
	DECLARE_EVENT_TABLE()
};
