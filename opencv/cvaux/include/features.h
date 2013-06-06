#ifndef __FEATURES_H__
#define __FEATURES_H__

#include "cv.h"
#include "cvhid.h"


typedef struct _CvGraphFeatureVtx
{
	CV_GRAPH_VERTEX_FIELDS();
	CvGraphVtx* _prototype;
	CvPoint pt;
	CvSeq* contour;
} CvGraphFeatureVtx;

typedef struct _CvGraphFeatureEdge
{
	CV_GRAPH_EDGE_FIELDS();
	CvSeq* contour;
	CvGraphEdge* _simple_edges[2];
} CvGraphFeatureEdge;

void Segment(IplImage* src, CvGraph** graph, CvGraph** chainGraph, CvMemStorage* storage);
void DrawSegments(CvGraph* graph, IplImage* dst, IplImage* segment, CvMemStorage* storage);
void TrackEdge(CvGraphVtx* start, CvGraphEdge* first, 
			   CvSeq* contour, CvGraphVtx** last_vtx, CvGraphEdge** last_edge);
CvGraph* ConvertEdgeGraph(CvGraph* graph, CvMemStorage* storage);
void ApproxEdgeGraph(CvGraph* graph, CvMemStorage* storage);
void DrawStructuredEdges(CvGraph* graph, IplImage* image);

#define CV_NEXT_GRAPH_VTX(edge, vertex)\
	(edge)->vtx[(vertex) == (edge)->vtx[0]]

inline void JoinGraphVertices(CvGraph* graph, CvGraphVtx* vtx1, CvGraphVtx* vtx2)
{
	CvGraphEdge* edge;
	for(edge = vtx2->first; edge; edge = CV_NEXT_GRAPH_EDGE(edge, vtx2))
	{
		CvGraphVtx* other = CV_NEXT_GRAPH_VTX(edge, vtx1);
		if(other != vtx1)
		{
			CvGraphEdge* _edge = (CvGraphEdge*)cvFindGraphEdgeByPtr(graph, vtx1, other);
			if(!_edge)
			{
				cvGraphAddEdgeByPtr(graph, vtx1, other, edge);
			}
		}
		cvGraphRemoveEdgeByPtr(graph, vtx2, other);
	}
	cvGraphRemoveVtxByPtr(graph, vtx2);
}

//float MatchLineSegments( IplImage* src1, IplImage* src2, 
//                         CvPoint left1, CvPoint right1, //left & right points of cut from scr1
//                         CvPoint left2, CvPoint right2, //left & right points of cut from scr2
//                         int* corr_left,  //indices of src1 cut
//                         int* corr_right, //indices of src2 cut
//                         int* corr_len);  //number of correspondencies

float MatchLineSegments( IplImage* src1, //left image
                         IplImage* src2, //right image
                         CvPoint left1, CvPoint right1, //points on left image
                         CvPoint left2, CvPoint right2, //points on right image
                         int max_disp,                  //maximal allowed disparity
                         int strict_bounds,             //if 1 then bound pixels correspond to bound pixels
                         int* corr_left,  //indices of src1 cut
                         int* corr_right, //indices of src2 cut
                         int* corr_len,   //number of correspondencies
                         float* dp_matrix = NULL, //optional buffer of size (right1.x-left1.x+3)*(right2.x-left2.x+3)
                         int* csi_matrix = NULL); //optional buffer of the same size 

float MatchLineSegments2( IplImage* src1, //left image
                         IplImage* src2, //right image
                         CvPoint left1, CvPoint right1, //points on left image
                         CvPoint left2, CvPoint right2, //points on right image
                         int max_disp,                  //maximal allowed disparity
                         int strict_bounds,             //if 1 then bound pixels correspond to bound pixels
                         int* corr_left,  //indices of src1 cut
                         int* corr_right, //indices of src2 cut
                         int* corr_len);  //number of correspondencies


#endif __FEATURES_H