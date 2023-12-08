#pragma once
#include <wx/wx.h>
//#include "MainFrame.h"

class wxCustomButton : public wxWindow {
public:
    wxCustomButton(wxPanel* parentPanel, int id, wxString string, wxSize size, bool active);
    

        
private:
    bool pressedDown;
    wxString text;
    wxSize size;
    bool active;

    void paintEvent(wxPaintEvent& evt);
    void paintNow();

    void mouseMoved(wxMouseEvent& event);
    void mouseDown(wxMouseEvent& event);
    void mouseWheelMoved(wxMouseEvent& event);
    void mouseReleased(wxMouseEvent& event);
    void rightClick(wxMouseEvent& event);
    void mouseLeftWindow(wxMouseEvent& event);
    void keyPressed(wxKeyEvent& event);
    void keyReleased(wxKeyEvent& event);
    void render(wxDC& dc);

    
    wxDECLARE_EVENT_TABLE();

};

