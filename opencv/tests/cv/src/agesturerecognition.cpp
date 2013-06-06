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

#include "cvtest.h"
#include "ats.h"
#include "stdio.h"

static char cTestName[] = "Gesture Recognition";

static char cTestClass[] = "Algorithm";

static char *cFuncName[] = 
{
    "cvGestureRecognition"
     
};
char data_path[1000];

static int aGestureRecognition(void)
{       
    IplImage *image, *imagew, *image_rez, *mask_rez, *image_hsv, *img_p[2],*img_v,
             *init_mask_ver = 0, *final_mask_ver = 0;
    CvPoint3D32f *pp, p;

    CvPoint pt;
    CvSize2D32f fsize;
    CvPoint3D32f center, cf;
    IplImage *image_mask, *image_maskw;
    
    CvSize size;
    CvHistogram *hist, *hist_mask;

    int width, height;
    int k_points, k_indexs;
    int warpFlag, interpolate;

    int hdim[2] = {20, 20};
    
    double coeffs[3][3], rect[2][2], rez = 0, eps_rez = 2.5, rez_h;
    float *thresh[2];
    float hv[3];
    
    float reps, aeps, ww;
    float line[6], in[3][3], h[3][3];
    float cx, cy, fx, fy;

    static char num[4]; 
    
    char *name_image;  
    char *name_range_image;
    char *name_verify_data;
    char *name_init_mask_very;
    char *name_final_mask_very;

    CvSeq *numbers;
    CvSeq *points;
    CvSeq *indexs;
        
    CvMemStorage *storage;
    CvRect hand_roi, hand_roi_trans;
    
    int i,j, lsize, block_size = 1000, flag;
    int code;

    FILE *filin, *fil_ver;

/* read tests params */

    code = TRS_OK;

/*  define input information    */
    strcpy (num, "001"); 

    lsize = strlen(data_path)+12;
    name_verify_data = (char*)trsmAlloc(lsize);
    name_range_image = (char*)trsmAlloc(lsize);
    name_image = (char*)trsmAlloc(lsize);

    name_init_mask_very = (char*)trsmAlloc(lsize);
    name_final_mask_very = (char*)trsmAlloc(lsize);

/*  define input range_image file path        */
    strcpy(name_range_image, data_path);
    strcat(name_range_image, "rpts");
    strcat(name_range_image, num);
    strcat(name_range_image, ".txt");

/*  define input image file path        */
    strcpy(name_image, data_path);
    strcat(name_image, "real");
    strcat(name_image, num);
    strcat(name_image, ".bmp");

/*  define verify data file path        */
    strcpy(name_verify_data, data_path);
    strcat(name_verify_data, "very");
    strcat(name_verify_data, num);
    strcat(name_verify_data, ".txt");

/*  define verify init mask file path    */
    strcpy(name_init_mask_very, data_path);
    strcat(name_init_mask_very, "imas");
    strcat(name_init_mask_very, num);
    strcat(name_init_mask_very, ".bmp");

/*  define verify final mask file path    */
    strcpy(name_final_mask_very, data_path);
    strcat(name_final_mask_very, "fmas");
    strcat(name_final_mask_very, num);
    strcat(name_final_mask_very, ".bmp");

    filin = fopen(name_range_image,"r");
    fil_ver = fopen(name_verify_data,"r");

    fscanf( filin, "\n%d %d\n", &width, &height);
    printf("width=%d height=%d  reading testing data...", width,height);

    OPENCV_CALL( storage = cvCreateMemStorage ( block_size ) );
    OPENCV_CALL( points = cvCreateSeq( CV_SEQ_POINT3D_SET, sizeof(CvSeq),
                            sizeof(CvPoint3D32f), storage ) );
    OPENCV_CALL (indexs = cvCreateSeq( CV_SEQ_POINT_SET, sizeof(CvSeq),
                            sizeof(CvPoint), storage ) );

    pp = 0;
    
/*  read input image from file   */   
    image = atsCreateImageFromFile( name_image );
    if(image == NULL)   {code = TRS_FAIL; goto m_exit;}

/*  read input 3D points from input file        */
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)    
        {
            fscanf( filin, "%f %f %f\n", &p.x, &p.y, &p.z);
            if(/*p.x != 0 || p.y != 0 ||*/ p.z != 0)
            {
                OPENCV_CALL(cvSeqPush(points, &p));
                pt.x = j; pt.y = i;
                OPENCV_CALL(cvSeqPush(indexs, &pt));
                               
            }
        }
    }

    k_points = points->total;
    k_indexs = indexs->total;

/*   convert sequence to array          */
    pp = (CvPoint3D32f*)trsmAlloc(k_points * sizeof(CvPoint3D32f));
    OPENCV_CALL(cvCvtSeqToArray(points, pp ));

/*  find 3D-line      */

    reps = (float)0.1;
    aeps = (float)0.1;
    ww = (float)0.08;

    OPENCV_CALL( cvFitLine3D(pp, k_points, CV_DIST_WELSCH, &ww, reps, aeps, line ));

/*  find hand location      */
    flag = -1;
    fsize.width = fsize.height = (float)0.22;  //   (hand size in m)

    numbers = NULL;
    OPENCV_CALL( cvFindHandRegion (pp, k_points, indexs,line, fsize,
                      flag,&center,storage, &numbers));

/*   read verify data    */
    fscanf( fil_ver, "%f %f %f\n", &cf.x, &cf.y, &cf.z);
    rez+= cvSqrt((center.x - cf.x)*(center.x - cf.x)+(center.y - cf.y)*(center.y - cf.y)+
         (center.z - cf.z)*(center.z - cf.z))/3.;
    
/*    create hand mask            */
    size.height = height;
    size.width = width;
    OPENCV_CALL( image_mask = cvCreateImage(size, IPL_DEPTH_8U, 1) ); 

    OPENCV_CALL( cvCreateHandMask(numbers, image_mask, &hand_roi) );

/*  read verify initial image mask                  */
    init_mask_ver = atsCreateImageFromFile( name_init_mask_very );
    if(init_mask_ver == NULL)   {code = TRS_FAIL; goto m_exit;}
    
    rez+= iplNorm(init_mask_ver, image_mask, IPL_L2) / (width*height+0.);

/*  calculate homographic transformation matrix            */
    cx = (float)(width / 2.);
    cy = (float)(height / 2.);
    fx = fy = (float)571.2048;

/* define intrinsic camera parameters                      */
    in[0][1] = in[1][0] = in[2][0] = in[2][1] = 0;
    in[0][0] = fx; in[0][2] = cx;
    in[1][1] = fy; in[1][2] = cy;
    in[2][2] = 1;

    OPENCV_CALL( cvCalcImageHomography(line, &center, in, h) );
    
    rez_h = 0;
    for(i=0;i<3;i++)
    {
        fscanf( fil_ver, "%f %f %f\n", &hv[0], &hv[1], &hv[2]);
        for(j=0;j<3;j++)
        {
            rez_h+=(hv[j] - h[i][j])*(hv[j] - h[i][j]);
        }
    }
    rez+=sqrt(rez_h)/9.;

/*   image unwarping         */
    size.width = image->width; 
    size.height = image->height; 
    OPENCV_CALL( imagew = cvCreateImage(size, IPL_DEPTH_8U,3) );
    OPENCV_CALL( image_maskw = cvCreateImage(size, IPL_DEPTH_8U,1) );

    iplSet(image_maskw, 0);

    cvSetImageROI(image, hand_roi);
    cvSetImageROI(image_mask, hand_roi);

/* convert homographic transformation matrix from float to double      */
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            coeffs[i][j] = (double)h[i][j];

/*  get bounding rectangle for image ROI         */
    iplGetPerspectiveBound(image, coeffs, rect);

    width = (int)(rect[1][0] - rect[0][0]);
    height = (int)(rect[1][1] - rect[0][1]);
    hand_roi_trans.x = (int)rect[0][0];hand_roi_trans.y = (int)rect[0][1];
    hand_roi_trans.width = width; hand_roi_trans.height = height;

    cvMaxRect(&hand_roi, &hand_roi_trans, &hand_roi);
    iplSetROI((IplROI*)image->roi, 0, hand_roi.x, hand_roi.y,
               hand_roi.width,hand_roi.height);
    iplSetROI((IplROI*)image_mask->roi, 0, hand_roi.x, hand_roi.y,
                hand_roi.width,hand_roi.height);

    warpFlag = IPL_WARP_R_TO_Q;
/*    interpolate = IPL_INTER_CUBIC;   */
/*    interpolate = IPL_INTER_NN;      */
    interpolate = IPL_INTER_LINEAR;
    iplWarpPerspective(image, imagew, coeffs, warpFlag, interpolate);
    iplWarpPerspective(image_mask, image_maskw, coeffs, warpFlag, IPL_INTER_NN);  
    
/*  set new image and mask ROI after transformation        */
    iplSetROI((IplROI*)imagew->roi,0, (int)rect[0][0], (int)rect[0][1],(int)width,(int)height);
    iplSetROI((IplROI*)image_maskw->roi,0, (int)rect[0][0], (int)rect[0][1],(int)width,(int)height);

/*  copy image ROI to new image and resize        */
    size.width = width; size.height = height;
    image_rez = cvCreateImage(size, IPL_DEPTH_8U,3);
    mask_rez = cvCreateImage(size, IPL_DEPTH_8U,1);
 
    iplCopy(imagew,image_rez);
    iplCopy(image_maskw,mask_rez);
    
/* convert rezult image from RGB to HSV               */
    image_hsv = iplCreateImageHeader(3, 0, IPL_DEPTH_8U, "HSV", "HSV",
                                   IPL_DATA_ORDER_PIXEL, IPL_ORIGIN_TL,IPL_ALIGN_DWORD,
                                   image_rez->width, image_rez->height, NULL, NULL, NULL, NULL);
    iplAllocateImage(image_hsv, 0, 0 ); 
    strcpy(image_rez->colorModel, "RGB");
    strcpy(image_rez->channelSeq, "RGB");
    image_rez->roi = NULL;

    iplRGB2HSV(image_rez, image_hsv);

/* convert to three images planes                      */
    img_p[0] = cvCreateImage(size, IPL_DEPTH_8U,1);
    img_p[1] = cvCreateImage(size, IPL_DEPTH_8U,1);
    img_v = cvCreateImage(size, IPL_DEPTH_8U,1);

    cvCvtPixToPlane(image_hsv, img_p[0], img_p[1], img_v, NULL);
   
/*  calculate histograms                */
    hist = cvCreateHist ( 2, hdim, CV_HIST_ARRAY);
    hist_mask = cvCreateHist ( 2, hdim, CV_HIST_ARRAY);

/*  install histogram threshold         */
    thresh[0] = (float*) trsmAlloc(2*sizeof(float));
    thresh[1] = (float*) trsmAlloc(2*sizeof(float));

    thresh[0][0] = thresh[1][0] = -0.5;
    thresh[0][1] = thresh[1][1] = 255.5;
    cvSetHistThresh( hist, thresh, 1);
    cvSetHistThresh( hist_mask, thresh, 1);

    cvCalcHist(img_p, hist, 0);
        
    cvCalcHistMask(img_p, mask_rez, hist_mask, 0);
            
    cvCalcProbDensity(hist, hist_mask, hist_mask);

    cvCalcBackProject( img_p, mask_rez, hist_mask ); 

/*  read verify final image mask                  */
    final_mask_ver = atsCreateImageFromFile( name_final_mask_very );
    if(final_mask_ver == NULL)   {code = TRS_FAIL; goto m_exit;}

    rez+= iplNorm(final_mask_ver, mask_rez, IPL_L2) / (width*height+0.);

    trsWrite( ATS_CON | ATS_SUM, "\n gesture recognition \n");
    trsWrite( ATS_CON | ATS_SUM, "result testing error = %f \n",rez);

    if(rez > eps_rez) code = TRS_FAIL;
    else code = TRS_OK;
    
m_exit:    

    cvReleaseImage(&image_mask);
    cvReleaseImage(&mask_rez);
    cvReleaseImage(&image_rez);
    atsReleaseImage(final_mask_ver);
    atsReleaseImage(init_mask_ver);

    cvReleaseImage(&imagew);
    cvReleaseImage(&image_maskw); 

    cvReleaseImage(&img_p[0]);
    cvReleaseImage(&img_p[1]);
    cvReleaseImage(&img_v);
 
    cvReleaseHist( &hist);
    cvReleaseHist( &hist_mask);
    
    cvReleaseMemStorage ( &storage );

    trsFree(pp);
    trsFree(name_final_mask_very);
    trsFree(name_init_mask_very);
    trsFree(name_image);
    trsFree(name_range_image);
    trsFree(name_verify_data);

    fclose(filin);
    fclose(fil_ver);

    
/*    _getch();       */
    return code;
}




void InitAGestureRecognition()
{
/* Test Registaration */
    atsGetTestDataPath( data_path, "GestureRecognition", 0, 0 );
        
    trsReg(cFuncName[0],cTestName,cTestClass,aGestureRecognition); 

} /*InitAGestureRecognition*/

/* End of file. */