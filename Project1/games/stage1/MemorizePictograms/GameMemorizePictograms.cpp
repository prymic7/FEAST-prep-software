#include "GameMemorizePictograms.h"


GameMemorizePictograms::GameMemorizePictograms(int level, std::string typeOfGame, int startW, int startH, int creatorW, int creatorH, std::string typeOfTimer)
	: BaseGame(level, typeOfGame, startW, startH, creatorW, creatorH, typeOfTimer)
{
	justRun = true;
	this->creatorW = creatorW;
	this->creatorH = creatorH;
	this->level = level;
	this->typeOfGame = typeOfGame;
	timer = true;
	taskIntroTimeMilisecs = 5000;
	if (typeOfGame == "practice")
	{
		if (level == 1)
		{
			numOfPictogramsToMemorize = 8; //checked
		}
		else if (level == 2)
		{
			numOfPictogramsToMemorize = 6;
		}
		else if (level == 3)
		{
			numOfPictogramsToMemorize = 12;
			numOfMath = 15;
			timeToMemorize = 15000;
		}
	}
	else if (typeOfGame == "test")
	{

	}
}

GameMemorizePictograms::~GameMemorizePictograms()
{
}

void GameMemorizePictograms::PickImages()
{

}

void GameMemorizePictograms::DrawText()
{
	if (memorizing)
	{
		BaseGame::CreateTextToRect("Memorize these pictograms:", 0.6f, 0.0f, 0.0f, creatorW, creatorH, blackColor[0], blackColor[1], blackColor[2], 1);
	}
	if (mathOn)
	{
		BaseGame::CreateTextToRect("Solve these math problems:", 0.6f, 0.0f, 0.0f, creatorW, creatorH, blackColor[0], blackColor[1], blackColor[2], 1);
	}
	if (guessing)
	{
		BaseGame::CreateTextToRect("Which pictogram/s do you remember?", 0.6f, 0.0f, 0.0f, creatorW, creatorH, blackColor[0], blackColor[1], blackColor[2], 1);
	}
}

void GameMemorizePictograms::LeftClickBtn(float xPos, float yPos)
{
}

void GameMemorizePictograms::LoadAllGraphics()
{
	BaseGame::LoadAllGraphics();
}

void GameMemorizePictograms::UpdateTime()
{

	timeNow = std::chrono::steady_clock::now();

	std::chrono::milliseconds elapsedTimeStamp;
	elapsedTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>((timeNow - timestamp));
	milisecsOfRoundGoing = static_cast<int>(elapsedTimeStamp.count());

	if (!gameStarted)
	{
		if (milisecsOfRoundGoing >= 3000)
		{
			gameStarted = true;
			memorizing = true;
			timestamp = std::chrono::steady_clock::now();

		}
	}

	if (gameStarted)
	{
		if (milisecsOfRoundGoing > timeToMemorize && memorizing)
		{
			memorizing = false;
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

void GameMemorizePictograms::Draw()
{
	glClearColor(greenColor2[0], greenColor2[1], greenColor2[2], greenColor2[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	BaseGame::DrawCountDown();
	BaseGame::DrawAmountOfRounds();
	BaseGame::DrawPause();
}

void GameMemorizePictograms::Update()
{
	GameMemorizePictograms::UpdateTime();
}
