#include "Rocket.h"


Rocket::Rocket(int level, int centerX, int centerY, ShaderProgram* flexibleProgram, std::vector<glm::vec2> vertexes, float rocketLength, float rocketWidth, float rotationAngle) : level(level), 
rocketX(centerX), rocketY(centerY), flexibleShaderProgram(flexibleProgram), vertexes(vertexes), rocketLength(rocketLength), rocketWidth(rocketWidth) , rotationAngle(rotationAngle)
{
	timeToGenerate = std::chrono::steady_clock::now();
	timeCollidedX = std::chrono::steady_clock::now();
	timeCollidedY = std::chrono::steady_clock::now();



	Rocket::GenerateRandomRotation();
	Rocket::GenerateRandomVelocity();
	Rocket::GenerateVertices();
}

Rocket::~Rocket()
{
	delete rocketVA;
	delete rocketVB;
	delete rocketIB;
	delete rocketVBL;
	delete flexibleShaderProgram;
}

void Rocket::LoadGraphics()
{
	rocketIB = new IndexBuffer(6, indices);
	rocketVA = new VertexArray();
	rocketVB = new VertexBuffer(vertices.size() * sizeof(std::vector<float>), vertices.data(), "dynamic");
	rocketVBL = new VertexBufferLayout();
	rocketVBL->Push<float>(2);
	rocketVA->AddBuffer(rocketVB, rocketVBL);
}

void Rocket::GenerateVertices()
{
	vertices.clear();

	float rotationRadians = glm::radians(rotationAngle);

	float cosTheta = cos(rotationRadians);
	float sinTheta = sin(rotationRadians);

	float x1 = rocketX - rocketWidth / 2;
	float y1 = rocketY - rocketLength / 2;
	rotatedX1 = rocketX + (x1 - rocketX) * cosTheta - (y1 - rocketY) * sinTheta;
	rotatedY1 = rocketY + (x1 - rocketX) * sinTheta + (y1 - rocketY) * cosTheta;
	vertices.push_back(rotatedX1);
	vertices.push_back(rotatedY1);

	float x2 = rocketX + rocketWidth / 2;
	float y2 = rocketY - rocketLength / 2;
	rotatedX2 = rocketX + (x2 - rocketX) * cosTheta - (y2 - rocketY) * sinTheta;
	rotatedY2 = rocketY + (x2 - rocketX) * sinTheta + (y2 - rocketY) * cosTheta;
	vertices.push_back(rotatedX2);
	vertices.push_back(rotatedY2);

	float x3 = rocketX + rocketWidth / 2;
	float y3 = rocketY + rocketLength / 2;
	rotatedX3 = rocketX + (x3 - rocketX) * cosTheta - (y3 - rocketY) * sinTheta;
	rotatedY3 = rocketY + (x3 - rocketX) * sinTheta + (y3 - rocketY) * cosTheta;
	vertices.push_back(rotatedX3);
	vertices.push_back(rotatedY3);

	float x4 = rocketX - rocketWidth / 2;
	float y4 = rocketY + rocketLength / 2;
	rotatedX4 = rocketX + (x4 - rocketX) * cosTheta - (y4 - rocketY) * sinTheta;
	rotatedY4 = rocketY + (x4 - rocketX) * sinTheta + (y4 - rocketY) * cosTheta;
	vertices.push_back(rotatedX4);
	vertices.push_back(rotatedY4);

}

void Rocket::UpdateRotation()
{
	if (std::abs(rotationAngle - wantedRotationAngle) > toleration)
	{
		if(rotationAngle > wantedRotationAngle)
		{
			rotationAngle -= rotationVelocity;
		}
		else if (rotationAngle < wantedRotationAngle)
		{
		rotationAngle += rotationVelocity;
		}
	}

}

void Rocket::GenerateRandomRotation()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> generatedRotation(lowestRotation, highestRotation);
	wantedRotationAngle = generatedRotation(gen);

	std::uniform_real_distribution<float> generatedRotationSteerVel(lowestRotationSpeed, highestRotationSpeed);
	rotationVelocity = generatedRotationSteerVel(gen);
}

void Rocket::MoveRocket()
{
	std::chrono::milliseconds elapsedTimeToGenerate;

	elapsedTimeToGenerate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timeToGenerate);
	milisecsOfGenerate = static_cast<int>(elapsedTimeToGenerate.count());

	if (milisecsOfGenerate > generateNewVelocityMilisecs && milisecsOfCollideX > nextCollisionTime && milisecsOfCollideY > nextCollisionTime)
	{
		timeToGenerate = std::chrono::steady_clock::now();
		Rocket::GenerateRandomVelocity();
		Rocket::GenerateRandomRotation();

	}

	rocketX += velocityX;
	rocketY += velocityY;

}

void Rocket::GenerateRandomVelocity()
{
	float randomX = 0.0f;
	float randomY = 0.0f;
	float randomSteerVel = 0.0f;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> generatedX(-highestRocketSpeed, highestRocketSpeed);
	std::uniform_real_distribution<float> generatedY(-highestRocketSpeed, highestRocketSpeed);
	std::uniform_real_distribution<float> generatedSteerVel(lowestSteerSpeed, highestSteerSpeed);

	steerVelocity = generatedSteerVel(gen);

	do
	{
		randomX = generatedX(gen);

	} while (randomX > -lowestRocketSpeed && randomX < lowestRocketSpeed);

	do
	{
		randomY = generatedY(gen);

	} while (randomY > -lowestRocketSpeed && randomY < lowestRocketSpeed);

	wantedVelocityX = randomX;
	wantedVelocityY = randomY;
}

void Rocket::ChangeRocketBuffer()
{
	rocketVB->SubData(vertices.size() * sizeof(std::vector<float>), vertices.data());
}

void Rocket::CheckBorderCollision()
{
	std::chrono::milliseconds elapsedTimeToCollideX;
	std::chrono::milliseconds elapsedTimeToCollideY;


	elapsedTimeToCollideX = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timeCollidedX);
	milisecsOfCollideX = static_cast<int>(elapsedTimeToCollideX.count());

	elapsedTimeToCollideY = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timeCollidedY);
	milisecsOfCollideY = static_cast<int>(elapsedTimeToCollideY.count());

	if (milisecsOfCollideX > nextCollisionTime)
	{
		if (rotatedX1 >= vertexes[1].x || rotatedX2 >= vertexes[1].x || rotatedX3 >= vertexes[1].x || rotatedX4 >= vertexes[1].x)
		{
			velocityX = -velocityX;
			timeCollidedX = std::chrono::steady_clock::now();


		}
		if (rotatedX1 <= vertexes[0].x || rotatedX2 <= vertexes[0].x || rotatedX3 <= vertexes[0].x || rotatedX4 <= vertexes[0].x)
		{
			velocityX = -velocityX;
			timeCollidedX = std::chrono::steady_clock::now();
		}
	}
	if (milisecsOfCollideY > nextCollisionTime)
	{
		if (rotatedY1 <= vertexes[1].y || rotatedY2 <= vertexes[1].y || rotatedY3 <= vertexes[1].y || rotatedY4 <= vertexes[1].y)
		{
			velocityY = -velocityY;
			timeCollidedY = std::chrono::steady_clock::now();


		}
		if (rotatedY1 >= vertexes[2].y || rotatedY2 >= vertexes[2].y || rotatedY3 >= vertexes[2].y || rotatedY4 >= vertexes[2].y)
		{
			velocityY = -velocityY;
			timeCollidedY = std::chrono::steady_clock::now();

		}
	}
}

void Rocket::HandleSteering()
{

	if (rocketX > wantedRocketX)
	{
		velocityX -= steerVelocity;
	}
	else if (rocketX < wantedRocketX)
	{
		velocityX += steerVelocity;
	}


	if (rocketY > wantedRocketY)
	{
		velocityY -= steerVelocity;
	}
	else if (rocketY < wantedRocketY)
	{
		velocityY += steerVelocity;
	}
}

void Rocket::Draw()
{
	GLCall(flexibleShaderProgram->Bind());
	GLCall(flexibleShaderProgram->SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f));
	GLCall(rocketVA->Bind());
	GLCall(rocketIB->Bind());
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr))
}

void Rocket::Update()
{
	Rocket::UpdateRotation();
	Rocket::MoveRocket();
	Rocket::HandleSteering();
	Rocket::GenerateVertices();
	Rocket::ChangeRocketBuffer();
	Rocket::CheckBorderCollision();
}



std::vector<float> Rocket::GetVertices()
{
	return vertices;
}
