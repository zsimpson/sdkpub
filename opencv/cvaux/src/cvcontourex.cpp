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

//
//  Advanced operations on sequences/contours
//

#include "_cvaux.h"

#include <float.h>
#include <limits.h>

#include "_cvutils.h"
#include "_cvwrap.h"


CV_IMPL void
icvInitSeqTreeIterator( CvSeqTreeIterator* seqIterator, CvSeq* first, int maxLevel )
{
    CV_FUNCNAME("icvInitSeqTreeIterator");

    __BEGIN__;
    
    if( !seqIterator || !first )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    if( maxLevel < 0 )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    seqIterator->seq = first;
    seqIterator->level = 0;
    seqIterator->maxLevel = maxLevel;

    __END__;
}


CV_IMPL CvSeq*
icvNextSeq( CvSeqTreeIterator* seqIterator )
{
    CvSeq* prevSeq = 0;
    
    CV_FUNCNAME("icvNextSeq");

    __BEGIN__;
    
    CvSeq* seq;
    int level;

    if( !seqIterator )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    prevSeq = seq = seqIterator->seq;
    level = seqIterator->level;
    
    if( seq )
    {
        if( seq->v_next && level < seqIterator->maxLevel )
        {
            seq = seq->v_next;
            level++;
        }
        else
        {
            while( seq->h_next == 0 )
            {
                seq = seq->v_prev;
                if( --level < 0 )
                {
                    seq = 0;
                    break;
                }
            }
            if( seq )
                seq = seq->h_next;
        }
    }

    seqIterator->seq = seq;
    seqIterator->level = level;

    __END__;

    return prevSeq;
}


CV_IMPL CvSeq*
icvPrevSeq( CvSeqTreeIterator* seqIterator )
{
    CvSeq* prevSeq = 0;
    
    CV_FUNCNAME("icvPrevSeq");

    __BEGIN__;

    CvSeq* seq;
    int level;

    if( !seqIterator )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );    

    prevSeq = seq = seqIterator->seq;
    level = seqIterator->level;
    
    if( seq )
    {
        if( !seq->h_prev )
        {
            seq = seq->v_prev;
            if( --level < 0 )
                seq = 0;
        }
        else
        {
            seq = seq->h_prev;

            while( seq->v_next && level < seqIterator->maxLevel )
            {
                seq = seq->v_next;
                level++;

                while( seq->h_next )
                    seq = seq->h_next;
            }
        }
    }

    seqIterator->seq = seq;
    seqIterator->level = level;

    __END__;

    return prevSeq;
}


CV_IMPL CvSlice
icvNormalizeSlice( CvSlice slice, CvSeq* seq )
{
    int total = seq->total;

    if( slice.startIndex < 0 )
        slice.startIndex += total;
    if( slice.endIndex <= 0 )
        slice.endIndex += total;
    slice.endIndex -= slice.startIndex;
    if( slice.startIndex >= total )
        slice.startIndex -= total;
    if( slice.endIndex < 0 ) slice.endIndex += total;
    if( slice.endIndex < 0 ) slice.endIndex += total;
    if( slice.endIndex > total ) slice.endIndex = total;

    return slice;
}


CV_IMPL CvSeq*
icvSeqSlice( CvSeq* seq, CvSlice slice, CvMemStorage* storage )
{
    CvSeq* subseq = 0;
    
    CV_FUNCNAME("icvSeqSlice");

    __BEGIN__;
    
    if( !seq )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    if( !storage )
    {
        storage = seq->storage;
        if( !storage )
            CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );
    }

    {
    int size, cnt;
    CvSeqBlock* start_block = 0, *block, *prev_block;
    char* data = 0;

    slice = icvNormalizeSlice(slice, seq);

    size = seq->header_size + (slice.endIndex > 0 ? sizeof(CvSeqBlock) : 0);

    CV_CALL( data = cvGetSeqElem( seq, slice.startIndex, &start_block ));
    block = start_block;

    cnt = start_block->start_index - seq->first->start_index +
          start_block->count - slice.startIndex;

    while( cnt < slice.endIndex )
    {
        block = block->next;
        cnt += block->count;
        size += sizeof(CvSeqBlock);
    }

    // allocate sequence header and memory for all sequence blocks
    CV_CALL( subseq = cvCreateSeq( seq->flags, size, seq->elem_size, storage ));
        
    if( slice.endIndex > 0 )
    {
        subseq->total = slice.endIndex;
        subseq->header_size = seq->header_size;
        subseq->first = prev_block = block = (CvSeqBlock*)((char*)subseq + seq->header_size );

        cnt = start_block->start_index - seq->first->start_index +
              start_block->count - slice.startIndex;

        prev_block->start_index = prev_block->count = 0;

        do
        {
            cnt = MIN( cnt, slice.endIndex );
            slice.endIndex -= cnt;
            block->prev = prev_block;
            prev_block->next = block;
            block->start_index = prev_block->start_index + prev_block->count;
            block->count = cnt;
            block->data = data;
            prev_block = block;
            block++;
            start_block = start_block->next;
            cnt = start_block->count;
            data = start_block->data;
        }
        while( slice.endIndex > 0 );

        --block;
        subseq->ptr = subseq->block_max = block->data + block->count*subseq->elem_size;
        block->next = subseq->first;
        subseq->first->prev = block;
    }
    }
    
    __END__;

    return subseq;
}

// Makes a copy of a sequence or a part of the sequence. Returns pointer to new sequence.
// By default (storage == 0), the new sequence is resided in the same storage as the original one.
CV_IMPL CvSeq*
icvCopySeq( CvSeq* seq, CvSlice slice, CvMemStorage* storage )
{
    CvSeq* newseq = 0;
    
    CV_FUNCNAME("icvCopySeq");

    __BEGIN__;

    if( !seq )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    if( !storage )
    {
        storage = seq->storage;
        if( !storage )
            CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );
    }

    CV_CALL( newseq = cvCreateSeq( seq->flags, seq->header_size, seq->elem_size, storage ));
    slice = icvNormalizeSlice(slice, seq);

    if( slice.endIndex > 0 )
    {
        CvSeqBlock* block = 0;
        char* data = 0;
 
        CV_CALL( data = cvGetSeqElem( seq, slice.startIndex, &block ));

        int cnt = block->start_index - seq->first->start_index +
                  block->count - slice.startIndex;

        do
        {
            cnt = MIN( cnt, slice.endIndex );
            slice.endIndex -= cnt;

            cvSeqPushMulti( newseq, data, cnt );

            block = block->next;
            cnt = block->count;
            data = block->data;
        }
        while( slice.endIndex > 0 );
    }

    __END__;

    return newseq;
}


CV_IMPL void
icvSeqPopFrontMulti( CvSeq* seq, void* _elements, int count )
{
    char *elements = (char *)_elements;
    
    CV_FUNCNAME("icvSeqPopFrontMulti");

    __BEGIN__;

    if( !seq )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    if( count < 0 )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    while( count > 0 )
    {
        int delta = seq->first->count;

        delta = MIN( delta, count );
        assert( delta > 0 );

        seq->first->count -= delta;
        seq->total -= delta;
        count -= delta;
        seq->first->start_index += delta;
        delta *= seq->elem_size;

        if( elements )
        {
            memcpy( elements, seq->first->data, delta );
            elements += delta;
        }

        seq->first->data += delta;

        if( seq->first->count == 0 )
        {
            // emulate icvFreeSequenceBlock( seq, 1 );
            seq->first->count++;
            seq->total++;
            seq->first->start_index++;

            seq->first->data -= seq->elem_size;
            cvSeqPopFront( seq, 0 );
        }
    }

    __END__;
}


// Remove slice from the middle of the sequence
// !!! TODO !!! Implement more efficient algorithm
CV_IMPL void
icvSeqRemoveSlice( CvSeq* seq, CvSlice slice )
{
    CV_FUNCNAME("icvSeqRemoveSlice");

    __BEGIN__;

    int total;

    if( !seq )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    slice = icvNormalizeSlice( slice, seq );
    total = seq->total;

    if( (unsigned)(slice.startIndex) >= (unsigned)total )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    slice.endIndex += slice.startIndex;

    if( slice.endIndex < total )
    {
        CvSeqReader reader_to, reader_from;
        int elem_size = seq->elem_size;

        cvStartReadSeq( seq, &reader_to );
        cvStartReadSeq( seq, &reader_from );

        if( slice.startIndex > total - slice.endIndex )
        {
            int i, count = seq->total - slice.endIndex;
            cvSetSeqReaderPos( &reader_to, slice.startIndex );
            cvSetSeqReaderPos( &reader_from, slice.endIndex );

            for( i = 0; i < count; i++ )
            {
                memcpy( reader_to.ptr, reader_from.ptr, elem_size );
                CV_NEXT_SEQ_ELEM( elem_size, reader_to );
                CV_NEXT_SEQ_ELEM( elem_size, reader_from );
            }

            cvSeqPopMulti( seq, 0, slice.endIndex - slice.startIndex );
        }
        else
        {
            int i, count = slice.startIndex;
            cvSetSeqReaderPos( &reader_to, slice.endIndex );
            cvSetSeqReaderPos( &reader_from, slice.startIndex );

            for( i = 0; i < count; i++ )
            {
                CV_PREV_SEQ_ELEM( elem_size, reader_to );
                CV_PREV_SEQ_ELEM( elem_size, reader_from );

                memcpy( reader_to.ptr, reader_from.ptr, elem_size );
            }

            icvSeqPopFrontMulti( seq, 0, slice.endIndex - slice.startIndex );
        }
    }
    else
    {
        cvSeqPopMulti( seq, 0, total - slice.startIndex );
        icvSeqPopFrontMulti( seq, 0, slice.endIndex - total );
    }

    __END__;
}


// Inserts a new sequence into the middle of another sequence
// !!! TODO !!! Implement more efficient algorithm
CV_IMPL void
icvSeqInsertSlice( CvSeq* seq, int index, CvSeq* from )
{
    char* element;
    CvSeqReader reader_to, reader_from;
    int i, elem_size, total, from_total;
    
    CV_FUNCNAME("icvSeqInsertSlice");

    __BEGIN__;

    if( !seq || !from )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    if( seq->elem_size != from->elem_size )
        CV_ERROR_FROM_STATUS( CV_UNMATCHED_FORMATS_ERR );

    from_total = from->total;

    if( from_total == 0 )
        EXIT;

    total = seq->total;
    index += index < 0 ? total : 0;
    index -= index > total ? total : 0;

    if( (unsigned)index > (unsigned)total )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    element = from->first->data;
    elem_size = seq->elem_size;

    if( index < total >> 1 )
    {
        for( i = 0; i < from_total; i++ )
            cvSeqPushFront( seq, element );

        cvStartReadSeq( seq, &reader_to );
        cvStartReadSeq( seq, &reader_from );
        cvSetSeqReaderPos( &reader_from, from_total );

        for( i = 0; i < index; i++ )
        {
            memcpy( reader_to.ptr, reader_from.ptr, elem_size );
            CV_NEXT_SEQ_ELEM( elem_size, reader_to );
            CV_NEXT_SEQ_ELEM( elem_size, reader_from );
        }
    }
    else
    {
        for( i = 0; i < from_total; i++ )
            cvSeqPush( seq, element );

        cvStartReadSeq( seq, &reader_to );
        cvStartReadSeq( seq, &reader_from );
        cvSetSeqReaderPos( &reader_from, total );
        cvSetSeqReaderPos( &reader_to, seq->total );

        for( i = 0; i < total - index; i++ )
        {
            CV_PREV_SEQ_ELEM( elem_size, reader_to );
            CV_PREV_SEQ_ELEM( elem_size, reader_from );
            memcpy( reader_to.ptr, reader_from.ptr, elem_size );
        }
    }

    cvStartReadSeq( from, &reader_from );
    cvSetSeqReaderPos( &reader_to, index );

    for( i = 0; i < from_total; i++ )
    {
        memcpy( reader_to.ptr, reader_from.ptr, elem_size );
        CV_NEXT_SEQ_ELEM( elem_size, reader_to );
        CV_NEXT_SEQ_ELEM( elem_size, reader_from );
    }

    __END__;
}


#define _CV_SWAP_ELEMS(a,b)           \
{                                     \
    int k;                            \
    for( k = 0; k < elem_size; k++ )  \
    {                                 \
        char t0 = (a)[k];             \
        char t1 = (b)[k];             \
        (a)[k] = t1;                  \
        (b)[k] = t0;                  \
    }                                 \
}

// Inverts the sequence in-place - 0-th element becomes last, 1-st becomes pre-last etc.
CV_IMPL void
icvSeqInvert( CvSeq* seq )
{
    CvSeqReader left_reader, right_reader;
    int i, elem_size, count;
    
    CV_FUNCNAME("icvSeqInvert");

    __BEGIN__;

    if( !seq )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    elem_size = seq->elem_size;

    cvStartReadSeq( seq, &left_reader, 0 );
    cvStartReadSeq( seq, &right_reader, 1 );
    count = seq->total >> 1;

    for( i = 0; i < count; i++ )
    {
        _CV_SWAP_ELEMS( left_reader.ptr, right_reader.ptr );
        CV_NEXT_SEQ_ELEM( elem_size, left_reader );
        CV_PREV_SEQ_ELEM( elem_size, right_reader );
    }

    __END__;
}


// Sort the sequence using user-specified comparison function.
// Semantics is the same as in qsort function
CV_IMPL void
icvSeqSort( CvSeq* seq, int (CV_CDECL* cmp_func)(const void*,const void*,void*), void* userdata)
{
    const int bubble_level = 16;

    struct
    {
        int lb, ub;
    }
    stack[48];

    int sp = 0;

    int elem_size;
    CvSeqReader left_reader, right_reader;

    CV_FUNCNAME("icvSeqSort");

    __BEGIN__;

    if( !seq || !cmp_func )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    stack[0].lb = 0;
    stack[0].ub = seq->total - 1;

    elem_size = seq->elem_size;

    CV_CALL( cvStartReadSeq( seq, &left_reader ));
    CV_CALL( cvStartReadSeq( seq, &right_reader ));

    while( sp >= 0 )
    {
        int lb = stack[sp].lb;
        int ub = stack[sp--].ub;

        for(;;)
        {
            int diff = ub - lb;
            if( diff < bubble_level )
            {
                int i, j;
                cvSetSeqReaderPos( &left_reader, lb );

                for( i = diff; i > 0; i-- )
                {
                    int f = 0;

                    right_reader.block = left_reader.block;
                    right_reader.ptr = left_reader.ptr;
                    right_reader.block_min = left_reader.block_min;
                    right_reader.block_max = left_reader.block_max;
                    
                    for( j = 0; j < i; j++ )
                    {
                        char* ptr = right_reader.ptr;
                        CV_NEXT_SEQ_ELEM( elem_size, right_reader );
                        if( cmp_func( ptr, right_reader.ptr, userdata ) > 0 )
                        {
                            _CV_SWAP_ELEMS( ptr, right_reader.ptr );
                            f = 1;
                        }
                    }
                    if( !f ) break;
                }
                break;
            }
            else
            {
                /* select pivot and exchange with 1st element */
                int  m = lb + (diff >> 1);
                int  i = lb, j = ub + 1;
                char* pivot_ptr;

                cvSetSeqReaderPos( &left_reader, lb );
                cvSetSeqReaderPos( &right_reader, m );
                pivot_ptr = right_reader.ptr;
                cvSetSeqReaderPos( &right_reader, ub );

                /* choose median among seq[lb], seq[m], seq[ub] */
                int a = cmp_func( pivot_ptr, left_reader.ptr, userdata ) < 0;
                int b = cmp_func( pivot_ptr, right_reader.ptr, userdata ) < 0;

                if( a == b )
                {
                    b = cmp_func( left_reader.ptr, right_reader.ptr, userdata ) < 0;
                    pivot_ptr = a == b ? left_reader.ptr : right_reader.ptr;
                }

                if( pivot_ptr != left_reader.ptr )
                {
                    _CV_SWAP_ELEMS( left_reader.ptr, pivot_ptr );
                    pivot_ptr = left_reader.ptr;
                }
                    
                CV_NEXT_SEQ_ELEM( elem_size, left_reader );

                /* partition into two segments */
                for(;;)
                {
                    for( ; ++i < j && cmp_func( left_reader.ptr, pivot_ptr, userdata ) <= 0; )
                    {
                        CV_NEXT_SEQ_ELEM( elem_size, left_reader );
                    }

                    for( ; --j >= i && cmp_func( pivot_ptr, right_reader.ptr, userdata ) <= 0; )
                    {
                        CV_PREV_SEQ_ELEM( elem_size, right_reader );
                    }

                    if( i >= j ) break;
                    _CV_SWAP_ELEMS( left_reader.ptr, right_reader.ptr );
                    CV_NEXT_SEQ_ELEM( elem_size, left_reader );
                    CV_PREV_SEQ_ELEM( elem_size, right_reader );
                }

                /* pivot belongs in A[j] */
                _CV_SWAP_ELEMS( right_reader.ptr, pivot_ptr );

                /* keep processing smallest segment, and stack largest*/
                if( j - lb <= ub - j )
                {
                    if( j + 1 < ub )
                    {
                        stack[++sp].lb   = j + 1;
                        stack[sp].ub = ub;
                    }
                    ub = j - 1;
                }
                else
                {
                    if( j - 1 > lb)
                    {
                        stack[++sp].lb = lb;
                        stack[sp].ub = j - 1;
                    }
                    lb = j + 1;
                }
            }
        }
    }

    __END__;
}


// Gathers pointers to all the sequences, accessible from the <first>, to the single sequence.
CV_IMPL CvSeq*
icvSeqTreeToSeq( CvSeq* first, int header_size, CvMemStorage* storage )
{
    CvSeq* allseq = 0;

    CV_FUNCNAME("icvSeqTreeToSeq");

    __BEGIN__;

    CvSeqTreeIterator iterator;

    if( !storage )
    {
        storage = first->storage;
        if( !storage )
            CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );
    }

    CV_CALL( allseq = cvCreateSeq( 0, header_size, sizeof(first), storage ));

    if( first )
    {
        CV_CALL( icvInitSeqTreeIterator( &iterator, first, INT_MAX ));

        for(;;)
        {
            CvSeq* seq = icvNextSeq( &iterator );
            if( !seq )
                break;
            cvSeqPush( allseq, &seq );
        }
    }

    __END__;

    return allseq;
}


// Insert contour into tree given certain parent sequence.
// If parent is equal to frame (the most external contour),
// then added contour will have null pointer to parent.
CV_IMPL void
icvInsertContourIntoTree( CvSeq* contour, CvSeq* parent, CvSeq* frame )
{
    CV_FUNCNAME( "icvInsertContourIntoTree" );

    __BEGIN__;

    if( !contour || !parent )
        CV_ERROR_FROM_STATUS( CV_NULLPTR_ERR );

    contour->v_prev = parent != frame ? parent : 0;
    contour->h_next = parent->v_next;
    if( parent->v_next )
        parent->v_next->h_prev = contour;
    parent->v_next = contour;

    __END__;
}


// Removes contour from tree (together with the contour children).
CV_IMPL void
icvRemoveContourFromTree( CvSeq* contour, CvSeq* frame )
{
    CV_FUNCNAME( "icvRemoveContourFromTree" );

    __BEGIN__;

    if( !contour )
        CV_ERROR_FROM_CODE( CV_StsNullPtr );

    if( contour == frame )
        CV_ERROR( CV_StsBadArg, "<contour> should not be equal to <frame>" );

    if( contour->h_next )
        contour->h_next->h_prev = contour->h_prev;

    if( contour->h_prev )
        contour->h_prev->h_next = contour->h_next;
    else
    {
        CvSeq* parent = contour->v_prev;
        if( !parent )
            parent = frame;

        if( parent )
        {
            assert( parent->v_next == contour );
            parent->v_next = contour->h_next;
        }
    }

    __END__;
}


CV_IMPL void
icvWarpAffineSeq( CvSeq* seq, double matrix[3][2] )
{
    CV_FUNCNAME( "icvWarpAffineSeq" );

    __BEGIN__;

    CvSeqReader reader;
    int i, total;

    if( !seq )
        CV_ERROR_FROM_CODE( CV_StsNullPtr );

    if( !matrix )
        CV_ERROR_FROM_CODE( CV_StsNullPtr );

    total = seq->total;
    cvStartReadSeq( seq, &reader );

    for( i = 0; i < total; i++ )
    {
        CvPoint pt;
        CvPoint new_pt;

        pt = *(CvPoint*)(reader.ptr);
        new_pt.x = cvRound( pt.x*matrix[0][0] + pt.y*matrix[0][1] + matrix[0][2]);
        new_pt.y = cvRound( pt.x*matrix[1][0] + pt.y*matrix[1][1] + matrix[1][2]);

        *(CvPoint*)(reader.ptr) = new_pt;

        CV_NEXT_SEQ_ELEM( sizeof(CvPoint), reader );
    }

    __END__;
}

/* End of file. */
