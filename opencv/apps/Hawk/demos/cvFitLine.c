char wndname01[] = "Source image";
char wndname02[] = "Thrshold image";
char barname01[] = "Threshold factor";
int slider_pos[1] = {0};


// Load the source image. HighGUI use.
IPLIMAGE image01 = load_iplimage("image009.bmp");

// Create the destination images. HighGUI use.
IPLIMAGE image02 = cvCreateImage(cvSize(image01->width, image01->height),
                                image01->depth,
                                1);

IPLIMAGE image03 = cvCreateImage(cvSize(image01->width, image01->height),
                                image01->depth,
                                1);                           
// Make onechannel image.
cvCvtColor(image01,image03, CV_BGR2GRAY);
                         

// Create windows. HighGUI use.
named_window(wndname01, 0);
named_window(wndname02, 0);

// Show the image. HighGUI use.
show_iplimage(wndname01, image03);


// Define trackbar callback functon. This function find contours,
// draw it and approximate it by lines.
void func(int h)
{
    CvMemStorage* stor;
    CvSeq* cont;
    float * line;
    CvPoint* PointArray;
    CvPoint2D32f* PointArray2D32f;
    CvPoint FirstPoint;
    CvPoint LastPoint;
        
    // Create dynamic structure and sequence.
    stor = cvCreateMemStorage(0);
    cont = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint) , stor);
    
    // Threshold the source image. This needful for cvFindContours().
    cvThreshold( image03, image02, slider_pos[0], 255, CV_THRESH_BINARY );
    
    // Find all contours.
    cvFindContours( image02, stor, &cont, sizeof(CvContour), 
                    CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    
    // Clear image. IPL use.
    cvSetZero(image02);
    
    // This cycle draw all contours and approximate it by lines.
    for(;cont;cont = cont->h_next)
    {   
        int i; // Indicator of cycle.
        int count = cont->total; // This is number point in contour
        
        
        // Alloc memory for contour point set.    
        PointArray = malloc( count*sizeof(CvPoint) );
        PointArray2D32f= malloc( count*sizeof(CvPoint2D32f) );
        
        // Alloc memory for line data.
        line = malloc(4*sizeof(float));
        // Get contour point set.
        cvCvtSeqToArray(cont, PointArray, CV_WHOLE_SEQ);
        
        // Convert CvPoint set to CvBox2D32f set.
        for(i=0; i<count; i++)
        {
            PointArray2D32f[i].x = PointArray[i].x;
            PointArray2D32f[i].y = PointArray[i].y;
        }
        
        // Fits line to current contour.
        cvFitLine2D(PointArray2D32f,cont->total,CV_DIST_L2,NULL,0.01,0.01,line);
        
        FirstPoint.x=line[2]-100*line[0];
        FirstPoint.y=line[3]-100*line[1];
        
        LastPoint.x=line[2]+100*line[0];
        LastPoint.y=line[3]+100*line[1];
        
        // Draw current contour.
        cvDrawContours(image02,cont,255,255,0,1,8);
        //Fits lines only to sufficiently large contours
        if (cont->total > 50 ) 
            cvLine(image02,FirstPoint,LastPoint,150,1,0);
        
        // Free memory.          
        free(PointArray);
        free(PointArray2D32f);
        free(line);
    }
    
    // Show image. HighGUI use. 
    show_iplimage(wndname02, image02);
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

                            