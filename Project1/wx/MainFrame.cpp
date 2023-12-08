#pragma once

#include "MainFrame.h"
#include <wx/wx.h>
#include <SDL.h>
#include <memory>
#include <wx/image.h>
#include <wx/scrolwin.h>
#include <wx/scrolbar.h>
#include <vector>
#include "buttons/CustomButton.h"


enum
{
    //TAKEN ---------------
    //3 - game count, 100 - game count, 1000 - game count
    //53 - game count, 200 - game count, 2000 - game count
    //1300 - game count (krat 3.. level 1,2,3)
    ID_EXIT_GAME_BTN = 999,
    ID_PAUSE_GAME_BTN = 998,
    ID_EU_STAGE1_BTN = 555,
    ID_EU_STAGE2_BTN = 556,
    ID_MATHS_BTN = 557,
    ID_OPTIONGAME_BTN1 = 558,
    ID_OPTIONGAME_BTN2 = 559,
    ID_OPTIONGAME_BTN3 = 560,


};

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(ID_EXIT_GAME_BTN, MainFrame::OnButtonClick)
EVT_BUTTON(ID_PAUSE_GAME_BTN, MainFrame::OnButtonClick)
EVT_BUTTON(ID_EU_STAGE1_BTN, MainFrame::OnButtonClick)
EVT_BUTTON(ID_EU_STAGE2_BTN, MainFrame::OnButtonClick)
EVT_BUTTON(ID_MATHS_BTN, MainFrame::OnButtonClick)
EVT_BUTTON(ID_OPTIONGAME_BTN1, MainFrame::OnButtonClick)
EVT_BUTTON(ID_OPTIONGAME_BTN2, MainFrame::OnButtonClick)
EVT_BUTTON(ID_OPTIONGAME_BTN3, MainFrame::OnButtonClick)

END_EVENT_TABLE()





MainFrame::MainFrame(const wxString& title, int startWidth, int startHeight) : wxFrame(nullptr, wxID_ANY, title)
{
    this->startWidth = startWidth;
    this->startHeight = startHeight;

    startAppWidth = 1100;
    startAppHeight = 700;
    minimumAppWidth = 800;
    minimumAppHeight = 600;

    SetSizeHints(wxSize(minimumAppWidth, minimumAppHeight), wxDefaultSize);
    Bind(wxEVT_SIZE, &MainFrame::OnSize, this);
    wxInitAllImageHandlers();
    //Gamepanel na frame 
    wxStatusBar* bar = CreateStatusBar();
    gamePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    gamePanel->SetBackgroundColour(gameBackgroundColor);
    gamePanel->Hide();

    //pannel na frame
    mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    mainPanel->SetBackgroundColour(wxColor("red"));
    wxBoxSizer* mainPanelSizer = new wxBoxSizer(wxVERTICAL);
    mainPanelSizer->Add(mainPanel, 1, wxEXPAND);
    SetSizer(mainPanelSizer);
    pauseBtn = new wxButton(gamePanel, ID_PAUSE_GAME_BTN, "PAUSE", wxPoint(20, 15), wxSize(100, 30));
    exitBtn = new wxButton(gamePanel, ID_EXIT_GAME_BTN, "EXIT", wxPoint(130, 15), wxSize(100, 30));

    optionGameBtn1 = new wxButton(gamePanel, ID_OPTIONGAME_BTN1, "neco", wxPoint(130, 15), wxSize(100, 30));
    optionGameBtn2 = new wxButton(gamePanel, ID_OPTIONGAME_BTN2, "neco", wxPoint(130, 15), wxSize(100, 30));
    optionGameBtn3 = new wxButton(gamePanel, ID_OPTIONGAME_BTN3, "neco", wxPoint(130, 15), wxSize(100, 30));
    optionGameBtn1->Hide();
    optionGameBtn2->Hide();
    optionGameBtn3->Hide();



    //zakladni rozlozeni na mainPanel
    topMainPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(mainPanel->GetClientSize().GetWidth(), topMainPanelHeight));
    addTopSizer = new wxBoxSizer(wxVERTICAL);
    addTopSizer->Add(topMainPanel, 0, wxEXPAND);
    topMainPanel->SetBackgroundColour(wxColor("green"));
    mainPanel->SetSizer(addTopSizer);
    sectionMainPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(200, wxDefaultSize.GetHeight()));
    selectGameMainPanel1 = new wxScrolledWindow(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    selectGameMainPanel2 = new wxScrolledWindow(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    selectGameMainPanel3 = new wxScrolledWindow(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    selectGameMainPanel2->Hide();
    selectGameMainPanel3->Hide();
    selectGameMainPanel1->SetBackgroundColour(wxColour("blue"));
    selectGameMainPanel2->SetBackgroundColour(wxColour("brown"));
    selectGameMainPanel3->SetBackgroundColour(wxColour("purple"));


    selectGameMainPanel1->SetScrollRate(0, FromDIP(10));
    selectGameMainPanel2->SetScrollRate(0, FromDIP(10));


    mainLayoutSizer = new wxBoxSizer(wxHORIZONTAL);
    mainLayoutSizer->Add(sectionMainPanel, 0, wxEXPAND);
    mainLayoutSizer->Add(selectGameMainPanel1, 1, wxEXPAND);
    mainLayoutSizer->Add(selectGameMainPanel2, 1, wxEXPAND);
    mainLayoutSizer->Add(selectGameMainPanel3, 1, wxEXPAND);


    addTopSizer->Add(mainLayoutSizer, 1, wxEXPAND);




    //rozlozeni vyberu her

    gamesSizer1 = new wxBoxSizer(wxVERTICAL);
    gamesSizer2 = new wxBoxSizer(wxVERTICAL);

    std::vector<std::string> colors = { "pink", "brown", "green", "black", "purple", "pink", "lightblue", "yellow", "white", "grey" };
    imgPaths1 = { "img/dividedAttention.png", "img/headingConflicts.png", "img/dividedAttention.png", "img/dividedAttention.png", "img/headingConflicts.png", "img/headingConflicts.png"  };
    imgPaths2 = { "img/headingConflicts.png", "img/headingConflicts.png", "img/headingConflicts.png", "img/headingConflicts.png", "img/headingConflicts.png", "img/headingConflicts.png", "img/headingConflicts.png", "img/headingConflicts.png", "img/headingConflicts.png", "img/headingConflicts.png" };



    wxBitmap playBitmap(wxT("img/playbtn.png"), wxBITMAP_TYPE_PNG);
    wxBitmap infoBitmap(wxT("img/infobtn.png"), wxBITMAP_TYPE_PNG);
    wxBitmap statsBitmap(wxT("img/statsbtn2.png"), wxBITMAP_TYPE_PNG);




    for (int i = 0; i < class1GamesCount; i++)
    {


        wxPanel* imgPanel = new wxPanel(selectGameMainPanel1, wxID_ANY, wxDefaultPosition, wxSize(250, 250));
        wxPanel* descPanel = new wxPanel(selectGameMainPanel1, wxID_ANY, wxDefaultPosition, wxSize(selectGameMainPanel1->GetClientSize().GetWidth(), 250));
        wxPanel* runPanel = new wxPanel(selectGameMainPanel1, wxID_ANY, wxDefaultPosition, wxSize(50, 250));

        wxPanel* infoPanel = new wxPanel(descPanel, wxID_ANY, wxDefaultPosition, wxSize(selectGameMainPanel1->GetClientSize().GetWidth(), 250));
        wxPanel* statsPanel = new wxPanel(descPanel, wxID_ANY, wxDefaultPosition, wxSize(selectGameMainPanel1->GetClientSize().GetWidth(), 250));
        wxPanel* levelPanel = new wxPanel(descPanel, wxID_ANY, wxDefaultPosition, wxSize(selectGameMainPanel1->GetClientSize().GetWidth(), 250));

        statsPanel->Hide();
        levelPanel->Hide();

        infoStatsSizer1 = new wxBoxSizer(wxVERTICAL);
        infoStatsSizer1->Add(infoPanel, 1, wxEXPAND);
        infoStatsSizer1->Add(statsPanel, 1, wxEXPAND);
        infoStatsSizer1->Add(levelPanel, 1, wxEXPAND);


        descPanel->SetSizer(infoStatsSizer1);

        wxStaticBitmap* img = new wxStaticBitmap(imgPanel, wxID_ANY, wxBitmap(imgPaths1[i], wxBITMAP_TYPE_PNG), wxDefaultPosition, wxDefaultSize);
        wxBitmapButton* playButton = new wxBitmapButton(runPanel, (i + 53), playBitmap);
        wxBitmapButton* infoButton = new wxBitmapButton(runPanel, (i + 200), infoBitmap, wxDefaultPosition, wxSize(40, 40));
        wxBitmapButton* statsButton = new wxBitmapButton(runPanel, (i + 2000), statsBitmap);

        wxCustomButton* level1Btn = new wxCustomButton(levelPanel, (i * 3 + 1300), "LEVEL 1", wxSize(100, 30), false);
        wxCustomButton* level2Btn = new wxCustomButton(levelPanel, (i * 3 + 1300 + 1), "LEVEL 2", wxSize(100, 30), false);
        wxCustomButton* level3Btn = new wxCustomButton(levelPanel, (i * 3 + 1300 + 2), "LEVEL 3", wxSize(100, 30), false);

        level1Btn->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClick, this);
        level2Btn->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClick, this);
        level3Btn->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClick, this);




        wxBoxSizer* levelBtnSizer = new wxBoxSizer(wxHORIZONTAL);

        levelBtnSizer->AddStretchSpacer();
        levelBtnSizer->Add(level1Btn, 0, wxALL | wxALIGN_CENTER, 0);
        levelBtnSizer->AddStretchSpacer();
        levelBtnSizer->Add(level2Btn, 0, wxALL | wxALIGN_CENTER, 0);
        levelBtnSizer->AddStretchSpacer();
        levelBtnSizer->Add(level3Btn, 0, wxALL | wxALIGN_CENTER, 0);
        levelBtnSizer->AddStretchSpacer();


        levelPanel->SetSizer(levelBtnSizer);

        infoButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
            infoPanel->Show();
            statsPanel->Hide();
            levelPanel->Hide();

            descPanel->Layout();

            });

        statsButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
            statsPanel->Show();
            levelPanel->Hide();
            infoPanel->Hide();
            descPanel->Layout();
            });

        playButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
            levelPanel->Show();
            infoPanel->Hide();
            statsPanel->Hide();
            descPanel->Layout();
            });

        mainGameBtnSizer1 = new wxBoxSizer(wxVERTICAL);
        mainGameBtnSizer1->AddSpacer(40);
        mainGameBtnSizer1->Add(playButton, 0, wxALL | wxALIGN_CENTER, 10);
        mainGameBtnSizer1->Add(infoButton, 0, wxALL | wxALIGN_CENTER, 10);
        mainGameBtnSizer1->Add(statsButton, 0, wxALL | wxALIGN_CENTER, 10);


        runPanel->SetSizerAndFit(mainGameBtnSizer1);

        imgDescRunSizer1 = new wxBoxSizer(wxHORIZONTAL);
        imgDescRunSizer1->Add(imgPanel, 0, wxEXPAND);
        imgDescRunSizer1->Add(descPanel, 1, wxEXPAND);
        imgDescRunSizer1->Add(runPanel, 0, wxEXPAND);

        imgPanel->SetBackgroundColour(wxColor(colors[i]));
        descPanel->SetBackgroundColour(wxColor(colors[i]));
        runPanel->SetBackgroundColour(wxColor(colors[5]));

        statsPanel->SetBackgroundColour(wxColour("black"));
        infoPanel->SetBackgroundColour(wxColour("white"));
        levelPanel->SetBackgroundColour(wxColour("blue"));
        gamesSizer1->Add(imgDescRunSizer1, 0, wxEXPAND); // zmeneno z "1"
    }

    for (int i = 0; i < class2GamesCount; i++)
    {
        wxPanel* imgPanel = new wxPanel(selectGameMainPanel2, wxID_ANY, wxDefaultPosition, wxSize(250, 250));
        wxPanel* descPanel = new wxPanel(selectGameMainPanel2, wxID_ANY, wxDefaultPosition, wxSize(selectGameMainPanel1->GetClientSize().GetWidth(), 250));
        wxPanel* runPanel = new wxPanel(selectGameMainPanel2, wxID_ANY, wxDefaultPosition, wxSize(50, 250));

        wxStaticBitmap* img = new wxStaticBitmap(imgPanel, wxID_ANY, wxBitmap(imgPaths2[i], wxBITMAP_TYPE_PNG), wxDefaultPosition, wxDefaultSize);
        wxBitmapButton* playButton = new wxBitmapButton(runPanel, (i + 3), playBitmap);
        wxBitmapButton* infoButton = new wxBitmapButton(runPanel, (i + 100), infoBitmap, wxDefaultPosition, wxSize(40, 40));
        wxBitmapButton* statsButton = new wxBitmapButton(runPanel, (i + 1000), statsBitmap);

        mainGameBtnSizer2 = new wxBoxSizer(wxVERTICAL);
        mainGameBtnSizer2->AddSpacer(40);
        mainGameBtnSizer2->Add(playButton, 0, wxALL | wxALIGN_CENTER, 10);
        mainGameBtnSizer2->Add(infoButton, 0, wxALL | wxALIGN_CENTER, 10);
        mainGameBtnSizer2->Add(statsButton, 0, wxALL | wxALIGN_CENTER, 10);


        runPanel->SetSizerAndFit(mainGameBtnSizer2);

        imgDescRunSizer2 = new wxBoxSizer(wxHORIZONTAL);
        imgDescRunSizer2->Add(imgPanel, 0, wxEXPAND);
        imgDescRunSizer2->Add(descPanel, 1, wxEXPAND);
        imgDescRunSizer2->Add(runPanel, 0, wxEXPAND);

        imgPanel->SetBackgroundColour(wxColor(colors[i]));
        descPanel->SetBackgroundColour(wxColor(colors[i]));
        runPanel->SetBackgroundColour(wxColor(colors[5]));

        gamesSizer2->Add(imgDescRunSizer2, 1, wxEXPAND);
    }
    selectGameMainPanel1->SetSizerAndFit(gamesSizer1);
    selectGameMainPanel2->SetSizerAndFit(gamesSizer2);

    sectionMainPanel->SetBackgroundColour(wxColor("yellow"));
    selectGameMainPanel1->SetBackgroundColour(wxColor("blue"));

    int appWidth = 900;
    int appHeight = 600;

    //sectionPanel
    sectionSizer = new wxBoxSizer(wxVERTICAL);
    wxCustomButton* euStage1btn = new wxCustomButton(sectionMainPanel, ID_EU_STAGE1_BTN, "EU STAGE 1", wxSize(250, 50), true);
    wxCustomButton* euStage2btn = new wxCustomButton(sectionMainPanel, ID_EU_STAGE2_BTN, "EU STAGE 2", wxSize(250, 50), false);
    wxCustomButton* mathsBtn = new wxCustomButton(sectionMainPanel, ID_MATHS_BTN, "MATHS", wxSize(250, 50), false);

    sectionSizer->AddSpacer(30);
    sectionSizer->Add(euStage1btn, 0, wxALL | wxALIGN_CENTER, 10);
    sectionSizer->Add(euStage2btn, 0, wxALL | wxALIGN_CENTER, 10);
    sectionSizer->Add(mathsBtn, 0, wxALL | wxALIGN_CENTER, 10);

    buttonsToHover = { euStage1btn, euStage2btn, mathsBtn };
    sectionMainPanel->SetSizer(sectionSizer);

    /*Bind(wxEVT_ENTER_WINDOW, &MainFrame::OnMouseEnter, this);
    Bind(wxEVT_LEAVE_WINDOW, &MainFrame::OnMouseLeave, this);*/

    Bind(wxEVT_BUTTON, &MainFrame::OnButtonClick, this, ID_EU_STAGE1_BTN);
    Bind(wxEVT_BUTTON, &MainFrame::OnButtonClick, this, ID_EU_STAGE2_BTN);
    Bind(wxEVT_BUTTON, &MainFrame::OnButtonClick, this, ID_MATHS_BTN);
    Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);
    vAttrs.PlatformDefaults().Defaults().EndList(); 

    timer.SetOwner(this, wxID_ANY);
    timer.Start(300);
}

void MainFrame::OnTimer(wxTimerEvent& event)
{
    MainFrame::HandleButtons();
    event.Skip();
}

void MainFrame::OnSize(wxSizeEvent& event)
{
    if (gamePanel->IsShown())
    {
        wxSize screenSize = GetClientSize();
        gamePanel->SetClientSize(screenSize);
    }
    MainFrame::HandleButtonProjection();
    event.Skip();
}

void MainFrame::HandleButtonProjection()
{
    wxSize sizeNow = GetClientSize();
    float ratioW = (float)sizeNow.x / startSize.x;
    float ratioH = (float)sizeNow.y / startSize.y;
    if (optionGameBtn1->IsShown())
    {
        wxPoint scaledPosition(startBtn1Point.x * ratioW, startBtn1Point.y * ratioH);
        optionGameBtn1->SetPosition(scaledPosition);
    }
    if (optionGameBtn2->IsShown())
    {
        wxPoint scaledPosition(startBtn2Point.x * ratioW, startBtn2Point.y * ratioH);
        optionGameBtn2->SetPosition(scaledPosition);
    }
    if (optionGameBtn3-> IsShown())
    {
        wxPoint scaledPosition(startBtn3Point.x * ratioW, startBtn3Point.y * ratioH);
        optionGameBtn3->SetPosition(scaledPosition);
    }
}

void MainFrame::HandleButtons()
{
    std::vector<bool> buttonsVisibility;
    if (canvas != nullptr)
    {
        buttonsVisibility = canvas->game->GetButtons(); 

        if (buttonsVisibility[0])
        {
            optionGameBtn1->Show();
        }
        else
        {
            optionGameBtn1->Hide();
        }

        if (buttonsVisibility[1])
        {
            optionGameBtn2->Show();
        }
        else
        {
            optionGameBtn2->Hide();
        }

        if (buttonsVisibility[2])
        {
            optionGameBtn3->Show();
        }
        else
        {
            optionGameBtn3->Hide();
        }
    }

    //if (buttons[3])
    //{
    //    optionGameBtn4->Show();
    //}
    //else
    //{
    //    optionGameBtn4->Hide();
    //}

    //if (buttons[4])
    //{
    //    optionGameBtn5->Show();
    //}
    //else
    //{
    //    optionGameBtn5->Hide();
    //}

    //if (buttons[5])
    //{
    //    optionGameBtn6->Show();
    //}
    //else
    //{
    //    optionGameBtn6->Hide();
    //}

    //if (buttons[6])
    //{
    //    optionGameBtn7->Show();
    //}
    //else
    //{
    //    optionGameBtn7->Hide();
    //}

    //if (buttons[7])
    //{
    //    optionGameBtn8->Show();
    //}
    //else
    //{
    //    optionGameBtn8->Hide();
    //}

    //if (buttons[8])
    //{
    //    optionGameBtn9->Show();
    //}
    //else
    //{
    //    optionGameBtn9->Hide();
    //}

    //if (buttons[9])
    //{
    //    optionGameBtn10->Show();
    //}
    //else
    //{
    //    optionGameBtn10->Hide();
    //}
}

void MainFrame::SwitchPanels()
{
    if (gamePanel->IsShown())
    {
        gamePanel->Hide();
        mainPanel->Show();
    }
    else if (mainPanel->IsShown())
    {
        mainPanel->Hide();
        gamePanel->Show();
    }
}

void MainFrame::HandleGame(int buttonID)
{

}

void MainFrame::OnButtonClick(wxCommandEvent& event) {
    int buttonID = event.GetId();
    if (buttonID == ID_EU_STAGE1_BTN)
    {
        selectGameMainPanel1->Show();
        selectGameMainPanel2->Hide();
        selectGameMainPanel3->Hide();
        mainPanel->Layout();
    }
    else if (buttonID == ID_EU_STAGE2_BTN)
    {
        selectGameMainPanel1->Hide();
        selectGameMainPanel2->Show();
        selectGameMainPanel3->Hide();
        selectGameMainPanel2->Layout();
        mainPanel->Layout();

    }
    else if (buttonID == ID_MATHS_BTN)
    {
        selectGameMainPanel1->Hide();
        selectGameMainPanel2->Hide();
        selectGameMainPanel3->Show();
        mainPanel->Layout();

    }
    else if (buttonID == ID_PAUSE_GAME_BTN)
    {
        canvas->game->SetFocusBackTimer(); 
        if (canvas->game->GetTypeOfGame() == "practice")
        {
            if (canvas->GetPause())
            {
                canvas->SetPause(false);
            }
            else
            {
                canvas->SetPause(true);

            }
        }

    }
    else if (buttonID == ID_EXIT_GAME_BTN)
    {
        canvas->DeleteGame();
        canvas->Destroy();
        gamePanel->Hide();
        mainPanel->Show();
    }

    else if (buttonID == ID_OPTIONGAME_BTN1)
    {
        canvas->game->OptionBtnPressed(1);
    }
    else if (buttonID == ID_OPTIONGAME_BTN2)
    {
        canvas->game->OptionBtnPressed(2);
    }
    else if (buttonID == ID_OPTIONGAME_BTN3)
    {
        canvas->game->OptionBtnPressed(3);
    }
    if (buttonID == 1300)
    {
        optionGameBtn1->Hide();

        wxSize clientSize = GetClientSize();
        startSize = GetClientSize(); //important for buttons moving
        gamePanel->SetClientSize(clientSize.x, clientSize.y);
        canvas = new Canvas(gamePanel, vAttrs, 2, "GameHeadingConflicts", "practice", "counter");
        wxBoxSizer* canvasSizer = new wxBoxSizer(wxHORIZONTAL);
        canvasSizer->Add(canvas, 1, wxEXPAND);

        optionGameBtn1->SetSize(wxSize(120, 50));
        optionGameBtn2->SetSize(wxSize(120, 50));

        wxSize buttonSize = optionGameBtn1->GetSize();
        int spacing = 60;  // Adjust this value as needed
        int totalButtonWidth = 2 * buttonSize.x + spacing;
        int startX = (startSize.x - totalButtonWidth) / 2;
        optionGameBtn1->SetPosition(wxPoint(startX + 500, startSize.y - 80));
        optionGameBtn2->SetPosition(wxPoint(startX + 500, startSize.y - 150));
        optionGameBtn1->SetLabel("CONFLICT");
        optionGameBtn2->SetLabel("CONTINUE");

        optionGameBtn1->Show();
        optionGameBtn2->Show();

        startBtn1Point = optionGameBtn1->GetPosition();
        startBtn2Point = optionGameBtn2->GetPosition();

        gamePanel->SetSizer(canvasSizer);
        gamePanel->Show();
        mainPanel->Hide();
        gamePanel->Layout();
        Layout();
    }

    if (buttonID == 1301)
    {
        wxSize clientSize = GetClientSize();
        gamePanel->SetClientSize(clientSize.x, clientSize.y);
        canvas = new Canvas(gamePanel, vAttrs, 2, "GameHeadingConflicts", "practice", "counter");
        canvasSizer = new wxBoxSizer(wxHORIZONTAL);
        canvasSizer->Add(canvas, 1, wxEXPAND);
        gamePanel->SetSizer(canvasSizer);
        gamePanel->Show();
        mainPanel->Hide();
        gamePanel->Layout();
        Layout();
    }   

    if (buttonID == 1302)
    {
        wxSize clientSize = GetClientSize();
        gamePanel->SetClientSize(clientSize.x, clientSize.y);
        //GameHeadingConflicts* game = new GameHeadingConflicts(3, "practice", clientSize.x, clientSize.y, 1100, 650);
        //canvas = new Canvas(gamePanel, vAttrs, game, err);
        canvasSizer = new wxBoxSizer(wxHORIZONTAL);
        canvasSizer->Add(canvas, 1, wxEXPAND);
        gamePanel->SetSizer(canvasSizer);
        gamePanel->Show();
        mainPanel->Hide();
        gamePanel->Layout();
        Layout();

    }

    if (buttonID == 1303)
    {
        wxSize clientSize = GetClientSize();
        gamePanel->SetClientSize(clientSize.x, clientSize.y);
        canvas = new Canvas(gamePanel, vAttrs, 3, "GameDividedAttention", "practice", "timer");
        canvasSizer = new wxBoxSizer(wxHORIZONTAL);
        canvasSizer->Add(canvas, 1, wxEXPAND);
        gamePanel->SetSizer(canvasSizer);
        gamePanel->Show();
        mainPanel->Hide();
        gamePanel->Layout();
        Layout();
    }
    if (buttonID == 1304)
    {
        wxSize clientSize = GetClientSize();
        gamePanel->SetClientSize(clientSize.x, clientSize.y);
        //GameHeadingConflicts* game = new GameHeadingConflicts(3, "practice", clientSize.x, clientSize.y, 1100, 650);
        //canvas = new Canvas(gamePanel, vAttrs, game, err);
        canvasSizer = new wxBoxSizer(wxHORIZONTAL);
        canvasSizer->Add(canvas, 1, wxEXPAND);
        gamePanel->SetSizer(canvasSizer);
        gamePanel->Show();
        mainPanel->Hide();
        gamePanel->Layout();
        Layout();

    }
    if (buttonID == 1305)
    {
        wxSize clientSize = GetClientSize();
        gamePanel->SetClientSize(clientSize.x, clientSize.y);
        //GameHeadingConflicts* game = new GameHeadingConflicts(3, "practice", clientSize.x, clientSize.y, 1100, 650);
        //canvas = new Canvas(gamePanel, vAttrs, game, err);
        canvasSizer = new wxBoxSizer(wxHORIZONTAL);
        canvasSizer->Add(canvas, 1, wxEXPAND);
        gamePanel->SetSizer(canvasSizer);
        gamePanel->Show();
        mainPanel->Hide();
        gamePanel->Layout();
        Layout();

    }
    if (buttonID == 1306)
    {
        int widthOfGame = 500;
        int heightOfGame = 500;
        startSize = GetClientSize();
        gamePanel->SetClientSize(startSize.x, startSize.y);
        canvas = new Canvas(gamePanel, vAttrs, 3, "GameSpotTheSide", "practice", "counter");
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

        gamePanel->SetSizer(sizer);
        int spacing = 60;  // Adjust this value as needed

        optionGameBtn1->SetSize(wxSize(120, 50));
        optionGameBtn2->SetSize(wxSize(120, 50));
        optionGameBtn3->SetSize(wxSize(120, 50));
        wxSize buttonSize = optionGameBtn1->GetSize();

        int totalButtonWidth = 2 * buttonSize.x + spacing;
        int startX = (startSize.x - totalButtonWidth) / 2;
        optionGameBtn1->SetPosition(wxPoint(startX, startSize.y - 60));
        optionGameBtn2->SetPosition(wxPoint(startX + buttonSize.x + spacing, startSize.y - 60));
        optionGameBtn3->SetPosition(wxPoint(startX + 2 * (buttonSize.x + spacing), startSize.y - 60));

        optionGameBtn1->SetLabel("LEFT");
        optionGameBtn2->SetLabel("RIGHT");
        optionGameBtn3->SetLabel("CONTINUE");

        optionGameBtn1->Show();
        optionGameBtn2->Show();
        optionGameBtn3->Hide();


        startBtn1Point = optionGameBtn1->GetPosition();
        startBtn2Point = optionGameBtn2->GetPosition();
        startBtn3Point = optionGameBtn3->GetPosition();


        canvas->SetMinSize(wxSize(widthOfGame, heightOfGame));
        canvas->SetMaxSize(wxSize(widthOfGame, heightOfGame));

        wxBoxSizer* gamePanelSizer = new wxBoxSizer(wxVERTICAL);
        gamePanelSizer->AddStretchSpacer(1);
        gamePanelSizer->Add(canvas, 0, wxALIGN_CENTER);
        gamePanelSizer->AddStretchSpacer(1);
        gamePanel->SetSizer(gamePanelSizer);
        gamePanel->Show();
        mainPanel->Hide();
        gamePanel->Layout();
        Layout();
    }
    if (buttonID == 1307)
    {

    }
    if (buttonID == 1308)
    {

    }
    if (buttonID == 1309)
    {
        int widthOfGame = 900;
        int heightOfGame = 600;
        startSize = GetClientSize();
        gamePanel->SetClientSize(startSize.x, startSize.y);
        canvas = new Canvas(gamePanel, vAttrs, 3, "GameMemorizePictograms", "practice", "counter");
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

        gamePanel->SetSizer(sizer);
        int spacing = 60;  // Adjust this value as needed

        optionGameBtn1->SetSize(wxSize(120, 50));
        optionGameBtn2->SetSize(wxSize(120, 50));
        wxSize buttonSize = optionGameBtn1->GetSize();

        int totalButtonWidth = 2 * buttonSize.x + spacing;
        int startX = (startSize.x - totalButtonWidth) / 2;
        optionGameBtn1->SetPosition(wxPoint(startX, startSize.y - 60));
        optionGameBtn2->SetPosition(wxPoint(startX + buttonSize.x + spacing, startSize.y - 60));
        optionGameBtn3->SetPosition(wxPoint(startX + 2 * (buttonSize.x + spacing), startSize.y - 60));

        optionGameBtn1->SetLabel("CORRECT");
        optionGameBtn2->SetLabel("INCORRECT");

        optionGameBtn1->Show();
        optionGameBtn2->Show();
        optionGameBtn3->Hide();


        startBtn1Point = optionGameBtn1->GetPosition();
        startBtn2Point = optionGameBtn2->GetPosition();

        canvas->SetMinSize(wxSize(widthOfGame, heightOfGame));
        canvas->SetMaxSize(wxSize(widthOfGame, heightOfGame));

        wxBoxSizer* gamePanelSizer = new wxBoxSizer(wxVERTICAL);
        gamePanelSizer->AddStretchSpacer(1);
        gamePanelSizer->Add(canvas, 0, wxALIGN_CENTER);
        gamePanelSizer->AddStretchSpacer(1);
        gamePanel->SetSizer(gamePanelSizer);
        gamePanel->Show();
        mainPanel->Hide();
        gamePanel->Layout();
        Layout();
    }
    if (buttonID == 1310)
    {

    }
    if (buttonID == 1311)
    {

    }
    if (buttonID == 1312)
    {
        wxSize clientSize = GetClientSize();
        gamePanel->SetClientSize(clientSize.x, clientSize.y);
        canvas = new Canvas(gamePanel, vAttrs, 3, "GameLearningAndApplying", "practice", "timer");
        canvasSizer = new wxBoxSizer(wxHORIZONTAL);
        canvasSizer->Add(canvas, 1, wxEXPAND);
        gamePanel->SetSizer(canvasSizer);
        gamePanel->Show();
        mainPanel->Hide();
        gamePanel->Layout();
        Layout();
    }
    if (buttonID == 1313)
    {

    }
    if (buttonID == 1314)
    {

    }
    if (buttonID == 1315)
    {
        int widthOfGame = 1100;
        int heightOfGame = 650;
        startSize = GetClientSize();
        wxSize forBtnSize = GetSize();

        gamePanel->SetClientSize(startSize.x, startSize.y);
        int wi = gamePanel->GetClientSize().x;
        int he = gamePanel->GetClientSize().y;

        canvas = new Canvas(gamePanel, vAttrs, 3, "GameMultiAttention", "practice", "timer");
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

        gamePanel->SetSizer(sizer);
        int spacing = 60;  // Adjust this value as needed

        optionGameBtn1->SetSize(wxSize(120, 50));
        optionGameBtn2->SetSize(wxSize(120, 50));
        optionGameBtn3->SetSize(wxSize(120, 50));

        wxSize buttonSize = optionGameBtn1->GetSize();

        optionGameBtn1->SetPosition(wxPoint((startSize.x / 2) - spacing / 2 - buttonSize.x, startSize.y - 400));
        optionGameBtn2->SetPosition(wxPoint((startSize.x / 2) + spacing / 2, startSize.y - 400));
        optionGameBtn3->SetPosition(wxPoint(startSize.x / 2 - buttonSize.x / 2, startSize.y - 200));

        optionGameBtn1->SetLabel("CORRECT");
        optionGameBtn2->SetLabel("INCORRENT");
        optionGameBtn3->SetLabel("MATCH");

        optionGameBtn1->Show();
        optionGameBtn2->Show();
        optionGameBtn3->Show();

        startBtn1Point = optionGameBtn1->GetPosition();
        startBtn2Point = optionGameBtn2->GetPosition();
        startBtn3Point = optionGameBtn3->GetPosition();


        canvas->SetMinSize(wxSize(widthOfGame, heightOfGame));
        canvas->SetMaxSize(wxSize(widthOfGame, heightOfGame));

        wxBoxSizer* gamePanelSizer = new wxBoxSizer(wxVERTICAL);
        gamePanelSizer->AddStretchSpacer(1);
        gamePanelSizer->Add(canvas, 0, wxALIGN_CENTER);
        gamePanelSizer->AddStretchSpacer(1);
        gamePanel->SetSizer(gamePanelSizer);
        gamePanel->Show();
        mainPanel->Hide();
        gamePanel->Layout();
        Layout();
    }

}