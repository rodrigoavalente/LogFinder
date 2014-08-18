#include "LogFinderFrame.h"
#include "LogFinderApp.h"


wxBEGIN_EVENT_TABLE(LogFinderFrame, wxFrame)
    EVT_MENU(LogFinderFrame::ID_MAINWINDOW, LogFinderFrame::OnHello)
    EVT_MENU(wxID_ABOUT, LogFinderFrame::OnAbout)
    EVT_MENU(wxID_EXIT, LogFinderFrame::OnExit)
    EVT_BUTTON(LogFinderFrame::ID_FILE_BUTTON, LogFinderFrame::OnFileButtonPress)
    EVT_BUTTON(LogFinderFrame::ID_SEARCH_BUTTON, LogFinderFrame::OnSearchButtonPress)
    EVT_TEXT_ENTER(LogFinderFrame::ID_WORD_SEARCH, LogFinderFrame::OnSearchButtonPress)
    EVT_BUTTON(LogFinderFrame::ID_EXPORT_BUTTON, LogFinderFrame::OnExportButtonPress)
    EVT_CHAR_HOOK(LogFinderFrame::OnTabKeyPress)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(LogFinderApp);
