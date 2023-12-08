#pragma once
#include "GameDividedAttention.h"
#include <chrono>
#include <wx/wx.h>
#include <random>
#include <array>

//doplnit cisla u rectanglu, at je jasny ktery je ktery (1,2,3,4)
//typ: premenit funkci pri detekci colize, aby se kolize checkovala az po opusteni kruhu rakety, ne podle casu
//typ: upravit rychlost a intenzitu srazeni

GameDividedAttention::GameDividedAttention(int level, std::string typeOfGame, int startW, int startH, int creatorW, int creatorH, std::string typeOfTimer)
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
            rectW = 600;
            rectH = 450;
            roundTimeMilisecs = 300000;
            playRectCount = 1;
        }
        else if (level == 2)
        {
            rectW = 450;
            rectH = 350;
            roundTimeMilisecs = 600000;
            playRectCount = 2;
        }
        else if (level == 3)
        {
            rectW = 350;
            rectH = 250;
            roundTimeMilisecs = 900000;
            playRectCount = 4;
        }
    }
    else if (typeOfGame == "test")
    {
        roundTimeMilisecs = 900000;
        playRectCount = 4;
    }

    GameDividedAttention::CreateRactangles();

}

GameDividedAttention::~GameDividedAttention()
{
    

}

void GameDividedAttention::CreateRactangles()
{
    if (level == 1)
    {

        dividedRects.push_back(creatorW / 2 - rectW / 2);      // Levý horní roh X
        dividedRects.push_back(creatorH / 2 - rectH / 2);      // Levý horní roh Y

        dividedRects.push_back(creatorW / 2 + rectW / 2);      // Pravý horní roh X
        dividedRects.push_back(creatorH / 2 - rectH / 2);      // Pravý horní roh Y

        dividedRects.push_back(creatorW / 2 + rectW / 2);      // Pravý dolní roh X
        dividedRects.push_back(creatorH / 2 + rectH / 2);      // Pravý dolní roh Y

        dividedRects.push_back(creatorW / 2 - rectW / 2);      // Levý dolní roh X
        dividedRects.push_back(creatorH / 2 + rectH / 2);

        playgroundRect1 = new PlaygroundRect(creatorW / 2 - rectW / 2, creatorH / 2 - rectH / 2, rectW, rectH, 1, flexibleShaderProgram, 1, creatorW, creatorH);
        playgroundsVec.push_back(playgroundRect1);


    }
    else if (level == 2)
    {
        // První obdélník

        dividedRects.push_back(creatorW / 2 - rectW);      // Levý horní roh X
        dividedRects.push_back(creatorH / 2 - rectH / 2);  // Levý horní roh Y

        dividedRects.push_back(creatorW / 2);              // Pravý horní roh X
        dividedRects.push_back(creatorH / 2 - rectH / 2);  // Pravý horní roh Y

        dividedRects.push_back(creatorW / 2);              // Pravý dolní roh X
        dividedRects.push_back(creatorH / 2 + rectH / 2);  // Pravý dolní roh Y

        dividedRects.push_back(creatorW / 2 - rectW);      // Levý dolní roh X
        dividedRects.push_back(creatorH / 2 + rectH / 2);  // Levý dolní roh Y

        playgroundRect1 = new PlaygroundRect(creatorW / 2 - rectW, creatorH / 2 - rectH / 2, rectW, rectH, 2, flexibleShaderProgram, 1, creatorW, creatorH);

        //Druhy obd

        dividedRects.push_back(creatorW / 2 + rectSpacing);     
        dividedRects.push_back(creatorH / 2 - rectH / 2);       

        dividedRects.push_back(creatorW / 2 + rectW + rectSpacing);  
        dividedRects.push_back(creatorH / 2 - rectH / 2);        

        dividedRects.push_back(creatorW / 2 + rectW + rectSpacing);  
        dividedRects.push_back(creatorH / 2 + rectH / 2);      

        dividedRects.push_back(creatorW / 2 + rectSpacing);        
        dividedRects.push_back(creatorH / 2 + rectH / 2);

        playgroundRect2 = new PlaygroundRect(creatorW / 2 + rectSpacing, creatorH / 2 - rectH / 2, rectW, rectH, 2, flexibleShaderProgram, 2, creatorW, creatorH);

        playgroundsVec.push_back(playgroundRect1);
        playgroundsVec.push_back(playgroundRect2);


    }
    else if (level == 3)
    {
        float rectSpacing = 20;
        float totalWidth = 2 * rectW + rectSpacing;
        float totalHeight = 2 * rectH + rectSpacing;

        float rectX = (creatorW - totalWidth) / 2; // X pro první obdélník
        float rectY = (creatorH - totalHeight) / 2; // Y pro první obdélník


        // První obdélník (nahoře vlevo)
        playgroundRect1 = new PlaygroundRect(rectX, rectY, rectW, rectH, 2, flexibleShaderProgram, 2, creatorW, creatorH);
        dividedRects.push_back(rectX); // Levý horní roh X
        dividedRects.push_back(rectY); // Levý horní roh Y

        dividedRects.push_back(rectX + rectW); // Pravý horní roh X
        dividedRects.push_back(rectY); // Pravý horní roh Y

        dividedRects.push_back(rectX + rectW); // Pravý dolní roh X
        dividedRects.push_back(rectY + rectH); // Pravý dolní roh Y

        dividedRects.push_back(rectX); // Levý dolní roh X
        dividedRects.push_back(rectY + rectH); // Levý dolní roh Y


        // Druhý obdélník (nahoře vpravo)
        rectX += rectW + rectSpacing; // Posunout X pro druhý obdélník
        playgroundRect2 = new PlaygroundRect(rectX, rectY, rectW, rectH, 2, flexibleShaderProgram, 2, creatorW, creatorH);
        dividedRects.push_back(rectX); // Levý horní roh X
        dividedRects.push_back(rectY); // Levý horní roh Y

        dividedRects.push_back(rectX + rectW); // Pravý horní roh X
        dividedRects.push_back(rectY); // Pravý horní roh Y

        dividedRects.push_back(rectX + rectW); // Pravý dolní roh X
        dividedRects.push_back(rectY + rectH); // Pravý dolní roh Y

        dividedRects.push_back(rectX); // Levý dolní roh X
        dividedRects.push_back(rectY + rectH); // Levý dolní roh Y

        // Třetí obdélník (dole vlevo)
        rectX = (creatorW - totalWidth) / 2; // Resetovat X pro třetí obdélník
        rectY += rectH + rectSpacing; // Posunout Y pro třetí obdélník

        playgroundRect3 = new PlaygroundRect(rectX, rectY, rectW, rectH, 2, flexibleShaderProgram, 2, creatorW, creatorH);
        dividedRects.push_back(rectX); // Levý horní roh X
        dividedRects.push_back(rectY); // Levý horní roh Y

        dividedRects.push_back(rectX + rectW); // Pravý horní roh X
        dividedRects.push_back(rectY); // Pravý horní roh Y

        dividedRects.push_back(rectX + rectW); // Pravý dolní roh X
        dividedRects.push_back(rectY + rectH); // Pravý dolní roh Y

        dividedRects.push_back(rectX); // Levý dolní roh X
        dividedRects.push_back(rectY + rectH); // Levý dolní roh Y

        // Čtvrtý obdélník (dole vpravo)
        rectX += rectW + rectSpacing; // Posunout X pro čtvrtý obdélník
        playgroundRect4 = new PlaygroundRect(rectX, rectY, rectW, rectH, 2, flexibleShaderProgram, 2, creatorW, creatorH);
        dividedRects.push_back(rectX); // Levý horní roh X
        dividedRects.push_back(rectY); // Levý horní roh Y

        dividedRects.push_back(rectX + rectW); // Pravý horní roh X
        dividedRects.push_back(rectY); // Pravý horní roh Y

        dividedRects.push_back(rectX + rectW); // Pravý dolní roh X
        dividedRects.push_back(rectY + rectH); // Pravý dolní roh Y

        dividedRects.push_back(rectX); // Levý dolní roh X
        dividedRects.push_back(rectY + rectH); // Levý dolní roh Y

        playgroundsVec.push_back(playgroundRect1);
        playgroundsVec.push_back(playgroundRect2);
        playgroundsVec.push_back(playgroundRect3);
        playgroundsVec.push_back(playgroundRect4);
    }
}


void GameDividedAttention::LoadAllGraphics()
{
    BaseGame::LoadAllGraphics();
    GameDividedAttention::LoadRectanglesGraphics();
    for (PlaygroundRect* rect : playgroundsVec)
    {
        rect->LoadAllGraphics();
    }


}

void GameDividedAttention::LoadRectanglesGraphics()
{
    if (level == 2)
    {
        twoRectanglesIB = new IndexBuffer(12, twoRectanglesIndices);
    }
    else if (level == 3)
    {
        threeRectanglesIB = new IndexBuffer(24, threeRectanglesIndices);
    }

    rect1VA = new VertexArray();
    rect1VB = new VertexBuffer(dividedRects.size() * sizeof(std::vector<float>), dividedRects.data(), "static");
    rect1VA->AddBuffer(rect1VB, twoFloatVBL);

}

void GameDividedAttention::DrawRectangles()
{
    GLCall(flexibleShaderProgram->Bind());
    GLCall(flexibleShaderProgram->SetUniform4f("u_Color", whiteColor[0], whiteColor[1], whiteColor[2], whiteColor[3]));
    GLCall(rect1VA->Bind());

    switch (level)
    {
    case 1:
        GLCall(rectangleIB->Bind());
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
        break;
    case 2:
        GLCall(twoRectanglesIB->Bind());
        GLCall(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, nullptr));
        break;
    case 3:
        GLCall(threeRectanglesIB->Bind());
        GLCall(glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, nullptr));
        break;
    default:
        break;
    }
}

void GameDividedAttention::DrawText()
{
    glm::vec2 textSize;
    std::string text;
    float scale;

    std::chrono::milliseconds elapsedTimeToCollide;

    elapsedTimeToCollide = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timeToDeleteText);
    milisecsOfKeyPressed = static_cast<int>(elapsedTimeToCollide.count());


    if (wrongInput)
    {
        text = "Wrong input.";
        scale = 0.5f;
        textSize = CalculateTextSize(text, scale);
        BaseGame::CreateText(text, scale, creatorW / 2 - textSize.x / 2, creatorH / 2 - textSize.y / 2, 1.0f, 0.0f, 0.0f, 1);
    }
    else if (correctInput)
    {
        text = "Correct input.";
        scale = 0.5f;
        textSize = CalculateTextSize(text, scale);
        BaseGame::CreateText(text, scale, creatorW / 2 - textSize.x / 2, creatorH / 2 - textSize.y / 2, 0.0f, 1.0f, 0.0f, 1);
    }
    else if (missedInput)
    {
        text = "Missed input.";
        scale = 0.5f;
        textSize = CalculateTextSize(text, scale);
        BaseGame::CreateText(text, scale, creatorW / 2 - textSize.x / 2, creatorH / 2 - textSize.y / 2, 1.0f, 0.0f, 0.0f, 1);
    }

    if (milisecsOfKeyPressed > milisecsOfDisplayingText)
    {
        wrongInput = false;
        correctInput = false;
        missedInput = false;
    }
}

void GameDividedAttention::LeftClickBtn(float xPos, float yPos)
{

}

void GameDividedAttention::CheckCollision()
{
    for (PlaygroundRect* rect : playgroundsVec)
    {
        if (rect->CheckMissedInput())
        {
            missedInput = true;
            countMissedInput++;
            timeToDeleteText = std::chrono::steady_clock::now();
        }
    }
}

void GameDividedAttention::KeyPressed(wxKeyEvent& event)
{
    timeToDeleteText = std::chrono::steady_clock::now();

    int keyCode = event.GetKeyCode();

    if (keyCode == 'a' || keyCode == 'A')
    {
        playgroundRect1->SetTimeSinceInput();
        if (playgroundRect1->CheckInput())
        {
            countCorrectInput++;
            correctInput = true;
            timeToDeleteText = std::chrono::steady_clock::now();
        }
        else
        {
            countWrongInput++;
            wrongInput = true;
            timeToDeleteText = std::chrono::steady_clock::now();

        }
    }
}

void GameDividedAttention::Draw()
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GameDividedAttention::DrawRectangles();
    for (PlaygroundRect* rect : playgroundsVec)
    {
        rect->Draw();
    }
    GameDividedAttention::DrawText();
    BaseGame::Draw();
}

void GameDividedAttention::Update()
{
    BaseGame::UpdateTime();
    if (gameStarted && !gamePaused)
    {
        for (PlaygroundRect* rect : playgroundsVec)
        {
            rect->Update();
        }
        GameDividedAttention::CheckCollision();
    }
}