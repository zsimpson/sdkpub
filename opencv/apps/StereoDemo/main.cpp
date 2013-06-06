/****************************************************************************************\
*                                                                                        *
*                                        Stereo Demo                                     *
*                                                                                        *
\****************************************************************************************/

#include "cv.h"
#include "cvhid.h"
#include "highgui.h"
#include "cvcam.h"

#include <limits.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

volatile int g_undistort = 0;
volatile int g_calib = 0;
volatile int g_rectify = 0;
volatile int g_save = 0;
volatile int g_switch_cameras = 0;

void callback( IplImage* image1,IplImage* image2 );

CvCalibFilter CalibFilter;
double EtalonParams[3] = { 7, 10, 3 };

void toggle_calib(void);
void toggle_undistort(void);

int thresh1 = 10;
int thresh2 = 10;

void calc_disparity(IplImage* image1, IplImage* image2);
void calc_dense_disparity(IplImage* image1, IplImage* image2);

void print_help(void)
{
    printf("Help:\n"
                   "h - this help screen\n"
                   "1 - tune first camera parameters\n"
                   "2 - tune second camera parameters\n"
                   "g - start/stop calibration\n"
                   "s - save camera parameters to camera.txt\n"
                   "l - load camera parameters from camera.txt\n"
                   "u - toggle undistortion\n"
                   "r - toggle rectification\n"
                   "t - reverse the cameras order\n"
                   "n - save the couple of frames\n" );
}

int main( int argc, char** argv )
{
    if( argc == 3 )
    {
        int w, h;
        if( !sscanf( argv[1], "%u", &w ) || !sscanf( argv[2], "%u", &h ))
        {
            printf("Invalid checkerboard size\n");
            return -1;
        }
        EtalonParams[0] = w;
        EtalonParams[1] = h;
    }

    CalibFilter.SetEtalon( CV_CALIB_ETALON_CHESSBOARD, EtalonParams );
    CalibFilter.SetCameraCount(2);
    CalibFilter.SetFrames(15);

    iplSetErrMode( IPL_ErrModeSilent );
    
    cvcamGetCamerasCount( );
    cvcamSetProperty(0, CVCAM_PROP_ENABLE, CVCAMTRUE );
    cvcamSetProperty(1, CVCAM_PROP_ENABLE, CVCAMTRUE );

    cvcamSetProperty(0, CVCAM_STEREO_CALLBACK , callback);

    cvcamInit();
    cvcamStart();

    cvvNamedWindow( "camera 1", 1 );
    cvvNamedWindow( "camera 2", 1 );
    cvvCreateTrackbar( "thresh1", "camera 1", &thresh1, 500, 0 );
    cvvCreateTrackbar( "thresh2", "camera 1", &thresh2, 100, 0 );

    print_help();

    for(;;)
    {
        int cmd = cvvWaitKey( 0 );
        if( cmd == '\x1b' )
            break;

        switch( tolower(cmd) )
        {
        case '1':
        case '2':
            cvcamStop();
            cvcamGetProperty( cmd - '1', CVCAM_CAMERAPROPS, NULL);
            cvcamStart();
            break;
        case 'g':
            toggle_calib();
            break;
        case 's':
            CalibFilter.SaveCameraParams("cameras.txt");
            break;
        case 'l':
            CalibFilter.LoadCameraParams("cameras.txt");
            g_rectify ^= 1;
            break;
        case 'u':
            g_undistort ^= 1;
            break;
        case 'r':
            g_rectify ^= 1;
            break;
        case 'n':
            g_save = 1;
            break;
        case 't':
            g_switch_cameras = !g_switch_cameras;
            break;
        case 'h':
            print_help();
            break;
        }
    }

    cvcamStop( );
    cvcamExit( );
    return 0;
}

void toggle_undistort( void )
{
    g_undistort ^= 1;
}


int prev_time = 0;

void toggle_calib( void )
{
    prev_time = clock() - 1000;
    if( !g_calib )
        g_undistort = 0;
    g_calib ^= 1;
}


void SaveStereoPair( IplImage** images, const char* rootname )
{
    int i = 0;
    char name[1000];

    for( i = 0; i < 1000; i++ )
    {
        sprintf( name, "%s%03dL.jpg", rootname, i );
        FILE* f = fopen( name, "rb" );

        if( f )
        {
            fclose(f);
            continue;
        }
        
        save_iplimage( name, images[0] );

        sprintf( name, "%s%03dR.jpg", rootname, i );
        save_iplimage( name, images[1] );

        break;
    }
}

void callback( IplImage* image1, IplImage* image2 )
{
    IplImage* images[] = { image1, image2 };
    int save = g_save != 0;

    if( g_switch_cameras )
    {
        images[0] = image2;
        images[1] = image1;
        image1 = images[0];
        image2 = images[1];
    }

#if 1
    bool found = CalibFilter.FindEtalon( images );
    if( !save )
        CalibFilter.DrawPoints( images );

    if( g_calib && found )
    {
        int cur_time = clock();
        if( cur_time >= prev_time + 1000 )
        {
            prev_time = cur_time;
            CalibFilter.Push();
            cvXorS( image1, cvScalarAll(255), image1 );
            cvXorS( image2, cvScalarAll(255), image2 );
            g_undistort = 0;
        }

        if( CalibFilter.IsCalibrated() )
        {
            g_calib ^= 1;
            g_undistort = 1;
            g_rectify = 1;
        }
    }

    //if( g_undistort )
    //    CalibFilter.Undistort( images, images );

    if( save )
    {
        SaveStereoPair( images, "imgU" );
    }

    if( g_rectify && CalibFilter.IsCalibrated() )
    {
        CalibFilter.Rectify( images, images );

        //calc_disparity(image1, image2);
        calc_dense_disparity(image1, image2);        

        if( save )
        {
            SaveStereoPair( images, "imgR" );
        }
    }
    
#endif

    show_iplimage( "camera 1", image1 );
    show_iplimage( "camera 2", image2 );
    g_save = 0;
}

CvMemStorage* storage = 0; 
CvStereoFeatureList* fl1 = 0;cvCreateStereoFeatureList();
CvStereoFeatureList* fl2 = 0;cvCreateStereoFeatureList();
CvStereoParams params;
void calc_disparity(IplImage* image1, IplImage* image2)
{
    if(!storage)
    {
        storage = cvCreateMemStorage(400000);
        fl1 = cvAllocateStereoFeatureList();
        fl2 = cvAllocateStereoFeatureList();
        InitStereoParams(&params);
        cvvNamedWindow("disparity", 1);
    }
    
    CvGraph* disparity = 0;
    CalculateSparseCorrespondence(image1, image2, storage, &disparity, fl1, fl2, &params);
    IplImage* vis_disp = VisualizeCorrespondence(image1, disparity, &params);
    printf("\nGraph size = %d", disparity->total);
    cvvShowImage("disparity", vis_disp);

    cvReleaseImage(&vis_disp);
    cvClearStereoFeatureList(fl1);
    cvClearStereoFeatureList(fl2);
    cvClearMemStorage(storage);
}

int dense_inited = 0;
void calc_dense_disparity(IplImage* image1, IplImage* image2)
{
    if(!dense_inited)
    {
        InitStereoParams(&params);
        cvvNamedWindow("disparity", 1);
        dense_inited = 1;
    }

    IplImage* vis_disp = cvCreateImage(cvSize(image1->width, image1->height), IPL_DEPTH_8U, 1);

   
    StereoBySimpleDP( image2,
                      image1,
                      NULL, //assoc. graph with features
                      NULL,  //array of subset of vertices to process 
                      0,   //size of above array
                      &params,
                      vis_disp //output dense stereo image 8u1c
                     );

    iplMirror(vis_disp, vis_disp, 0);
    cvErode(vis_disp, vis_disp, 0, 2);
    cvDilate(vis_disp, vis_disp, 0, 4);
    cvErode(vis_disp, vis_disp, 0, 2);
    iplMultiplyS(vis_disp, vis_disp, 2);
    cvvShowImage("disparity", vis_disp);

    cvReleaseImage(&vis_disp);
}

