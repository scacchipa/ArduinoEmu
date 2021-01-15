/***************************************************************
 * Name:      ArduinoEmuApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2021-01-06
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "ArduinoEmuApp.h"
#include "ArduinoEmuMain.h"

IMPLEMENT_APP(ArduinoEmuApp);

bool ArduinoEmuApp::OnInit()
{
    ArduinoEmuFrame* frame = new ArduinoEmuFrame(0L);
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();
    
    return true;
}
