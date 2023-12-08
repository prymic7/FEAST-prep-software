#include "ShapesPositions.h"


ShapePositions::ShapePositions(int columnsCount, int rowsCount, int rectangleCount) : columnsCount(columnsCount), rowsCount(rowsCount), 
rectangleCount(rectangleCount)
{
	gen = std::mt19937(std::random_device{}());
	ShapePositions::GenerateShapes(columnsCount, rowsCount, rectangleCount, 30);
}

ShapePositions::~ShapePositions()
{

}

void ShapePositions::GenerateShapes(int columns, int rows, int numOfRects, int numOfShapes)
{
	std::uniform_int_distribution<> xDistrib(0, columns - 1);
	std::uniform_int_distribution<> yDistrib(0, rows - 1);
	int randomX = 0;
	int randomY = 0;
	std::pair<int, int> randomPair;

	for (int j = 0; j < numOfShapes; j++)
	{
		std::vector<std::pair<int, int>> shape;
		for (int i = 0; i < numOfRects; i++)
		{
			do
			{
				randomX = xDistrib(gen);
				randomY = yDistrib(gen);
				randomPair = { randomX, randomY };
			} while (std::find(shape.begin(), shape.end(), randomPair) != shape.end());
			shape.push_back(randomPair);
		}
		allShapes.push_back(shape);
	}
}

std::vector<std::pair<int, int>> ShapePositions::GetRandomShape()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::shuffle(allShapes.begin(), allShapes.end(), gen);

	do
	{
		std::shuffle(allShapes.begin(), allShapes.end(), gen);
	} while (std::find(usedShapes.begin(), usedShapes.end(), allShapes[0]) != usedShapes.end());

	usedShapes.push_back(allShapes[0]);
	return allShapes[0];
}