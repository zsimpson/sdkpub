char wname[] = "Processed frame";
char barname1[] = "Red";
char barname2[] = "Green";
char barname3[] = "Blue";
int slider_pos[3] = {16, 16, 16};
IPLIMAGE im = 0;
IPLIMAGE temp = 0, temp16 = 0;

void threshold(IPLIMAGE in, IPLIMAGE out, int* thresh)
{
    IplROI roi = {0, 0, 0, 0, 0};
    int i;
    
    roi.width = in->width;
    roi.height = in->height;
    in->roi = &roi;
    out->roi = &roi;
    
    if(!temp)
        temp = cvCreateImage(cvSize(in->width, in->height), IPL_DEPTH_8U, 1);
    if(!temp16)
        temp16 = cvCreateImage(cvSize(in->width, in->height), IPL_DEPTH_16S, 1);
    temp->origin = in->origin;
    temp16->origin = in->origin;
   
    for(i = 0; i < 3; i++)
    {
        roi.coi = i + 1;
        //cvThreshold(in, out, (char)(thresh[i]*8), 255, CV_THRESH_BINARY);
        cvCopy(in, temp,0);
        cvLaplace(temp, temp16, 5);
        cvConvertScale(temp16, temp,1,0);
        cvCopy(temp, out,0);
    }
    
    in->roi = 0;
    out->roi = 0;
}

void process(IPLIMAGE image)
{
    if(!im)
        im = cvCloneImage(image);
    else
        cvCopy(image, im,0);
        
    
    threshold(im, im, slider_pos);
    show_iplimage(wname, im);
}

named_window(wname, 0);
create_trackbar(barname1, wname, &slider_pos[0], 31, 0);
create_trackbar(barname2, wname, &slider_pos[1], 31, 0);
create_trackbar(barname3, wname, &slider_pos[2], 31, 0);
play_ds(process);
