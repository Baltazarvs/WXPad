#include "MainApp.h"

bool MainApp::OnInit()
{
	AppFrame* frame = new AppFrame("WXPad", wxPoint(100, 100), wxSize(800, 600));
	frame->Show(true);
	return true;
}
