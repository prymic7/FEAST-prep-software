#include "GameLearningAndApplying.h"



//typ: handle the frequency of special rules
//		handle milisecond of game atd.. better

//todo: timer
//		finish lvls in contructor and wx
GameLearningAndApplying::GameLearningAndApplying(int level, std::string typeOfGame, int startW, int startH, int creatorW, int creatorH, std::string typeOfTimer)
	: BaseGame(level, typeOfGame, startW, startH, creatorW, creatorH, typeOfTimer)
{
	textTime = std::chrono::steady_clock::now();
	justRun = true;
	this->creatorW = creatorW;
	this->creatorH = creatorH;
	this->level = level;
	this->typeOfGame = typeOfGame;
	timer = true;
	textTimeMilisecsSolid = 1000;

	colorDictionary["red"] = std::vector<float>{ 1.0f, 0.0f, 0.0f, 1.0f }; 
	colorDictionary["blue"] = std::vector<float>{ 0.0f, 0.0f, 1.0f, 1.0f }; 
	colorDictionary["yellow"] = std::vector<float>{ 1.0f, 1.0f, 0.0f, 1.0f }; 
	colorDictionary["green"] = std::vector<float>{ 0.0f, 1.0f, 0.0f, 1.0f };
	colorDictionary["orange"] = std::vector<float>{ 1.0f, 0.5f, 0.0f, 1.0f };
	colorDictionary["purple"] = std::vector<float>{ 0.5f, 0.0f, 0.5f, 1.0f };
	colorDictionary["pink"] = std::vector<float>{ 1.0f, 0.75f, 0.8f, 1.0f };
	//wxString str = wxString::Format("creatorW: %d, startW: %d", creatorW, startW);
	//wxLogStatus(str);
	if (typeOfGame == "practice")
	{
		if (level == 1)
		{
			specialRules = false;
			secondShape = false;
		}
		else if (level == 2)
		{
			specialRules = false;
			secondShape = true;
		}
		else if (level == 3)
		{
			miniRoundMilisecs = 30000;
			taskIntroTimeMilisecs = 2000;
			roundsTillChangeRule = 15;
			numOfExamples = 2;
			specialRules = true;
			secondShape = true;
		}
	}
	else if (typeOfGame == "test")
	{
		miniRoundMilisecs = 3000;
		taskIntroTimeMilisecs = 5000;
		roundsTillChangeRule = 15;
		numOfExamples = 2;
		specialRules = true;
		secondShape = true;
	}

	glm::vec2 position = glm::vec2(20.0f, 20.0f);

	circleVertices = BaseGame::GenerateCircle(position, circleRadius, numSegments);
	triangleVertices = BaseGame::GenerateTriangle(position, baseLength, lineLength);
	squareVertices = BaseGame::GenerateSquare(position, squareSize);
	rectangleVertices = BaseGame::GenerateRectangle(position, rectWidth, rectHeight);
	starVertices = BaseGame::GenerateStar(position, outerRadius, innerRadius, 5);
	hexagonVertices = BaseGame::GenerateHexagon(position, hexagonRadius);
	octagonVertices = BaseGame::GenerateOctagon(position, octagonRadius);

	circleVertices2 = BaseGame::GenerateCircle(position, circleRadius, numSegments);
	triangleVertices2 = BaseGame::GenerateTriangle(position, baseLength, lineLength);
	squareVertices2 = BaseGame::GenerateSquare(position, squareSize);
	rectangleVertices2 = BaseGame::GenerateRectangle(position, rectWidth, rectHeight);
	starVertices2 = BaseGame::GenerateStar(position, outerRadius, innerRadius, 5);
	hexagonVertices2 = BaseGame::GenerateHexagon(position, hexagonRadius);
	octagonVertices2 = BaseGame::GenerateOctagon(position, octagonRadius);

	circleVertices3 = BaseGame::GenerateCircle(position, circleRadius, numSegments);
	triangleVertices3 = BaseGame::GenerateTriangle(position, baseLength, lineLength);
	squareVertices3 = BaseGame::GenerateSquare(position, squareSize);
	rectangleVertices3 = BaseGame::GenerateRectangle(position, rectWidth, rectHeight);
	starVertices3 = BaseGame::GenerateStar(position, outerRadius, innerRadius, 5);
	hexagonVertices3 = BaseGame::GenerateHexagon(position, hexagonRadius);
	octagonVertices3 = BaseGame::GenerateOctagon(position, octagonRadius);

}



void GameLearningAndApplying::DrawText()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	//BASIC RULES
	if (taskIntroActive)
	{
		//BaseGame::CreateText("BASIC RULE:", 0.5f, creatorW / 2 - BaseGame::CalculateTextSize("BASIC RULE:", 0.5f).x / 2.0f, creatorH / 2 - BaseGame::CalculateTextSize("BASIC RULE:", 0.5f).y / 2.0f + 30.0f, blackColor[0], blackColor[1], blackColor[2], 1);

		if (activeNumberOrShape == "shapes")
		{
			if (activeRule == "byShape")
			{
				BaseGame::CreateText("Sort out all shapes by their shape.", 0.4f, creatorW / 2 - BaseGame::CalculateTextSize("Sort out all shapes by their shape.", 0.4f).x / 2.0f, creatorH / 2 - BaseGame::CalculateTextSize("Sort out all shapes by their shape.", 0.5f).y / 2.0f, whiteColor[0], whiteColor[1], whiteColor[2], 1);
			}
			else if (activeRule == "byColor")
			{
				BaseGame::CreateText("Sort out all shapes by their color.", 0.4f, creatorW / 2 - BaseGame::CalculateTextSize("Sort out all shapes by their color.", 0.4f).x / 2.0f, creatorH / 2 - BaseGame::CalculateTextSize("Sort out all shapes by their color.", 0.5f).y / 2.0f, whiteColor[0], whiteColor[1], whiteColor[2], 1);
			}
		}
		else if (activeNumberOrShape == "numbers")
		{
			if (activeRule == "byNumber")
			{
				BaseGame::CreateText("Sort out all numbers numerically.", 0.4f, creatorW / 2 - BaseGame::CalculateTextSize("Sort out all numbers numerically.", 0.4f).x / 2.0f, creatorH / 2 - BaseGame::CalculateTextSize("Sort out all numbers numerically.", 0.5f).y / 2.0f, whiteColor[0], whiteColor[1], whiteColor[2], 1);
			}
			else if (activeRule == "byColor")
			{
				BaseGame::CreateText("Sort out all numbers by their color.", 0.4f, creatorW / 2 - BaseGame::CalculateTextSize("Sort out all numbers by their color.", 0.4f).x / 2.0f, creatorH / 2 - BaseGame::CalculateTextSize("Sort out all numbers by their color.", 0.5f).y / 2.0f, whiteColor[0], whiteColor[1], whiteColor[2], 1);
			}
		}
	}
	if (!taskIntroActive && gameStarted)
	{
		//ThisAs specialRule
		if (specialRuleOn)
		{
			if (thisAsOn)
			{
				BaseGame::CreateText(thisAsString, 0.4f, 100.0f, specialRuleStringY, blackColor[0], blackColor[1], blackColor[2], 1);
			}
			if (allObjectAsOn)
			{
				if (allObjectStringVec.size() > 0)
				{
					for (int i = 0; i < allObjectStringVec.size(); i++)
					{
						BaseGame::CreateText(allObjectStringVec[i], 0.4f, 100.0f, specialRuleStringY + (i * 40), blackColor[0], blackColor[1], blackColor[2], 1);
					}
				}
			}
		}

		BaseGame::CreateTextToRect("SAME", 0.5f, fifthBtnX, firstBtnY, btnWidth, btnHeight, 1.0f, 1.0f, 1.0f, 1);

		//correct and incorrect text
		if (correctAnswerForText)
		{
			BaseGame::CreateText("Correct button pressed!", 0.5f, creatorW / 2 - BaseGame::CalculateTextSize("Correct button pressed!", 0.5f).x / 2.0f, 200.0f, greenColor2[0], greenColor2[1], greenColor2[2], 1);
		}
		else if (wrongAnswerForText)
		{
			BaseGame::CreateText("Wrong button pressed.", 0.5f, creatorW / 2 - BaseGame::CalculateTextSize("Wrong button pressed.", 0.5f).x / 2.0f, 200.0f, redColor[0], redColor[1], redColor[2], 1);
		}
		else if (missedInputForText)
		{
			BaseGame::CreateText("Missed input.", 0.5f, creatorW / 2 - BaseGame::CalculateTextSize("Missed input.", 0.5f).x / 2.0f, 200.0f, redColor[0], redColor[1], redColor[2], 1);
		}
	}

	if (!taskIntroActive)
	{
		if (activeNumberOrShape == "numbers")
		{
			//EXAMPLE 
			if (activeRule == "byColor")
			{
				BaseGame::CreateTextToRect(std::to_string(mainExampleNumber), 0.5f, firstExampleX, firstExampleY, btnWidth, btnHeight, colorDictionary[mainExampleColor][0], colorDictionary[mainExampleColor][1], colorDictionary[mainExampleColor][2], 1);
				//SECOND EXAMPLE
				if (secondExampleOn && secondSameExampleOn)
				{
					BaseGame::CreateTextToRect(std::to_string(mainExampleNumber), 0.5f, secondExampleX, firstExampleY, btnWidth, btnHeight, colorDictionary[mainExampleColor][0], colorDictionary[mainExampleColor][1], colorDictionary[mainExampleColor][2], 1);
				}
			}
			else if (activeRule == "byNumber")
			{
				BaseGame::CreateTextToRect(std::to_string(mainExampleNumber), 0.5f, firstExampleX, firstExampleY, btnWidth, btnHeight, colorDictionary[mainExampleColor][0], colorDictionary[mainExampleColor][1], colorDictionary[mainExampleColor][2], 1);
				//SECOND EXAMPLE
				if (secondExampleOn && secondSameExampleOn)
				{
					BaseGame::CreateTextToRect(std::to_string(mainExampleNumber), 0.5f, secondExampleX, firstExampleY, btnWidth, btnHeight, colorDictionary[mainExampleColor][0], colorDictionary[mainExampleColor][1], colorDictionary[mainExampleColor][2], 1);
				}
			}
			//SECOND EXAMPLE
			if (secondExampleOn && !secondSameExampleOn)
			{
				BaseGame::CreateTextToRect(std::to_string(randomSecondNumber), 0.5f, secondExampleX, firstExampleY, btnWidth, btnHeight, colorDictionary[randomSecondNumberColor][0], colorDictionary[randomSecondNumberColor][1], colorDictionary[randomSecondNumberColor][2], 1);
			}
			//BTNS
			bool found = false;
			for (int i = 0; i < sizeof(btns) / sizeof(btns[0]) - 1; i++)
			{
				bool waka = false;
				if (i == btnIncludingCorrectAnswer)
				{
					if (specialRuleOn && possibleSpecialRules[0] == "allObjectAs")
					{
						for (int j = 0; j < allObjectStringVec.size(); j++)
						{
							if (byWhatVec[j] == "byColor")
							{
								if (allThatVec[j] == mainExampleColor)
								{
									BaseGame::CreateTextToRect(numbers1[i], 0.5f, allBtnXs[i], firstBtnY, btnWidth, btnHeight, colorDictionary[asThatVec[j]][0], colorDictionary[asThatVec[j]][1], colorDictionary[asThatVec[j]][2], 1);
									found = true;
									break;
								}
							}
						}
						if (!found)
						{
							if (activeRule == "byNumber")
							{
								BaseGame::CreateTextToRect(numbers1[i], 0.5f, allBtnXs[i], firstBtnY, btnWidth, btnHeight, colorDictionary[colorKeys[i]][0], colorDictionary[colorKeys[i]][1], colorDictionary[colorKeys[i]][2], 1);
							}
							else if (activeRule == "byColor")
							{
								BaseGame::CreateTextToRect(numbers1[i], 0.5f, allBtnXs[i], firstBtnY, btnWidth, btnHeight, colorDictionary[mainExampleColor][0], colorDictionary[mainExampleColor][1], colorDictionary[mainExampleColor][2], 1);
							}
						}
					}
					else
					{
						if (activeRule == "byColor")
						{
							if (specialRuleOn && possibleSpecialRules[0] == "thisAs")
							{
								BaseGame::CreateTextToRect(numbers1[i], 0.5f, allBtnXs[i], firstBtnY, btnWidth, btnHeight, colorDictionary[colorKeys[btnIncludingCorrectAnswer]][0], colorDictionary[colorKeys[btnIncludingCorrectAnswer]][1], colorDictionary[colorKeys[btnIncludingCorrectAnswer]][2], 1);
							}
							else if(!specialRuleOn)
							{
								BaseGame::CreateTextToRect(numbers1[i], 0.5f, allBtnXs[i], firstBtnY, btnWidth, btnHeight, colorDictionary[mainExampleColor][0], colorDictionary[mainExampleColor][1], colorDictionary[mainExampleColor][2], 1);
							}
						}
						else if (activeRule == "byNumber")
						{
							BaseGame::CreateTextToRect(numbers1[i], 0.5f, allBtnXs[i], firstBtnY, btnWidth, btnHeight, colorDictionary[colorKeys[i]][0], colorDictionary[colorKeys[i]][1], colorDictionary[colorKeys[i]][2], 1);
						}
					}
				}
				else
				{
					if (specialRuleOn && possibleSpecialRules[0] == "allObjectAs")
					{
						for (int j = 0; j < allThatVec.size(); j++)
						{
							if (byWhatVec[j] == "byColor")
							{
								if (allThatVec[j] == mainExampleColor)
								{
									if (colorKeys[i] == asThatVec[j])
									{
										waka = true;
										BaseGame::CreateTextToRect(numbers1[i], 0.5f, allBtnXs[i], firstBtnY, btnWidth, btnHeight, colorDictionary[colorKeys[colorKeys.size()-1]][0], colorDictionary[colorKeys[colorKeys.size() - 1]][1], colorDictionary[colorKeys[colorKeys.size() - 1]][2], 1);
										break;
									}
								}
							}
						}
						if (!waka)
						{
							BaseGame::CreateTextToRect(numbers1[i], 0.5f, allBtnXs[i], firstBtnY, btnWidth, btnHeight, colorDictionary[colorKeys[i]][0], colorDictionary[colorKeys[i]][1], colorDictionary[colorKeys[i]][2], 1);
						}
					}
					else if (!specialRuleOn && activeRule == "byNumber") //																						issue?????????????????????????????????????????????????,
					{
						if (luckyNumColorCrazy == i) //makes it harder for users, one number will be same color as example, even its not sorting my color
						{
							BaseGame::CreateTextToRect(numbers1[i], 0.5f, allBtnXs[i], firstBtnY, btnWidth, btnHeight, colorDictionary[mainExampleColor][0], colorDictionary[mainExampleColor][1], colorDictionary[mainExampleColor][2], 1);
						}
						else
						{
							BaseGame::CreateTextToRect(numbers1[i], 0.5f, allBtnXs[i], firstBtnY, btnWidth, btnHeight, colorDictionary[colorKeys[i]][0], colorDictionary[colorKeys[i]][1], colorDictionary[colorKeys[i]][2], 1);
						}
					}
					else
					{
						BaseGame::CreateTextToRect(numbers1[i], 0.5f, allBtnXs[i], firstBtnY, btnWidth, btnHeight, colorDictionary[colorKeys[i]][0], colorDictionary[colorKeys[i]][1], colorDictionary[colorKeys[i]][2], 1);
					}
				}
			}
		}
	}
}

void GameLearningAndApplying::ChooseBtnGraphics()
{
	guessCircleDrawOn = false;
	guessTriangleDrawOn = false;
	guessSquareDrawOn = false;
	guessRectangleDrawOn = false;
	guessStarDrawOn = false;
	guessHexagonDrawOn = false;
	guessOctagonDrawOn = false;

	exampleCircleDrawOn = false;
	exampleTriangleDrawOn = false;
	exampleSquareDrawOn = false;
	exampleRectangleDrawOn = false;
	exampleStarDrawOn = false;
	exampleHexagonDrawOn = false;
	exampleOctagonDrawOn = false;

	secondCircleDrawOn = false;
	secondTriangleDrawOn = false;
	secondSquareDrawOn = false;
	secondRectangleDrawOn = false;
	secondStarDrawOn = false;
	secondHexagonDrawOn = false;
	secondOctagonDrawOn = false;

	secondExampleOn = false;
	secondSameExampleOn = false;

	std::random_device rd;
	std::mt19937 gen(rd());

	numOfBtns = sizeof(btns) / sizeof(btns[0]);
	std::uniform_int_distribution<> btnDistrib(0, numOfBtns - 2);
	btnIncludingCorrectAnswer = btns[btnDistrib(gen)];
	std::uniform_int_distribution<> numDistrib(0, 1000);

	GameLearningAndApplying::ChooseSpecialRules();

	if (activeNumberOrShape == "numbers")
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> btnIncludingAnswerDistrib(0, numOfBtns);
		std::uniform_int_distribution<> btnDistrib(0, numOfBtns-2);

		luckyNumColorCrazy = btnDistrib(gen);

		int first, second;
		if (activeRule == "byNumber")
		{
			for (int i = 0; i < numbers1.size(); i++)
			{
				size_t pos = numbers1[i].find("-");
				std::string firstNumString = numbers1[i].substr(0, pos);
				std::string secondNumString = numbers1[i].substr(pos + 1);

				int first, second;
				std::istringstream(firstNumString) >> first;
				std::istringstream(secondNumString) >> second;
				if (mainExampleNumber >= first && mainExampleNumber <= second)
				{
					if (!thisAsOn) //change right button only if we are not playing thisAs round
					{
						btnIncludingCorrectAnswer = i;
					}
				}
			}
		}
		if (possibleSpecialRules[0] == "allObjectAs" && specialRuleOn)
		{

			for (int i = 0; i < allObjectStringVec.size(); i++)
			{
				if (byWhatVec[i] == "byThat")
				{
					size_t pos = allThatVec[i].find("-");
					std::string firstNumString = allThatVec[i].substr(0, pos);
					std::string secondNumString = allThatVec[i].substr(pos + 1);
					int firstAll, secondAll;
					std::istringstream(firstNumString) >> firstAll;
					std::istringstream(secondNumString) >> secondAll;
					if (mainExampleNumber >= firstAll && mainExampleNumber <= secondAll)
					{
						shitCoding = true;
						size_t pos = asThatVec[i].find("-");
						std::string firstNumString = asThatVec[i].substr(0, pos);
						std::string secondNumString = asThatVec[i].substr(pos + 1);

						int firstAs, secondAs;
						std::istringstream(firstNumString) >> firstAs;
						std::istringstream(secondNumString) >> secondAs;

						if (firstAs == 0)
						{
							btnIncludingCorrectAnswer = 0;
						}
						else if (firstAs == 250)
						{
							btnIncludingCorrectAnswer = 1;
						}
						else if (firstAs == 500)
						{
							btnIncludingCorrectAnswer = 2;
						}
						else if (firstAs == 750)
						{
							btnIncludingCorrectAnswer = 3;
						}
					}
				}
			}
		}
	}

	bool finished = false;
	std::shuffle(shapes.begin(), shapes.end(), gen);


	if (activeNumberOrShape == "shapes")
	{
		GameLearningAndApplying::ChooseWhatToDraw(mainExampleShape, 0, "example");
		GameLearningAndApplying::AssignColorsToShapes(mainExampleShape, mainExampleShape, "example");
		std::shuffle(shapes.begin(), shapes.end(), gen);
		bool saka = false;
		std::string what;
		std::uniform_int_distribution<> btnDistrib(0, 3);
		int luckyNum = btnDistrib(gen);
		for (int i = 0; i < numOfBtns - 1; i++)
		{
			saka = false;
			if (i == btnIncludingCorrectAnswer)
			{
				bool shapeInVecFound = false;
				if (specialRuleOn && possibleSpecialRules[0] == "allObjectAs" && allObjectStringVec.size() > 0)
				{
					for (int j = 0; j < byWhatVec.size(); j++)
					{
						if (byWhatVec[j] == "byThat")
						{
							if (allThatVec[j] == mainExampleShape)
							{
								shapeInVecFound = true;
								GameLearningAndApplying::ChooseWhatToDraw(asThatVec[j], i, "guess");
								GameLearningAndApplying::AssignColorsToShapes(asThatVec[j], colorKeys[i], "guess");

								break;
							}
						}
						else if (byWhatVec[j] == "byColor")
						{
							if (allThatVec[j] == mainExampleColor)
							{
								shapeInVecFound = true;
								GameLearningAndApplying::ChooseWhatToDraw(shapes[i], i, "guess");
								GameLearningAndApplying::AssignColorsToShapes(shapes[i], asThatVec[j], "guess");
								break;
							}
						}
					}
					if (!shapeInVecFound)
					{
						if (activeRule == "byShape")
						{
							GameLearningAndApplying::ChooseWhatToDraw(mainExampleShape, i, "guess");
							GameLearningAndApplying::AssignColorsToShapes(mainExampleShape, colorKeys[i], "guess");
						}
						else if (activeRule == "byColor")
						{
							GameLearningAndApplying::ChooseWhatToDraw(shapes[i], i, "guess");
							GameLearningAndApplying::AssignColorsToShapes(shapes[i], mainExampleColor, "guess");
						}
					}
				}
				else if (specialRuleOn && possibleSpecialRules[0] == "thisAs")
				{

					if (byWhat == "byThat")
					{
						GameLearningAndApplying::ChooseWhatToDraw(thisAsShape, i, "guess");
						GameLearningAndApplying::AssignColorsToShapes(thisAsShape, colorKeys[i], "guess");
					}
					else if (byWhat == "byColor")
					{
						GameLearningAndApplying::ChooseWhatToDraw(shapes[i], i, "guess");
						GameLearningAndApplying::AssignColorsToShapes(shapes[i], thisAsColor, "guess");
					}
				}

				else
				{
					if (activeRule == "byShape")
					{
						GameLearningAndApplying::ChooseWhatToDraw(mainExampleShape, i, "guess");
						GameLearningAndApplying::AssignColorsToShapes(mainExampleShape, colorKeys[i], "guess");
					}
					else if (activeRule == "byColor")
					{
						GameLearningAndApplying::ChooseWhatToDraw(shapes[i], i, "guess");
						GameLearningAndApplying::AssignColorsToShapes(shapes[i], mainExampleColor, "guess");
					}
				}
			}
			else
			{
				if (specialRuleOn && possibleSpecialRules[0] == "thisAs")
				{
					if (byWhat == "byColor")
					{
						if (colorKeys[i] == thisAsColor)
						{
							saka = true;
							GameLearningAndApplying::ChooseWhatToDraw(shapes[i], i, "guess");
							GameLearningAndApplying::AssignColorsToShapes(shapes[i], colorKeys[colorKeys.size() - 1], "guess");
						}
					}
					else if (byWhat == "byThat")
					{
						if (shapes[i] == thisAsShape)
						{
							saka = true;
							GameLearningAndApplying::ChooseWhatToDraw(shapes[shapes.size() - 1], i, "guess");
							GameLearningAndApplying::AssignColorsToShapes(shapes[shapes.size() - 1], colorKeys[i], "guess");
						}
					}
				}
				if (specialRuleOn && possibleSpecialRules[0] == "allObjectAs")
				{
					bool found = false;
					if (!finished)
					{
						for (int k = 0; k < allObjectStringVec.size(); k++)
						{
							if (byWhatVec[k] == "byColor")
							{
								if (mainExampleColor == allThatVec[k])
								{
									if (colorKeys[i] == asThatVec[k])
									{
										found = true;
										finished = true;
										what = "byColor";
									}
								}
							}
							if (byWhatVec[k] == "byThat")
							{
								if (mainExampleShape == allThatVec[k])
								{
									if (shapes[i] == asThatVec[k])
									{
										found = true;
										finished = true;
										what = "byThat";
									}
								}
							}
						}
						if (found)
						{
							if (what == "byColor")
							{
								GameLearningAndApplying::ChooseWhatToDraw(shapes[i], i, "guess");
								GameLearningAndApplying::AssignColorsToShapes(shapes[i], colorKeys[colorKeys.size() - 1], "guess");
							}
							else if (what == "byThat")
							{
								GameLearningAndApplying::ChooseWhatToDraw(shapes[shapes.size() - 1], i, "guess");
								GameLearningAndApplying::AssignColorsToShapes(shapes[shapes.size() - 1], colorKeys[i], "guess");
							}

						}
						if (!found)
						{
							GameLearningAndApplying::ChooseWhatToDraw(shapes[i], i, "guess");
							GameLearningAndApplying::AssignColorsToShapes(shapes[i], colorKeys[i], "guess");
						}
					}
					else
					{
						GameLearningAndApplying::ChooseWhatToDraw(shapes[i], i, "guess");
						GameLearningAndApplying::AssignColorsToShapes(shapes[i], colorKeys[i], "guess");
					}
				}
				else
				{
					if (!saka) //idk why just because... in thisAs important
					{
						GameLearningAndApplying::ChooseWhatToDraw(shapes[i], i, "guess");
						GameLearningAndApplying::AssignColorsToShapes(shapes[i], colorKeys[i], "guess");
					}
					if (activeRule == "byShape" && !specialRuleOn) //																			issue??????????????????????????????????????????????????
					{
						if (i == luckyNum)
						{
							GameLearningAndApplying::ChooseWhatToDraw(shapes[i], i, "guess");
							GameLearningAndApplying::AssignColorsToShapes(shapes[i], mainExampleColor, "guess");

						}
						else
						{
							GameLearningAndApplying::ChooseWhatToDraw(shapes[i], i, "guess");
							GameLearningAndApplying::AssignColorsToShapes(shapes[i], colorKeys[i], "guess");
						}
					}
				}

			}
		}
	}

	std::shuffle(secondExample, secondExample + 2, gen);
	std::shuffle(secondSameExample, secondSameExample + 3, gen);
	//Checking if there will be second example, and if they will be the same
	if (secondShape) //if we turn it on in contructor
	{
		std::shuffle(secondExample, secondExample + 2, gen);
		std::shuffle(secondSameExample, secondSameExample + 4, gen);

		if (secondExample[0] == 1)
		{
			secondExampleOn = true;
			if (secondSameExample[0] == 1)
			{
				secondSameExampleOn = true;
				btnIncludingCorrectAnswer = 4; //set correct btn on "SAME" btn
			}
		}
		if (activeNumberOrShape == "shapes")
		{
			GameLearningAndApplying::SetSecondExample();
		}
		else if (activeNumberOrShape == "numbers")
		{
			if (secondExampleOn && !secondSameExampleOn)
			{
				randomSecondNumber = numDistrib(gen);
				randomSecondNumberColor = colorKeys[colorKeys.size() - 1];
			}
		}
	}
}

void GameLearningAndApplying::ChooseSpecialRules()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(specialRule, specialRule + 2, gen);
	std::shuffle(possibleSpecialRules, possibleSpecialRules + 2, gen);
	std::uniform_int_distribution<> btnDistrib(0, 3);
	std::uniform_int_distribution<> shapeDistrib(0, shapes.size() - 1);
	std::uniform_int_distribution<> colorDistrib(0, colorKeys.size() - 1);
	std::uniform_int_distribution<> numbersDistrib(0, numbers1.size() - 1);

	shitCoding = false;
	do
	{
		specialBtnNum = btnDistrib(gen);
	} while (specialBtnNum == btnIncludingCorrectAnswer);

	thisAsOn = false;
	allObjectAsOn = false;
	if (specialRule[0] == 1)
	{
		specialRuleOn = true;
	}
	else if (specialRule[0] == 0)
	{
		specialRuleOn = false;
	}
	//specialRuleOn = false;
	//byWhat = "byColor";
	if (specialRuleOn)
	{
		if (possibleSpecialRules[0] != lastTime)
		{
			allObjectStringVec.clear();
			byWhatVec.clear();
			asThatVec.clear();
			allThatVec.clear();
			lastTime = possibleSpecialRules[0];
		}
		//possibleSpecialRules[0] = "allObjectAs";

		std::shuffle(byColorByThat, byColorByThat + 2, gen);
		byWhat = byColorByThat[0];
		//byWhat = "byThat";
		if (activeNumberOrShape == "shapes")
		{
			if (possibleSpecialRules[0] == "thisAs")
			{
				lastTime = "thisAs";
				thisAsOn = true;
				btnIncludingCorrectAnswer = specialBtnNum;
				if (byWhat == "byThat")
				{
					asShape = shapeDistrib(gen);
					thisAsShape = shapes[asShape];
					thisAsString = "Sort this as " + thisAsShape;
				}
				else if (byWhat == "byColor")
				{
					asColor = shapeDistrib(gen);
					thisAsColor = colorKeys[asColor];
					thisAsString = "Sort this as " + thisAsColor;
				}
			}
			else if (possibleSpecialRules[0] == "allObjectAs")
			{
				lastTime = "allObjectAs";

				allObjectAsOn = true;
				if (allObjectStringVec.size() == 3) //deleting first elements so vectors will be not bigger size then 3
				{
					allObjectStringVec.erase(allObjectStringVec.begin());
					byWhatVec.erase(byWhatVec.begin());
					asThatVec.erase(asThatVec.begin());
					allThatVec.erase(allThatVec.begin());
				}
				byWhatVec.push_back(byWhat);
				btnIncludingCorrectAnswer = specialBtnNum;

				if (byWhat == "byThat")
				{

					asShape = shapeDistrib(gen);
					asThatVec.push_back(shapes[asShape]);
					do
					{
						allShape = shapeDistrib(gen);
					} while (allShape == asShape || std::find(allThatVec.begin(), allThatVec.end(), shapes[allShape]) != allThatVec.end());
					allThatVec.push_back(shapes[allShape]);

					std::string fokume = shapes[asShape];
					allObjectString = "Sort all " + shapes[allShape] + " as " + shapes[asShape];
					allObjectStringVec.push_back(allObjectString);
				}

				else if (byWhat == "byColor")
				{
					asColor = colorDistrib(gen);
					asThatVec.push_back(colorKeys[asColor]);

					do
					{
						allColor = colorDistrib(gen);
					} while (allColor == asColor || std::find(allThatVec.begin(), allThatVec.end(), colorKeys[allColor]) != allThatVec.end());
					allThatVec.push_back(colorKeys[allColor]);

					allObjectString = "Sort all " + colorKeys[allColor] + " as " + colorKeys[asColor];
					allObjectStringVec.push_back(allObjectString);
				}
			}
		}
		else if (activeNumberOrShape == "numbers")
		{
			if (possibleSpecialRules[0] == "thisAs")
			{
				lastTime = "thisAs";
				thisAsOn = true;
				if (byWhat == "byThat")
				{
					std::string specialRulePick = numbers1[specialBtnNum];
					thisAsString = "Sort this as " + specialRulePick;
				}
				else if (byWhat == "byColor")
				{
					std::string specialRuleShape = colorKeys[specialBtnNum];
					thisAsString = "Sort this as " + specialRuleShape;
				}
				btnIncludingCorrectAnswer = specialBtnNum;
			}
			else if (possibleSpecialRules[0] == "allObjectAs")
			{
				lastTime = "allObjectAs";
				allObjectAsOn = true;
				if (allObjectStringVec.size() == 3) //deleting first elements so vectors will be not bigger size then 3
				{
					allObjectStringVec.erase(allObjectStringVec.begin());
					byWhatVec.erase(byWhatVec.begin());
					asThatVec.erase(asThatVec.begin());
					allThatVec.erase(allThatVec.begin());
				}
				byWhatVec.push_back(byWhat);
				btnIncludingCorrectAnswer = specialBtnNum;
				if (byWhat == "byColor")
				{
					asColor = colorDistrib(gen);
					asThatVec.push_back(colorKeys[asColor]);
					do
					{
						allColor = colorDistrib(gen);
					} while (allColor == asColor || std::find(allThatVec.begin(), allThatVec.end(), colorKeys[allColor]) != allThatVec.end());
					allThatVec.push_back(colorKeys[allColor]);

					allObjectString = "Sort all " + colorKeys[allColor] + " as " + colorKeys[asColor];
					allObjectStringVec.push_back(allObjectString);
				}
				else if (byWhat == "byThat")
				{
					asShape = numbersDistrib(gen);
					asShape2 = numbersDistrib(gen);

					asThatVec.push_back(numbers1[asShape]);
					do
					{
						allShape = numbersDistrib(gen);
					} while (allShape == asShape || std::find(allThatVec.begin(), allThatVec.end(), numbers1[allShape]) != allThatVec.end());
					allThatVec.push_back(numbers1[allShape]);

					std::string fokume = numbers1[asShape];
					allObjectString = "Sort all " + numbers1[allShape] + " as " + numbers1[asShape];
					allObjectStringVec.push_back(allObjectString);
				}

			}
		}
	}
}

void GameLearningAndApplying::ChooseExample()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	shapes = { "star", "square", "triangle", "octagon", "hexagon", "circle", "rectangle" };
	numbers1 = { "0-249", "250-499", "500-749", "750-999" };
	colorKeys = { "red", "blue", "yellow", "green", "orange", "purple", "pink" };

	std::shuffle(shapes.begin(), shapes.end(), gen);
	std::shuffle(colorKeys.begin(), colorKeys.end(), gen);

	numOfExamples = 1;
	std::uniform_int_distribution<> randomNumDistrib(0, 1000);
	std::uniform_int_distribution<> btnRightAnswerDistrib(0, 3);

	if (activeNumberOrShape == "shapes")
	{
		mainExampleShape = shapes[0];
		mainExampleColor = colorKeys[0];

		auto it = std::find(shapes.begin(), shapes.end(), mainExampleShape);
		if (it != shapes.end())
		{
			shapes.erase(it);
			numOfExamples--;
		}

		auto ti = std::find(colorKeys.begin(), colorKeys.end(), mainExampleColor);
		if (ti != colorKeys.end())
		{
			colorKeys.erase(ti);
		}
	}
	else if (activeNumberOrShape == "numbers")
	{
		mainExampleNumber = randomNumDistrib(gen);
		mainExampleColor = colorKeys[0];

		auto it = std::find(colorKeys.begin(), colorKeys.end(), mainExampleColor);
		if (it != colorKeys.end())
		{
			colorKeys.erase(it);
			numOfExamples--;
		}
	}
}

void GameLearningAndApplying::ChooseRule()
{

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> ruleDistrib(0, 1);

	if (activeNumberOrShape == "numbers")
	{
		activeRule = basicRules1[ruleDistrib(gen)];
	}
	else if (activeNumberOrShape == "shapes")
	{
		activeRule = basicRules2[ruleDistrib(gen)];
	}
	activeRule = "byShape";
}

void GameLearningAndApplying::ChooseNumbersOrShapes()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(numbersOrShapes, numbersOrShapes + 2, gen);
	activeNumberOrShape = numbersOrShapes[0];
	activeNumberOrShape = "numbers";
}

void GameLearningAndApplying::LoadAllGraphics()
{
	BaseGame::LoadAllGraphics();
	GameLearningAndApplying::LoadButtonGraphics();
	GameLearningAndApplying::LoadShapeGraphics();
}

void GameLearningAndApplying::UpdateTime()
{

	timeNow = std::chrono::steady_clock::now();
	std::chrono::milliseconds elapsedTimeStamp;
	elapsedTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>((timeNow - timestamp));
	milisecsOfRoundGoing = static_cast<int>(elapsedTimeStamp.count());

	std::chrono::milliseconds elapsedTextTime;
	elapsedTextTime = std::chrono::duration_cast<std::chrono::milliseconds>((timeNow - textTime));
	milisecsOfText = static_cast<int>(elapsedTextTime.count());

	if (!gameStarted)
	{
		if (milisecsOfRoundGoing >= 3000)
		{
			gameStarted = true;
			timestamp = std::chrono::steady_clock::now();
			taskIntroActive = true;
			GameLearningAndApplying::ChooseNumbersOrShapes();
			GameLearningAndApplying::ChooseRule();
			GameLearningAndApplying::ChooseExample();
			GameLearningAndApplying::ChooseBtnGraphics();
			gameJustStarted = true;
		}
	}

	elapsedTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>((timeNow - timestamp));
	milisecsOfRoundGoing = static_cast<int>(elapsedTimeStamp.count());

	if (gameStarted)
	{
		if (milisecsOfText > textTimeMilisecsSolid)
		{
			missedInputForText = false;
			correctAnswerForText = false;
			wrongAnswerForText = false;
		}

		if (milisecsOfRoundGoing > miniRoundMilisecs && !taskIntroActive)
		{
			if (!firstTime)
			{
				totalCount++;
				miniRoundsDone++;
				GameLearningAndApplying::ChooseExample();
				thisAsOn = false;
				allObjectAsOn = false;
				specialRuleOn = false;
				GameLearningAndApplying::ChooseBtnGraphics();
				timestamp = std::chrono::steady_clock::now();
				textTime = std::chrono::steady_clock::now();
				missedInputForText = true;
				gameJustStarted = false;
			}
			firstTime = false;
		}

		if (miniRoundsDone == roundsTillChangeRule && !taskIntroActive)
		{
			taskIntroActive = true;
			GameLearningAndApplying::ChooseNumbersOrShapes();
			GameLearningAndApplying::ChooseRule();
			GameLearningAndApplying::ChooseExample();
			thisAsOn = false;
			allObjectAsOn = false;
			specialRuleOn = false;
			allObjectStringVec.clear();
			byWhatVec.clear();
			asThatVec.clear();
			allThatVec.clear();
			GameLearningAndApplying::ChooseBtnGraphics();
			miniRoundsDone = 0;
			timestamp = std::chrono::steady_clock::now();

		}
		else if (milisecsOfRoundGoing > taskIntroTimeMilisecs && taskIntroActive)
		{
			taskIntroActive = false;
			timestamp = std::chrono::steady_clock::now();
			textTime = std::chrono::steady_clock::now();
		}
	}
}

void GameLearningAndApplying::LeftClickBtn(float xPos, float yPos)
{
	if (!taskIntroActive && gameStarted)
	{
		if (BaseGame::CheckBtnClicked(xPos, yPos, creatorW, creatorH, btnWidth, btnHeight, firstBtnX, firstBtnY)) //first btn
		{
			totalCount++;
			miniRoundsDone++;

			if (btnIncludingCorrectAnswer == 0)
			{
				correctCount++;
				correctAnswerForText = true;
			}
			else
			{
				wrongAnswerForText = true;
			}
			GameLearningAndApplying::ChooseExample();
			thisAsOn = false;
			allObjectAsOn = false;
			specialRuleOn = false;
			GameLearningAndApplying::ChooseBtnGraphics();
			textTime = std::chrono::steady_clock::now();
			timestamp = std::chrono::steady_clock::now();
		}
		if (BaseGame::CheckBtnClicked(xPos, yPos, creatorW, creatorH, btnWidth, btnHeight, secondBtnX, firstBtnY)) //second btn
		{
			totalCount++;
			miniRoundsDone++;

			if (btnIncludingCorrectAnswer == 1)
			{
				correctCount++;
				correctAnswerForText = true;
			}
			else
			{
				wrongAnswerForText = true;
			}
			GameLearningAndApplying::ChooseExample();
			thisAsOn = false;
			allObjectAsOn = false;
			specialRuleOn = false;
			GameLearningAndApplying::ChooseBtnGraphics();
			textTime = std::chrono::steady_clock::now();
			timestamp = std::chrono::steady_clock::now();
		}
		if (BaseGame::CheckBtnClicked(xPos, yPos, creatorW, creatorH, btnWidth, btnHeight, thirdBtnX, firstBtnY)) //third btn
		{
			totalCount++;
			miniRoundsDone++;

			if (btnIncludingCorrectAnswer == 2)
			{
				correctCount++;
				correctAnswerForText = true;
			}
			else
			{
				wrongAnswerForText = true;
			}
			GameLearningAndApplying::ChooseExample();
			thisAsOn = false;
			allObjectAsOn = false;
			specialRuleOn = false;
			GameLearningAndApplying::ChooseBtnGraphics();
			textTime = std::chrono::steady_clock::now();
			timestamp = std::chrono::steady_clock::now();
		}
		if (BaseGame::CheckBtnClicked(xPos, yPos, creatorW, creatorH, btnWidth, btnHeight, fourthBtnX, firstBtnY)) //fourth btn
		{
			totalCount++;
			miniRoundsDone++;

			if (btnIncludingCorrectAnswer == 3)
			{
				correctCount++;
				correctAnswerForText = true;
			}
			else
			{
				wrongAnswerForText = true;
			}
			GameLearningAndApplying::ChooseExample();
			thisAsOn = false;
			allObjectAsOn = false;
			specialRuleOn = false;
			GameLearningAndApplying::ChooseBtnGraphics();
			textTime = std::chrono::steady_clock::now();
			timestamp = std::chrono::steady_clock::now();
		}
		if (BaseGame::CheckBtnClicked(xPos, yPos, creatorW, creatorH, btnWidth, btnHeight, fifthBtnX, firstBtnY)) //fifth btn
		{
			totalCount++;
			miniRoundsDone++;

			if (btnIncludingCorrectAnswer == 4)
			{
				correctCount++;
				correctAnswerForText = true;
			}
			else
			{
				wrongAnswerForText = true;
			}
			GameLearningAndApplying::ChooseExample();
			thisAsOn = false;
			allObjectAsOn = false;
			specialRuleOn = false;
			GameLearningAndApplying::ChooseBtnGraphics();
			textTime = std::chrono::steady_clock::now();
			timestamp = std::chrono::steady_clock::now();
		}
	}
}

void GameLearningAndApplying::HoverButtons(int x, int y)
{
	btn1Hovering = BaseGame::CheckEnterRect(x, y, creatorW, creatorH, btnWidth, btnHeight, firstBtnX, firstBtnY);
	btn2Hovering = BaseGame::CheckEnterRect(x, y, creatorW, creatorH, btnWidth, btnHeight, secondBtnX, firstBtnY);
	btn3Hovering = BaseGame::CheckEnterRect(x, y, creatorW, creatorH, btnWidth, btnHeight, thirdBtnX, firstBtnY);
	btn4Hovering = BaseGame::CheckEnterRect(x, y, creatorW, creatorH, btnWidth, btnHeight, fourthBtnX, firstBtnY);
	btn5Hovering = BaseGame::CheckEnterRect(x, y, creatorW, creatorH, btnWidth, btnHeight, fifthBtnX, firstBtnY);
}

void GameLearningAndApplying::AssignColorsToShapes(std::string decider, std::string color, std::string which)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	if (which == "guess")
	{
		if (decider == "circle")
		{
			circleGuessColor = colorDictionary[color];
		}
		else if (decider == "triangle")
		{
			triangleGuessColor = colorDictionary[color];
		}
		else if (decider == "square")
		{
			squareGuessColor = colorDictionary[color];
		}
		else if (decider == "rectangle")
		{
			rectangleGuessColor = colorDictionary[color];
		}
		else if (decider == "star")
		{
			starGuessColor = colorDictionary[color];
		}
		else if (decider == "hexagon")
		{
			hexagonGuessColor = colorDictionary[color];
		}
		else if (decider == "octagon")
		{
			octagonGuessColor = colorDictionary[color];
		}
	}
	else if (which == "example")
	{
		if (decider == "circle")
		{
			circleExampleColor = colorDictionary[mainExampleColor];
		}
		else if (decider == "triangle")
		{
			triangleExampleColor = colorDictionary[mainExampleColor];
		}
		else if (decider == "rectangle")
		{
			rectangleExampleColor = colorDictionary[mainExampleColor];

		}
		else if (decider == "square")
		{
			squareExampleColor = colorDictionary[mainExampleColor];
		}

		else if (decider == "star")
		{
			starExampleColor = colorDictionary[mainExampleColor];

		}
		else if (decider == "hexagon")
		{
			hexagonExampleColor = colorDictionary[mainExampleColor];

		}
		else if (decider == "octagon")
		{
			octagonExampleColor = colorDictionary[mainExampleColor];
		}
	}
}

void GameLearningAndApplying::SetSecondExample()
{
	std::string randomShape;
	if (secondExampleOn && !secondSameExampleOn)
	{
		randomShape = shapes[shapes.size() - 1];
		if (randomShape == "circle")
		{
			secondCircleDrawOn = true;
			circleSecondColor = colorDictionary[colorKeys[colorKeys.size()-1]];
			circleVertices3 = BaseGame::GenerateCircle(exampleSpawnPositions[1], circleRadius, numSegments);
			GLCall(circleVB3->SubData(circleVertices3.size() * sizeof(std::vector<float>), circleVertices3.data()));
		}
		if (randomShape == "triangle")
		{
			triangleSecondColor = colorDictionary[colorKeys[colorKeys.size() - 1]];
			secondTriangleDrawOn = true;
			triangleVertices3 = BaseGame::GenerateTriangle(exampleSpawnPositions[1], baseLength, lineLength);
			GLCall(triangleVB3->SubData(triangleVertices3.size() * sizeof(std::vector<float>), triangleVertices3.data()));
		}
		if (randomShape == "square")
		{
			squareSecondColor = colorDictionary[colorKeys[colorKeys.size() - 1]];
			secondSquareDrawOn = true;
			squareVertices3 = BaseGame::GenerateSquare(exampleSpawnPositions[1], squareSize);
			GLCall(squareVB3->SubData(squareVertices3.size() * sizeof(std::vector<float>), squareVertices3.data()));
		}
		if (randomShape == "rectangle")
		{
			rectangleSecondColor = colorDictionary[colorKeys[colorKeys.size() - 1]];
			secondRectangleDrawOn = true;
			rectangleVertices3 = BaseGame::GenerateRectangle(exampleSpawnPositions[1], rectWidth, rectHeight);
			GLCall(rectangleVB3->SubData(rectangleVertices3.size() * sizeof(std::vector<float>), rectangleVertices3.data()));
		}
		if (randomShape == "star")
		{
			starSecondColor = colorDictionary[colorKeys[colorKeys.size() - 1]];
			secondStarDrawOn = true;
			starVertices3 = BaseGame::GenerateStar(exampleSpawnPositions[1], outerRadius, innerRadius, 5);
			GLCall(starVB3->SubData(starVertices3.size() * sizeof(std::vector<float>), starVertices3.data()));
		}
		if (randomShape == "hexagon")
		{
			hexagonSecondColor = colorDictionary[colorKeys[colorKeys.size() - 1]];
			secondHexagonDrawOn = true;
			hexagonVertices3 = BaseGame::GenerateHexagon(exampleSpawnPositions[1], hexagonRadius);
			GLCall(hexagonVB3->SubData(hexagonVertices3.size() * sizeof(std::vector<float>), hexagonVertices3.data()));
		}
		if (randomShape == "octagon")
		{
			octagonSecondColor = colorDictionary[colorKeys[colorKeys.size() - 1]];
			secondOctagonDrawOn = true;
			octagonVertices3 = BaseGame::GenerateOctagon(exampleSpawnPositions[1], octagonRadius);
			GLCall(octagonVB3->SubData(octagonVertices3.size() * sizeof(std::vector<float>), octagonVertices3.data()));
		}
	}
	if (secondSameExampleOn)
	{
		if (exampleCircleDrawOn)
		{
			secondCircleDrawOn = true;
			circleSecondColor = colorDictionary[mainExampleColor];
			circleVertices3 = BaseGame::GenerateCircle(exampleSpawnPositions[1], circleRadius, numSegments);
			GLCall(circleVB3->SubData(circleVertices3.size() * sizeof(std::vector<float>), circleVertices3.data()));
		}
		if (exampleTriangleDrawOn)
		{
			secondTriangleDrawOn = true;
			triangleSecondColor = colorDictionary[mainExampleColor];
			triangleVertices3 = BaseGame::GenerateTriangle(exampleSpawnPositions[1], baseLength, lineLength);
			GLCall(triangleVB3->SubData(triangleVertices3.size() * sizeof(std::vector<float>), triangleVertices3.data()));
		}
		if (exampleRectangleDrawOn)
		{
			secondRectangleDrawOn = true;
			rectangleSecondColor = colorDictionary[mainExampleColor];
			rectangleVertices3 = BaseGame::GenerateRectangle(exampleSpawnPositions[1], rectWidth, rectHeight);
			GLCall(rectangleVB3->SubData(rectangleVertices3.size() * sizeof(std::vector<float>), rectangleVertices3.data()));
		}
		if (exampleSquareDrawOn)
		{
			secondSquareDrawOn = true;
			squareSecondColor = colorDictionary[mainExampleColor];
			squareVertices3 = BaseGame::GenerateSquare(exampleSpawnPositions[1], squareSize);
			GLCall(squareVB3->SubData(squareVertices3.size() * sizeof(std::vector<float>), squareVertices3.data()));
		}
		if (exampleStarDrawOn)
		{
			secondStarDrawOn = true;
			starSecondColor = colorDictionary[mainExampleColor];
			starVertices3 = BaseGame::GenerateStar(exampleSpawnPositions[1], outerRadius, innerRadius, 5);
			GLCall(starVB3->SubData(starVertices3.size() * sizeof(std::vector<float>), starVertices3.data()));
		}
		if (exampleHexagonDrawOn)
		{
			secondHexagonDrawOn = true;
			hexagonSecondColor = colorDictionary[mainExampleColor];
			hexagonVertices3 = BaseGame::GenerateHexagon(exampleSpawnPositions[1], hexagonRadius);
			GLCall(hexagonVB3->SubData(hexagonVertices3.size() * sizeof(std::vector<float>), hexagonVertices3.data()));
		}
		if (exampleOctagonDrawOn)
		{
			secondOctagonDrawOn = true;
			octagonSecondColor = colorDictionary[mainExampleColor];
			octagonVertices3 = BaseGame::GenerateOctagon(exampleSpawnPositions[1], octagonRadius);
			GLCall(octagonVB3->SubData(octagonVertices3.size() * sizeof(std::vector<float>), octagonVertices3.data()));
		}
	}
}

void GameLearningAndApplying::ChooseWhatToDraw(std::string decider, int i, std::string which)
{

	if (which == "guess")
	{
		if (decider == "circle")
		{
			circleVertices = BaseGame::GenerateCircle(guessesSpawnPositions[i], circleRadius, numSegments);
			GLCall(circleVB->SubData(circleVertices.size() * sizeof(std::vector<float>), circleVertices.data()));
			guessCircleDrawOn = true;
		}
		else if (decider == "triangle")
		{
			triangleVertices = BaseGame::GenerateTriangle(guessesSpawnPositions[i], baseLength, lineLength);
			GLCall(triangleVB->SubData(triangleVertices.size() * sizeof(std::vector<float>), triangleVertices.data()));
			guessTriangleDrawOn = true;
		}
		else if (decider == "square")
		{
			squareVertices = BaseGame::GenerateSquare(guessesSpawnPositions[i], squareSize);
			GLCall(squareVB->SubData(squareVertices.size() * sizeof(std::vector<float>), squareVertices.data()));
			guessSquareDrawOn = true;
		}
		else if (decider == "rectangle")
		{
			rectangleVertices = BaseGame::GenerateRectangle(guessesSpawnPositions[i], rectWidth, rectHeight);
			GLCall(rectangleVB->SubData(rectangleVertices.size() * sizeof(std::vector<float>), rectangleVertices.data()));
			guessRectangleDrawOn = true;
		}
		else if (decider == "star")
		{
			starVertices = BaseGame::GenerateStar(guessesSpawnPositions[i], outerRadius, innerRadius, 5);
			GLCall(starVB->SubData(starVertices.size() * sizeof(std::vector<float>), starVertices.data()));
			guessStarDrawOn = true;
		}
		else if (decider == "hexagon")
		{
			hexagonVertices = BaseGame::GenerateHexagon(guessesSpawnPositions[i], hexagonRadius);
			GLCall(hexagonVB->SubData(hexagonVertices.size() * sizeof(std::vector<float>), hexagonVertices.data()));
			guessHexagonDrawOn = true;
		}
		else if (decider == "octagon")
		{
			octagonVertices = BaseGame::GenerateOctagon(guessesSpawnPositions[i], octagonRadius);
			GLCall(octagonVB->SubData(octagonVertices.size() * sizeof(std::vector<float>), octagonVertices.data()));
			guessOctagonDrawOn = true;
		}
	}
	else if (which == "example")
	{
		if (decider == "circle")
		{
			circleVertices2 = BaseGame::GenerateCircle(exampleSpawnPositions[i], circleRadius, numSegments);
			GLCall(circleVB2->SubData(circleVertices2.size() * sizeof(std::vector<float>), circleVertices2.data()));
			exampleCircleDrawOn = true;
		}
		else if (decider == "triangle")
		{
			triangleVertices2 = BaseGame::GenerateTriangle(exampleSpawnPositions[i], baseLength, lineLength);
			GLCall(triangleVB2->SubData(triangleVertices2.size() * sizeof(std::vector<float>), triangleVertices2.data()));
			exampleTriangleDrawOn = true;
		}
		else if (decider == "square")
		{
			squareVertices2 = BaseGame::GenerateSquare(exampleSpawnPositions[i], squareSize);
			GLCall(squareVB2->SubData(squareVertices2.size() * sizeof(std::vector<float>), squareVertices2.data()));
			exampleSquareDrawOn = true;
		}

		else if (decider == "star")
		{
			starVertices2 = BaseGame::GenerateStar(exampleSpawnPositions[i], outerRadius, innerRadius, 5);
			GLCall(starVB2->SubData(starVertices2.size() * sizeof(std::vector<float>), starVertices2.data()));
			exampleStarDrawOn = true;
		}
		else if (decider == "hexagon")
		{
			hexagonVertices2 = BaseGame::GenerateHexagon(exampleSpawnPositions[i], hexagonRadius);
			GLCall(hexagonVB2->SubData(hexagonVertices2.size() * sizeof(std::vector<float>), hexagonVertices2.data()));
			exampleHexagonDrawOn = true;
		}
		else if (decider == "octagon")
		{
			octagonVertices2 = BaseGame::GenerateOctagon(exampleSpawnPositions[i], octagonRadius);
			GLCall(octagonVB2->SubData(octagonVertices2.size() * sizeof(std::vector<float>), octagonVertices2.data()));
			exampleOctagonDrawOn = true;
		}
		else if (decider == "rectangle")
		{
			rectangleVertices2 = BaseGame::GenerateRectangle(exampleSpawnPositions[i], rectWidth, rectHeight);
			GLCall(rectangleVB2->SubData(rectangleVertices2.size() * sizeof(std::vector<float>), rectangleVertices2.data()));
			exampleRectangleDrawOn = true;
		}
	}
}

void GameLearningAndApplying::DrawGraphics()
{
	if (!taskIntroActive)
	{
		GLCall(flexibleShaderProgram->Bind());
		GLCall(flexibleShaderProgram->SetUniform4f("u_Color", appColor[0], appColor[1], appColor[2], appColor[3]));

		if (gameStarted && !taskIntroActive)
		{
			GLCall(btns1VA->Bind());
			GLCall(rectangleIB->Bind());
			if (btn1Hovering)
			{
				GLCall(flexibleShaderProgram->SetUniform4f("u_Color", btnHoverColor[0], btnHoverColor[1], btnHoverColor[2], btnHoverColor[3]));
			}
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
			GLCall(btns2VA->Bind());
			GLCall(rectangleIB->Bind());
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", appColor[0], appColor[1], appColor[2], appColor[3]));


			if (btn2Hovering)
			{
				GLCall(flexibleShaderProgram->SetUniform4f("u_Color", btnHoverColor[0], btnHoverColor[1], btnHoverColor[2], btnHoverColor[3]));
			}
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
			GLCall(btns3VA->Bind());
			GLCall(rectangleIB->Bind());
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", appColor[0], appColor[1], appColor[2], appColor[3]));


			if (btn3Hovering)
			{
				GLCall(flexibleShaderProgram->SetUniform4f("u_Color", btnHoverColor[0], btnHoverColor[1], btnHoverColor[2], btnHoverColor[3]));
			}
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
			GLCall(btns4VA->Bind());
			GLCall(rectangleIB->Bind());
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", appColor[0], appColor[1], appColor[2], appColor[3]));


			if (btn4Hovering)
			{
				GLCall(flexibleShaderProgram->SetUniform4f("u_Color", btnHoverColor[0], btnHoverColor[1], btnHoverColor[2], btnHoverColor[3]));
			}
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
			GLCall(btns5VA->Bind());
			GLCall(rectangleIB->Bind());
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", appColor[0], appColor[1], appColor[2], appColor[3]));


			if (btn5Hovering)
			{
				GLCall(flexibleShaderProgram->SetUniform4f("u_Color", btnHoverColor[0], btnHoverColor[1], btnHoverColor[2], btnHoverColor[3]));
			}
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", appColor[0], appColor[1], appColor[2], appColor[3]));

			GLCall(showVA->Bind());
			GLCall(doubleRectangleIB->Bind());
			GLCall(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, nullptr));
		}


		GLCall(flexibleShaderProgram->SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f));
		if (guessCircleDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", circleGuessColor[0], circleGuessColor[1], circleGuessColor[2], circleGuessColor[3]));
			GLCall(circleVA->Bind());
			GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, circleVertices.size() / 2));
		}

		if (guessTriangleDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", triangleGuessColor[0], triangleGuessColor[1], triangleGuessColor[2], triangleGuessColor[3]));

			GLCall(triangleVA->Bind());
			GLCall(glDrawArrays(GL_TRIANGLES, 0, triangleVertices.size() / 2))
		}

		if (guessSquareDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", squareGuessColor[0], squareGuessColor[1], squareGuessColor[2], squareGuessColor[3]));

			GLCall(squareVA->Bind());
			GLCall(rectangleIB->Bind());
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
		}

		if (guessRectangleDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", rectangleGuessColor[0], rectangleGuessColor[1], rectangleGuessColor[2], rectangleGuessColor[3]));

			GLCall(rectangleVA->Bind());
			GLCall(rectangleIB->Bind());
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr))
		}

		if (guessStarDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", starGuessColor[0], starGuessColor[1], starGuessColor[2], starGuessColor[3]));

			GLCall(starVA->Bind());
			GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, starVertices.size() / 2))
		}

		if (guessHexagonDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", hexagonGuessColor[0], hexagonGuessColor[1], hexagonGuessColor[2], hexagonGuessColor[3]));

			GLCall(hexagonVA->Bind());
			GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, hexagonVertices.size() / 2));
		}

		if (guessOctagonDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", octagonGuessColor[0], octagonGuessColor[1], octagonGuessColor[2], octagonGuessColor[3]));

			GLCall(octagonVA->Bind());
			GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, octagonVertices.size() / 2));
		}

		if (exampleCircleDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", circleExampleColor[0], circleExampleColor[1], circleExampleColor[2], circleExampleColor[3]));

			GLCall(circleVA2->Bind());
			GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, circleVertices2.size() / 2));
		}

		if (exampleTriangleDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", triangleExampleColor[0], triangleExampleColor[1], triangleExampleColor[2], triangleExampleColor[3]));

			GLCall(triangleVA2->Bind());
			GLCall(glDrawArrays(GL_TRIANGLES, 0, triangleVertices2.size() / 2))
		}

		if (exampleSquareDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", squareExampleColor[0], squareExampleColor[1], squareExampleColor[2], squareExampleColor[3]));

			GLCall(squareVA2->Bind());
			GLCall(rectangleIB->Bind());
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr))
		}
		if (exampleRectangleDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", rectangleExampleColor[0], rectangleExampleColor[1], rectangleExampleColor[2], rectangleExampleColor[3]));

			GLCall(rectangleVA2->Bind());
			GLCall(rectangleIB->Bind());
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
		}

		if (exampleStarDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", starExampleColor[0], starExampleColor[1], starExampleColor[2], starExampleColor[3]));

			GLCall(starVA2->Bind());
			GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, starVertices2.size() / 2))
		}

		if (exampleHexagonDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", hexagonExampleColor[0], hexagonExampleColor[1], hexagonExampleColor[2], hexagonExampleColor[3]));

			GLCall(hexagonVA2->Bind());
			GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, hexagonVertices2.size() / 2));
		}

		if (exampleOctagonDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", octagonExampleColor[0], octagonExampleColor[1], octagonExampleColor[2], octagonExampleColor[3]));

			GLCall(octagonVA2->Bind());
			GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, octagonVertices2.size() / 2));
		}
		if (secondCircleDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", circleSecondColor[0], circleSecondColor[1], circleSecondColor[2], circleSecondColor[3]));
			GLCall(circleVA3->Bind());
			GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, circleVertices3.size() / 2));
		}

		if (secondTriangleDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", triangleSecondColor[0], triangleSecondColor[1], triangleSecondColor[2], triangleSecondColor[3]));


			GLCall(triangleVA3->Bind());
			GLCall(glDrawArrays(GL_TRIANGLES, 0, triangleVertices3.size() / 2))
		}

		if (secondSquareDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", squareSecondColor[0], squareSecondColor[1], squareSecondColor[2], squareSecondColor[3]));
			GLCall(squareVA3->Bind());
			GLCall(rectangleIB->Bind());
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr))
		}
		if (secondRectangleDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", rectangleSecondColor[0], rectangleSecondColor[1], rectangleSecondColor[2], rectangleSecondColor[3]));
			GLCall(rectangleVA3->Bind());
			GLCall(rectangleIB->Bind());
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
		}

		if (secondStarDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", starSecondColor[0], starSecondColor[1], starSecondColor[2], starSecondColor[3]));
			GLCall(starVA3->Bind());
			GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, starVertices3.size() / 2))
		}

		if (secondHexagonDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", hexagonSecondColor[0], hexagonSecondColor[1], hexagonSecondColor[2], hexagonSecondColor[3]));
			GLCall(hexagonVA3->Bind());
			GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, hexagonVertices3.size() / 2));
		}

		if (secondOctagonDrawOn)
		{
			GLCall(flexibleShaderProgram->SetUniform4f("u_Color", octagonSecondColor[0], octagonSecondColor[1], octagonSecondColor[2], octagonSecondColor[3]));
			GLCall(octagonVA3->Bind());
			GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, octagonVertices3.size() / 2));
		}
	}

}

void GameLearningAndApplying::LoadShapeGraphics()
{
	//btns
	circleVA = new VertexArray();
	circleVB = new VertexBuffer(circleVertices.size() * sizeof(std::vector<float>), circleVertices.data(), "dynamic");
	circleVA->AddBuffer(circleVB, twoFloatVBL);

	triangleVA = new VertexArray();
	triangleVB = new VertexBuffer(triangleVertices.size() * sizeof(std::vector<float>), triangleVertices.data(), "dynamic");
	triangleVA->AddBuffer(triangleVB, twoFloatVBL);

	rectangleVA = new VertexArray();
	rectangleVB = new VertexBuffer(rectangleVertices.size() * sizeof(std::vector<float>), rectangleVertices.data(), "dynamic");
	rectangleVA->AddBuffer(rectangleVB, twoFloatVBL);

	squareVA = new VertexArray();
	squareVB = new VertexBuffer(squareVertices.size() * sizeof(std::vector<float>), squareVertices.data(), "dynamic");
	squareVA->AddBuffer(squareVB, twoFloatVBL);

	starVA = new VertexArray();
	starVB = new VertexBuffer(starVertices.size() * sizeof(std::vector<float>), starVertices.data(), "dynamic");
	starVA->AddBuffer(starVB, twoFloatVBL);

	octagonVA = new VertexArray();
	octagonVB = new VertexBuffer(octagonVertices.size() * sizeof(std::vector<float>), octagonVertices.data(), "dynamic");
	octagonVA->AddBuffer(octagonVB, twoFloatVBL);

	hexagonVA = new VertexArray();
	hexagonVB = new VertexBuffer(hexagonVertices.size() * sizeof(std::vector<float>), hexagonVertices.data(), "dynamic");
	hexagonVA->AddBuffer(hexagonVB, twoFloatVBL);

	//examples
	circleVA2 = new VertexArray();
	circleVB2 = new VertexBuffer(circleVertices2.size() * sizeof(std::vector<float>), circleVertices2.data(), "dynamic");
	circleVA2->AddBuffer(circleVB2, twoFloatVBL);

	triangleVA2 = new VertexArray();
	triangleVB2 = new VertexBuffer(triangleVertices2.size() * sizeof(std::vector<float>), triangleVertices2.data(), "dynamic");
	triangleVA2->AddBuffer(triangleVB2, twoFloatVBL);

	rectangleVA2 = new VertexArray();
	rectangleVB2 = new VertexBuffer(rectangleVertices2.size() * sizeof(std::vector<float>), rectangleVertices2.data(), "dynamic");
	rectangleVA2->AddBuffer(rectangleVB2, twoFloatVBL);

	squareVA2 = new VertexArray();
	squareVB2 = new VertexBuffer(squareVertices2.size() * sizeof(std::vector<float>), squareVertices2.data(), "dynamic");
	squareVA2->AddBuffer(squareVB2, twoFloatVBL);

	starVA2 = new VertexArray();
	starVB2 = new VertexBuffer(starVertices2.size() * sizeof(std::vector<float>), starVertices2.data(), "dynamic");
	starVA2->AddBuffer(starVB2, twoFloatVBL);

	octagonVA2 = new VertexArray();
	octagonVB2 = new VertexBuffer(octagonVertices2.size() * sizeof(std::vector<float>), octagonVertices2.data(), "dynamic");
	octagonVA2->AddBuffer(octagonVB2, twoFloatVBL);

	hexagonVA2 = new VertexArray();
	hexagonVB2 = new VertexBuffer(hexagonVertices2.size() * sizeof(std::vector<float>), hexagonVertices2.data(), "dynamic");
	hexagonVA2->AddBuffer(hexagonVB2, twoFloatVBL);

	circleVA3 = new VertexArray();
	circleVB3 = new VertexBuffer(circleVertices3.size() * sizeof(std::vector<float>), circleVertices3.data(), "dynamic");
	circleVA3->AddBuffer(circleVB3, twoFloatVBL);

	triangleVA3 = new VertexArray();
	triangleVB3 = new VertexBuffer(triangleVertices3.size() * sizeof(std::vector<float>), triangleVertices3.data(), "dynamic");
	triangleVA3->AddBuffer(triangleVB3, twoFloatVBL);

	rectangleVA3 = new VertexArray();
	rectangleVB3 = new VertexBuffer(rectangleVertices3.size() * sizeof(std::vector<float>), rectangleVertices3.data(), "dynamic");
	rectangleVA3->AddBuffer(rectangleVB3, twoFloatVBL);

	squareVA3 = new VertexArray();
	squareVB3 = new VertexBuffer(squareVertices3.size() * sizeof(std::vector<float>), squareVertices3.data(), "dynamic");
	squareVA3->AddBuffer(squareVB3, twoFloatVBL);

	starVA3 = new VertexArray();
	starVB3 = new VertexBuffer(starVertices3.size() * sizeof(std::vector<float>), starVertices3.data(), "dynamic");
	starVA3->AddBuffer(starVB3, twoFloatVBL);

	octagonVA3 = new VertexArray();
	octagonVB3 = new VertexBuffer(octagonVertices3.size() * sizeof(std::vector<float>), octagonVertices3.data(), "dynamic");
	octagonVA3->AddBuffer(octagonVB3, twoFloatVBL);

	hexagonVA3 = new VertexArray();
	hexagonVB3 = new VertexBuffer(hexagonVertices3.size() * sizeof(std::vector<float>), hexagonVertices3.data(), "dynamic");
	hexagonVA3->AddBuffer(hexagonVB3, twoFloatVBL);
}

void GameLearningAndApplying::LoadButtonGraphics()
{
	btns1VA = new VertexArray();
	btns1VB = new VertexBuffer(sizeof(btnVertices1), btnVertices1, "static");
	btns1VA->AddBuffer(btns1VB, twoFloatVBL);
	btns2VA = new VertexArray();
	btns2VB = new VertexBuffer(sizeof(btnVertices2), btnVertices2, "static");
	btns2VA->AddBuffer(btns2VB, twoFloatVBL);
	btns3VA = new VertexArray();
	btns3VB = new VertexBuffer(sizeof(btnVertices3), btnVertices3, "static");
	btns3VA->AddBuffer(btns3VB, twoFloatVBL);
	btns4VA = new VertexArray();
	btns4VB = new VertexBuffer(sizeof(btnVertices4), btnVertices4, "static");
	btns4VA->AddBuffer(btns4VB, twoFloatVBL);
	btns5VA = new VertexArray();
	btns5VB = new VertexBuffer(sizeof(btnVertices5), btnVertices5, "static");
	btns5VA->AddBuffer(btns5VB, twoFloatVBL);


	showVA = new VertexArray();
	showVB = new VertexBuffer(sizeof(exampleVertices), exampleVertices, "static");
	showVA->AddBuffer(showVB, twoFloatVBL);
}

void GameLearningAndApplying::Draw()
{

	glClearColor(greyColor2[0], greyColor2[1], greyColor2[2], greyColor2[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	GameLearningAndApplying::DrawGraphics();
	BaseGame::DrawCountDown();
	BaseGame::DrawAmountOfRounds();
	BaseGame::DrawTasksIntroGraphics();
	GameLearningAndApplying::DrawText();
	BaseGame::DrawPause();

}

void GameLearningAndApplying::Update()
{
	if (!gamePaused)
	{
		GameLearningAndApplying::UpdateTime();
	}
};

GameLearningAndApplying::~GameLearningAndApplying()
{
	// Delete VertexArrays
	delete btns1VA;
	delete btns2VA;
	delete btns3VA;
	delete btns4VA;
	delete btns5VA;
	delete showVA;
	delete triangleVA;
	delete circleVA;
	delete rectangleVA;
	delete squareVA;
	delete hexagonVA;
	delete octagonVA;
	delete starVA;
	delete btnsVA2;
	delete showVA2;
	delete triangleVA2;
	delete circleVA2;
	delete rectangleVA2;
	delete squareVA2;
	delete hexagonVA2;
	delete octagonVA2;
	delete starVA2;
	delete triangleVA3;
	delete circleVA3;
	delete rectangleVA3;
	delete squareVA3;
	delete hexagonVA3;
	delete octagonVA3;
	delete starVA3;

	// Delete VertexBuffers
	delete btns1VB;
	delete btns2VB;
	delete btns3VB;
	delete btns4VB;
	delete btns5VB;
	delete showVB;
	delete triangleVB;
	delete circleVB;
	delete rectangleVB;
	delete squareVB;
	delete hexagonVB;
	delete octagonVB;
	delete starVB;
	delete btnsVB2;
	delete showVB2;
	delete triangleVB2;
	delete circleVB2;
	delete rectangleVB2;
	delete squareVB2;
	delete hexagonVB2;
	delete octagonVB2;
	delete starVB2;
	delete triangleVB3;
	delete circleVB3;
	delete rectangleVB3;
	delete squareVB3;
	delete hexagonVB3;
	delete octagonVB3;
	delete starVB3;

	// Delete VertexBufferLayouts
	delete showVBL;
	delete triangleVBL;
	delete rectangleVBL;
	delete squareVBL;
	delete hexagonVBL;
	delete octagonVBL;
	delete starVBL;
	delete btnsVBL2;
	delete showVBL2;
	delete triangleVBL2;
	delete rectangleVBL2;
	delete squareVBL2;
	delete hexagonVBL2;
	delete octagonVBL2;
	delete starVBL2;
	delete triangleVBL3;
	delete rectangleVBL3;
	delete squareVBL3;
	delete hexagonVBL3;
	delete octagonVBL3;
	delete starVBL3;

	// Delete IndexBuffers
	delete showIB;
	delete btnsIB2;
	delete showIB2;

	// Set pointers to nullptr
	btns1VA = nullptr;
	btns2VA = nullptr;
	btns3VA = nullptr;
	btns4VA = nullptr;
	btns5VA = nullptr;
	showVA = nullptr;
	triangleVA = nullptr;
	circleVA = nullptr;
	rectangleVA = nullptr;
	squareVA = nullptr;
	hexagonVA = nullptr;
	octagonVA = nullptr;
	starVA = nullptr;
	btnsVA2 = nullptr;
	showVA2 = nullptr;
	triangleVA2 = nullptr;
	circleVA2 = nullptr;
	rectangleVA2 = nullptr;
	squareVA2 = nullptr;
	hexagonVA2 = nullptr;
	octagonVA2 = nullptr;
	starVA2 = nullptr;
	triangleVA3 = nullptr;
	circleVA3 = nullptr;
	rectangleVA3 = nullptr;
	squareVA3 = nullptr;
	hexagonVA3 = nullptr;
	octagonVA3 = nullptr;
	starVA3 = nullptr;

	btns1VB = nullptr;
	btns2VB = nullptr;
	btns3VB = nullptr;
	btns4VB = nullptr;
	btns5VB = nullptr;
	showVB = nullptr;
	triangleVB = nullptr;
	circleVB = nullptr;
	rectangleVB = nullptr;
	squareVB = nullptr;
	hexagonVB = nullptr;
	octagonVB = nullptr;
	starVB = nullptr;
	btnsVB2 = nullptr;
	showVB2 = nullptr;
	triangleVB2 = nullptr;
	circleVB2 = nullptr;
	rectangleVB2 = nullptr;
	squareVB2 = nullptr;
	hexagonVB2 = nullptr;
	octagonVB2 = nullptr;
	starVB2 = nullptr;
	triangleVB3 = nullptr;
	circleVB3 = nullptr;
	rectangleVB3 = nullptr;
	squareVB3 = nullptr;
	hexagonVB3 = nullptr;
	octagonVB3 = nullptr;
	starVB3 = nullptr;

	showVBL = nullptr;
	triangleVBL = nullptr;
	rectangleVBL = nullptr;
	squareVBL = nullptr;
	hexagonVBL = nullptr;
	octagonVBL = nullptr;
	starVBL = nullptr;
	btnsVBL2 = nullptr;
	showVBL2 = nullptr;
	triangleVBL2 = nullptr;
	rectangleVBL2 = nullptr;
	squareVBL2 = nullptr;
	hexagonVBL2 = nullptr;
	octagonVBL2 = nullptr;
	starVBL2 = nullptr;
	triangleVBL3 = nullptr;
	rectangleVBL3 = nullptr;
	squareVBL3 = nullptr;
	hexagonVBL3 = nullptr;
	octagonVBL3 = nullptr;
	starVBL3 = nullptr;

	showIB = nullptr;
	btnsIB2 = nullptr;
	showIB2 = nullptr;

}
