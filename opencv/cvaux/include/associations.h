#ifndef __ASSOCIATIONS_H__
#define __ASSOCIATIONS_H__

#include "cvhid.h"
#include <functional>
#include <list>
#include "cv.h"
#include "features.h"

using namespace std;

typedef struct _CvLine
{
	CvPoint p[2];
} CvLine;

struct CvGraphAssocVtx;
struct CvStereoFeature
{
	CvLine line;
	int edge_id;
	int line_id;
	int vtx_id;
	int seq_id;
	CvSeq* seq;
	list<CvGraphAssocVtx*> assoc_list;

	float color_left[3];
	float color_right[3];
	float contrast[3];

    CvStereoFeature::CvStereoFeature() {};
    CvStereoFeature::CvStereoFeature(const CvStereoFeature& f)
    {
        line = f.line;
        edge_id = f.edge_id;
        line_id = f.line_id;
        vtx_id = f.vtx_id;
        seq_id = f.seq_id;
        seq = f.seq;

//        if(f.assoc_list.size())
//        {
            assoc_list = f.assoc_list;
//        }

        memcpy(color_left, f.color_left, sizeof(float)*3);
        memcpy(color_right, f.color_right, sizeof(float)*3);
        memcpy(contrast, f.contrast, sizeof(float)*3);
    };
};

template<> struct std::greater<CvStereoFeature> : binary_function<CvStereoFeature, CvStereoFeature, bool>
{
	int offset1, offset2;
	bool operator ()(const CvStereoFeature& f1, const CvStereoFeature& f2) const
	{
		return *((int*)f1.line.p + offset1) > *((int*)f2.line.p + offset2);
	};
};
/*
template<> struct std::greater<CvGraphAssocVtx*> : public binary_function<CvGraphAssocVtx*, CvGraphAssocVtx*, bool>
{
	bool operator()(const CvGraphAssocVtx*& vtx1, const CvGraphAssocVtx*& vtx2)
	{
		return vtx1->weight > vtx2->weight;
	};
};*/

struct CvStereoFeatureList : public list<CvStereoFeature> {};

struct StereoFeaturePred
{
	CvStereoFeature* etalon;
	greater<CvStereoFeature> great;
	StereoFeaturePred(CvStereoFeature* e, const greater<CvStereoFeature>& gr) 
	{
		etalon = e;
		great = gr;
	};
	bool operator ()(const CvStereoFeature& f)
	{
		return great(f, *etalon);
	}
};

struct CvGraphAssocVtx
{
    CV_GRAPH_VERTEX_FIELDS();
    float weight;

    CvStereoFeature* f1;
    CvStereoFeature* f2;
    void* reserved;
};

typedef struct _CvGraphAssocEdge
{
    CV_GRAPH_EDGE_FIELDS();
    float weight;
    int rule;
    float params[2];
} CvGraphAssocEdge;

typedef struct _CvAssocGraph
{
	CV_GRAPH_FIELDS();
	IplImage* source1;
	IplImage* source2;
} CvAssocGraph;

static char* rule_names[] = {
	"from_the_same_edge",
		"collinear",
		"orientation"
};

struct ImDeriv
{
	ImDeriv()
	{
		x = 0;
		y = 0;
		src = 0;
	};
	ImDeriv(IplImage* _src, IplImage* _x, IplImage* _y)
	{
		x = cvCloneImage(_x);
		y = cvCloneImage(_y);
		src = cvCloneImage(_src);
	};
	ImDeriv(const ImDeriv& imd)
	{
		x = cvCloneImage(imd.x);
		y = cvCloneImage(imd.y);
		src = cvCloneImage(imd.src);
	};
	void operator =(const ImDeriv& imd)
	{
		cvReleaseImage(&x);
		cvReleaseImage(&y);
		cvReleaseImage(&src);
		x = cvCloneImage(imd.x);
		y = cvCloneImage(imd.y);
		src = cvCloneImage(imd.src);
	};
	~ImDeriv()
	{
		cvReleaseImage(&x);
		cvReleaseImage(&y);
		cvReleaseImage(&src);
	};
	IplImage* src;
	IplImage* x;
	IplImage* y;
};

struct PreCalc
{
	ImDeriv d1, d2;
};


template<> struct std::greater<void*> : binary_function<void*, void*, bool>
{
	bool operator ()(const void*& e1, const void*& e2) const
	{
		CvGraphAssocEdge* _e1 = (CvGraphAssocEdge*)e1;
		CvGraphAssocEdge* _e2 = (CvGraphAssocEdge*)e2;
		return _e1->params[1] < _e2->params[1];
	};
};


#define PI 3.1415926f

float CalcEpipolarDistance(const CvLine& la, const CvLine& lb);

CvAssocGraph* BuildAssociationGraph(CvGraph* graph1, CvGraph* graph2, CvGraph* chainGraph1, CvGraph* chainGraph2, 
                CvMemStorage* storage, IplImage* source1, IplImage* source2, 
				CvStereoFeatureList* feature_list1, CvStereoFeatureList* feature_list2,
				const CvStereoParams* params);
void DrawAssocGraph(CvGraph* assoc, IplImage* im1, IplImage* im2);
int  GetRightCorrespondences( CvGraph* assoc, IplImage* ground_truth, int* vertices_array, int num_vert );
int NumRightVerticesInClique( CvGraph* assoc, IplImage* ground_truth, int* vertices_array, int num_vert );

int InducedSubgraphNumEdges( CvGraph* graph, int* vertices_array, int num_vert );


int CountSetSize(CvSet* set);
void FilterFeatureGraph(CvGraph* graph, CvMemStorage* storage, IplImage* im, 
                        const CvStereoParams* params);

void ComplementGraph( CvGraph* graph );
void AddEdgeWeightsToAssocGraph(IplImage* image1, IplImage* image2, CvGraph* graph);

#endif //__ASSOCIATIONS_H__