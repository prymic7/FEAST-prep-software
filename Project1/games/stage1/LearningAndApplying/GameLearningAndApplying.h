#pragma once
#include "../../BaseGame.h"
#include <wx/wx.h>
#include <chrono>
#include <random>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <unordered_map>


class GameLearningAndApplying : public BaseGame
{
    int miniRoundsDone = 0;

    std::unordered_map<std::string, std::vector<float>> colorDictionary;
    std::vector<std::string> colorKeys = { "red", "blue", "yellow", "green", "orange", "purple", "pink" };

    bool shitCoding = false;
    int asShape;
    int asShape2;
    int asColor;
    int allShape;
    int allColor;

    std::string lastTime;

    std::string thisAsShape;
    std::string thisAsColor;

    std::string asThat;
    std::string allThat;
    std::string allObjectString;
    std::string byWhat;
    std::vector<std::string> allObjectStringVec;
    std::vector<std::string> byWhatVec;
    std::vector<std::string> asColorVec;
    std::vector<std::string> allColorVec;
    std::vector<std::string> asThatVec;
    std::vector<std::string> allThatVec;

    int specialRuleStringY = 280.0f;
    bool thisAsOn = false;
    bool allObjectAsOn = false;

    std::string thisAsString;


	int miniRoundMilisecs;
	int numOfBtns;
    std::vector<std::string> shapes = { "star", "circle", "triangle", "octagon", "hexagon", "square", "rectangle" };
    std::vector<std::string> shapesChill = { "star", "circle", "triangle", "octagon", "hexagon", "square", "rectangle" };
    std::vector<std::string> newCreatedColors = {};
    std::vector<std::string> numbers1 = { "0-249", "250-499", "500-749", "750-999" };
    std::string numbersOrShapes[2] = {"shapes", "numbers"};
    std::string activeNumberOrShape;
	std::string basicRules1[2] = { "byNumber", "byColor" };
    std::string basicRules2[2] = { "byShape", "byColor" };
    std::vector<std::string> specialShapesLookingFor;
    int secondExample[2] = {0, 1};
    int secondSameExample[4] = { 0, 0, 0, 1 };
    int specialRule[2] = { 0, 1 };
    bool specialRuleOn = false;
    std::string possibleSpecialRules[2] = { "thisAs", "allObjectAs", };
    std::string byColorByThat[2] = { "byColor", "byThat", };

    int luckyNumColorCrazy;
    bool secondExampleOn = false;
    bool secondSameExampleOn = false;
    bool specialRules = false;

    int specialBtnNum;
    bool secondShape;
    int randomSecondNumber;
    std::string randomSecondNumberColor;

    std::vector<float> circleGuessColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> triangleGuessColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> rectangleGuessColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> squareGuessColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> starGuessColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> hexagonGuessColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> octagonGuessColor = { 0.0f, 0.0f, 0.0f, 1.0f };

    std::vector<float> circleExampleColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> triangleExampleColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> rectangleExampleColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> squareExampleColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> starExampleColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> hexagonExampleColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> octagonExampleColor = { 0.0f, 0.0f, 0.0f, 1.0f };

    std::vector<float> circleSecondColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> triangleSecondColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> rectangleSecondColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> squareSecondColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> starSecondColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> hexagonSecondColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    std::vector<float> octagonSecondColor = { 0.0f, 0.0f, 0.0f, 1.0f };

    int btns[5] = {0, 1, 2, 3, 4};
    int btnIncludingCorrectAnswer;

    std::string mainExampleShape;
    std::string mainExampleColor;

    int mainExampleNumber;
    int randomNumber1;

    std::string activeRule;

    int roundsTillChangeRule;
    int roundsDone = 0;
    int numOfExamples = 1;

    const float width = 90.0f;
    const float height = 40.0f;

    int correctCount;
    int totalCount;

    //btns
    VertexArray* btns1VA;
    VertexBuffer* btns1VB;
    VertexArray* btns2VA;
    VertexBuffer* btns2VB;
    VertexArray* btns3VA;
    VertexBuffer* btns3VB;
    VertexArray* btns4VA;
    VertexBuffer* btns4VB;
    VertexArray* btns5VA;
    VertexBuffer* btns5VB;

    //example btns
    IndexBuffer* showIB;
    VertexArray* showVA;
    VertexBuffer* showVB;
    VertexBufferLayout* showVBL;

    //guessing opengl
    VertexArray* triangleVA;
    VertexBuffer* triangleVB;
    VertexBufferLayout* triangleVBL;

    VertexArray* circleVA;
    VertexBuffer* circleVB;

    VertexArray* rectangleVA;
    VertexBuffer* rectangleVB;
    VertexBufferLayout* rectangleVBL;

    VertexArray* squareVA;
    VertexBuffer* squareVB;
    VertexBufferLayout* squareVBL;

    VertexArray* hexagonVA;
    VertexBuffer* hexagonVB;
    VertexBufferLayout* hexagonVBL;

    VertexArray* octagonVA;
    VertexBuffer* octagonVB;
    VertexBufferLayout* octagonVBL;

    VertexArray* starVA;
    VertexBuffer* starVB;
    VertexBufferLayout* starVBL;

    //example opengl
    IndexBuffer* btnsIB2;
    VertexArray* btnsVA2;
    VertexBuffer* btnsVB2;
    VertexBufferLayout* btnsVBL2;

    IndexBuffer* showIB2;
    VertexArray* showVA2;
    VertexBuffer* showVB2;
    VertexBufferLayout* showVBL2;

    VertexArray* triangleVA2;
    VertexBuffer* triangleVB2;
    VertexBufferLayout* triangleVBL2;

    VertexArray* circleVA2;
    VertexBuffer* circleVB2;

    VertexArray* rectangleVA2;
    VertexBuffer* rectangleVB2;
    VertexBufferLayout* rectangleVBL2;

    VertexArray* squareVA2;
    VertexBuffer* squareVB2;
    VertexBufferLayout* squareVBL2;

    VertexArray* hexagonVA2;
    VertexBuffer* hexagonVB2;
    VertexBufferLayout* hexagonVBL2;

    VertexArray* octagonVA2;
    VertexBuffer* octagonVB2;
    VertexBufferLayout* octagonVBL2;

    VertexArray* starVA2;
    VertexBuffer* starVB2;
    VertexBufferLayout* starVBL2;

    VertexArray* triangleVA3;
    VertexBuffer* triangleVB3;
    VertexBufferLayout* triangleVBL3;

    VertexArray* circleVA3;
    VertexBuffer* circleVB3;

    VertexArray* rectangleVA3;
    VertexBuffer* rectangleVB3;
    VertexBufferLayout* rectangleVBL3;

    VertexArray* squareVA3;
    VertexBuffer* squareVB3;
    VertexBufferLayout* squareVBL3;

    VertexArray* hexagonVA3;
    VertexBuffer* hexagonVB3;
    VertexBufferLayout* hexagonVBL3;

    VertexArray* octagonVA3;
    VertexBuffer* octagonVB3;
    VertexBufferLayout* octagonVBL3;

    VertexArray* starVA3;
    VertexBuffer* starVB3;
    VertexBufferLayout* starVBL3;


    std::vector<float> rectangleVertices;
    std::vector<float> triangleVertices;
    std::vector<float> circleVertices;
    std::vector<float> squareVertices;
    std::vector<float> starVertices;
    std::vector<float> hexagonVertices;
    std::vector<float> octagonVertices;

    std::vector<float> rectangleVertices2;
    std::vector<float> triangleVertices2;
    std::vector<float> circleVertices2;
    std::vector<float> squareVertices2;
    std::vector<float> starVertices2;
    std::vector<float> hexagonVertices2;
    std::vector<float> octagonVertices2;

    std::vector<float> rectangleVertices3;
    std::vector<float> triangleVertices3;
    std::vector<float> circleVertices3;
    std::vector<float> squareVertices3;
    std::vector<float> starVertices3;
    std::vector<float> hexagonVertices3;
    std::vector<float> octagonVertices3;

    int answeredBtn = -1;
    int correctBtn = -1;
    float btnWidth = 160.0f;
    float btnHeight = 120.0f;
    float spaceBtnsExample = 30.0f;
    float spaceBtnsGuess = 30.0;


    float firstExampleX = creatorW / 2 - spaceBtnsExample - btnWidth;
    float firstExampleY = creatorH / 2 - btnHeight / 2;
    float secondExampleX = firstExampleX + spaceBtnsExample * 2 + btnWidth;

    float exampleFirstMiddleX = firstExampleX + btnWidth / 2;
    float exampleFirstMiddleY = firstExampleY + btnHeight / 2;
    float exampleSecondMiddleX = secondExampleX + btnWidth / 2;

    float exampleVertices[16] = {

        firstExampleX, firstExampleY,
        firstExampleX + btnWidth, firstExampleY,
        firstExampleX + btnWidth, firstExampleY + btnHeight,
        firstExampleX, firstExampleY + btnHeight,

        secondExampleX, firstExampleY,
        secondExampleX + btnWidth, firstExampleY,
        secondExampleX + btnWidth, firstExampleY + btnHeight,
        secondExampleX, firstExampleY + btnHeight,
    };

    std::vector<glm::vec2> exampleSpawnPositions = { glm::vec2(exampleFirstMiddleX, exampleFirstMiddleY), glm::vec2(exampleSecondMiddleX, exampleFirstMiddleY)};


    float firstBtnX = 85.0f;
    float firstBtnY = 500.0f;
    float secondBtnX = firstBtnX + spaceBtnsGuess + btnWidth;
    float thirdBtnX = secondBtnX + spaceBtnsGuess + btnWidth;
    float fourthBtnX = thirdBtnX + spaceBtnsGuess + btnWidth;
    float fifthBtnX = fourthBtnX + spaceBtnsGuess + btnWidth;

    float firstBtnMiddleX = firstBtnX + btnWidth / 2;
    float firstBtnMiddleY = firstBtnY + btnHeight / 2;

    float secondBtnMiddleX = secondBtnX + btnWidth / 2;
    float secondBtnMiddleY = firstBtnY + btnHeight / 2;

    float thirdBtnMiddleX = thirdBtnX + btnWidth / 2;
    float thirdBtnMiddleY = firstBtnY + btnHeight / 2;

    float fourthBtnMiddleX = fourthBtnX + btnWidth / 2;
    float fourthBtnMiddleY = firstBtnY + btnHeight / 2;

    float fifthBtnMiddleX = fifthBtnX + btnWidth / 2;
    float fifthBtnMiddleY = firstBtnY + btnHeight / 2;

    std::vector<glm::vec2> guessesSpawnPositions = {
        {firstBtnMiddleX, firstBtnMiddleY},
        {secondBtnMiddleX, secondBtnMiddleY},
        {thirdBtnMiddleX, thirdBtnMiddleY},
        {fourthBtnMiddleX, fourthBtnMiddleY},
        {fifthBtnMiddleX, fifthBtnMiddleY}
    };

    std::vector<float> allBtnXs = { firstBtnX, secondBtnX, thirdBtnX, fourthBtnX, fifthBtnX };

    float circleRadius = btnWidth / 3.3f;
    int numSegments = 25;
    float lineLength = btnWidth / 3.1f;
    float baseLength = btnWidth / 2.5f;
    float squareSize = btnWidth / 1.75f;
    float rectWidth = btnWidth / 1.3f;
    float rectHeight = btnWidth / 2.3f;
    float outerRadius = btnWidth / 2.85f;
    float innerRadius = btnWidth / 5.5f;
    int startPoints = 5;
    float hexagonRadius = btnWidth / 3.2f;
    float octagonRadius = btnWidth / 3.2f;

    bool guessCircleDrawOn = false;
    bool guessTriangleDrawOn = false;
    bool guessSquareDrawOn = false;
    bool guessRectangleDrawOn = false;
    bool guessStarDrawOn = false;
    bool guessHexagonDrawOn = false;
    bool guessOctagonDrawOn = false;

    bool exampleCircleDrawOn = false;
    bool exampleTriangleDrawOn = false;
    bool exampleSquareDrawOn = false;
    bool exampleRectangleDrawOn = false;
    bool exampleStarDrawOn = false;
    bool exampleHexagonDrawOn = false;
    bool exampleOctagonDrawOn = false;

    bool secondCircleDrawOn = false;
    bool secondTriangleDrawOn = false;
    bool secondSquareDrawOn = false;
    bool secondRectangleDrawOn = false;
    bool secondStarDrawOn = false;
    bool secondHexagonDrawOn = false;
    bool secondOctagonDrawOn = false;

    bool btn1Hovering = false;
    bool btn2Hovering = false;
    bool btn3Hovering = false;
    bool btn4Hovering = false;
    bool btn5Hovering = false;


    float btnVertices1[8] = 
    {
        firstBtnX, firstBtnY,        
        firstBtnX + btnWidth, firstBtnY,       
        firstBtnX + btnWidth, firstBtnY + btnHeight,
        firstBtnX, firstBtnY + btnHeight,
    };
    float btnVertices2[8] =
    {

        secondBtnX, firstBtnY,
        secondBtnX + btnWidth, firstBtnY,
        secondBtnX + btnWidth, firstBtnY + btnHeight,
        secondBtnX, firstBtnY + btnHeight,
    };
    float btnVertices3[8] =
    {

        thirdBtnX, firstBtnY,
        thirdBtnX + btnWidth, firstBtnY,
        thirdBtnX + btnWidth, firstBtnY + btnHeight,
        thirdBtnX, firstBtnY + btnHeight,
    };
    float btnVertices4[8] =
    {
        fourthBtnX, firstBtnY,
        fourthBtnX + btnWidth, firstBtnY,
        fourthBtnX + btnWidth, firstBtnY + btnHeight,
        fourthBtnX, firstBtnY + btnHeight,
    };
    float btnVertices5[8] =
    {
        fifthBtnX, firstBtnY,
        fifthBtnX + btnWidth, firstBtnY,
        fifthBtnX + btnWidth, firstBtnY + btnHeight,
        fifthBtnX, firstBtnY + btnHeight,
    };

    GLushort showIndices[12] = //LT, RT, RD, LD
    {
        0, 1, 2,
        0, 2, 3,
        4, 5, 6,
        4, 6, 7
    };

public:
	GameLearningAndApplying(int level, std::string typeOfGame, int startW, int startH, int creatorW, int creatorH, std::string typeOfTimer);
	~GameLearningAndApplying();

	void Draw() override;
	void Update() override;
	void DrawText() override;
	void LeftClickBtn(float xPos, float yPos) override;
	void LoadAllGraphics() override;
    void LoadButtonGraphics();
    void LoadShapeGraphics();
	void UpdateTime() override;
	void DrawGraphics();
    void ChooseExample();
    void ChooseRule();
    void ChooseNumbersOrShapes();
    void ChooseBtnGraphics();
    void ChooseWhatToDraw(std::string decider, int i, std::string which); // ->which = example or guess btn
    void AssignColorsToShapes(std::string decider, std::string mainExampleColor, std::string which);
    void HoverButtons(int x, int y) override;
    void SetSecondExample();
    void ChooseSpecialRules();
};

