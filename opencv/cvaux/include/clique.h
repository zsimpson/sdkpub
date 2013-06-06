//#include <functional>
//#include <list>
#include "cv.h"
#include "cvaux.h"

//#include "features.h"

//using namespace std;
typedef struct CvIntVtx
{
    CV_GRAPH_VERTEX_FIELDS();
    float weight;
    int value;
} CvIntVtx;

CvSeq* GraphToComponents( CvGraph* graph, CvMemStorage* storage );
//int MaxWeightedClique( CvGraph* graph, int* clique, float* weight ); 

//Actually function finds maximal independent set (IS)
//function returns the number of elements in "clique" array
int MaxWeightedClique( CvGraph* graph, //input assoc graph with edges==contradictions
                       int* clique,    //on input stores indices of vertices of initial IS
                                       //on output stores full IS (including initial)
                       int init_size,  //size of initial IS
                       float* weight   //
                     );

#define CLIQUE_MAX_ITER 0x7fffffff
#define CLIQUE_CLOCK_LIMIT 100 //1 second on my computer