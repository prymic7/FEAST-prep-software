#pragma once
#include <wx/wx.h>
#include <SDL.h>
#include <chrono>
#include <random>
#include <array>
#include <map>

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <wx/glcanvas.h>

#include "../opengl/programs/ShaderProgram.h"
#include "../opengl/buffers/VertexBuffer.h"
#include "../opengl/buffers/IndexBuffer.h"
#include "../opengl/errorHandlers/ErrorHandler.h"
#include "../opengl/layout/VertexBufferLayout.h"
#include "../opengl/layout/VertexArray.h"

#include <stb/stb_image.h>
#include "../img/stb/STBimage.h"

#include <ft2build.h>
#include FT_FREETYPE_H  


class BaseGame
{


	struct Character {
		unsigned int TextureID;  // ID handle of the glyph texture
		glm::ivec2   Size;       // Size of glyph
		glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
		unsigned int Advance;    // Offset to advance to next glyph
	};
	//grid
protected:


	bool justRun;
	bool countDownActive = true;
	float creatorW;
	float creatorH;

	glm::mat4 ratioProjection;

	float wRatio;
	float hRatio;
	float BaseWindowDiffW;
	float BaseWindowDiffH;

	int startW;
	int startH;
	int goodStartW;
	int goodStartH;
	int nowW;
	int nowH;



	int appWidth;
	int appHeight;
	int newWidth;
	int newHeight;
	int gridX = 0;
	int gridY = 0;
	int gridStartX = gridX;
	int gridStartY = gridY;
	int gridWidth;
	int gridHeight;
	int xNow;
	int yNow;
	int diffX;
	int diffY;
	std::string mode;
	SDL_Rect gridRect;
	bool timer;
	std::string typeOfGame;
	std::string typeOfTimer;
	bool pauseTurnedOff = false;
	bool pauseTurnedOn = false;
	std::chrono::steady_clock::time_point adjusted_play_time;
	int roundTimeMilisecs;
	int taskIntroTimeMilisecs; // Za takto nastavneych podminek musi byt minimalne > 3000
	bool pauseWaiting = false;



	//important stuff
	wxPanel* parentPanel;
	wxPanel* mainPanel;

	int level;

	//main game bar

	GLuint VBO1;
	GLuint VAO1;
	GLuint gameBarEB;

	//text
	GLuint textVAO;
	GLuint textVBO;
	std::map<char, Character> Characters;


	IndexBuffer* gameBarIB;
	VertexArray* gameBarVA;
	VertexBuffer* gameBarVB;
	VertexBufferLayout* gameBarVBL;

	float gameBarWidth = 300.0f;
	float gameBarHeight = 60.0f;
	float gameBarX = 300.0f;
	float gameBarY = nowH;

	float pauseBtnWidth = 100.0f;
	float pauseBtnHeight = 40.0f;

	float exitBtnWidth = 100.0f;
	float exitBtnHeight = 40.0f;
	float gameBarOneDifferenceX = (gameBarWidth - (pauseBtnWidth + exitBtnWidth)) / 3;
	float gameBarOneDifferenceY = (gameBarHeight - pauseBtnHeight) / 2;


	GLfloat gameBarVertices[72] = {
		gameBarX, gameBarY,                 0.0745f, 0.1529f, 0.3098f, 1.0f,
		gameBarX, gameBarHeight,            0.0745f, 0.1529f, 0.3098f, 1.0f,
		gameBarWidth, gameBarY,				0.0745f, 0.1529f, 0.3098f, 1.0f,
		gameBarWidth, gameBarHeight,        0.0745f, 0.1529f, 0.3098f, 1.0f,


		(gameBarX + gameBarOneDifferenceX), (gameBarY + gameBarOneDifferenceY),										1.0f, 1.0f, 1.0f, 1.0f,
		(gameBarX + gameBarOneDifferenceX), (gameBarY + gameBarOneDifferenceY + pauseBtnHeight),					1.0f, 1.0f, 1.0f, 1.0f,
		(gameBarX + gameBarOneDifferenceX + pauseBtnWidth), (gameBarY + gameBarOneDifferenceY),						1.0f, 1.0f, 1.0f, 1.0f,
		(gameBarX + gameBarOneDifferenceX + pauseBtnWidth), (gameBarY + gameBarOneDifferenceY + pauseBtnHeight),	1.0f, 1.0f, 1.0f, 1.0f,

		(gameBarX + gameBarOneDifferenceX * 2 + pauseBtnWidth), (gameBarY + gameBarOneDifferenceY),							1.0f, 1.0f, 1.0f, 1.0f,
		(gameBarX + gameBarOneDifferenceX * 2 + pauseBtnWidth), (gameBarY + gameBarOneDifferenceY + pauseBtnHeight),		1.0f, 1.0f, 1.0f, 1.0f,
		(gameBarX + gameBarOneDifferenceX * 2 + pauseBtnWidth * 2), (gameBarY + gameBarOneDifferenceY),						1.0f, 1.0f, 1.0f, 1.0f,
		(gameBarX + gameBarOneDifferenceX * 2 + pauseBtnWidth * 2), (gameBarY + gameBarOneDifferenceY + pauseBtnHeight),	1.0f, 1.0f, 1.0f, 1.0f,
	};

	GLushort gameBarIndicies[18] =
	{
		0,1,2,2,3,1,
		4,5,6,6,7,5,
		8,9,10,10,11,9,
	};



	int timerBarWidth = 80;
	int timerBarHeight = 30;
	int timerBarX = gameBarWidth;
	int timerBarY = (gameBarHeight - timerBarHeight) / 2;

	std::chrono::steady_clock::time_point currentTime;
	std::chrono::steady_clock::time_point startPause;
	std::chrono::steady_clock::time_point endPause;
	std::string timeStr;

	std::chrono::milliseconds pauseTimeDiff;
	std::chrono::milliseconds relativeTime;
	int pauseTimeAddedUp = 0;
	int timeWithPause = 0;


	int targetTime;
	//int targetIntSecs;

	int currentTimeSecs;
	int targetTimeSecs;
	int targetRounds;
	int currentRound;
	int oldNumOfRounds;


	int pauseIntroWidth = 200;
	int pauseIntroHeight = 40;
	int pauseIntroX = xNow + gridWidth / 2 - pauseIntroWidth / 2;
	int pauseIntroY = yNow + gridHeight / 2 - pauseIntroHeight / 2;





	//count down to start
	int countRectWidth;
	int countRectHeight;

	//explanation of round
	int introRectX;
	int introRectY;
	int introRectWidth;
	int introRectHeight;
	//sizing
	int startAppWidth;
	int startAppHeight;
	int parentPanelWidth;
	int parentPanelHeight;

	bool firstTime = true;
	bool timeoutBetweenRounds;
	//response btn
	int responseBtnWidth;
	int responseBtnHeight;
	int responseBtnX;
	int responseBtnY;
	bool responseBtnHover = false;
	//continue btn
	int continueBtnWidth;
	int continueBtnHeight;
	int continueBtnX;
	int continueBtnY;
	bool continueBtnHover = false;
	//barvy

	//float btnHoverColor[4] = { 0.991176f, 0.901961f, 0.54902f, 1.0f };
	float btnHoverColor[4] = { 0.145f , 0.3529f, 0.5098f, 1.0f }; //grey / blue ? wtf
	float appColor[4] = { 0.0745f , 0.1529f, 0.3098f, 1.0f };
	float greyColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	float greyColor2[4] = { 0.8275f, 0.8275f, 0.8275f, 1.0f }; //lighter grey
	float blackColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; 
	float greenColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f }; 
	float greenColor2[4] = { 0.0f, 0.5f, 0.0f, 1.0f }; //darker green
	float redColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; 
	float whiteColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float yellowColor[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
	float orangeColor[4] = { 1.0f, 0.5f, 0.0f, 1.0f };
	float purpleColor[4] = { 0.5f, 0.0f, 0.5f, 1.0f };
	float cyanColor[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
	float magentaColor[4] = { 1.0f, 0.0f, 1.0f, 1.0f };

	bool optionBtn1Visible = false;
	bool optionBtn2Visible = false;
	bool optionBtn3Visible = false;
	bool optionBtn4Visible = false;
	bool optionBtn5Visible = false;
	bool optionBtn6Visible = false;
	bool optionBtn7Visible = false;
	bool optionBtn8Visible = false;
	bool optionBtn9Visible = false;
	bool optionBtn10Visible = false;

	int oldSec;
	int oldMin;
	int min;
	int sec;
	//bools
	bool playingGame;
	bool rightAnswer;
	bool roundOver = false;
	bool taskIntroActive = false;
	bool gamePlaying;
	bool gameStarted = false;
	bool gameJustStarted = false;

	bool gamePaused;
	bool windowResizedNow = true;
	bool oneTime = true;

	const char* output;
	//chrono
	std::chrono::system_clock::time_point time_start;
	std::chrono::system_clock::time_point time_timeout;
	std::chrono::system_clock::time_point time_before_pause;
	std::chrono::steady_clock::time_point play_time;
	std::chrono::steady_clock::time_point timeNow;
	std::chrono::steady_clock::time_point realTime;
	std::chrono::steady_clock::time_point focusBackTime;

	std::chrono::steady_clock::time_point textTime;   // <---------------------------------------------------- nahradit u vsech
	int textTimeMilisecsSolid;
	int milisecsOfText;
	bool correctAnswerForText;
	bool wrongAnswerForText;
	bool missedInputForText;

	bool setFocusBack = true;;

	int milisecsOfCountDown = 0;
	int milisecsOfTimeTotal = 0;
	int milisecsOfRoundGoing = 0;
	int milisecsAfterInput = 0;
	int milisecsOfTaskIntroGoing = 0;


	std::chrono::steady_clock::time_point timestamp;
	std::chrono::steady_clock::time_point roundFinishedTime;


	std::chrono::milliseconds elapsedTimeAfterCountDown;
	int hrubyTime;




	std::chrono::steady_clock::time_point appStartTime;

	std::chrono::milliseconds duration_pause;
	long timeInPause = 0;

	int shaderProgramInit = -1;
	ShaderProgram* staticShaderProgram;
	ShaderProgram* textStaticShaderProgram;
	ShaderProgram* textFlexibleShaderProgram;
	ShaderProgram* flexibleShaderProgram;
	ShaderProgram* staticImageShaderProgram;



	IndexBuffer* rectangleIB;
	IndexBuffer* doubleRectangleIB;


	VertexBufferLayout* twoFloatVBL;
	GLushort rectangleIndices[6] = //LT, RT, RD, LD
	{
		0, 1, 2,
		0, 2, 3
	};

	GLushort doubleRectangleIndices[12] = //LT, RT, RD, LD
	{
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7
	};


	//count down variables
	std::string countDownText = "3";
	VertexArray* countDownVA;
	VertexBuffer* countDownVB;
	float countDownRectSize = 90.0;
	float countDownVertices[8] =
	{
		creatorW / 2 - countDownRectSize / 2, creatorH / 2 - countDownRectSize / 2,
		creatorW / 2 + countDownRectSize / 2, creatorH / 2 - countDownRectSize / 2,
		creatorW / 2 + countDownRectSize / 2, creatorH / 2 + countDownRectSize / 2,
		creatorW / 2 - countDownRectSize / 2, creatorH / 2 + countDownRectSize / 2,
	};

	//task intro vars
	VertexArray* taskIntroVA;
	VertexBuffer* taskIntroVB;
	float taskIntroRectWidth = 400.0;
	float taskIntroRectHeight = 100.0;

	float taskIntroVertices[8] =
	{
		creatorW / 2 - taskIntroRectWidth / 2, creatorH / 2 - taskIntroRectHeight / 2,
		creatorW / 2 + taskIntroRectWidth / 2, creatorH / 2 - taskIntroRectHeight / 2,
		creatorW / 2 + taskIntroRectWidth / 2, creatorH / 2 + taskIntroRectHeight / 2,
		creatorW / 2 - taskIntroRectWidth / 2, creatorH / 2 + taskIntroRectHeight / 2,
	};


	//pause vars
	VertexArray* pauseVA;
	VertexBuffer* pauseVB;
	float pauseRectWidth = 300.0f;
	float pauseRectHeight = 60.0f;
	float pauseVertices[8] =
	{
		creatorW / 2 - pauseRectWidth / 2, creatorH / 2 - pauseRectHeight / 2,
		creatorW / 2 + pauseRectWidth / 2, creatorH / 2 - pauseRectHeight / 2,
		creatorW / 2 + pauseRectWidth / 2, creatorH / 2 + pauseRectHeight / 2,
		creatorW / 2 - pauseRectWidth / 2, creatorH / 2 + pauseRectHeight / 2,
	};

	//menu vars
	VertexArray* menuVA;
	VertexBuffer* menuVB;
	float menuRectWidth = 300.0f;
	float menuRectHeight = 60.0f;
	float menuVertices[8] =
	{
		0.0f, 0.0f,
		menuRectWidth, 0.0f,
		menuRectWidth, menuRectHeight,
		0.0f, menuRectHeight
	};
	int count = 1;
public:
	std::mt19937 gen;

	BaseGame(int level, std::string typeOfGame, int startW, int startH, int creatorW, int creatorH, std::string typeOfTimer);
	~BaseGame();


	virtual void HandleTimerBar();
	virtual void DrawPause();
	virtual void UpdateAmountOfRounds();
	virtual void DrawAmountOfRounds();

	virtual void Draw();
	virtual void Update();

	virtual void HandleViewport(int nowW, int nowH, int creatorW, int creatorH, int startW, int startH);
	virtual void HandleShaders(int nowW, int nowH, int creatorW, int creatorH, int startW, int startH);


	//text
	virtual void RenderText(std::string text, float x, float y, float scale, glm::vec3 color, int shader);
	virtual void CreateTextToRect(std::string text, float scale, float rectX, float rectY, float rectW, float rectH, float r, float g, float b, int shader);
	virtual void CreateText(std::string text, float scale, float posX, float posY, float r, float g, float b, int shader);
	virtual void EnableBlending();
	virtual void DisableBlending();
	virtual void LoadFont();
	virtual glm::vec2 CalculateTextSize(const std::string& text, float scale);
	virtual void KeyPressed(wxKeyEvent& event) {}

	virtual void SetGameStarted(bool v);


	virtual void UpdateTime();
	virtual void HoverButtons(int x, int y) {}
	std::vector<float> GetBaseGameScreenDefaultSize();
	virtual std::vector<float> GetGameScreenDefaultSize();

	void SetPause(bool v);

	virtual void LoadAllGraphics();
	void LoadMenuGraphics();
	void LoadCountDownGraphics();
	void LoadPauseGraphics();

	void LoadTasksIntroGraphics();
	void SetScreenSize(float w, float h);
	void SetStartSize(float w, float h);
	virtual std::vector<float> GetCreatorSize() { return std::vector<float>(); };

	virtual void DrawText() {};
	void DrawCountDown();
	void DrawMenu();
	void DrawTasksIntroGraphics();
	void InitShaders();
	void ChangePause();
	virtual void LeftClickBtn(float xPos, float yPos) {};
	virtual bool CheckBtnClicked(float xPos, float yPos, float creatorW, float creatorH, float btnW, float btnH, float btnX, float btnY);
	virtual void RightClickBtn(int xPos, int yPos) {};
	std::vector<float> GetStartSize();
	float GetStartWidth();
	float GetStartHeight();
	void SetFocusBack(wxGLCanvas* canvas);
	void SetFocusBackTimer();
	std::string GetTypeOfGame();
	virtual void OptionBtnPressed(int btn) {};
	virtual std::vector<bool> GetButtons();
	virtual void HandleImageStaticShader() {};
	virtual void HandleNormalFlexibleShader() {};
	bool CheckEnterRect(float xPos, float yPos, float creatorW, float creatorH, float btnW, float btnH, float btnX, float btnY);



	virtual void neco();



	virtual std::vector<float> GenerateCircle(glm::vec2 spawnPoint, float radius, int numSegments);       //0 = smallest, 1 = mid, 2, biggest
	virtual std::vector<float> GenerateTriangle(glm::vec2 spawnPoint, float baseLength, float lineLength);
	virtual std::vector<float> GenerateSquare(glm::vec2 spawnPoint, float size);
	virtual std::vector<float> GenerateRectangle(glm::vec2 spawnPoint, float width, float height);
	virtual std::vector<float> GenerateStar(glm::vec2 center, float outerRadius, float innerRadius, int numPoints = 5);
	virtual std::vector<float> GenerateOctagon(glm::vec2 center, float radius);;
	virtual std::vector<float> GenerateHexagon(glm::vec2 center, float radius);

	//static std::mt19937& getGenerator();

};

