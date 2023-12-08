#pragma once
#include "../../BaseGame.h"
#include <wx/wx.h>
#include <chrono>
#include <random>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameMemorizePictograms : public BaseGame
{

	bool mathOn = false;
	bool memorizing = true;
	bool guessing = false;
	bool doublePictograms = true;
	int numOfPictogramsToMemorize;
	int timeToMemorize;
	int numOfMath;
	std::string pictogramsTypes[19] = { "speedometer", "snowflake", "maze", "eyes", "puzzles", "thumbs", "emonecklase", "compas", "illuminati", "crusader", "raindrop", "babydraw", "drawapp", "star", "roadsign", "pie", "zebra", "weather", "arrows"};
	std::string speedometersIMGS[9] = {};


public:
	GameMemorizePictograms(int level, std::string typeOfGame, int startW, int startH, int creatorW, int creatorH, std::string typeOfTimer);
	~GameMemorizePictograms();

	void Draw() override;
	void Update() override;
	void DrawText() override;
	void LeftClickBtn(float xPos, float yPos) override;
	void LoadAllGraphics() override;
	void UpdateTime() override;
	void PickImages();
};

