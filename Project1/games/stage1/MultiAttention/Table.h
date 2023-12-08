#pragma once
#include "../../BaseGame.h" 
#include <wx/wx.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Table
{
	int columnsCount;
	int rowsCount;
	float rectSize;
	float firstRectX;
	float firstRectY;
	int tableNum;
	float creatorW;
	float creatorH;
	float spaceFromBorder = 125.0f;

	std::vector<std::pair<int, int>> tableCoords;
	std::vector<float> tableVertices;
	std::vector<GLushort> tableIndices;

	IndexBuffer* tableIB;
	VertexArray* tableVA;
	VertexBuffer* tableVB;
	VertexBufferLayout* tableVBL;
	ShaderProgram* flexibleShaderProgram;

	float tableColor[4] = {0.2f, 0.2f, 0.2f, 1.0f};



public:
	Table(int columnsCount, int rowsCount, float rectSize, int tableNum, float creatorW, float creatorH, ShaderProgram* flexibleShaderProgram);
	~Table();

	void Draw();
	void Update();
	void LoadAllGraphics();
	void CreateTable();
	inline std::pair<float, float> GetTableStart() { return std::pair<float, float>(firstRectX, firstRectY); }
	inline float GetRectSize() { return rectSize; }



};

