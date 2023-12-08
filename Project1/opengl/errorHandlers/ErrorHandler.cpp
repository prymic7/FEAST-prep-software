#include "ErrorHandler.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        wxString msg;
        msg.Printf(wxT("[OpenGL error] (%d): %s %s:%d"), error, function, file, line);
        wxMessageBox(msg, wxT("OpenGL Error"), wxOK | wxICON_ERROR);

        return false;
    }
    return true;
}
