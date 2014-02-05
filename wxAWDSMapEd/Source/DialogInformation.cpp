#include "precomp.h"
#include "DialogInformation.h"


BEGIN_EVENT_TABLE(DialogInformation, wxDialog)

	// Event handling: ButtonClick
	EVT_BUTTON(wxID_OK,				DialogInformation::EvButton_OK)
	EVT_BUTTON(wxID_CANCEL,			DialogInformation::EvButton_Cancel)

END_EVENT_TABLE()



DialogInformation::DialogInformation(wxWindow* parent, Map* map, int id, const wxPoint& pos)
	: wxDialog(parent, id, "", pos, wxDefaultSize, wxCAPTION | wxCLOSE_BOX | wxSYSTEM_MENU)
{
	int width = 350;
	int height = 250;
	
	SetClientSize(width, height);
	SetTitle("Map Information");
	m_map = map;

	new wxStaticText(this, wxID_ANY, "Map name:", wxPoint(10, 10));
		o_textName = new wxTextCtrl(this, ID_TEXT_NAME, "", wxPoint(100, 10), wxSize(width - 110, -1));
		o_textName->SetMaxLength(NAME_MAX_LEN);
	new wxStaticText(this, wxID_ANY, "Author:", wxPoint(10, 35));
		o_textAuthor = new wxTextCtrl(this, ID_TEXT_AUTHOR, "", wxPoint(100, 35), wxSize(width - 110, -1));
		o_textAuthor->SetMaxLength(AUTHOR_MAX_LEN);
	new wxStaticText(this, wxID_ANY, "Description:", wxPoint(10, 60));
		o_textDescription = new wxTextCtrl(this, ID_TEXT_DESCRIPTION, "", wxPoint(100, 60), wxSize(width - 110, height - 110), wxTE_MULTILINE);
		o_textDescription->SetMaxLength(DESCRIPTION_MAX_LEN);
	o_buttonOK = new wxButton(this, wxID_OK, "&OK", wxPoint(width - PLATSPEC(160, 180, 160), height - 35), wxSize(PLATSPEC(70, 70, 70), 25));
	o_buttonCancel = new wxButton(this, wxID_CANCEL, "&Cancel", wxPoint(width - PLATSPEC(80, 100, 80), height - 35), wxSize(PLATSPEC(70, 90, 70), 25));

	o_textName->SetValue(m_map->GetName());
	o_textAuthor->SetValue(m_map->GetAuthor());
	o_textDescription->SetValue(m_map->GetDescription());
    o_buttonOK->SetDefault();
}



//////////////////////////////////////////////////////////
//                                                      //
//  EVENT HANDLING:  ButtonClick                        //
//                                                      //
//////////////////////////////////////////////////////////

void DialogInformation::EvButton_OK(wxCommandEvent& event)
{
	m_map->SetName(o_textName->GetValue());
	m_map->SetAuthor(o_textAuthor->GetValue());
	m_map->SetDescription(o_textDescription->GetValue());
	if (m_map->GetDescription().Length() > DESCRIPTION_MAX_LEN)
		m_map->SetDescription(m_map->GetDescription().Truncate(DESCRIPTION_MAX_LEN));

	EndModal(wxID_OK);
	Destroy();
}

void DialogInformation::EvButton_Cancel(wxCommandEvent& event)
{
	EndModal(wxID_CANCEL);
	Destroy();
}
