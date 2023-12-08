#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>


wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	int startWidth = 1100;
	int startHeight = 650;
	MainFrame* mainFrame = new MainFrame("GUI", startWidth, startHeight);

	mainFrame->SetClientSize(startWidth, startHeight);



	mainFrame->Center();
	mainFrame->Show();
	return true;
}