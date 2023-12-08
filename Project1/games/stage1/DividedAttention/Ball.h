#pragma once

#include "../../BaseGame.h" 
#include <wx/wx.h>
#include <chrono>
#include <random>
#include <array>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Ball
{
	std::chrono::steady_clock::time_point timeToGenerate;
	std::chrono::steady_clock::time_point timeCollidedX;
	std::chrono::steady_clock::time_point timeCollidedY;

	int level;
	float radius;
	float ballX;
	float ballY;

	VertexArray* ballVA;
	VertexBuffer* ballVB;
	VertexBufferLayout* ballVBL;
	IndexBuffer* ballIB;
	ShaderProgram* flexibleShaderProgram;
	std::vector<glm::vec2> vertexes;
	std::vector<float> vertices;
	int shaderProgramInit;
	float velocityX;
	float velocityY;
	float wantedVelocityX;
	float wantedVelocityY;
	float steerVelocity = 0.01;
	const float toleration = 0.1;
	const float highestBallSpeed = 20.0;
	const float lowestBallSpeed = 18.5;
	const float lowestSteerSpeed = 0.01;
	const float highestSteerSpeed = 0.1;
	float rotationAngle = 0.0f;

	bool xSteeringFinished;
	bool ySteeringFinished;
	bool firstTime = true;
	bool generatedVelocity = false;

	float milisecsOfGenerate;

	float milisecsOfCollideX;
	float milisecsOfCollideY;
	int nextCollisionTime = 200;
	int generateNewVelocityMilisecs = 4000;
	int count = 0;

public:
	Ball(int level, int centerX, int centerY, ShaderProgram* flexibleProgram, std::vector<glm::vec2> vertexes, float radius);
	~Ball();

	void Draw();
	void Update();
	void LoadGraphics();
	void GenerateVertices(float centerX, float centerY, float radius, float numSegments);
	void MoveBall();
	void GenerateRandomVelocity();
	void ChangeBallBuffer();
	void CheckBorderCollision();
	void HandleSteering();
	float GetRadius();
	std::vector<float> GetPosition();
	std::vector<float> GetVertices();

};

