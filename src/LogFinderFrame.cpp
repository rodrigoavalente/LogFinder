#include "LogFinderFrame.h"

LogFinderFrame::LogFinderFrame(const wxString& Title, const wxPoint& Position, const wxSize& WindowSize)
              :wxFrame(NULL, wxID_ANY, Title, Position, WindowSize)
{
    wxMenu *MenuFile = new wxMenu;
    MenuFile->Append(wxID_EXIT, "&Sair \tAlt-F4", "Sair");

    wxMenu *MenuHelp = new wxMenu;
    MenuHelp->Append(wxID_ABOUT, "&Ajuda \tF1", "Ajuda");

    wxMenuBar *MenuBar = new wxMenuBar;
    MenuBar->Append(MenuFile, "&Arquivo");
    MenuBar->Append(MenuHelp, "&Sobre");

    SetMenuBar(MenuBar);

    CreateStatusBar();
    SetStatusText("Bem vindo ao LogFinder!");

    LabelPath = new wxStaticText(this, ID_LABEL_PATH, "Arquivo:", wxPoint(25, 55));
    FilePath = new wxTextCtrl(this, ID_TEXT_FILE_PATH, wxEmptyString, wxPoint(75, 50), wxSize(250, 25));
    FileButton = new wxButton(this, ID_FILE_BUTTON, "Procurar",wxPoint(340, 49));

    LabelWord = new wxStaticText(this, ID_LABEL_SEARCH, "Buscar por:", wxPoint(10, 105));
    WordField = new wxTextCtrl(this, ID_WORD_SEARCH, wxEmptyString, wxPoint(75, 100), wxSize(250, 25), wxTE_PROCESS_ENTER);
    SearchButton = new wxButton(this, ID_SEARCH_BUTTON, "Buscar", wxPoint(340, 99));
    SearchOutput = new wxTextCtrl(this, ID_TEXT_SEARCH_OUTPUT, wxEmptyString, wxPoint(75, 200), wxSize(620, 350), wxTE_MULTILINE | wxTE_READONLY | wxTE_NOHIDESEL | wxHSCROLL);

    wxString choices[] = {"Sim", "Não"};
    TypeSearch = new wxRadioBox(this, ID_SEARCH_TYPE_BOX, "Diferenciar maiúsculas e minúsculas?", wxPoint(445, 33), wxSize(250, 100), 2, choices, 50, wxRA_VERTICAL);

    ExportButton = new wxButton(this, ID_EXPORT_BUTTON, "Salvar Pesquisa", wxPoint(595, 165));

    //FramePanel = new wxPanel(this, ID_MAINWINDOW, wxDefaultPosition, wxSize(730, 630));
}

void LogFinderFrame::OnExit(wxCommandEvent& Event)
{
    Close( true );
}

void LogFinderFrame::OnHello(wxCommandEvent& Event)
{
    wxLogMessage("Bem vindo ao LogFinder");
}

void LogFinderFrame::OnAbout(wxCommandEvent& Event)
{
    wxMessageBox("LogFinder: Encontra ocorrências em seus logs!");
}

void LogFinderFrame::OnFileButtonPress(wxCommandEvent& Event)
{
    FileDialog = new wxFileDialog(this, "Escolha o arquivo...", "", "", "Arquivos de texto (*.txt)|*.txt|Arquivos de log (*.log)|*.log", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    FileDialog->ShowModal();
    FilePath->SetValue( FileDialog->GetPath() );
    LogFinder::OpenFile(FileDialog->GetPath().c_str(), MyFile);
    if(MyFile.is_open())
        SetStatusText("Arquivo carregado com sucesso!");
    else
        SetStatusText("Falha ao carregar arquivo!");
}

void LogFinderFrame::OnSearchButtonPress(wxCommandEvent& Event)
{
    int BoxIndex = 0;

    if(!MyFile.is_open())
        LogFinder::OpenFile(FileDialog->GetPath().c_str(), MyFile);

    Search.clear();
    BoxIndex = TypeSearch->GetSelection();
    switch (BoxIndex)
    {
        case 0:
            Search = LogFinder::CaseSensitiveFind(MyFile, WordField->GetValue().ToStdString());
            break;
        case 1:
            Search = LogFinder::CaseInsensitiveFind(MyFile, WordField->GetValue().ToStdString());
            break;
    }
    SearchOutput->Clear();
    for(std::list<std::string>::const_iterator i = Search.begin(); i != Search.end(); ++i)
        SearchOutput->AppendText(*i + "\n");
    WordField->Clear();
}

void LogFinderFrame::OnExportButtonPress(wxCommandEvent& Event)
{
    FileDialog = new wxFileDialog(this, "Escolha onde salvar o arquivo...", "", "", "Arquivo de texto (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    FileDialog->ShowModal();
    LogFinder::ExportSearch(Search, FileDialog->GetPath().ToStdString());
    Search.clear();
    SearchOutput->Clear();
}

void LogFinderFrame::OnTabKeyPress(wxKeyEvent& Event)
{
    wxWindow *Window = FindFocus();

    if(Event.GetKeyCode() == WXK_TAB)
        {
            bool Backward = Event.ShiftDown();
            switch (Window->GetId())
            {
                case ID_TEXT_FILE_PATH:
                    if(Backward)
                        FindWindow(ID_EXPORT_BUTTON)->SetFocus();
                    else
                        FindWindow(ID_FILE_BUTTON)->SetFocus();
                    break;
                case ID_FILE_BUTTON:
                    if(Backward)
                        FindWindow(ID_TEXT_FILE_PATH)->SetFocus();
                    else
                        FindWindow(ID_WORD_SEARCH)->SetFocus();
                    break;
                case ID_WORD_SEARCH:
                    if(Backward)
                        FindWindow(ID_FILE_BUTTON)->SetFocus();
                    else
                        FindWindow(ID_SEARCH_BUTTON)->SetFocus();
                    break;
                case ID_SEARCH_BUTTON:
                    if(Backward)
                        FindWindow(ID_WORD_SEARCH)->SetFocus();
                    else
                        FindWindow(ID_EXPORT_BUTTON)->SetFocus();
                    break;
                case ID_EXPORT_BUTTON:
                    if(Backward)
                        FindWindow(ID_SEARCH_BUTTON)->SetFocus();
                    else
                        FindWindow(ID_TEXT_FILE_PATH)->SetFocus();
                    break;
                default:
                    if(Backward)
                        FindWindow(ID_EXPORT_BUTTON)->SetFocus();
                    else
                        FindWindow(ID_TEXT_FILE_PATH)->SetFocus();
            }
        }
}
