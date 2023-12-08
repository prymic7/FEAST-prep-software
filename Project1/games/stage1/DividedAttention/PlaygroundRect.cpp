#pragma once
#include "PlaygroundRect.h"
#include "Rocket.h"
#include "Ball.h"
#include <wx/wx.h>
#include <cstdlib>
#include <ctime>
#include <vector>

PlaygroundRect::PlaygroundRect(int ltX, int ltY, int w, int h, int level, ShaderProgram* flexibleShaderProgram, int number, float creatorW, float creatorH) : ltX(ltX), ltY(ltY), width(w), height(h), level(level),
 flexibleShaderProgram(flexibleShaderProgram), serieNumber(number), creatorW(creatorW), creatorH(creatorH)
{
	timeSinceInput = std::chrono::steady_clock::now();
	//timeCollide = std::chrono::steady_clock::now();

	vertex1.x = ltX;
	vertex1.y = ltY;

	vertex2.x = ltX + w;
	vertex2.y = ltY;

	vertex3.x = ltX + w;
	vertex3.y = ltY + h;

	vertex4.x = ltX;
	vertex4.y = ltY + h;

	vertexes.push_back(vertex1); // border vertecies
	vertexes.push_back(vertex2);
	vertexes.push_back(vertex3);
	vertexes.push_back(vertex4);

	ballSpawnX = ltX + w / 2;
	ballSpawnY = ltY + h / 2;

	rocketSpawnX = ltX + w / 1.5;
	rocketSpawnY = ltY + h / 2;


	float size = w * h;

	rocketLength = h * 0.5;
	rocketWidth = w * 0.008;
	ballRadius = w * 0.02;

	if (level == 1)
	{
		//rocketLength = 200.0f;
		//rocketWidth = 13.0f;
		//ballRadius = 15.0f;

	}
	if (level == 2)
	{
		ballRadius = 8.0f;
	}
	if (level == 3)
	{
		ballRadius == 6.0f;
	}

	ball = new Ball(level, ballSpawnX, ballSpawnY, flexibleShaderProgram, vertexes, ballRadius);
	rocket = new Rocket(level, rocketSpawnX, rocketSpawnY, flexibleShaderProgram, vertexes, rocketLength, rocketWidth, rotationAngle);
	axes.push_back(200.0f);
	axes.push_back(200.0f);
	axes.push_back(300.0f);
	axes.push_back(200.0f);
	axes.push_back(250.0f);
	axes.push_back(500.0f);

	jebak.push_back(200.0f);
	jebak.push_back(200.0f);
	jebak.push_back(300.0f);
	jebak.push_back(200.0f);
	jebak.push_back(250.0f);
	jebak.push_back(500.0f);

}

PlaygroundRect::~PlaygroundRect()
{
	delete ball;
	delete rocket;
}

void PlaygroundRect::LoadAllGraphics()
{
	ball->LoadGraphics();
	rocket->LoadGraphics();
}

void PlaygroundRect::CheckCollision()
{
	int size = timeVec.size();
	wxString str = wxString::Format("%d", size);
	wxLogStatus(str);
	std::chrono::milliseconds elapsedTimeToCollision;
	elapsedTimeToCollision = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timeCollide);
	milisecsOfCollision = static_cast<int>(elapsedTimeToCollision.count());


	if (milisecsOfCollision > milisecsOfCollideAgain)
	{
		ballVertices = ball->GetVertices();
		rectVertices = rocket->GetVertices();
		collided = PlaygroundRect::CircleCollision(rectVertices, ballVertices);
	}
}

bool PlaygroundRect::CheckMissedInput()
{

	if (timeVec.size() > 0)
	{
		std::chrono::milliseconds elapsedTimeToCollide;
		elapsedTimeToCollide = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timeVec[0]);
		milisecsOfCollision = static_cast<int>(elapsedTimeToCollide.count());

		if (milisecsOfCollision > milisecsOfTimeToResponse)
		{
			timeVec.erase(timeVec.begin());
			missedInput = true;
			timeSinceInput = std::chrono::steady_clock::now();
			return true;
		}
	}
	return false;
}

void PlaygroundRect::ResetInputs()
{
	std::chrono::milliseconds elapsedTimeToReset;
	elapsedTimeToReset = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timeSinceInput);
	milisecsOfLastInput = static_cast<int>(elapsedTimeToReset.count());

	if (milisecsOfLastInput > milisecsToResetInputs)
	{
		missedInput = false;
		correctInput = false;
		wrongInput = false;
	}
}

bool PlaygroundRect::GetMissedInput()
{
	return missedInput;
}

void PlaygroundRect::SetMissedInput(bool v)
{
	missedInput = v;
}

bool PlaygroundRect::CheckInput()
{
	if (timeVec.size() == 0)
	{
		return false;
	}
	else
	{
		timeVec.erase(timeVec.begin());
		return true;
	}
	return false;
}

std::array<bool, 3> PlaygroundRect::GetInputValues()
{
	std::array<bool, 3> result = { missedInput, correctInput, wrongInput };
	return result;
}

bool PlaygroundRect::CircleCollision(std::vector<float> rectVertices, std::vector<float> ballVertices) 
{

	for (int i = 0; i < rectVertices.size(); i += 2)
	{
		float x1 = rectVertices[i];
		float y1 = rectVertices[i + 1];
		float x2 = rectVertices[(i + 2) % rectVertices.size()];
		float y2 = rectVertices[(i + 3) % rectVertices.size()];
		float edgeX = x2 - x1;
		float edgeY = y2 - y1;

		float axisX = -edgeY;
		float axisY = edgeX;

		float min_r1 = INFINITY, max_r1 = -INFINITY;
		for (int j = 0; j < rectVertices.size(); j+=2)
		{
			float q = (rectVertices[j] * axisX + rectVertices[j+1] * axisY);
			min_r1 = std::min(min_r1, q);
			max_r1 = std::max(max_r1, q);
		}
		float min_r2 = INFINITY, max_r2 = -INFINITY;
		for (int j = 0; j < ballVertices.size(); j += 2)
		{
			float q = (ballVertices[j] * axisX + ballVertices[j + 1] * axisY);
			min_r2 = std::min(min_r2, q);
			max_r2 = std::max(max_r2, q);
		}
		if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
		{
			return false;
		}


	}

	for (int i = 0; i < ballVertices.size(); i += 2)
	{
		float x1 = ballVertices[i];
		float y1 = ballVertices[i + 1];
		float x2 = ballVertices[(i + 2) % ballVertices.size()];
		float y2 = ballVertices[(i + 3) % ballVertices.size()];
		float edgeX = x2 - x1;
		float edgeY = y2 - y1;

		float axisX = -edgeY;
		float axisY = edgeX;

		float min_r1 = INFINITY, max_r1 = -INFINITY;
		for (int j = 0; j < rectVertices.size(); j += 2)
		{
			float q = (rectVertices[j] * axisX + rectVertices[j + 1] * axisY);
			min_r1 = std::min(min_r1, q);
			max_r1 = std::max(max_r1, q);
		}
		float min_r2 = INFINITY, max_r2 = -INFINITY;
		for (int j = 0; j < ballVertices.size(); j += 2)
		{
			float q = (ballVertices[j] * axisX + ballVertices[j + 1] * axisY);
			min_r2 = std::min(min_r2, q);
			max_r2 = std::max(max_r2, q);
		}
		if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
		{
			return false;
		}
	}

	std::chrono::steady_clock::time_point time_point = std::chrono::steady_clock::now();
	timeCollide = std::chrono::steady_clock::now();
	timeVec.push_back(time_point);
	countTotalCollisions++;
	return true;
}



void PlaygroundRect::DrawText()
{

}

void PlaygroundRect::SetCollidedBack(bool v)
{
	collided = v;
}

void PlaygroundRect::SetTimeSinceInput()
{
	timeSinceInput = std::chrono::steady_clock::now();
}

bool PlaygroundRect::GetCollided()
{
	return collided;
}

void PlaygroundRect::Draw()
{
	ball->Draw();
	rocket->Draw();
}

void PlaygroundRect::Update()
{

	ball->Update();
	rocket->Update();
	PlaygroundRect::CheckCollision();
	PlaygroundRect::ResetInputs();

}



