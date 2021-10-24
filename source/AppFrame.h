#ifndef FRAME_H
#define FRAME_H
#include <wx/wx.h>
#include <sstream>
#include <fstream>
#include <cstdlib>

class AppFrame : public wxFrame
{
private:
	static bool bFileOpened;
	static std::string RuntimePath_OpenedFilename;
	
public:
	AppFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	wxTextCtrl* MainTextArea;
	wxStatusBar* MainStatusBar;

private:
	void OnNew(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnSaveAs(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
};

enum
{
	ID_New = 1,
	ID_Open,
	ID_Save,
	ID_SaveAs,
	ID_About,

	ID_TEXTCTRL_Main,
	ID_STATUSBAR_Main
};

#endif
