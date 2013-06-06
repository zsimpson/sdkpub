int ncameras;
int c1 = 1;
int c0 = 0;
IplImage* img;
int i;

ncameras = cvcamGetCamerasCount();

printf("count = %d\n", ncameras);

cvcamSetProperty(0, "enable", (void*)&c1);
cvcamSetProperty(0, "render", (void*)&c0);
cvcamSetProperty(0, "callback", NULL);

cvcamGetProperty(0, "video_pp", 0);

cvcamInit();

printf("start\n");
cvvNamedWindow("test", 0);
cvcamStart();

printf("start3\n");

for(i = 0; i < 100; )
{
    cvcamGetProperty(0, "raw_image", &img);
    cvvShowImage("test", img);
}

