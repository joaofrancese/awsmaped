#include "precomp.h"
#include "DialogStatus.h"


BEGIN_EVENT_TABLE(DialogStatus, wxDialog)

	// Event handling: ButtonClick
	EVT_BUTTON(wxID_CANCEL,			DialogStatus::EvButton_Close)

END_EVENT_TABLE()



DialogStatus::DialogStatus(wxWindow* parent, Map* map, int id, const wxPoint& pos)
	: wxDialog(parent, id, "", pos, wxDefaultSize, wxCAPTION | wxCLOSE_BOX | wxSYSTEM_MENU)
{
	int width = PLATSPEC(410, 520, 410);
	int height = 260;
	
	int vertlinepos = PLATSPEC(100, 135, 100);
	int colfirstpos = vertlinepos + PLATSPEC(5, 20, 5);
	int colwidth = PLATSPEC(50, 60, 50);
	
	// SetClientSize is in the end of the method.
	SetTitle("Map Status");
	m_map = map;

	int i, j, k;
	wxFont fontBold = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
		fontBold.SetWeight(wxFONTWEIGHT_BOLD);
	wxColour colourDefault = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);
	wxColour colourDisabled = wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT);

	new wxStaticLine(this, wxID_ANY, wxPoint(5, 30), wxSize(width - 10, 2), wxLI_HORIZONTAL);
	new wxStaticLine(this, wxID_ANY, wxPoint(vertlinepos, 5), wxSize(2, 190), wxLI_VERTICAL);

	o_labelArmies[ARMY_ORANGE_STAR] = new wxStaticText(this, wxID_ANY, "Orange Star", wxPoint(10, 45));
	o_labelArmies[ARMY_BLUE_MOON] = new wxStaticText(this, wxID_ANY, "Blue Moon", wxPoint(10, 70));
	o_labelArmies[ARMY_GREEN_EARTH] = new wxStaticText(this, wxID_ANY, "Green Earth", wxPoint(10, 95));
	o_labelArmies[ARMY_YELLOW_COMET] = new wxStaticText(this, wxID_ANY, "Yellow Comet", wxPoint(10, 120));
	o_labelArmies[ARMY_BLACK_HOLE] = new wxStaticText(this, wxID_ANY, "Black Hole", wxPoint(10, 145));
	o_labelArmies[ARMY_NEUTRAL] = new wxStaticText(this, wxID_ANY, "Neutral", wxPoint(10, 170));
	for (i = 0; i <= ARMY_NEUTRAL; i++)
	{
		o_labelArmies[i]->SetFont(fontBold);
		if ((i == ARMY_NEUTRAL || !Calculate(Element(BUILDING_HQ), i)) && !Calculate(Element(BUILDING_LAB), i))
			o_labelArmies[i]->SetForegroundColour(colourDisabled);
	}

	o_labelColumns[0] = new wxStaticText(this, wxID_ANY, "Cities", wxPoint(colfirstpos + (colwidth * 0), 10), wxSize(colwidth, -1), wxALIGN_CENTER | wxST_NO_AUTORESIZE);
	o_labelColumns[1] = new wxStaticText(this, wxID_ANY, "Bases", wxPoint(colfirstpos + (colwidth * 1), 10), wxSize(colwidth, -1), wxALIGN_CENTER | wxST_NO_AUTORESIZE);
	o_labelColumns[2] = new wxStaticText(this, wxID_ANY, "Ports", wxPoint(colfirstpos + (colwidth * 2), 10), wxSize(colwidth, -1), wxALIGN_CENTER | wxST_NO_AUTORESIZE);
	o_labelColumns[3] = new wxStaticText(this, wxID_ANY, "Airports", wxPoint(colfirstpos + (colwidth * 3), 10), wxSize(colwidth, -1), wxALIGN_CENTER | wxST_NO_AUTORESIZE);
	o_labelColumns[4] = new wxStaticText(this, wxID_ANY, "Towers", wxPoint(colfirstpos + (colwidth * 4), 10), wxSize(colwidth, -1), wxALIGN_CENTER | wxST_NO_AUTORESIZE);
	o_labelColumns[5] = new wxStaticText(this, wxID_ANY, "Units", wxPoint(colfirstpos + (colwidth * 5), 10), wxSize(colwidth, -1), wxALIGN_CENTER | wxST_NO_AUTORESIZE);
	for (i = 0; i < STATUS_COLS; i++)
	{
		o_labelColumns[i]->SetFont(fontBold);
		o_labelColumns[i]->SetForegroundColour(colourDisabled);
	}

	Element elements[STATUS_COLS];
	elements[0] = BUILDING_CITY;
	elements[1] = BUILDING_BASE;
	elements[2] = BUILDING_PORT;
	elements[3] = BUILDING_AIRPORT;
	elements[4] = BUILDING_TOWER;
	elements[5] = UNIT_INFANTRY;

	o_labelNoHQ = 0;
	for (i = 0; i < STATUS_COLS; i++)
		for (j = 0; j <= ARMY_NEUTRAL; j++)
		{
			o_labelNumbers[i][j] = new wxStaticText(this, wxID_ANY, "", wxPoint(colfirstpos + (i * colwidth), 45 + (j * 25)), wxSize(50, -1), wxALIGN_CENTER | wxST_NO_AUTORESIZE);
			k = Calculate(elements[i], j);
			o_labelNumbers[i][j]->SetLabel(ConvertToString(k));
			if (!k)
				o_labelNumbers[i][j]->SetForegroundColour(colourDisabled);
			else
			{
				if (o_labelArmies[j]->GetForegroundColour() == colourDisabled && j != ARMY_NEUTRAL)
				{
					o_labelArmies[j]->SetLabel(o_labelArmies[j]->GetLabel() + "*");
					if (!o_labelNoHQ)
					{
						o_labelNoHQ = new wxStaticText(this, wxID_ANY, "*Army with no HQ or Lab.", wxPoint(10, height - 60));
						height += 30;
					}
				}
				o_labelColumns[i]->SetForegroundColour(colourDefault);
				o_labelArmies[j]->SetForegroundColour(colourDefault);
			}
		}
	o_labelNumbers[STATUS_COLS - 1][ARMY_NEUTRAL]->Hide();

	k = Calculate(Element(TERRAIN_SEAM));
	if (k)
	{
		o_labelSeams = new wxStaticText(this, wxID_ANY, wxString("Pipe seams: ") + ConvertToString(k), wxPoint(10, height - 60));
		height += 20;
	}

	k = Calculate(Element(BUILDING_SILO));
	if (k)
	{
		o_labelSilos = new wxStaticText(this, wxID_ANY, wxString("Missile silos: ") + ConvertToString(k), wxPoint(10, height - 60));
		height += 20;
	}

	k = Calculate(BUILDING_CITY, -2);
	if (k == 1)
		o_labelTotalProperties = new wxStaticText(this, wxID_ANY, wxString("Total: ") + ConvertToString(k) + " property.", wxPoint(10, height - 55), wxSize(width - 10, -1));
	else if (k > PROPERTIES_LIMIT)
		o_labelTotalProperties = new wxStaticText(this, wxID_ANY, wxString("Total: ") + ConvertToString(k) + " properties (shouldn't exceed " + ConvertToString(PROPERTIES_LIMIT) + ").", wxPoint(10, height - 55), wxSize(width - 10, -1));
	else
		o_labelTotalProperties = new wxStaticText(this, wxID_ANY, wxString("Total: ") + ConvertToString(k) + " properties.", wxPoint(10, height - 55), wxSize(width - 10, -1));
	o_labelTotalProperties->SetFont(fontBold);


	int compatsize, compat1elem, compat2elem, compat3elem;
	bool compatarmies;
	compatsize = m_map->IsCompatibleSize(MAPTYPE_AW1);
	compat1elem = m_map->IsCompatibleElements(MAPTYPE_AW1);
	compat2elem = m_map->IsCompatibleElements(MAPTYPE_AW2);
	compat3elem = m_map->IsCompatibleElements(MAPTYPE_AWDS);
	compatarmies = !((o_labelArmies[ARMY_ORANGE_STAR]->GetForegroundColour() != colourDisabled)
				&& (o_labelArmies[ARMY_BLUE_MOON]->GetForegroundColour() != colourDisabled)
				&& (o_labelArmies[ARMY_GREEN_EARTH]->GetForegroundColour() != colourDisabled)
				&& (o_labelArmies[ARMY_YELLOW_COMET]->GetForegroundColour() != colourDisabled)
				&& (o_labelArmies[ARMY_BLACK_HOLE]->GetForegroundColour() != colourDisabled));
	if (compatsize != COMPAT_OK || compat1elem != COMPAT_OK || compat2elem != COMPAT_OK || compat3elem != COMPAT_OK || !compatarmies)
	{
		height += 30;
		o_labelWarnings = new wxStaticText(this, wxID_ANY, "", wxPoint(10, height - 60));
		height -= 15;

		if (compatsize != COMPAT_OK)								// If the map size is compatible with old maps.
		{
			o_labelWarnings->SetLabel("This map's size is not compatible with AW, AW2 and AWDS.\n");
			height += 15;
		}

		if (compat3elem != COMPAT_OK)								// Assumes it's incompatible with older formats as well.
		{
			o_labelWarnings->SetLabel(o_labelWarnings->GetLabel() + "This map contains tiles incompatible with AW1, AW2 and AWDS.\n");
			height += 15;
		}
		else if (compat2elem != COMPAT_OK)
		{
			o_labelWarnings->SetLabel(o_labelWarnings->GetLabel() + "This map contains tiles incompatible with Advance Wars and Advance Wars 2.\n");
			height += 15;
		}
		else if (compat1elem != COMPAT_OK)
		{
			o_labelWarnings->SetLabel(o_labelWarnings->GetLabel() + "This map contains tiles incompatible with the original Advance Wars.\n");
			height += 15;
		}

		if (!compatarmies)
		{
			o_labelWarnings->SetLabel(o_labelWarnings->GetLabel() + "Maps with five armies cannot be used in the real games.");
			height += 15;
		}
	}

	o_buttonClose = new wxButton(this, wxID_CANCEL, "&Close", wxPoint(width - 80, height - 35), wxSize(70, 25));
    o_buttonClose->SetDefault();
    
	SetClientSize(width, height);
}



//////////////////////////////////////////////////////////
//                                                      //
//  EVENT HANDLING:  ButtonClick                        //
//                                                      //
//////////////////////////////////////////////////////////

void DialogStatus::EvButton_Close(wxCommandEvent& event)
{
	Destroy();
}



//////////////////////////////////////////////////////////
//                                                      //
//  OTHER MISC FUNCTIONS.                               //
//                                                      //
//////////////////////////////////////////////////////////

int DialogStatus::Calculate(Element element, int army)
{
	int i, j, k;
	k = 0;

	if (element.IsUnit())
	{
		if(army == ARMY_NEUTRAL)
			return 0;
		for (i = 0; i < m_map->GetWidth(); i++)
			for (j = 0; j < m_map->GetHeight(); j++)
				if (m_map->GetForeground(i, j).IsUnitNonEmpty() && m_map->GetForeground(i, j).GetArmy() == army)
						k++;
	}
	else if (element == TERRAIN_SEAM || element == BUILDING_SILO)
	{
		for (i = 0; i < m_map->GetWidth(); i++)
			for (j = 0; j < m_map->GetHeight(); j++)
				if (m_map->GetBackground(i, j).Simplify() == element)
					k++;
	}
	else if (element.IsBuilding() && army < 0)
	{
		for (i = 0; i < m_map->GetWidth(); i++)
			for (j = 0; j < m_map->GetHeight(); j++)
				if (m_map->GetBackground(i, j).IsBuilding() || m_map->GetBackground(i, j) == TERRAIN_SEAM)
					k++;
	}
	else
	{
		element.ChangeArmy(army);
		for (i = 0; i < m_map->GetWidth(); i++)
			for (j = 0; j < m_map->GetHeight(); j++)
				if (m_map->GetBackground(i, j) == element)
					k++;
	}
	return k;
}
