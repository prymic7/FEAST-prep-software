#include "Table.h"


Table::Table(int columnsCount, int rowsCount, float rectSize, int tableNum, float creatorW, float creatorH, ShaderProgram* flexibleShaderProgram) : columnsCount(columnsCount), rowsCount(rowsCount), rectSize(rectSize), 
tableNum(tableNum), creatorW(creatorW), creatorH(creatorH), flexibleShaderProgram(flexibleShaderProgram)
{
	if (tableNum == 1)
	{
		firstRectX = spaceFromBorder;
	}
	else if (tableNum == 2)
	{
		firstRectX = creatorW - spaceFromBorder - (columnsCount * rectSize);
	}

	firstRectY = (creatorH - (rowsCount * rectSize)) / 2;

	Table::CreateTable();
}

void Table::CreateTable()
{
	for (int i = 0; i < columnsCount; i++)
	{
		for (int j = 0; j < rowsCount; j++)
		{
			tableCoords.push_back({ i, j });
			float rectX = firstRectX + (i * rectSize);
			float rectY = firstRectY + (j * rectSize);

			// LT - left top
			tableVertices.push_back(rectX);
			tableVertices.push_back(rectY);

			// RT - right top
			tableVertices.push_back(rectX + rectSize);
			tableVertices.push_back(rectY);

			// RD - right bottom
			tableVertices.push_back(rectX + rectSize);
			tableVertices.push_back(rectY + rectSize);

			// LD - left bottom
			tableVertices.push_back(rectX);
			tableVertices.push_back(rectY + rectSize);

			tableIndices.push_back((i * rowsCount + j) * 4);
			tableIndices.push_back((i * rowsCount + j) * 4 + 1);

			tableIndices.push_back((i * rowsCount + j) * 4 + 1);
			tableIndices.push_back((i * rowsCount + j) * 4 + 2);

			tableIndices.push_back((i * rowsCount + j) * 4 + 2);
			tableIndices.push_back((i * rowsCount + j) * 4 + 3);

			tableIndices.push_back((i * rowsCount + j) * 4 + 3);
			tableIndices.push_back((i * rowsCount + j) * 4);
		}
	}
}

void Table::LoadAllGraphics()
{
	tableIB = new IndexBuffer((columnsCount* rowsCount) * 8, tableIndices.data());
	tableVA = new VertexArray();
	tableVB = new VertexBuffer(tableVertices.size() * sizeof(std::vector<float>), tableVertices.data(), "static");
	tableVBL = new VertexBufferLayout();

	tableVBL->Push<float>(2);
	tableVA->AddBuffer(tableVB, tableVBL);

}

void Table::Draw()
{
	GLCall(flexibleShaderProgram->Bind());
	GLCall(flexibleShaderProgram->SetUniform4f("u_Color", tableColor[0], tableColor[1], tableColor[2], tableColor[3]));
	tableVA->Bind();
	tableIB->Bind();
	GLCall(glDrawElements(GL_LINES, 8 * columnsCount * rowsCount, GL_UNSIGNED_SHORT, nullptr));
}

void Table::Update()
{

}

Table::~Table()
{

}
