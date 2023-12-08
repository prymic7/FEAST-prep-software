#pragma once
#include "../../BaseGame.h"
#include "PlaygroundRect.h"
#include <wx/wx.h>
#include <chrono>
#include <random>
#include <array>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameDividedAttention : public BaseGame 
{
	int playRectCount;
	

	int conflictTurnedOn;
	bool clickedConflict;

	PlaygroundRect* playgroundRect1; 
	PlaygroundRect* playgroundRect2;
	PlaygroundRect* playgroundRect3;
	PlaygroundRect* playgroundRect4;

	std::vector<PlaygroundRect*> playgroundsVec;

	float rectW;
	float rectH;
	std::vector<float>dividedRects;
	float rectSpacing = 20;

	VertexArray* rect1VA;
	VertexBuffer* rect1VB;
	VertexBufferLayout* rect1VBL;
	IndexBuffer* twoRectanglesIB;
	IndexBuffer* threeRectanglesIB;
	int collidedCount = 0;
	int milisecsOfCollision;
	int milisecsOfCollideAgain = 500;
	int milisecsOfTimeToResponse = 3000;
	std::vector<std::chrono::steady_clock::time_point> timeVec;
	bool missedInput;
	bool correctInput;
	bool wrongInput;

	std::chrono::steady_clock::time_point timeToDeleteText;
	int milisecsOfDisplayingText = 2000;
	int milisecsOfKeyPressed;

	int countCorrectInput = 0;
	int countWrongInput = 0;
	int countMissedInput = 0;
	int totalCollisions = 0;




	GLushort twoRectanglesIndices[12] = //LT, RT, RD, LD
	{
		0, 1, 2,
		0, 2, 3,

		4,5,6,
		4,6,7
	};

	GLushort threeRectanglesIndices[24] = //LT, RT, RD, LD
	{
		0, 1, 2,
		0, 2, 3,

		4,5,6,
		4,6,7,

		8,9,10,
		8,10,11,

		12,13,14,
		12,14,15

	};

	VertexArray* ballVA;
	VertexBuffer* ballVB;
	VertexBufferLayout* ballVBL;
	IndexBuffer* ballIB;
	float jebaci[6] =
	{
		200.0f, 200.0f,
		500.0f, 200.0f,
		500.0f, 500.0f,
	};

	
public:
	GameDividedAttention(int level, std::string typeOfGame, int startW, int startH, int creatorW, int creatorH, std::string typeOfTimer);
	~GameDividedAttention();

	void DrawPlaygrounds() {};
	void UpdatePlaygrounds() {};
	void DrawRectangles();
	void CreateRactangles();
	void ResetInput();

	
	void KeyPressed(wxKeyEvent& event) override;
	void HandleCollisionTime();
	void LoadRectanglesGraphics();
	void CheckCollision();
	void Draw() override;
	void Update() override;
	void DrawText() override;
	void LeftClickBtn(float xPos, float yPos) override;
	void LoadAllGraphics() override;
};


