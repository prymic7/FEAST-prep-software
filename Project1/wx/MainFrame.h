
#pragma once
#include <wx/wx.h>
#include "../games/stage1/DividedAttention/GameDividedAttention.h"
#include "../games/stage1/HeadingConflicts/GameHeadingConflicts.h"
#include "../games/stage1/SpotTheSide/GameSpotTheSide.h"
#include "../games/stage1/MemorizePictograms/GameMemorizePictograms.h"
#include "../games/stage1/LearningAndApplying/GameLearningAndApplying.h"


#include "../games/BaseGame.h"
#include "buttons/CustomButton.h"//s
#include "Canvas.h"
#include <glew.h>

//class GameDividedAttention;
//class GameHeadingConflicts;
//class GameSpotTheSide;
class BaseGame;


class MainFrame : public wxFrame
{

public:

	MainFrame(const wxString& title, int startWidth, int startHeight);
	void SwitchPanels(); 
	void HandleGame(int buttonID);
	Canvas* canvas;
	wxPanel* gamePanel;


private:
	bool gamePaused;

	int descriptionPanelX;

	
	wxPanel* sectionMainPanel;
	wxPanel* topMainPanel;
	wxPanel* mainPanel;

	wxScrolledWindow* selectGameMainPanel1;
	wxScrolledWindow* selectGameMainPanel2;
	wxScrolledWindow* selectGameMainPanel3;

	wxPanel* descMainPanel;
	wxPanel* imgMainPanel;
	wxPanel* runMainPanel;

	int slideClicked = 0;

	wxWindow* euStage1btn;
	wxWindow* euStage2btn;
	wxWindow* mathsBtn;


	std::vector<wxWindow*> buttonsToHover;
	

	int startAppWidth;
	int startAppHeight;
	int minimumAppWidth;
	int minimumAppHeight;

	int topMainPanelHeight = 50;
	int imageWidth = 270;
	int imageHeight = 260;
	int sectionWidth = 200;
	int imgBtnSize = 30;

	wxButton* startGameButton;
	wxButton* exitGameButton;
	wxButton* pauseGameButton;
	
	


	wxStaticBitmap* game1img;
	wxStaticBitmap* game2img;
	wxStaticBitmap* game3img;
	wxStaticBitmap* game4img;
	wxStaticBitmap* game5img;
	wxStaticBitmap* game6img;
	wxStaticBitmap* game7img;
	wxStaticBitmap* game8img;
	wxStaticBitmap* game9img;
	wxStaticBitmap* game10img;

	wxGridSizer* buttonSizer;
	wxImage* image;
	wxStaticBitmap* staticBitmap;

	wxBoxSizer* verticalSizer;
	wxBoxSizer* horizontalSizer;
	wxBoxSizer* mainPanelSizer;
	wxBoxSizer* gamePanelSizer;
	wxBoxSizer* mainLayoutSizer;
	wxBoxSizer* addTopSizer;

	wxBoxSizer* gamesSizer1;
	wxBoxSizer* imgDescRunSizer1;
	wxBoxSizer* mainGameBtnSizer1;
	wxBoxSizer* infoStatsSizer1;


	wxBoxSizer* gamesSizer2;
	wxBoxSizer* imgDescRunSizer2;
	wxBoxSizer* mainGameBtnSizer2;
	wxBoxSizer* infoStatsSizer2;


	wxBoxSizer* sectionSizer;


	int class1GamesCount = 6;
	int class2GamesCount = 10;


	std::vector<std::string> imgPaths1;
	std::vector<std::string> imgPaths2;



	bool gameRunning = false;
	GameDividedAttention* game2;
	GameHeadingConflicts* game1;

	BaseGame* activeGame;

	wxButton* pauseBtn; 
	wxButton* exitBtn;
	wxButton* bullyBtn;
	wxButton* optionGameBtn1;
	wxButton* optionGameBtn2;
	wxButton* optionGameBtn3;

	wxSize startSize;
	wxPoint startBtn1Point;
	wxPoint startBtn2Point;
	wxPoint startBtn3Point;
	wxColor gameBackgroundColor = { 211,211,211,255 };
	wxColor blueColor = { 0, 0, 255, 255 };


	bool gameCreated = false;
	GLenum err;

	wxTimer timer;
	wxGLAttributes vAttrs;
	int startWidth;
	int startHeight;

	wxBoxSizer* canvasSizer;

	bool gamePlaying = false;

	int count = 0;

	wxDECLARE_EVENT_TABLE();

	void OnSize(wxSizeEvent& event);
	void OnButtonClick(wxCommandEvent& event);
	void OnTimer(wxTimerEvent& event);
	void OnPaint(wxPaintEvent& event);

	void SetTimerValue(wxTimer *timer, int miliseconds); //How was will canvas refresh (100ms - 10fps)
	void StartGame();
	void SwitchPause(BaseGame* basegame, wxCommandEvent& event);
	void HandleButtonProjection();
	void HandleButtons();
};



