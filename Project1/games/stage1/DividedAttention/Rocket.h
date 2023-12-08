#pragma once
#include <vector>
#include "../../BaseGame.h" 
#include <wx/wx.h>
#include <chrono>
#include <random>
#include <array>
#include <glew.h>

class Rocket
{

	int level;
	float rocketX;
	float rocketY;
	float rocketLength;
	float rocketWidth;

	std::chrono::steady_clock::time_point timeToGenerate;
	std::chrono::steady_clock::time_point timeCollidedX;
	std::chrono::steady_clock::time_point timeCollidedY;


	ShaderProgram* flexibleShaderProgram;
	VertexArray* rocketVA;
	VertexBuffer* rocketVB;
	VertexBufferLayout* rocketVBL;
	IndexBuffer* rocketIB;
	std::vector<glm::vec2> vertexes;
	std::vector<float> vertices;

	float rotatedX1;
	float rotatedY1;
	float rotatedX2;
	float rotatedY2;
	float rotatedX3;
	float rotatedY3;
	float rotatedX4;
	float rotatedY4;
	float velocityX;
	float velocityY;
	const float lowestSteerSpeed = 0.01;
	const float highestSteerSpeed = 0.2;
	const float highestRocketSpeed = 1.0;
	const float lowestRocketSpeed = 0.5;
	float wantedVelocityX;
	float wantedVelocityY;
	float steerVelocity = 0.01;
	float wantedRocketX;
	float wantedRocketY;
	float rotationAngle = 0.0;
	float wantedRotationAngle;
	const float highestRotation = 90.0;
	const float lowestRotation = -90.0;
	float rotationVelocity = 0.2;
	const float lowestRotationSpeed = 0.1;
	const float highestRotationSpeed = 1.0;
	const float toleration = 1.5;
	bool xSteeringFinished;
	bool ySteeringFinished;
	bool firstTime = true;
	bool generatedVelocity = false;
	float milisecsOfGenerate;
	float milisecsOfCollideX;
	float milisecsOfCollideY;
	int nextCollisionTime = 700;
	int generateNewVelocityMilisecs = 4000;
	int count = 0;

	GLushort indices[6] =
	{
		0, 1, 2,
		0, 2, 3
	};
public:
	Rocket(int level, int centerX, int centerY, ShaderProgram* flexibleProgram, std::vector<glm::vec2> vertexes, float rocketLength, float rocketWidth, float rotationAngle);
	~Rocket();

	void Draw();
	void Update();
	void LoadGraphics();
	void GenerateVertices();
	void MoveRocket();
	void GenerateRandomVelocity();
	void ChangeRocketBuffer();
	void CheckBorderCollision();
	void UpdateRotation();
	void HandleSteering();
	void GenerateRandomRotation();
	float GetRotationAngle();
	std::vector<float> GetVertices();

};

