#include "AppFrame.h"

bool AppFrame::bFileOpened;
std::string AppFrame::RuntimePath_OpenedFilename;

AppFrame::AppFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	wxMenu* menu_file = new wxMenu;
	menu_file->Append(ID_New, "&New\tCtrl-N", "Creates a new file.");
	menu_file->Append(ID_Open, "&Open\tCtrl-O", "Opens a file.");
	menu_file->Append(ID_Save, "&Save\tCtrl-S", "Saves a file.");
	menu_file->Append(ID_SaveAs, "Sa&ve As\tCtrl-V", "Saves a file always with dialog.");
	menu_file->AppendSeparator();
	menu_file->Append(wxID_EXIT, "&Exit\tAlt-F4", "Close the application");

	wxMenu* menu_help = new wxMenu;
	menu_help->AppendSeparator();
	menu_help->Append(ID_About, "Abou&t", "About this application.");
	
	wxMenuBar* mb = new wxMenuBar;
	mb->Append(menu_file, "&File");
	mb->Append(menu_help, "&Help");
	SetMenuBar(mb);

	this->MainTextArea = new wxTextCtrl(
		this, ID_TEXTCTRL_Main, wxT(""), 
		wxPoint(0, 0), wxSize(300, 300), wxTE_MULTILINE | wxTE_DONTWRAP
	);

	int widths[] = { 300, 400 };
	this->MainStatusBar = this->CreateStatusBar(2, wxSTB_DEFAULT_STYLE);
	this->MainStatusBar->SetStatusWidths(2, widths);
	this->MainStatusBar->SetStatusText("No file opened.", 1);
	return;
}

void AppFrame::OnNew(wxCommandEvent& event)
{
	this->MainTextArea->Clear();
	if(this->bFileOpened)
	{
		this->bFileOpened = false;
		this->RuntimePath_OpenedFilename = std::string();
	}
	this->MainStatusBar->SetStatusText("No file opened.", 1);
	return;
}

void AppFrame::OnOpen(wxCommandEvent& event)
{
	wxFileDialog ofn(this, "Open Text File", "", "", "Text File (*.txt)|*.txt|All Files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if(ofn.ShowModal() == wxID_CANCEL)
		return;

	std::ostringstream oss;
	std::string path(ofn.GetPath());

	std::fstream file;
	file.open(path.c_str(), std::ios::in | std::ios::out);
	if(file.is_open())
	{
		if(!bFileOpened)
		{
			this->bFileOpened = true;
			this->RuntimePath_OpenedFilename = path;
			this->MainStatusBar->SetStatusText(path.c_str(), 1);
		}

		this->MainTextArea->Clear();
		oss << file.rdbuf();
		this->MainTextArea->WriteText(oss.str().c_str());
		file.close();
	}
	else
	{
		wxMessageBox("Cannot open a file!", "Error!", wxICON_ERROR | wxOK);
		return;
	}
	return;
}

void AppFrame::OnSave(wxCommandEvent& event)
{
	std::ostringstream oss_total_text;

	// Get number of lines.
	int lines_num = this->MainTextArea->GetNumberOfLines();
	if(lines_num < 1);
	else
	{
		for(int i = 0; i < lines_num; ++i)
			oss_total_text << this->MainTextArea->GetLineText(i) << std::endl;
	}

	std::string path;
	if(!this->bFileOpened)
	{
		wxFileDialog sfn(this, "Save File", "", "", "Text File (*.txt)|*.txt|All Files (*.*)|*.*", wxFD_SAVE);
		if(sfn.ShowModal() == wxID_CANCEL)
			return;

		std::string path_temp(sfn.GetPath());
		path = path_temp;
	}
	else
		path = this->RuntimePath_OpenedFilename;

	std::ofstream file(path.c_str());
	if(file.is_open())
	{
		if(!bFileOpened)
		{
			this->bFileOpened = true;
			this->RuntimePath_OpenedFilename = path;
			this->MainStatusBar->SetStatusText(path.c_str(), 1);
		}

		file << oss_total_text.str().c_str();
		file.close();
	}
	else
		wxMessageBox("Cannot save the file!\nFile not found.", "Error!", wxOK | wxICON_ERROR);
	return;
}

void AppFrame::OnSaveAs(wxCommandEvent& event)
{
	std::ostringstream oss_total_text;

	// Get number of lines.
	int lines_num = this->MainTextArea->GetNumberOfLines();
	if(lines_num < 1);
	else
	{
		for(int i = 0; i < lines_num; ++i)
			oss_total_text << this->MainTextArea->GetLineText(i) << std::endl;
	}

	wxFileDialog sfn(this, "Save File", "", "", "Text File (*.txt)|*.txt|All Files (*.*)|*.*", wxFD_SAVE);
	if(sfn.ShowModal() == wxID_CANCEL)
		return;
	std::ofstream file(sfn.GetPath());
	if(file.is_open())
	{
		this->bFileOpened = true;
		RuntimePath_OpenedFilename = sfn.GetPath();
		this->MainStatusBar->SetStatusText(sfn.GetPath(), 1);
		file << oss_total_text.str().c_str();
		file.close();
	}
	else
		wxMessageBox("Cannot save file!\nFile not found.", "Error!", wxOK | wxICON_ERROR);
	return;
}

void AppFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("Created 2021 Baltazarus", "About", wxOK | wxICON_INFORMATION);
	return;
}

void AppFrame::OnExit(wxCommandEvent& event)
{
	int confirm = wxMessageBox("Are you sure you want to exit?", "Exit?", wxYES_NO | wxICON_QUESTION);
	if(confirm == wxYES)
	{
		this->RuntimePath_OpenedFilename = std::string();
		Close(true);
	}
	return;
}
