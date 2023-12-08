#pragma once
#include "../../BaseGame.h"
#include <wx/wx.h>
#include <chrono>
#include <random>
#include <array>


class GameHeadingConflicts : public BaseGame
{
	int trianglesCount;

	//bool verticalConflicts = false;
	//bool horizontalConflicts = false;
	//bool doubleConflicts = false;
	std::string typeOfConflict;
	bool correctAnswer;
	bool wrongAnswer;

	float lineLength;
	float baseLength;
	bool conflictTurnedOn;
	int conflictTurnedOnHolder[2] = { 0, 1 };
	std::string directionHolder[2] = { "vertical", "horizontal" };

	IndexBuffer* triangleCollidingIB;
	VertexArray* triangleCollidingVA;
	VertexBuffer* triangleCollidingVB;
	VertexBufferLayout* triangleCollidingVBL;

	IndexBuffer* triangleIB;
	VertexArray* triangleVA;
	VertexBuffer* triangleVB;
	VertexBufferLayout* triangleVBL;

	std::vector<glm::vec2> trianglePositions;
	std::vector<glm::vec2> triangleCollidingPositions;

	std::vector<int> triangleAngles = { 0, 20, 40, 60, 70, 110, 120, 140, 150, 190, 220, 240, 250, 290, 300, 320, 340, 345 };
	std::vector<glm::vec2> storedPositions;

	float generateDistanceFromBorder = 100.0f;


	GLuint VBO2, VAO2; 
	int count = 0;


public:
	GameHeadingConflicts(int level, std::string typeOfGame, int startW, int startH, int creatorW, int creatorH, std::string typeOfTimer);
	~GameHeadingConflicts();

	void UpdateTime() override;
	void Update() override;
	void Draw() override;
	void DrawText() override;
	void LoadAllGraphics() override;

	void DecideDirection();
	void DrawTriangles();
	void UpdateTriangles();
	void GenerateTrianglesPositions(int count);
	void GenerateCollidingTrianglesPositions();
	void CreateNewTriangleGroup();
	void LoadTriangleGraphics();
	void ClearTriangles();
	void DecideConflictOn();
	void OptionBtnPressed(int btn) override;
	
};

