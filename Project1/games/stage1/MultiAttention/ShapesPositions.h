#pragma once
#include <wx/wx.h>
#include <chrono>
#include <random>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ShapePositions
{
	std::vector<std::vector<std::pair<int, int>>> allShapes;
	std::vector<std::vector<std::pair<int, int>>> usedShapes;
	std::vector<std::pair<int, int>> usedPairs;
	std::mt19937 gen;

	int columnsCount;
	int rowsCount;
	int rectangleCount;
	int deformationCount;

public:
	ShapePositions(int columnsCount, int rowsCount, int rectangleCount);
	~ShapePositions();

	inline std::vector<std::vector<std::pair<int, int>>> GetAllShapes() { return allShapes; };
	std::vector<std::pair<int, int>> GetRandomShape();
	void GenerateShapes(int columns, int rows, int numOfRects, int numOfShapes);

};



