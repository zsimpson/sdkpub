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
#include <stdlib.h>

#ifndef WIN32
#include <unistd.h>
#endif

#ifndef WIN32
    #define Tk_GetHWND(id) id
#else
    extern "C"
    {
    int Tk_GetHWND(int win);
    }
#endif

#include <math.h>
#include <string.h>
#include "cvcam.h"
#include "csdemoview.h"

#define SYSTEM_WIN_FROM_TK_WIN(tkwin) Tk_GetHWND(Tk_WindowId(tkwin))

char cmd[300];

void    MainEx(int argc, char ** /*argv*/, Tcl_AppInitProc *pfappInitProc, Tcl_Interp *pintrp,
               char *pchfileName);
int     Tcl_AppInit(Tcl_Interp *pintrp);
void    WishPanic TCL_VARARGS_DEF(char *,arg1);
void    Panic (Tcl_Interp * pintrp, const char * pch);

CCsDemoView view;
CvImage limage;
bool g_created = false;
bool g_pressed = false;
bool g_paused = false;

int camtype = -1;

int X,Y;
cvcamWindow mainwin;

static char* module_path;
CvPoint P;

cvcamAVIFILE avifile = (cvcamAVIFILE)-1;


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

//----------------------------------------------------------------------------

void  CheckBackProject( CvImage* image )
{
    if( view.m_params.view == 1 )
    {
        IplImage* src = view.m_cCamShift.get_back_project();
        if( src && src->imageData && image )
        {
            //iplGrayToColor( src, image, 0, 0, 0 );
            cvCvtPlaneToPix( src, src, src, 0, image);
        }
    }
    else if( view.m_params.view == 2 && view.m_track)
    {
        int i, dims;
        CvSize size;

        view.m_cCamShift.get_hist_dims( &dims );
        cvGetImageRawData( image, 0, 0, &size );

        for( i = 0; i < dims; i++ )
        {
            int val = view.m_cCamShift.query(i);
            CvPoint p[4];

            p[0].x = p[1].x = i*size.width/(2*dims);
            p[2].x = p[3].x = (i+1)*size.width/(2*dims);

            p[1].y = p[2].y = 0;
            p[0].y = p[3].y = (val*size.height)/(3*255);

            cvFillConvexPoly( image, p, 4, CV_RGB(255,0,0));
        }
    }
}


void  DrawCross( CvImage* image )
{
    float cs = (float)cos( view.m_cCamShift.get_orientation() );
    float sn = (float)sin( view.m_cCamShift.get_orientation() );

    int x = view.m_object.x + view.m_object.width / 2;
    int y = view.m_object.y + view.m_object.height / 2;

    CvPoint p1 = {(int)(x + view.m_cCamShift.get_length() * cs / 2),
        (int)(y + view.m_cCamShift.get_length() * sn / 2)};
    CvPoint p2 = {(int)(x - view.m_cCamShift.get_length() * cs / 2),
        (int)(y - view.m_cCamShift.get_length() * sn / 2)};
    CvPoint p3 = {(int)(x + view.m_cCamShift.get_width() * sn / 2),
        (int)(y - view.m_cCamShift.get_width() * cs / 2)};
    CvPoint p4 = {(int)(x - view.m_cCamShift.get_width() * sn / 2),
        (int)(y + view.m_cCamShift.get_width() * cs / 2)};
    cvLine( image, p1, p2, CV_RGB(255,255,0) );
    cvLine( image, p4, p3, CV_RGB(255,255,0) );
}

void  ApplyCamShift( CvImage* image, bool initialize )
{
    CvSize size;
    int bins = view.m_params.bins;

    view.m_cCamShift.set_hist_dims( 1, &bins );
    view.m_cCamShift.set_thresh( 0, 1, 180 );
    view.m_cCamShift.set_threshold( 0 );
    view.m_cCamShift.set_min_ch_val( 1, view.m_params.Smin );
    view.m_cCamShift.set_max_ch_val( 1, 255 );
    view.m_cCamShift.set_min_ch_val( 2, view.m_params.Vmin );
    view.m_cCamShift.set_max_ch_val( 2, view.m_params.Vmax );

    cvGetImageRawData( image, 0, 0, &size );

    if( view.m_object.x < 0 ) view.m_object.x = 0;
    if( view.m_object.x > size.width - view.m_object.width - 1 )
        view.m_object.x = MAX(0, size.width - view.m_object.width - 1);

    if( view.m_object.y < 0 ) view.m_object.y = 0;
    if( view.m_object.y > size.height - view.m_object.height - 1 )
        view.m_object.y = MAX(0, size.height - view.m_object.height - 1);

    if( view.m_object.width > size.width - view.m_object.x )
        view.m_object.width = MIN(size.width, size.width - view.m_object.x);

    if( view.m_object.height > size.height - view.m_object.y )
        view.m_object.height = MIN(size.height, size.height - view.m_object.y);
    view.m_cCamShift.set_window(view.m_object);

    if( initialize )
    {
        view.m_cCamShift.reset_histogram();
        view.m_cCamShift.update_histogram( image );
    }

    view.m_cCamShift.track_object( image );
    view.m_object = view.m_cCamShift.get_window();
}

// Callback function ----------------------------------------------------------
void testcallback(IplImage* img)
{
    CvSize imgsize = view.SetImgSize( img->width, img->height );
    int stride = (imgsize.width * 3 + 3) & -4;

    cvInitImageHeader( &limage, imgsize, IPL_DEPTH_8U, 3, IPL_ORIGIN_TL, 4, 1 );
    //cvSetImageData( &image, pData,stride );
    cvSetImageData( &limage, img->imageData,stride );

    if(view.m_track == false)
    {
        if(view.m_init == false)
        {
            CvPoint p1, p2;
            // Draw box
            p1.x = cvRound( imgsize.width * view.m_params.x );
            p1.y = cvRound( imgsize.height * view.m_params.y );

            p2.x = cvRound( imgsize.width * (view.m_params.x + view.m_params.width));
            p2.y = cvRound( imgsize.height * (view.m_params.y + view.m_params.height));

            CheckBackProject( &limage );
            cvRectangle( &limage, p1, p2, -1, 1 );
            cvCircle(&limage, p1, 1, CV_RGB(255,0,0), 1);

            view.m_cCamShift.set_window(view.m_object);
        }
        else
        {
            view.m_object.x = cvRound( imgsize.width * view.m_params.x );
            view.m_object.y = cvRound( imgsize.height * view.m_params.y );

            view.m_object.width = cvRound( imgsize.width * view.m_params.width );
            view.m_object.height = cvRound( imgsize.height * view.m_params.height );


            if( view.m_object.x < 0 ) view.m_object.x = 0;
            if( view.m_object.x > imgsize.width - view.m_object.width - 1 )
                view.m_object.x = MAX(0, imgsize.width - view.m_object.width - 1);

            if( view.m_object.y < 0 ) view.m_object.y = 0;
            if( view.m_object.y > imgsize.height - view.m_object.height - 1 )
                view.m_object.y = MAX(0, imgsize.height - view.m_object.height - 1);

            if( view.m_object.width > imgsize.width - view.m_object.x )
                view.m_object.width = MIN(imgsize.width, imgsize.width - view.m_object.x);

            if( view.m_object.height > imgsize.height - view.m_object.y )
                view.m_object.height = MIN(imgsize.height, imgsize.height - view.m_object.y);

            view.m_cCamShift.set_window(view.m_object);

            ApplyCamShift( &limage, true );
            CheckBackProject( &limage );

            view.m_track = true;
        }
    }
    else
    {
        ApplyCamShift( &limage, false );
        CheckBackProject( &limage );

        DrawCross( &limage );

        CvPoint p1, p2;
        // Draw box
        p1.x = cvRound( imgsize.width * view.m_params.x );
        p1.y = cvRound( imgsize.height * view.m_params.y );

        p2.x = cvRound( imgsize.width * (view.m_params.x + view.m_params.width));
        p2.y = cvRound( imgsize.height * (view.m_params.y + view.m_params.height));

        cvRectangle( &limage, p1, p2, CV_RGB(0,0,255), 1 );
        cvCircle(&limage, p1, 1, CV_RGB(255,0,0), 1);
    }
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
                 int, char **)
{
    int ncameras, ret;
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


    if (ncameras > 1)
    {
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

        strcpy(com, "ComboBox $top.cb -width 50 -height 4 -editable no -modifycmd CVCsDemo::Modify");
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

        strcpy(com,"$top.cb setvalue @0 \n CVCsDemo::Modify \n set ret [$dlg draw]");
        ret = Tcl_Eval(interp, com);

        strcpy(com,"destroy $dlg");
        ret = Tcl_Eval(interp, com);

        ret = Tcl_Eval(interp, "set tmp $CVCsDemo::cam");

        avifile = atoi(interp->result);
    }
    else
    {
        avifile=0;
    }

    ret = Tcl_Eval(interp, "set f $CVCsDemo::curframe");

    win = Tk_NameToWindow(interp, interp->result,
        Tk_MainWindow(interp));

    Tk_MapWindow(win);
    int w = Tk_Width(win);
    int h = Tk_Height(win);

    mainwin = SYSTEM_WIN_FROM_TK_WIN(win);

    cvcamSetProperty(avifile, CVCAM_PROP_ENABLE, CVCAMTRUE);
    cvcamSetProperty(avifile, CVCAM_PROP_RENDER, CVCAMTRUE);
    cvcamSetProperty(avifile, CVCAM_PROP_WINDOW,  &mainwin);
    cvcamSetProperty(avifile, CVCAM_PROP_CALLBACK, (void*)testcallback);
    cvcamSetProperty(avifile, CVCAM_RNDWIDTH, (void*)&w);
    cvcamSetProperty(avifile, CVCAM_RNDHEIGHT, (void*)&h);
    view.SetVwSize(w,h);

    cvcamInit();
    camtype = 1;
    g_created = true;
    cvcamGetProperty(avifile, CVCAM_DESCRIPTION, (void*)&cd);
    sprintf(com,"set CVCsDemo::curcam \"%s\"",cd.DeviceDescription);
    Tcl_Eval(interp, com);

    return TCL_OK;
}

int Close_Camera (ClientData, Tcl_Interp * /*interp*/,
                  int, char ** /*argv*/)
{
    view.m_start = false;
    g_created = false;
    cvcamExit();
    camtype = -1;
    avifile = (cvcamAVIFILE)-1;
    return TCL_OK;
}

int Start_Camera (ClientData, Tcl_Interp * /*interp*/,
                 int, char ** /*argv*/)
{
    view.m_start = true;

    cvcamStart();
    return TCL_OK;
}

int Stop_Camera (ClientData, Tcl_Interp * /*interp*/,
                  int, char ** /*argv*/)
{
    view.m_start = false;

    cvcamStop();
    return TCL_OK;
}
#ifndef __WIN32
#define __stdcall
#endif

unsigned __stdcall thread_main(void * data)
{
    CvSize sz;
    sz = view.GetVwSize();
    return cvcamPlayAVI(0,
                        data,
                        sz.width,
                        sz.height,
                        (void*)testcallback);
}

int Init_Avi (ClientData, Tcl_Interp *interp,
                 int, char ** /*argv*/)
{
    int ret;
    Tk_Window win;

    char * val = Tcl_GetVar(interp, "CVCsDemo::pagesnum", TCL_GLOBAL_ONLY);

    if ( *val != '0' )
    {
        Tcl_Eval(interp, "tk_dialog .mes {Message} { CVCsDemo support only one tracker.} {} 0 OK");
        return TCL_OK;
    }

    avifile = cvcamAVIOpenFile(NULL);
    if (avifile == -1)
    {
        Tcl_Eval( interp, "tk_dialog .mes {Error} { Can't open file.} {} 0 OK");
        return TCL_OK;
    }

    char com_ok[] = "incr CVCsDemo::pagescount \n"
                    "incr CVCsDemo::pagesnum\n"
                    "set CVCsDemo::avistate \"1\" \n"
                    "CVCsDemo::longmenu 1 \n"
                    "CVCsDemo::longbar 1 \n"
                    "CVCsDemo::longstbar 1 \n"
                    "set CVCsDemo::curpage p[expr $CVCsDemo::pagescount] \n"
                    "lappend CVCsDemo::pages $CVCsDemo::curpage \n"
                    "lappend CVCsDemo::cams \"AVI\" \n"
                    "set text [format \"AVI %i\" $CVCsDemo::pagescount] \n"
                    "CVCsDemo::createtab $CVCsDemo::curpage $text \n"
                    "$CVCsDemo::nb see [$CVCsDemo::nb pages end] \n"
                    "$CVCsDemo::nb raise [$CVCsDemo::nb pages end] \n"
                    "update \n"
                    "set CVCsDemo::capturestate 0 \n"
                    "$CVCsDemo::tb.bbox2.b0 configure -state active \n"
                    "$CVCsDemo::tb.bbox2.b1 configure -state disable \n"
                    "$CVCsDemo::tb.bbox2.b2 configure -state disable ";

    ret = Tcl_Eval(interp, com_ok);

    ret = Tcl_Eval(interp, "set f $CVCsDemo::curframe");
    win = Tk_NameToWindow(interp, interp->result,
        Tk_MainWindow(interp));

    Tk_MapWindow(win);
    int w = Tk_Width(win);
    int h = Tk_Height(win);

    mainwin = SYSTEM_WIN_FROM_TK_WIN(win);

    cvcamSetProperty(avifile, CVCAM_PROP_ENABLE, CVCAMTRUE);
    cvcamSetProperty(avifile, CVCAM_PROP_RENDER, CVCAMTRUE);
    cvcamSetProperty(avifile, CVCAM_PROP_WINDOW,  &mainwin);
    cvcamSetProperty(avifile, CVCAM_PROP_CALLBACK, (void*)testcallback);
    cvcamSetProperty(avifile, CVCAM_RNDWIDTH, (void*)&w);
    cvcamSetProperty(avifile, CVCAM_RNDHEIGHT, (void*)&h);
    view.SetVwSize(w,h);

    sprintf(com_ok,"set CVCsDemo::curcam \"%s\"", "AVI");
    Tcl_Eval(interp, com_ok);

    g_created = true;
    camtype = 0;

    return TCL_OK;
}

int Pause_Camera (ClientData, Tcl_Interp * /*interp*/,
                  int, char ** /*argv*/)
{
    g_paused = true;
    cvcamPause();

    return TCL_OK;
}

int Resume_Camera (ClientData, Tcl_Interp * /*interp*/,
                   int, char ** /*argv*/)
{
    g_paused = false;
    cvcamResume();

    return TCL_OK;
}

int Pause_Avi (ClientData, Tcl_Interp * /*interp*/,
               int, char ** /*argv*/)
{
    g_paused = true;
    cvcamAVIPause(avifile);

    return TCL_OK;
}

int Resume_Avi (ClientData, Tcl_Interp * /*interp*/,
                int, char ** /*argv*/)
{
    g_paused = false;
    cvcamAVIResume(avifile);

    return TCL_OK;
}

int Stop_Avi (ClientData, Tcl_Interp * /*interp*/,
              int, char ** /*argv*/)
{
    g_created = false;
    view.m_start = false;
    cvcamAVICloseFile(avifile);
    avifile = (cvcamAVIFILE)-1;
    camtype = -1;

    return TCL_OK;
}


int Start_Avi (ClientData, Tcl_Interp *interp,
                 int, char ** /*argv*/)
{
    int ret;
    Tk_Window win;

    ret = Tcl_Eval(interp, "set f $CVCsDemo::curframe");
    win = Tk_NameToWindow(interp, interp->result,
        Tk_MainWindow(interp));

    Tk_MapWindow(win);
    int w = Tk_Width(win);
    int h = Tk_Height(win);

    mainwin = SYSTEM_WIN_FROM_TK_WIN(win);
    view.SetVwSize(w,h);

    ret = cvcamAVISetWindow(avifile, &mainwin);
    ret = cvcamAVISetCallback(avifile,(void*)testcallback);
    ret = cvcamAVISetSize(avifile, w, h);

    ret = cvcamAVIRun(avifile);

    view.m_start = true;

    return TCL_OK;
}

int Set_Track (ClientData, Tcl_Interp * /*interp*/,
               int, char ** /*argv*/)
{
    view.m_init = true;
    view.m_track = false;
    view.m_params.view = 0;

    return TCL_OK;
}

int Reset_Track (ClientData, Tcl_Interp * /*interp*/,
               int, char ** /*argv*/)
{
    view.m_init =  view.m_track = false;

    return TCL_OK;
}

int Set_Night (ClientData, Tcl_Interp * /*interp*/,
               int, char ** /*argv*/)
{
    view.m_params.view = 1;
    return TCL_OK;
}

int Reset_Night (ClientData, Tcl_Interp * /*interp*/,
                 int, char ** /*argv*/)
{
    view.m_params.view = 0;
    return TCL_OK;
}

int Set_Hist (ClientData, Tcl_Interp * /*interp*/,
               int, char ** /*argv*/)
{
    view.m_params.view = 2;
    return TCL_OK;
}

int Reset_Hist (ClientData, Tcl_Interp * /*interp*/,
                 int, char ** /*argv*/)
{
    view.m_params.view = 0;
    return TCL_OK;
}

int Set_Video (ClientData, Tcl_Interp * /*interp*/,
               int, char ** /*argv*/)
{
    void *p = 0;
    cvcamGetProperty(0,CVCAM_VIDEOFORMAT, p);

    return TCL_OK;
}

int Set_CameraOpt (ClientData, Tcl_Interp * /*interp*/,
               int, char ** /*argv*/)
{
    void *p = 0;
    cvcamGetProperty(0,CVCAM_CAMERAPROPS, p);

    return TCL_OK;
}

int Button_Press (ClientData, Tcl_Interp * /*interp*/,
               int, char ** argv)
{
    if (view.m_start)
    {
        CvPoint p,imgp;
        p.x = atoi(argv[1]);
        p.y = atoi(argv[2]);
    #ifdef WIN32
        p.y = view.m_VwSize.height - p.y;
    #endif
        CvSize imgsize = view.GetImgSize();

        imgp = view.ConvertViewToImage(p);
        X = view.m_object.x = imgp.x;
        Y = view.m_object.y = imgp.y;

        view.m_params.x = ((float)imgp.x) / imgsize.width ;
        view.m_params.y = ((float)imgp.y) / imgsize.height ;

        g_pressed = true;
    }
    return TCL_OK;
}

int Button_Release (ClientData, Tcl_Interp * /*interp*/,
                  int, char ** /*argv*/)
{
    if (view.m_start)
    {
        g_pressed = false;
        if (view.m_track)
        {
            view.m_init  = true;
            view.m_track = false;
        }
    }

    return TCL_OK;
}

int Motion (ClientData, Tcl_Interp * /*interp*/,
                    int, char ** argv)
{
    if (view.m_start)
    {
        if (g_pressed)
        {

            CvPoint p,imgp;
            p.x = atoi(argv[1]);
            p.y = atoi(argv[2]);
    #ifdef WIN32
            p.y = view.m_VwSize.height - p.y;
    #endif
            CvSize imgsize = view.GetImgSize();

            imgp = view.ConvertViewToImage(p);

            view.m_object.width  = abs(imgp.x - X);
            view.m_object.height = abs(imgp.y - Y);


            if (view.m_object.width == 0)
            {
                view.m_object.width = 1;
                X--;
            }

            if (view.m_object.height == 0)
            {
                view.m_object.height = 1;
                Y--;
            }

            if (imgp.x < X)
                view.m_object.x = imgp.x;
            if (imgp.y < Y)
                view.m_object.y = imgp.y;

            if( view.m_object.x < 0 ) view.m_object.x = 0;
            if( view.m_object.x > imgsize.width - view.m_object.width - 1 )
                view.m_object.x = MAX(0, imgsize.width - view.m_object.width - 1);

            if( view.m_object.y < 0 ) view.m_object.y = 0;
            if( view.m_object.y > imgsize.height - view.m_object.height - 1 )
                view.m_object.y = MAX(0, imgsize.height - view.m_object.height - 1);

            if( view.m_object.width > imgsize.width - view.m_object.x )
                view.m_object.width = MIN(imgsize.width, imgsize.width - view.m_object.x);

            if( view.m_object.height > imgsize.height - view.m_object.y )
                view.m_object.height = MIN(imgsize.height, imgsize.height - view.m_object.y);

            view.m_params.x = ((float)view.m_object.x) / imgsize.width ;
            view.m_params.y = ((float)view.m_object.y) / imgsize.height ;
            view.m_params.width  = ((float)view.m_object.width) / imgsize.width;
            view.m_params.height  = ((float)view.m_object.height) / imgsize.height;

            view.m_cCamShift.set_window(view.m_object);
        }
    }

    return TCL_OK;
}

int Configure (ClientData, Tcl_Interp *interp,
            int, char ** /*argv*/)
{
    if (g_created)
    {
        Tk_Window win;
        Tcl_Eval(interp, "set f $CVCsDemo::curframe");

        win = Tk_NameToWindow(interp, interp->result,
            Tk_MainWindow(interp));

        Tk_MapWindow(win);
        int w = Tk_Width(win);
        int h = Tk_Height(win);

        cvcamSetProperty(avifile, CVCAM_RNDWIDTH, (void*)&w);
        cvcamSetProperty(avifile, CVCAM_RNDHEIGHT, (void*)&h);

        view.SetVwSize(w,h);
    }

    return TCL_OK;
}

int Set_Bins (ClientData, Tcl_Interp * /*interp*/,
               int, char ** argv )
{
    view.m_params.bins = atoi(argv[1]);

    if (view.m_track)
    {
        view.m_init  = true;
        view.m_track = false;
    }
    return TCL_OK;
}

int Set_S (ClientData, Tcl_Interp * /*interp*/,
              int, char ** argv)
{
    view.m_params.Smin = atoi(argv[1]);
    return TCL_OK;
}

int Set_V1 (ClientData, Tcl_Interp * /*interp*/,
              int, char ** argv)
{
    view.m_params.Vmin = atoi(argv[1]);
    return TCL_OK;
}

int Set_V2 (ClientData, Tcl_Interp * /*interp*/,
              int, char ** argv )
{
    view.m_params.Vmax = atoi(argv[1]);
    return TCL_OK;
}

//-----------------------------------------------------------------------------

/*
 *----------------------------------------------------------------------
 *
 * Commands_Init --	Commands initialisation routine.
 *
 * Results:
 *	TCL_OK - if sucsess, or TCL_ERROR
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

    Tcl_CreateCommand (interp, "pInitAvi", Init_Avi,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pStartAvi", Start_Avi,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pStopAvi", Stop_Avi,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);

    Tcl_CreateCommand (interp, "pSetTrack", Set_Track,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pResetTrack", Reset_Track,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pSetNight", Set_Night,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pResetNight", Reset_Night,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);

    Tcl_CreateCommand (interp, "pSetHist", Set_Hist,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pResetHist", Reset_Hist,
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
    Tcl_CreateCommand (interp, "pSetBins", Set_Bins,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pSetS", Set_S,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pSetV1", Set_V1,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pSetV2", Set_V2,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);

    Tcl_CreateCommand (interp, "pPauseCamera", Pause_Camera,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pPauseAvi", Pause_Avi,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pResumeCamera", Resume_Camera,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    Tcl_CreateCommand (interp, "pResumeAvi", Resume_Avi,
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
MainEx( int /*argc*/, char** /*argv*/, Tcl_AppInitProc *appInitProc,
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

    MainEx(argc, argv, Tcl_AppInit, g_pInterp, "cvcsdemo.tcl");

    if (camtype == 1)
        cvcamExit();

    if (camtype == 0)
        cvcamAVICloseFile(avifile);

    return 0;
}
