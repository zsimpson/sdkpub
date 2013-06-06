/************************************************************************************
*
*
*  This program is demonstration for histogram and functions: cvCreateHist(), 
*  cvSetHistThresh(), cvCalcHist(), cvNormalizeHist(), cvQueryHistValue_1D(),
*  cvReleaseHist() and cvCopyHist().
*
*
*  Trackbar specify normalize factor for histogram value.
*
*
*
*  Autor:  Denis Burenkov
*
*
************************************************************************************/

#define DIMENSION_SIZE   50

char file_name[] = "EXPO0002.bmp";

char wndname01[] = "Source image";
char wndname02[] = "Histogram";
char barname01[] = "Normalize factor";
int dims[1] = {DIMENSION_SIZE};
float thresh[1][2] = { {0, 255} };
float* pthresh[1] = { thresh[0] };
int slider_pos[1] = {2000};

// Load the source image. HighGUI use.
IPLIMAGE image01 = load_iplimage( file_name );

if(image01==NULL)
{
    printf("File '%s' not found.\n", file_name);
    
}

// Create the destination images. HighGUI use.
IplImage * image02 = cvCreateImage( cvSize(image01->width,image01->height),
                                    IPL_DEPTH_8U,
                                    1);
IplImage * image03 = cvCreateImage( cvSize(image01->width,image01->height),
                                    IPL_DEPTH_8U,
                                    3);
                                    
// Make onechannel image.
cvCvtColor(image01,image02, CV_BGR2GRAY);


// Created histogram headers. OpenCV use.
CvHistogram* hist01 = cvCreateHist(1,               // Histogram dimension number.
                                   dims,            // Dimension size array.
                                   CV_HIST_ARRAY,   // Histogram type.
                                   0, 1);  
                                   
CvHistogram* hist02 = cvCreateHist(1, dims, CV_HIST_ARRAY, 0, 1);


// Set bounds of histogram bins. The histogram or back project are calculated 
// if within the specified boundaries. 
// OpenCV use.
cvSetHistBinRanges( hist01,  // Destination histogram.
                 pthresh, 1); // Pointer to the array of threshold values.



// Create windows. HighGUI use.
named_window( wndname01, 0 );
named_window( wndname02, 0 );

// Show the image. HighGUI use.
show_iplimage( wndname01, image02 );


// Calculated the histogram. OpenCV use. 
cvCalcHist( &image02,  // Source images.
            hist01,    // Pointer to the histogram.
            0, 0 );       // Clear flag.


// Define trackbar callback functon. This function normalize and draw histogram.
void ShowHist(int h)
{
    int i;
    CvPoint pt1, pt2;
    pt2.x=0;
    pt2.y=image01->height;
    
    // Clear image. OpenCV use.
    //cvFillImage(image03,0); //old code
    cvSetZero(image03);
    
    
    // Copy histogram to save data. OpenCV use.
    cvCopyHist(hist01,    // Source histogram.
               &hist02);  // Pointer to destination histogram.
    
    // Normalize histogram.
    // The sum of histogram bins becomes equal to factor.
    // OpenCV use.
    cvNormalizeHist( hist02,           //Pointer to the histogram.
                     slider_pos[0] );  //Normalize factor.
    
    // Draw histogram.
    for(i=0; i<DIMENSION_SIZE; i++)
    {
        pt1.x=pt1.x+5;
        pt1.y=image01->height -
         cvQueryHistValue_1D(hist02, // Pointer to the source histogram.
                             i);     // Address of a required element.
         // The function cvQueryHistValue_1D() returns the
         // value of the specified histogram bin.
         
        pt2.x=pt2.x+5;
        
        cvLine(image03, pt1, pt2, CV_RGB(200,0,0), 2, 8);
    }
    
    // Show the image. HighGUI use.
    show_iplimage( wndname02, image03 );
}



ShowHist(0);

// Create toolbars. HighGUI use.
create_trackbar(barname01, 
                wndname02,
                &slider_pos[0],
                4000,
                ShowHist);

// Wait for a key stroke; the same function arranges events processing                
wait_key(0);
cvReleaseImage(&image01);
cvReleaseImage(&image02);
cvReleaseImage(&image03);

destroy_window(wndname01);
destroy_window(wndname02);

cvReleaseHist( &hist01 );
cvReleaseHist( &hist02 );

//                                    END