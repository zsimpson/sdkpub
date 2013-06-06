/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include <glob.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <malloc.h>
#include <errno.h>
#include <pthread.h>
#include "dialogs.h"


#include "cvcam.h"
#include "cvvidtypes.h"
#include "videodev.h"
#include "icvvideo.h"
#include "render.h"

const int FRAMES_FORMAT=0;
const int TIME_FORMAT = 1;

CvVideoCamera* cameras;
static int ncameras;
static pthread_mutex_t ioctlmutex=PTHREAD_MUTEX_INITIALIZER;


int cvcamGetCamerasCount()
{
    glob_t               pglob;
    int                     count, count1;
    int                     CamerasCount =  0;
    int*                    descriptors;
    
    struct video_capability VidCap;
    struct video_channel    Channel;
    
    if(ncameras)
        return ncameras;
    
    if(glob("/dev/video*",GLOB_MARK,NULL, &pglob))
    {
        fprintf(stderr, "cvcamGetCamerasCount:no video devices /dev/video(n)"
                        "found\n");
        return 0;
    }

    descriptors = (int*)malloc(pglob.gl_pathc*sizeof(int));
    
    for(count = 0; count < pglob.gl_pathc; count++)
    {
        descriptors[count] = open(pglob.gl_pathv[count],O_RDWR);
        if (descriptors[count]  != -1 )
        {
            pthread_mutex_lock(&ioctlmutex);
            if(ioctl(descriptors[count], VIDIOCGCAP, &VidCap)==-1)
            {
                pthread_mutex_unlock(&ioctlmutex);
                break;
            }
            pthread_mutex_unlock(&ioctlmutex);
            
            for(count1=0; count1<VidCap.channels; count1++)
                
            {
                Channel.channel = count1;
                
                pthread_mutex_lock(&ioctlmutex);
                if((ioctl(descriptors[count], VIDIOCGCHAN, &Channel) != -1))
                {
                    
                    Channel.norm = 1;
                    Channel.channel = count1;
                    
                    if((ioctl(descriptors[count],VIDIOCSCHAN, &Channel) != -1)&&
                        (ioctl(descriptors[count], VIDIOCGCAP, &VidCap)    != -1))
                    {
                        if(Channel.type&VIDEO_TYPE_CAMERA)
                        {
                            
                            cameras =
                                (CvVideoCamera*)realloc(cameras,
                                (CamerasCount+1)*sizeof(CvVideoCamera));
                            
                            if(!icvVideoSetDefaultValues(CamerasCount, 
                                descriptors[count],
                                count1, VidCap))    
                                break; 

                            
                            strcpy(cameras[CamerasCount].description.device,
                                pglob.gl_pathv[count]);
                            
                            strcpy(cameras[CamerasCount].description.DeviceDescription,
                                VidCap.name);
                            
                            strcpy(cameras[CamerasCount].description.ChannelDescription,
                                Channel.name);
                            
                            CamerasCount++;
                            pthread_mutex_unlock(&ioctlmutex);
                            break;
                            
                        }//if(Channel.type&VIDEO_TYPE_CAMERA)
                    }//if((ioctl(descriptors[count],VIDIOCSCHAN, &Channel) != -1)&&
                    //(ioctl(descriptors[count], VIDIOCGCAP, &VidCap)!=-1))
                }//if(ioctl(fd, VIDIOCSCHAN, &Channel) != -1)
                pthread_mutex_unlock(&ioctlmutex);
            }//for(count1=0; count1<VidCap.channels; count1++)
        }//if (descriptors[count] = open(pglob.gl_pathv[count],O_RDWR)  != -1 )
    }//for (count = 0; count < pglob.gl_pathc; count++)
    globfree(&pglob);
    free(descriptors);
    ncameras = CamerasCount;
    XInitThreads();
    return CamerasCount;
}
///////////////////////////////////////////////////////////////////////////////
int cvcamGetProperty(int camera, const char* property, void* value)
{
    if(!cameras||camera>ncameras-1||camera<0)
    {
        fprintf(stderr,"cvcamGetProperty:no such camera\n");
        return 0;
    }//if(!cameras||camera>ncameras-1||camera<0)
    
    IF_GETTING_PROPERTY("description")
    {
        strcpy(((CameraDescription*)value)->DeviceDescription,cameras[camera].description.DeviceDescription);
        strcpy(((CameraDescription*)value)->device, cameras[camera].description.device);
        strcpy(((CameraDescription*)value)->ChannelDescription,cameras[camera].description.ChannelDescription);
        
        ((CameraDescription*)value)->channel = cameras[camera].description.channel;
        
        ((CameraDescription*)value)->maxwidth = cameras[camera].description.maxwidth;
        ((CameraDescription*)value)->maxheight = cameras[camera].description.maxheight;
        ((CameraDescription*)value)->minwidth = cameras[camera].description.minwidth;
        ((CameraDescription*)value)->minheight = cameras[camera].description.minheight;
        
        return 1;
    }//IF_GETTING_PROPERTY("description")
    
    IF_GETTING_PROPERTY("enable")
    {
        *(int*)value = cameras[camera].enabled;
        return 1;
    }//IF_GETTING_PROPERTY("enable")
    
    IF_GETTING_PROPERTY("render")
    {
        *(int*)value = cameras[camera].rendered;
        //TODO: real call to rendering ioctl(if after initialisation)
        
        return 1;
    }//IF_GETTING_PROPERTY("render")
    
    IF_GETTING_PROPERTY("window")
    {
        *(Window*)value = cameras[camera].window;
        return 1;
    }//IF_GETTING_PROPERTY("window")
    
    IF_GETTING_PROPERTY("callback")
    {
        fprintf(stdout,"The property \"callback\" is set-only\n");
        return 0;
    }//IF_GETTING_PROPERTY("callback")
    
    IF_GETTING_PROPERTY("camera_pp")
    {
        icvVideoCameraPPDialog(camera);
        return 1;
    }//IF_GETTING_PROPERTY("camera_pp")
    
    IF_GETTING_PROPERTY("set_video_format")
    {
        /*
        if(!cameras[camera].initialised)
        {
        fprintf(stderr, "cvcamGetProperty, property = video_pp, camera\
        isn't initialised");
        return 0;
        }
        */
        ((VideoFormat*)value)->width = cameras[camera].videopp.width;
        ((VideoFormat*)value)->height = cameras[camera].videopp.height;
        
        ((VideoFormat*)value)->picture.brightness =
            cameras[camera].videopp.picture.brightness;
        
        ((VideoFormat*)value)->picture.hue =
            cameras[camera].videopp.picture.hue;
        
        ((VideoFormat*)value)->picture.colour =
            cameras[camera].videopp.picture.colour;
        
        ((VideoFormat*)value)->picture.contrast =
            cameras[camera].videopp.picture.contrast;
        
        ((VideoFormat*)value)->picture.whiteness   =
            cameras[camera].videopp.picture.whiteness;
        
        ((VideoFormat*)value)->picture.depth =
            cameras[camera].videopp.picture.depth;
        
        ((VideoFormat*)value)->picture.palette =
            cameras[camera].videopp.picture.palette;
        
        return 1;
    }//IF_GETTING_PROPERTY("set_video_format")
    
    IF_GETTING_PROPERTY("rectify_parameters")
    {
        fprintf(stdout,"TODO get prop rectify_parameters\n");
        return 1;
    }//IF_GETTING_PROPERTY("rectify_parameters")
    
    IF_GETTING_PROPERTY("stereo_parameters")
    {
        fprintf(stdout,"TODO get prop stereo_parameters\n");
        return 1;
    }//IF_GETTING_PROPERTY("stereo_parameters")
    
    IF_GETTING_PROPERTY("raw_image")
    {
        if(cameras[camera].capturestate != CAPTURING)
            return 0;
        icvVideoPauseCamera(camera);
        
        if(cameras[camera].callback == NULL)
            *((IplImage**)value) = cameras[camera].image;
        else
        {
            cameras[camera].callback((cameras[camera].image));
            *((IplImage**)value) = cameras[camera].image;
        }
        
        icvVideoResumeCamera(camera);
        //fprintf(stdout,"1-st image copied");
        
        return 1;
    }//IF_GETTING_PROPERTY("raw_image")
    
    IF_GETTING_PROPERTY("disparity")
    {
        fprintf(stdout,"TODO get prop disparity\n");
        return 1;
    }//IF_GETTING_PROPERTY("disparity")
    
    IF_GETTING_PROPERTY("stereo_image")
    {
        fprintf(stdout,"TODO get prop stereo_image\n");
        return 1;
    }//IF_GETTING_PROPERTY("stereo_image")
    
    IF_GETTING_PROPERTY("video_pp")
    {
        icvVideoVideoPPDialog(camera);
        return 1;
    }//IF_GETTING_PROPERTY("video_pp")

    IF_GETTING_PROPERTY(CVCAM_RNDWIDTH)
    {
        *(int*)value = cameras[camera].renderwidth;
        return 1;
    }//IF_GETTING_PROPERTY (CVCAM_RNDWIDTH)

    IF_GETTING_PROPERTY(CVCAM_RNDHEIGHT)
    {
     *(int*)value = cameras[camera].renderheight;
        return 1;
    }//IF_GETTING_PROPERTY("CVCAM_RNDHEIGHT")


    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////


int cvcamGetPropertiesList(int camera, const char** properties, int count)
{
    assert(properties);
    
    properties[0] = "description" ;
    properties[1] = "enable";
    properties[2] = "render";
    properties[3] = "window";
    properties[4] = "callback";
    properties[5] = "camera_pp";
    properties[6] = "video_pp" ;
    properties[7] = "raw_image";
    properties[8] = "set_video_format" ;
    
    return 9;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////


int cvcamSetProperty(int camera, const char* property, void* value)
{
    int k;
    
    if(!cameras||camera>ncameras-1||camera<0)
    {
        fprintf(stderr,"cvcamSetProperty: no such camera\n");
        return 0;
    }//if(!cameras||camera>ncameras-1)
    
    IF_SETTING_PROPERTY("description")
    {
        fprintf(stdout, "cvcamSetProperty: The property \"description\" cannot be "
                        "set\n");
        return 0;
    }//IF_SETTING_PROPERTY("description")
    
    IF_SETTING_PROPERTY("enable")
    {
        cameras[camera].enabled = (int)value;
        return 1;
    }//IF_SETTING_PROPERTY("enable")
    
    IF_SETTING_PROPERTY("render")
    {
        cameras[camera].rendered = (int)value;
        return 1;
    }//IF_SETTING_PROPERTY("render")
    
    IF_SETTING_PROPERTY("window")
    {
        cameras[camera].window = *(Window*)value;
        
        //fprintf(stdout,"TODO get prop window\n");
        return 1;
    }//IF_SETTING_PROPERTY("window")
    
    IF_SETTING_PROPERTY("callback")
    {
        cameras[camera].callback = ( void (*)(IplImage*) )value;
        return 1;
    }//IF_SETTING_PROPERTY("callback")

    IF_SETTING_PROPERTY("camera_pp")
    {
        fprintf(stdout,"TODO get prop camera_pp\n");
        return 1;
    }//IF_SETTING_PROPERTY("camera_pp")
    
    IF_SETTING_PROPERTY("description")
    {
        fprintf(stdout,"TODO get prop camera_pp\n");
        return 1;
    }//IF_SETTING_PROPERTY("camera_pp")
    
    IF_SETTING_PROPERTY("set_video_format")
    {
        k = icvVideoStop(camera);
        cameras[camera].initialised =0;
        if(
            (((VideoFormat*)value)->picture.brightness>0xffff)||
            (((VideoFormat*)value)->picture.hue>0xffff)||
            (((VideoFormat*)value)->picture.colour>0xffff)||
            (((VideoFormat*)value)->picture.contrast>0xffff)||
            (((VideoFormat*)value)->picture.whiteness>0xffff)
            )return 0;
        
        if(
            (((VideoFormat*)value)->width > cameras[camera].description.maxwidth)||
            (((VideoFormat*)value)->height > cameras[camera].description.maxheight)||
            (((VideoFormat*)value)->width < cameras[camera].description.minwidth)||
            (((VideoFormat*)value)->height < cameras[camera].description.minheight)
            )                                                                                   
            return 0;
        if(
            ((((VideoFormat*)value)->width == cameras[camera].description.maxwidth)&&
            (((VideoFormat*)value)->height == cameras[camera].description.maxheight))||
            ((((VideoFormat*)value)->width == cameras[camera].description.minwidth)&&
            (((VideoFormat*)value)->height == cameras[camera].description.minheight))||
            ((((VideoFormat*)value)->width == 320)&&                
            (((VideoFormat*)value)->height == 240))
            )
        {
            cameras[camera].videopp.width = ((VideoFormat*)value)->width;
            cameras[camera].videopp.height= ((VideoFormat*)value)->height;
        }
        else
        {
            if(
                ((((VideoFormat*)value)->width > 320)&&
                ((VideoFormat*)value)->height > 240)
                )
            {
                cameras[camera].videopp.width = 320;
                cameras[camera].videopp.height= 240;
            }else
            {
                cameras[camera].videopp.width=
                    cameras[camera].description.minwidth;
                
                cameras[camera].videopp.height=
                    cameras[camera].description.minheight;
            }
        }
        
        cameras[camera].videopp.picture.brightness=
            ((VideoFormat*)value)->picture.brightness;
        
        cameras[camera].videopp.picture.hue=
            ((VideoFormat*)value)->picture.hue;
        
        cameras[camera].videopp.picture.colour=
            ((VideoFormat*)value)->picture.colour;
        
        cameras[camera].videopp.picture.contrast=
            ((VideoFormat*)value)->picture.contrast ;
        
        cameras[camera].videopp.picture.whiteness=
            ((VideoFormat*)value)->picture.whiteness;
        
        cameras[camera].videopp.picture.depth=
            icvVideoFormat2Depth(
            ((VideoFormat*)value)->picture.palette);
        
        if(!cameras[camera].videopp.picture.depth)
            return 0;

        cameras[camera].videopp.picture.palette=
            ((VideoFormat*)value)->picture.palette;
        
        cvcamInit();

        if(k)
            cvcamStart();
        //fprintf(stdout,"TODO get prop video_pp\n");
        return 1;
    }//IF_SETTING_PROPERTY("set_video_format")
    
    IF_SETTING_PROPERTY("rectify_parameters")
    {
        fprintf(stdout,"TODO get prop rectify_parameters\n");
        return 1;
    }//IF_SETTING_PROPERTY("rectify_parameters")
    
    IF_SETTING_PROPERTY("stereo_parameters")
    {
        fprintf(stdout,"TODO get prop stereo_parameters\n");
        return 1;
    }//IF_SETTING_PROPERTY("stereo_parameters")
    
    IF_SETTING_PROPERTY("raw_image")
    {
        fprintf(stdout,"TODO get prop raw_image\n");
        return 1;
    }//IF_SETTING_PROPERTY("raw_image")
    
    IF_SETTING_PROPERTY("disparity")
    {
        fprintf(stdout,"TODO get prop disparity\n");
        return 1;
    }//IF_SETTING_PROPERTY("disparity")
    
    IF_SETTING_PROPERTY("stereo_image")
    {
        fprintf(stdout,"TODO get prop stereo_image\n");
        return 1;
    }//IF_SETTING_PROPERTY("stereo_image")

    IF_SETTING_PROPERTY("video_pp")
    {
        fprintf(stdout,"TODO get prop set_video_format\n");
        return 1;
    }//IF_SETTING_PROPERTY( "video_pp" )


    IF_SETTING_PROPERTY(CVCAM_RNDWIDTH)
    {
        k=icvVideoStop(camera);
    cameras[camera].renderwidth = *(int*)value;
    if(k)
        cvcamStart();
    return 1;

    }//IF_SETTING_PROPERTY(CVCAM_RNDWIDTH)

    IF_SETTING_PROPERTY(CVCAM_RNDHEIGHT)
    {
        k=icvVideoStop(camera);
    cameras[camera].renderheight = *(int*)value;
    if(k)
        cvcamStart();
    return 1;

    }//IF_SETTING_PROPERTY(CVCAM_RNDHEIGHT)

    return 0;
}
///////////////////////////////////////////////////////////////////////////////

int cvcamInit()
{
    int camera;
    for(camera=0; camera<ncameras; camera++)
    {
        icvVideoInit(camera);
    }//for(camera=0; camera<ncameras; camera++)

    return 1;
}

///////////////////////////////////////////////////////////////////////////////
int cvcamStart()
{
    int camera;
    static pthread_mutex_t cvVideoStartmutex = PTHREAD_MUTEX_INITIALIZER;
    cvcamInit();
    pthread_mutex_lock(&cvVideoStartmutex);
    
    for(camera=0; camera<ncameras; camera++)
    {
        if(cameras[camera].enabled)
        {
            if(cameras[camera].capturestate == READY)
            {
                cameras[camera].capturestate = CAPTURING;
                
                if(pthread_create((&(cameras[camera].thread)),NULL,
                    icvVideoCaptureProc, (void*)camera))
                {
                    fprintf(stderr, "cvcamStart: couldn't start thread for "
                                    "camera %d\n", camera);
                    pthread_mutex_unlock(&cvVideoStartmutex);
                    return 0;
                }//if pthread_create ...
                
                if(cameras[camera].rendered)
                    icvVideoRenderStart(camera);
            }//if(cameras[camera].state == READY)
        }//if(cameras[camera].IsEnabled)
    }//for(camera=0; camera<ncameras; camera++)
    
    pthread_mutex_unlock(&cvVideoStartmutex);
    return 1;
}
////////////////////////////////////////////////////////////////////////////////
void* icvVideoCaptureProc(void* arg)
{
    int camera = (int) arg;
    
    //lock frame 0
    pthread_mutex_lock(&(cameras[camera].mutex0));
    while(cameras[camera].capturestate == CAPTURING)
    {
        //lock frame 1
        pthread_mutex_lock(&(cameras[camera].mutex1));
        
        cameras[camera].currentframe = 0;
        
        //capture frame 1
        cameras[camera].vid_mmap.frame=1;
        pthread_mutex_lock(&ioctlmutex);
        if(ioctl(cameras[camera].device, VIDIOCMCAPTURE,
            &(cameras[camera].vid_mmap)) == -1)
        {
            fprintf(stderr,"icvVideoCaptureProc:ioctl VIDIOCMCAPTURE "
                            "failed\n");
        
            pthread_mutex_unlock(&ioctlmutex);
            cameras[camera].capturestate = FINISHED;
            cameras[camera].initialised = 0;
            return NULL;
        }
        
        pthread_mutex_unlock(&ioctlmutex);
        
        //sync frame 0
        cameras[camera].vid_mmap.frame=0;
        pthread_mutex_lock(&ioctlmutex);
        if(ioctl(cameras[camera].device, VIDIOCSYNC,
            &(cameras[camera].vid_mmap.frame)) == -1)
        {
            pthread_mutex_unlock(&ioctlmutex);
            fprintf(stderr, "icvVideoCaptureProc:ioctl VIDIOCSYNC "
                            "failed\n");
            cameras[camera].capturestate = FINISHED;
            cameras[camera].initialised = 0;
            return NULL;
        }
        pthread_mutex_unlock(&ioctlmutex);
        
        cameras[camera].currentframe = 0;
        //unlock frame0
        cvSetImageData(cameras[camera].image,
            (void*)(cameras[camera].memorymap+
            cameras[camera].mbuf.offsets[0]),
            cameras[camera].videopp.width*
            icvVideoFormat2Depth(
            cameras[camera].videopp.picture.palette)/8);
        
        pthread_mutex_unlock(&(cameras[camera].mutex0));
        
        //lock frame 0
        pthread_mutex_lock(&(cameras[camera].mutex0));
        
        cameras[camera].currentframe = 1;
        
        //capture frame 0
        cameras[camera].vid_mmap.frame=0;
        pthread_mutex_unlock(&ioctlmutex);
        if(ioctl(cameras[camera].device, VIDIOCMCAPTURE,
            &(cameras[camera].vid_mmap)) == -1)
        {
            fprintf(stderr, "icvVideoCaptureProc:ioctl VIDIOCMCAPTURE "
                            "failed");
            pthread_mutex_unlock(&ioctlmutex);
            cameras[camera].capturestate = FINISHED;
            cameras[camera].initialised = 0;
            return NULL;
        }
        
        pthread_mutex_unlock(&ioctlmutex);
        
        //sync frame 1
        cameras[camera].vid_mmap.frame=1;
        pthread_mutex_lock(&ioctlmutex);
        if(ioctl(cameras[camera].device, VIDIOCSYNC,
            &(cameras[camera].vid_mmap.frame)) == -1)
        {
            pthread_mutex_unlock(&ioctlmutex);
            fprintf(stderr, "icvVideoCaptureProc:ioctl VIDIOCSYNC"
                            "failed\n");
            cameras[camera].capturestate = FINISHED;
            cameras[camera].initialised = 0;
            return NULL;
        }
        
        pthread_mutex_unlock(&ioctlmutex);
        
        cameras[camera].currentframe = 1;
        
        //unlock frame 1
        cvSetImageData(cameras[camera].image,
            (void*)(cameras[camera].memorymap+
            cameras[camera].mbuf.offsets[1]),
            cameras[camera].videopp.width*
            icvVideoFormat2Depth(
            cameras[camera].videopp.picture.palette)/8);
        pthread_mutex_unlock(&(cameras[camera].mutex1));
        
    }//while(cameras[camera].state == CAPTURING)

    //sync frame 0 - otherwise device can be busy next time
    cameras[camera].vid_mmap.frame=0;
    pthread_mutex_unlock(&ioctlmutex);
    
    if(ioctl(cameras[camera].device, VIDIOCSYNC,
        &(cameras[camera].vid_mmap.frame)) == -1)
    {
        pthread_mutex_unlock(&ioctlmutex);
        fprintf(stderr, "icvVideoCaptureProc:ioctl VIDIOCSYNC "
                        "failed\n");
        
        cameras[camera].capturestate = FINISHED;
        cameras[camera].initialised = 0;
        
        return NULL;
    }
    pthread_mutex_unlock(&ioctlmutex);
    
    cameras[camera].capturestate = FINISHED;
    pthread_exit(NULL);
}
////////////////////////////////////////////////////////////////////////////////

int cvcamExit()
{
    ncameras=0;
    if(cameras)
        free(cameras);
    return 1;
}

////////////////////////////////////////////////////////////////////////////////

int icvVideoPauseCamera(int camera)
{
    if(!(cameras[camera].capturestate==CAPTURING))
        return 1;
    if(cameras[camera].currentframe==0)
        pthread_mutex_lock(&(cameras[camera].mutex0));
    else
        pthread_mutex_lock(&(cameras[camera].mutex1));
    return 0;
}
////////////////////////////////////////////////////////////////////////////////

int icvVideoResumeCamera(int camera)
{
    if(!(cameras[camera].capturestate==CAPTURING))
        return 1;
    if(cameras[camera].currentframe==0)
        pthread_mutex_unlock(&(cameras[camera].mutex0));
    else
        pthread_mutex_unlock(&(cameras[camera].mutex1));
    
    return 0;
}
////////////////////////////////////////////////////////////////////////////////

int cvcamPause()
{
    int i;
    
    for(i=0; i<ncameras; i++)
    {
        icvVideoPauseCamera(i);
    }
    
    
    return 0;

}
////////////////////////////////////////////////////////////////////////////////

int cvcamResume()
{
    int i;
    
    for(i=0; i<ncameras; i++)
    {
        icvVideoResumeCamera(i);
    }
    
    return 0;
    
}
////////////////////////////////////////////////////////////////////////////////

int icvVideoInit(int camera)
{
    CvSize size;
    struct video_channel Channel;
    struct video_capability VidCap;
    pthread_mutexattr_t mutexattr;
    static pthread_mutex_t icvVideoInitmutex = PTHREAD_MUTEX_INITIALIZER;
    mutexattr.__mutexkind = PTHREAD_MUTEX_RECURSIVE_NP;
    pthread_mutex_lock(&icvVideoInitmutex);
    
    if(cameras[camera].initialised)
    {
    /*
    fprintf(stderr, "icvVideoInit:camera %d is already "
                        "initialized\n",camera);*/
        pthread_mutex_unlock(&icvVideoInitmutex);
        return 0;
    }
    
    if(cameras[camera].enabled)
    {
        cameras[camera].vid_mmap.frame  = 0;
        
        cameras[camera].vid_mmap.width  =
            cameras[camera].videopp.width;
        
        cameras[camera].vid_mmap.height =
            cameras[camera].videopp.height;
        
        cameras[camera].vid_mmap.format =
            cameras[camera].videopp.picture.palette;
        
        cameras[camera].currentframe = 0;
        
        pthread_mutex_lock(&ioctlmutex);
        if(ioctl(cameras[camera].device,VIDIOCSPICT,
            &(cameras[camera].videopp.picture) )==-1)
        {
            pthread_mutex_unlock(&ioctlmutex);
            fprintf(stdout, "icvVideoInit: ioctl VIDIOCSPICT failed\n");
            pthread_mutex_unlock(&icvVideoInitmutex);
            return 0;
        }
        pthread_mutex_unlock(&ioctlmutex);
        
        Channel.norm = 1;
        Channel.channel = cameras[camera].channel;
        pthread_mutex_lock(&ioctlmutex);
        if((ioctl(cameras[camera].device,VIDIOCSCHAN, &Channel) == -1)||
            (ioctl(cameras[camera].device, VIDIOCGCAP, &VidCap)==-1))
        {
            fprintf(stderr,
                "icvVideoInit: ioctl VIDIOCSCHAN or VIDIOCGCAP failed\n");
            pthread_mutex_unlock(&ioctlmutex);
            pthread_mutex_unlock(&icvVideoInitmutex);
            return 0;
        }
        pthread_mutex_unlock(&ioctlmutex);
        
        pthread_mutex_init(&(cameras[camera].mutex0), &mutexattr);
        pthread_mutex_init(&(cameras[camera].mutex1), &mutexattr);
        
        pthread_mutex_lock(&ioctlmutex);
        if(ioctl(cameras[camera].device, VIDIOCGMBUF,
            &(cameras[camera].mbuf)) == -1)
        {
            pthread_mutex_unlock(&ioctlmutex);
            fprintf(stdout, "icvVideoInit: ioctl VIDIOCGMBUF failed\n");
            pthread_mutex_unlock(&icvVideoInitmutex);
            return 0;
        }
        pthread_mutex_unlock(&ioctlmutex);
        
        cameras[camera].memorymap = (char*)mmap(0,
            cameras[camera].mbuf.size,
            PROT_READ|PROT_WRITE, MAP_SHARED,
            cameras[camera].device,
            0);
        
        if((int)cameras[camera].memorymap == -1)
        {
            fprintf(stderr, "icvVideoInit: mmap failed");
            pthread_mutex_unlock(&icvVideoInitmutex);
            return 0;
        }
        pthread_mutex_lock(&ioctlmutex);
        if(ioctl(cameras[camera].device,
            VIDIOCSCHAN, &Channel)==-1)
        {
            fprintf(stderr, "icvVideoInit: couldn't set channel %d",
                Channel.channel);
            pthread_mutex_unlock(&ioctlmutex);
            pthread_mutex_unlock(&icvVideoInitmutex);
            return 0;
        }
        pthread_mutex_unlock(&ioctlmutex);
        pthread_mutex_lock(&ioctlmutex);
        
        if(ioctl(cameras[camera].device, VIDIOCMCAPTURE,
            &(cameras[camera].vid_mmap)) == -1)
        {
            if(ioctl(cameras[camera].device, VIDIOCSYNC,
                cameras[camera].vid_mmap.frame )==-1)
            {
                fprintf(stderr, "icvVideoInit: ioctl VIDIOCMCAPTURE and "
                                "VIDIOCSYNC failed \n");
                //return 0;
            }//if ioctl(..., VIDIOCSYNK, ...)
            else
            {
                if(ioctl(cameras[camera].device, VIDIOCMCAPTURE,
                    &(cameras[camera].vid_mmap)) == -1)
                {
                    fprintf(stderr, "icvVideoInit: ioctl VIDIOCMCAPTURE "
                                    "failed \n");
                    pthread_mutex_unlock(&ioctlmutex);
                    pthread_mutex_unlock(&icvVideoInitmutex);
                    return 0;
                }//if ioctl(..., VIDIOCMCAPTURE, ...)
            }//else
        }//if ioctl(..., VIDIOCMCAPTURE, ...)
        
        pthread_mutex_unlock(&ioctlmutex);
        
        pthread_mutex_lock(&ioctlmutex);
        if(ioctl(cameras[camera].device, VIDIOCGMBUF,
            &(cameras[camera].mbuf)) == -1)
        {
            pthread_mutex_unlock(&ioctlmutex);
            pthread_mutex_unlock(&icvVideoInitmutex);
            return 0;
        }
        
        pthread_mutex_unlock(&ioctlmutex);
        
        size.width = cameras[camera].videopp.width;
        size.height = cameras[camera].videopp.height;
        
        assert(cameras[camera].videopp.picture.palette);
        assert(icvVideoFormat2Depth(cameras[camera].videopp.picture.palette));
        
        cameras[camera].image =
            cvCreateImageHeader(size,IPL_DEPTH_8U,
            icvVideoFormat2Depth(
            cameras[camera].videopp.picture.palette)/8);
        
        cvSetImageData(cameras[camera].image,
            (void*)cameras[camera].memorymap,
            cameras[camera].videopp.width*
            icvVideoFormat2Depth(
            cameras[camera].videopp.picture.palette)/8);
        
        cameras[camera].initialised = 1;
        cameras[camera].capturestate = READY;
   }//if(cameras[camera].IsEnabled)
   pthread_mutex_unlock(&icvVideoInitmutex);
   return 1;
}
////////////////////////////////////////////////////////////

int icvVideoStop(int camera)
{
    static pthread_mutex_t icvVideoStopmutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&icvVideoStopmutex);
    
    if(cameras[camera].capturestate != CAPTURING)
    {
        pthread_mutex_unlock(&icvVideoStopmutex);
        return 0;
    }
    
    cameras[camera].capturestate = STOPPING;
    
    while(pthread_mutex_destroy(&(cameras[camera].mutex0)))
        pthread_mutex_unlock(&(cameras[camera].mutex0));
    
    while(pthread_mutex_destroy(&(cameras[camera].mutex1)))
        pthread_mutex_unlock(&(cameras[camera].mutex1));
    
    while (cameras[camera].capturestate != FINISHED );
    while (cameras[camera].renderstate );
    
    munmap(cameras[camera].memorymap,
        cameras[camera].mbuf.size);
    
    cvReleaseImageHeader(&(cameras[camera].image));
    
    cameras[camera].initialised =0;
    pthread_mutex_unlock(&icvVideoStopmutex);
    return 1;
}
//////////////////////////////////////////////////////////////////

int cvcamStop()
{
    int camera;
    for(camera=0; camera<ncameras; camera++)
    {
        icvVideoStop(camera);
    }//for(camera=0; camera<ncameras; camera++)
    
    return 1;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
int icvVideoFormat2Depth(int format)
{
    switch (format)
    {
    case VIDEO_PALETTE_RGB24:
        return 24;
        
    case VIDEO_PALETTE_RGB32:
        return 32;
        
    case VIDEO_PALETTE_RGB565:
        return 16;
        
    case VIDEO_PALETTE_RGB555:
        return 16;
        
    default:
        return 0;
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int icvVideoSetDefaultValues(int camera, int device, int channel, 
     struct video_capability VidCap)
{
    cameras[camera].device                = device;
    cameras[camera].channel               = channel;
    cameras[camera].description.channel   = channel;
    cameras[camera].enabled               = 0;
    cameras[camera].rendered              = 0;
    cameras[camera].initialised           = 0;
    cameras[camera].memorymap             = NULL;
    cameras[camera].renderstate           = 0;
    
    cameras[camera].videopp.picture.palette = VIDEO_PALETTE_RGB24;
    
    cameras[camera].description.maxwidth    = VidCap.maxwidth;
    
    cameras[camera].description.maxheight   = VidCap.maxheight;
    
    cameras[camera].description.minwidth    = VidCap.minwidth;

    if(cameras[camera].description.minwidth<160)
        cameras[camera].description.minwidth = 160;
    
    cameras[camera].description.minheight   = VidCap.minheight;
    
    if(cameras[camera].description.minheight<120)
        cameras[camera].description.minheight = 120;
    
    if(ioctl(device,VIDIOCGPICT,
        &(cameras[camera].videopp.picture) )==-1)
        return 0;   
    
    cameras[camera].videopp.picture.palette   = VIDEO_PALETTE_RGB24;
    
    cameras[camera].videopp.width             = cameras[camera].description.maxwidth;
    
    cameras[camera].videopp.height            = cameras[camera].description.maxheight;
    cameras[camera].videopp.picture.depth      = 24;
    cameras[camera].videopp.picture.brightness = 30000;
    cameras[camera].videopp.picture.hue        = 30000;
    cameras[camera].videopp.picture.colour     = 30000;
    cameras[camera].videopp.picture.contrast   = 30000;
    cameras[camera].videopp.picture.whiteness  = 30000;
    cameras[camera].callback                   = NULL;

    cameras[camera].renderwidth                = 0;
    cameras[camera].renderheight               = 0;
    
    if(ioctl(device,VIDIOCSPICT,
        &(cameras[camera].videopp.picture) )==-1)
        return 0;
    return 1;
}
//Stubs for avi files

/*Plays a specified avi file into a specified window
if file is NULL, file browser is opened. if window is 0,
it is created. width and height mean output size's 0 means
those of avi file are used. __cdecl (*callback)(IplImage*) would be
called on every frame. NULL means no callback*/
CVCAM_API int cvcamPlayAVI(const char* file,
                           void* window,
                           int width,
                           int height,
                           void* callback)
{

return -1;
}


/*Advanced API for dealing with AVI files*/




/*Opens a given file or pops up a dialog if file is NULL
returns a handle to the file opened for success or -1 for failure*/
CVCAM_API cvcamAVIFILE cvcamAVIOpenFile(char* file)
{
    return (cvcamAVIFILE)-1;
}

/*The next functions just do what they say and return 0
for success, anything other for failure*/

CVCAM_API int cvcamAVICloseFile(cvcamAVIFILE file)
{
    return -1;
}

CVCAM_API int cvcamAVISetWindow(cvcamAVIFILE file, void* window)
{
    return -1;
}

CVCAM_API int cvcamAVISetCallback(cvcamAVIFILE file, void* callback)
{
    return -1;
}

CVCAM_API int cvcamAVISetSize(cvcamAVIFILE file, int width, int height)
{
    return -1;
}

CVCAM_API int cvcamAVIRun(cvcamAVIFILE file)
{
    return -1;
}

CVCAM_API int cvcamAVIStop(cvcamAVIFILE file)
{
    return -1;
}

CVCAM_API int cvcamAVIPause(cvcamAVIFILE file)
{
    return -1;
}

CVCAM_API int cvcamAVIResume(cvcamAVIFILE file)
{
    return -1;
}

CVCAM_API int cvcamAVIWaitCompletion(cvcamAVIFILE file)
{
    return -1;
}

CVCAM_API int cvcamAVIIsRunning(cvcamAVIFILE file)
{
    return -1;
}

