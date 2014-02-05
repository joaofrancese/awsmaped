#pragma once

class AppMain: public wxApp
{
    virtual bool OnInit();
	bool TimeActivation();
	bool LoadPreferences();
};
