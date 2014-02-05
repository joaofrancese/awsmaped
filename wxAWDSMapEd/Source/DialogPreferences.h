#pragma once


class DialogPreferences: public wxDialog
{
public:
	DialogPreferences(wxWindow* parent, int id = wxID_ANY, const wxPoint& pos = wxDefaultPosition);

	wxStaticBox* o_boxVolume;
		wxCheckBox* o_checkVolume;
		wxSlider* o_sliderVolume;
		wxStaticText* o_labelVolume;
	wxStaticBox* o_boxOthers;
		wxSpinCtrl* o_spinWidth;
		wxSpinCtrl* o_spinHeight;
		wxComboBox* o_comboTerrain;
		wxComboBox* o_comboTileset;
		wxTextCtrl* o_textAuthor;
		wxComboBox* o_comboUndo;
		wxCheckBox* o_checkDrawCursor;
	wxButton* o_buttonOK;
	wxButton* o_buttonCancel;



	//Event handling: ButtonClick
	void EvButton_OK(wxCommandEvent& event);
	void EvButton_Cancel(wxCommandEvent& event);

	//Event handling: Others
	void EvChange_VolumeSlider(wxScrollEvent& event);
	void EvChange_VolumeEnable(wxCommandEvent& event);


	
	//Other misc methods.
	bool UpdateVolumeEnable();
	bool UpdateVolumeValue();


	enum enumIDs
	{
		ID_VOLUME_SLIDER,
		ID_VOLUME_ENABLE,
		ID_DEFAULT_WIDTH,
		ID_DEFAULT_HEIGHT,
		ID_DEFAULT_TERRAIN,
		ID_DEFAULT_TILESET,
		ID_DEFAULT_AUTHOR,
		ID_UNDO_LIMIT,
		ID_DRAW_CURSOR
	};


private:
	DECLARE_EVENT_TABLE()
};
