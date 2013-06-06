/********************************************************************************
*
*
*  This program is demonstration for ellipse fitting. Program finds 
*  contours and approximate it by ellipses.
*
*  Trackbar specify threshold parametr.
*
*  White lines is contours. Red lines is fitting ellipses.
*
*
*  Autor:  Denis Burenkov.
*
*
*
********************************************************************************/

char file_name[] = "image009.bmp";

char wndname01[] = "Source image";
char wndname02[] = "Thrshold image";
char barname01[] = "Threshold factor";
int slider_pos[1] = {70};


// Load the source image. HighGUI use.
IPLIMAGE image01 = load_iplimage(file_name);

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


// Define trackbar callback functon. This function find contours,
// draw it and approximate it by ellipses.
void func(int h)
{
    CvMemStorage* stor;
    CvSeq* cont;
    CvBox2D32f* box;
    CvPoint* PointArray;
    CvPoint2D32f* PointArray2D32f;
    
    // Create dynamic structure and sequence.
    stor = cvCreateMemStorage(0);
    cont = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint) , stor);
    
    // Threshold the source image. This needful for cvFindContours().
    cvThreshold( image03, image02, slider_pos[0], 255, CV_THRESH_BINARY );
    
    // Find all contours.
    cvFindContours( image02, stor, &cont, sizeof(CvContour), 
                    CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    
    // Clear images. IPL use.
    cvSetZero(image02);
    cvSetZero(image04);
    
    // This cycle draw all contours and approximate it by ellipses.
    for(;cont;cont = cont->h_next)
    {   
        int i; // Indicator of cycle.
        int count = cont->total; // This is number point in contour
        CvPoint center;
        CvSize size;
        
        // Number point must be more than or equal to 6 (for cvFitEllipse_32f).        
        if( count < 6 )
            continue;
        
        // Alloc memory for contour point set.    
        PointArray = malloc( count*sizeof(CvPoint) );
        PointArray2D32f= malloc( count*sizeof(CvPoint2D32f) );
        
        // Alloc memory for ellipse data.
        box = malloc(sizeof(CvBox2D32f));
        
        // Get contour point set.
        cvCvtSeqToArray(cont, PointArray, CV_WHOLE_SEQ);
        
        // Convert CvPoint set to CvBox2D32f set.
        for(i=0; i<count; i++)
        {
            PointArray2D32f[i].x = PointArray[i].x;
            PointArray2D32f[i].y = PointArray[i].y;
        }
        
        // Fits ellipse to current contour.
        cvFitEllipse(PointArray2D32f, count, box);
        
        // Draw current contour.
        cvDrawContours(image04,cont,RGB(255,255,255),RGB(255,255,255),0,1, 8);
        
        // Convert ellipse data from float to integer representation.
        center.x = box->center.x;
        center.y = box->center.y;
        size.width = box->size.width/2;
        size.height = box->size.height/2;
        box->angle = -box->angle;
        
        // Draw ellipse.
        cvEllipse(image04, 
                  center,
                  size,
                  box->angle,
                  0,
                  360,
                  RGB(0,0,255),
                  1);
        
        // Free memory.          
        free(PointArray);
        free(PointArray2D32f);
        free(box);
    }
    
    // Show image. HighGUI use.
    show_iplimage(wndname02, image04);
    
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