#include "GameMultiAttention.h"

//w: 11
//h: 22
GameMultiAttention::GameMultiAttention(int level, std::string typeOfGame, int startW, int startH, int creatorW, int creatorH, std::string typeOfTimer)
	: BaseGame(level, typeOfGame, startW, startH, creatorW, creatorH, typeOfTimer)
{
	for (int i = 0; i < 200; i++)
	{
		if (i % 2 == 0)
		{
			evenNumbers.push_back(i);
		}
	}

	timeMath = std::chrono::steady_clock::now();;
	textTime = std::chrono::steady_clock::now();
	this->creatorW = creatorW;
	this->creatorH = creatorH;
	this->level = level;
	this->typeOfGame = typeOfGame;
	timer = true;

	columnsCount = 11;
	rowsCount = 22;

	textTimeMilisecsSolid = 2000;

	if (typeOfGame == "practice")
	{
		if (level == 1)
		{
		}
		else if (level == 2)
		{
		}
		else if (level == 3)
		{
			roundTimeMilisecs = 10000;
			deformationCount = 3;
			rectangleCount = 30;
			mathExampleMilisecs = 13000;
		}
	}
	else if (typeOfGame == "test")
	{
	}

	shapes = new ShapePositions(columnsCount, rowsCount, rectangleCount);
	table1 = new Table(columnsCount, rowsCount, 20.0f, 1, creatorW, creatorH, flexibleShaderProgram);
	table2 = new Table(columnsCount, rowsCount, 20.0f, 2, creatorW, creatorH, flexibleShaderProgram);


	table1StartPos = table1->GetTableStart();
	table2StartPos = table2->GetTableStart();
	rectSize = table1->GetRectSize();

	GameMultiAttention::GetRandomShape();
	GameMultiAttention::CreateMathProblem(2, 100, 3, 3, mathOperators, 2, 2);


	//wxString str = wxString::Format("mathStr: %s", mathProblemStr);
	//wxLogStatus(str);
}

void GameMultiAttention::CreateMathProblem(int minimumNum, int maximumNum, int segmentMinNumberCount, int segmentMaxNumberCount, std::vector<char> mathOperators, int segmentMinCount /*= 1*/, int segmentMaxCount /*= 1*/)

{
	mathProblemStr = "";
	//smallest number, biggest number, min. count of segments, max. count of segments, min. count of numbers in segments, max. count of numbers in segments, operators
	std::uniform_int_distribution<> numDistrib(minimumNum, maximumNum);
	std::uniform_int_distribution<> segmentsDistrib(segmentMinCount, segmentMaxCount);
	std::uniform_int_distribution<> countOfNumsInSegmentDistrib(segmentMinNumberCount, segmentMaxNumberCount);

	int result = 0; // result of the whole math problem
	int number = 0; // generated numnber
	int segmentCount = segmentsDistrib(gen); //count of segments
	int countOfNumsInSegment = 0; //count of numbers in segments

	bool poprvy = true;

	int papa = 0;
	for (int i = 0; i < segmentCount; i++)
	{
		std::string segmentStr;
		bool priority; //if segment will be prioritized -> (27 + 45) or 27 + 45
		int priorityArray[2] = { 0, 1 };
		std::shuffle(priorityArray, priorityArray + 2, gen);
		priority = priorityArray[0];
		priority = true;
		char segmentOp = mathOperators[0]; //operator connecting segments
		countOfNumsInSegment = countOfNumsInSegmentDistrib(gen); 

		std::vector<int> numsOfSegment; //vector including numbers in segment
		std::vector<char> operatorsOfSegment; //vector including operators in segment(operators connecting numbers in segment)
		int segmentResult; //result of segment

		for (int j = 0; j < countOfNumsInSegment; j++)
		{
			std::shuffle(mathOperators.begin(), mathOperators.end(), gen);
			char op = mathOperators[0];
			char lastOp;
			if (operatorsOfSegment.size() > 0)
			{
				lastOp = operatorsOfSegment[operatorsOfSegment.size() - 1];
				if (lastOp == '/') //manage there will be no residue 
				{
					int divided = 0;
					int divisor = 0;
					do
					{
						papa++;
						std::shuffle(evenNumbers.begin(), evenNumbers.end(), gen);
						divided = evenNumbers[0];
						bool noDivider = true;
						for (int k = 1; k < divided; k++)
						{
							if (divided % k == 0)
							{
								divisorNumbers.push_back(k);
							}
						}
						std::shuffle(divisorNumbers.begin(), divisorNumbers.end(), gen);
						divisor = divisorNumbers[0];
						numsOfSegment[numsOfSegment.size() - 1] = divided;
						number = divisor;

					} while (divided % divisor != 0 || papa < 300);
				}
				else
				{
					number = numDistrib(gen); // generating random number
				}
			}
			else
			{
				number = numDistrib(gen); // generating random number
			}

			numsOfSegment.push_back(number); //pushing number to vector of segment numbers
			operatorsOfSegment.push_back(mathOperators[0]);

			if (j != countOfNumsInSegment - 1)
			{
				segmentStr = segmentStr + std::to_string(number) + op;
			}
			else
			{
				segmentStr = segmentStr + std::to_string(number);
			}
		}

		if (i != 0)
		{
			if (countOfNumsInSegment == 1 || !priority)

			{
				mathProblemStr += segmentOp + segmentStr;

			}
			else 
			{
				mathProblemStr = mathProblemStr + segmentOp + " (" + segmentStr + ") ";
			}
		}
		else 
		{
			if (countOfNumsInSegment == 1 || !priority)
			{
				mathProblemStr = segmentStr;
			}
			else
			{
				mathProblemStr = " (" + segmentStr + ") ";
			}
		}
	}
	wxString str = wxString::Format("mathStr: %s", mathProblemStr);
	wxLogStatus(str);


	boolec = false;
}

void GameMultiAttention::DrawText()
{
	GameMultiAttention::DrawMathText();
	GameMultiAttention::DrawInputText();

}

void GameMultiAttention::DrawInputText()
{
	if (gameStarted)
	{
		if (correctAnswerForText)
		{
			BaseGame::CreateText("Correct!", 0.5f, creatorW / 2 - BaseGame::CalculateTextSize("Correct!", 0.5f).x / 2.0f, 100.0f, greenColor2[0], greenColor2[1], greenColor2[2], 1);
		}
		else if (wrongAnswerForText)
		{
			BaseGame::CreateText("Wrong! There is no match.", 0.5f, creatorW / 2 - BaseGame::CalculateTextSize("Wrong! There is no match.", 0.5f).x / 2.0f, 100.0f, redColor[0], redColor[1], redColor[2], 1);
		}
		else if (missedInputForText)
		{
			BaseGame::CreateText("Missed input.", 0.5f, creatorW / 2 - BaseGame::CalculateTextSize("Missed input.", 0.5f).x / 2.0f, 100.0f, redColor[0], redColor[1], redColor[2], 1);
		}

		if (correctAnswerForMath)
		{
			BaseGame::CreateText("Correct!", 0.5f, creatorW / 2 - BaseGame::CalculateTextSize("Correct!", 0.5f).x / 2.0f, 100.0f, greenColor2[0], greenColor2[1], greenColor2[2], 1);
		}
		else if (wrongAnswerForMath)
		{
			BaseGame::CreateText("Wrong! Right answer is", 0.5f, creatorW / 2 - BaseGame::CalculateTextSize("Wrong! There is no match.", 0.5f).x / 2.0f, 100.0f, redColor[0], redColor[1], redColor[2], 1);
		}
		else if (missedInputForMath)
		{
			BaseGame::CreateText("Missed input.", 0.5f, creatorW / 2 - BaseGame::CalculateTextSize("Missed input.", 0.5f).x / 2.0f, 100.0f, redColor[0], redColor[1], redColor[2], 1);
		}
	}
}

void GameMultiAttention::DrawMathText()
{

}

void GameMultiAttention::DeformateShape()
{
	activeDefShape = activeShape;

	int randomRect = 0;
	std::vector<int> usedRects;
	std::uniform_int_distribution<> countDistrib(0, rectangleCount - 1);
	std::uniform_int_distribution<> columnsDistrib(0, columnsCount - 1);
	std::uniform_int_distribution<> rowsDistrib(0, rowsCount - 1);

	bool poprvy = true;
	for (int i = 0; i < deformationCount; i++)
	{
		int randomColumn = columnsDistrib(gen);
		int randomRow = rowsDistrib(gen);

		std::pair<int, int> newPosOfRect = { randomColumn , randomRow };
		do
		{
			randomRect = countDistrib(gen);
		} while (std::find(usedRects.begin(), usedRects.end(), randomRect) != usedRects.end());
		usedRects.push_back(randomRect);

		activeDefShape[randomRect] = newPosOfRect;
	}
}

void GameMultiAttention::GetRandomShape()
{
	delete shapeIB1;
	delete shapeVA1;
	delete shapeVB1;
	delete shapeVBL1;

	delete shapeIB2;
	delete shapeVA2;
	delete shapeVB2;
	delete shapeVBL2;

	shape1Indices.clear();
	shape2Indices.clear();
	shape1Vertices.clear();
	shape2Vertices.clear();

	activeShape = shapes->GetRandomShape();
	int rectangleCount = activeShape.size();

	deformationOn = GameMultiAttention::ChooseIfDeformated();
	if (deformationOn)
	{
		GameMultiAttention::DeformateShape();
		std::shuffle(sideChances, sideChances + 2, gen);
	}

	for (int i = 0; i < activeShape.size(); i++)
	{

		//Left table
		float rectXLT1 = 0;
		float rectYLT1 = 0;

		if (activeDefShape == activeShape)
		{
			//wxLogStatus("same");
		}
		else
		{
			//wxLogStatus("notsame");
		}
		if (deformationOn)
		{
			if (sideChances[0] == 1)		//when result is 1, deformated shape will be on left side, when 2, right side
			{
				rectXLT1 = table1StartPos.first + (activeDefShape[i].first * rectSize);
				rectYLT1 = table1StartPos.second + (activeDefShape[i].second * rectSize);
			}
			else
			{
				rectXLT1 = table1StartPos.first + (activeShape[i].first * rectSize);
				rectYLT1 = table1StartPos.second + (activeShape[i].second * rectSize);
			}
		}
		else
		{
			rectXLT1 = table1StartPos.first + (activeShape[i].first * rectSize);
			rectYLT1 = table1StartPos.second + (activeShape[i].second * rectSize);
		}

		float rectXRT1 = rectXLT1 + rectSize;
		float rectYRT1 = rectYLT1;
		float rectXRD1 = rectXRT1;
		float rectYRD1 = rectYRT1 + rectSize;
		float rectXLD1 = rectXLT1;
		float rectYLD1 = rectYRD1;
		shape1Vertices.push_back(rectXLT1);
		shape1Vertices.push_back(rectYLT1);
		shape1Vertices.push_back(rectXRT1);
		shape1Vertices.push_back(rectYRT1);
		shape1Vertices.push_back(rectXRD1);
		shape1Vertices.push_back(rectYRD1);
		shape1Vertices.push_back(rectXLD1);
		shape1Vertices.push_back(rectYLD1);
		shape1Indices.push_back(i * 4);
		shape1Indices.push_back(i * 4 + 1);
		shape1Indices.push_back(i * 4 + 2);
		shape1Indices.push_back(i * 4 + 2);
		shape1Indices.push_back(i * 4 + 3);
		shape1Indices.push_back(i * 4);

		//Right table
		float rectXLT2 = 0;
		float rectYLT2 = 0;

		if (deformationOn)
		{
			if (sideChances[0] == 2)		//when result is 1, deformated shape will be on left side, when 2, right side
			{
				rectXLT2 = table2StartPos.first + (activeDefShape[i].first * rectSize);
				rectYLT2 = table2StartPos.second + (activeDefShape[i].second * rectSize);
			}
			else
			{
				rectXLT2 = table2StartPos.first + (activeShape[i].first * rectSize);
				rectYLT2 = table2StartPos.second + (activeShape[i].second * rectSize);
			}
		}
		else
		{
			rectXLT2 = table2StartPos.first + (activeShape[i].first * rectSize);
			rectYLT2 = table2StartPos.second + (activeShape[i].second * rectSize);
		}
		float rectXRT2 = rectXLT2 + rectSize;
		float rectYRT2 = rectYLT2;
		float rectXRD2 = rectXRT2;
		float rectYRD2 = rectYRT2 + rectSize;
		float rectXLD2 = rectXLT2;
		float rectYLD2 = rectYRD2;
		shape2Vertices.push_back(rectXLT2);
		shape2Vertices.push_back(rectYLT2);
		shape2Vertices.push_back(rectXRT2);
		shape2Vertices.push_back(rectYRT2);
		shape2Vertices.push_back(rectXRD2);
		shape2Vertices.push_back(rectYRD2);
		shape2Vertices.push_back(rectXLD2);
		shape2Vertices.push_back(rectYLD2);
		shape2Indices.push_back(i * 4);
		shape2Indices.push_back(i * 4 + 1);
		shape2Indices.push_back(i * 4 + 2);
		shape2Indices.push_back(i * 4 + 2);
		shape2Indices.push_back(i * 4 + 3);
		shape2Indices.push_back(i * 4);
	}
	//Left table
	shapeIB1 = new IndexBuffer(shape1Indices.size(), shape1Indices.data());
	shapeVA1 = new VertexArray();
	shapeVB1 = new VertexBuffer(shape1Vertices.size() * sizeof(std::vector<float>), shape1Vertices.data(), "static");
	shapeVBL1 = new VertexBufferLayout();
	shapeVBL1->Push<float>(2);
	shapeVA1->AddBuffer(shapeVB1, shapeVBL1);

	//Right table
	shapeIB2 = new IndexBuffer(shape2Indices.size(), shape1Indices.data());
	shapeVA2 = new VertexArray();
	shapeVB2 = new VertexBuffer(shape2Vertices.size() * sizeof(std::vector<float>), shape2Vertices.data(), "static");
	shapeVBL2 = new VertexBufferLayout();
	shapeVBL2->Push<float>(2);
	shapeVA2->AddBuffer(shapeVB2, shapeVBL2);
	
}

void GameMultiAttention::OptionBtnPressed(int btn)
{

	if (btn == 1)
	{
		timeMath = std::chrono::steady_clock::now();
		//GameMultiAttention::CreateNewMath();
		GameMultiAttention::CreateMathProblem(2, 100, 3, 3, mathOperators, 2, 2);


	}

	if (btn == 2)
	{
		timeMath = std::chrono::steady_clock::now();
		//GameMultiAttention::CreateNewMath();
	}

	if (btn == 3)
	{
		timestamp = std::chrono::steady_clock::now();
		textTime = std::chrono::steady_clock::now();
		if (deformationOn)
		{
			wrongAnswerForText = true;
		}
		else
		{
			correctAnswerForText = true;
		}
		GameMultiAttention::GetRandomShape();
	}
}

bool GameMultiAttention::ChooseIfDeformated()
{
	std::shuffle(deformationChances, deformationChances + 2, gen);
	if (deformationChances[0] == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

void GameMultiAttention::LoadAllGraphics()
{

	BaseGame::LoadAllGraphics();
	table1->LoadAllGraphics();
	table2->LoadAllGraphics();
}


void GameMultiAttention::DrawShapes()
{
	if (gameStarted)
	{
		GLCall(flexibleShaderProgram->Bind());
		GLCall(flexibleShaderProgram->SetUniform4f("u_Color", appColor[0], appColor[1], appColor[2], appColor[3]));

		//Left table
		GLCall(shapeVA1->Bind());
		GLCall(shapeIB1->Bind());
		GLCall(glDrawElements(GL_TRIANGLES, shape1Indices.size(), GL_UNSIGNED_SHORT, nullptr));

		//Right table
		GLCall(shapeVA2->Bind());
		GLCall(shapeIB2->Bind());
		GLCall(glDrawElements(GL_TRIANGLES, shape2Indices.size(), GL_UNSIGNED_SHORT, nullptr));
	}
}

void GameMultiAttention::Draw()
{
	//glClearColor(greyColor[0], greyColor[1], greyColor[2], greyColor[3]);
	glClearColor(greyColor2[0], greyColor2[1], greyColor2[2], greyColor2[3]);


	glClear(GL_COLOR_BUFFER_BIT);
	GameMultiAttention::DrawShapes();
	BaseGame::DrawCountDown();
	BaseGame::DrawAmountOfRounds();
	if (gameStarted)
	{
		table1->Draw();
		table2->Draw();
	}

	GameMultiAttention::DrawText();
	BaseGame::DrawPause();
}

void GameMultiAttention::UpdateTime()
{
	timeNow = std::chrono::steady_clock::now(); 

	std::chrono::milliseconds elapsedTimeStamp;
	elapsedTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>((timeNow - timestamp)); //table time
	milisecsOfRoundGoing = static_cast<int>(elapsedTimeStamp.count());

	std::chrono::milliseconds elapsedTimeMath;
	elapsedTimeMath = std::chrono::duration_cast<std::chrono::milliseconds>((timeNow - timestamp)); //math time
	milisecsOfMathGoing = static_cast<int>(elapsedTimeStamp.count());

	std::chrono::milliseconds elapsedTextTime;
	elapsedTextTime = std::chrono::duration_cast<std::chrono::milliseconds>((timeNow - textTime));
	milisecsOfText = static_cast<int>(elapsedTextTime.count());

	if (!gameStarted)
	{
		if (milisecsOfRoundGoing >= 3000)
		{
			gameStarted = true;
			timestamp = std::chrono::steady_clock::now();
			optionBtn1Visible = true;
			optionBtn2Visible = true;
			optionBtn3Visible = true;
		}
	}
	if (gameStarted)
	{

		if (milisecsOfText > textTimeMilisecsSolid)
		{
			missedInputForText = false;
			correctAnswerForText = false;
			wrongAnswerForText = false;
		}

		if (milisecsOfRoundGoing > roundTimeMilisecs)
		{
			totalTableExamples++;
			if (deformationOn)
			{
				correctTableAnswer++;
				correctAnswerForText = true;
			}
			else
			{
				missedInputForText = true;
				wrongTableAnswer++;
			}
			GameMultiAttention::GetRandomShape();
			textTime = std::chrono::steady_clock::now();
			timestamp = std::chrono::steady_clock::now();
		}

		if (milisecsOfMathGoing > mathExampleMilisecs)
		{
			totalMathExamplesCount++;
			missedMathExamplesCount++;
			miniRoundsDone++;
			timeMath = std::chrono::steady_clock::now();
			textTime = std::chrono::steady_clock::now();
			missedInputForMath = true;
		}
	}
}

void GameMultiAttention::Update()
{
	if (!gamePaused)
	{
		GameMultiAttention::UpdateTime();
	}
}

GameMultiAttention::~GameMultiAttention()
{
}
