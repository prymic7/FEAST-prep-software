#include "Ball.h"


Ball::Ball(int level, int centerX, int centerY, ShaderProgram* flexibleProgram, std::vector<glm::vec2> vertexes, float radius)
	: level(level), ballX(centerX), ballY(centerY), flexibleShaderProgram(flexibleProgram), vertexes(vertexes), radius(radius)
{
	timeToGenerate = std::chrono::steady_clock::now();
	timeCollidedX = std::chrono::steady_clock::now();
	timeCollidedY = std::chrono::steady_clock::now();

	Ball::GenerateVertices(ballX, ballY, radius, 20);
	Ball::GenerateRandomVelocity();
}

Ball::~Ball()
{
	delete ballVA;
	delete ballVB;
	delete ballIB;
	delete ballVBL;
	delete flexibleShaderProgram; // bacha, nevymaze to cely shader, nebo jenom shader v teto classe?
}

void Ball::GenerateVertices(float centerX, float centerY, float radius, float numSegments)
{
	vertices.clear();

	for (int i = 0; i < numSegments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
		float x = radius * cos(theta) + centerX;
		float y = radius * sin(theta) + centerY;
		vertices.push_back(x);
		vertices.push_back(y);
	}
}

void Ball::LoadGraphics()
{
	ballVA = new VertexArray();
	ballVB = new VertexBuffer(vertices.size() * sizeof(std::vector<float>), vertices.data(), "dynamic");
	ballVBL = new VertexBufferLayout();
	ballVBL->Push<float>(2);
	ballVA->AddBuffer(ballVB, ballVBL);
}

void Ball::ChangeBallBuffer()
{
	ballVB->SubData(vertices.size() * sizeof(std::vector<float>), vertices.data());
}

void Ball::MoveBall()
{
	std::chrono::milliseconds elapsedTimeToGenerate;

	elapsedTimeToGenerate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timeToGenerate);
	milisecsOfGenerate = static_cast<int>(elapsedTimeToGenerate.count());

	if (milisecsOfGenerate > generateNewVelocityMilisecs && milisecsOfCollideX > nextCollisionTime && milisecsOfCollideY > nextCollisionTime)
	{
		timeToGenerate = std::chrono::steady_clock::now();
		Ball::GenerateRandomVelocity();
	}

	ballX += velocityX;
	ballY += velocityY;


}

void Ball::HandleSteering()
{

	if (velocityX > wantedVelocityX)
	{
		velocityX -= steerVelocity;
	}
	else if (velocityX < wantedVelocityX)
	{
		velocityX += steerVelocity;
	}

			
	if (velocityY > wantedVelocityY)
	{
		velocityY -= steerVelocity;
	}
	else if (velocityY < wantedVelocityY)
	{
		velocityY += steerVelocity;
	}


	if (velocityX == wantedVelocityX)
	{
		xSteeringFinished = true;
	}
	if (velocityY == wantedVelocityY)
	{
		ySteeringFinished = true;
	}

	if (xSteeringFinished && ySteeringFinished)
	{
		timeToGenerate = std::chrono::steady_clock::now();
		xSteeringFinished = false;
		ySteeringFinished = false;
	}

}
void Ball::GenerateRandomVelocity()
{
	float randomX = 0.0f;
	float randomY = 0.0f;
	float randomSteerVel = 0.0f;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> generatedX(-highestBallSpeed, highestBallSpeed);
	std::uniform_real_distribution<float> generatedY(-highestBallSpeed, highestBallSpeed);
	std::uniform_real_distribution<float> generatedSteerVel(lowestSteerSpeed, highestSteerSpeed);

	steerVelocity = generatedSteerVel(gen);

	do
	{
		randomX = generatedX(gen);

	} while (randomX > -lowestBallSpeed && randomX < lowestBallSpeed);

	do
	{
		randomY = generatedY(gen);

	} while (randomY > -lowestBallSpeed && randomY < lowestBallSpeed);

	wantedVelocityX = randomX;
	wantedVelocityY = randomY;

}

void Ball::CheckBorderCollision()
{
	std::chrono::milliseconds elapsedTimeToCollideX;
	std::chrono::milliseconds elapsedTimeToCollideY;

	elapsedTimeToCollideX = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timeCollidedX);
	milisecsOfCollideX = static_cast<int>(elapsedTimeToCollideX.count());

	elapsedTimeToCollideY = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timeCollidedY);
	milisecsOfCollideY = static_cast<int>(elapsedTimeToCollideY.count());

	if (milisecsOfCollideX > nextCollisionTime)
	{
		if (ballX - radius <= vertexes[0].x || ballX + radius >= vertexes[1].x)
		{
			velocityX = -velocityX;
			timeCollidedX = std::chrono::steady_clock::now();

		}
	}

	if (milisecsOfCollideY > nextCollisionTime)
	{
		if (ballY - radius <= vertexes[0].y || ballY + radius >= vertexes[2].y)
		{
			velocityY = -velocityY;
			timeCollidedY = std::chrono::steady_clock::now();

		}
	}


}

void Ball::Draw()
{

	GLCall(flexibleShaderProgram->Bind());
	GLCall(flexibleShaderProgram->SetUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f));
	GLCall(ballVA->Bind());
	GLCall(glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size()/2))
}



void Ball::Update()
{
	Ball::MoveBall();
	Ball::HandleSteering();
	Ball::GenerateVertices(ballX, ballY, radius, 20);
	Ball::ChangeBallBuffer();
	Ball::CheckBorderCollision();
}


float Ball::GetRadius()
{
	return radius;
}

std::vector<float> Ball::GetPosition()
{
	std::vector<float> pos;

	pos.push_back(ballX);
	pos.push_back(ballY);

	return pos;
}

std::vector<float> Ball::GetVertices() 
{
	return vertices;
}
