#define NUMBER 50
char wndname[] = "Primitives";
int i;

// Load the source image
IPLIMAGE image = load_iplimage("headband.bmp");


// Create a window
named_window(wndname, 0);
show_iplimage(wndname,image);

srand(11111);
CvPoint pt1,pt2;

for (i = 0; i< NUMBER; i++)
{
pt1.x=rand()/80;
pt1.y=rand()/80;
pt2.x=rand()/80;
pt2.y=rand()/80;

cvLine( image,pt1, pt2,
CV_RGB(rand()/100,rand()/100,rand()/100), rand()/3000, 8 );
show_iplimage(wndname,image);
}

for (i = 0; i< NUMBER; i++)
{
pt1.x=rand()/80;
pt1.y=rand()/80;
pt2.x=rand()/80;
pt2.y=rand()/80;

cvRectangle( image,pt1, pt2, 
CV_RGB(rand()/100,rand()/100,rand()/100),
rand()/3000 );
show_iplimage(wndname,image);
}

double angle;
CvSize sz;

for (i = 0; i< NUMBER; i++)
{
pt1.x=rand()/100;
pt1.y=rand()/100;
sz.width =rand()/50;
sz.height=rand()/50;
sz.height = sz.width = 100;
angle =((double)rand())*3.14/12000.0;

cvEllipse( image,
pt1, sz, angle,
angle - 100,
angle + 200,
CV_RGB(rand()/100,rand()/100,rand()/100), 6 );

show_iplimage(wndname,image);
}

CvPoint  ptt[6];
CvPoint* pt[6];

pt[0] = &(ptt[0]);
pt[1] = &(ptt[1]);
pt[2] = &(ptt[2]);
pt[3] = &(ptt[3]);
pt[4] = &(ptt[4]);
pt[5] = &(ptt[5]);

int  arr[2];
arr[0] = 3;
arr[1] = 3;

for (i = 0; i< NUMBER; i++)
{
pt[0]->x=rand()/100;
pt[0]->y=rand()/100;
pt[1]->x=rand()/100;
pt[1]->y=rand()/100;
pt[2]->x=pt[0]->x;
pt[2]->y=pt[0]->y;
pt[3]->x=rand()/100;
pt[3]->y=rand()/100;
pt[4]->x=rand()/100;
pt[4]->y=rand()/100;
pt[5]->x=pt[3]->x;
pt[5]->y=pt[3]->y;

cvPolyLine( image, &pt,&arr, 2, 1, 
CV_RGB(rand()/100,rand()/100,rand()/100), 2, 8 );

show_iplimage(wndname,image);
}

for (i = 0; i< NUMBER; i++)
{
pt[0]->x=rand()/100;
pt[0]->y=rand()/100;
pt[1]->x=rand()/100;
pt[1]->y=rand()/100;
pt[2]->x=pt[0]->x;
pt[2]->y=pt[0]->y;
pt[3]->x=rand()/100;
pt[3]->y=rand()/100;
pt[4]->x=rand()/100;
pt[4]->y=rand()/100;
pt[5]->x=pt[3]->x;
pt[5]->y=pt[3]->y;

cvFillPoly( image, 
&pt,&arr,2,CV_RGB(rand()/100,rand()/100,rand()/100) );

show_iplimage(wndname,image);
}

for (i = 0; i< NUMBER; i++)
{
pt1.x=rand()/80;
pt1.y=rand()/80;
pt2.x=rand()/80;
pt2.y=rand()/80;

cvCircle (image, pt1, rand()/120,
CV_RGB(rand()/100,rand()/100,rand()/100) , 1);
show_iplimage(wndname,image);
}


CvFont font;

for (i = 1; i< NUMBER; i++)
{
pt1.x=rand()/150;
pt1.y=rand()/110;

cvInitFont( &font , CV_FONT_VECTOR0 ,
rand()/5000.0, rand()/5000.0, 
rand()/40000.0, rand()/2000.0 );

cvPutText( image, "Hawk",
pt1, &font,
CV_RGB((rand()/100)*10/i,(rand()/100)*10/i,(rand()/100)*10/i));

show_iplimage(wndname,image);
}

cvInitFont( &font , CV_FONT_VECTOR0 ,
1, 2, 
0.0, 7 );

pt1.x=40;
pt1.y=200;

for(i = 0; i < 255; i++)
{
    cvPutText( image, "OpenCV forever!",
    pt1, &font,
    CV_RGB(255,i,i));
    show_iplimage(wndname,image);
}


// Wait for a key stroke; the same function arranges events processing
wait_key(0);
cvReleaseImage(&image);
destroy_window(wndname);
