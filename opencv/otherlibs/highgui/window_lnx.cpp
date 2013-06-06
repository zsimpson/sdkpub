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

#include "_highgui.h"

#ifndef WIN32

#ifndef WIN32
#include <pthread.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xaw/Paned.h>
#include <X11/Xaw/Scrollbar.h>
#include <unistd.h>
#endif

//#ifndef NDEBUG
#define Assert(exp)                                                 \
    if( !(exp) )                                                    \
    {                                                               \
        printf("Assertion: %s  %s: %d\n", #exp, __FILE__, __LINE__);\
        assert(exp);                                                \
    }
//#else
//#define Assert(exp)
//#endif

static CvvWindow* windows = 0;

#ifndef WIN32
static void icvvCloseWindow( Widget w, XEvent* event,
                             String* params, Cardinal* num_params );
static Widget       topLevel;
static XtAppContext appContext;
static Atom         wm_delete_window;
static XtActionsRec actions[] = { { "quit", icvvCloseWindow  }, { 0, 0 } };
static XtTranslations translations;

static pthread_mutex_t mutex;
static int             last_key;
static XtIntervalId    timer = 0;
extern "C"{
Widget cvvTopLevelWidget = 0;
}
#endif

#ifndef WIN32
/* this function finds window by toplevel widget */
static CvvWindow* icvvFindWindowByWidget( Widget widget )
{
    CvvWindow* window = windows;
    while( window && window->window != widget )
        window = window->next;
    return window;
}

/* draw image to frame */
static void icvvPutImage( CvvWindow* window )
{
    Assert( window != 0 );

    if( !window->image ) return;
    
    int width = 10, height = 10;

    XtVaGetValues( window->frame, XtNwidth, &width, XtNheight, &height, 0 );

    if( width < 2 || height < 2 )
        return;

    int step = (width * (window->image->depth / 8) + 3) & ~3;

    if( window->dst_image &&
        (window->dst_image->width  != width  ||
         window->dst_image->height != height ||
         window->dst_image->bytes_per_line != step ))
    {
        XDestroyImage( window->dst_image );
        window->dst_image = 0;
    }

    if( !window->dst_image )
    {
        char* data = (char*)malloc( step * height );
        window->dst_image = XCreateImage( XtDisplay(window->frame),
                                          CopyFromParent,
                                          window->image->depth,
                                          ZPixmap, 0, data, width, height,
                                          8, step );
        window->dst_image->bits_per_pixel = window->dst_image->depth;
    }
    
    {
    CvMat src;
    CvMat dst;
    int type = ((window->image->depth/8) - 1)*8 + CV_8U;

    OPENCV_CALL( cvInitMatHeader( &src, window->image->height, window->image->width,
                 type, window->image->data, window->image->bytes_per_line ));

    OPENCV_CALL( cvInitMatHeader( &dst, height, width, type, window->dst_image->data, step ));

    OPENCV_CALL( cvResize( &src, &dst, CV_INTER_NN ));
    }

    GC gc = XCreateGC( XtDisplay(window->frame), XtWindow(window->frame), 0, 0 );
    XPutImage( XtDisplay(window->frame), XtWindow(window->frame), gc,
               window->dst_image, 0, 0, 0, 0,
               width, height );
    XFreeGC( XtDisplay(window->frame), gc );
}                                                   
                                                    
/* callback to redraw message */                    
static void icvvDrawImage( Widget w, XtPointer pData, XEvent* event, Boolean* cont )
{
    CvvWindow* wnd   = (CvvWindow*)pData;

    Assert( w == wnd->frame );

    switch( event->type )
    {
        case Expose:
        case VisibilityNotify:
            if( wnd->image )
                icvvPutImage( wnd );
            break;
        default:
            break;
    }
    
    if( !wnd->converted )
    {
        wnd->converted = 1;
        XSetWMProtocols( XtDisplay(wnd->window), XtWindow(wnd->window),
                         &wm_delete_window, 1 );
    }
}


static void icvvKeyPress( Widget w, XtPointer pData, XEvent* event, Boolean* cont )
{
    KeySym key;
    XLookupString( &event->xkey, 0, 0, &key, 0 );
    if( !IsModifierKey(key) )
    {
        last_key = key;
        pthread_mutex_unlock( &mutex );
        if( timer )
        {
            XtRemoveTimeOut( timer );
            timer = 0;
        }
    }
}

static void icvvTimer( XtPointer, XtIntervalId* )
{
    timer = 0;
    last_key = 0;
    pthread_mutex_unlock( &mutex );
}


/* this function creates new window                         */
/* (topLevelShellWidgetClass -> panedWidget...) and returns */
/* resuld widget                                            */
static Widget icvvCreateWindow( const char* name, CvvWindow* window )
{
    Assert( window != 0 );
    if( !name ) name = "CvVisual";

    window->window = XtVaAppCreateShell( name, name, topLevelShellWidgetClass,
                                XtDisplay( topLevel ),
                                XtNminWidth, 10, XtNminHeight, 10,
                                XtNinput, 1, 0 );
    Assert( window->window != 0 );

    window->paned = XtVaCreateManagedWidget( "CvVisual_paned", panedWidgetClass,
                                            window->window,
                                            XtNminWidth, 100, XtNminHeight, 100,
                                            XtNmaxWidth, 100, XtNmaxHeight, 100,
                                            XtNwidth, 100, XtNheight, 100, 0 );
    Assert( window->paned != 0 );

    window->frame = XtVaCreateManagedWidget( "CvVisual", widgetClass, window->paned,
                                             XtNwidth, 100, XtNheight, 100, XtNshowGrip, False,
                                             XtNallowResize, True,
                                             XtNmin, 2, 0 );
    Assert( window->frame != 0 );

    XtAddEventHandler( window->frame, ExposureMask | VisibilityChangeMask,
                       False, icvvDrawImage, window );
    XtAddEventHandler( window->window, KeyPressMask, False, icvvKeyPress, 0 );
    
    XtRealizeWidget( window->window );

    XtOverrideTranslations( window->window, XtParseTranslationTable("<Message>WM_PROTOCOLS:quit()") );

    return window->window;
}

/* this function deletes window structure and all data */
static int icvvDeleteWindow( CvvWindow* window )
{
#ifndef WIN32
    Assert( window != 0 );
    Assert( window->created != 0 );
    //XtUnrealizeWidget( window->window );
    if( window->image )
    {
        XImage* image = window->image;
        window->image = 0;
        XDestroyImage( image );
    }
    if( window->dst_image )
    {
        XImage* image = window->dst_image;
        window->image = 0;
        XDestroyImage( image );
    }
    XtDestroyWidget( window->window );
#endif
    CvvTrackbar* track = window->trackbar;
    while( track )
    {
        CvvTrackbar* next = track->next;
        free( track );
        track = next;
    }

    if( !window->prev )
        windows = window->next;
    else
        window->prev->next = window->next;
    if( window->next )
        window->next->prev = window->prev;
    window->created = 0;
    window->next = window->prev = 0;
    free( window );
    return 0;
}

/* this function is called from Xt system when button Close is pressed */
static void icvvCloseWindow( Widget w, XEvent* event,
                             String* params, Cardinal* num_params )
{
    CvvWindow* window = icvvFindWindowByWidget( w );
    Assert( window != 0 );
    if( window )
        icvvDeleteWindow( window );
}

/* main loop for events handling */
static void* icvvMainLoop( void* )
{
    XtAppMainLoop( appContext );
    printf( "main loop finished :(\n" );
    exit(1);
}
#endif

void icvvSetWindowSize( CvvWindow* window, int width, int height )
{
    Assert( window != 0 );
    CvvTrackbar* bar = window->trackbar;
    while( bar )
    {
        height += 10;
        bar = bar->next;
    }
    if( windows->flags )
        XtVaSetValues( window->window, 
                       XtNminWidth, width, XtNmaxWidth, width,
                       XtNminHeight, height, XtNmaxHeight, height, 0 );
    XtVaSetValues( window->window, XtNwidth, width, XtNheight, height, 0 );
}

/* attach IplImage to window */
static void icvvSetIplImage( CvvWindow* window, IplImage* image )
{
    Assert( window != 0 );
    Assert( image != 0 );
#ifndef WIN32
    int width = image->width;
    int height = image->height;

    if( !window->image )
        icvvSetWindowSize( window, width, height );

    if( window->image &&
        (window->image->width  != image->width  ||
         window->image->height != image->height ||
         window->image->bytes_per_line != image->widthStep ||
         window->image->depth  != image->nChannels * (image->depth & 255) ))
    {
        free( window->image->data );
        window->image->data = 0;
        XDestroyImage( window->image );
        window->image = 0;
    }

    if( !window->image )
    {
        int   depth = DefaultDepth(XtDisplay(window->window), 0);
        int   step = (image->width * depth / 8 + 3) & ~3;
        char* data = (char*)malloc( step * image->height );
        window->image = XCreateImage( XtDisplay(window->window),
                                      CopyFromParent,
                                      depth,
                                      ZPixmap, 0, data, image->width, image->height,
                                      8, step );
        window->image->bits_per_pixel = window->image->depth;
    }

    {
    CvMat dst;

    OPENCV_CALL( cvInitMatHeader( &dst, image->height, image->width,
                     CV_8U + ((window->image->depth/8)-1)*8, 
                     window->image->data, window->image->bytes_per_line ));

    cvvConvertImage( image, &dst, 0 );
    }
    icvvPutImage( window );
#endif
}

/* this function finds window by name */
static CvvWindow* icvvFindWindowByName( const char* name )
{
    CvvWindow* window = windows;
    while( window && strcmp(name, window->name) )
            window = window->next;
    return window;
}

/* this function creates new structure element in windows array and */
/* calls icvvCreateWindow function to create new window */
static CvvWindow* icvvNewWindow( const char* name, int flags )
{
    if( icvvFindWindowByName(name) )
        return 0;
    CvvWindow* window = (CvvWindow*)malloc( sizeof(CvvWindow) );
    Assert( window != 0 );
    memset( window, 0, sizeof(*window) );
    strcpy(window->name, name);
    window->created = 1;
    window->flags = flags;
    window->next = windows;
    windows = window;
    if( window->next )
        window->next->prev = window;
#ifndef WIN32
    icvvCreateWindow( name, window );
    Assert( window->window != 0 );
    Assert( window->frame != 0 );
#endif
    return window;
}


#ifndef WIN32
static void icvvTrackbarJumpProc( Widget w, XtPointer client_data, XtPointer percent )
{
    Assert( client_data != 0 );
    Assert( percent != 0 );

    CvvTrackbar* tracker = (CvvTrackbar*)client_data;
    int value = (int)(*(float*)percent * tracker->count);
    
    if( tracker->value )
        *tracker->value = value;

    if( tracker->on_notify )
        tracker->on_notify( value );
}
#endif


static CvvTrackbar* icvvCreateTrackbar( const char* name, int count, int* value,
                                        void (*on_notify)(int), CvvWindow* window )
{
    Assert( window != 0 );
    
    CvvTrackbar* track = (CvvTrackbar*)malloc(sizeof(CvvTrackbar));
    Assert( track != 0 );
    memset( track, 0, sizeof(CvvTrackbar) );
    strcpy( track->name, name );
    track->count = count;
    track->value = value;
    track->on_notify = on_notify;
    
#ifndef WIN32
    Widget widget = XtVaCreateManagedWidget( name, scrollbarWidgetClass, window->paned,
                                             XtNshowGrip, False,
                                             XtNresizeToPreferred, true,
                                             XtNorientation, XtorientHorizontal, 0 );
    int width  = 10;
    int height = 10;
    int sheight = 10;

    if( window->flags )
    {
        XtVaGetValues( window->window, XtNwidth, &width, XtNheight, &height, 0 );
        XtVaSetValues( window->window, XtNwidth, width, XtNheight, height + sheight,
                       XtNminWidth, width, XtNmaxWidth, width,
                       XtNminHeight, height + sheight, XtNmaxHeight, height + sheight, 0 );
    }
    
    XawPanedSetMinMax( widget, sheight, sheight );

    if( value )
    {
        Arg   args[1];
        float top = (float)*value / count;

        if (sizeof(float) > sizeof(XtArgVal))
            XtSetArg(args[0], XtNtopOfThumb, &top);
        else
        {
            union {
                XtArgVal xt;
                float   fp;
            } foo;
            foo.fp = top;
            XtSetArg(args[0], XtNtopOfThumb, foo.xt);
        }
        XtSetValues(widget,args,1);
    }
//        XawScrollbarSetThumb( widget, (float)*value / count, 0.1f );
    XtAddCallback( widget, "jumpProc", icvvTrackbarJumpProc, track );
#endif
    
    return track;
}

static int init = 0;

HIGHGUI_IMPL int cvvInitSystem( int argc, char** argv )
{
#ifndef WIN32
    if( !XtToolkitThreadInitialize() )
    {
        printf( "System doesn't support threads or "
                "Xt system doesn't support threads\n" );
        exit(1);
    }
    cvvTopLevelWidget = topLevel = XtVaAppInitialize( &appContext, "CvVisual", 0, 0,
                                  &argc, argv, 0, XtNwidth, 10, XtNheight, 10, 0 );
    XtAppAddActions(appContext, actions, XtNumber(actions));
    wm_delete_window = XInternAtom(XtDisplay(topLevel),"WM_DELETE_WINDOW",False);

    translations = XtParseTranslationTable("<Message>WM_PROTOCOLS:quit()");

    if( pthread_mutex_init( &mutex, 0 ) )
    {
        printf( "Can't init mutex\n" );
        exit(1);
    }
    
    pthread_t thread;
    pthread_create( &thread, 0, icvvMainLoop, 0 );
    sleep(1);
#endif
    init = 1;
    return CVV_OK;
}


HIGHGUI_IMPL int cvvNamedWindow( const char* name, unsigned long flags )
{
    if( !init )
        cvvInitSystem( 0, 0 );
    if( !icvvNewWindow( name, flags ) ) return CVV_BADNAME;
    return CVV_OK;
}


HIGHGUI_IMPL int cvvDestroyWindow( const char* name )
{
    CvvWindow* window = icvvFindWindowByName( name );
    if( window )
    {
        icvvDeleteWindow( window );
    }
    else
        return CVV_BADNAME;
    return CVV_OK;
}


HIGHGUI_IMPL void cvvShowImage( const char* name, const CvArr* array )
{
    CV_FUNCNAME( "cvvShowImage" );

    __BEGIN__;

    CvvWindow* window;
    IplImage stub, *image;
    
    if( !name || !image )
        EXIT;

    window = icvvFindWindowByName( name );
    
    if( !window )
        EXIT;

    image = cvGetImage( array, &stub );
    icvvSetIplImage( window, image );

    __END__;
}


HIGHGUI_IMPL int cvvCreateTrackbar( const char* name, const char* window_name,
                                   int* value, int count, void (*on_notify)(int) )
{
    CvvWindow* window = icvvFindWindowByName( window_name );
    if( !window )
        return CVV_BADNAME;

    CvvTrackbar* track = icvvCreateTrackbar( name, count, value, on_notify, window );
    track->next = window->trackbar;
    window->trackbar = track;
    return CVV_OK;
}


int cvvWaitKey( const char* )
{
    last_key = 0;
#ifndef WIN32
    pthread_mutex_lock( &mutex );
    pthread_mutex_lock( &mutex );
    pthread_mutex_unlock( &mutex );
#endif
    return last_key;
}


int cvvWaitKeyEx( const char* name, int usecs )
{
#ifndef WIN32
    XtAppAddTimeOut( appContext, usecs, icvvTimer, 0 );
    cvvWaitKey( name );
#endif
}

int cvvResizeWindow( const char* name, int w, int h )
{
#ifndef WIN32
    CvvWindow* window = icvvFindWindowByName( name );
    if( !window )
        return false;
    icvvSetWindowSize( window, w, h );
    return true;
#else
    return false;
#endif
}

#endif /* WIN32 */
