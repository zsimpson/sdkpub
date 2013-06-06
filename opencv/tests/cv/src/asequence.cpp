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

static char* struct_names[] = 
{
    "cvStartWriteSeq, cvEndWriteSeq, CV_WRITE_SEQ_ELEM, "
    "cvGetSeqElem, cvSeqElemIdx, "
    "cvStartReadSeq, CV_READ_SEQ_ELEM, "
    "cvSetSeqReaderPos, cvGetSeqReaderPos, "
    "cvSeqPush, cvSeqPop, "
    "cvSeqPushMulti, cvSeqPopMulti, "
    "cvSeqInsert, cvSeqRemove",
    "cvCreateSet, cvSetAdd, cvSetRemove, cvGetSetElem, cvClearSet",
    "cvCreateGraph, cvGraphAddVtx, cvGraphAddEdge, cvGraphRemoveVtx, "
    "cvGraphRemoveEdge, cvFindGraphEdge, cvClearGraph, cvCalcVertexDegree ",
    "icvSeqSort, icvSeqInvert, icvCopySeq, icvSeqSlice",
    "icvSeqInsertSlice, icvSeqRemoveSlice",
    "icvStartScanGraph, icvEndScanGraph, icvNextGraphItem"
};

static char* test_desc = "Verifying results of operations on abstract data types";

static int adt_l = 0, adt_h = ATS_DIM(struct_names)-1;
static int max_struct_size = 0; 
static int storage_block_size = 0;
static int iters = 0;
static int struct_count = 0;
//static int elem_size = 0;
const int elem_size = 7;
typedef struct elem_type
{
    char a[elem_size];
}
elem_type;

static int init_data_struct_params = 0;

static const char* ok_message = "No errors";

#define SEQUENCE_TEST     0
#define SET_TEST          1
#define GRAPH_TEST        2

static void read_data_struct_params( void )
{
    if( !init_data_struct_params )
    {
        int adt;
        
        trsCaseRead( &adt, "/a/seq/set/gr", "a",
                     "Structures to test: \n"
                     "a - all\n"
                     "seq - Sequences\n"
                     "set - Set\n"
                     "gr  - Graph\n" );
        if( adt != 0 ) adt_l = adt_h = adt - 1;

        trsiRead( &struct_count, "2", "number of structures" );
        trsiRead( &max_struct_size, "2000", "maximal number of elements in the struct" );
        //trsiRead( &elem_size, "7", "size of element" );
        trsiRead( &iters, "10", "number of iterations");
        trsiRead( &storage_block_size, "104", "size of storage blocks (bytes)" );

        init_data_struct_params = 1;
    }
}


/****************************************************************************************\
*                          implementation of array sequence                              *
\****************************************************************************************/

typedef  struct  _simple_seq
{
    char* array;
    int   count;
    int   max_count;
    int   elem_size;
}
simple_seq;


simple_seq*  create_simple_seq( int max_count, int elem_size )
{
    simple_seq* seq = (simple_seq*)icvAlloc( sizeof(*seq) + max_count * elem_size);
    seq->elem_size = elem_size;
    seq->max_count = max_count;
    seq->count = 0;
    seq->array = (char*)(seq + 1);
    return seq;
}

void release_simple_seq( simple_seq** seq )
{
    icvFree( seq );
}


char*  simple_seq_elem( simple_seq* seq, int index )
{
    assert( 0 <= index && index < seq->count );
    return seq->array + index * seq->elem_size;
}


void  push_simple_seq_elem( simple_seq* seq, void* elem )
{
    assert( seq->count < seq->max_count );
    memcpy( seq->array + seq->count * seq->elem_size, elem, seq->elem_size );
    seq->count++;
}


void  drop_simple_seq_elem( simple_seq* seq )
{
    assert( seq->count > 0 );
    seq->count--;
}


void  clear_simple_seq( simple_seq* seq )
{
    seq->count = 0;
}


void  remove_simple_seq_elem( simple_seq* seq, int index )
{
    int elem_size = seq->elem_size;
    assert( seq->count > index );
    
    memmove( seq->array + index*elem_size, seq->array + (index + 1)*elem_size,
             (seq->count - index - 1) * elem_size );
    seq->count--;
}


void  insert_simple_seq_elem( simple_seq* seq, int index, void* elem )
{
    int elem_size = seq->elem_size;
    assert( seq->count < seq->max_count );
    
    memmove( seq->array + (index + 1)*elem_size, seq->array + index * elem_size,
             (seq->count - index) * elem_size );
    memcpy( seq->array + index * elem_size, elem, elem_size );
    
    seq->count++;
}


/****************************************************************************************\
*                            implementation of simple set                                *
\****************************************************************************************/

typedef  struct  _simple_set
{
    char* array;
    int   count;
    int   max_count;
    int   elem_size;
    int*  free_stack;
    int   free_count;
}
simple_set;


void  clear_simple_set( simple_set* set )
{
    int i;
    int elem_size = set->elem_size;
    set->count = 0;

    for( i = 0; i < set->max_count; i++ )
    {
        set->array[i*elem_size] = 0;
        set->free_stack[i] = set->max_count - i - 1;
    }
    set->free_count = set->max_count;
}


simple_set*  create_simple_set( int max_count, int elem_size )
{
    simple_set* set = (simple_set*)icvAlloc( sizeof(*set) + max_count *
                                        (elem_size + 1 + sizeof(int)));
    set->elem_size = elem_size + 1;
    set->max_count = max_count;
    set->array = (char*)(set + 1);
    set->free_stack = (int*)(set->array + max_count * set->elem_size);

    clear_simple_set( set );
    return set;
}

void release_simple_set( simple_set** set )
{
    icvFree( set );
}


char*  find_simple_set_elem( simple_set* set, int index )
{
    int idx = index * set->elem_size;
    assert( 0 <= index && index < set->max_count );
    return set->array[idx] ? set->array + idx + 1 : 0;
}


int  add_simple_set_elem( simple_set* set, void* elem )
{
    int idx, idx2;
    assert( set->free_count > 0 );

    idx = set->free_stack[--set->free_count];
    idx2 = idx * set->elem_size;
    assert( set->array[idx2] == 0 );
    set->array[idx2] = 1;
    memcpy( set->array + idx2 + 1, elem, set->elem_size - 1 );
    
    if( idx >= set->count ) set->count = idx + 1;
    return idx;
}


void  remove_simple_set_elem( simple_set* set, int index )
{
    assert( set->free_count < set->max_count &&
            0 <= index && index < set->max_count );
    assert( set->array[index * set->elem_size] == 1 );

    set->free_stack[set->free_count++] = index;
    set->array[index * set->elem_size] = 0;
}


/****************************************************************************************\
*                              implementation of simple graph                            *
\****************************************************************************************/

typedef  struct  _simple_graph
{
    char* matrix;
    int   elem_size;
    int   oriented;
    simple_set* vtx;
}
simple_graph;


void  clear_simple_graph( simple_graph* graph )
{
    int max_vtx_count = graph->vtx->max_count;
    clear_simple_set( graph->vtx );
    memset( graph->matrix, 0, max_vtx_count * max_vtx_count * graph->elem_size );
}


simple_graph*  create_simple_graph( int max_vtx_count, int vtx_size,
                                    int edge_size, int oriented )
{
    simple_graph* graph;

    assert( max_vtx_count > 1 && vtx_size > 0 && edge_size > 0 );
    graph = (simple_graph*)icvAlloc( sizeof(*graph) +
                  max_vtx_count * max_vtx_count * (edge_size + 1));
    graph->vtx = create_simple_set( max_vtx_count, vtx_size );
    graph->elem_size = edge_size + 1;
    graph->matrix = (char*)(graph + 1);
    graph->oriented = oriented;

    clear_simple_graph( graph );
    return graph;
}


void release_simple_graph( simple_graph** graph )
{
    release_simple_set( &(graph[0]->vtx) );
    icvFree( graph );
}


int  add_simple_graph_vertex( simple_graph* graph, void* vertex )
{
    return add_simple_set_elem( graph->vtx, vertex );
}


void  remove_simple_graph_vertex( simple_graph* graph, int index )
{
    int i, max_vtx_count = graph->vtx->max_count;
    int elem_size = graph->elem_size;
    remove_simple_set_elem( graph->vtx, index );

    /* remove all the corresponding edges */
    for( i = 0; i < max_vtx_count; i++ )
    {
        graph->matrix[(i*max_vtx_count + index)*elem_size] = 
        graph->matrix[(index*max_vtx_count + i)*elem_size] = 0;
    }
}


void  add_simple_graph_edge( simple_graph* graph, int idx1, int idx2, void* edge )
{
    assert( find_simple_set_elem( graph->vtx, idx1 ) &&
            find_simple_set_elem( graph->vtx, idx2 ));

    if( graph->oriented )
    {
        int ofs = (idx1*graph->vtx->max_count + idx2)*graph->elem_size;
        assert( graph->matrix[ofs] == 0 );
        graph->matrix[ofs] = 1;
        memcpy( graph->matrix + ofs + 1, edge, graph->elem_size - 1 );
    }
    else
    {
        graph->oriented = 1;
        add_simple_graph_edge( graph, idx1, idx2, edge );
        add_simple_graph_edge( graph, idx2, idx1, edge );
        graph->oriented = 0;
    }
}


void  remove_simple_graph_edge( simple_graph* graph, int idx1, int idx2 )
{
    assert( find_simple_set_elem( graph->vtx, idx1 ) &&
            find_simple_set_elem( graph->vtx, idx2 ));

    if( graph->oriented )
    {
        int ofs = (idx1*graph->vtx->max_count + idx2)*graph->elem_size;
        assert( graph->matrix[ofs] == 1 );
        graph->matrix[ofs] = 0;
    }
    else
    {
        graph->oriented = 1;
        remove_simple_graph_edge( graph, idx1, idx2 );
        remove_simple_graph_edge( graph, idx2, idx1 );
        graph->oriented = 0;
    }
}


char*  find_simple_graph_vertex( simple_graph* graph, int index )
{
    return find_simple_set_elem( graph->vtx, index );
}


char*  find_simple_graph_edge( simple_graph* graph, int idx1, int idx2 )
{
    if( find_simple_graph_vertex( graph, idx1 ) &&
        find_simple_graph_vertex( graph, idx2 ))
    {
        char* edge = graph->matrix + (idx1 * graph->vtx->max_count + idx2)*graph->elem_size;
        if( edge[0] ) return edge + 1;
    }
    return 0;
}


int  calc_simple_graph_vertex_degree( simple_graph* graph, int index )
{
    int i, count = 0;
    int elem_size = graph->elem_size;
    int max_vtx_count = graph->vtx->max_count;
    assert( find_simple_graph_vertex( graph, index ) != 0 );
    
    for( i = 0; i < max_vtx_count; i++ )
    {
        count += graph->matrix[(i*max_vtx_count + index)*elem_size] + 
                 graph->matrix[(index*max_vtx_count + i)*elem_size];
    }

    if( !(graph->oriented))
    {
        assert( count % 2 == 0 );
        count /= 2;
    }
    return count;
}

/*********************** tests ****************************/

/*#define DO_CV_ACTION( func_name, args )            \
    result = func_name args;                         \
    if( result < 0 )                                 \
    {                                                \
        message_string = #func_name " fails";        \
        goto test_exit;                              \
    }*/

#define DO_CV_ACTION( func_name, args ) { func_name args; }


#define CHECK_CONDITION( expr, msg )   \
    if( !(expr) )                      \
    {                                  \
        message_string = (msg);        \
        code = TRS_FAIL;               \
        goto test_exit;                \
    }


static int check_seq_block_consistence( CvSeq* seq, int total, const char** msg )
{
    int sum = 0, code = TRS_OK;
    const char* message_string = *msg;

    CHECK_CONDITION( seq, "Null sequence pointer" );
    
    if( seq->first )
    {
        CvSeqBlock* block = seq->first;
        CvSeqBlock* prev_block = block->prev;
        
        int delta_idx = seq->first->start_index;

        for( ;; )
        {
            CHECK_CONDITION( sum == block->start_index - delta_idx &&
                             block->count > 0 && block->prev == prev_block &&
                             prev_block->next == block,
                             "Sequence blocks are inconsistent" );
            sum += block->count;                
            prev_block = block;
            block = block->next;
            if( block == seq->first ) break;
        }

        CHECK_CONDITION( block->prev->count * seq->elem_size +
                         block->prev->data <= seq->block_max,
                         "block->data or block_max pointer are incorrect" );
    }

    CHECK_CONDITION( seq->total == sum && sum == total, "total number is undefined" );

test_exit:

    *msg = message_string;
    return code;
}


static int  check_get_seq_elem( CvSeq* seq, simple_seq* sseq,
                                AtsRandState* rng_state, int iters,
                                const char** msg, CvStatus * _result )
{
    const char* message_string = *msg;
    CvStatus  result = *_result;
    int i = 0, code = TRS_OK;
    assert( seq->total == sseq->count );
    atsRandSetBounds( rng_state, -sseq->count*3/2, sseq->count*3/2 );

    for( i = 0; i < iters; i++ )
    {
        CvSeqBlock* block = 0;
        CvSeqBlock* block1 = 0;
        int idx = atsRand32s( rng_state );
        int idx0 = (unsigned)idx < (unsigned)(sseq->count) ? idx : idx < 0 ?
                   idx + sseq->count : idx - sseq->count;
        int flag = atsRand32s(rng_state) & 1;
        int bad_range = (unsigned)idx0 >= (unsigned)(sseq->count);
        char* elem = cvGetSeqElem( seq, idx, flag ? &block : 0 );

        if( bad_range )
        {
            CHECK_CONDITION( elem == 0,
                             "cvGetSeqElem doesn't "
                             "handle \"out of range\" properly" );
        }
        else
        {
            CHECK_CONDITION( elem != 0 &&
                             !memcmp( elem, simple_seq_elem( sseq, idx0), elem_size ) &&
                             (!flag || block != 0 &&
                            (unsigned)(idx0 - block->start_index +
                            seq->first->start_index) <= (unsigned)(block->count)),
                            "cvGetSeqElem is incorrect" );

            flag = atsRand32s(rng_state) & 1;
            idx = cvSeqElemIdx(seq, elem, flag ? &block1 : 0 );

            CHECK_CONDITION( idx >= 0 && idx == idx0 &&
                             (!flag || block1 != 0 && (!block || block1 == block)),
                            "cvSeqElemIdx is incorrect" );
        }
    }

test_exit:
    *msg = message_string;
    *_result = result;
    return code;
}



static int  check_get_seq_reading( CvSeq* seq, simple_seq* sseq,
                                   AtsRandState* rng_state, int iters,
                                   const char** msg, CvStatus * _result )
{
    const int max_val = 3*5 + 2;
    const char* message_string = *msg;
    CvStatus  result = *_result;
    int i = 0, code = TRS_OK, pos;
    int total = seq->total;
    CvSeqReader  reader;
    char* elem;
    elem_type el;

    elem = (char*)icvAlloc( sseq->elem_size );

    assert( total == sseq->count );

    atsRandSetBounds( rng_state, 0, 2 );
    pos = atsRand32s( rng_state ); 

    if( total == 0 )
    {
        cvStartReadSeq( seq, &reader, pos );
        /*CHECK_CONDITION( cvStartReadSeq( seq, &reader, pos ) < 0,
                         "start reading doesn't fail on empty seq" );*/
        goto test_exit;
    }

    cvStartReadSeq( seq, &reader, pos );
    DO_CV_ACTION( cvStartReadSeq, ( seq, &reader, pos ) );
    pos = pos ? seq->total - 1 : 0;

    CHECK_CONDITION( pos == cvGetSeqReaderPos(&reader),
                     "initial position of reader is wrong" );

    for( i = 0; i < iters; i++ )
    {
        int op;

        atsRandSetBounds( rng_state, 0, max_val );
        op = atsRand32s( rng_state );

        if( op >= max_val - 2 )
        {
            int new_pos, new_pos0;
            int bad_range;
            int is_relative = op == max_val - 1;

            atsRandSetBounds( rng_state, -total, total );

            new_pos = atsRand32s( rng_state );
            new_pos0 = new_pos + (is_relative ? pos : 0 );

            if( new_pos0 < 0 ) new_pos0 += total;
            if( new_pos0 >= total ) new_pos0 -= total;

            bad_range = (unsigned)new_pos0 >= (unsigned)total;

            if( !bad_range )
            {
                DO_CV_ACTION( cvSetSeqReaderPos,
                                ( &reader, new_pos, is_relative ) );
                CHECK_CONDITION( new_pos0 == cvGetSeqReaderPos( &reader ),
                                 "set reader position doesn't work" );
                pos = new_pos0;
            }
            else
            {
                cvSetSeqReaderPos( &reader, new_pos, is_relative );
                /*CHECK_CONDITION( cvSetSeqReaderPos( new_pos, is_relative, &reader ) < 0,
                   "set reader position doesn't handle \"out of range\"" );*/
                CHECK_CONDITION( pos == cvGetSeqReaderPos( &reader ),
                   "reader doesn't leave previous position after wrong positioning" );
            }
        }
        else
        {
            int direction = (op % 3) - 1;

            if( direction > 0 )
            {
                CV_READ_SEQ_ELEM( el, reader )
            }
            else if( direction < 0 )
            {
                CV_REV_READ_SEQ_ELEM( el, reader )
            }
            else
            {
                el = (elem_type&)(reader.ptr[0]);
            }

            CHECK_CONDITION( !memcmp( &el, simple_seq_elem( sseq, pos), elem_size),
                             "reading is incorrect" );
            pos += direction;
            if( pos < 0 ) pos += total;
            if( pos >= total ) pos -= total;

            CHECK_CONDITION( pos == cvGetSeqReaderPos( &reader ),
                   "reader doesn't move position correctly after reading" );
        }
    }

test_exit:
    
    icvFree( &elem );
    *msg = message_string;
    *_result = result;
    return code;
}


static int  test_multi_create( int count, CvSeq** seq,
                               int hdr_size, simple_seq** sseq,
                               CvMemStorage* storage, AtsRandState* rng_state,
                               const char** msg, CvStatus * _result )
{
    const char* message_string = *msg;
    CvStatus  result = *_result;
    CvSeqWriter* writer = 0;
    int* pos = 0;
    int* index = 0;
    int  j, count2;
    int  code = TRS_OK;

    writer = (CvSeqWriter*)icvAlloc( count * sizeof(writer[0]));
    index = (int*)icvAlloc(count * sizeof(index[0]));
    pos = (int*)icvAlloc(count * sizeof(pos[0]));

    assert( writer && index && pos );
    
    for( j = 0; j < count; j++ )
    {
        pos[j] = -1;
        index[j] = j;
    }

    for( count2 = count; count2 > 0; count2-- )
    {
        atsRandSetBounds( rng_state, 0, count2 );

        for(;;)
        {
            int k = atsRand32s( rng_state );
            int seq_idx = index[k];

            if( pos[seq_idx] < 0 )
            {
                DO_CV_ACTION( cvStartWriteSeq,
                    ( 0, hdr_size, elem_size, storage, writer + seq_idx ));
                cvSetSeqBlockSize( writer[seq_idx].seq, atsRandPlain32s( rng_state ) % 10000 );
                pos[seq_idx] = 0;
            }

            if( pos[seq_idx] == sseq[seq_idx]->count )
            {
                seq[seq_idx] = cvEndWriteSeq( writer + seq_idx );
                /* del index */
                memmove( index + k, index + k + 1, (count2 - k - 1)*sizeof(int));
                break;
            }
            
            {
                elem_type el = (elem_type&)(simple_seq_elem( sseq[seq_idx],
                                                             pos[seq_idx] )[0]);
                CV_WRITE_SEQ_ELEM( el, writer[seq_idx] );
            }
            pos[seq_idx]++;
        }
    }

/*test_exit:*/

    icvFree( &writer );
    icvFree( &index );
    icvFree( &pos );

    *msg = message_string;
    *_result = result;
    return code;
}


static int  test_seq_ops( int count, CvSeq** seq, simple_seq** sseq,
                          AtsRandState* rng_state, int iters,
                          const char** msg, CvStatus * _result )
{
    const int max_op = 8;
    const char* message_string = *msg;
    CvStatus  result = *_result;
    int i, k, code = TRS_OK;
    char* elem;
    char* elem2;
    int idx, num;
    int seq_idx, op;

    elem = (char*)icvAlloc( (max_struct_size + 1) * elem_size );

    for( i = 0; i < iters; i++ )
    {
        atsRandSetBounds( rng_state, 0, count * max_op );

        seq_idx = atsRand32s( rng_state );
        op = seq_idx % max_op;
        seq_idx /= max_op;

        switch( op )
        {
        case 0: /* push */

            if( sseq[seq_idx]->count == sseq[seq_idx]->max_count  ) break;

            atsbRand8s( rng_state, elem, elem_size );
            push_simple_seq_elem( sseq[seq_idx], elem );
            
            DO_CV_ACTION( cvSeqPush, ( seq[seq_idx], elem ));

            idx = sseq[seq_idx]->count - 1;
            elem2 = cvGetSeqElem( seq[seq_idx], idx, 0 );
            if( !elem2 )
            {
                message_string = "Push operation doesn't add the element";
                code = TRS_FAIL;
                goto test_exit;
            }

            CHECK_CONDITION( seq[seq_idx]->total == sseq[seq_idx]->count &&
                             !memcmp( elem2, simple_seq_elem(sseq[seq_idx],idx), elem_size),
                             "The last sequence element is wrong after PUSH" );
            break;

        case 1: /* pop */

            if( sseq[seq_idx]->count == 0 ) break;
            
            idx = sseq[seq_idx]->count - 1;
            DO_CV_ACTION( cvSeqPop, ( seq[seq_idx], elem ));

            CHECK_CONDITION( seq[seq_idx]->total == sseq[seq_idx]->count - 1 &&
                       !memcmp( elem, simple_seq_elem(sseq[seq_idx],idx), elem_size),
                       "The popped sequence element isn't equal to last elem of simple seq" );

            drop_simple_seq_elem( sseq[seq_idx] );
            if( sseq[seq_idx]->count != 0 )
            {
                elem2 = cvGetSeqElem( seq[seq_idx], -1, 0 );
                if( !elem2 )
                {
                    message_string = "GetSequenceElementPtr fails after POP";
                    code = TRS_FAIL;
                    goto test_exit;
                }

                CHECK_CONDITION( !memcmp( elem2, simple_seq_elem(sseq[seq_idx],idx-1), elem_size),
                                 "The last sequence element is wrong after POP" );
            }
            else
            {
                CHECK_CONDITION( seq[seq_idx]->first == 0,
                                 "The sequence doesn't become empty after final POP" );
            }
            break;

        case 2: /* insert */

            if( sseq[seq_idx]->count == sseq[seq_idx]->max_count  ) break;
            atsbRand8s( rng_state, elem, elem_size );

            idx = atsRandPlain32s( rng_state ) % (sseq[seq_idx]->count + 1);
            
            insert_simple_seq_elem( sseq[seq_idx], idx, elem );
            
            DO_CV_ACTION( cvSeqInsert, ( seq[seq_idx], idx, elem ));

            elem2 = cvGetSeqElem( seq[seq_idx], idx, 0 );
            if( !elem2 )
            {
                message_string = "Insert operation doesn't add the element";
                code = TRS_FAIL;
                goto test_exit;
            }

            CHECK_CONDITION( seq[seq_idx]->total == sseq[seq_idx]->count &&
                             !memcmp( elem2, simple_seq_elem(sseq[seq_idx],idx), elem_size),
                             "The inserted sequence element is wrong" );
            break;

        case 3: /* remove */

            if( sseq[seq_idx]->count == 0 ) break;
            
            idx = atsRandPlain32s( rng_state ) % sseq[seq_idx]->count;
            DO_CV_ACTION( cvSeqRemove, ( seq[seq_idx], idx ));

            remove_simple_seq_elem( sseq[seq_idx], idx );

            if( idx < sseq[seq_idx]->count )
            {
                elem2 = cvGetSeqElem( seq[seq_idx], idx, 0 );
                if( !elem2 )
                {
                    message_string = "GetSequenceElementPtr fails after Remove";
                    code = TRS_FAIL;
                    goto test_exit;
                }

                CHECK_CONDITION( seq[seq_idx]->total == sseq[seq_idx]->count &&
                                 !memcmp( elem2, simple_seq_elem(sseq[seq_idx],idx), elem_size),
                                 "The element after removed one is wrong" );
            }
            else
            {
                CHECK_CONDITION( seq[seq_idx]->total == sseq[seq_idx]->count,
                                 "The sequence doesn't become empty after final POP" );
            }
            break;

        case 4: /* batch push */
            
            if( sseq[seq_idx]->count == sseq[seq_idx]->max_count  ) break;

            num = atsRandPlain32s( rng_state ) %
                  (sseq[seq_idx]->max_count - sseq[seq_idx]->count + 1);

            atsbRand8s( rng_state, elem, num * elem_size );
            
            for( k = 0; k < num; k++ )
            {
                push_simple_seq_elem( sseq[seq_idx], elem + k * elem_size );
            }
            
            DO_CV_ACTION( cvSeqPushMulti, ( seq[seq_idx], elem, num ));

            idx = sseq[seq_idx]->count;

            if( idx > 0 )
            {
                /* choose the random element among added */
                idx = num > 0 ? atsRandPlain32s( rng_state ) % num + (idx - num) : idx - 1;
                elem2 = cvGetSeqElem( seq[seq_idx], idx, 0 );
                if( !elem2 )
                {
                    message_string = "Multi Push operation doesn't add the element";
                    code = TRS_FAIL;
                    goto test_exit;
                }

                CHECK_CONDITION( seq[seq_idx]->total == sseq[seq_idx]->count &&
                                 !memcmp( elem2, simple_seq_elem(sseq[seq_idx],idx), elem_size),
                                 "The last sequence element is wrong after PUSH" );
            }
            else
            {
                CHECK_CONDITION( seq[seq_idx]->total == 0 && seq[seq_idx]->first == 0,
                                 "Adding no elements to empty sequence fails" );
            }
            break;

        case 5: /* multi pop */
            
            if( sseq[seq_idx]->count == 0 ) break;
            
            num = atsRandPlain32s( rng_state ) % (sseq[seq_idx]->count+1);

            DO_CV_ACTION( cvSeqPopMulti, ( seq[seq_idx], elem, num ));
            
            CHECK_CONDITION( seq[seq_idx]->total == sseq[seq_idx]->count - num,
                       "The multi pop left a wrong number of elements in the sequence" );

            idx = sseq[seq_idx]->count - num;
            if( num != 0 )
            {
                CHECK_CONDITION( !memcmp( elem, simple_seq_elem(sseq[seq_idx],idx), elem_size),
                             "The last popped sequence element is wrong after MULTI PUSH" );
            }

            sseq[seq_idx]->count = idx;

            if( sseq[seq_idx]->count != 0 )
            {
                elem2 = cvGetSeqElem( seq[seq_idx], -1, 0 );
                if( !elem2 )
                {
                    message_string = "GetSequenceElementPtr fails after POP";
                    code = TRS_FAIL;
                    goto test_exit;
                }

                CHECK_CONDITION( !memcmp( elem2, simple_seq_elem(sseq[seq_idx],idx-1), elem_size),
                                 "The last sequence element is wrong after POP" );
            }
            else
            {
                CHECK_CONDITION( seq[seq_idx]->first == 0,
                                 "The sequence doesn't become empty after final POP" );
            }
            break;

        case 6: /* push front */
            
            if( sseq[seq_idx]->count == sseq[seq_idx]->max_count  ) break;

            atsbRand8s( rng_state, elem, elem_size );
            
            idx = 0;
            insert_simple_seq_elem( sseq[seq_idx], idx, elem );
            
            DO_CV_ACTION( cvSeqPushFront, ( seq[seq_idx], elem ));
            
            elem2 = cvGetSeqElem( seq[seq_idx], idx, 0 );
            if( !elem2 )
            {
                message_string = "Push operation doesn't add the element";
                code = TRS_FAIL;
                goto test_exit;
            }

            CHECK_CONDITION( seq[seq_idx]->total == sseq[seq_idx]->count &&
                             !memcmp( elem2, simple_seq_elem(sseq[seq_idx],idx), elem_size),
                             "The first sequence element is wrong after PUSH FRONT" );
            break;

        case 7: /* pop front */
            
            if( sseq[seq_idx]->count == 0 ) break;
            
            idx = 0;
            DO_CV_ACTION( cvSeqPopFront, ( seq[seq_idx], elem ));

            CHECK_CONDITION( seq[seq_idx]->total == sseq[seq_idx]->count - 1 &&
                       !memcmp( elem, simple_seq_elem(sseq[seq_idx],idx), elem_size),
                       "The popped sequence element isn't equal to last elem of simple seq" );

            remove_simple_seq_elem( sseq[seq_idx], 0 );
            if( sseq[seq_idx]->count != 0 )
            {
                elem2 = cvGetSeqElem( seq[seq_idx], 0, 0 );
                if( !elem2 )
                {
                    message_string = "GetSequenceElementPtr fails after POP";
                    code = TRS_FAIL;
                    goto test_exit;
                }

                CHECK_CONDITION( !memcmp( elem2, simple_seq_elem(sseq[seq_idx],0), elem_size),
                                 "The first sequence element is wrong after POP FRONT" );
            }
            else
            {
                CHECK_CONDITION( seq[seq_idx]->first == 0,
                                 "The sequence doesn't become empty after final POP FRONT" );
            }
            break;

        default:
            assert(0);
            message_string = "Unknown error";
            code = TRS_FAIL;
            goto test_exit;
        }

        code = check_seq_block_consistence( seq[seq_idx], sseq[seq_idx]->count,
                                            &message_string );
        if( code != TRS_OK ) goto test_exit;

        code = check_get_seq_elem( seq[seq_idx], sseq[seq_idx],
                                   rng_state, 7, &message_string, &result );
        if( code != TRS_OK || result < 0 ) goto test_exit;
    }

test_exit:

    icvFree( &elem );

    *msg = message_string;
    *_result = result;
    return code;
}


static int calc_storage_blocks( CvMemStorage* storage )
{
    CvMemBlock* mblock = storage->bottom;
    int count = 0;

    for( ; mblock != 0; count++, mblock = mblock->next );

    return count;
}

/* sequence test */
static int  test_sequence( void )
{
    const char*  message_string = ok_message;
    int i = 0, j, k = 0, code = TRS_OK;
    CvStatus   result = CV_NO_ERR;
    simple_seq** sseq = 0;
    CvSeq** seq = 0;
    CvMemStorage* storage = 0;

    int seed = atsGetSeed();
    AtsRandState rng_state;

    read_data_struct_params();
    if( !ATS_RANGE( SEQUENCE_TEST, adt_l, adt_h+1 )) return TRS_UNDEF;

    atsRandInit( &rng_state, 0, 1, seed );

    sseq = (simple_seq**)icvAlloc( struct_count * sizeof(simple_seq*));
    seq = (CvSeq**)icvAlloc( struct_count * sizeof(CvSeq*));

    for( j = 0; j < struct_count; j++ )
    {
        sseq[j] = create_simple_seq( max_struct_size, elem_size );
        seq[j] = 0;
    }

    storage = cvCreateMemStorage( storage_block_size );

#if 1
    for( i = 0; i < iters; i++ )
    {
        atsRandSetBounds( &rng_state, 0, max_struct_size - 10 );
        
        for( j = 0; j < struct_count; j++ )
        {
            sseq[j]->count = atsRand32s( &rng_state );
            atsbRand8s( &rng_state, sseq[j]->array, sseq[j]->count * sseq[j]->elem_size );
        }

        code = test_multi_create( struct_count, seq, sizeof(CvSeq) + 12,
                                  sseq, storage, &rng_state,
                                  &message_string, &result );
        if( code != TRS_OK || result < 0 ) goto test_exit;

        for( j = 0; j < struct_count; j++ )
        {
            code = check_seq_block_consistence( seq[j], sseq[j]->count, &message_string );
            if( code != TRS_OK ) goto test_exit;

            code = check_get_seq_elem( seq[j], sseq[j], &rng_state,
                                       MAX( sseq[j]->count/2, 10),
                                       &message_string, &result );
            if( code != TRS_OK || result < 0 ) goto test_exit;

            code = check_get_seq_reading( seq[j], sseq[j], &rng_state,
                                          MAX( sseq[j]->count/2, 10),
                                          &message_string, &result );

            if( code != TRS_OK || result < 0 ) goto test_exit;
        }

        code = test_seq_ops( struct_count, seq, sseq, &rng_state,
                             max_struct_size, &message_string, &result );
        if( code != TRS_OK || result < 0 ) goto test_exit;

        trsWrite( ATS_LST|ATS_CON,
            "iter = %d, storage blocks = %d\n", i, calc_storage_blocks(storage) );
    }
#else
    CvSeq* mseq = cvCreateSeq( 0, sizeof(CvSeq), 3, storage );
    for( int k1 = 0; k1 < 10000; k1++ )
    {
        cvSeqPush( mseq, &k1 );
    }
#endif
test_exit:

    if( code == TRS_OK && result >= 0 )
    {
        DO_CV_ACTION( cvReleaseMemStorage, ( &storage ));
    }
    else
    {
        cvReleaseMemStorage( &storage );
        trsWrite( ATS_LST, "seed = %08x, iter = %d, index = %d", seed, i, k );
        if( result < 0 ) trsWrite( ATS_LST, "error code: %d", result );
    }

    for( j = 0; j < struct_count; j++ )
    {
        release_simple_seq( sseq + j );
    }

    icvFree( &sseq );
    icvFree( &seq );

    return trsResult( code, message_string );
}



static int  test_set_ops( int count, CvSet** set, simple_set** sset,
                          AtsRandState* rng_state, int iters,
                          CvMemStorage* storage,
                          const char** msg, CvStatus * _result )
{
    const int max_op = 50*2 + 1;
    const char* message_string = *msg;
    CvStatus  result = *_result;
    int i, code = TRS_OK;
    char *elem4;
    CvSetElem *elem, *elem2, *elem3;
    int idx, idx2;
    int set_idx, op;
    int elem_size = sset[0]->elem_size - 1;
    int work_elem_size = ((elem_size + 3) & -4) + 4;

    elem = (CvSetElem*)icvAlloc( work_elem_size );

    for( i = 0; i < iters; i++ )
    {
        atsRandSetBounds( rng_state, 0, count * max_op );

        set_idx = atsRand32s( rng_state );
        op = set_idx % max_op;
        set_idx /= max_op;

        if( op == 0 ) /* clear */
        {
            if( set[set_idx] != 0 )
            {
                int prev_total = set[set_idx]->total;
                
                clear_simple_set( sset[set_idx] );
                DO_CV_ACTION( cvClearSet, ( set[set_idx] ));

                CHECK_CONDITION( set[set_idx]->total == 0 &&
                                 set[set_idx]->first == 0 &&
                                 set[set_idx]->free_elems == 0 &&
                                 (set[set_idx]->free_blocks != 0 || prev_total == 0),
                                 "The set is not empty after clearing" );
            }
            else
            {
                CHECK_CONDITION( sset[set_idx]->free_count == sset[set_idx]->max_count,
                                 "The set is empty while the simple_set is not" );
            }
        }
        else if( op % 2 == 0 ) /* add */
        {
            if( sset[set_idx]->free_count == 0  ) break;

            atsbRand8s( rng_state, (char*)(elem + 1), elem_size );
            idx = add_simple_set_elem( sset[set_idx], elem + 1 );
        
            if( set[set_idx] == 0 )
            {
                set[set_idx] = cvCreateSet( 0, sizeof(CvSet),
                                              work_elem_size, storage );
                if( !set[set_idx] )
                {
                    message_string = "cvCreateSet fails";
                    code = TRS_FAIL;
                    goto test_exit;
                }
            }
        
            idx2 = cvSetAdd( set[set_idx], elem, &elem2 );
            if( idx2 < 0 )
            {
                message_string = "cvSetAdd fails";
                code = TRS_FAIL;
                goto test_exit;
            }

            elem3 = cvGetSetElem( set[set_idx], idx2 );
            if( !elem3 )
            {
                message_string = "cvSetAdd doesn't add the element";
                code = TRS_FAIL;
                goto test_exit;
            }

            elem4 = find_simple_set_elem( sset[set_idx], idx );

            CHECK_CONDITION( CV_IS_SET_ELEM_EXISTS( elem2 ) &&
                             elem2 == elem3 && idx == idx2 &&
                             !memcmp( elem2 + 1, elem4, elem_size),
                             "The element is added to set incorrectly" );
        }
        else /* remove */
        {
            idx = atsRandPlain32s( rng_state ) % MAX( sset[set_idx]->count, 1);
            elem4 = find_simple_set_elem( sset[set_idx], idx );

            if( elem4 != 0 )
            {
                assert( set[set_idx] != 0 );

                elem2 = cvGetSetElem( set[set_idx], idx );
                if( !elem2 )
                {
                    message_string = "Existing element is not found";
                    code = TRS_FAIL;
                    goto test_exit;
                }

                CHECK_CONDITION( CV_IS_SET_ELEM_EXISTS(elem2) &&
                                 !memcmp( elem2 + 1, elem4, elem_size ),
                                 "Found element is incorrect");

                remove_simple_set_elem( sset[set_idx], idx );

                DO_CV_ACTION( cvSetRemove, ( set[set_idx], idx ));
                if( cvGetSetElem( set[set_idx], idx ) != 0 )
                {
                    message_string = "Element is not removed from the set";
                    code = TRS_FAIL;
                    goto test_exit;
                }

                CHECK_CONDITION( !CV_IS_SET_ELEM_EXISTS( elem2 ),
                                 "Remove operation doesn't clear existence flag");
            }
        }


        if( set[set_idx] )
        {
            code = check_seq_block_consistence( (CvSeq*)set[set_idx],
                                                sset[set_idx]->count,
                                                &message_string );
            if( code != TRS_OK ) goto test_exit;
        }
        else
        {
            CHECK_CONDITION( sset[set_idx]->free_count == sset[set_idx]->max_count,
                         "CvSet has different number of elements with simple_set");
        }
    }

test_exit:

    icvFree( &elem );

    *msg = message_string;
    *_result = result;
    return code;
}


static int  test_set( void )
{
    const char*  message_string = ok_message;
    int i = 0, j, k = 0, code = TRS_OK;
    CvStatus   result = CV_NO_ERR;
    simple_set** sset = 0;
    CvSet** set = 0;
    CvMemStorage* storage = 0;

    int seed = atsGetSeed();
    AtsRandState rng_state;

    read_data_struct_params();
    if( !ATS_RANGE( SET_TEST, adt_l, adt_h+1 )) return TRS_UNDEF;

    atsRandInit( &rng_state, 0, 1, seed );

    sset = (simple_set**)icvAlloc( struct_count * sizeof(simple_set*));
    set = (CvSet**)icvAlloc( struct_count * sizeof(CvSet*));

    for( j = 0; j < struct_count; j++ )
    {
        sset[j] = create_simple_set( max_struct_size, elem_size );
        set[j] = 0;
    }

    storage = cvCreateMemStorage( storage_block_size );

    for( i = 0; i < iters; i++ )
    {
        atsRandSetBounds( &rng_state, 0, max_struct_size - 10 );
        
        code = test_set_ops( struct_count, set, sset, &rng_state,
                             max_struct_size*2, storage, &message_string, &result );
        if( code != TRS_OK || result < 0 ) goto test_exit;

        trsWrite( ATS_LST|ATS_CON,
            "iter = %d, storage blocks = %d\n", i, calc_storage_blocks(storage) );
    }

test_exit:

    if( result < 0 ) code = TRS_FAIL;

    if( code == TRS_OK && result >= 0 )
    {
        DO_CV_ACTION( cvReleaseMemStorage, ( &storage ));
    }
    else
    {
        cvReleaseMemStorage( &storage );
        trsWrite( ATS_LST, "seed = %08x, iter = %d, index = %d", seed, i, k );
        if( result < 0 ) trsWrite( ATS_LST, "error code: %d", result );
    }

    for( j = 0; j < struct_count; j++ )
    {
        release_simple_set( sset + j );
    }

    icvFree( &sset );
    icvFree( &set );

    return trsResult( code, message_string );
}


static int  test_graph_ops( int count, CvGraph** gr, simple_graph** sgr,
                            AtsRandState* rng_state, int iters,
                            CvMemStorage* storage,
                            const char** msg, CvStatus * _result )
{
    const int max_op_ex = 4;
    const int max_op = 100*max_op_ex + 1;
    const char* message_string = *msg;
    CvStatus  result = *_result;
    int i, j, code = TRS_OK;
    char *elem4, *elem5;
    CvGraphVtx *v_elem, *v_elem2, *v_elem3;
    CvGraphEdge *e_elem, *e_elem2, *e_elem3;
    CvGraphEdge **e_list;
    int idx, idx2;
    int e_count, e_count2;
    int e_count3, e_count4;
    int gr_idx, op;
    int vtx_size = sgr[0]->vtx->elem_size - 1;
    int edge_size= sgr[0]->elem_size - 1;
    int work_vtx_size = ((vtx_size + 3) & -4) + sizeof(CvGraphVtx);
    int work_edge_size = ((edge_size + 3) & -4) + sizeof(CvGraphEdge);
    int max_struct_size = sgr[0]->vtx->max_count;

    v_elem = (CvGraphVtx*)icvAlloc( work_vtx_size );
    e_elem = (CvGraphEdge*)icvAlloc( work_edge_size );
    e_list = (CvGraphEdge**)icvAlloc( max_struct_size * sizeof(e_list[0]));
    
    for( i = 0; i < iters; i++ )
    {
        atsRandSetBounds( rng_state, 0, count * max_op );

        gr_idx = atsRand32s( rng_state );
        op = gr_idx % max_op;
        gr_idx /= max_op;

        if( op == 0 ) /* clear */
        {
            if( gr[gr_idx] != 0 )
            {
                int prev_vtxs = gr[gr_idx]->total;
                int prev_edges = gr[gr_idx]->edges->total;

                clear_simple_graph( sgr[gr_idx] );
                DO_CV_ACTION( cvClearGraph, ( gr[gr_idx] ));

                CHECK_CONDITION( gr[gr_idx]->total == 0 &&
                                 gr[gr_idx]->first == 0 &&
                                 gr[gr_idx]->free_elems == 0 &&
                                 (gr[gr_idx]->free_blocks != 0 || prev_vtxs == 0),
                                 "The graph is not empty after clearing" );

                CHECK_CONDITION( gr[gr_idx]->edges->total == 0 &&
                                 gr[gr_idx]->edges->first == 0 &&
                                 gr[gr_idx]->edges->free_elems == 0 &&
                                 (gr[gr_idx]->edges->free_blocks != 0 || prev_edges == 0),
                                 "The graph is not empty after clearing" );
            }
            else
            {
                CHECK_CONDITION( sgr[gr_idx]->vtx->free_count == sgr[gr_idx]->vtx->max_count,
                                 "The graph is empty while the simple_graph is not" );
            }
        }
        else
        {
            op %= max_op_ex;

            switch( op )
            {
            case 0: /* add vertex */
                if( sgr[gr_idx]->vtx->free_count == 0  ) break;

                atsbRand8s( rng_state, (char*)(v_elem + 1), vtx_size );
                idx = add_simple_graph_vertex( sgr[gr_idx], v_elem + 1 );
    
                if( gr[gr_idx] == 0 )
                {
                    gr[gr_idx] = cvCreateGraph( CV_SEQ_KIND_GRAPH | 
                        (sgr[gr_idx]->oriented ? CV_GRAPH_FLAG_ORIENTED : 0),
                        sizeof(CvGraph), work_vtx_size, work_edge_size, storage );
                    if( !gr[gr_idx] )
                    {
                        message_string = "cvCreateGraph fails";
                        code = TRS_FAIL;
                        goto test_exit;
                    }
                }
    
                idx2 = cvGraphAddVtx( gr[gr_idx], v_elem, &v_elem2 );
                CHECK_CONDITION( idx2 >= 0, "cvGraphAddVtx fails" );

                v_elem3 = cvGetGraphVtx( gr[gr_idx], idx2 );
                CHECK_CONDITION( v_elem3,
                                "cvGraphAddVtx doesn't add the element" );

                elem4 = find_simple_graph_vertex( sgr[gr_idx], idx );

                CHECK_CONDITION( CV_IS_SET_ELEM_EXISTS( v_elem2 ) &&
                                 v_elem2->first == 0 &&
                                 v_elem2 == v_elem3 && idx == idx2 &&
                                 !memcmp( v_elem2 + 1, elem4, vtx_size),
                                 "The vertex is added to graph incorrectly" );
                break;
            case 1: /* remove vertex */
                
                idx = atsRandPlain32s( rng_state ) % MAX( sgr[gr_idx]->vtx->max_count, 1);
                elem4 = find_simple_graph_vertex( sgr[gr_idx], idx );

                if( elem4 != 0 )
                {
                    assert( gr[gr_idx] != 0 );

                    v_elem2 = cvGetGraphVtx( gr[gr_idx], idx );
                    CHECK_CONDITION( v_elem2 != 0, "Existing element is not found" );
                    assert( CV_IS_SET_ELEM_EXISTS(v_elem2) );

                    e_count = calc_simple_graph_vertex_degree( sgr[gr_idx], idx );
                    if( atsRandPlain32s( rng_state ) % 2 )
                    {
                        e_count2 = cvGraphVtxDegree( gr[gr_idx], idx );
                    }
                    else
                    {
                        CvGraphVtx* vtx = cvGetGraphVtx( gr[gr_idx], idx );
                        CHECK_CONDITION( vtx != 0, "Existing element is not found" );
                        e_count2 = cvGraphVtxDegreeByPtr( gr[gr_idx], vtx );
                    }
            
                    CHECK_CONDITION( !memcmp( v_elem2 + 1, elem4, vtx_size ) &&
                                     e_count == e_count2,
                                     "Found element is incorrect");

                    e_elem2 = v_elem2->first;
                    e_count = 0;

                    /* iteration through the edge list */
                    while( e_elem2 )
                    {
                        e_list[e_count++] = e_elem2;
                        idx2 = e_elem2->vtx[1] == v_elem2;

                        CHECK_CONDITION( idx2 == 1 || e_elem2->vtx[0] == v_elem2,
                                        "Graph edge is invalid");
                        e_elem2 = e_elem2->next[idx2];
                    }

                    remove_simple_graph_vertex( sgr[gr_idx], idx );
                    if( atsRandPlain32s( rng_state ) % 2 )
                    {
                        DO_CV_ACTION( cvGraphRemoveVtx, ( gr[gr_idx], idx ));
                    }
                    else
                    {
                        CvGraphVtx* vtx = cvGetGraphVtx( gr[gr_idx], idx );
                        CHECK_CONDITION( vtx != 0, "Existing vertex is not found" );
                        DO_CV_ACTION( cvGraphRemoveVtxByPtr, ( gr[gr_idx], vtx ));
                        
                        //////////// !!!!! HACK: write index to make the test pass !!!! ////////////
                        ((CvMemBlock*)(vtx))->next = (CvMemBlock*)(idx);
                    }

                    v_elem3 = cvGetGraphVtx( gr[gr_idx], idx );

                    CHECK_CONDITION( !v_elem3 && !CV_IS_SET_ELEM_EXISTS( v_elem2 ),
                             "Remove operation doesn't clear vertex existence flag");

                    for( j = 0; j < e_count; j++ )
                    {
                        CHECK_CONDITION( !CV_IS_SET_ELEM_EXISTS( e_list[j] ),
                             "Remove operation doesn't clear edge existence flag");
                    }
                }
                break;

            case 2: /* add edge */

                idx = atsRandPlain32s( rng_state ) % MAX( sgr[gr_idx]->vtx->max_count, 1);
                elem4 = find_simple_graph_vertex( sgr[gr_idx], idx );

                if( elem4 == 0 ) break;

                for( j = 0; j <= max_struct_size/4; j++ )
                {
                    idx2 = atsRandPlain32s( rng_state ) %
                           MAX( sgr[gr_idx]->vtx->max_count, 1);
                    elem5 = find_simple_graph_vertex( sgr[gr_idx], idx2 );
                    if( idx != idx2 && elem5 )
                    {
                        char* edge = find_simple_graph_edge( sgr[gr_idx], idx, idx2 );
                        int e_count3, e_count4;

                        if( edge ) continue;

                        v_elem2 = cvGetGraphVtx( gr[gr_idx], idx );
                        v_elem3 = cvGetGraphVtx( gr[gr_idx], idx2 );

                        CHECK_CONDITION( v_elem2 && v_elem3 &&
                                       !memcmp( v_elem2 + 1, elem4, vtx_size ) &&
                                       !memcmp( v_elem3 + 1, elem5, vtx_size ),
                                       "Existing vertex is not found" );

                        e_count3 = calc_simple_graph_vertex_degree( sgr[gr_idx], idx );
                        e_count4 = calc_simple_graph_vertex_degree( sgr[gr_idx], idx2);

                        e_count = cvGraphVtxDegree( gr[gr_idx], idx );
                        e_count2= cvGraphVtxDegree( gr[gr_idx], idx2);

                        CHECK_CONDITION( e_count == e_count3 && e_count2 == e_count4, 
                                         "Different number of edges for vertices" );
                        
                        atsbRand8s( rng_state, (char*)(e_elem + 1), edge_size );
                        
                        add_simple_graph_edge( sgr[gr_idx], idx, idx2, e_elem + 1);

                        DO_CV_ACTION( cvGraphAddEdge,
                            ( gr[gr_idx], idx, idx2, e_elem, &e_elem2 ));
                                                    
                        e_elem3 = cvFindGraphEdge( gr[gr_idx], idx, idx2 );
                        elem4 = find_simple_graph_edge( sgr[gr_idx], idx, idx2 );
                        
                        CHECK_CONDITION( e_elem3 != 0 && e_elem3 == e_elem2 &&
                                         !memcmp( e_elem2 + 1, elem4, edge_size),
                                         "Added edge is incorrect");
                        
                        assert( CV_IS_SET_ELEM_EXISTS(e_elem2) );

                        e_count3 = cvGraphVtxDegree( gr[gr_idx], idx );
                        e_count4 = cvGraphVtxDegree( gr[gr_idx], idx2);

                        CHECK_CONDITION( e_count+1 == e_count3 &&
                                         e_count2+1 == e_count4, 
                                        "Incorrect number of edges for vertex" );
                        break;
                    }
                } /* end of search loop for pair */
                break;

            case 3: /* remove edge */

                if( gr[gr_idx] == 0 ) break;

                idx = atsRandPlain32s( rng_state ) % MAX( gr[gr_idx]->total, 1);
                e_elem2 = (CvGraphEdge*)cvGetSetElem(
                                  (CvSet*)(gr[gr_idx]->edges), idx );

                if( !e_elem2 ) break;
                assert( CV_IS_SET_ELEM_EXISTS( e_elem2 ));

                v_elem2 = e_elem2->vtx[0];
                v_elem3 = e_elem2->vtx[1];

                CHECK_CONDITION( v_elem2 && v_elem3,
                                 "Existing graph edge is invalid" );

                idx = cvSeqElemIdx( (CvSeq*)gr[gr_idx], v_elem2, 0 );
                idx2= cvSeqElemIdx( (CvSeq*)gr[gr_idx], v_elem3, 0 );

                CHECK_CONDITION( idx >= 0 && idx2 >= 0,
                                 "Edge vertices are not found" );

                e_count3 = calc_simple_graph_vertex_degree( sgr[gr_idx], idx );
                e_count4 = calc_simple_graph_vertex_degree( sgr[gr_idx], idx2);

                e_count = cvGraphVtxDegree( gr[gr_idx], idx );
                e_count2= cvGraphVtxDegree( gr[gr_idx], idx2);

                CHECK_CONDITION( e_count == e_count3 && e_count2 == e_count4 &&
                                 e_count > 0 && e_count2 > 0, 
                                 "Wrong number of edges for vertices" );

                elem4 = find_simple_graph_edge( sgr[gr_idx], idx, idx2 );
                e_elem3 = cvFindGraphEdge( gr[gr_idx], idx, idx2 );

                CHECK_CONDITION( e_elem3 == e_elem2 &&
                                 !memcmp( elem4, e_elem2 + 1, edge_size ),
                                 "Found graph edge is wrong" );

                remove_simple_graph_edge( sgr[gr_idx], idx, idx2 );
                DO_CV_ACTION( cvGraphRemoveEdge, ( gr[gr_idx], idx, idx2 ));

                e_count3 = cvGraphVtxDegree( gr[gr_idx], idx );
                e_count4 = cvGraphVtxDegree( gr[gr_idx], idx2);

                e_elem3 = cvFindGraphEdge( gr[gr_idx], idx, idx2 );

                CHECK_CONDITION( e_count3 == e_count - 1 && e_count4 == e_count2 - 1 &&
                                 !e_elem3 && !CV_IS_SET_ELEM_EXISTS( e_elem2 ),
                                 "Edge is removed incorrectly" );

                break;
            default:
                assert(0);
                message_string = "Unknown error";
                code = TRS_FAIL;
                goto test_exit;
            }
        }

        if( gr[gr_idx] )
        {
            /* check edges */
            code = check_seq_block_consistence( (CvSeq*)(gr[gr_idx]->edges),
                                                gr[gr_idx]->edges->total, &message_string );
            if( code != TRS_OK ) goto test_exit;

            /* check vertices */
            code = check_seq_block_consistence( (CvSeq*)gr[gr_idx],
                                                sgr[gr_idx]->vtx->count, &message_string );
            if( code != TRS_OK ) goto test_exit;
        }
        else
        {
            CHECK_CONDITION( sgr[gr_idx]->vtx->free_count == sgr[gr_idx]->vtx->max_count,
                         "CvGraph is empty while the simple_graph is not");
        }
    }

test_exit:

    icvFree( &v_elem );
    icvFree( &e_elem );
    icvFree( &e_list );

    *msg = message_string;
    *_result = result;
    return code;
}



static int  test_graph( void )
{
    const char*  message_string = ok_message;
    int i = 0, j, k = 0, code = TRS_OK;
    CvStatus   result = CV_NO_ERR;
    simple_graph** sgr = 0;
    CvGraph** gr = 0;
    CvMemStorage* storage = 0;

    int seed = atsGetSeed();
    AtsRandState rng_state;

    read_data_struct_params();
    if( !ATS_RANGE( GRAPH_TEST, adt_l, adt_h+1 )) return TRS_UNDEF;

    atsRandInit( &rng_state, 0, 1, seed );

    sgr = (simple_graph**)icvAlloc( struct_count * sizeof(sgr[0]));
    gr = (CvGraph**)icvAlloc( struct_count * sizeof(CvGraph*));

    for( j = 0; j < struct_count; j++ )
    {
        sgr[j] = create_simple_graph( max_struct_size/20, elem_size, elem_size + 2, j & 1 );
        gr[j] = 0;
    }

    storage = cvCreateMemStorage( storage_block_size );

    for( i = 0; i < iters; i++ )
    {
        atsRandSetBounds( &rng_state, 0, max_struct_size - 10 );
        
        code = test_graph_ops( struct_count, gr, sgr, &rng_state,
                               max_struct_size*2, storage, &message_string, &result );
        if( code != TRS_OK || result < 0 ) goto test_exit;

        trsWrite( ATS_LST|ATS_CON,
            "iter = %d, storage blocks = %d\n", i, calc_storage_blocks(storage) );
    }

test_exit:

    if( result < 0 ) code = TRS_FAIL;

    if( code == TRS_OK && result >= 0 )
    {
        DO_CV_ACTION( cvReleaseMemStorage, ( &storage ));
    }
    else
    {
        cvReleaseMemStorage( &storage );
        trsWrite( ATS_LST, "seed = %08x, iter = %d, index = %d", seed, i, k );
        if( result < 0 ) trsWrite( ATS_LST, "error code: %d", result );
    }

    for( j = 0; j < struct_count; j++ )
    {
        release_simple_graph( sgr + j );
    }

    icvFree( &sgr );
    icvFree( &gr );

    return trsResult( code, message_string );
}


typedef CvPoint3D32f T;

int cmp( const void* _a, const void* _b, void* /*userdata*/ )
{
    T* a = (T*)_a;
    T* b = (T*)_b;
    return a->x < b->x || a->x == b->x && (a->y < b->y || a->y == b->y && a->z < b->z) ? -1:
           a->x > b->x || a->x == b->x && (a->y > b->y || a->y == b->y && a->z > b->z) ? 1 : 0;
}


int test_sort_invert_seq(void)
{
    int code = TRS_OK;

    const char* err_desc = "No errors";
    
    CvMemStorage* storage = cvCreateMemStorage( 2000 );
    int iters = 1000;
    int i, j;
    int seed = atsGetSeed();
    AtsRandState state;
    double sum = 0;

    atsRandInit( &state, 0, 1000, seed );

    for( i = 0; i < iters; i++ )
    {
        CvSeq* seq = cvCreateSeq( 0, sizeof(*seq), sizeof(T), storage );
        CvSeqReader reader;
        CvSeqReader reader2;
        int count = atsRandPlain32s(&state)%1000 + 1;
        CvSlice slice = cvSlice( atsRandPlain32s(&state)%(count*2) - count,
                                 atsRandPlain32s(&state)%(count*2) - count );
        CvSeq *nseq = 0, *nseq2 = 0;

        for( j = 0; j < count; j++ )
        {
            T a;
            atsbRand32f( &state, (float*)&a, sizeof(a)/sizeof(int));
            cvSeqPush( seq, &a );
        }

        nseq = icvCopySeq( seq, slice );
        nseq2 = icvCopySeq( icvSeqSlice( seq, slice ));

        double t = (double)atsGetTickCount();
        icvSeqInvert( nseq );
        sum += (double)atsGetTickCount() - t;
        
        icvSeqSort( seq, cmp, 0 );
        
        cvStartReadSeq( seq, &reader );

        char* ptr = reader.ptr;

        for( j = 1; j < count; j++ )
        {
            CV_NEXT_SEQ_ELEM( seq->elem_size, reader );

            if( cmp( ptr, reader.ptr, 0 ) > 0 )
            {
                code = TRS_FAIL;
                err_desc = "Sequence was not sorted properly";
                goto test_exit;
            }
            ptr = reader.ptr;
        }

        if( nseq->total != nseq2->total || nseq->elem_size != seq->elem_size ||
            nseq2->elem_size != seq->elem_size )
        {
            code = TRS_FAIL;
            err_desc = "SeqSlice and CopySeq( SeqSlice ) return different sequences (length and/or elem_size)";
            goto test_exit;
        }

        cvStartReadSeq( nseq, &reader );
        cvStartReadSeq( nseq2, &reader2, 1 );

        for( j = 0; j < nseq->total; j++ )
        {
            if( memcmp( reader.ptr, reader2.ptr, nseq->elem_size ) != 0 )
            {
                code = TRS_FAIL;
                err_desc = "Sequences don't match";
                goto test_exit;
            }
            CV_NEXT_SEQ_ELEM( nseq->elem_size, reader );
            CV_PREV_SEQ_ELEM( nseq->elem_size, reader2 );
        }

        cvClearMemStorage( storage ); 
    }

test_exit:
    printf("Time: %g\n", sum/1.5e9 );
    cvReleaseMemStorage( &storage );

    trsWrite( ATS_LST, "seed = %08x\n", seed );
    return trsResult( code, err_desc );
}


static int  test_seq_slice( void )
{
    CvMemStorage* storage = cvCreateMemStorage();
    int seed = atsGetSeed();
    int i, iters = 1000;
    int code = TRS_OK;
    const char* err_desc = "No errors";
    AtsRandState state;

    atsRandInit( &state, 0, 10000, seed );

    for( i = 0; i < iters; i++ )
    {
        int j, count = (atsRandPlain32s(&state) % 10000) + 1;
        CvSeq* seq = cvCreateSeq( 0, sizeof(*seq), sizeof(int), storage );
        CvSlice slice = cvSlice( atsRandPlain32s(&state)%(count),
                                 atsRandPlain32s(&state)%(count) );
        CvSeq *nseq = 0;
        CvSeqReader reader;

        for( j = 0; j < count; j++ )
        {
            cvSeqPush( seq, &j );
        }

        if( slice.startIndex > slice.endIndex )
        {
            int t;
            CV_SWAP( slice.startIndex, slice.endIndex, t );
        }

        slice.endIndex++;

        nseq = icvCopySeq( seq, slice );
        icvSeqRemoveSlice( seq, slice );

        if( seq->total != count - (slice.endIndex - slice.startIndex))
        {
            code = TRS_FAIL;
            err_desc = "Incorrect sequence length after RemoveSlice";
            goto test_exit;
        }

        icvSeqInsertSlice( seq, slice.startIndex, nseq );
        cvStartReadSeq( seq, &reader );

        for( j = 0; j < count; j++ )
        {
            int k;
            CV_READ_SEQ_ELEM( k, reader );
            if( k != j )
            {
                code = TRS_FAIL;
                err_desc = "InsertSlice after RemoveSlice didn't restores the sequence";
                goto test_exit;
            }
        }
        cvClearMemStorage( storage );
    }
test_exit:
    cvReleaseMemStorage( &storage );
    trsWrite( ATS_LST, "seed = %08x\n", seed );
    return trsResult( code, err_desc );
}


static int test_graph_search(void)
{
    int edges[][2] = {{0, 3}, {1, 2}, {1, 3}, {2, 0}, {4, 3}, {0,4}, {3,5}, {5,4}, {-1,-1}};
    int i, max_vtx = -1;
    int code = TRS_OK;

    CvMemStorage* storage = cvCreateMemStorage();
    CvGraph* graph = cvCreateGraph( CV_SEQ_KIND_GRAPH|CV_GRAPH_FLAG_ORIENTED,
                                    sizeof(CvGraph), sizeof(CvGraphVtx),
                                    sizeof(CvGraphEdge), storage );
    CvGraphScanner scanner;

    for( i = 0; edges[i][0] >= 0; i++ )
    {
        max_vtx = MAX( max_vtx, edges[i][0] );
        max_vtx = MAX( max_vtx, edges[i][1] );
    }

    for( i = 0; i <= max_vtx; i++ )
    {
        cvGraphAddVtx( graph, 0, 0 );
    }

    for( i = 0; edges[i][0] >= 0; i++ )
    {
        cvGraphAddEdge( graph, edges[i][0], edges[i][1], 0, 0 );
    }

    icvStartScanGraph( graph, &scanner, 0 );
    
    for(;;)
    {
        int code = icvNextGraphItem( &scanner );
        char* event = "";
        int a = -1, b = -1;

        switch( code )
        {
        case CV_GRAPH_VERTEX:
            event = "Vertex";
            a = cvGraphVtxIdx( graph, scanner.vtx );
            break;
        case CV_GRAPH_TREE_EDGE:
            event = "Tree Edge";
            a = cvGraphVtxIdx( graph, scanner.vtx );
            b = cvGraphVtxIdx( graph, scanner.dst );
            break;
        case CV_GRAPH_BACK_EDGE:
            event = "Back Edge";
            a = cvGraphVtxIdx( graph, scanner.vtx );
            b = cvGraphVtxIdx( graph, scanner.dst );
            break;
        case CV_GRAPH_CROSS_EDGE:
            event = "Cross Edge";
            a = cvGraphVtxIdx( graph, scanner.vtx );
            b = cvGraphVtxIdx( graph, scanner.dst );
            break;
        case CV_GRAPH_FORWARD_EDGE:
            event = "Forward Edge";
            a = cvGraphVtxIdx( graph, scanner.vtx );
            b = cvGraphVtxIdx( graph, scanner.dst );
            break;
        case CV_GRAPH_BACKTRACKING:
            event = "Backtracking";
            a = cvGraphVtxIdx( graph, scanner.vtx );
            break;
        case CV_GRAPH_NEW_TREE:
            event = "New search tree";
            break;
        case CV_GRAPH_OVER:
            event = "End of procedure";
            break;
        default:
            assert(0);
            code = TRS_FAIL;
            goto test_exit;
        }

        trsWrite( ATS_CON, "%s", event );
        
        if( a >= 0 )
        {
            if( b >= 0 )
                trsWrite( ATS_CON, ": (%2d,%2d)", a, b );
            else
                trsWrite( ATS_CON, ": %2d", a );
        }

        trsWrite( ATS_CON, "\n");

        if( code < 0 )
            break;
    }

test_exit:
    icvEndScanGraph( &scanner );
    cvReleaseMemStorage( &storage );

    return code;
}

void InitASequence(void)
{
    /* Registering test functions */
    trsReg( struct_names[0], test_desc, atsAlgoClass, test_sequence );
    trsReg( struct_names[1], test_desc, atsAlgoClass, test_set );
    trsReg( struct_names[2], test_desc, atsAlgoClass, test_graph );
    trsReg( struct_names[3], test_desc, atsAlgoClass, test_sort_invert_seq );
    trsReg( struct_names[4], test_desc, atsAlgoClass, test_seq_slice );
    trsReg( struct_names[5], test_desc, atsAlgoClass, test_graph_search );

} /* InitASequence */

/* End of file. */

