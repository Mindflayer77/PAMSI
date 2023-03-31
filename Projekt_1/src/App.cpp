// wxWidgets "Hello World" Program

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/notebook.h>
#include <wx/splitter.h>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <fstream>
#include <iostream>

const wxString appName = "Project number 1";

class MyApp : public wxApp
{
  public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
  public:
    MyFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style);

  private:
    wxMenu *menuFile;
    wxMenu *menuHelp;
    wxMenuBar *menuBar;
    wxStatusBar *statBar;

    wxPanel *panel;
    wxPanel *left;  // Lewa kolumna GUI
    wxPanel *right; // Prawa kolumna GUI
    wxSplitterWindow *splitter;

    wxPanel *rightTop;    // Prawa kolumna – góra
    wxPanel *rightBottom; // Prawa kolumna – dół
    wxSplitterWindow *splitterRight;

    wxTextCtrl *editor;

    wxTextCtrl *console;

    wxPanel *leftTop;
    wxPanel *leftBottom;
    wxSplitterWindow *splitterLeft;

    wxButton *send;
    wxButton *receive;

    // wxNotebook *container;

  private:
    void OnHello(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnSend(wxCommandEvent &event);
    void OnReceive(wxCommandEvent &event);
    void OnNewFile(wxCommandEvent &event);

  private:
    DECLARE_EVENT_TABLE();
};

wxIMPLEMENT_APP(MyApp);

enum
{
    ID_Hello = wxID_HIGHEST + 1,
    ID_MAIN_WINDOW,
    ID_EXIT,
    ID_CONSOLE,
    ID_CONTAINER,
    ID_EDITOR,
    ID_BUTTON_SEND,
    ID_BUTTON_RECEIVE,
    ID_NEW_FILE
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_Hello, MyFrame::OnHello)
EVT_MENU(ID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_BUTTON(ID_BUTTON_SEND, MyFrame::OnSend)
EVT_BUTTON(ID_BUTTON_RECEIVE, MyFrame::OnReceive)
EVT_MENU(ID_NEW_FILE, MyFrame::OnNewFile)
END_EVENT_TABLE()

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame(nullptr, ID_MAIN_WINDOW, appName, wxPoint(400, 150), wxSize(800, 600),
                                 wxCAPTION | wxMAXIMIZE_BOX | wxMINIMIZE_BOX | wxCLOSE_BOX | wxRESIZE_BORDER);
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size,
                 long style)
    : wxFrame(parent, id, title, pos, size, style)
{
    menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(ID_EXIT, wxT("&Close the application\tCtrl-Q"), wxT("Closes the application"));
    menuFile->AppendSeparator();
    menuFile->Append(ID_NEW_FILE, wxT("&Create a new file\tCtrl-N"), wxT("Creates a new file"));

    menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    statBar = CreateStatusBar(2, wxSTB_DEFAULT_STYLE);
    int width[] = {-1, 200};
    statBar->SetFieldsCount(2, width);
    statBar->SetStatusText("Welcome to my Application!", 0);
    statBar->SetStatusText("By Mateusz Biedka", 1);
    this->SetStatusBar(statBar);

    // Sizer main frame
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(mainSizer);
    panel = new wxPanel(this);
    // Sizer main panel
    wxBoxSizer *panelSizer = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(panelSizer);
    mainSizer->Add(panel, 1, wxEXPAND | wxALL, 0);

    splitter = new wxSplitterWindow(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH | wxSP_NO_XP_THEME);
    panelSizer->Add(splitter, 1, wxEXPAND | wxALL, 0);
    left = new wxPanel(splitter, wxID_ANY);
    right = new wxPanel(splitter, wxID_ANY);
    left->SetMinSize(wxSize(200, -1));
    right->SetMinSize(wxSize(200, -1));
    splitter->SplitVertically(left, right, 250);

    // Sizer prawej kolumy
    wxBoxSizer *rightSizer = new wxBoxSizer(wxVERTICAL);
    right->SetSizer(rightSizer);
    splitterRight =
        new wxSplitterWindow(right, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH | wxSP_NO_XP_THEME);
    rightSizer->Add(splitterRight, 1, wxEXPAND | wxALL, 0);
    rightTop = new wxPanel(splitterRight, wxID_ANY);
    rightBottom = new wxPanel(splitterRight, wxID_ANY);
    rightTop->SetMinSize(wxSize(-1, 200));
    rightBottom->SetMinSize(wxSize(-1, 100));
    splitterRight->SplitHorizontally(rightTop, rightBottom, (this->GetSize().GetHeight() - 120));

    // Sizer lewej kolumny
    wxBoxSizer *left_sizer = new wxBoxSizer(wxVERTICAL);
    left->SetSizer(left_sizer);
    // Sizer obszaru edytora
    wxBoxSizer *rightTop_sizer = new wxBoxSizer(wxVERTICAL);
    rightTop->SetSizer(rightTop_sizer);
    // Sizer obszaru konsoli
    wxBoxSizer *rightBottom_sizer = new wxBoxSizer(wxVERTICAL);
    rightBottom->SetSizer(rightBottom_sizer);

    // konsola
    console = new wxTextCtrl(rightBottom, ID_CONSOLE, wxEmptyString, wxDefaultPosition, wxDefaultSize,
                             wxTE_READONLY | wxTE_MULTILINE);
    rightBottom_sizer->Add(console, 1, wxEXPAND | wxALL, 0);
    wxLog::SetActiveTarget(new wxLogTextCtrl(console));

    // container = new wxNotebook(rightTop, ID_CONTAINER);
    // container->SetImageList(img); // Lista obrazów drzewa projektu
    // rightTop_sizer->Add(container, 1, wxEXPAND | wxALL, 0);
    editor = new wxTextCtrl(rightTop, ID_EDITOR, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    rightTop_sizer->Add(editor, 1, wxEXPAND | wxALL, 0);

    splitterLeft =
        new wxSplitterWindow(left, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DSASH | wxSP_NO_XP_THEME);
    left_sizer->Add(splitterLeft, 1, wxEXPAND | wxALL, 0);
    leftTop = new wxPanel(splitterLeft, wxID_ANY);
    leftBottom = new wxPanel(splitterLeft, wxID_ANY);
    leftTop->SetMinSize(wxSize(-1, 100));
    leftBottom->SetMinSize(wxSize(-1, 100));
    splitterLeft->SplitHorizontally(leftTop, leftBottom);
    wxBoxSizer *leftTop_sizer = new wxBoxSizer(wxVERTICAL);
    leftTop->SetSizer(leftTop_sizer);
    wxBoxSizer *leftBottom_sizer = new wxBoxSizer(wxVERTICAL);
    leftBottom->SetSizer(leftBottom_sizer);
    send = new wxButton(leftTop, ID_BUTTON_SEND, wxT("Send Data"), wxDefaultPosition, wxSize(200, 200));
    leftTop_sizer->Add(send, 1, wxEXPAND | wxALL, 0);
    receive = new wxButton(leftBottom, ID_BUTTON_RECEIVE, wxT("Receive Data"), wxDefaultPosition, wxDefaultSize);
    leftBottom_sizer->Add(receive, 1, wxEXPAND | wxALL, 0);
}

void MyFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a wxWidgets application implementing a priority queue", "About application",
                 wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent &event)
{
    wxLogMessage("Hello there!");
}

void MyFrame::OnSend(wxCommandEvent &event)
{
    wxString data;
    int line = 0;
    int numLines = editor->GetNumberOfLines();
    std::ofstream ostrm("../txt/out.txt", std::ios::out | std::ios::app);
    while (line != numLines)
    {
        try
        {
            data = editor->GetLineText(line++);
            ostrm << data;
            if (line != numLines)
                ostrm << "\n";
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            ostrm.close();
            event.Skip();
        }
    }
    ostrm.close();
    editor->Clear();
    *console << wxT("Sending data...\n");
    statBar->SetStatusText(wxT("Data send successfully"));
}

void MyFrame::OnReceive(wxCommandEvent &event)
{
    std::string data = "";
    std::ifstream istrm("../txt/out.txt", std::ios::in);
    while (!istrm.eof())
    {
        try
        {
            istrm >> data;
            *editor << data << " ";
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            istrm.close();
            event.Skip();
        }
    }
    istrm.close();
    *console << wxT("Receiving data...\n");
    statBar->SetStatusText(wxT("Data received successfully"));
}

void MyFrame::OnNewFile(wxCommandEvent &event)
{
    editor->Clear();
    statBar->SetStatusText(wxT("Created a new file"));
    *console << wxT("Creating a new file...\n");
}