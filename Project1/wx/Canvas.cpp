#include "Canvas.h"


Canvas::Canvas(wxPanel* parentPanel, const wxGLAttributes& canvasAttrs, int level, std::string gameName, std::string typeOfGame, std::string typeOfTimer)
    : wxGLCanvas(parentPanel, canvasAttrs)
{
    this->gameName = gameName;
    this->level = level;
    this->parentPanel = parentPanel;
    this->typeOfGame = typeOfGame;
    this->typeOfTimer = typeOfTimer;

    wxGLContextAttrs ctxAttrs;
    ctxAttrs.PlatformDefaults().CoreProfile().OGLVersion(3, 3).EndList();

    openGLContext = new wxGLContext(this, nullptr, &ctxAttrs);
    if (!openGLContext->IsOK())
    {
        wxMessageBox("This sample needs an OpenGL 3.3 capable driver.",
            "OpenGL version error", wxOK | wxICON_INFORMATION, this);
        delete openGLContext;
        openGLContext = nullptr;
    }

    Canvas::BindEvents();
    Canvas::InitializeOpenGL();


    timer.SetOwner(this, wxID_ANY);
    timer.Start(25);
    this->SetFocus();


}

Canvas::~Canvas()
{
    delete flexibleShader;
    delete staticShader;
    delete openGLContext;

}

void Canvas::LoadOGLGraphics()
{
    game->GetGameScreenDefaultSize();
    game->LoadAllGraphics();
    game->LoadFont();
}

void Canvas::DeleteGame()
{
    delete game;
    game = nullptr;
}

bool Canvas::InitializeOpenGLFunctions()
{
    GLenum err = glewInit();

    if (GLEW_OK != err)
    {
        wxLogError("OpenGL GLEW initialization failed: %s", reinterpret_cast<const char*>(glewGetErrorString(err)));
        return false;
        wxLogStatus("rip");
    }
    else
    {
        glewOK = true;
    }

    wxLogDebug("Status: Using GLEW %s", reinterpret_cast<const char*>(glewGetString(GLEW_VERSION)));

    return true;
}

bool Canvas::InitializeOpenGL()
{

    if (!openGLContext)
    {
        return false;
    }
    else
    {
        openglOK = true;
    }

    SetCurrent(*openGLContext);

    if (!InitializeOpenGLFunctions())
    {
        wxMessageBox("Error: Could not initialize OpenGL function pointers.",
            "OpenGL initialization error", wxOK | wxICON_INFORMATION, this);
        return false;
        wxLogStatus("rip");

    }

    wxLogDebug("OpenGL version: %s", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    wxLogDebug("OpenGL vendor: %s", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));

    return true;
}

void Canvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);

    if (!openglOK || !glewOK)
    {
        return;
    }
    SetCurrent(*openGLContext);

    if (graphicsOK)
    {
        if (gameCreated)
        {
            game->Update();
            game->Draw();
        }

    }

    SwapBuffers();
}

void Canvas::OnTimer(wxTimerEvent& event)
{
    Refresh();
    Update();
    game->SetFocusBack(this);
}

void Canvas::OnSize(wxSizeEvent& event)
{

    if (openglOK && glewOK)
    {

        if (firstTime)
        {
            wxSize size = parentPanel->GetClientSize();

            if (gameName == "GameHeadingConflicts")
            {

                game = new GameHeadingConflicts(level, typeOfGame, size.x, size.y, 1100, 650, typeOfTimer);
                Canvas::LoadOGLGraphics();
                gameCreated = true;
            }
            else if (gameName == "GameDividedAttention")
            {
                //game = new GameDividedAttention(level, typeOfGame, 1100, 700, size.x, size.y, typeOfTimer);
                game = new GameDividedAttention(level, typeOfGame, size.x, size.y, 1100, 650, typeOfTimer);

                Canvas::LoadOGLGraphics();
                gameCreated = true;
            }
            else if (gameName == "GameSpotTheSide")
            {
                game = new GameSpotTheSide(2, typeOfGame, 500, 500, 500, 500, typeOfTimer);
                Canvas::LoadOGLGraphics();
                gameCreated = true;
            }
            else if (gameName == "GameMemorizePictograms")
            {
                game = new GameMemorizePictograms(2, typeOfGame, 900, 600, 900, 600, typeOfTimer);
                Canvas::LoadOGLGraphics();
                gameCreated = true;
            }
            else if (gameName == "GameLearningAndApplying")
            {
                game = new GameLearningAndApplying(3, typeOfGame, size.x, size.y, 1100, 650, typeOfTimer);
                Canvas::LoadOGLGraphics();
                gameCreated = true;
            }
            else if (gameName == "GameMultiAttention")
            {
                game = new GameMultiAttention(3, typeOfGame, 1100, 650, 1100, 650, typeOfTimer);
                Canvas::LoadOGLGraphics();
                gameCreated = true;
            }
            firstTime = false;
        }
        if (gameCreated)
        {
            std::vector<float> vec = game->GetStartSize();
            int startW = vec[0];
            int startH = vec[1];
            wxSize clientSize = GetClientSize();
            game->SetScreenSize(clientSize.x, clientSize.y);
            game->HandleViewport(clientSize.x, clientSize.y, game->GetGameScreenDefaultSize()[0], game->GetGameScreenDefaultSize()[1], startW, startH);
            game->HandleShaders(clientSize.x, clientSize.y, game->GetGameScreenDefaultSize()[0], game->GetGameScreenDefaultSize()[1], startW, startH);
        }


    }
    event.Skip();
}

void Canvas::KeyPressed(wxKeyEvent& event)
{
    //count++;
    //wxString str = wxString::Format("%d", count);
    //wxLogStatus(str);
    int keyCode = event.GetKeyCode();

    int plusKey = '+';
    int eCaronKey = 283; // Klíčový kód pro "ě"
    int sCaronKey = 353; // Klíčový kód pro "š"
    int cCaronKey = 269; // Klíčový kód pro "č"


    // Porovnání klíčových kódů
 /*   if (keyCode == 'ě' || keyCode == 'š')
    {
        wxLogStatus("fuk");
    }
    else if (keyCode == eCaronKey)
    {
        wxLogStatus("2");

    }
    else if (keyCode == sCaronKey)
    {
        wxLogStatus("3");

    }
    else if (keyCode == cCaronKey)
    {
        wxLogStatus("4");

    }*/
    game->KeyPressed(event);
}

void Canvas::RightClick(wxMouseEvent& event)
{
    int x = event.GetX();
    int y = event.GetY();
    game->RightClickBtn(x, y);

}

void Canvas::LeftClick(wxMouseEvent& event)
{
    int x = event.GetX();
    int y = event.GetY();
    game->LeftClickBtn(x, y);
}

void Canvas::MouseMove(wxMouseEvent& event)
{
    wxPoint mousePos = event.GetPosition();
    int x = mousePos.x;
    int y = mousePos.y;
    game->HoverButtons(x, y);
}

void Canvas::BindEvents()
{
    Bind(wxEVT_PAINT, &Canvas::OnPaint, this); 
    Bind(wxEVT_SIZE, &Canvas::OnSize, this); 
    Bind(wxEVT_TIMER, &Canvas::OnTimer, this); 
    //Bind(wxEVT_MOTION, &Canvas::MouseMoved, this);
    //Bind(wxEVT_LEFT_DOWN, &Canvas::MouseDown, this); 
    //Bind(wxEVT_MOUSEWHEEL, &Canvas::MouseWheelMoved, this); 
    //Bind(wxEVT_LEFT_UP, &Canvas::MouseReleased, this); 
    Bind(wxEVT_RIGHT_DOWN, &Canvas::RightClick, this);
    Bind(wxEVT_LEFT_DOWN, &Canvas::LeftClick, this);
    Bind(wxEVT_MOTION, &Canvas::MouseMove, this);
    //Bind(wxEVT_ENTER_WINDOW, &Canvas::MouseLeftWindow, this); 
    Bind(wxEVT_KEY_DOWN, &Canvas::KeyPressed, this); 
    //Bind(wxEVT_KEY_UP, &Canvas::KeyReleased, this); 
}

void Canvas::SetPause(bool v)
{
    game->SetPause(v);
    gamePaused = v;
}

bool Canvas::GetPause()
{
    return gamePaused;
}

bool Canvas::GetGameCreated()
{
    return gameCreated;
}



