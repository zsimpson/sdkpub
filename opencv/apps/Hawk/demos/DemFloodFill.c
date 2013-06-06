/************************************************************************************
*
*
*  This program is demonstration for functions cvFloodFill() and cvFloodFill8()
*
*
*  Trackbar specify maximal difference of the values of appurtenant to 
*  repainted area pixel and one of its neighbors.
*
*  Autor:  Denis Burenkov
*
*
************************************************************************************/

char file_name[] = "EXPO0002.bmp";

char wndname01[] = "Source image";
char wndname02[] = "Result image for cvFloodFill";
char wndname03[] = "Result image for cvFloodFill8";
char barname01[] = "Maximal difference";
int slider_pos[1] = {5};

CvPoint seed;
CvConnectedComp comp;


// Load the source image. HighGUI use.
IPLIMAGE image01 = load_iplimage( file_name );

if(image01==NULL)
{
    printf("File '%s' not found.\n", file_name);
    
}


// Create the destination images. HighGUI use.
IPLIMAGE image02 = cvCreateImage( cvSize(image01->width,image01->height),
                                    IPL_DEPTH_8U,
                                    1);

IPLIMAGE image03 = cvCreateImage( cvSize(image01->width,image01->height),
                                    IPL_DEPTH_8U,
                                    1);


// Make onechannel image. IPL use.
cvCvtColor(image01,image02,CV_BGR2GRAY);


// Create windows. HighGUI use.
named_window( wndname01, 0 );
named_window( wndname02, 0 );



// Specify coordinates of the seed point inside the image ROI.
seed.x=200;
seed.y=20;


// Define trackbar callback functons. This function make a
// flood filling of connected area of the image.
void on_trackbar_FloodFill( int h )
{

    cvCopyImage(image02 , image03);
    
    // Flood filling
    cvFloodFill( image03, seed, 0, slider_pos[0], slider_pos[0], &comp,4);

    // Show the result image. HighGUI use.
    show_iplimage( wndname02, image03 );

}




// Create toolbars. HighGUI use.
create_trackbar( barname01, wndname02, &slider_pos[0], 30, on_trackbar_FloodFill );



on_trackbar_FloodFill(0);



// Show the source image. HighGUI use.
show_iplimage( wndname01, image02 );


// Wait for a key stroke; the same function arranges events processing                
wait_key(0);
cvReleaseImage(&image01);
cvReleaseImage(&image02);
cvReleaseImage(&image03);


destroy_window(wndname01);
destroy_window(wndname02);
