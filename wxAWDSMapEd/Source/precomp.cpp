#include "precomp.h"

// This is the cpp for the precompiled header.
// Add includes to precomp.h.



// Global variables.

wxString g_messageboxTitle;
wxString g_version;
wxString g_appname;
wxString g_clipboardstring;

bool g_infoVolumeEnable;
int g_infoVolume;
int g_infoDefaultWidth;
int g_infoDefaultHeight;
int g_infoDefaultTerrain;
int g_infoDefaultTileset;
wxString g_infoDefaultAuthor;
int g_infoUndoLimit;
bool g_infoDrawCursor;


// Global functions.

wxString ConvertToString(long number)
{
	wxString buffer;
	buffer << number;
	return buffer;
}

long ConvertToNumber(wxString string)
{
	long val;
	if (!string.ToLong(&val))
		val = 0;
	return val;
}

long power(long a, long b)
{
	long temp = 1;
	for (long i = 0; i < b; i++)
		temp *= a;
	return temp;
}

bool DoNothing()
{
	return true;
}
