// Created 2021 Baltazarus
// wxpad.cpp was something like unneeded, but I added it like starting point of an app.

#include "MainApp.h"

wxBEGIN_EVENT_TABLE(AppFrame, wxFrame)
	EVT_MENU(ID_New, AppFrame::OnNew)
	EVT_MENU(ID_Open, AppFrame::OnOpen)
	EVT_MENU(ID_Save, AppFrame::OnSave)
	EVT_MENU(ID_SaveAs, AppFrame::OnSaveAs)
	EVT_MENU(wxID_EXIT, AppFrame::OnExit)
	EVT_MENU(ID_About, AppFrame::OnAbout)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MainApp);

