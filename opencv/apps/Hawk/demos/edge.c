char wndname[] = "Edge";
char tbarname[] = "Threshold";
int edge_thresh = 1;

// Load the source image
IPLIMAGE image = load_iplimage("headband.bmp");

// Create the output image
IPLIMAGE cedge = cvCreateImage(cvSize(image->width,image->height), IPL_DEPTH_8U, 3);

IPLIMAGE temp = cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U, 3);

// Convert to grayscale
IPLIMAGE gray = cvCreateImage(cvSize(image->width,image->height), IPL_DEPTH_8U, 1);
IPLIMAGE edge = cvCreateImage(cvSize(image->width,image->height), IPL_DEPTH_8U, 1);
cvCvtColor(image, gray, CV_BGR2GRAY);

// define a trackbar callback
void on_trackbar(int h)
{
    int i;
  
    // Run the edge detector on grayscale
    cvCanny(gray, edge, 0.0f, (float)edge_thresh*5, 3);
  
    // Apply the edge image as a mask to the color
    cvCvtColor( edge, temp, CV_GRAY2BGR );
    cvAnd(image, temp, cedge, 0);
    
    show_iplimage(wndname, cedge);
}

// Create a window
named_window(wndname, 0);

// create a toolbar 
create_trackbar(tbarname, wndname, &edge_thresh, 100, on_trackbar);

// Show the image
on_trackbar(0);

// Wait for a key stroke; the same function arranges events processing
wait_key(0);
cvReleaseImage(&image);
cvReleaseImage(&gray);
cvReleaseImage(&edge);
cvReleaseImage(&temp);
destroy_window(wndname);

