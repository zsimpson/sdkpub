/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include <tcl.h>
#include <tk.h>
//#include <tkInt.h>

#ifndef WIN32
//#include <pthread.h>
//#include <sys/types.h>
#include <unistd.h>
//#include <signal.h>
//#include <wait.h>
//#include <stdlib.h>
//#include <string.h>
#endif

#ifndef WIN32
    #define Tk_GetHWND(id) id
#else
    extern "C"
    {
    int Tk_GetHWND(int win);
    }
#endif

#include "cvcam.h"
#include "highgui.h"
#include "demoview.h"

#define SYSTEM_WIN_FROM_TK_WIN(tkwin) Tk_GetHWND(Tk_WindowId(tkwin)) 

char cmd[300];

void    MainEx(int argc, char **argv, Tcl_AppInitProc *pfappInitProc, Tcl_Interp *pintrp,
               char *pchfileName);
int     Tcl_AppInit(Tcl_Interp *pintrp);
void    WishPanic TCL_VARARGS_DEF(char *,arg1);
void    Panic (Tcl_Interp * pintrp, const char * pch);

CLkDemoView view;
CImage lastframe;


static char* module_path;
CvPoint P;

///////////////////////////////////////////////////////////////////////////////
static char* GetPathFromModuleName( char* modulename )
{
    int i;
    if( !modulename )
        return 0;
#ifndef WIN32
    /* if module is link find real path */
    int  len;
    char real[1000];
    strcpy( real, modulename );
    while( (len = readlink( real, real, 1000 )) > 0 )
        real[len] = 0;
    char* path = (char*)malloc( strlen( real ) + 10 );
    strcpy( path, real );
#else
    char* path = (char*)malloc( strlen( modulename ) + 10 );
    strcpy( path, modulename );
#endif

    for( i = strlen( path ) - 1;
         i > 0 && path[i] != '\\' && path[i] != '/';
         i-- );

    if( i <= 0 )
    {
        path[0] = '.';
        i = 1;
    }

    path[i] = '/';
    path[i + 1] = 0;

#ifdef WIN32
    for( i = 0; i < (int)strlen( path ); i++ )
        if( path[i] == '\\' )
            path[i] = '/';
#endif

    return path;
}

// Callback function ----------------------------------------------------------
void testcallback(IplImage* img)
{
    assert (img);
    lastframe.Destroy();
    lastframe.Create(img->width,img->height,24,img->origin);
    lastframe.CopyOf(img);
    
    if (view.m_track) {

        if (!view.m_trackinit) {
            view.StartTracking(lastframe);
            view.m_trackinit = true;
        }

        view.TrackFeatures(lastframe);
        
        //double kx = (double)view.m_w/img->width;
        //double ky = (double)view.m_h/img->height;
        
        if( !view.m_night_mode )
        {
            
        }
        else
        {
            //iplSet( img, 0 );
            CvPoint tl = {0,0};
            CvPoint br = {img->width,img->height};
            //cvRectangle(img, tl, br, 0, (img->width > img->height) ? img->width : img->height);
            //cvRectangle(img, tl, br, 0, 255);
            memset(img->imageData,0,img->imageSize);
        }
        
        int i, count = view.m_tracker.GetCount();
        const PointArray& array = view.m_tracker.GetPoints();

        cvCircle( img, P, cvRound(3), CV_RGB(0,0,255));
                
        for( i = 0; i < count; i++ )
        {
            CvPoint pt;
            int color;
            if( i != view.m_moved_idx )
            {
                pt = cvPoint( cvRound(array[i].x), cvRound(array[i].y));
                color = CV_RGB(0,255,0);
            }
            else
            {
                pt = cvPoint( cvRound(view.m_moved_point.x),
                    cvRound(view.m_moved_point.y));
                color = CV_RGB(255,0,0);
            }
            cvCircle( img, pt, 1, color, CV_FILLED );
        }
    }
    else
    {
        if  (view.m_trackinit)
        {
            view.StopTracking();
            view.m_trackinit = false;
        }
    }
    
#ifdef WIN32
    Sleep(10);
#endif
}
//-----------------------------------------------------------------------------

/*
 *----------------------------------------------------------------------
 *
 * Commands routines.
 *
 * Results:
 *  TCL_OK - if sucsess, or TCL_ERROR
 *
 *----------------------------------------------------------------------
 */

int Init_Camera (ClientData, Tcl_Interp *interp,
    int, char **argv)
{
    cvcamWindow mainwin;
    int ncameras,ret;
    Tk_Window win;
    char com[1000]="set dlg [Dialog .dlg -parent . -modal local -separator 1 -title   \"Choice of cameras\" \
                   -side bottom -anchor  s -default 0]";
    CameraDescription cd;
    
    ncameras = cvcamGetCamerasCount();

    if (ncameras==0) 
    {
        Tcl_Eval(interp,"tk_dialog .pattern {Error} { Cameras not found.} {} 0 OK");
        return TCL_ERROR;
    }
  
    ret = Tcl_Eval(interp,com);

    strcpy(com,"$dlg add -name ok -width 5");
    ret = Tcl_Eval(interp,com);

    strcpy(com, "set top [$dlg getframe]");
    ret = Tcl_Eval(interp,com);

    strcpy(com, "label $top.lab1 -text \"Several cameras has found in your system. Choose one of them.\" \n\
                pack $top.lab1 -side top -anchor nw" );
    ret = Tcl_Eval(interp,com);
                
    strcpy(com, "label $top.lab2 -text \"\" \n\
                pack $top.lab2 -side top -anchor nw");
    ret = Tcl_Eval(interp,com);

    strcpy(com, "label $top.lab3 -text \"Cameras:\" \n\
                 pack $top.lab3 -side top -anchor nw");
    ret = Tcl_Eval(interp,com);

    strcpy(com, "ComboBox $top.cb -width 50 -height 4 -editable no -modifycmd CVLkDemo::Modify");
    ret = Tcl_Eval(interp,com);
    
    strcpy(com, "pack $top.cb -side top");
    ret = Tcl_Eval(interp,com);

    strcpy(com, "$top.cb configure -values {");
    for (int i=0; i<ncameras; i++)
    {        
        cvcamGetProperty(i, CVCAM_DESCRIPTION, (void*)&cd);
        strcat(com,"\"");
        strcat(com,cd.DeviceDescription);
        strcat(com,"\" ");
    }
    strcat(com,"}");
    ret = Tcl_Eval(interp, com);

    strcpy(com,"$top.cb setvalue @0 \n CVLkDemo::Modify \n set ret [$dlg draw]");
    ret = Tcl_Eval(interp, com);

    strcpy(com,"destroy $dlg");
    ret = Tcl_Eval(interp, com);
    
    ret = Tcl_Eval(interp, "set tmp $CVLkDemo::cam");
    int n = atoi(interp->result);

    ret = Tcl_Eval(interp, "set f $CVLkDemo::curframe");
        
    win = Tk_NameToWindow(interp, interp->result, 
        Tk_MainWindow(interp));
    
    Tk_MapWindow(win);
    int w = Tk_Width(win);
    int h = Tk_Height(win);
 
    mainwin = SYSTEM_WIN_FROM_TK_WIN(win);
    int prop;
    
    cvcamSetProperty(n, CVCAM_PROP_ENABLE, CVCAMTRUE);
    cvcamSetProperty(n, CVCAM_PROP_RENDER, CVCAMTRUE);
    cvcamSetProperty(n, CVCAM_PROP_WINDOW,  &mainwin);
    cvcamSetProperty(n, CVCAM_PROP_CALLBACK, (void*)testcallback);
    cvcamSetProperty(n, CVCAM_RNDWIDTH, (void*)&w);
    cvcamSetProperty(n, CVCAM_RNDHEIGHT, (void*)&h);
    view.SetSize(w,h);

    cvcamInit();
    cvcamGetProperty(n, CVCAM_DESCRIPTION, (void*)&cd);
    sprintf(com,"set CVLkDemo::curcam \"%s\"",cd.DeviceDescription);
    Tcl_Eval(interp, com);
        
    return TCL_OK;
}

int Close_Camera (ClientData, Tcl_Interp *interp,
                  int, char **argv)
{
    view.m_started = false;
    cvcamExit();
    return TCL_OK;
}

int Start_Camera (ClientData, Tcl_Interp *interp,
                 int, char **argv)
{
    view.m_started = true;
    cvcamStart();
    return TCL_OK;
}

int Stop_Camera (ClientData, Tcl_Interp *interp,
                  int, char **argv)
{
    view.m_started = false;
    cvcamStop();
    return TCL_OK;
}

int Set_Track (ClientData, Tcl_Interp *interp,
                 int, char **argv)
{
    view.m_track = true;
    //view.StartTracking(lastframe);
    return TCL_OK;
}

int Reset_Track (ClientData, Tcl_Interp *interp,
               int, char **argv)
{
    //view.StopTracking();
    view.m_track = false;

    return TCL_OK;
}

int Set_Night (ClientData, Tcl_Interp *interp,
               int, char **argv)
{
    view.m_night_mode = true;
    return TCL_OK;
}

int Reset_Night (ClientData, Tcl_Interp *interp,
                 int, char **argv)
{
    view.m_night_mode = false;
        
    return TCL_OK;
}

int Set_Video (ClientData, Tcl_Interp *interp,
               int, char **argv)
{
    void *p;
    cvcamGetProperty(0,CVCAM_VIDEOFORMAT, p);

    return TCL_OK;
}

int Set_CameraOpt (ClientData, Tcl_Interp *interp,
               int, char **argv)
{
    void *p;
    cvcamGetProperty(0,CVCAM_CAMERAPROPS, p);
    
    return TCL_OK;
}

int Button_Press (ClientData, Tcl_Interp *interp,
               int, char **argv)
{
    CvPoint p;
    p.x = atoi(argv[1]);
    p.y = atoi(argv[2]);
#ifdef WIN32    
    p.y = view.m_h - p.y;
#endif
    P = view.ConvertScreenToImage(p);

    if (view.m_track)
    {
        int index = view.FindPoint(P);
        if( index > 0 )
        {
            view.m_moved_idx = index;
            view.m_moved_point = P;
        }
        else if( view.m_gray.GetImage() )
        {
            view.m_tracker.AddPoint( P, view.m_gray );
        }
    }
    return TCL_OK;
}

int Button_Release (ClientData, Tcl_Interp *interp,
                  int, char **argv)
{
    CvPoint p;
    p.x = atoi(argv[1]);
    p.y = atoi(argv[2]);
#ifdef WIN32    
    p.y = view.m_h - p.y;
#endif

    
    if (view.m_track)
    {
        if( view.m_moved_idx > 0 && view.m_gray.GetImage() )
        {
            view.m_tracker.MovePoint( view.m_moved_idx, view.m_moved_point, view.m_gray );
            view.m_moved_idx = -1;
        }
    }
    
    return TCL_OK;
}

int Motion (ClientData, Tcl_Interp *interp,
                    int, char **argv)
{
    CvPoint p;
    p.x = atoi(argv[1]); 
    p.y = atoi(argv[2]);
#ifdef WIN32    
    p.y = view.m_h - p.y;
#endif
    P = view.ConvertScreenToImage(p);
    if (view.m_track)
    {
        if( view.m_moved_idx > 0 && view.m_gray.GetImage() )
        {
            view.m_moved_point.x = P.x;
            view.m_moved_point.y = P.y;
        }
    }
    
    return TCL_OK;
}

int Configure (ClientData, Tcl_Interp *interp,
            int, char **argv)
{
    if (view.m_started)
    {
        Tk_Window win;
        Tcl_Eval(interp, "set f $CVLkDemo::curframe");
    
        win = Tk_NameToWindow(interp, interp->result, 
            Tk_MainWindow(interp));
    
        Tk_MapWindow(win);
        int w = Tk_Width(win);
        int h = Tk_Height(win);
    
        cvcamSetProperty(0, CVCAM_RNDWIDTH, (void*)&w);
        cvcamSetProperty(0, CVCAM_RNDHEIGHT, (void*)&h);
        view.SetSize(w,h);
    }
    
    return TCL_OK;
}


//-----------------------------------------------------------------------------

/*
 *----------------------------------------------------------------------
 *
 * Commands_Init -- Commands initialisation routine.
 *
 * Results:
 *  TCL_OK - if sucsess, or TCL_ERROR
 *
 *----------------------------------------------------------------------
 */
int
Commands_Init(Tcl_Interp *interp)
{
    Tcl_CreateCommand (interp, "pInitCamera", Init_Camera,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pStartCamera", Start_Camera,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pCloseCamera", Close_Camera,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pStopCamera", Stop_Camera,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pSetTrack", Set_Track,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pResetTrack", Reset_Track,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pSetNight", Set_Night,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pResetNight", Reset_Night,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pSetVideo", Set_Video,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pButtonPress", Button_Press,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pButtonRelease", Button_Release,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pMotion", Motion,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pSetCameraOpt", Set_CameraOpt,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pConfigure", Configure,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    
    
    return TCL_OK;
}


/*
 *----------------------------------------------------------------------
 *
 * MainEx -- Main program for Tk-based applications.
 *
 *----------------------------------------------------------------------
 */
void
MainEx( int argc, char** argv, Tcl_AppInitProc *appInitProc,
        Tcl_Interp *pintrp, char *fileName )
{
    int code;

    (*appInitProc)(pintrp);

    if ( Commands_Init(pintrp) != TCL_OK) 
        Panic (pintrp,"Can't initialise commands!");

    char set_path[1000];
    strcat( strcat( strcpy( set_path, "set ::image_path \"" ), module_path ), "\"" );
    code = Tcl_Eval( pintrp, set_path );
    
    if (fileName != NULL) 
    {
        char  script[1000];
        strcat( strcat( strcpy( script, module_path ), "" ), fileName );
        code = Tcl_EvalFile(pintrp, script);
        if (code != TCL_OK)
            Panic (pintrp,"Evaluate file error!");
    }
    else Tcl_SourceRCFile(pintrp);

    Tcl_ResetResult(pintrp);

    Tk_MainLoop();
    
    Tcl_DeleteInterp(pintrp);
    return;
}

/*
 *----------------------------------------------------------------------
 *
 * WishPanic -- escape function.
 *
 *----------------------------------------------------------------------
 */

void WishPanic TCL_VARARGS_DEF(char *,arg1)
{
    va_list argList;
    char buf[1024];
    char *format;

    format = TCL_VARARGS_START(char *,arg1,argList);
    printf(buf, format, argList);
}

/*
 *----------------------------------------------------------------------
 *
 * Panic -- error output & exit function.
 *
 *----------------------------------------------------------------------
 */

void Panic (Tcl_Interp * pintrp, const char * pch)
{
    printf("Thread %P:",Tcl_GetCurrentThread());
    printf(pch);
    printf("\n    Reason:");
    printf(pintrp->result);
    printf("\n");

    Tcl_DeleteInterp(pintrp);
    Tcl_Exit(1);
}

/*void Panic (Tcl_Interp * pintrp, const char * pch)
{
    char buf[2048];
    sprintf(buf, "\nThread %p, Interpetator %p:\n",
        Tcl_GetCurrentThread(), pintrp);
    
    Tcl_AddErrorInfo(pintrp, buf);
    Tcl_AddErrorInfo(pintrp, pch);
    TkpDisplayWarning(Tcl_GetVar(pintrp, "errorInfo",
    TCL_GLOBAL_ONLY), "Error in startup script");
    Tcl_DeleteInterp(pintrp);
    Tcl_Exit(1);
}*/

/*
 *----------------------------------------------------------------------
 *
 * Tcl_AppInit -- Initialisation function.
 *
 *----------------------------------------------------------------------
 */

int Tcl_AppInit(Tcl_Interp *pintrp)
{

    if (Tcl_InitStubs(pintrp, TCL_VERSION, 1) == NULL)
        Panic (pintrp,"Tcl stub's initialisation failed!");
        
    if (Tcl_Init(pintrp) == TCL_ERROR)
        Panic (pintrp,"Tcl's initialisation failed!");
    
    if (Tk_Init(pintrp) == TCL_ERROR)
        Panic (pintrp,"Tk's initialisation failed!");

    return TCL_OK;
}

// main body ------------------------------------------------------------------

int main(int argc, char* argv[])
{
    module_path = GetPathFromModuleName( argv[0] );

    Tcl_Interp* g_pInterp = Tcl_CreateInterp();
    
    Tcl_SetPanicProc(WishPanic);
    Tcl_FindExecutable(argv[0]);

    MainEx(argc, argv, Tcl_AppInit, g_pInterp, "cvlkdemo.tcl");

    cvcamExit();

    return 0;
}
