/***************************************************************
 * Name:      ArduinoEmuMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2021-01-06
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef ARDUINOEMUMAIN_H
#define ARDUINOEMUMAIN_H



#include "ArduinoEmuApp.h"


#include "GUIFrame.h"

class ArduinoEmuFrame: public GUIFrame
{
    public:
        ArduinoEmuFrame(wxFrame *frame);
        ~ArduinoEmuFrame();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
};

#endif // ARDUINOEMUMAIN_H
