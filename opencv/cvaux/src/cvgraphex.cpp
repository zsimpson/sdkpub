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

#include "_cvaux.h"

#include <float.h>
#include <limits.h>

#include "_cvutils.h"
#include "_cvwrap.h"


typedef struct CvGraphItem
{
    CvGraphVtx* vtx;
    CvGraphEdge* edge;
}
CvGraphItem;


static  void  icvSeqElemsClearMask( CvSeq* seq, int offset, int clear_mask )
{
    CV_FUNCNAME("icvStartScanGraph");

    __BEGIN__;
    
    CvSeqReader reader;
    int i, total, elem_size;

    if( !seq )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    elem_size = seq->elem_size;
    total = seq->total;

    if( (unsigned)offset > (unsigned)elem_size )
        CV_ERROR_FROM_STATUS( CV_BADARG_ERR );

    CV_CALL( cvStartReadSeq( seq, &reader ));

    for( i = 0; i < total; i++ )
    {
        int* flag_ptr = (int*)(reader.ptr + offset);
        *flag_ptr &= ~clear_mask;

        CV_NEXT_SEQ_ELEM( elem_size, reader );
    }

    __END__;
}


static  char*  icvSeqFindNextElem( CvSeq* seq, int offset, int mask,
                                   int value, int* start_index )
{
    char* elem_ptr = 0;
    
    CV_FUNCNAME("icvStartScanGraph");

    __BEGIN__;
    
    CvSeqReader reader;
    int total, elem_size, index;

    if( !seq || !start_index )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    elem_size = seq->elem_size;
    total = seq->total;
    index = *start_index;

    if( (unsigned)offset > (unsigned)elem_size )
        CV_ERROR_FROM_STATUS( CV_BADARG_ERR );

    if( total == 0 )
        EXIT;

    if( (unsigned)index >= (unsigned)total )
    {
        index %= total;
        index += index < 0 ? total : 0;
    }

    CV_CALL( cvStartReadSeq( seq, &reader ));

    if( index != 0 )
    {
        CV_CALL( cvSetSeqReaderPos( &reader, index ));
    }

    for( index = 0; index < total; index++ )
    {
        int* flag_ptr = (int*)(reader.ptr + offset);
        if( (*flag_ptr & mask) == value )
            break;

        CV_NEXT_SEQ_ELEM( elem_size, reader );
    }

    if( index < total )
    {
        elem_ptr = reader.ptr;
        *start_index = index;
    }

    __END__;

    return  elem_ptr;
}

#define CV_FIELD_OFFSET( field, structtype ) ((int)(long)&((structtype*)0)->field)

CV_IMPL void
icvStartScanGraph( CvGraph* graph, CvGraphScanner* scanner,
                   CvGraphVtx* vtx, int mask )
{
    CvMemStorage* child_storage = 0;

    CV_FUNCNAME("icvStartScanGraph");

    __BEGIN__;

    if( !graph || !scanner )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    if( !(graph->storage ))
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    memset( scanner, 0, sizeof(*scanner));

    scanner->graph = graph;
    scanner->mask = mask;
    scanner->vtx = vtx;
    scanner->index = vtx == 0 ? 0 : -1;

    CV_CALL( child_storage = cvCreateChildMemStorage( graph->storage ));

    CV_CALL( scanner->stack = cvCreateSeq( 0, sizeof(CvSet),
                       sizeof(CvGraphItem), child_storage ));

    CV_CALL( icvSeqElemsClearMask( (CvSeq*)graph,
                                   CV_FIELD_OFFSET( flags, CvGraphVtx ),
                                   CV_GRAPH_ITEM_VISITED_FLAG|
                                   CV_GRAPH_SEARCH_TREE_NODE_FLAG ));

    CV_CALL( icvSeqElemsClearMask( (CvSeq*)(graph->edges),
                                   CV_FIELD_OFFSET( flags, CvGraphEdge ),
                                   CV_GRAPH_ITEM_VISITED_FLAG ));

    __END__;

    if( cvGetErrStatus() < 0 )
        cvReleaseMemStorage( &child_storage );
}


CV_IMPL void
icvEndScanGraph( CvGraphScanner* scanner )
{
    CV_FUNCNAME("icvEndScanGraph");

    __BEGIN__;

    if( !scanner )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    if( scanner->stack )
        CV_CALL( cvReleaseMemStorage( &(scanner->stack->storage)));

    __END__;
}


CV_IMPL int
icvNextGraphItem( CvGraphScanner* scanner )
{
    int code = -1;
    
    CV_FUNCNAME("icvNextGraphItem");

    __BEGIN__;

    CvGraphVtx* vtx;
    CvGraphVtx* dst;
    CvGraphEdge* edge;
    CvGraphItem item;

    if( !scanner || !(scanner->stack))
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    dst = scanner->dst;
    vtx = scanner->vtx;
    edge = scanner->edge;

    for(;;)
    {
        for(;;)
        {
            if( dst && !CV_IS_GRAPH_VERTEX_VISITED(dst) )
            {
                scanner->vtx = vtx = dst;
                edge = vtx->first;
                dst->flags |= CV_GRAPH_ITEM_VISITED_FLAG;

                if((scanner->mask & CV_GRAPH_VERTEX))
                {
                    scanner->vtx = vtx;
                    scanner->edge = vtx->first;
                    scanner->dst = 0;
                    code = CV_GRAPH_VERTEX;
                    EXIT;
                }
            }

            while( edge )
            {
                dst = edge->vtx[vtx == edge->vtx[0]];
                
                if( !CV_IS_GRAPH_EDGE_VISITED(edge) )
                {
                    // check that the edge is outcoming
                    if( !CV_IS_GRAPH_ORIENTED( scanner->graph ) || dst != edge->vtx[0] )
                    {
                        edge->flags |= CV_GRAPH_ITEM_VISITED_FLAG;
                        code = CV_GRAPH_BACK_EDGE;

                        if( !CV_IS_GRAPH_VERTEX_VISITED(dst) )
                        {
                            item.vtx = vtx;
                            item.edge = edge;

                            vtx->flags |= CV_GRAPH_SEARCH_TREE_NODE_FLAG;

                            cvSeqPush( scanner->stack, &item );
                            
                            if( scanner->mask & CV_GRAPH_TREE_EDGE )
                            {
                                code = CV_GRAPH_TREE_EDGE;
                                scanner->dst = dst;
                                scanner->edge = edge;
                                EXIT;
                            }
                            break;
                        }
                        else
                        {
                            if( scanner->mask & (CV_GRAPH_BACK_EDGE|
                                                 CV_GRAPH_CROSS_EDGE|
                                                 CV_GRAPH_FORWARD_EDGE) )
                            {
                                code = (dst->flags & CV_GRAPH_SEARCH_TREE_NODE_FLAG) ?
                                       CV_GRAPH_BACK_EDGE :
                                       (edge->flags & CV_GRAPH_FORWARD_EDGE_FLAG) ?
                                       CV_GRAPH_FORWARD_EDGE : CV_GRAPH_CROSS_EDGE;
                                edge->flags &= ~CV_GRAPH_FORWARD_EDGE_FLAG;
                                if( scanner->mask & code )
                                {
                                    scanner->vtx = vtx;
                                    scanner->dst = dst;
                                    scanner->edge = edge;
                                    EXIT;
                                }
                            }
                        }
                    }
                    else if( (dst->flags & (CV_GRAPH_ITEM_VISITED_FLAG|
                             CV_GRAPH_SEARCH_TREE_NODE_FLAG)) ==
                             (CV_GRAPH_ITEM_VISITED_FLAG|
                             CV_GRAPH_SEARCH_TREE_NODE_FLAG))
                    {
                        edge->flags |= CV_GRAPH_FORWARD_EDGE_FLAG;
                    }
                }

                edge = CV_NEXT_GRAPH_EDGE( edge, vtx );
            }

            if( !edge ) // need to backtrack
            {
                if( scanner->stack->total == 0 )
                {
                    if( scanner->index >= 0 )
                        vtx = 0;
                    else
                        scanner->index = 0;
                    break;
                }
                cvSeqPop( scanner->stack, &item );
                vtx = item.vtx;
                vtx->flags &= ~CV_GRAPH_SEARCH_TREE_NODE_FLAG;
                edge = item.edge;
                dst = 0;

                if( scanner->mask & CV_GRAPH_BACKTRACKING )
                {
                    scanner->vtx = vtx;
                    scanner->edge = edge;
                    scanner->dst = edge->vtx[vtx == edge->vtx[0]];
                    code = CV_GRAPH_BACKTRACKING;
                    EXIT;
                }
            }
        }

        if( !vtx )
        {
            vtx = (CvGraphVtx*)icvSeqFindNextElem( (CvSeq*)(scanner->graph),
                  CV_FIELD_OFFSET( flags, CvGraphVtx ), CV_GRAPH_ITEM_VISITED_FLAG|1,
                  0, &(scanner->index) );

            if( !vtx )
            {
                code = CV_GRAPH_OVER;
                icvEndScanGraph( scanner );
                scanner->stack = 0;
                break;
            }
        }

        dst = vtx;
        if( scanner->mask & CV_GRAPH_NEW_TREE )
        {
            scanner->dst = dst;
            scanner->edge = 0;
            scanner->vtx = 0;
            code = CV_GRAPH_NEW_TREE;
            break;
        }
    }

    __END__;

    return code;
}

/* End of file. */
