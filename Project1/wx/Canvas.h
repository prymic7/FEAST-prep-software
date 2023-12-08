#pragma once

#include <glew.h>
#include <wx/wx.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <wx/glcanvas.h>
#include "../opengl/programs/ShaderProgram.h"
#include "../opengl/errorHandlers/ErrorHandler.h"
#include "../games/BaseGame.h"
#include "../games/stage1/HeadingConflicts/GameHeadingConflicts.h"
#include "../games/stage1/DividedAttention/GameDividedAttention.h"
#include "../games/stage1/SpotTheSide/GameSpotTheSide.h"
#include "../games/stage1/MemorizePictograms/GameMemorizePictograms.h"
#include "../games/stage1/MemorizePictograms/GameMemorizePictograms.h"
#include "../games/stage1/LearningAndApplying/GameLearningAndApplying.h"
#include "../games/stage1/MultiAttention/GameMultiAttention.h"


class Canvas : public wxGLCanvas
{
public:
    Canvas(wxPanel* parent, const wxGLAttributes& canvasAttrs, int level, std::string game, std::string typeOfGame, std::string typeOfTimer);
    ~Canvas();

    bool InitializeOpenGLFunctions();
    bool InitializeOpenGL();

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnTimer(wxTimerEvent& event);
    void BindEvents();
    void SetPause(bool v);
    bool GetPause();
    void LoadOGLGraphics();

    void MouseMoved(wxMouseEvent& event);
    void MouseDown(wxMouseEvent& event);
    void MouseWheelMoved(wxMouseEvent& event);
    void MouseReleased(wxMouseEvent& event);
    void LeftClick(wxMouseEvent& event);
    void RightClick(wxMouseEvent& event);

    void MouseLeftWindow(wxMouseEvent& event);
    void KeyPressed(wxKeyEvent& event);
    void KeyReleased(wxKeyEvent& event);
    void MouseMove(wxMouseEvent& event);

    void DeleteGame();
    bool GetGameCreated();
    void SetFocusTimerBridge();
    BaseGame* game;


private:
    int level;
    wxPanel* parentPanel; 
    GLenum err;
    wxGLContext* openGLContext;
    bool isOpenGLInitialized{ false };
    bool gameRunning = false;
    std::string typeOfGame;
    std::string typeOfTimer;

    unsigned int VAO, VBO, shaderProgram;
    ShaderProgram* flexibleShader;
    ShaderProgram* staticShader;
    int gameLevel;
    std::string gameName;
    wxTimer timer;
    bool gamePaused = false;
    bool gameCreated;
    bool firstTime = true;
    bool graphicsOK = true;
    bool glewOK = false;
    bool openglOK = false;

    int count = 0;
    //GAMES

};


