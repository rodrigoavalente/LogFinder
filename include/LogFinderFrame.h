#ifndef LOGFINDERFRAME_H
#define LOGFINDERFRAME_H

#include "LogFinder.h"
#include <wx/ffile.h>
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP


class LogFinderFrame : public wxFrame
{
    public:
        LogFinderFrame(const wxString& Title, const wxPoint& Position, const wxSize& WindowSize);

        enum
        {
            ID_MAINWINDOW = 1,
            ID_LABEL_PATH,
            ID_LABEL_SEARCH,
            ID_TEXT_FILE_PATH,
            ID_FILE_BUTTON,
            ID_WORD_SEARCH,
            ID_SEARCH_BUTTON,
            ID_TEXT_SEARCH_OUTPUT,
            ID_SEARCH_TYPE_BOX,
            ID_EXPORT_BUTTON,
        };

    private:

        wxTextCtrl* FilePath;
        wxStaticText* LabelPath;
        wxButton* FileButton;

        wxTextCtrl* WordField;
        wxStaticText* LabelWord;
        wxButton* SearchButton;

        wxTextCtrl* SearchOutput;

        wxPanel* FramePanel;

        wxFileDialog* FileDialog;

        wxRadioBox* TypeSearch;

        wxButton* ExportButton;

        std::ifstream MyFile;
        std::list<std::string> Search;

        void OnHello(wxCommandEvent& Event);
        void OnExit(wxCommandEvent& Event);
        void OnAbout(wxCommandEvent& Event);
        void OnFileButtonPress(wxCommandEvent& Event);
        void OnSearchButtonPress(wxCommandEvent& Event);
        void OnExportButtonPress(wxCommandEvent& Event);
        void OnTabKeyPress(wxKeyEvent& Event);

        wxDECLARE_EVENT_TABLE();
};

#endif // LOGFINDERFRAME_H
