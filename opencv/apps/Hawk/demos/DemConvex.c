/********************************************************************************
*
*
*  This program is demonstration for functions: cvConvexHull() and
*  cvConvexityDefects. Program finds contours, convex hull 
*  and defects of convexity of this contours.
*
*  Trackbar specify threshold parametr.
*
*  White lines is contours. Blue lines is convex hull.
*  Red triangles marks defects of convexity.
*
*
*  Autor:  Denis Burenkov.
*
*
*
********************************************************************************/

char file_name[] = "image009.bmp";

char wndname01[] = "Source image";
char wndname02[] = "Output image";
char barname01[] = "Threshold factor";
int slider_pos[1] = {70};


// Load the source image. HighGUI use.
IPLIMAGE image01 = load_iplimage( file_name );

if(image01==NULL)
{
    printf("File '%s' not found.\n", file_name);
    
}

// Create the destination images. HighGUI use.
IPLIMAGE image02 = cvCreateImage(cvSize(image01->width, image01->height),
                                image01->depth,
                                1);

IPLIMAGE image03 = cvCreateImage(cvSize(image01->width, image01->height),
                                image01->depth,
                                1);
                                              
IPLIMAGE image04 = cvCreateImage(cvSize(image01->width, image01->height),
                                image01->depth,
                                3);

// Make onechannel image. IPL use.
iplColorToGray(image01,image03);
                         

// Create windows. HighGUI use.
named_window(wndname01, 0);
named_window(wndname02, 0);

// Show the image. HighGUI use.
show_iplimage(wndname01, image03);




// Define trackbar callback functon. This function find contours, convex hull
// and defects of convexity. Then draw it all.
void func(int h)
{
    CvMemStorage* stor;
    CvMemStorage* stor02;
    CvMemStorage* stor03;
    CvSeq* cont;
    CvSeq* seqhull;
    CvSeq* defects;
    int* hull;
    int hullsize;
    CvPoint* PointArray;
    CvConvexityDefect* defectArray;
    
    
    // Create memory storage for sequence.
    stor = cvCreateMemStorage(0);
    stor02 = cvCreateMemStorage(0);
    stor03 = cvCreateMemStorage(0);
            
    // Threshold the source image. This needful for cvFindContours().
    cvThreshold( image03, image02, slider_pos[0], 255, CV_THRESH_BINARY );
    
    // Find all contours.
    cvFindContours( image02, stor, &cont, sizeof(CvContour), 
                    CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    
    // Clear image
    cvSetZero(image04);
    
    // This cycle draw all contours and find convex hull
    // and defects of convexity.
    for(;cont;cont = cont->h_next)
    {   
        int i;                   // Indicator of cycles.
        int count = cont->total; // This is number point in contour
        CvPoint center;
        CvSize size;
        
        
        // Alloc memory for contour point set.    
        PointArray = malloc( count*sizeof(CvPoint) );
                
        // Alloc memory for indices of convex hull vertices.
        hull = malloc(sizeof(int)*count);
        
        // Get contour point set.
        cvCvtSeqToArray(cont, PointArray, CV_WHOLE_SEQ);
        
                
        // Find convex hull for curent contour.
        cvConvexHull( PointArray,
                      count,
                      NULL,
                      CV_COUNTER_CLOCKWISE,
                      hull,
                      &hullsize);
        
        // Find convex hull for current contour.
        // This required for cvConvexityDefects().
        seqhull = cvContourConvexHull( cont,
                             CV_COUNTER_CLOCKWISE,
                             stor02);
        
        // This required for cvConvexityDefects().
        // Otherwise cvConvexityDefects() falled.
        if( hullsize < 4 )
            continue;
         
        // Find defects of convexity of current contours.                        
        defects = cvConvexityDefects( cont,
                            seqhull,
                            stor03);
        
        // This cycle marks all defects of convexity of current contours.
        for(;defects;defects = defects->h_next)
        {
            int nomdef = defects->total; // defect amount
            
            if(nomdef == 0)
                continue;
             
            // Alloc memory for defect set.   
            defectArray = malloc(sizeof(CvConvexityDefect)*nomdef);
            
            // Get defect set.
            cvCvtSeqToArray(defects,defectArray, CV_WHOLE_SEQ);
            
            // Draw marks for all defects.
            for(i=0; i<nomdef; i++)
            {
                cvLine(image04, *(defectArray[i].start), 
                            *(defectArray[i].depth_point),RGB(0,0,255), 0, 8);
                cvLine(image04, *(defectArray[i].depth_point),
                             *(defectArray[i].end),RGB(0,0,255), 0, 8);
            }
             
            // Free memory.       
            free(defectArray);
        }
        
        // Draw current contour.
        cvDrawContours(image04,cont,RGB(255,255,255),RGB(255,255,255),0,1, 8);
        
        // Draw convex hull for current contour.        
        for(i=0; i<hullsize-1; i++)
        {
            cvLine(image04, PointArray[hull[i]], 
                            PointArray[hull[i+1]],RGB(255,0,0),0, 8);
        }
        cvLine(image04, PointArray[hull[hullsize-1]],
                             PointArray[hull[0]],RGB(255,0,0),0, 8);
        
          
        // Free memory.          
        free(PointArray);
        free(hull);
        
    }
    
    // Show image. HighGUI use. 
    show_iplimage(wndname02, image04);
    
    // Free memory.
    cvReleaseMemStorage(&stor);
    cvReleaseMemStorage(&stor03);
    cvReleaseMemStorage(&stor02);

    }


func(0);

// Create toolbars. HighGUI use.
create_trackbar(barname01, wndname02, &slider_pos[0], 255, func);


// Wait for a key stroke; the same function arranges events processing                
wait_key(0);
cvReleaseImage(&image01);
cvReleaseImage(&image02);
cvReleaseImage(&image03);

destroy_window(wndname01);
destroy_window(wndname02);

//                              END