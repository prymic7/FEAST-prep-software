#pragma once
#include "GameHeadingConflicts.h"
#include <chrono>
#include <wx/wx.h>
#include <random>
#include <array>


//dodelat statistiky(body za dobrou ci spatnou odpoved)
//Zmenit conflict a continue btn na btns wxwidgets
GameHeadingConflicts::GameHeadingConflicts(int level, std::string typeOfGame, int startW, int startH, int creatorW, int creatorH, std::string typeOfTimer)
    : BaseGame(level, typeOfGame, startW, startH, creatorW, creatorH, typeOfTimer)
{

    justRun = false;
    this->creatorW = creatorW;
    this->creatorH = creatorH;
    this->level = level;
    this->typeOfGame = typeOfGame;
    currentRound = 0;

    lineLength = 23.0f;
    baseLength = 21.0f;
    optionBtn1Visible = true;
    if (typeOfGame == "practice")
    {
        if (level == 1)
        {
            trianglesCount = 12;
            roundTimeMilisecs = 15000;
            targetRounds = 10;
            taskIntroTimeMilisecs = 8000;
        }
        else if (level == 2)
        {
            trianglesCount = 16;
            roundTimeMilisecs = 12000;
            targetRounds = 20;
            taskIntroTimeMilisecs = 6000;
        }
        else if (level == 3)
        {
            trianglesCount = 20;
            roundTimeMilisecs = 10000;
            targetRounds = 30;
            taskIntroTimeMilisecs = 5000;
        }
    }
    else if (typeOfGame == "test")
    {
        trianglesCount = 25;
        roundTimeMilisecs = 10000;
        taskIntroTimeMilisecs = 5000;
    }

    GameHeadingConflicts::DecideConflictOn();
    GameHeadingConflicts::GenerateCollidingTrianglesPositions();
    GameHeadingConflicts::GenerateTrianglesPositions(trianglesCount);

}

GameHeadingConflicts::~GameHeadingConflicts()
{
}

void GameHeadingConflicts::GenerateTrianglesPositions(int count)
{
    float randomX;
    float randomY;
    float randomGap;
    float angle;
    std::uniform_real_distribution<float> generatedX((generateDistanceFromBorder/2), creatorW - (generateDistanceFromBorder/2));
    std::uniform_real_distribution<float> generatedY(generateDistanceFromBorder, creatorH - generateDistanceFromBorder);

    for (int i = 0; i < count; i++)
    {
        bool distanceOK = true;
        int count = 0;
        do
        {
            count++;
            randomX = generatedX(gen);
            randomY = generatedY(gen);
            float distance;
            if (count < 500)
            {
                for (int i = 0; i < storedPositions.size(); i++)
                {
                    float x = storedPositions[i].x;
                    float y = storedPositions[i].y;

                    distance = glm::sqrt((glm::pow(randomX - x, 2.0f)) + glm::pow(randomY - y, 2.0f));
                    if (distance < 45)
                    {
                        distanceOK = false;
                        break;
                    }
                }
            }
            else
            {
                distanceOK = true;
            }

        } while (!distanceOK);

        std::shuffle(triangleAngles.begin(), triangleAngles.end(), gen);
        angle = triangleAngles[0];
        float radians = glm::radians(angle);

        float armAngleFromMiddle = 45.0f;
        float armAngleFromMiddleRad = glm::radians(armAngleFromMiddle);


        float upX1 = randomX;
        float upY1 = randomY - lineLength;
        float leftX1 = randomX + baseLength * cos(armAngleFromMiddleRad);
        float leftY1 = randomY + baseLength * sin(armAngleFromMiddleRad);
        float rightX1 = randomX - baseLength * cos(-armAngleFromMiddleRad);
        float rightY1 = randomY - baseLength * sin(-armAngleFromMiddleRad);

        float rotatedX1 = randomX + (upX1 - randomX) * cos(angle) - (upY1 - randomY) * sin(angle);
        float rotatedY1 = randomY + (upX1 - randomX) * sin(angle) + (upY1 - randomY) * cos(angle);
        float rotatedX2 = randomX + (leftX1 - randomX) * cos(angle) - (leftY1 - randomY) * sin(angle);
        float rotatedY2 = randomY + (leftX1 - randomX) * sin(angle) + (leftY1 - randomY) * cos(angle);
        float rotatedX3 = randomX + (rightX1 - randomX) * cos(angle) - (rightY1 - randomY) * sin(angle);
        float rotatedY3 = randomY + (rightX1 - randomX) * sin(angle) + (rightY1 - randomY) * cos(angle);

        glm::vec2 vertex1(rotatedX1, rotatedY1);
        glm::vec2 vertex2(rotatedX2, rotatedY2);
        glm::vec2 vertex3(rotatedX3, rotatedY3);

        storedPositions.push_back(glm::vec2(randomX, randomY));

        trianglePositions.push_back(vertex1);
        trianglePositions.push_back(vertex2);
        trianglePositions.push_back(vertex3);
    }
}

void GameHeadingConflicts::GenerateCollidingTrianglesPositions()
{
    int numOfPossibleCollidingTriangles = 2;

    float randomX;
    float randomY;
    float randomGap;
    std::shuffle(directionHolder, directionHolder + 2, gen);
    typeOfConflict = directionHolder[0];
    std::uniform_real_distribution<float> generatedX((generateDistanceFromBorder / 2), creatorW - (generateDistanceFromBorder / 2));
    std::uniform_real_distribution<float> generatedY(generateDistanceFromBorder, creatorH - generateDistanceFromBorder);

    for (int i = 0; i < numOfPossibleCollidingTriangles; i++)
    {
        float angle = 0.0f;
        float radians = 0.0f;
        if (conflictTurnedOn)
        {
            if (typeOfConflict == "vertical")
            {
                if (i == 0)
                {
                    std::uniform_int_distribution<int> generatedX(generateDistanceFromBorder, creatorW - generateDistanceFromBorder);
                    std::uniform_int_distribution<int> generatedY(300, creatorH - generateDistanceFromBorder);
                    randomX = generatedX(gen);
                    randomY = generatedY(gen);
                    angle = 360.0f;
                }
                else
                {
                    std::uniform_int_distribution<int> generatedGap(generateDistanceFromBorder, 300);
                    randomGap = generatedGap(gen);
                    randomY -= randomGap;
                    angle = 180.0f;
                }
            }
            else if (typeOfConflict == "horizontal")
            {

                if (i == 0)
                {
                    std::uniform_int_distribution<int> generatedX(500, creatorW - generateDistanceFromBorder);
                    std::uniform_int_distribution<int> generatedY(generateDistanceFromBorder, creatorH - generateDistanceFromBorder);
                    randomX = generatedX(gen);
                    randomY = generatedY(gen);
                    angle = -90.0;
                }
                else
                {
                    std::uniform_int_distribution<int> generatedGap(150, 500);
                    randomGap = generatedGap(gen);
                    randomX -= randomGap;
                    angle = -270.0;
                }
            }
            radians = glm::radians(angle);

        }
        else
        {
            bool distanceOK = true;
            int count = 0;
            do
            {
                count++;
                randomX = generatedX(gen);
                randomY = generatedY(gen);
                float distance;
                if (count < 500)
                {
                    for (int i = 0; i < storedPositions.size(); i++)
                    {
                        float x = storedPositions[i].x;
                        float y = storedPositions[i].y;

                        distance = glm::sqrt((glm::pow(randomX - x, 2.0f)) + glm::pow(randomY - y, 2.0f));
                        if (distance < 45)
                        {
                            distanceOK = false;
                            break;
                        }
                    }
                }
                else
                {
                    distanceOK = true;
                }

            } while (!distanceOK);

            std::shuffle(triangleAngles.begin(), triangleAngles.end(), gen);
            angle = triangleAngles[0];
            radians = glm::radians(angle);
        }



        float armAngleFromMiddle = 45.0f;
        float armAngleFromMiddleRad = glm::radians(armAngleFromMiddle);

        float upX1 = randomX;
        float upY1 = randomY - lineLength;
        float leftX1 = randomX + baseLength * cos(armAngleFromMiddleRad);
        float leftY1 = randomY + baseLength * sin(armAngleFromMiddleRad);
        float rightX1 = randomX - baseLength * cos(-armAngleFromMiddleRad);
        float rightY1 = randomY - baseLength * sin(-armAngleFromMiddleRad);

        float rotatedX1 = randomX + (upX1 - randomX) * cos(radians) - (upY1 - randomY) * sin(radians);
        float rotatedY1 = randomY + (upX1 - randomX) * sin(radians) + (upY1 - randomY) * cos(radians);
        float rotatedX2 = randomX + (leftX1 - randomX) * cos(radians) - (leftY1 - randomY) * sin(radians);
        float rotatedY2 = randomY + (leftX1 - randomX) * sin(radians) + (leftY1 - randomY) * cos(radians);
        float rotatedX3 = randomX + (rightX1 - randomX) * cos(radians) - (rightY1 - randomY) * sin(radians);
        float rotatedY3 = randomY + (rightX1 - randomX) * sin(radians) + (rightY1 - randomY) * cos(radians);

        glm::vec2 vertex1(rotatedX1, rotatedY1);
        glm::vec2 vertex2(rotatedX2, rotatedY2);
        glm::vec2 vertex3(rotatedX3, rotatedY3);

        storedPositions.push_back(glm::vec2(randomX, randomY));

        triangleCollidingPositions.push_back(vertex1);
        triangleCollidingPositions.push_back(vertex2);
        triangleCollidingPositions.push_back(vertex3);
    }
}

void GameHeadingConflicts::DecideConflictOn()
{
    std::shuffle(conflictTurnedOnHolder, conflictTurnedOnHolder + 2, gen);
    if(conflictTurnedOnHolder[0] == 1)
    {
        conflictTurnedOn = true;
    }
    else if(conflictTurnedOnHolder[0] == 0)
    {
        conflictTurnedOn = false;
    }
}

void GameHeadingConflicts::DrawTriangles()
{

    flexibleShaderProgram->Bind();
    if (!taskIntroActive && gameStarted)
    {
        if (typeOfGame == "practice")
        {
            flexibleShaderProgram->SetUniform4f("u_Color", blackColor[0], blackColor[1], blackColor[2], blackColor[3]);
            triangleVA->Bind();
            glDrawArrays(GL_TRIANGLES, 0, trianglePositions.size() * 3);
            if (roundOver)
            {
                if (correctAnswer && conflictTurnedOn)
                {
                    flexibleShaderProgram->SetUniform4f("u_Color", greenColor[0], greenColor[1], greenColor[2], greenColor[3]);
                }
                else if (!correctAnswer && conflictTurnedOn)
                {
                    flexibleShaderProgram->SetUniform4f("u_Color", redColor[0], redColor[1], redColor[2], redColor[3]);

                }
                triangleCollidingVA->Bind();

                glDrawArrays(GL_TRIANGLES, 0, triangleCollidingPositions.size() * 3);
            }
            else if (!roundOver)
            {
                flexibleShaderProgram->SetUniform4f("u_Color", blackColor[0], blackColor[1], blackColor[2], blackColor[3]);
                triangleCollidingVA->Bind();
                glDrawArrays(GL_TRIANGLES, 0, triangleCollidingPositions.size() * 3);

            }
        }
        else if (typeOfGame == "test")
        {
            if (!taskIntroActive)
            {
                flexibleShaderProgram->Bind();
                flexibleShaderProgram->SetUniform4f("u_Color", blackColor[0], blackColor[1], blackColor[2], blackColor[3]);
                triangleVA->Bind();
                glDrawArrays(GL_TRIANGLES, 0, trianglePositions.size() * 3);

                triangleCollidingVA->Bind();
                glDrawArrays(GL_TRIANGLES, 0, triangleCollidingPositions.size() * 3);
            }
        }
    }
}

void GameHeadingConflicts::LoadAllGraphics()
{
    BaseGame::LoadAllGraphics();
    GameHeadingConflicts::LoadTriangleGraphics();

}

void GameHeadingConflicts::LoadTriangleGraphics()
{
    triangleVA = new VertexArray();
    triangleVB = new VertexBuffer(trianglePositions.size() * sizeof(glm::vec2), trianglePositions.data(), "dynamic");
    triangleVBL = new VertexBufferLayout();
    triangleVBL->Push<glm::vec2>(1);
    triangleVA->AddBuffer(triangleVB, triangleVBL);

    triangleCollidingVA = new VertexArray();
    triangleCollidingVB = new VertexBuffer(triangleCollidingPositions.size() * sizeof(glm::vec2), triangleCollidingPositions.data(), "dynamic");
    triangleCollidingVBL = new VertexBufferLayout();
    triangleCollidingVBL->Push<glm::vec2>(1);
    triangleCollidingVA->AddBuffer(triangleCollidingVB, triangleCollidingVBL);
}

void GameHeadingConflicts::DrawText()
{


    if (roundOver && typeOfGame == "practice")
    {
        if (correctAnswer && conflictTurnedOn)
        {
            BaseGame::CreateText("Correct answer!", 0.4f, 100.0f, 50.0f, 0.0f, 1.0f, 0.0f, 1); 
        }
        else if (correctAnswer && !conflictTurnedOn)
        {
            BaseGame::CreateText("Correct! There is no conflict.", 0.4f, 100.0f, 50.0f, 0.0f, 1.0f, 0.0f, 1);
        }
        else if (!correctAnswer && conflictTurnedOn)
        {
            BaseGame::CreateText("You missed a conflict.", 0.4f, 100.0f, 50.0f, 1.0f, 0.0f, 0.0f, 1);
        }
        else if (!correctAnswer && !conflictTurnedOn)
        {
            BaseGame::CreateText("Wrong response. There is no conflict.", 0.4f, 100.0f, 50.0f, 1.0f, 0.0f, 0.0f, 1);
        }

    }
}

void GameHeadingConflicts::CreateNewTriangleGroup()
{
    GameHeadingConflicts::ClearTriangles();
    GameHeadingConflicts::DecideConflictOn();
    GameHeadingConflicts::GenerateCollidingTrianglesPositions();
    GameHeadingConflicts::GenerateTrianglesPositions(trianglesCount);
    
    triangleVB->SubData(trianglePositions.size() * sizeof(glm::vec2), trianglePositions.data());
    triangleCollidingVB->SubData(triangleCollidingPositions.size() * sizeof(glm::vec2), triangleCollidingPositions.data());
}

void GameHeadingConflicts::ClearTriangles()
{
    storedPositions.clear();
    trianglePositions.clear();
    triangleCollidingPositions.clear();
}

void GameHeadingConflicts::OptionBtnPressed(int btn)
{
    if (!roundOver && !taskIntroActive)
    {
        if (btn == 1) //conflict btn
        {
            optionBtn2Visible = true;
            optionBtn1Visible = false;
            pauseTimeAddedUp = 0;
            if (typeOfGame == "practice")
            {
                if (conflictTurnedOn)
                {
                    correctAnswer = true;
                }
                else
                {
                    wrongAnswer = true;
                }
                roundOver = true;
            }
            else
            {
                taskIntroActive = true;
                GameHeadingConflicts::CreateNewTriangleGroup();
                timestamp = std::chrono::steady_clock::now();
            }
        }
    }
    if (roundOver)
    {
        if (typeOfGame == "practice")
        {
            if (btn == 2) //continue btn
            {
                optionBtn2Visible = false;
                pauseTimeAddedUp = 0;
                taskIntroActive = true;
                correctAnswer = false;
                wrongAnswer = false;
                roundOver = false;
                timestamp = std::chrono::steady_clock::now();
                GameHeadingConflicts::CreateNewTriangleGroup();
            }
        }
    }
}

void GameHeadingConflicts::UpdateTime()
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
            timestamp = std::chrono::steady_clock::now();
            taskIntroActive = true;
        }
    }

    if (gameStarted)
    {
        if (milisecsOfRoundGoing > taskIntroTimeMilisecs && taskIntroActive)
        {
            optionBtn1Visible = true;
            taskIntroActive = false;
            timestamp = std::chrono::steady_clock::now();
        }
        if (typeOfGame == "practice")
        {
            if (milisecsOfRoundGoing > roundTimeMilisecs && !taskIntroActive && !wrongAnswer && !correctAnswer)
            {
                roundOver = true;
                if (!conflictTurnedOn)
                {
                    correctAnswer = true;
                }
                else
                {
                    correctAnswer = false;
                }
            }
        }
        else if (typeOfGame == "test")
        {
            if (milisecsOfRoundGoing > roundTimeMilisecs && !taskIntroActive)
            {
                GameHeadingConflicts::CreateNewTriangleGroup();
                timestamp = std::chrono::steady_clock::now();
                taskIntroActive = true;
            }
        }
    }
}



void GameHeadingConflicts::Update()
{
    if (!gamePaused)
    {
        GameHeadingConflicts::UpdateTime();
    }
}

void GameHeadingConflicts::Draw()
{
    glClearColor(greyColor2[0], greyColor2[1], greyColor2[2], greyColor2[3]);
    glClear(GL_COLOR_BUFFER_BIT);
    GameHeadingConflicts::DrawTriangles();
    GameHeadingConflicts::DrawText();
    BaseGame::Draw();
}

