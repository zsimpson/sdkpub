IPLIMAGE  image[2], image0, image1;
CvSize size;

int  w0, h0,i;
int  threshold1, threshold2;
int  l,level;
int sthreshold1, sthreshold2;
int  l_comp;
int block_size = 1000;
float  parameter;
double threshold;
double rezult, min_rezult;
CvFilter filter = CV_GAUSSIAN_5x5;
CvConnectedComp *cur_comp, min_comp;
CvSeq *comp;
CvMemStorage *storage;

CvPoint pt1, pt2;

void ON_SEGMENT(int a)
{	
    
    cvPyrSegmentation(image0, image1, storage, &comp, 
                      level, threshold1, threshold2);

	l_comp = comp->total;

    printf("  l_comp = %d \n ",l_comp);
	i = 0;
    min_comp.value = 0;
	while(i<l_comp)
	{
        cur_comp = (CvConnectedComp*)cvGetSeqElem ( comp, i, 0);
        if(fabs(CV_RGB(255,0,0)- min_comp.value)>
           fabs(CV_RGB(255,0,0)- cur_comp->value))
           min_comp = *cur_comp;
/*          
    pt1.x = cur_comp->rect.x;
	pt2.x = cur_comp->rect.x + cur_comp->rect.width;
	pt1.y = cur_comp->rect.y;
	pt2.y = cur_comp->rect.y + cur_comp->rect.height;
    cvRectangle(image1, pt1, pt2, 255, 3);
*/   	         
     	i++;
	}
/*    
    pt1.x = min_comp.rect.x;
	pt2.x = min_comp.rect.x + min_comp.rect.width;
	pt1.y = min_comp.rect.y;
	pt2.y = min_comp.rect.y + min_comp.rect.height;
    cvRectangle(image1, pt1, pt2, 255, 3);
*/    
//    bitmap1 = get_image_cv(image1);
    show_iplimage("Segmentation", image1);


};

image[0] = load_iplimage("..\\Bitmaps\\parrot.bmp");

named_window("Source", 0);
show_iplimage("Source", image[0]);
wait_key(0);

printf("\n i = %d width = %d height = %d", i,size.width, size.height);   


named_window("Segmentation", 0);


storage = cvCreateMemStorage ( block_size );

image0 = cvCreateImage(cvSize(image[0]->width, image[0]->height), IPL_DEPTH_8U, 3);
image1 = cvCreateImage(cvSize(image[0]->width, image[0]->height), IPL_DEPTH_8U, 3);
cvCopy(image[0],image0,0); 
image0->roi = NULL;
image1->roi = NULL;
// segmentation of the color image
l = 1;
level =4;
threshold1 =255;
threshold2 =30;


ON_SEGMENT(1);

sthreshold1 = create_slider("Threshold1", "Segmentation", &threshold1, 255, ON_SEGMENT);
sthreshold2 = create_slider("Threshold2", "Segmentation",  &threshold2, 255, ON_SEGMENT);

show_iplimage("Segmentation", image1);
wait_key(0);

destroy_window("Segmentation");
destroy_window("Source");

cvReleaseMemStorage (&storage );


cvReleaseImage  (&image[0]);
cvReleaseImage  (&image0);
cvReleaseImage  (&image1);

