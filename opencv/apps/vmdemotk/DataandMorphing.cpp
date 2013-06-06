#include "DataandMorphing.h"
#include "VMDemoTk.h"
#include "Globals.h"
#include <highgui.h>

//Static vars
static CvMatrix3   matrix;
IplImage* datal = 0;
IplImage* datar = 0;
static IplImage* datares = 0;


static int*    runs_1;
static int*    runs_2;

static uchar*  buffer_1;
static uchar*  buffer_2;
static uchar*  morph_buffer;


static int*    num_runs_1;
static int*    num_runs_2;

static int*    corr_1;
static int*    corr_2;

static int*    lens_1, *lens_2;

static int*    morph_lens;


///////////////////////////////////////////////////////////////////////////////
int MemoryAllocation()
{
    int numlines;
    cvMakeScanlines( &matrix, imgsize, 0, 0, 0, 0, &numlines);

    scanlines_1 = (int*)(calloc( numlines * 2, sizeof(int) * 4));
    scanlines_2 = (int*)(calloc( numlines * 2, sizeof(int) * 4));
    scanlines_a = (int*)(calloc( numlines * 2, sizeof(int) * 4));

    lens_1 = (int*)(calloc( numlines * 2, sizeof(int)*4));
    lens_2 = (int*)(calloc( numlines * 2, sizeof(int)*4));
    morph_lens = (int*)(calloc( numlines * 2, sizeof(int)*4));

    runs_1 = (int*)(calloc(imgsize.width * imgsize.height * 2, 2 * sizeof(int)));
    runs_2 = (int*)(calloc(imgsize.width * imgsize.height * 2, 2 * sizeof(int)));

    corr_1 = (int*)(calloc(imgsize.width * imgsize.height * 2, 2 * sizeof(int)));
    corr_2 = (int*)(calloc(imgsize.width * imgsize.height * 2, 2 * sizeof(int)));

    num_runs_1 = (int*)(calloc(imgsize.width * imgsize.height * 2, 2 * sizeof(int)));
    num_runs_2 = (int*)(calloc(imgsize.width * imgsize.height * 2, 2 * sizeof(int)));

    buffer_1 = (uchar*)(malloc(imgsize.width * (imgsize.height+1) * 2 * sizeof(int)));

    buffer_2 = (uchar*)(malloc(imgsize.width * (imgsize.height+1) * 2 * sizeof(int)));

    morph_buffer = (uchar*)(calloc(imgsize.width * (imgsize.height+1), 2 * sizeof(int)));
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////
int loaddata (Tcl_Interp  *interp)
{
    int   tx, tx1, ty, ty1;

    //datal = cvvLoadImage(

    tx = datal->width;
    tx1 = datar->width;
    ty = datal->height;
    ty1 = datar->height;

    if( datares )
        cvReleaseImage( &datares );

    datares = cvCreateImage( cvSize( tx, ty ), IPL_DEPTH_8U, 3 );

    if(tx !=tx1 || ty != ty1) return 2;

    Tcl_Eval(interp, "readini $var FundMatrix {F[0][0]}");
    (matrix).m[0][0] = (float)atof( (*interp).result );

    Tcl_Eval(interp, "readini $var FundMatrix {F[0][1]}");
    (matrix).m[0][1] = (float)atof( (*interp).result );

    Tcl_Eval(interp, "readini $var FundMatrix {F[0][2]}");
    (matrix).m[0][2] = (float)atof( (*interp).result );

    Tcl_Eval(interp, "readini $var FundMatrix {F[1][0]}");
    (matrix).m[1][0] = (float)atof( (*interp).result );

    Tcl_Eval(interp, "readini $var FundMatrix {F[1][1]}");
    (matrix).m[1][1] = (float)atof( (*interp).result );

    Tcl_Eval(interp, "readini $var FundMatrix {F[1][2]}");
    (matrix).m[1][2] = (float)atof( (*interp).result );

    Tcl_Eval(interp, "readini $var FundMatrix {F[2][0]}");
    (matrix).m[2][0] = (float)atof( (*interp).result );

    Tcl_Eval(interp, "readini $var FundMatrix {F[2][1]}");
    (matrix).m[2][1] = (float)atof( (*interp).result );

    Tcl_Eval(interp, "readini $var FundMatrix {F[2][2]}");
    (matrix).m[2][2] = (float)atof( (*interp).result );

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
int OnMakeMorphing(float sk,Tcl_Interp  *interp)
{
    CvMatrix3  matrix1;
    IplImage *image1, *image2, *imageRes;

    matrix1 = matrix;

    image1   = datal;
    image2   = datar;
    imageRes = datares;

    cvMakeScanlines( &matrix1, imgsize, 0, 0, 0, 0, &numScanlines);

    if( !HaveMorph )
    {
        cvMakeScanlines( &matrix1, imgsize, scanlines_1,
                         scanlines_2, lens_1, lens_2, &numScanlines);

        cvPreWarpImage( numScanlines, image1, buffer_1, 
                        lens_1, scanlines_1);

        /* Prewarp second image */
        cvPreWarpImage( numScanlines, image2, 
                        buffer_2, lens_2, scanlines_2);

        cvFindRuns( numScanlines, buffer_1,   /* prewarp image                */
                    buffer_2, lens_1,     /* prewarp line lens in pixels  */
                    lens_2, runs_1,     /* first runs                   */
                    runs_2,
                    num_runs_1, /* number of first runs         */
                    num_runs_2);

        cvDynamicCorrespondMulti(
                         numScanlines,         // number of scanlines
                         runs_1,         // s0|w0|s1|w1|...
                         num_runs_1,    // numbers of runs
                         runs_2,
                         num_runs_2,
                         corr_1,    // s0'|e0'|s1'|e1'|...
                         corr_2 );


        HaveMorph   = true;
    } // if(!HaveMorph)


    cvMakeAlphaScanlines(    scanlines_1,
                             scanlines_2,
                             scanlines_a,
                             morph_lens,
                             numScanlines,
                             sk);


    cvMorphEpilinesMulti(
                        numScanlines,       /* number of lines                              */
                             buffer_1,       /* raster epilines from the first image         */
                             lens_1,         /* number of pixel in first line                */
                             buffer_2,       /* raster epilines from the second image        */
                             lens_2,         /* number of pixel in second line               */
                             morph_buffer ,   /* raster epiline from the destination image    */
                                        /* (it's an output parameter)                   */
                             morph_lens,     /* numbers of pixel in output line              */
                             sk,          /* relative position of camera                  */
                             runs_1,         /* first sequence of runs                       */
                             num_runs_1,     /* it's length                                  */
                             runs_2,         /* second sequence of runs                      */
                             num_runs_2,     /*                                              */
                             corr_1,         /* correspond information for the 1st seq       */
                             corr_2);        /* correspond information for the 2nd seq       */

    cvPostWarpImage(
                        numScanlines,                       /* number of scanlines  */
                             morph_buffer,                   /* source buffers       */
                             morph_lens,                     /* lens of buffers      */
                             imageRes,       /* dest image           */
                             scanlines_a                     /* scanline             */
                                    );

    cvDeleteMoire(  imageRes);
    cvvShowImage( "result", imageRes );

    return 0;
}



//////////////////////////////////////////////////////////////////////////////////

int FreeMemory()
{
    if (scanlines_1     != 0)   free (scanlines_1);
    if (scanlines_2     != 0)   free (scanlines_2);
    if (scanlines_a     != 0)   free (scanlines_a);

    if (lens_1          != 0)   free (lens_1);
    if (lens_2          != 0)   free (lens_2);
    if (morph_lens      != 0)   free (morph_lens);

    if (buffer_1        != 0)   free (buffer_1);
    if (buffer_2        != 0)   free (buffer_2);
    if (morph_buffer    != 0)   free (morph_buffer);

    if (runs_1          != 0)   free (runs_1);
    if (runs_2          != 0)   free (runs_2);

    if (corr_1          != 0)   free (corr_1);
    if (corr_2          != 0)   free (corr_2);

    if (num_runs_1      != 0)   free (num_runs_1);
    if (num_runs_2      != 0)   free (num_runs_2);


    scanlines_1     = 0;
    scanlines_2     = 0;
    scanlines_a     = 0;

    lens_1          = 0;
    lens_2          = 0;
    morph_lens      = 0;

    runs_1          = 0;
    runs_2          = 0;

    buffer_1        = 0;
    buffer_2        = 0;
    morph_buffer    = 0;

    num_runs_1      = 0;
    num_runs_2      = 0;

    corr_1          = 0;
    corr_2          = 0;

    return 0;
}
