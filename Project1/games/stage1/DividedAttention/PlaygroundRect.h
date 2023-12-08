#pragma once

#include <wx/wx.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Ball.h"
#include "Rocket.h"
#define GLEW_STATIC
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vector2D {
	float x;
	float y;

	Vector2D(float x, float y) : x(x), y(y) {}
};

class PlaygroundRect
{
	float creatorW;
	float creatorH;
	int serieNumber;
	std::chrono::steady_clock::time_point timeCollide;
	int checkCollisionMilisecs = 2000;
	int milisecsOfCollision;
	int milisecsOfCollideAgain = 500;
	int milisecsToResetInputs = 2000;
	int milisecsOfLastInput;
	int milisecsOfMissedCollision = 3000;
	int milisecsOfTimeToResponse = 3000;
	bool colliding = false;

	int level;
	int ltX;
	int ltY;
	int width;
	int height;
	
	float ballRadius;
	float rocketLength;
	float rocketWidth;
	float rotationAngle = 0.0f;

	glm::vec2 vertex1; //LT
	glm::vec2 vertex2; //RT
	glm::vec2 vertex3; //RD
	glm::vec2 vertex4; //LD
	std::vector<glm::vec2> vertexes;
	float ballSpawnX;
	float ballSpawnY;
	float rocketSpawnX;
	float rocketSpawnY;
	Ball* ball;
	Rocket* rocket;
	std::vector<float> rocketPos;

	VertexArray* transRectVA;
	VertexBuffer* transRectVB;
	VertexBufferLayout* transRectVBL;
	IndexBuffer* transIB;
	bool collided;

	ShaderProgram* flexibleShaderProgram;
	int shaderProgramInit;

	std::vector<float> rectVertices;
	std::vector<float> ballPos;
	int count = 0;
	std::vector<float> axes;
	bool loaded = false;
	std::vector<float> jebak;
	std::vector<float> ballVertices;
	int collisionCount;
	std::vector<std::chrono::steady_clock::time_point> timeVec;
	std::chrono::steady_clock::time_point timeSinceInput;

	bool missedInput;
	bool correctInput;
	bool wrongInput;
	int milisecsOfDisplayingText = 2000;
	int milisecsOfKeyPressed;
	int countCorrectInput = 0;
	int countWrongInput = 0;
	int countMissedInput = 0;
	int countTotalCollisions;



public:
	PlaygroundRect(int ltX, int ltY, int w, int h, int level, ShaderProgram* flexibleProgram, int number, float creatorW, float creatorH);
	~PlaygroundRect();
	bool CircleCollision(std::vector<float> rectVertices, std::vector<float> ballVertices);
	std::array<bool, 3> GetInputValues();
	void ResetInputs();
	bool CheckInput();
	void Draw();
	void Update();
	void CheckCollision();
	void LoadAllGraphics();
	bool GetCollided();
	void SetCollidedBack(bool v);
	void SetTimeSinceInput();
	bool CheckMissedInput();
	void DrawText();
	bool GetMissedInput();
	void SetMissedInput(bool v);
	std::vector<float> GetRectangleAxes(std::vector<float> vertices);
	std::vector<float> GenerateBallPosition(float minX, float maxX, float minY, float maxY, float ballRadius) {};
	std::vector<float> GenerateRocketPosition(float minX, float maxX, float minY, float maxY, float rocketLength, float rocketWidth) {};


	


};