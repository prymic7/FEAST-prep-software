#pragma once
#include "../../BaseGame.h"
#include <wx/wx.h>
#include <chrono>
#include <random>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameSpotTheSide : public BaseGame
{

	std::string shapes[4] = { "circle", "triangle", "square", "rectangle" };
	
	std::vector<std::string> typeOfQuestion;
	std::vector<glm::vec2> spawnPositions;
	std::vector<glm::vec2> guessingSpawnPositions;
	std::vector<glm::vec2> fakeSpawnPositions;
	std::vector<glm::vec2> finishedSpawnPositions;
	std::vector<glm::vec2> sideSpawnPositions;


	std::vector<std::string> shapesToDraw;
	std::vector<std::string> directions;
	glm::vec2 searchedShapePosition;
	glm::vec2 sideSearchedShapePosition;
	glm::vec2 fakeShapePosition;
	std::string activeDirection;
	std::string activeQuestion;
	std::string questionString;
	std::string shapeLookingFor;
	std::string doubleShape;
	bool bigFirstSide = false;

	bool sideActiveInt;
	bool onSide = false;
	bool sideSearchedShapeBig = false;
	bool sideSearchedShapeSmall = false;
	int firstSmallOrBig; // i=0 side shape
	int secondSmallOrBig; // i=1 side shape

	int papaja = 0;
	int trotl = 0;


	int leftRight; //prvni z leva je minus
	int upDown;
	int backFront;
	int finalSide;
	int correctAnswer;
	bool answeredCorrectly;
	int firstSideObjectPosition;
	int secondSideObjectPosition;



	int typeOfRound[4] = { 0,1,2,3 };
	int numOfShapes;
	int iteratorNumOfShapes;

	int borderMargin;
	VertexArray* trianglikVA;
	VertexArray* trianglik2VA;
	VertexBuffer* trianglikVB;
	VertexBuffer* trianglik2VB;
	VertexBufferLayout* trianglikVBL;

	VertexArray* circlikVA;
	VertexArray* circlik2VA;
	VertexBuffer* circlikVB;
	VertexBuffer* circlik2VB;


	VertexArray* rectikVA;
	VertexArray* rectik2VA;
	VertexBuffer* rectikVB;
	VertexBuffer* rectik2VB;
	VertexBufferLayout* rectikVBL;

	VertexArray* squarikVA;
	VertexArray* squarik2VA;
	VertexBuffer* squarikVB;
	VertexBuffer* squarik2VB;
	VertexBufferLayout* squarikVBL;

	float shapeDiameter = 40.0;

	std::vector<float> circleReal;
	std::vector<float> triangleReal;
	std::vector<float> squareReal;
	std::vector<float> rectangleReal;

	std::vector<float> circleSecond;
	std::vector<float> triangleSecond;
	std::vector<float> squareSecond;
	std::vector<float> rectangleSecond;

	bool circleBufferChange = false;
	bool triangleBufferChange = false;
	bool squareBufferChange = false;
	bool rectangleBufferChange = false;


	int tap = 0;
	int triangleCount = 0;
	int circleCount = 0;
	int squareCount = 0;
	int rectangleCount = 0;

	unsigned int texture1, texture2;
	unsigned int VBO, VAO, EBO;
	int width_pic;
	int height_pic;
	int channels_pic;
	STBimage* imageFront;
	STBimage* imageBack;
	STBimage* imageSide;


	float pictureVertices[32] = {
		// positions          // colors           // texture coords
		 0.5f,  0.25f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.25f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.25f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.25f,    1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};



	float vertices[32] = {
		// positions          // colors           // texture coords
		 0.2f,  0.6f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.2f, -0.6f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.2f, -0.6f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.2f,  0.6f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	
	GLushort pictureIndices[6] =
	{
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};

	unsigned int indices[6] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};

	VertexArray* imageVA;
	VertexBuffer* imageVB;
	IndexBuffer* imageIB;
	VertexBufferLayout* imageVBL;

	bool circleDrawOn = false;
	bool triangleDrawOn = false;
	bool squareDrawOn = false;
	bool rectangleDrawOn = false;

	bool secondCircleDrawOn = false;
	bool secondTriangleDrawOn = false;
	bool secondSquareDrawOn = false;
	bool secondRectangleDrawOn = false;

	bool imageFrontDrawOn = false;
	bool imageBackDrawOn = false;
	bool imageSideDrawOn = false;
	//bool imageLooksRight = false;
	//bool imageLookLeft = false;

	bool leftSideAnswer = false;
	bool rightSideAnswer = false;

	

	float pauseRectWidth = 200.0f;
	float pauseRectHeight = 60.0f;
	float pauseVertices[8] =
	{
		creatorW / 2 - pauseRectWidth / 2, creatorH / 2 - pauseRectHeight / 2,
		creatorW / 2 + pauseRectWidth / 2, creatorH / 2 - pauseRectHeight / 2,
		creatorW / 2 + pauseRectWidth / 2, creatorH / 2 + pauseRectHeight / 2,
		creatorW / 2 - pauseRectWidth / 2, creatorH / 2 + pauseRectHeight / 2,
	};


	float rectangleWidth = 100.0f;
	float rectangleHeight = 30.0f;

	float ballRadius = 15.0f;

	float squareWidth = 60.0f;
	float squareHeight = 60.0f;




public:
	GameSpotTheSide(int level, std::string typeOfGame, int startW, int startH, int creatorW, int creatorH, std::string typeOfTimer);
	~GameSpotTheSide();

	void Draw() override;
	void Update() override;
	void DrawText() override;
	void LeftClickBtn(float xPos, float yPos) override;
	void LoadAllGraphics() override;
	void LoadShapesGraphics();
	void DrawGraphics();
	void GenerateCircle(glm::vec2 spawnPoint, bool secondShape, int size);//0 = smallest, 1 = mid, 2, biggest
	void GenerateTriangle(glm::vec2 spawnPoint, bool secondShape, int size);
	void GenerateSquare(glm::vec2 spawnPoint, bool secondShape, int size);
	void GenerateRectangle(glm::vec2 spawnPoint, bool secondShape, int size);
	void CreateQuestion();
	void HandleShaders(int nowW, int nowH, int creatorW, int creatorH, int startW, int startH) override;
	void ChooseLayout();
	void GenerateSpawnPositions();
	void DeleteSearchedPosition();


	void OptionBtnPressed(int btn) override;
	void UpdateTime() override;
	void HandleViewport(int nowW, int nowH, int creatorW, int creatorH, int startW, int startH) override;
	void ChangeVertices();
	void HandleImageStaticShader() override;
	void HandleNormalFlexibleShader() override;


};

