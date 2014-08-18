#include "LogFinderApp.h"

bool LogFinderApp::OnInit()
{
    LogFinderFrame* MainWindow = new LogFinderFrame("Pesquisa Logs", wxPoint(wxDefaultPosition), wxSize(730, 650));
    MainWindow->Show();
    return true;
}
