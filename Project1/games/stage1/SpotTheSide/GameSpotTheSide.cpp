#include "GameSpotTheSide.h"
//make a counter
GameSpotTheSide::GameSpotTheSide(int level, std::string typeOfGame, int startW, int startH, int creatorW, int creatorH, std::string typeOfTimer)
	: BaseGame(level, typeOfGame, startW, startH, creatorW, creatorH, typeOfTimer)
{

	justRun = false;
	this->creatorW = creatorW;
	this->creatorH = creatorH;
	this->level = level;
	this->typeOfGame = typeOfGame;
	imageBack = new STBimage("img/SpotTheSide/bodyback.png");
	imageFront = new STBimage("img/SpotTheSide/bodyfront.png");
	imageSide = new STBimage("img/SpotTheSide/bodysideleft.png");

	optionBtn1Visible = true;
	optionBtn2Visible = true;
	borderMargin = 50;
	if (typeOfGame == "practice")
	{
		if (level == 1)
		{
			typeOfQuestion.push_back("Normal");
			numOfShapes = 2;
			iteratorNumOfShapes = numOfShapes;
			directions.push_back("backup");
			directions.push_back("frontup");
			taskIntroTimeMilisecs = 5000;

		}
		else if (level == 2)
		{
			typeOfQuestion.push_back("Normal");
			typeOfQuestion.push_back("MainObject");
			numOfShapes = 3;
			iteratorNumOfShapes = numOfShapes;
			directions.push_back("backup");
			directions.push_back("frontup");
			directions.push_back("backdown");
			directions.push_back("frontdown");
			taskIntroTimeMilisecs = 4000;

		}
		else if (level == 3)
		{
			typeOfQuestion.push_back("Normal");
			typeOfQuestion.push_back("Negation");
			//typeOfQuestion.push_back("MainObject");

			numOfShapes = 3;
			iteratorNumOfShapes = numOfShapes;
			directions.push_back("backup");
			directions.push_back("frontup");
			directions.push_back("backdown");
			directions.push_back("frontdown");
			directions.push_back("leftup");
			directions.push_back("rightup");
			directions.push_back("leftdown");
			directions.push_back("rightdown");


			taskIntroTimeMilisecs = 3200;

		}
	}
	else if (typeOfGame == "test")
	{
		typeOfQuestion.push_back("Normal");
		typeOfQuestion.push_back("MainObject");
		typeOfQuestion.push_back("Negation");
		numOfShapes = 3;
		iteratorNumOfShapes = numOfShapes;
		directions.push_back("backup");
		directions.push_back("frontup");
		directions.push_back("backdown");
		directions.push_back("frontdown");
		directions.push_back("leftup");
		directions.push_back("rightup");
		directions.push_back("leftdown");
		directions.push_back("rightdown");
		taskIntroTimeMilisecs = 3200;

	}


	GameSpotTheSide::GenerateSpawnPositions();
	GameSpotTheSide::GenerateTriangle(glm::vec2(2.0f, 2.0f), false, 1);
	GameSpotTheSide::GenerateCircle(glm::vec2(2.0f, 2.0f), false, 1);
	GameSpotTheSide::GenerateSquare(glm::vec2(2.0f, 2.0f), false, 1);
	GameSpotTheSide::GenerateRectangle(glm::vec2(2.0f, 2.0f), false, 1);


	GameSpotTheSide::GenerateTriangle(glm::vec2(2.0f, 2.0f), true, 1);
	GameSpotTheSide::GenerateCircle(glm::vec2(2.0f, 2.0f), true, 1);
	GameSpotTheSide::GenerateSquare(glm::vec2(2.0f, 2.0f), true, 1);
	GameSpotTheSide::GenerateRectangle(glm::vec2(2.0f, 2.0f), true, 1);


	GameSpotTheSide::ChangeVertices();
}

void GameSpotTheSide::HandleShaders(int nowW, int nowH, int creatorW, int creatorH, int startW, int startH)
{
	wRatio = (float)nowW / startW;
	hRatio = (float)nowH / startH;
	BaseWindowDiffW = (creatorW - nowW) / 2;
	BaseWindowDiffH = (creatorH - nowH) / 2;

	glm::mat4 normalizeOrtho = glm::ortho(0.0f, static_cast<float>(nowW), 0.0f, static_cast<float>(nowH));
	ratioProjection = glm::ortho(-wRatio, wRatio, -hRatio, hRatio, -1.0f, 1.0f);





	GLCall(staticShaderProgram->Bind());
	GLCall(staticShaderProgram->SetUniform2f("u_WindowSize", nowW, nowH));
	GLCall(staticShaderProgram->Unbind());

	GLCall(textFlexibleShaderProgram->Bind());
	GLCall(textFlexibleShaderProgram->SetUniform2f("u_Ratio", wRatio, hRatio));
	GLCall(textFlexibleShaderProgram->SetUniformMatrix4fv("normalizeOrtho", 1, GL_FALSE, glm::value_ptr(normalizeOrtho)));
	GLCall(textFlexibleShaderProgram->SetUniformMatrix4fv("projection3", 1, GL_FALSE, glm::value_ptr(ratioProjection)));
	GLCall(textFlexibleShaderProgram->Unbind());

	GLCall(textStaticShaderProgram->Bind());
	GLCall(textStaticShaderProgram->SetUniformMatrix4fv("normalizeOrtho", 1, GL_FALSE, glm::value_ptr(normalizeOrtho)));


	GameSpotTheSide::HandleImageStaticShader();
	GameSpotTheSide::HandleNormalFlexibleShader();
}

void GameSpotTheSide::HandleImageStaticShader()
{
	GLCall(staticImageShaderProgram->Bind());
	if (sideActiveInt == 1)
	{
		GLCall(staticImageShaderProgram->SetUniform1i("xReverse", leftRight));
	}
	else
	{
		GLCall(staticImageShaderProgram->SetUniform1i("xReverse", 1));
	}
	GLCall(staticImageShaderProgram->SetUniform1i("yReverse", upDown));
}

void GameSpotTheSide::HandleNormalFlexibleShader()
{
	GLCall(flexibleShaderProgram->Bind());
	GLCall(flexibleShaderProgram->SetUniformMatrix4fv("u_OrthographicMatrix", 1, GL_FALSE, glm::value_ptr(ratioProjection)));
	if (upDown == -1)
	{
		GLCall(flexibleShaderProgram->SetUniform2f("u_Ratio", wRatio, -hRatio));

	}
	else if (upDown == 1)
	{
		GLCall(flexibleShaderProgram->SetUniform2f("u_Ratio", wRatio, hRatio));

	}
	GLCall(flexibleShaderProgram->SetUniform2f("u_WindowSize", nowW, nowH));
	GLCall(flexibleShaderProgram->SetUniform2f("u_BaseWindowDiff", BaseWindowDiffW, BaseWindowDiffH));
	GLCall(flexibleShaderProgram->Unbind());
}

void GameSpotTheSide::GenerateCircle(glm::vec2 spawnPoint, bool secondShape, int size)
{

	if (!secondShape)
	{
		circleReal.clear();
	}
	else if (secondShape)
	{
		circleSecond.clear();
	}

	float radius = 0.0f;
	if (size == 0)
	{
		radius = shapeDiameter / 4;
	}
	else if (size == 1)
	{
		radius = shapeDiameter / 2;
	}
	else if (size == 2)
	{
		radius = shapeDiameter / 1.25;
	}
	float numSegments = 18.0f;

	for (int i = 0; i < numSegments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
		float x = radius * cos(theta) + spawnPoint.x;
		float y = radius * sin(theta) + spawnPoint.y;
		if (!secondShape)
		{
			circleReal.push_back(x);
			circleReal.push_back(y);
		}
		else if (secondShape)
		{
			circleSecond.push_back(x);
			circleSecond.push_back(y);
		}

	};
}

void GameSpotTheSide::GenerateTriangle(glm::vec2 spawnPoint, bool secondShape, int size)
{


	float baseLength = 0.0f;
	float lineLength = 0.0f;


	if (size == 0)
	{
		baseLength = shapeDiameter / 2.8f;
		lineLength = shapeDiameter / 2.8f;
	}
	else if (size == 1)
	{
		baseLength = shapeDiameter / 1.5f;
		lineLength = shapeDiameter / 1.5f;
	}
	else if (size == 2)
	{
		baseLength = shapeDiameter;
		lineLength = shapeDiameter;
	}

	float x = spawnPoint.x;
	float y = spawnPoint.y;

	float armAngleFromMiddle = 45.0f;
	float armAngleFromMiddleRad = glm::radians(armAngleFromMiddle);

	float upX1 = x;
	float upY1 = y - lineLength;
	float leftX1 = x + baseLength * cos(armAngleFromMiddleRad);
	float leftY1 = y + baseLength * sin(armAngleFromMiddleRad);
	float rightX1 = x - baseLength * cos(-armAngleFromMiddleRad);
	float rightY1 = y - baseLength * sin(-armAngleFromMiddleRad);

	if (!secondShape)
	{
		triangleReal.clear();

		triangleReal.push_back(upX1);
		triangleReal.push_back(upY1);
		triangleReal.push_back(leftX1);
		triangleReal.push_back(leftY1);
		triangleReal.push_back(rightX1);
		triangleReal.push_back(rightY1);
	}
	else if (secondShape)
	{
		triangleSecond.clear();

		triangleSecond.push_back(upX1);
		triangleSecond.push_back(upY1);
		triangleSecond.push_back(leftX1);
		triangleSecond.push_back(leftY1);
		triangleSecond.push_back(rightX1);
		triangleSecond.push_back(rightY1);
	}
}

void GameSpotTheSide::GenerateSquare(glm::vec2 spawnPoint, bool secondShape, int size)
{

	float width = 0.0f;
	float height = 0.0f;

	if (size == 0)
	{
		width = shapeDiameter / 2.0f;
		height = shapeDiameter / 2.0f;
	}
	else if (size == 1)
	{
		width = shapeDiameter;
		height = shapeDiameter;
	}
	else if (size == 2)
	{
		width = shapeDiameter * 1.6f;
		height = shapeDiameter * 1.6f;
	}

	float topLeftX = spawnPoint.x - width / 2.0f;
	float topLeftY = spawnPoint.y - height / 2.0f;
	float topRightX = spawnPoint.x + width / 2.0f;
	float topRightY = spawnPoint.y - height / 2.0f;
	float bottomLeftX = spawnPoint.x - width / 2.0f;
	float bottomLeftY = spawnPoint.y + height / 2.0f;
	float bottomRightX = spawnPoint.x + width / 2.0f;
	float bottomRightY = spawnPoint.y + height / 2.0f;

	if (!secondShape)
	{
		squareReal.clear();

		squareReal.push_back(topLeftX);
		squareReal.push_back(topLeftY);
		squareReal.push_back(topRightX);
		squareReal.push_back(topRightY);
		squareReal.push_back(bottomRightX);
		squareReal.push_back(bottomRightY);
		squareReal.push_back(bottomLeftX);
		squareReal.push_back(bottomLeftY);
	}
	else if (secondShape)
	{
		squareSecond.clear();

		squareSecond.push_back(topLeftX);
		squareSecond.push_back(topLeftY);
		squareSecond.push_back(topRightX);
		squareSecond.push_back(topRightY);
		squareSecond.push_back(bottomRightX);
		squareSecond.push_back(bottomRightY);
		squareSecond.push_back(bottomLeftX);
		squareSecond.push_back(bottomLeftY);
	}
}

void GameSpotTheSide::GenerateRectangle(glm::vec2 spawnPoint, bool secondShape, int size)
{

	float width = 0.0f;
	float height = 0.0f;

	if (size == 0)
	{
		width = shapeDiameter * 0.85;
		height = shapeDiameter * 0.4;
	}
	else if (size == 1)
	{
		width = shapeDiameter * 1.7;
		height = shapeDiameter * 0.7;
	}
	else if (size == 2)
	{
		width = shapeDiameter * 2.3;
		height = shapeDiameter * 1.0;
	}

	float topLeftX = spawnPoint.x - width / 2.0f;
	float topLeftY = spawnPoint.y - height / 2.0f;
	float topRightX = spawnPoint.x + width / 2.0f;
	float topRightY = spawnPoint.y - height / 2.0f;
	float bottomLeftX = spawnPoint.x - width / 2.0f;
	float bottomLeftY = spawnPoint.y + height / 2.0f;
	float bottomRightX = spawnPoint.x + width / 2.0f;
	float bottomRightY = spawnPoint.y + height / 2.0f;

	if (!secondShape)
	{
		rectangleReal.clear();

		rectangleReal.push_back(topLeftX);
		rectangleReal.push_back(topLeftY);
		rectangleReal.push_back(topRightX);
		rectangleReal.push_back(topRightY);
		rectangleReal.push_back(bottomRightX);
		rectangleReal.push_back(bottomRightY);
		rectangleReal.push_back(bottomLeftX);
		rectangleReal.push_back(bottomLeftY);
	}
	else if (secondShape)
	{
		rectangleSecond.clear();

		rectangleSecond.push_back(topLeftX);
		rectangleSecond.push_back(topLeftY);
		rectangleSecond.push_back(topRightX);
		rectangleSecond.push_back(topRightY);
		rectangleSecond.push_back(bottomRightX);
		rectangleSecond.push_back(bottomRightY);
		rectangleSecond.push_back(bottomLeftX);
		rectangleSecond.push_back(bottomLeftY);
	}
}

void GameSpotTheSide::DrawText()
{
	if (!taskIntroActive && gameStarted)
	{
		CreateTextToRect(questionString, 0.4f, 0.0f, 0.0f, creatorW, 30.0f, blackColor[0], blackColor[1], blackColor[2], 1);
	}
	if (roundOver)
	{
		if (answeredCorrectly)
		{
			CreateText("Correct!", 0.6f, 25.0f, 25.0f, greenColor2[0], greenColor2[1], greenColor2[2], 1);
		}
		else
		{
			CreateText("Wrong!", 0.6f, 25.0f, 25.0f, redColor[0], redColor[1], redColor[2], 1);
		}
	}

}

void GameSpotTheSide::LeftClickBtn(float xPos, float yPos)
{
}

void GameSpotTheSide::LoadAllGraphics()
{
	BaseGame::LoadAllGraphics();
	GameSpotTheSide::LoadShapesGraphics();
}

void GameSpotTheSide::LoadShapesGraphics()
{

	circlikVA = new VertexArray();
	circlikVB = new VertexBuffer(circleReal.size() * sizeof(std::vector<float>), circleReal.data(), "dynamic");
	circlikVA->AddBuffer(circlikVB, twoFloatVBL);
	circlik2VA = new VertexArray();
	circlik2VB = new VertexBuffer(circleSecond.size() * sizeof(std::vector<float>), circleSecond.data(), "dynamic");
	circlik2VA->AddBuffer(circlik2VB, twoFloatVBL);

	trianglikVA = new VertexArray();
	trianglikVB = new VertexBuffer(triangleReal.size() * sizeof(std::vector<float>), triangleReal.data(), "dynamic");
	trianglikVA->AddBuffer(trianglikVB, twoFloatVBL);
	trianglik2VA = new VertexArray();
	trianglik2VB = new VertexBuffer(triangleSecond.size() * sizeof(std::vector<float>), triangleSecond.data(), "dynamic");
	trianglik2VA->AddBuffer(trianglik2VB, twoFloatVBL);

	rectikVA = new VertexArray();
	rectikVB = new VertexBuffer(rectangleReal.size() * sizeof(std::vector<float>), rectangleReal.data(), "dynamic");
	rectikVA->AddBuffer(rectikVB, twoFloatVBL);
	rectik2VA = new VertexArray();
	rectik2VB = new VertexBuffer(rectangleSecond.size() * sizeof(std::vector<float>), rectangleSecond.data(), "dynamic");
	rectik2VA->AddBuffer(rectik2VB, twoFloatVBL);

	squarikVA = new VertexArray();
	squarikVB = new VertexBuffer(squareReal.size() * sizeof(std::vector<float>), squareReal.data(), "dynamic");
	squarikVA->AddBuffer(squarikVB, twoFloatVBL);
	squarik2VA = new VertexArray();
	squarik2VB = new VertexBuffer(squareSecond.size() * sizeof(std::vector<float>), squareSecond.data(), "dynamic");
	squarik2VA->AddBuffer(squarik2VB, twoFloatVBL);

	imageVA = new VertexArray();
	imageVB = new VertexBuffer(sizeof(vertices), vertices, "static");
	imageIB = new IndexBuffer(6, pictureIndices);
	imageVBL = new VertexBufferLayout();
	imageVBL->Push<float>(3);
	imageVBL->Push<float>(3);
	imageVBL->Push<float>(2);
	imageVA->AddBuffer(imageVB, imageVBL);
}



void GameSpotTheSide::DrawGraphics()
{
	if (gameStarted && !taskIntroActive)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		GLCall(staticImageShaderProgram->Bind());
		imageVA->Bind();
		if (backFront == 1 && !onSide)
		{
			imageFront->Bind(0);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		}
		else if (backFront == -1 && !onSide)
		{
			imageBack->Bind(0);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		}
		else if (onSide)
		{
			imageSide->Bind(0);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		}
		BaseGame::DisableBlending();
	}

	if (!taskIntroActive && gameStarted)
	{
		GLCall(flexibleShaderProgram->Bind());
		GLCall(flexibleShaderProgram->SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f));

		if (circleDrawOn)
		{
			circlikVB->SubData(circleReal.size() * sizeof(std::vector<float>), circleReal.data());
			GLCall(circlikVA->Bind());
			GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, circleReal.size() / 2));
		}
		if (secondCircleDrawOn)
		{
			circlikVB->SubData(circleSecond.size() * sizeof(std::vector<float>), circleSecond.data());
			GLCall(circlikVA->Bind());
			GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, circleSecond.size() / 2));
		}

		if (triangleDrawOn)
		{
			trianglikVB->SubData(triangleReal.size() * sizeof(std::vector<float>), triangleReal.data());
			GLCall(trianglikVA->Bind());
			GLCall(glDrawArrays(GL_TRIANGLES, 0, triangleReal.size() / 2))
		}
		if (secondTriangleDrawOn)
		{
			trianglikVB->SubData(triangleSecond.size() * sizeof(std::vector<float>), triangleSecond.data());
			GLCall(trianglikVA->Bind());
			GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, triangleSecond.size() / 2));
		}

		if (rectangleDrawOn)
		{
			rectikVB->SubData(rectangleReal.size() * sizeof(std::vector<float>), rectangleReal.data());
			GLCall(rectikVA->Bind());
			GLCall(rectangleIB->Bind());
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
		}
		if (secondRectangleDrawOn)
		{
			rectikVB->SubData(rectangleSecond.size() * sizeof(std::vector<float>), rectangleSecond.data());
			GLCall(rectikVA->Bind());
			GLCall(rectangleIB->Bind());
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr))
		}

		if (squareDrawOn)
		{
			squarikVB->SubData(squareReal.size() * sizeof(std::vector<float>), squareReal.data());
			GLCall(squarikVA->Bind());
			GLCall(rectangleIB->Bind());
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr))
		}
		if (secondSquareDrawOn)
		{
			squarikVB->SubData(squareSecond.size() * sizeof(std::vector<float>), squareSecond.data());
			GLCall(squarikVA->Bind());
			GLCall(rectangleIB->Bind());
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
		}
	}
}

void GameSpotTheSide::CreateQuestion()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	do
	{
		std::shuffle(typeOfQuestion.begin(), typeOfQuestion.end(), gen);
		activeQuestion = typeOfQuestion[0];
	} while (onSide && activeQuestion == "MainObject");

	if (activeQuestion == "Normal")
	{
		questionString = "Where is " + shapeLookingFor + "?";
	}
	else if (activeQuestion == "Negation")
	{
		questionString = "Where is NOT " + shapeLookingFor + "?";
	}
	else if (activeQuestion == "MainObject")
	{
		questionString = "Where is main object?";
	}
}

void GameSpotTheSide::ChooseLayout()
{
	firstSmallOrBig = -1;
	secondSmallOrBig = -1;
	sideSearchedShapeBig = false;
	sideSearchedShapeSmall = true;
	onSide = false;
	leftRight = 1;
	sideActiveInt = 0;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(-1, 1);
	std::uniform_int_distribution<> distrib2(0, 1);

	if (level == 3 || typeOfGame == "test")
	{
		sideActiveInt = distrib2(gen);// -1 = side profile off, 1 = side profile on, decides if image will be seen from the side
		upDown = distrib2(gen) * 2 - 1;
		sideActiveInt = 0;
		if (sideActiveInt == 1)
		{
			onSide = true;
			leftRight = distrib2(gen) * 2 - 1;//from side will be image rotated
			firstSmallOrBig = distrib2(gen) * 2; //checking if searching shape will be big or small // 0 or 1, will be added to creating shapes function
		}
		else
		{
			backFront = distrib2(gen) * 2 - 1;

		}

		if (!onSide)
		{
			finalSide = -backFront * upDown;
		}
		else
		{
			finalSide = upDown * leftRight;
		}
	}

	if (level == 1 || level == 2)
	{
		backFront = distrib2(gen) * 2 - 1; // checking if image will be from front or back
		upDown = distrib2(gen) * 2 - 1; // checking if image will be head down or head up;
		finalSide = -backFront * upDown; //final checking where searched shape is.. (right or left) left = -1, right 1
	}
}

void GameSpotTheSide::DeleteSearchedPosition()
{
	finishedSpawnPositions.clear();
	std::vector<int> indexesToRemove;

	if (activeQuestion == "MainObject")
	{
		for (int i = 0; i < spawnPositions.size(); i++)
		{
			if (spawnPositions[i] != searchedShapePosition && spawnPositions[i] != fakeShapePosition)
			{
				finishedSpawnPositions.push_back(spawnPositions[i]);
			}
		}
	}
	else
	{
		for (int i = 0; i < spawnPositions.size(); i++)
		{
			if (spawnPositions[i] != searchedShapePosition)
			{
				finishedSpawnPositions.push_back(spawnPositions[i]);
			}
		}
	}
}

void GameSpotTheSide::GenerateSpawnPositions()
{
	bigFirstSide = false;
	int middleShapesDifference = 60;
	firstSideObjectPosition = creatorW / 2 - middleShapesDifference / 2;
	secondSideObjectPosition = creatorW / 2 + middleShapesDifference / 2;

	spawnPositions.clear();
	guessingSpawnPositions.clear();
	fakeSpawnPositions.clear();
	sideSpawnPositions.clear();

	spawnPositions.push_back(glm::vec2(creatorW / 2, creatorH - borderMargin)); //bottom 
	spawnPositions.push_back(glm::vec2(creatorW / 2, borderMargin)); //top
	spawnPositions.push_back(glm::vec2(borderMargin, creatorH / 2)); //left
	spawnPositions.push_back(glm::vec2(creatorW - borderMargin, creatorH / 2)); //right

	guessingSpawnPositions.push_back(glm::vec2(borderMargin, creatorH / 2)); //left
	guessingSpawnPositions.push_back(glm::vec2(creatorW - borderMargin, creatorH / 2)); //right

	fakeSpawnPositions.push_back(glm::vec2(creatorW / 2, creatorH - borderMargin)); //bottom
	fakeSpawnPositions.push_back(glm::vec2(creatorW / 2, borderMargin)); //top

	sideSpawnPositions.push_back(glm::vec2(firstSideObjectPosition, creatorH / 3)); //mid left
	sideSpawnPositions.push_back(glm::vec2(secondSideObjectPosition, creatorH / 3));  // mid right
}

void GameSpotTheSide::ChangeVertices() // po shufflovani bude generovana hodnota vzdy ta prvni (shapes[0], position[0])
{
	std::random_device rd;
	std::mt19937 gen(rd());
	GameSpotTheSide::GenerateSpawnPositions(); //reset shape spawn positions
	GameSpotTheSide::ChooseLayout(); //choosing picture position(frontup,...)

	std::shuffle(shapes, shapes + 4, gen);
	shapeLookingFor = shapes[0];
	GameSpotTheSide::CreateQuestion(); //creating string of question
	std::shuffle(spawnPositions.begin(), spawnPositions.end(), gen);
	std::shuffle(guessingSpawnPositions.begin(), guessingSpawnPositions.end(), gen);
	std::shuffle(fakeSpawnPositions.begin(), fakeSpawnPositions.end(), gen);
	std::shuffle(sideSpawnPositions.begin(), sideSpawnPositions.end(), gen);

	sideSearchedShapePosition = sideSpawnPositions[0];
	fakeShapePosition = fakeSpawnPositions[0];
	searchedShapePosition = guessingSpawnPositions[0];
	GameSpotTheSide::DeleteSearchedPosition(); //deleting searchedPosition from spawnPositions vector

	if (!onSide)
	{
		if (guessingSpawnPositions[0].x > creatorW / 2)
		{
			if (activeQuestion == "Normal")
			{
				correctAnswer = 1; // 1 = pravá, -1 = levá
			}
			else if (activeQuestion == "Negation")
			{
				correctAnswer = -1;
			}
			else if (activeQuestion == "MainObject")
			{
				correctAnswer = 1;
			}
		}
		else
		{
			if (activeQuestion == "Normal")
			{
				correctAnswer = -1;
			}
			else if (activeQuestion == "Negation")
			{
				correctAnswer = 1;
			}
			else if (activeQuestion == "MainObject")
			{
				correctAnswer = -1;
			}
		}
	}
	else
	{
		if (activeQuestion == "Normal")
		{
			correctAnswer = 1; // 1 = pravá, -1 = levá
		}
		else if (activeQuestion == "Negation")
		{
			correctAnswer = -1;
		}
	}

	iteratorNumOfShapes = numOfShapes;
	for (int i = 0; i < iteratorNumOfShapes; i++)
	{
		if (shapes[i] == "triangle")
		{
			if (i == 0)
			{
				if (!onSide)
				{
					GameSpotTheSide::GenerateTriangle(guessingSpawnPositions[0], false, 1);
				}
				else
				{
					if (sideSearchedShapePosition.x == firstSideObjectPosition)
					{
						GameSpotTheSide::GenerateTriangle(sideSpawnPositions[0], false, 2);
						bigFirstSide = true;
						correctAnswer = -1 * correctAnswer; //because body looks left on default
					}
					else
					{
						GameSpotTheSide::GenerateTriangle(sideSpawnPositions[0], false, 0);
						correctAnswer = 1 * correctAnswer;
					}
				}
				if (activeQuestion == "MainObject")
				{
					GameSpotTheSide::GenerateTriangle(fakeSpawnPositions[0], true, 1);
					secondTriangleDrawOn = true;
					if (i != iteratorNumOfShapes - 1)
					{
						iteratorNumOfShapes--;
					}
				}
			}
			else if (i == 1 && onSide)
			{

				if (bigFirstSide)
				{
					GameSpotTheSide::GenerateTriangle(sideSpawnPositions[1], false, 0);
				}
				else
				{
					GameSpotTheSide::GenerateTriangle(sideSpawnPositions[1], false, 2);
				}
				papaja++;
			}
			else
			{
				GameSpotTheSide::GenerateTriangle(finishedSpawnPositions[i], false, 1);
			}
			triangleCount++;
			triangleDrawOn = true;
		}
		else if (shapes[i] == "circle")
		{

			if (i == 0)
			{
				if (!onSide)
				{
					GameSpotTheSide::GenerateCircle(guessingSpawnPositions[0], false, 1);
				}
				else
				{
					if (sideSearchedShapePosition.x == firstSideObjectPosition)
					{
						GameSpotTheSide::GenerateCircle(sideSpawnPositions[0], false, 2); // This means shape will be bigger -> will be closer to us
						bigFirstSide = true;
						correctAnswer = -1 * correctAnswer; //because body looks left on default
					}
					else
					{
						GameSpotTheSide::GenerateCircle(sideSpawnPositions[0], false, 0);
						correctAnswer = 1 * correctAnswer;
					}
				}
				if (activeQuestion == "MainObject")
				{
					GameSpotTheSide::GenerateCircle(fakeSpawnPositions[0], true, 1);
					secondCircleDrawOn = true;
					if (i != iteratorNumOfShapes - 1)
					{
						iteratorNumOfShapes--;
					}
				}
			}
			else if (i == 1 && onSide)
			{


				if (bigFirstSide)
				{
					GameSpotTheSide::GenerateCircle(sideSpawnPositions[1], false, 0);
				}
				else
				{
					GameSpotTheSide::GenerateCircle(sideSpawnPositions[1], false, 2);
				}
				papaja++;
			}
			else
			{
				GameSpotTheSide::GenerateCircle(finishedSpawnPositions[i], false, 1);
			}
			circleCount++;
			circleDrawOn = true;
		}
		else if (shapes[i] == "square")
		{

			if (i == 0)
			{
				if (!onSide)
				{
					GameSpotTheSide::GenerateSquare(guessingSpawnPositions[0], false, 1);
				}
				else
				{
					if (sideSearchedShapePosition.x == firstSideObjectPosition)
					{
						GameSpotTheSide::GenerateSquare(sideSpawnPositions[0], false, 2);
						bigFirstSide = true;
						correctAnswer = -1 * correctAnswer; //because body looks left on default
					}
					else
					{
						GameSpotTheSide::GenerateSquare(sideSpawnPositions[0], false, 0);
						correctAnswer = 1 * correctAnswer;
					}

				}
				if (activeQuestion == "MainObject")
				{
					GameSpotTheSide::GenerateSquare(fakeSpawnPositions[0], true, 1);
					secondSquareDrawOn = true;
					if (i != iteratorNumOfShapes - 1)
					{
						iteratorNumOfShapes--;
					}
				}
			}
			else if (i == 1 && onSide)
			{

				if (bigFirstSide)
				{
					GameSpotTheSide::GenerateSquare(sideSpawnPositions[1], false, 0);
				}
				else
				{
					GameSpotTheSide::GenerateSquare(sideSpawnPositions[1], false, 2);
				}
			}
			else
			{
				GameSpotTheSide::GenerateSquare(finishedSpawnPositions[i], false, 1);
			}
			squareCount++;
			squareDrawOn = true;
		}

		else if (shapes[i] == "rectangle")
		{

			if (i == 0)
			{
				if (!onSide)
				{
					GameSpotTheSide::GenerateRectangle(guessingSpawnPositions[0], false, 1);
				}
				else
				{
					if (sideSearchedShapePosition.x == firstSideObjectPosition)
					{
						GameSpotTheSide::GenerateRectangle(sideSpawnPositions[0], false, 2);
						bigFirstSide = true;
						correctAnswer = -1 * correctAnswer; //because body looks left on default
					}
					else
					{
						GameSpotTheSide::GenerateRectangle(sideSpawnPositions[0], false, 0);
						correctAnswer = 1 * correctAnswer;
					}

				}
				if (activeQuestion == "MainObject")
				{
					GameSpotTheSide::GenerateRectangle(fakeSpawnPositions[0], true, 1);
					secondRectangleDrawOn = true;
					if (i != iteratorNumOfShapes - 1)
					{
						iteratorNumOfShapes--;
					}
				}
			}
			else if (i == 1 && onSide)
			{

				if (bigFirstSide)
				{
					GameSpotTheSide::GenerateRectangle(sideSpawnPositions[1], false, 0);
				}
				else
				{
					GameSpotTheSide::GenerateRectangle(sideSpawnPositions[1], false, 2);
				}
			}
			else
			{
				GameSpotTheSide::GenerateRectangle(finishedSpawnPositions[i], false, 1);
			}
			rectangleCount++;
			rectangleDrawOn = true;
		}
	}
	correctAnswer = correctAnswer * finalSide;

	firstTime = false;
}

void GameSpotTheSide::OptionBtnPressed(int btn)
{
	if (typeOfGame == "practice")
	{
		if (btn == 1) //left btn
		{
			if (!taskIntroActive && !roundOver && gameStarted)
			{
				optionBtn1Visible = false;
				optionBtn2Visible = false;
				optionBtn3Visible = true;
				roundOver = true;
				if (correctAnswer == -1)
				{
					answeredCorrectly = true;
				}
				else
				{
					answeredCorrectly = false;
				}
			}
		}
		else if (btn == 2) //right btn
		{
			if (!taskIntroActive && !roundOver && gameStarted)
			{
				optionBtn1Visible = false;
				optionBtn2Visible = false;
				optionBtn3Visible = true;
				roundOver = true;
				if (correctAnswer == 1)
				{
					answeredCorrectly = true;
				}
				else
				{
					answeredCorrectly = false;
				}
			}
		}
		else if (btn == 3)
		{
			circleDrawOn = false;
			triangleDrawOn = false;
			squareDrawOn = false;
			rectangleDrawOn = false;
			secondCircleDrawOn = false;
			secondTriangleDrawOn = false;
			secondSquareDrawOn = false;
			secondRectangleDrawOn = false;
			roundOver = false;
			optionBtn1Visible = true;
			optionBtn2Visible = true;
			optionBtn3Visible = false;
			rightSideAnswer = true;
			taskIntroActive = true;
			timestamp = std::chrono::steady_clock::now();
			GameSpotTheSide::ChangeVertices();
			GameSpotTheSide::HandleImageStaticShader();
			GameSpotTheSide::HandleNormalFlexibleShader();
		}
	}
	else if (typeOfGame == "test")
	{
		if (btn == 1)
		{
			leftSideAnswer = true;
		}
		else if (btn == 2)
		{
			rightSideAnswer = true;
		}
	}

}

void GameSpotTheSide::UpdateTime()
{

	timeNow = std::chrono::steady_clock::now();

	std::chrono::milliseconds elapsedTimeStamp;
	elapsedTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>((timeNow - timestamp));
	milisecsOfRoundGoing = static_cast<int>(elapsedTimeStamp.count());
	wxString str = wxString::Format("%d", milisecsOfRoundGoing);

	if (!gameStarted)
	{
		if (milisecsOfRoundGoing >= 3000)
		{
			gameStarted = true;
			timestamp = std::chrono::steady_clock::now();
			taskIntroActive = true;

		}
	}

	if (gameStarted)
	{
		if (milisecsOfRoundGoing > taskIntroTimeMilisecs && taskIntroActive)
		{
			taskIntroActive = false;
			timestamp = std::chrono::steady_clock::now();
		}

		else if (typeOfGame == "test")
		{
			if (milisecsOfRoundGoing > roundTimeMilisecs && !taskIntroActive)
			{
				timestamp = std::chrono::steady_clock::now();
				taskIntroActive = true;
			}
		}
	}
}

void GameSpotTheSide::HandleViewport(int nowW, int nowH, int creatorW, int creatorH, int startW, int startH)
{

	glViewport(0, 0, nowW, nowH);

}

void GameSpotTheSide::Draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	GameSpotTheSide::DrawGraphics();
	BaseGame::DrawCountDown();
	BaseGame::DrawAmountOfRounds();
	GameSpotTheSide::DrawText();
	BaseGame::DrawPause();

}

void GameSpotTheSide::Update()
{
	if (!gamePaused)
	{
		GameSpotTheSide::UpdateTime();
	}
}
