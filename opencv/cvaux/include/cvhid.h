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

#ifndef __CVHID_H__
#define __CVHID_H__

#include "cvaux.h"
///////////////////////////////////////////////////////////
// Gradient runs block

#define GRRUN_TYPE_HORIZ_D   1
#define GRRUN_TYPE_HORIZ_U   2
#define GRRUN_TYPE_VERT_D    4
#define GRRUN_TYPE_VERT_U    8
#define GRRUN_TYPE_INCREASE  16
#define GRRUN_TYPE_DECREASE  32


#define FORM_RUN(r,xx1,zz1,xx2,zz2,t,res)\
    r.x1=xx1;r.x2=xx2;r.z1=zz1;r.z2=zz2;r.attr.type=t;r.reserved=res;

#define SO_DIRECT(r1,r2)((((r1.z2-r1.z1)*(r2.z2-r2.z1)>0)?true:false))
#define IN_EPS(r1,r2,t)((((labs(r1.z1-r2.z1)<=t)?true:false)&& \
    ((labs(r1.z2-r2.z2)<=t)?true:false))|| \
    (((labs(r1.z1-r2.z2)<=t)?true:false)&& \
    ((labs(r1.z2-r2.z1)<=t)?true:false)))

#define GET_GRRUN_TYPE(r)( (r.z2-r.z1>0) ? GRRUN_INCREASE : GRRUN_DECREASE )

#define VAL_CONNECTED(r1,r2)( (MAX(r1.x2, r2.x2) - MIN(r1.x1, r2.x1) - labs(r1.x2 - r2.x2) - labs(r1.x1 - r2.x1) ) )
#define IS_CONNECTED(r1,r2)( ( (r1.x1 <= r2.x2) && (r1.x2 >= r2.x1) ) )
#define GET_RUN_TAN(r)(fabs((float)(r.z2 - r.z1)/(r.x2 - r.x1)))
#define IS_INCREASE(r)((((r.z2-r.z1)>0)?true:false))
//#define RUN_MEAN(r)((int)(cvRound((double)(r.x1 + r.x2)*0.5)))
#define RUN_MEAN(r)(r.attr.mid)
#define RUN_MEAN_FLOAT(r)((float)((r.x1 + r.x2)*0.5))

#define AREA_UNDER_RUN(run)( ((run.z2+run.z1)*(run.x2-run.x1))>>1 )
#define RIGHT_HALFAREA_UNDER_RUN(run)( ((3*run.z2+run.z1)*(run.x2-run.x1))>>3 )
#define LEFT_HALFAREA_UNDER_RUN(run)( ((3*run.z1+run.z2)*(run.x2-run.x1))>>3 )

#define RUN_LEN_2(r)((r.x2-r.x1)*(r.x2-r.x1)+(r.z2-r.z1)*(r.z2-r.z1))
#define RUNS_SMUL(r1,r2)((r1.x2-r1.x1)*(r2.x2-r2.x1)+(r1.z2-r1.z1)*(r2.z2-r2.z1))
#define RUNS_COS_2(r1,r2)((RUNS_SMUL(r1,r2)*RUNS_SMUL(r1,r2))/(double)(RUN_LEN_2(r1)*RUN_LEN_2(r2)))
#define RUN_INTERVAL(r)((r.x2 - r.x1 + 1))
#define VAL_MEAN(v)(((int)((v)*0.5+0.5)))
//#define GET_ST_RUNS_EDGE_LEN(r1, r2)( (labs( RUN_MEAN(r1) - RUN_MEAN(r2) ) ) )
#define GET_RT_RUNS_EDGE_LEN_2(hr, y, vr, x)( (RUN_MEAN(hr)-x)*(RUN_MEAN(hr)-x)+(RUN_MEAN(vr)-y)*(RUN_MEAN(vr)-y) )
#define GET_GR_RUN_COLOR_DIFF(r1, r2)( MIN(labs(r1.z1-r2.z1),labs(r1.z2-r2.z2)) )
#define GET_GR_RUN_GRAD_DIFF(r1, r2)( (labs(GET_RUN_TAN(r1)-GET_RUN_TAN(r2))))
#define GET_GR_RUN_MIN_Z(r1, r2)( MIN(labs(r1.z1-r1.z2), labs(r2.z1-r1.z2)))
//#define GET_2RUNS_DIST(r1,r2)(MIN(labs(r1.attr.lCol-r2.attr.lCol),labs(r1.attr.rCol-r2.attr.rCol)))
#define GET_2RUNS_DIST(r1,r2)(labs(RUN_MEAN(r1)-RUN_MEAN(r2)))


typedef struct _CvGrRunAttr
{    
    uchar     type;    
    //uchar     lCol, rCol;    
    //float     tg;    
    int       mid;
}CvGrRunAttr;
typedef struct _CvGrRun
{    
    int         x1,x2;
    int         z1,z2;      
    int         reserved;
    CvGrRunAttr attr;
}CvGrRun;
typedef struct _CvGrRunSt
{
    int             count;
    CvGrRun*        runs;    
}CvGrRunSt;

OPENCVAUXAPI  CvGrRunSt* cvAllocateGrRuns( int stringcount, int runcount );

OPENCVAUXAPI  void cvReleaseGrRuns( CvGrRunSt* strings, int stringcount );

OPENCVAUXAPI  void cvCreateSimpleGradientRuns( IplImage*  src,                          
                                 CvGrRunSt* hRuns, 
                                 CvGrRunSt* vRuns );

OPENCVAUXAPI  void  cvGrRunsApprox( CvGrRunSt* grRuns, 
                       int        stcount,
                       double     thresh,
                       double     cos_thresh );

OPENCVAUXAPI  void  cvGrRunsFiltering( CvGrRunSt* grRuns, 
                         int        stcount,
                         double     thresh );

OPENCVAUXAPI  void  cvRemoveSmallRuns( CvGrRunSt* grRuns, 
                         int        stcount,
                         double     thresh );

OPENCVAUXAPI  void  cvRemoveSmallRunsEx( CvGrRunSt* grRuns, 
                           int        stcount,
                           int        grThresh,
                           double     lenThresh );

OPENCVAUXAPI  void cvCreateGradientRunsDP( IplImage*          src,  
                             float              thresh,                             
                             CvGrRunSt*         hRuns, 
                             CvGrRunSt*         vRuns );

OPENCVAUXAPI  void cvCreateGradientRuns( IplImage*  src,  
                           double     intThresh,
                           double     cosThresh,
                           CvGrRunSt* hRuns, 
                           CvGrRunSt* vRuns,
						   int method //0-via integrals, 1-cones method, 2-by 1st derivative, 3 -DP
                          );

OPENCVAUXAPI  void  cvFilterGrRunsForEdgeDetector( CvGrRunSt* grRuns, 
                                     int        stcount,
                                     double     thresh );

// end gradient runs block
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// Mixed Run Graph & segmentation via one block

#define  SECOND_EDGE_VTX( e, v )( e->vtx[e->vtx[0]==v] )

#define PT_3_SMUL(p1,p2,p3)((p2.x-p1.x)*(p3.x-p2.x)+(p2.y-p1.y)*(p3.y-p2.y))
#define PT_3_VMUL(p1,p2,p3)((p2.x-p1.x)*(p3.y-p2.y)-(p3.x-p2.x)*(p2.y-p1.y))

#define FORM_GRMG_NODE(v, i, xx, yy, run) \
(v)->runIndx=i; \
(v)->pt.x=xx; \
(v)->pt.y=yy;  \
(v)->lCol = run.z1; \
(v)->rCol = run.z2; \

#define getSizeForGraph(xxxType) \
    ( sizeof(xxxType) < 8 ? 8 : sizeof(xxxType) + 4 - sizeof(xxxType) % 4 )

#define MRG_EDGE_COMPLEX             0
#define MRG_EDGE_HORIZ               1
#define MRG_EDGE_VERTICAL            2
#define MRG_EDGE_HORIZ_ADD           3
#define MRG_EDGE_VERTICAL_ADD        4
#define MRG_EDGE_ADD_TO_FRAME        5

typedef struct _CvMRGNode
{
    CvGraphVtx  vtx;
    CvPoint     pt;    
    int         runIndx;
    int         chainID;    
    int         lCol;
    int         rCol;
    _CvMRGNode* nextInChain;
}CvMRGNode;
typedef struct _CvMRGEdge
{
    CvGraphEdge edge;
    int         edgeType;
    int         seg1;
    int         seg2;
    int         reserved;
}CvMRGEdge;
typedef struct _CvMRGChainNode
{
    CvGraphVtx  vtx;
    CvMRGNode*  beg;    
    CvMRGNode*  end;    
    int         length;    
}CvMRGChainNode;
typedef struct _CvMRGChainEdge
{
    CvGraphEdge   edge;
    CvGraphVtx*   vtx1;
    CvGraphVtx*   vtx2;
    int           linkLen;
}CvMRGChainEdge;

typedef struct _CvMRGSeg
{
    CvGraphVtx  vtx;
    CvMRGEdge*  fisrt;
    CvSeq*      seq;
    int         color;
}CvMRGSeg;

#define  IS_EQUAL_POINTS( p1, p2 )( p1.x == p2.x && p1.y == p2.y )
#define  IS_EQUAL_NODES( n1, n2 )( n1->pt.x == n2->pt.x && n1->pt.y == n2->pt.y )
#define  DIST_2_PT(pt1, pt2)( (pt1.x-pt2.x)*(pt1.x-pt2.x)+(pt1.y-pt2.y)*(pt1.y-pt2.y) )

CV_INLINE double _cvCosOf2Vectors( CvPoint p1, CvPoint p2, CvPoint ip1, CvPoint  ip2 )
{
    int dx1 = p2.x-p1.x;
    int dx2 = ip2.x-ip1.x;
    int dy1 = p2.y-p1.y;
    int dy2 = ip2.y-ip1.y;
    long p = ( dx1 * dx2 + dy1 * dy2 );

    return 
        (double)( p * p ) / ( ( dx1 * dx1 + dy1 * dy1 ) * ( dx2 * dx2 + dy2 * dy2 ) );
}
#define  COS_2_VECTORS( p1, p2, ip1, ip2 )(((p2.x-p1.x)*(ip2.x-ip1.x)+(p2.y-p1.y)*(ip2.y-ip1.y)))

OPENCVAUXAPI  CvSeq*  cvGetSegmentsFromMRGGraph( CvGraph*         graph,
                                   CvMemStorage*    storage,
                                   CvGraph**        ppSegGraph );

OPENCVAUXAPI  void  cvMixedRunGraph( CvGrRunSt* hRuns,
                       CvGrRunSt* vRuns,                       
                       int        imgH,
                       int        imgW,
                       double     thresh,                       
                       CvGraph**  ppGraph,
                       CvGraph**  ppChainGraph,                       
                       CvMemStorage* storage,
                       IplImage*  tmp );

// end gradient runs block
///////////////////////////////////////////////////////////

/* 
DESCRIPTION OF THE ASSOCIATION GRAPH CONSTRUCTION PARAMETERS.

Note: AG = association graph, feature = an edge extracted from an image

DP_ERROR:
Douglas-Peucker parameter used for contours approximation

COLOR_ERROR:  
Look at the color cr to the right and cl to the left of the feature. Average both along the edge. 
Compare these values for a pair of features from two images. Find the minimum: M = min(|cl1 - cl2|, |cr1 - cr2|). 
If M > COLOR_ERROR, then do not insert this pair in the AG. 

EPIPOLAR_ERROR:
If the features are separated by EPIPOLAR_ERROR scanlines then do not insert the pair in the AG

LENGTH_THRESH:
If the length of the feature is less than LENGTH_THRESH, the feature is not inserted in the AG

ORIENT_ERROR:
If the angle between two features is less than ORIENT_ERROR, do not insert the pair in the AG

ORIENT_SQUARE_THRESH: 
If the area of the parallelogram built on two features is greater than ORIENT_SQUARE_THRESH, 
these edges cannot be considered collinear.

EDGE_DIST_THRESH:
If the distance between two features from the same image is greater than EDGE_DIST_THRESH, the vertices og AG 
that contain these features cannot be considered contradicting to each other.

DISPARITY_MAX: 
If the disparity between two features is greater than DISPARITY_MAX, do no insert the pair in the AG

CONTRAST_ERROR:
Not used.

MAX_ASSOC:
Not used.
*/

struct CvStereoParams
{
	int DPError;
	int ColorError;
	int EpipolarError;
	int LengthThresh;
	float OrientError;
	float OrientSquareThresh;
	int EdgeDistThresh;
	float ContrastError;
	int DisparityMax;
	int MaxAssoc;
};

struct CvStereoFeatureList;

OPENCVAUXAPI CvStereoFeatureList* cvAllocateStereoFeatureList();
OPENCVAUXAPI void cvFreeStereoFeatureList(CvStereoFeatureList*);
OPENCVAUXAPI void cvClearStereoFeatureList(CvStereoFeatureList*);

OPENCVAUXAPI void InitStereoParams(CvStereoParams* params);
OPENCVAUXAPI int ProcessStereoPair(const char* fname, CvMemStorage* storage);
OPENCVAUXAPI void CalculateSparseCorrespondence(IplImage* src1, IplImage* src2, 
            CvMemStorage* storage, CvGraph** disparity, 
            CvStereoFeatureList* fl1, CvStereoFeatureList* fl2,
            const CvStereoParams* params);
OPENCVAUXAPI IplImage* VisualizeCorrespondence(IplImage* source, CvGraph* assoc, const CvStereoParams* params);

// assoc,vertices,num_vert may be equal to 0
OPENCVAUXAPI void StereoBySimpleDP( IplImage* left,
							   IplImage* right,
							   CvGraph* assoc, //assoc. graph with features
							   int* vertices,  //array of subset of vertices to process 
							   int num_vert,   //size of above array
							   CvStereoParams* stereo_params,
							   IplImage* disparity_image //output dense stereo image 8u1c
							 );


#endif/*__CVHID_H_*/

/* End of file. */
