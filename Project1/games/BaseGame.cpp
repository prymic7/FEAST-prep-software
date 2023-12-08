#pragma once

#include "BaseGame.h"

//type: rozdelit funkci HandleShaders na vice funkci(kazda funkce bude pro jeden shader)... kdyz potrebuju zmenit neco v jednom shaderu u jedny hry, musim menit celou funkci
BaseGame::BaseGame(int level, std::string typeOfGame, int startW, int startH, int creatorW, int creatorH, std::string typeOfTimer) : level(level), typeOfGame(typeOfGame), startW(startW), startH(startH), creatorW(creatorW), creatorH(creatorH), typeOfTimer(typeOfTimer)
{
    gen = std::mt19937(std::random_device{}());

    time_start = std::chrono::system_clock::now();
    startPause = std::chrono::steady_clock::now();
    endPause = std::chrono::steady_clock::now();
    appStartTime = std::chrono::steady_clock::now();
    timestamp = std::chrono::steady_clock::now();
    roundFinishedTime = std::chrono::steady_clock::now();
    realTime = std::chrono::steady_clock::now();
    focusBackTime = std::chrono::steady_clock::now();


    timer = true;
    gameStarted = false;
    targetTime = 3000000;
    BaseGame::InitShaders();
}

BaseGame::~BaseGame()
{
    delete gameBarVA;
    delete gameBarVB;
    delete gameBarVBL;
    delete gameBarIB;
}

void BaseGame::SetScreenSize(float w, float h)
{
    nowW = w;
    nowH = h;
}

void BaseGame::InitShaders()
{
    flexibleShaderProgram = new ShaderProgram("opengl/shaders/flexible.shader");
    staticShaderProgram = new ShaderProgram("opengl/shaders/static.shader");
    textStaticShaderProgram = new ShaderProgram("opengl/shaders/textStatic.shader");
    textFlexibleShaderProgram = new ShaderProgram("opengl/shaders/textFlexible.shader");
    staticImageShaderProgram = new ShaderProgram("opengl/shaders/staticImage.shader");

    shaderProgramInit = 1;
}

void BaseGame::HandleShaders(int nowW, int nowH, int creatorW, int creatorH, int startW, int startH)
{
    wRatio = (float)nowW / startW;
    hRatio = (float)nowH / startH;
    BaseWindowDiffW = (creatorW - nowW) / 2;
    BaseWindowDiffH = (creatorH - nowH) / 2;

    ratioProjection = glm::ortho(-wRatio, wRatio, -hRatio, hRatio, -1.0f, 1.0f);
    glm::mat4 normalizeOrtho = glm::ortho(0.0f, static_cast<float>(nowW), 0.0f, static_cast<float>(nowH));

    GLCall(flexibleShaderProgram->Bind());
    GLCall(flexibleShaderProgram->SetUniformMatrix4fv("u_OrthographicMatrix", 1, GL_FALSE, glm::value_ptr(ratioProjection)));
    GLCall(flexibleShaderProgram->SetUniform2f("u_Ratio", wRatio, hRatio)); //pridanim "-" pred hRatio se objekty otoci
    GLCall(flexibleShaderProgram->SetUniform2f("u_WindowSize", nowW, nowH));
    GLCall(flexibleShaderProgram->SetUniform2f("u_BaseWindowDiff", BaseWindowDiffW, BaseWindowDiffH));
    GLCall(flexibleShaderProgram->Unbind());

    GLCall(staticShaderProgram->Bind()); 
    GLCall(staticShaderProgram->SetUniform2f("u_WindowSize", nowW, nowH));
    GLCall(staticShaderProgram->Unbind());

    GLCall(textFlexibleShaderProgram->Bind());
    GLCall(textFlexibleShaderProgram->SetUniform2f("u_Ratio", wRatio, hRatio));
    GLCall(textFlexibleShaderProgram->SetUniformMatrix4fv("normalizeOrtho", 1, GL_FALSE, glm::value_ptr(normalizeOrtho)));
    GLCall(textFlexibleShaderProgram->SetUniformMatrix4fv("projection3", 1, GL_FALSE, glm::value_ptr(ratioProjection)));
    GLCall(textFlexibleShaderProgram->Unbind());

    GLCall(textStaticShaderProgram->Bind());
    GLCall(textStaticShaderProgram->SetUniformMatrix4fv("normalizeOrtho", 1, GL_FALSE, glm::value_ptr(normalizeOrtho)));
}


void BaseGame::HandleViewport(int nowW, int nowH, int creatorW, int creatorH, int startW, int startH)
{
    glViewport(0, 0, nowW, nowH);

}

std::vector<bool> BaseGame::GetButtons() //hard on cpu?? Pouzit bitset #include <bitset>
{
    std::vector<bool> vec;
    vec.push_back(optionBtn1Visible);
    vec.push_back(optionBtn2Visible);
    vec.push_back(optionBtn3Visible);
    vec.push_back(optionBtn4Visible);
    vec.push_back(optionBtn5Visible);
    vec.push_back(optionBtn6Visible);
    vec.push_back(optionBtn7Visible);
    vec.push_back(optionBtn8Visible);
    vec.push_back(optionBtn9Visible);
    vec.push_back(optionBtn10Visible);
    return vec;
}

void BaseGame::DrawCountDown()
{
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - time_start);

    if (!gameStarted)
    {
        GLCall(flexibleShaderProgram->Bind());
        GLCall(flexibleShaderProgram->SetUniform4f("u_Color", appColor[0], appColor[1], appColor[2], appColor[3]));
        GLCall(countDownVA->Bind());
        GLCall(rectangleIB->Bind());
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));

        CreateTextToRect(countDownText, 0.9, creatorW / 2 - countDownRectSize / 2, creatorH / 2 - countDownRectSize / 2, countDownRectSize, countDownRectSize, whiteColor[0], whiteColor[0], whiteColor[0], 2);
        //CreateTextToRect(countDownText, 0.9f, 950, 550, 60.0f, 60.0f, 0.5f, 0.5f, 0.5f, 2);
    }
    if (duration.count() - pauseTimeAddedUp > 1000 && duration.count() < 2000)
    {
        countDownText = "2";
    }
    else if (duration.count() - pauseTimeAddedUp > 2000 && duration.count() < 3000)
    {
        countDownText = "1";
    }
    else if (duration.count() - pauseTimeAddedUp > 3000)
    {
        countDownActive = false;
    }
}

void BaseGame::RenderText(std::string text, float x, float y, float scale, glm::vec3 color, int shader)
{
    shader = 2;
    if (shader == 1)
    {
        textStaticShaderProgram->Bind();
        textStaticShaderProgram->SetUniform3f("textColor", color.x, color.y, color.z);
    }
    else if (shader == 2)
    {
        textFlexibleShaderProgram->Bind();
        textFlexibleShaderProgram->SetUniform3f("textColor", color.x, color.y, color.z); //flexible dat do staticu

    }

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);

    // iterate through all characters
    std::string::const_iterator c;

    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        BaseGame::EnableBlending();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        BaseGame::DisableBlending();

        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void BaseGame::CreateTextToRect(std::string text, float scale, float rectX, float rectY, float rectW, float rectH, float r, float g, float b, int shader)
{

    glm::vec2 textSize = BaseGame::CalculateTextSize(text, scale);

    float textWidth = textSize.x; 
    float textHeight = textSize.y; 

    float textX = rectX + (std::abs(textWidth - rectW)) / 2;
    float textY = rectY + (std::abs(textHeight + rectH)) / 2;

    BaseGame::RenderText(text, textX, nowH - textY, scale, glm::vec3(r, g, b), shader);
}

void BaseGame::CreateText(std::string text, float scale, float posX, float posY, float r, float g, float b, int shader)
{
    BaseGame::RenderText(text, posX, posY, scale, glm::vec3(r, g, b), shader);

}

void BaseGame::EnableBlending()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void BaseGame::DisableBlending()
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ZERO);
}

void BaseGame::LoadFont()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        wxLogStatus("ERROR::FREETYPE: Could not init FreeType Library");
    }

    FT_Face face;
    if (FT_New_Face(ft, "fonts/Kanit-SemiBold.ttf", 0, &face)) {
        wxLogStatus("ERROR::FREETYPE: Failed to load font");
    }
    else {
        FT_Set_Pixel_Sizes(face, 0, 48);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        for (unsigned char c = 0; c < 128; c++)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                wxLogStatus("ERROR::FREETYTPE: Failed to load Glyph");
                continue;
            }
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
    GLCall(glGenVertexArrays(1, &textVAO));
    GLCall(glGenBuffers(1, &textVBO));
    GLCall(glBindVertexArray(textVAO));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, textVBO));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindVertexArray(0));
}

glm::vec2 BaseGame::CalculateTextSize(const std::string& text, float scale)
{
    float width = 0.0f;
    float maxHeight = 0.0f;
    for (char c : text)
    {
        if (Characters.find(c) != Characters.end())
        {
            Character ch = Characters[c];
            width += (ch.Advance >> 6) * scale;

            float characterHeight = ch.Size.y * scale;
            if (characterHeight > maxHeight)
            {
                maxHeight = characterHeight;
            }
        }
    }
    return glm::vec2(width, maxHeight);  
}

void BaseGame::UpdateAmountOfRounds() /*Has to call when we press continue to nextround*/
{
    if (!timer)
    {

    }
}

void BaseGame::LoadAllGraphics()
{
    BaseGame::LoadCountDownGraphics();
    BaseGame::LoadMenuGraphics();
    BaseGame::LoadPauseGraphics();
    BaseGame::LoadTasksIntroGraphics();
}

void BaseGame::LoadPauseGraphics()
{
    pauseVA = new VertexArray();
    pauseVB = new VertexBuffer(sizeof(pauseVertices), pauseVertices, "static");
    pauseVA->AddBuffer(pauseVB, twoFloatVBL);
}

void BaseGame::LoadTasksIntroGraphics()
{
    taskIntroVA = new VertexArray();
    taskIntroVB = new VertexBuffer(sizeof(taskIntroVertices), taskIntroVertices, "static");
    taskIntroVA->AddBuffer(taskIntroVB, twoFloatVBL);
}

void BaseGame::LoadCountDownGraphics()
{
    countDownVA = new VertexArray();
    countDownVB = new VertexBuffer(sizeof(countDownVertices), countDownVertices, "static");
    twoFloatVBL = new VertexBufferLayout();
    twoFloatVBL->Push<float>(2);
    rectangleIB = new IndexBuffer(6, rectangleIndices);
    doubleRectangleIB = new IndexBuffer(12, doubleRectangleIndices);
    countDownVA->AddBuffer(countDownVB, twoFloatVBL);
}

void BaseGame::LoadMenuGraphics()
{
    menuVA = new VertexArray();
    menuVB = new VertexBuffer(sizeof(menuVertices), menuVertices, "static");
    menuVA->AddBuffer(menuVB, twoFloatVBL);
}


void BaseGame::DrawAmountOfRounds()
{

}

void BaseGame::DrawPause()
{
    if (gamePaused)
    {
        GLCall(flexibleShaderProgram->Bind());
        GLCall(flexibleShaderProgram->SetUniform4f("u_Color", appColor[0], appColor[1], appColor[2], appColor[3]));
        GLCall(pauseVA->Bind());
        GLCall(rectangleIB->Bind());
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr))
    }
}

void BaseGame::DrawTasksIntroGraphics()
{
    //if (!justRun)
    //{
    //    if (taskIntroActive && !countDownActive)
    //    {
    //        GLCall(flexibleShaderProgram->Bind());
    //        GLCall(flexibleShaderProgram->SetUniform4f("u_Color", appColor[0], appColor[1], appColor[2], appColor[3]));
    //        GLCall(taskIntroVA->Bind());
    //        GLCall(rectangleIB->Bind());
    //        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
    //    }
    //}
    if (taskIntroActive && gameStarted)
    {
        GLCall(flexibleShaderProgram->Bind());
        GLCall(flexibleShaderProgram->SetUniform4f("u_Color", appColor[0], appColor[1], appColor[2], appColor[3]));
        GLCall(taskIntroVA->Bind());
        GLCall(rectangleIB->Bind());
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr));
    }


}

void BaseGame::DrawMenu()
{
    GLCall(staticShaderProgram->Bind());
    GLCall(staticShaderProgram->SetUniform4f("u_Color", appColor[0], appColor[1], appColor[2], appColor[3]));
    GLCall(menuVA->Bind());
    GLCall(rectangleIB->Bind());
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr))
}

void BaseGame::Draw()
{
    BaseGame::DrawCountDown();
    BaseGame::DrawAmountOfRounds();
    BaseGame::DrawPause(); 
    BaseGame::DrawTasksIntroGraphics();
    BaseGame::HandleTimerBar();
    //BaseGame::DrawMenu();

}

void BaseGame::Update()
{
    BaseGame::UpdateTime();
}

void BaseGame::SetGameStarted(bool v)
{
    gameStarted = v;
}

void BaseGame::UpdateTime()
{

    timeNow = std::chrono::steady_clock::now();

    std::chrono::milliseconds elapsedTimeStamp;

    elapsedTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - timestamp);
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

    if (!justRun)
    {
        if (gameStarted)
        {
            std::chrono::milliseconds elapsedTimeRound = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - timestamp);
            milisecsOfRoundGoing = static_cast<int>(elapsedTimeRound.count());
            if (milisecsOfRoundGoing > roundTimeMilisecs && !taskIntroActive)
            {
                if (typeOfGame == "practice")
                {
                    roundOver = true;
                }
                else if (typeOfGame == "test")
                {
                    timestamp = std::chrono::steady_clock::now();
                    taskIntroActive = true;
                }
            }

            else if (milisecsOfRoundGoing > taskIntroTimeMilisecs && taskIntroActive)
            {
                taskIntroActive = false;
                timestamp = std::chrono::steady_clock::now();

            }
        }
    }

}

void BaseGame::SetPause(bool v)
{
    gamePaused = v;
    if (v)
    {
        startPause = std::chrono::steady_clock::now();
        pauseWaiting = true;
    }
    else
    {
        endPause = std::chrono::steady_clock::now();
        std::chrono::steady_clock::duration pauseTimeDiff = endPause - startPause;
        timeInPause = std::chrono::duration_cast<std::chrono::milliseconds>(pauseTimeDiff).count();
        pauseTimeAddedUp += timeInPause; // main timer
        std::chrono::milliseconds timeElapsedInPause = std::chrono::milliseconds(timeInPause);
        timestamp += timeElapsedInPause; // sector of game(for example countdown, or taskintro time)
    }
}

void BaseGame::HandleTimerBar()
{

    play_time = std::chrono::steady_clock::now();
    if (!gamePaused)
    {
        adjusted_play_time = play_time - std::chrono::milliseconds(pauseTimeAddedUp);
        std::chrono::steady_clock::duration timeDifference = adjusted_play_time - appStartTime;
        timeWithPause = std::chrono::duration_cast<std::chrono::milliseconds>(timeDifference).count();
    }


    currentTimeSecs = timeWithPause / 1000;
    targetTimeSecs = targetTime / 1000;

    int diffSecs = targetTimeSecs - currentTimeSecs;
    oldMin = min;
    oldSec = sec;
    min = diffSecs / 60;
    sec = diffSecs % 60;



    if (sec < 10)
    {
        timeStr = std::to_string(min) + ":0" + std::to_string(sec);
    }
    else
    {
        timeStr = std::to_string(min) + ":" + std::to_string(sec);
    }
    if (oneTime)
    {
        oneTime = false;
    }
    if (timeWithPause > targetTime)
    {
        parentPanel->Hide();
        mainPanel->Show();
        playingGame = false;  //GAME OVER
    }


    if (typeOfTimer == "timer")
    {
        if (min == 0 && sec <= 30)
        {
            CreateTextToRect(timeStr, 0.5, 200.0f, 200.0f, 100.0f, 100.0f, 1.0f, 1.0f, 1.0f, 2);
        }
        else
        {
            CreateTextToRect(timeStr, 0.5, 200.0f, 200.0f, 100.0f, 100.0f, 1.0f, 0.0f, 0.0f, 2);
        }
    }

}


std::vector<float> BaseGame::GetBaseGameScreenDefaultSize()
{
    std::vector<float> screenSize;
    screenSize.push_back(creatorW);
    screenSize.push_back(creatorH);

    return screenSize;
}

void BaseGame::SetStartSize(float w, float h)
{
    startW = w;
    startH = h;
}

std::vector<float> BaseGame::GetStartSize()
{
    std::vector<float> startSize;
    startSize.push_back(startW);
    startSize.push_back(startH);

    return startSize;
}


float BaseGame::GetStartWidth()
{
    return startW;
}

float BaseGame::GetStartHeight()
{
    return startH;
}

void BaseGame::SetFocusBackTimer()
{
    focusBackTime = std::chrono::steady_clock::now();
    setFocusBack = true;
}

void BaseGame::SetFocusBack(wxGLCanvas* canvas)
{

    std::chrono::milliseconds elapsedTimeRound;
    elapsedTimeRound = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - focusBackTime);
    milisecsAfterInput = static_cast<int>(elapsedTimeRound.count());


    if (milisecsAfterInput > 200 && setFocusBack)
    {
        canvas->SetFocus();
        setFocusBack = false;
    }
}

void BaseGame::neco()
{
    wxLogStatus("basegame");
}

std::vector<float> BaseGame::GenerateCircle(glm::vec2 spawnPoint, float radius, int numSegments)
{
    std::vector<float> vec;
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = radius * cos(theta) + spawnPoint.x;
        float y = radius * sin(theta) + spawnPoint.y;
        vec.push_back(x);
        vec.push_back(y);
    };
    return vec;
}

std::vector<float> BaseGame::GenerateTriangle(glm::vec2 spawnPoint, float baseLength, float lineLength)
{
    std::vector<float> vec;
    float x = spawnPoint.x;
    float y = spawnPoint.y;

    float armAngleFromMiddle = 45.0f;
    float armAngleFromMiddleRad = glm::radians(armAngleFromMiddle);

    float upX1 = x;
    float upY1 = y - lineLength;
    float leftX1 = x + baseLength * cos(armAngleFromMiddleRad);
    float leftY1 = y + baseLength * sin(armAngleFromMiddleRad);
    float rightX1 = x - baseLength * cos(-armAngleFromMiddleRad);
    float rightY1 = y - baseLength * sin(-armAngleFromMiddleRad);
    vec.push_back(upX1);
    vec.push_back(upY1);
    vec.push_back(leftX1);
    vec.push_back(leftY1);
    vec.push_back(rightX1);
    vec.push_back(rightY1);
    return vec;
}

std::vector<float> BaseGame::GenerateSquare(glm::vec2 spawnPoint, float size)
{
    std::vector<float> vec;

    float topLeftX = spawnPoint.x - size / 2.0f;
    float topLeftY = spawnPoint.y - size / 2.0f;
    float topRightX = spawnPoint.x + size / 2.0f;
    float topRightY = spawnPoint.y - size / 2.0f;
    float bottomLeftX = spawnPoint.x - size / 2.0f;
    float bottomLeftY = spawnPoint.y + size / 2.0f;
    float bottomRightX = spawnPoint.x + size / 2.0f;
    float bottomRightY = spawnPoint.y + size / 2.0f;

    vec.push_back(topLeftX);
    vec.push_back(topLeftY);
    vec.push_back(topRightX);
    vec.push_back(topRightY);
    vec.push_back(bottomRightX);
    vec.push_back(bottomRightY);
    vec.push_back(bottomLeftX);
    vec.push_back(bottomLeftY);
    return vec;
}

std::vector<float> BaseGame::GenerateRectangle(glm::vec2 spawnPoint, float width, float height)
{
    std::vector<float> vec;

    float topLeftX = spawnPoint.x - width / 2.0f;
    float topLeftY = spawnPoint.y - height / 2.0f;
    float topRightX = spawnPoint.x + width / 2.0f;
    float topRightY = spawnPoint.y - height / 2.0f;
    float bottomLeftX = spawnPoint.x - width / 2.0f;
    float bottomLeftY = spawnPoint.y + height / 2.0f;
    float bottomRightX = spawnPoint.x + width / 2.0f;
    float bottomRightY = spawnPoint.y + height / 2.0f;

    vec.push_back(topLeftX);
    vec.push_back(topLeftY);
    vec.push_back(topRightX);
    vec.push_back(topRightY);
    vec.push_back(bottomRightX);
    vec.push_back(bottomRightY);
    vec.push_back(bottomLeftX);
    vec.push_back(bottomLeftY);
    return vec;
}

std::vector<float> BaseGame::GenerateStar(glm::vec2 center, float outerRadius, float innerRadius, int numPoints)
{
    std::vector<float> vertices;

    float angle = glm::pi<float>() / numPoints;

    for (int i = 0; i < 2 * numPoints; ++i) 
    {
        float radius = (i % 2 == 0) ? innerRadius : outerRadius;
        float x = center.x + radius * std::cos(i * angle - 55.0f);
        float y = center.y + radius * std::sin(i * angle - 55.0f);

        vertices.push_back(x);
        vertices.push_back(y);
    }

    return vertices;

}

std::vector<float> BaseGame::GenerateHexagon(glm::vec2 center, float radius)
{
    std::vector<float> vec;

    const int sides = 6;
    const float angleIncrement = 360.0f / sides;

    for (int i = 0; i < sides; ++i) {
        float angle = glm::radians(i * angleIncrement);

        float x = center.x + radius * std::cos(angle);
        float y = center.y + radius * std::sin(angle);

        vec.push_back(x);
        vec.push_back(y);
    }

    return vec;
}

std::vector<float> BaseGame::GenerateOctagon(glm::vec2 center, float radius)
{
    std::vector<float> vec;

    const int sides = 8;
    const float angleIncrement = 360.0f / sides;

    for (int i = 0; i < sides; ++i) {
        float angle = glm::radians(i * angleIncrement);

        float x = center.x + radius * std::cos(angle);
        float y = center.y + radius * std::sin(angle);

        vec.push_back(x);
        vec.push_back(y);
    }

    return vec;
}



std::vector<float> BaseGame::GetGameScreenDefaultSize()
{
    //std::vector<float> screenSize = {creatorW, creatorH}; //ZMENA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //return screenSize;

    std::vector<float> screenSize;
    screenSize.push_back(creatorW);
    screenSize.push_back(creatorH);
    return screenSize;
}

bool BaseGame::CheckBtnClicked(float xPos, float yPos, float creatorW, float creatorH, float btnW, float btnH, float btnX, float btnY)
{
    wRatio = (float)nowW / startW;
    hRatio = (float)nowH / startH;
    BaseWindowDiffW = (creatorW - nowW) / 2;
    BaseWindowDiffH = (creatorH - nowH) / 2;

    ratioProjection = glm::ortho(-wRatio, wRatio, -hRatio, hRatio, -1.0f, 1.0f);

    int xRect = btnX;
    int yRect = btnY;
    int xRectLong = btnX + btnW;
    int yRectLong = btnY + btnH;

    glm::vec2 rectPos = glm::vec2(xRect, yRect);
    glm::vec2 newRectPos = glm::vec2();
    glm::vec4 gl_Position = glm::vec4();

    newRectPos.x = rectPos.x - BaseWindowDiffW;
    newRectPos.y = rectPos.y - BaseWindowDiffH;
    gl_Position = ratioProjection * glm::vec4(newRectPos.x * wRatio, newRectPos.y * hRatio, 0.0, 1.0);

    if (xPos >= gl_Position.x && xPos <= gl_Position.x + btnW &&
        yPos >= gl_Position.y && yPos <= gl_Position.y + btnH)
    {
        return true;
    }
    return false;
}


std::string BaseGame::GetTypeOfGame()
{
    return typeOfGame;
}

bool BaseGame::CheckEnterRect(float xPos, float yPos, float creatorW, float creatorH, float btnW, float btnH, float btnX, float btnY)
{
    wRatio = (float)nowW / startW;
    hRatio = (float)nowH / startH;
    BaseWindowDiffW = (creatorW - nowW) / 2;
    BaseWindowDiffH = (creatorH - nowH) / 2;

    ratioProjection = glm::ortho(-wRatio, wRatio, -hRatio, hRatio, -1.0f, 1.0f);

    int xRect = btnX;
    int yRect = btnY;
    int xRectLong = btnX + btnW;
    int yRectLong = btnY + btnH;

    glm::vec2 rectPos = glm::vec2(xRect, yRect);
    glm::vec2 newRectPos = glm::vec2();
    glm::vec4 gl_Position = glm::vec4();

    newRectPos.x = rectPos.x - BaseWindowDiffW;
    newRectPos.y = rectPos.y - BaseWindowDiffH;
    gl_Position = ratioProjection * glm::vec4(newRectPos.x * wRatio, newRectPos.y * hRatio, 0.0, 1.0);

    if (xPos >= gl_Position.x && xPos <= gl_Position.x + btnW &&
        yPos >= gl_Position.y && yPos <= gl_Position.y + btnH)
    {
        return true;
    }
    return false;
}

//std::mt19937& BaseGame::getGenerator() 
//{
//    return gen;
//}





