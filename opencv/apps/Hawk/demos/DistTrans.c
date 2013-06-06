char wndname[] = "Distance transform";
char tbarname[] = "Threshold";
int edge_thresh = 1;

// Load the source image
IPLIMAGE image = load_iplimage( "y2k.bmp" );

// Create the output image
IPLIMAGE dist = cvCreateImage( cvSize( image -> width, image -> height ), IPL_DEPTH_32F, 1 );
IPLIMAGE dist8u1 = cvCreateImage( cvSize( image -> width, image -> height ), IPL_DEPTH_8U, 1 );
IPLIMAGE dist8u2 = cvCreateImage( cvSize( image -> width, image -> height ), IPL_DEPTH_8U, 1 );
IPLIMAGE dist8u = cvCreateImage( cvSize( image -> width, image -> height ), IPL_DEPTH_8U, 3 ); // Converted depth32f to depth8u
IPLIMAGE dist32s = cvCreateImage( cvSize( image -> width, image -> height ), IPL_DEPTH_32S, 1 );

// Convert to grayscale
IPLIMAGE gray = cvCreateImage( cvSize(image->width, image->height), IPL_DEPTH_8U, 1 );
IPLIMAGE edge = cvCreateImage( cvSize(image->width, image->height), IPL_DEPTH_8U, 1 ); // After Threshold
cvCvtColor( image, gray, CV_BGR2GRAY );

// define a trackbar callback
void on_trackbar( int h )
{
    int j;
    int distStep = dist -> widthStep / 4;
    float* currPointer;
    
    cvThreshold( gray, edge,
                 ( float )( edge_thresh ),
                 ( float )( edge_thresh ),
                  CV_THRESH_BINARY );
    //Distance transform                  
    cvDistTransform( edge, dist,
                     CV_DIST_L2,
                     CV_DIST_MASK_5,
                     NULL );

    cvConvertScale( dist, dist, 5000.0, 0 );
    
    for( j = 0, currPointer = dist -> imageData; j < dist -> height; j++, currPointer += distStep )
    {
        cvbSqrt( ( float* )( currPointer ),
                 ( float* )( currPointer ),
                 dist -> width );            
    }
    
    cvConvertScale( dist, dist32s, 1.0, 0.5 );
    cvAndS( dist32s, cvScalarAll(255), dist32s, 0 );
    cvConvertScale( dist32s, dist8u1, 1, 0 );
    cvConvertScale( dist32s, dist32s, -1, 0 );
    cvAddS( dist32s, cvScalarAll(255), dist32s, 0 );
    cvConvertScale( dist32s, dist8u2, 1, 0 );
    cvCvtPlaneToPix( dist8u1, dist8u2, dist8u2, 0, dist8u );
    show_iplimage( wndname, dist8u );
}

// Create a window
named_window( wndname, 0 );

// create a toolbar 
create_trackbar( tbarname, wndname, &edge_thresh, 255, on_trackbar );

// Show the image
on_trackbar( 0 );

// Wait for a key stroke; the same function arranges events processing
wait_key( 0 );
cvReleaseImage( &image );
cvReleaseImage( &gray );
cvReleaseImage( &edge );
cvReleaseImage( &dist );
cvReleaseImage( &dist8u );
cvReleaseImage( &dist8u1 );
cvReleaseImage( &dist8u2 );
cvReleaseImage( &dist32s );
destroy_window( wndname );

