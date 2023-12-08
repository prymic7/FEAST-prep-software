#pragma once
#include "../../BaseGame.h"
#include "Table.h"
#include "ShapesPositions.h"
#include <wx/wx.h>
#include <chrono>
#include <random>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameMultiAttention : public BaseGame
{

	std::vector<char> mathOperators = {'+', '-', '/', '*'};
	//std::vector<char> mathOperators = { '+', '-', '*' };
	// 
	//const char* addition = mathOperators[0];  // Contains "+"
	//const char* subtraction = mathOperators[1];  // Contains "-"
	//const char* division = mathOperators[2];  // Contains "/"
	//const char* multiplication = mathOperators[3];  // Contains "*"

	std::chrono::steady_clock::time_point timeMath;
	int rectanglesChangeMilisecs;
	int milisecsOfRoundGoing;
	int miniRoundsDone;

	int correctTableAnswer;
	int wrongTableAnswer;
	int totalTableExamples;



	bool mathExampleCorrect;
	int foku = 0;
	int totalMathExamplesCount;
	int correctMathExamplesCount;
	int wrongMathExamplesCount;
	int missedRectangleExamplesCount;
	int missedMathExamplesCount;

	int deformationChances[2] = {0, 1};
	int sideChances[2] = { 1, 2 };

	bool deformationOn;
	std::vector<std::pair<int, int>> activeShape;
	std::vector<std::pair<int, int>> activeDefShape;


	ShapePositions* shapes;
	Table* table1;
	Table* table2;

	int correctAnswer;
	int totalCount;

	int tableW = 22;
	int tableH = 11;

	int milisecsOfMathGoing;
	int mathExampleMilisecs;

	bool missedInputForMath = false;
	bool correctAnswerForMath = false;
	bool wrongAnswerForMath = false;


	std::vector<float> shape1Vertices;
	std::vector<float> shape2Vertices;
	std::pair<int, int> table1StartPos;
	std::pair<int, int> table2StartPos;
	float rectSize;
	bool drawingOn = false;

	int columnsCount;
	int rowsCount;
	int rectangleCount;
	int deformationCount;


	IndexBuffer* shapeIB1;
	VertexArray* shapeVA1;
	VertexBuffer* shapeVB1;
	VertexBufferLayout* shapeVBL1;

	std::vector<GLushort> shape1Indices;
	std::vector<GLushort> shape2Indices;


	IndexBuffer* shapeIB2;
	VertexArray* shapeVA2;
	VertexBuffer* shapeVB2;
	VertexBufferLayout* shapeVBL2;

	std::vector<int> evenNumbers;
	std::vector<int> divisorNumbers;

	bool boolec = false;
	std::string mathProblemStr = "";


public:
	GameMultiAttention(int level, std::string typeOfGame, int startW, int startH, int creatorW, int creatorH, std::string typeOfTimer);
	~GameMultiAttention();


	void Draw() override;
	void Update() override;
	void DrawText() override;

	void CreateMathProblem(int maximumNum, int minimumNum, int segmentMinNumberCount, int segmentMaxNumberCount, std::vector<char> mathOperators, int segmentMinCount = 1, int segmentMaxCount = 1);
	//smallest number, biggest number, minimal count of segments, maximal count of segments, min. count of numbers in segments, max. count of numbers in segments, operators
	void LoadAllGraphics() override;
	void UpdateTime() override;
	void DrawShapes();
	void DrawMathText();
	void GetRandomShape();
	void OptionBtnPressed(int btn) override;
	void DeformateShape();
	void DrawInputText();
	bool ChooseIfDeformated();

};

