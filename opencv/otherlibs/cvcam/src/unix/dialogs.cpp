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
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include "dialogs.h"
#include "cvcam.h"
#include "cvvidtypes.h"
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xaw/Paned.h>
#include <X11/Xaw/Scrollbar.h>
#include <X11/Xaw/Label.h>
#include <X11/Xaw/Toggle.h>
#include <stdlib.h>
#include "highgui.h"
////////////////////////////////////////////////////////////////////////////////
extern Widget cvvTopLevelWidget;
static int select_res = 1;
static int select_format = 0;

typedef struct
{
    __u16* value;
    Widget w;
} Tracker;

typedef struct
{
    int         n;
    Widget      w;
    VideoFormat vf;
    CameraDescription descr;
    Tracker     br;
    Tracker     con;
    Tracker     col;
    Tracker     hue;
    int         min_w;
    int         min_h;
    int         mid_w;
    int         mid_h;
    int         max_w;
    int         max_h;
    int         enable;
    int         render;
} VideoWidget;

static void on_apply( Widget w, VideoWidget* data )
{
    cvcamSetProperty(data->n, "set_video_format", &data->vf);
    XtVaSetValues( w, XtNstate, False, 0 );
}

static void on_cancel( Widget w, VideoWidget* data )
{
    XtDestroyWidget( data->w );
    free( data );
}

static void on_ok( Widget w, VideoWidget* data )
{
    on_apply( w, data );
    on_cancel( w, data );
}

static void on_track( Widget w, Tracker* data, float* percent )
{
    char s[100];
    __u16 value = (__u16)(*percent * 0xFFFF);
    *(data->value) = value;
    sprintf( s, "%d", value );
    XtVaSetValues( data->w, XtNlabel, s, 0 );
}

static void set_float( Widget w, char* name, float value )
{
    Arg   args[1];

    if (sizeof(float) > sizeof(XtArgVal))
        XtSetArg(args[0], name, &value);
    else
    {
        union {
            XtArgVal xt;
            float   fp;
        } foo;
        foo.fp = value;
        XtSetArg(args[0], name, foo.xt);
    }
    XtSetValues(w,args,1);
}

static void on_24( Widget w, VideoWidget* v )
{
    int state = 1;
    XtVaGetValues( w, XtNstate, &state, 0 );
    if( !state )
        return;
    v->vf.picture.palette = VIDEO_PALETTE_RGB24;
}

static void on_32( Widget w, VideoWidget* v )
{
    int state = 1;
    XtVaGetValues( w, XtNstate, &state, 0 );
    if( !state )
        return;
    v->vf.picture.palette = VIDEO_PALETTE_RGB32;
}

static void on_min( Widget w, VideoWidget* v )
{
    int state = 1;
    XtVaGetValues( w, XtNstate, &state, 0 );
    if( !state )
        return;
    v->vf.width = v->min_w;
    v->vf.height = v->min_h;
}

static void on_mid( Widget w, VideoWidget* v )
{
    int state = 1;
    XtVaGetValues( w, XtNstate, &state, 0 );
    if( !state )
        return;
    v->vf.width = v->mid_w;
    v->vf.height = v->mid_h;
}

static void on_max( Widget w, VideoWidget* v )
{
    int state = 1;
    XtVaGetValues( w, XtNstate, &state, 0 );
    if( !state )
        return;
    v->vf.width = v->max_w;
    v->vf.height = v->max_h;
}

void icvVideoVideoPPDialog(int camera)
{
    Widget dialog;
    Widget label;
    Widget paned;

    Widget paned_res;
    Widget paned_format;
    Widget res_min;
    Widget res_middle;
    Widget res_max;

    Widget format_24;
    Widget format_32;

    Widget brightness;
    Widget contrast;
    Widget color;
    Widget hue;
    Widget br;
    Widget con;
    Widget col;
    Widget h;

    Widget buttons;
    Widget b_ok;
    Widget b_apply;
    Widget b_cancel;

    CameraDescription descr;

    char title[100];

    VideoWidget* vf = (VideoWidget*)malloc( sizeof(*vf) );
    vf->n = camera;
    cvcamGetProperty(camera, "description", &descr);

    cvcamGetProperty(camera, "set_video_format", &vf->vf);

    sprintf( title, "%d", camera );
    
    cvvInitSystem(0, 0);
    /* Creating main dialog window */
    dialog = XtVaAppCreateShell( title, "video", topLevelShellWidgetClass,
                                XtDisplay( /*(void*)*/cvvTopLevelWidget ),
                                XtNminWidth, 10, XtNminHeight, 10,
                                XtNinput, 1, 0 );
    /* Creating main paned window... It will parent for all smaller elements */
    paned = XtVaCreateManagedWidget( "CvVisual_paned", panedWidgetClass, dialog,
                                     0 );
    /* Resolution elements */
    label = XtVaCreateManagedWidget( "resolution", labelWidgetClass, paned,
                                     XtNshowGrip, False,
                                     XtNlabel, "camera resolution",
                                     XtNjustify, XtJustifyCenter, 0 );

    paned_res = XtVaCreateManagedWidget( "resolution_res", panedWidgetClass, paned,
                                         XtNshowGrip, False,
                                         XtNorientation, XtorientHorizontal,
                                         0 );
    
    sprintf( title, "%dx%d", descr.minwidth, descr.minheight );
    res_min = XtVaCreateManagedWidget( "res min", toggleWidgetClass, paned_res,
                                       XtNlabel, title,
                                       XtNshowGrip, False,
                                       XtNradioData, &select_res,
                                       0 );
    XtAddCallback( res_min, "callback", (XtCallbackProc)on_min, vf );
    vf->min_w = descr.minwidth;
    vf->min_h = descr.minheight;

    res_middle = XtVaCreateManagedWidget( "res middle", toggleWidgetClass, paned_res,
                                       XtNlabel, "320x240",
                                       XtNshowGrip, False,
                                       XtNradioData, &select_res,
                                       XtNradioGroup, res_min,
                                       0 );
    XtAddCallback( res_middle, "callback", (XtCallbackProc)on_mid, vf );
    vf->mid_w = 320;
    vf->mid_h = 240;

    sprintf( title, "%dx%d", descr.maxwidth, descr.maxheight );
    res_max = XtVaCreateManagedWidget( "res max", toggleWidgetClass, paned_res,
                                       XtNlabel, title,
                                       XtNshowGrip, False,
                                       XtNradioData, &select_res,
                                       XtNradioGroup, res_min,
                                       0 );
    XtAddCallback( res_max, "callback", (XtCallbackProc)on_max, vf );
    vf->max_w = descr.maxwidth;
    vf->max_h = descr.maxheight;
    if( vf->vf.width == descr.minwidth )
        XtVaSetValues( res_min, XtNstate, True, 0 );
    else if( vf->vf.width == descr.maxwidth )
        XtVaSetValues( res_max, XtNstate, True, 0 );
    else
        XtVaSetValues( res_middle, XtNstate, True, 0 );

    /* Video format elements */
    label = XtVaCreateManagedWidget( "format", labelWidgetClass, paned,
                                     XtNshowGrip, False,
                                     XtNlabel, "data format",
                                     XtNjustify, XtJustifyCenter, 0 );

    paned_res = XtVaCreateManagedWidget( "format", panedWidgetClass, paned,
                                         XtNshowGrip, False,
                                         XtNorientation, XtorientHorizontal,
                                         0 );

    format_24 = XtVaCreateManagedWidget( "bpp24", toggleWidgetClass, paned_res,
                                         XtNlabel, "RGB24",
                                         XtNshowGrip, False,
                                         XtNradioData, &select_format,
                                         0 );
    XtAddCallback( format_24, "callback", (XtCallbackProc)on_24, vf );

    format_32 = XtVaCreateManagedWidget( "bpp32", toggleWidgetClass, paned_res,
                                       XtNlabel, "RGB32",
                                       XtNshowGrip, False,
                                       XtNradioData, &select_format,
                                       XtNradioGroup, format_24,
                                       0 );
    XtAddCallback( format_32, "callback", (XtCallbackProc)on_32, vf );
    switch( vf->vf.picture.palette )
    {
        case VIDEO_PALETTE_RGB24:
            XtVaSetValues( format_24, XtNstate, True, 0 );
            break;
        case VIDEO_PALETTE_RGB32:
            XtVaSetValues( format_32, XtNstate, True, 0 );
            break;
        default:
            XtDestroyWidget( dialog );
            free( vf );
            printf( "supported only RGB23 & RGB32 formats\n" );
            return;
    }

    /* Brightness, contrast, color & hue elements */
    /* brightness */
    label = XtVaCreateManagedWidget( "brigthness", labelWidgetClass, paned,
                                     XtNshowGrip, False,
                                     XtNlabel, "brigthness",
                                     XtNjustify, XtJustifyCenter, 0 );
    sprintf( title, "%d", vf->vf.picture.brightness);
    brightness = XtVaCreateManagedWidget( "brigthness", labelWidgetClass, paned,
                                     XtNshowGrip, False,
                                     XtNlabel, title,
                                     XtNjustify, XtJustifyCenter, 0 );
    vf->br.w = brightness;
    vf->br.value = &vf->vf.picture.brightness;
    br = XtVaCreateManagedWidget( "br", scrollbarWidgetClass, paned,
                                  XtNshowGrip, False,
                                  XtNorientation, XtorientHorizontal, 0 );
    set_float( br, XtNtopOfThumb, (float)vf->vf.picture.brightness / 0xFFFF );
    XtAddCallback( br, "jumpProc", (XtCallbackProc)on_track, &vf->br );

    /* contrast */
    label = XtVaCreateManagedWidget( "contrast", labelWidgetClass, paned,
                                     XtNshowGrip, False,
                                     XtNlabel, "contrast",
                                     XtNjustify, XtJustifyCenter, 0 );
    sprintf( title, "%d", vf->vf.picture.contrast);
    contrast = XtVaCreateManagedWidget( "brigthness", labelWidgetClass, paned,
                                     XtNshowGrip, False,
                                     XtNlabel, title,
                                     XtNjustify, XtJustifyCenter, 0 );
    vf->con.w = contrast;
    vf->con.value = &vf->vf.picture.contrast;
    con = XtVaCreateManagedWidget( "con", scrollbarWidgetClass, paned,
                                  XtNshowGrip, False,
                                  XtNorientation, XtorientHorizontal, 0 );
    set_float( con, XtNtopOfThumb, (float)vf->vf.picture.contrast / 0xFFFF );
    XtAddCallback( con, "jumpProc", (XtCallbackProc)on_track, &vf->con );

    /* colour */
    label = XtVaCreateManagedWidget( "color", labelWidgetClass, paned,
                                     XtNshowGrip, False,
                                     XtNlabel, "color",
                                     XtNjustify, XtJustifyCenter, 0 );
    sprintf( title, "%d", vf->vf.picture.colour);
    color = XtVaCreateManagedWidget( "brigthness", labelWidgetClass, paned,
                                     XtNshowGrip, False,
                                     XtNlabel, title,
                                     XtNjustify, XtJustifyCenter, 0 );
    vf->col.w = color;
    vf->col.value = &vf->vf.picture.colour;
    col = XtVaCreateManagedWidget( "col", scrollbarWidgetClass, paned,
                                  XtNshowGrip, False,
                                  XtNorientation, XtorientHorizontal, 0 );
    set_float( col, XtNtopOfThumb, (float)vf->vf.picture.colour / 0xFFFF );
    XtAddCallback( col, "jumpProc", (XtCallbackProc)on_track, &vf->col );

    /* hue */
    label = XtVaCreateManagedWidget( "hue", labelWidgetClass, paned,
                                     XtNshowGrip, False,
                                     XtNlabel, "hue",
                                     XtNjustify, XtJustifyCenter, 0 );
    sprintf( title, "%d", vf->vf.picture.contrast);
    hue = XtVaCreateManagedWidget( "brigthness", labelWidgetClass, paned,
                                     XtNshowGrip, False,
                                     XtNlabel, title,
                                     XtNjustify, XtJustifyCenter, 0 );
    vf->hue.w = hue;
    vf->hue.value = &vf->vf.picture.hue;
    h = XtVaCreateManagedWidget( "h", scrollbarWidgetClass, paned,
                                  XtNshowGrip, False,
                                  XtNorientation, XtorientHorizontal, 0 );
    set_float( h, XtNtopOfThumb, (float)vf->vf.picture.hue / 0xFFFF );
    XtAddCallback( h, "jumpProc", (XtCallbackProc)on_track, &vf->hue );

    /* Buttons */
    buttons = XtVaCreateManagedWidget( "buttons", panedWidgetClass, paned,
                                         XtNshowGrip, False,
                                         XtNorientation, XtorientHorizontal,
                                         0 );

    b_ok = XtVaCreateManagedWidget( "b_ok", toggleWidgetClass, buttons,
                                       XtNlabel, "Ok",
                                       XtNshowGrip, False,
                                       XtNstate, False,
                                       0 );
    XtAddCallback( b_ok, XtNcallback, (XtCallbackProc)on_ok, (void*)vf );

    b_apply = XtVaCreateManagedWidget( "b_apply", toggleWidgetClass, buttons,
                                       XtNlabel, "Apply",
                                       XtNshowGrip, False,
                                       XtNstate, False,
                                       0 );
    XtAddCallback( b_apply, XtNcallback, (XtCallbackProc)on_apply, (void*)vf );

    b_cancel = XtVaCreateManagedWidget( "b_cancel", toggleWidgetClass, buttons,
                                       XtNlabel, "Cancel",
                                       XtNshowGrip, False,
                                       XtNstate, False,
                                       0 );
    XtAddCallback( b_cancel, XtNcallback, (XtCallbackProc)on_cancel, (void*)vf );
    vf->w = dialog;
    vf->n = camera;

    XtRealizeWidget( dialog );

    {
        /* fixating window size */
        int width = 10;
        int height = 10;
        XtVaGetValues( dialog, XtNwidth, &width, XtNheight, &height, 0 );
        XtVaSetValues( dialog, XtNminWidth, width, XtNminHeight, height,
                               XtNmaxWidth, width, XtNmaxHeight, height, 0 );
    }
}

////////////////////////////////////////////////////////////////////////////////
static void on_enable( Widget w, VideoWidget* data )
{
    int status = 1;
    XtVaGetValues( w, XtNstate, &status, 0 );
    data->enable = status;
}

static void on_render( Widget w, VideoWidget* data )
{
    int status = 1;
    XtVaGetValues( w, XtNstate, &status, 0 );
    data->render = status;
}

static void on_cam_apply( Widget w, VideoWidget* data )
{
    cvcamSetProperty( data->n, "enable", &data->enable );
    cvcamSetProperty( data->n, "render", &data->render );
    XtVaSetValues( w, XtNstate, False, 0 );
}

static void on_cam_ok( Widget w, VideoWidget* data )
{
    on_cam_apply( w, data );
    on_cancel( w, data );
}

void icvVideoCameraPPDialog(int camera)
{
    Widget dialog;
    Widget label;
    Widget paned;

    Widget enable;
    Widget render;

    Widget buttons;
    Widget b_ok;
    Widget b_apply;
    Widget b_cancel;

    int    res;

    char title[1000];

    VideoWidget* vf = (VideoWidget*)malloc( sizeof(*vf) );
    cvcamGetProperty(camera, "description", &vf->descr);

    sprintf( title, "camera %d", camera );
    
    cvvInitSystem(0, 0);
    /* Creating main dialog window */
    dialog = XtVaAppCreateShell( title, "camera", topLevelShellWidgetClass,
                                XtDisplay( cvvTopLevelWidget ),
                                XtNminWidth, 10, XtNminHeight, 10,
                                XtNinput, 1, 0 );
    /* Creating main paned window... It will parent for all smaller elements */
    paned = XtVaCreateManagedWidget( "CvCamera_paned", panedWidgetClass, dialog,
                                     0 );
    /* Resolution elements */
    sprintf( title, "%s on %s", vf->descr.DeviceDescription, vf->descr.device );
    label = XtVaCreateManagedWidget( "desriprion", labelWidgetClass, paned,
                                     XtNshowGrip, False,
                                     XtNlabel, title,
                                     XtNjustify, XtJustifyCenter, 0 );

    cvcamGetProperty(camera, "enable", &res);
    enable = XtVaCreateManagedWidget( "enable", toggleWidgetClass, paned,
                                      XtNlabel, "enable",
                                      XtNshowGrip, False,
                                      XtNradioData, &select_res,
                                      XtNstate, res,
                                      0 );
    XtAddCallback( enable, "callback", (XtCallbackProc)on_enable, vf );

    cvcamGetProperty(camera, "render", &res);
    render = XtVaCreateManagedWidget( "render", toggleWidgetClass, paned,
                                      XtNlabel, "render",
                                      XtNshowGrip, False,
                                      XtNradioData, &select_res,
                                      XtNstate, res,
                                      0 );
    XtAddCallback( render, "callback", (XtCallbackProc)on_render, vf );

    /* Buttons */
    buttons = XtVaCreateManagedWidget( "buttons", panedWidgetClass, paned,
                                         XtNshowGrip, False,
                                         XtNorientation, XtorientHorizontal,
                                         0 );

    b_ok = XtVaCreateManagedWidget( "b_ok", toggleWidgetClass, buttons,
                                     XtNlabel, "Ok",
                                     XtNshowGrip, False,
                                     XtNstate, False,
                                     0 );
    XtAddCallback( b_ok, XtNcallback, (XtCallbackProc)on_cam_ok, (void*)vf );

    b_apply = XtVaCreateManagedWidget( "b_apply", toggleWidgetClass, buttons,
                                       XtNlabel, "Apply",
                                       XtNshowGrip, False,
                                       XtNstate, False,
                                       0 );
    XtAddCallback( b_apply, XtNcallback, (XtCallbackProc)on_cam_apply, (void*)vf );

    b_cancel = XtVaCreateManagedWidget( "b_cancel", toggleWidgetClass, buttons,
                                         XtNlabel, "Cancel",
                                         XtNshowGrip, False,
                                         XtNstate, False,
                                         0 );
    XtAddCallback( b_cancel, XtNcallback, (XtCallbackProc)on_cancel, (void*)vf );
    XtRealizeWidget( dialog );
    
    vf->n = camera;
    vf->w = dialog;

    {
        /* fixating window size */
        int width = 10;
        int height = 10;
        XtVaGetValues( dialog, XtNwidth, &width, XtNheight, &height, 0 );
        XtVaSetValues( dialog, XtNminWidth, width, XtNminHeight, height,
                               XtNmaxWidth, width, XtNmaxHeight, height, 0 );
    }
}

