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
#include "_cv.h"
#include <limits.h>
#include <string.h>
#include "_cvwrap.h"
#include "_cvdatastructs.h"

/****************************************************************************************\
*            Functions for manipulating memory storage - list of memory blocks           *
\****************************************************************************************/

void
icvInitMemStorage( CvMemStorage* storage, int block_size )
{
    CV_FUNCNAME( "icvInitMemStorage " );
    
    __BEGIN__;

    if( !storage )
        CV_ERROR( CV_StsNullPtr, "" );

    if( block_size == 0 )
        block_size = CV_STORAGE_BLOCK_SIZE;

    if( block_size < (int)sizeof(CvMemStorage)*2 )
        CV_ERROR( CV_StsBadSize, "" );

    memset( storage, 0, sizeof( *storage ));
    storage->block_size = block_size;

    __END__;
}


void
icvInitChildMemStorage( CvMemStorage* parent, CvMemStorage* storage )
{
    CV_FUNCNAME( "icvInitChildMemStorage" );

    __BEGIN__;

    if( !storage || !parent )
        CV_ERROR( CV_StsNullPtr, "" );

    CV_CALL( icvInitMemStorage( storage, parent->block_size ));
    storage->parent = parent;

    __END__;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvCreateMemStorage
//    Purpose:
//      Creates empty storage
//    Parameters:
//      block_size - size of storage blocks. If 0, it uses default value
//                   (which is ~64K) 
//    Returns:
//      created storage
//    Notes:
//F*/
CV_IMPL CvMemStorage*
cvCreateMemStorage( int block_size )
{
    CvMemStorage *storage = 0;

    CV_FUNCNAME( "cvCreateMemStorage" );

    __BEGIN__;

    CV_CALL( storage = (CvMemStorage *)cvAlloc( sizeof( CvMemStorage )));
    CV_CALL( icvInitMemStorage( storage, block_size ));

    __END__;

    if( cvGetErrStatus() < 0 )
        cvFree( (void**)&storage );

    return storage;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvCreateChildMemStorage
//    Purpose:
//      Creates empty storage. The storage uses <parent> storage as a supplier (creditor)
//      of memory blocks. When the storage is released, it returns all the borrowed blocks
//      to the parent. Parent storage must be created and initialized before its children
//      and released after all the children have been released.
//    Parameters:
//      parent - pointer to parent storage
//    Returns:
//      created storage
//    Notes:
//F*/
CV_IMPL CvMemStorage *
cvCreateChildMemStorage( CvMemStorage * parent )
{
    CvMemStorage *storage = 0;
    CV_FUNCNAME( "cvCreateChildMemStorage" );

    __BEGIN__;

    if( !parent )
        CV_ERROR( CV_StsNullPtr, "" );

    CV_CALL( storage = cvCreateMemStorage( parent->block_size ));
    storage->parent = parent;

    __END__;

    if( cvGetErrStatus() < 0 )
        cvFree( (void**)&storage );

    return storage;
}


/* release all blocks of the list */
void
icvDestroyMemStorage( CvMemStorage* storage )
{
    CV_FUNCNAME( "icvDestroyMemStorage" );

    __BEGIN__;

    int k = 0;

    CvMemBlock *block;
    CvMemBlock *dst_top = 0;

    if( !storage )
        CV_ERROR( CV_StsNullPtr, "" );

    if( storage->parent )
        dst_top = storage->parent->top;

    for( block = storage->bottom; block != 0; k++ )
    {
        CvMemBlock *temp = block;

        block = block->next;
        if( storage->parent )
        {
            if( dst_top )
            {
                temp->prev = dst_top;
                temp->next = dst_top->next;
                if( temp->next )
                    temp->next->prev = temp;
                dst_top = dst_top->next = temp;
            }
            else
            {
                dst_top = storage->parent->bottom = storage->parent->top = temp;
                temp->prev = temp->next = 0;
                storage->free_space = storage->block_size - sizeof( *temp );
            }
        }
        else
        {
            cvFree( (void**)&temp );
        }
    }

    storage->top = storage->bottom = 0;
    storage->free_space = 0;

    __END__;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvReleaseMemStorage
//    Purpose:
//      Creates empty storage
//    Context:
//    Parameters:
//      storage - pointer to pointer to released storage
//    Returns:
//      CV_OK or error code
//    Notes:
//F*/
CV_IMPL void
cvReleaseMemStorage( CvMemStorage** storage )
{
    CvMemStorage *st;
    CV_FUNCNAME( "cvReleaseMemStorage" );

    __BEGIN__;

    if( !storage )
        CV_ERROR( CV_StsNullPtr, "" );

    st = *storage;
    *storage = 0;

    if( st )
    {
        CV_CALL( icvDestroyMemStorage( st ));
        cvFree( (void**)&st );
    }

    __END__;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvClearMemStorage
//    Purpose:
//      Reset write pointer of the storage to initial state.
//      Memory is not released.
//    Context:
//    Parameters:
//      storage - pointer to the storage
//    Returns:
//      CV_OK or error code
//    Notes:
//F*/
CV_IMPL void
cvClearMemStorage( CvMemStorage * storage )
{
    CV_FUNCNAME( "cvClearMemStorage" );

    __BEGIN__;

    if( !storage )
        CV_ERROR( CV_StsNullPtr, "" );

    if( storage->parent )
    {
        icvDestroyMemStorage( storage );
    }
    else
    {
        storage->top = storage->bottom;
        storage->free_space = storage->bottom ? storage->block_size - sizeof( CvMemBlock ) : 0;
    }

    __END__;
}


/* move stack pointer to next block.
   If no blocks, allocate new one and link it to the storage */
void
icvGoNextMemBlock( CvMemStorage * storage )
{
    CV_FUNCNAME( "icvGoNextMemBlock" );
    
    __BEGIN__;
    
    if( !storage )
        CV_ERROR( CV_StsNullPtr, "" );

    if( !storage->top || !storage->top->next )
    {
        CvMemBlock *block;

        if( !(storage->parent) )
        {
            CV_CALL( block = (CvMemBlock *)cvAlloc( storage->block_size ));
        }
        else
        {
            CvMemStorage *parent = storage->parent;
            CvMemStoragePos parent_pos;

            cvSaveMemStoragePos( parent, &parent_pos );
            CV_CALL( icvGoNextMemBlock( parent ));

            block = parent->top;
            cvRestoreMemStoragePos( parent, &parent_pos );

            if( block == parent->top )  /* the single allocated block */
            {
                assert( parent->bottom == block );
                parent->top = parent->bottom = 0;
                parent->free_space = 0;
            }
            else
            {
                /* cut the block from the parent's list of blocks */
                parent->top->next = block->next;
                if( block->next )
                    block->next->prev = parent->top;
            }
        }

        /* link block */
        block->next = 0;
        block->prev = storage->top;

        if( storage->top )
            storage->top->next = block;
        else
            storage->top = storage->bottom = block;
    }

    if( storage->top->next )
        storage->top = storage->top->next;
    storage->free_space = (storage->block_size -
            (int)sizeof( CvMemBlock )) & -CV_STRUCT_ALIGN;

    __END__;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: icvSaveMemStoragePos
//    Purpose:
//      Save position of the storage pointer.
//    Context:
//    Parameters:
//      storage - pointer to the storage
//    Returns:
//      CV_OK or error code
//    Notes:
//F*/
CV_IMPL void
cvSaveMemStoragePos( CvMemStorage * storage, CvMemStoragePos * pos )
{
    CV_FUNCNAME( "cvSaveMemStoragePos" );

    __BEGIN__;

    if( !storage || !pos )
        CV_ERROR( CV_StsNullPtr, "" );

    pos->top = storage->top;
    pos->free_space = storage->free_space;

    __END__;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: icvRestoreMemStoragePos
//    Purpose:
//      Restores position of the storage pointer.
//    Context:
//    Parameters:
//      storage - pointer to the storage
//    Returns:
//      CV_OK or error code
//    Notes:
//F*/
CV_IMPL void
cvRestoreMemStoragePos( CvMemStorage * storage, CvMemStoragePos * pos )
{
    CV_FUNCNAME( "cvRestoreMemStoragePos" );

    __BEGIN__;

    if( !storage || !pos )
        CV_ERROR( CV_StsNullPtr, "" );
    if( pos->free_space > storage->block_size )
        CV_ERROR_FROM_STATUS( CV_BADSIZE_ERR );

    storage->top = pos->top;
    storage->free_space = pos->free_space;

    if( !storage->top )
    {
        storage->top = storage->bottom;
        storage->free_space = storage->top ? storage->block_size - sizeof( CvMemBlock ) : 0;
    }

    __END__;
}


/****************************************************************************************\
*                               Sequence implementation                                  *
\****************************************************************************************/

/* creates empty sequence */
CV_IMPL CvSeq *
cvCreateSeq( int seq_flags, int header_size, int elem_size, CvMemStorage * storage )
{
    CvSeq *seq = 0;

    CV_FUNCNAME( "cvCreateSeq" );

    __BEGIN__;

    if( !storage )
        CV_ERROR( CV_StsNullPtr, "" );
    if( header_size < (int)sizeof( CvSeq ) || elem_size <= 0 )
        CV_ERROR( CV_StsBadSize, "" );

    /* allocate sequence header */
    if( storage->free_space < header_size + CV_STRUCT_ALIGN)
    {
        CV_CALL( icvGoNextMemBlock( storage ));

        if( storage->free_space < header_size )
            CV_ERROR( CV_StsBadSize, "" );
    }

    seq = (CvSeq *)((char *)storage->top + storage->block_size - storage->free_space);
    seq = (CvSeq*)icvAlignPtr(seq,CV_STRUCT_ALIGN);
    storage->free_space = (storage->free_space - header_size) & -CV_STRUCT_ALIGN;

    memset( seq, 0, header_size );

    seq->header_size = header_size;
    seq->flags = seq_flags;
    seq->elem_size = elem_size;
    seq->storage = storage;

    CV_CALL( cvSetSeqBlockSize( seq, (1 << 10)/elem_size ));

    __END__;

    return seq;
}


/* adjust <delta_elems> field of sequence. It determines how much sequence
   grows if there are not free space inside the sequence buffers */
CV_IMPL void
cvSetSeqBlockSize( CvSeq *seq, int delta_elements )
{
    int elem_size;
    int useful_block_size;

    CV_FUNCNAME( "cvSetSeqBlockSize" );

    __BEGIN__;

    if( !seq || !seq->storage )
        CV_ERROR( CV_StsNullPtr, "" );
    if( delta_elements < 0 )
        CV_ERROR( CV_StsOutOfRange, "" );

    useful_block_size = seq->storage->block_size - sizeof( CvMemBlock ) - sizeof( CvSeqBlock );
    elem_size = seq->elem_size;

    if( delta_elements == 0 )
        delta_elements = (1 << 10) / elem_size;
    if( delta_elements * elem_size > useful_block_size )
    {
        delta_elements = useful_block_size / elem_size;
        if( delta_elements == 0 )
            CV_ERROR( CV_StsOutOfRange, "" );
    }

    seq->delta_elems = delta_elements;

    __END__;
}


/* find sequence element by its index */
CV_IMPL char*
cvGetSeqElem( CvSeq *seq, int index, CvSeqBlock **_block )
{
    CvSeqBlock *block;
    char *elem = 0;
    int count, total;

    CV_FUNCNAME( "cvGetSeqElem" );

    __BEGIN__;

    if( !seq )
        CV_ERROR( CV_StsNullPtr, "" );
    total = seq->total;
    index += index < 0 ? total : 0;
    index -= index >= total ? total : 0;

    if( (unsigned)index < (unsigned)total )
    {
        block = seq->first;
        while( index >= (count = block->count) )
        {
            index -= count;
            block = block->next;
        }

        if( _block )
            *_block = block;
        elem = block->data + index * seq->elem_size;
    }

    __END__;

    return elem;
}


/* calculate index of sequence element */
CV_IMPL int
cvSeqElemIdx( CvSeq *seq, void *_element, CvSeqBlock ** _block )
{
    char *element = (char *) _element;
    int elem_size;
    int id = -1;
    CvSeqBlock *first_block;
    CvSeqBlock *block;

    CV_FUNCNAME( "cvSeqElemIdx" );

    __BEGIN__;

    if( !seq || !element )
        CV_ERROR( CV_StsNullPtr, "" );

    block = first_block = seq->first;
    elem_size = seq->elem_size;

    for( ;; )
    {
        if( (unsigned) (element - block->data) < (unsigned) (block->count * elem_size) )
        {
            if( _block )
                *_block = block;
            id = (element - block->data) / elem_size +
                block->start_index - seq->first->start_index;
            break;
        }
        block = block->next;
        if( block == first_block )
            break;
    }

    __END__;

    return id;
}


/* copies all the sequence elements into single continuous array */
CV_IMPL void*
cvCvtSeqToArray( CvSeq *seq, void *array, CvSlice slice )
{
    int elem_size, total;
    CvSeqBlock *block;
    char *dstPtr = (char*)array;
    char *ptr = 0;

    CV_FUNCNAME( "cvCvtSeqToArray" );

    __BEGIN__;

    if( !seq || !array )
        CV_ERROR( CV_StsNullPtr, "" );

    elem_size = seq->elem_size;
    total = icvSliceLength( slice, seq )*elem_size;
    ptr = cvGetSeqElem( seq, slice.startIndex, &block );

    if( !ptr )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    while( total > 0 )
    {
        int count = block->data + block->count*elem_size - ptr;
        if( count > total )
            count = total;

        memcpy( dstPtr, ptr, count );
        dstPtr += count;
        total -= count;
        block = block->next;
        ptr = block->data;
    }

    __END__;

    return array;
}


/* construct sequence from array without copying any data.
   the resultant sequence can't grow above its initial size */
CV_IMPL void
cvMakeSeqHeaderForArray( int seq_type, int header_size,
                         int elem_size,
                         void *array, int total, CvSeq *seq, CvSeqBlock * block )
{
    CV_FUNCNAME( "cvMakeSeqHeaderForArray" );

    __BEGIN__;

    if( elem_size <= 0 || header_size < (int)sizeof( CvSeq ) || total < 0 )
        CV_ERROR_FROM_STATUS( CV_BADSIZE_ERR );

    if( !seq || ((!array || !block) && total > 0) )
        CV_ERROR( CV_StsNullPtr, "" );

    memset( seq, 0, header_size );

    seq->header_size = header_size;
    seq->flags = seq_type;
    seq->elem_size = elem_size;
    seq->total = total;
    seq->block_max = seq->ptr = (char *) array + total * elem_size;

    if( total > 0 )
    {
        seq->first = block;
        block->prev = block->next = block;
        block->start_index = 0;
        block->count = total;
        block->data = (char *) array;
    }

    __END__;
}


/* tries to allocate space for at least single sequence element.
   if the sequence has released blocks (seq->free_blocks != 0),
   they are used, else additional space is allocated in the storage */
static void
icvGrowSequence( CvSeq *seq, int in_front_of )
{
    CV_FUNCNAME( "icvGrowSequence" );

    __BEGIN__;

    CvSeqBlock *free_blocks;

    if( !seq )
        CV_ERROR( CV_StsNullPtr, "" );
    free_blocks = seq->free_blocks;

    if( !free_blocks )
    {
        int elem_size = seq->elem_size;
        int delta_elems = seq->delta_elems;
        CvMemStorage *storage = seq->storage;

        /* if there is a free space just after last allocated block
           and it's big enough then enlarge the last block
           (this can happen only a new block is added to the end of sequence */
        if( (unsigned) (((char *)storage->top + storage->block_size - storage->free_space)
                        - seq->block_max) < CV_STRUCT_ALIGN &&
            storage->free_space >= seq->elem_size && !in_front_of )
        {
            int delta = storage->free_space / elem_size;

            delta = MIN( delta, delta_elems ) * elem_size;
            seq->block_max += delta;
            storage->free_space = (((char*)storage->top + storage->block_size) -
                                   seq->block_max) & -CV_STRUCT_ALIGN;
            EXIT;
        }
        else
        {
            int delta = elem_size * delta_elems + sizeof( CvSeqBlock );

            /* try to allocate <delta_elements> elements */
            if( storage->free_space < delta )
            {
                int small_block_size = MAX(1, delta_elems/2)*elem_size +
                                       sizeof( CvSeqBlock );
                /* try to allocate smaller part */
                if( storage->free_space >= small_block_size )
                {
                    delta = ((storage->free_space - sizeof(CvSeqBlock))/seq->elem_size)*
                            seq->elem_size + sizeof( CvSeqBlock );
                }
                else
                {
                    CV_CALL( icvGoNextMemBlock( storage ));
                    assert( storage->free_space >= delta );
                }
            }

            free_blocks = (CvSeqBlock *) ((char *) storage->top +
                           storage->block_size - storage->free_space);
            free_blocks = (CvSeqBlock*)icvAlignPtr(free_blocks,CV_STRUCT_ALIGN);
            free_blocks->data = (char *) (free_blocks + 1);
            free_blocks->count = delta - sizeof( CvSeqBlock );
            free_blocks->prev = free_blocks->next = 0;
            storage->free_space = (storage->free_space - delta) & -CV_STRUCT_ALIGN;
        }
    }
    else
    {
        seq->free_blocks = free_blocks->next;
    }

    if( !(seq->first) )
    {
        seq->first = free_blocks;
        free_blocks->prev = free_blocks->next = free_blocks;
    }
    else
    {
        free_blocks->prev = seq->first->prev;
        free_blocks->next = seq->first;
        free_blocks->prev->next = free_blocks->next->prev = free_blocks;
    }

    /* for free blocks the <count> field means total number of bytes in the block.
       And for used blocks it means a current number of sequence
       elements in the block */
    assert( free_blocks->count % seq->elem_size == 0 && free_blocks->count > 0 );

    if( !in_front_of )
    {
        seq->ptr = free_blocks->data;
        seq->block_max = free_blocks->data + free_blocks->count;
        free_blocks->start_index = free_blocks == free_blocks->prev ? 0 :
            free_blocks->prev->start_index + free_blocks->prev->count;
    }
    else
    {
        int delta = free_blocks->count / seq->elem_size;

        free_blocks->data += free_blocks->count;

        if( free_blocks != free_blocks->prev )
        {
            assert( seq->first->start_index == 0 );
            seq->first = free_blocks;
        }
        else
        {
            seq->block_max = seq->ptr = free_blocks->data;
        }

        free_blocks->start_index = 0;

        for( ;; )
        {
            free_blocks->start_index += delta;
            free_blocks = free_blocks->next;
            if( free_blocks == seq->first )
                break;
        }
    }

    free_blocks->count = 0;

    __END__;
}


static void
icvFreeSequenceBlock( CvSeq *seq, int in_front_of )
{
    /*CV_FUNCNAME( "icvFreeSequenceBlock" );*/

    __BEGIN__;

    CvSeqBlock *block = seq->first;

    assert( (in_front_of ? block : block->prev)->count == 0 );

    if( block == block->prev )  /* single block case */
    {
        block->count = (seq->block_max - block->data) + block->start_index * seq->elem_size;
        block->data = seq->block_max - block->count;
        seq->first = 0;
        seq->ptr = seq->block_max = 0;
        seq->total = 0;
    }
    else
    {
        if( !in_front_of )
        {
            block = block->prev;
            assert( seq->ptr == block->data );

            block->count = seq->block_max - seq->ptr;
            seq->block_max = seq->ptr = block->prev->data +
                block->prev->count * seq->elem_size;
        }
        else
        {
            int delta = block->start_index;

            block->count = delta * seq->elem_size;
            block->data -= block->count;

            /* update start indices of sequence blocks */
            for( ;; )
            {
                block->start_index -= delta;
                block = block->next;
                if( block == seq->first )
                    break;
            }

            seq->first = block->next;
        }

        block->prev->next = block->next;
        block->next->prev = block->prev;
    }

    assert( block->count > 0 && block->count % seq->elem_size == 0 );
    block->next = seq->free_blocks;
    seq->free_blocks = block;

    __END__;
}


/****************************************************************************************\
*                             Sequence Writer implementation                             *
\****************************************************************************************/

/* initializes sequence writer */
CV_IMPL void
cvStartAppendToSeq( CvSeq *seq, CvSeqWriter * writer )
{
    CV_FUNCNAME( "cvStartAppendToSeq" );

    __BEGIN__;

    if( !seq || !writer )
        CV_ERROR( CV_StsNullPtr, "" );

    memset( writer, 0, sizeof( *writer ));
    writer->header_size = sizeof( CvSeqWriter );

    writer->seq = seq;
    writer->block = seq->first ? seq->first->prev : 0;
    writer->ptr = seq->ptr;
    writer->block_max = seq->block_max;

    __END__;
}


/* initializes sequence writer */
CV_IMPL void
cvStartWriteSeq( int seq_flags, int header_size,
                 int elem_size, CvMemStorage * storage, CvSeqWriter * writer )
{
    CvSeq *seq = 0;

    CV_FUNCNAME( "cvStartWriteSeq" );

    __BEGIN__;

    if( !storage || !writer )
        CV_ERROR( CV_StsNullPtr, "" );

    seq = cvCreateSeq( seq_flags, header_size, elem_size, storage );
    CV_CHECK()cvStartAppendToSeq( seq, writer );

    __END__;
}


/* updates sequence header */
CV_IMPL void
cvFlushSeqWriter( CvSeqWriter * writer )
{
    CvSeq *seq = 0;

    CV_FUNCNAME( "cvFlushSeqWriter" );

    __BEGIN__;

    if( !writer )
        CV_ERROR( CV_StsNullPtr, "" );

    seq = writer->seq;
    seq->ptr = writer->ptr;

    if( writer->block )
    {
        int total = 0;
        CvSeqBlock *first_block = writer->seq->first;
        CvSeqBlock *block = first_block;

        writer->block->count = (writer->ptr - writer->block->data) / seq->elem_size;
        assert( writer->block->count > 0 );

        do
        {
            total += block->count;
            block = block->next;
        }
        while( block != first_block );

        writer->seq->total = total;
    }

    __END__;
}


/* calls icvFlushSeqWriter and finishes writing process */
CV_IMPL CvSeq *
cvEndWriteSeq( CvSeqWriter * writer )
{
    CvSeq *seq = 0;

    CV_FUNCNAME( "cvEndWriteSeq" );

    __BEGIN__;

    if( !writer )
        CV_ERROR( CV_StsNullPtr, "" );

    cvFlushSeqWriter( writer );
    CV_CHECK()
        /* truncate the last block */
        if( writer->block )
    {
        CvSeq *seq = writer->seq;
        CvMemStorage *storage = seq->storage;
        char *storage_block_max = (char *) storage->top + storage->block_size;

        assert( writer->block->count > 0 );

        if( (unsigned) ((storage_block_max - storage->free_space)
            - seq->block_max) < CV_STRUCT_ALIGN )
        {
            storage->free_space = (storage_block_max - seq->ptr) & -4;
            seq->block_max = seq->ptr;
        }
    }

    seq = writer->seq;

    /*writer->seq = 0; */
    writer->ptr = 0;

    __END__;

    return seq;
}


/* creates new sequence block */
CV_IMPL void
cvCreateSeqBlock( CvSeqWriter * writer )
{
    CV_FUNCNAME( "cvCreateSeqBlock" );

    __BEGIN__;

    CvSeq *seq;

    if( !writer || !writer->seq )
        CV_ERROR( CV_StsNullPtr, "" );

    seq = writer->seq;

    cvFlushSeqWriter( writer );

    CV_CALL( icvGrowSequence( seq, 0 ));

    writer->block = seq->first->prev;
    writer->ptr = seq->ptr;
    writer->block_max = seq->block_max;

    __END__;
}


/****************************************************************************************\
*                               Sequence Reader implementation                           *
\****************************************************************************************/

/* initializes sequence reader */
CV_IMPL void
cvStartReadSeq( CvSeq *seq, CvSeqReader * reader, int reverse )
{
    CvSeqBlock *first_block;
    CvSeqBlock *last_block;

    CV_FUNCNAME( "cvStartReadSeq" );

    __BEGIN__;

    if( !seq || !reader )
        CV_ERROR( CV_StsNullPtr, "" );

    reader->header_size = sizeof( CvSeqReader );
    reader->seq = seq;

    first_block = seq->first;

    if( first_block )
    {
        last_block = first_block->prev;
        reader->ptr = first_block->data;
        reader->prev_elem = _CV_GET_LAST_ELEM( seq, last_block );
        reader->delta_index = seq->first->start_index;

        if( reverse )
        {
            char *temp = reader->ptr;

            reader->ptr = reader->prev_elem;
            reader->prev_elem = temp;

            reader->block = last_block;
        }
        else
        {
            reader->block = first_block;
        }

        reader->block_min = reader->block->data;
        reader->block_max = reader->block_min + reader->block->count * seq->elem_size;
    }
    else
    {
        reader->delta_index = 0;
        reader->block = 0;

        reader->ptr = reader->prev_elem = reader->block_min = reader->block_max = 0;
    }

    __END__;
}


/* change the current reading block to the previous or to the next */
CV_IMPL void
cvChangeSeqBlock( CvSeqReader * reader, int direction )
{
    CV_FUNCNAME( "cvChangeSeqBlock" );

    __BEGIN__;
    
    if( !reader )
        CV_ERROR( CV_StsNullPtr, "" );

    if( direction > 0 )
    {
        reader->block = reader->block->next;
        reader->ptr = reader->block->data;
    }
    else
    {
        reader->block = reader->block->prev;
        reader->ptr = _CV_GET_LAST_ELEM( reader->seq, reader->block );
    }
    reader->block_min = reader->block->data;
    reader->block_max = reader->block_min + reader->block->count * reader->seq->elem_size;

    __END__;
}


/* returns the current reader position */
CV_IMPL int
cvGetSeqReaderPos( CvSeqReader * reader )
{
    int elem_size;
    int index = -1;

    CV_FUNCNAME( "cvGetSeqReaderPos" );

    __BEGIN__;

    if( !reader || !reader->ptr )
        CV_ERROR( CV_StsNullPtr, "" );

    elem_size = reader->seq->elem_size;
    if( elem_size == 8 )
    {
        index = (reader->ptr - reader->block_min) >> 3;
    }
    else if( elem_size == 4 )
    {
        index = (reader->ptr - reader->block_min) >> 2;
    }
    else if( elem_size == 1 )
    {
        index = reader->ptr - reader->block_min;
    }
    else
    {
        index = (reader->ptr - reader->block_min) / elem_size;
    }

    index += reader->block->start_index - reader->delta_index;

    __END__;

    return index;
}


/* set reader position to given absolute or relative
   (relatively to the current one) position */
CV_IMPL void
cvSetSeqReaderPos( CvSeqReader * reader, int index, int is_relative )
{
    int total;
    CvSeqBlock *block;
    int idx, elem_size;

    CV_FUNCNAME( "cvSetSeqReaderPos" );

    __BEGIN__;

    if( !reader )
        CV_ERROR( CV_StsNullPtr, "" );

    total = reader->seq->total;

    if( is_relative )
        index += cvGetSeqReaderPos( reader );

    if( index < 0 )
        index += total;
    if( index >= total )
        index -= total;
    if( (unsigned) index >= (unsigned) total )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    elem_size = reader->seq->elem_size;

    block = reader->block;
    idx = index - block->start_index + reader->delta_index;

    if( (unsigned) idx < (unsigned) block->count )
    {
        reader->ptr = block->data + idx * elem_size;
    }
    else
    {
        reader->ptr = cvGetSeqElem( reader->seq, index, &block );
        assert( reader->ptr && block );

        reader->block = block;
        reader->block_min = block->data;
        reader->block_max = _CV_GET_LAST_ELEM( reader->seq, block ) + elem_size;
    }

    __END__;
}


/* pushes element to the sequence */
CV_IMPL char*
cvSeqPush( CvSeq *seq, void *element )
{
    char *ptr = 0;
    int elem_size;

    CV_FUNCNAME( "cvSeqPush" );

    __BEGIN__;

    if( !seq )
        CV_ERROR( CV_StsNullPtr, "" );

    elem_size = seq->elem_size;
    ptr = seq->ptr;

    if( ptr >= seq->block_max )
    {
        CV_CALL( icvGrowSequence( seq, 0 ));

        ptr = seq->ptr;
        assert( ptr + elem_size <= seq->block_max /*&& ptr == seq->block_min */  );
    }

    if( element )
        memcpy( ptr, element, elem_size );
    seq->first->prev->count++;
    seq->total++;
    seq->ptr = ptr + elem_size;

    __END__;

    return ptr;
}


CV_IMPL void
cvSeqPop( CvSeq *seq, void *element )
{
    char *ptr;
    int elem_size;

    CV_FUNCNAME( "cvSeqPop" );

    __BEGIN__;

    if( !seq )
        CV_ERROR( CV_StsNullPtr, "" );
    if( seq->total <= 0 )
        CV_ERROR_FROM_STATUS( CV_BADSIZE_ERR );

    elem_size = seq->elem_size;
    seq->ptr = ptr = seq->ptr - elem_size;

    if( element )
        memcpy( element, ptr, elem_size );
    seq->ptr = ptr;
    seq->total--;

    if( --(seq->first->prev->count) == 0 )
    {
        icvFreeSequenceBlock( seq, 0 );
        assert( seq->ptr == seq->block_max );
    }

    __END__;
}


/* pushes element to the front of the sequence */
CV_IMPL char*
cvSeqPushFront( CvSeq *seq, void *element )
{
    char* ptr = 0;
    int elem_size;
    CvSeqBlock *block;

    CV_FUNCNAME( "cvSeqPushFront" );

    __BEGIN__;

    if( !seq )
        CV_ERROR( CV_StsNullPtr, "" );

    elem_size = seq->elem_size;
    block = seq->first;

    if( !block || block->start_index == 0 )
    {
        CV_CALL( icvGrowSequence( seq, 1 ));

        block = seq->first;
        assert( block->start_index > 0 );
    }

    ptr = block->data -= elem_size;

    if( element )
        memcpy( ptr, element, elem_size );
    block->count++;
    block->start_index--;
    seq->total++;

    __END__;

    return ptr;
}


/* pulls out the first element of the sequence */
CV_IMPL void
cvSeqPopFront( CvSeq *seq, void *element )
{
    int elem_size;
    CvSeqBlock *block;

    CV_FUNCNAME( "cvSeqPopFront" );

    __BEGIN__;

    if( !seq )
        CV_ERROR( CV_StsNullPtr, "" );
    if( seq->total <= 0 )
        CV_ERROR_FROM_STATUS( CV_BADSIZE_ERR );

    elem_size = seq->elem_size;
    block = seq->first;

    if( element )
        memcpy( element, block->data, elem_size );
    block->data += elem_size;
    block->start_index++;
    seq->total--;

    if( --(block->count) == 0 )
    {
        icvFreeSequenceBlock( seq, 1 );
    }

    __END__;
}


CV_IMPL char*
cvSeqInsert( CvSeq *seq, int before_index, void *element )
{
    int elem_size;
    int block_size;
    CvSeqBlock *block;
    int delta_index;
    int total;
    char* ret_ptr = 0;

    CV_FUNCNAME( "cvSeqInsert" );

    __BEGIN__;

    if( !seq )
        CV_ERROR( CV_StsNullPtr, "" );

    total = seq->total;
    before_index += before_index < 0 ? total : 0;
    before_index -= before_index > total ? total : 0;

    if( (unsigned)before_index > (unsigned)total )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    if( before_index == total )
    {
        CV_CALL( ret_ptr = cvSeqPush( seq, element ));
    }
    else if( before_index == 0 )
    {
        CV_CALL( ret_ptr = cvSeqPushFront( seq, element ));
    }
    else
    {
        elem_size = seq->elem_size;

        if( before_index >= total >> 1 )
        {
            char *ptr = seq->ptr + elem_size;

            if( ptr > seq->block_max )
            {
                CV_CALL( icvGrowSequence( seq, 0 ));

                ptr = seq->ptr + elem_size;
                assert( ptr <= seq->block_max );
            }

            delta_index = seq->first->start_index;
            block = seq->first->prev;
            block->count++;
            block_size = ptr - block->data;

            while( before_index < block->start_index - delta_index )
            {
                CvSeqBlock *prev_block = block->prev;

                memmove( block->data + elem_size, block->data, block_size - elem_size );
                block_size = prev_block->count * elem_size;
                memcpy( block->data, prev_block->data + block_size - elem_size, elem_size );
                block = prev_block;

                /* check that we don't fall in the infinite loop */
                assert( block != seq->first->prev );
            }

            before_index = (before_index - block->start_index + delta_index) * elem_size;
            memmove( block->data + before_index + elem_size, block->data + before_index,
                     block_size - before_index - elem_size );

            ret_ptr = block->data + before_index;

            if( element )
                memcpy( ret_ptr, element, elem_size );
            seq->ptr = ptr;
        }
        else
        {
            block = seq->first;

            if( block->start_index == 0 )
            {
                CV_CALL( icvGrowSequence( seq, 1 ));

                block = seq->first;
            }

            delta_index = block->start_index;
            block->count++;
            block->start_index--;
            block->data -= elem_size;

            while( before_index > block->start_index - delta_index + block->count )
            {
                CvSeqBlock *next_block = block->next;

                block_size = block->count * elem_size;
                memmove( block->data, block->data + elem_size, block_size - elem_size );
                memcpy( block->data + block_size - elem_size, next_block->data, elem_size );
                block = next_block;
                /* check that we don't fall in the infinite loop */
                assert( block != seq->first );
            }

            before_index = (before_index - block->start_index + delta_index) * elem_size;
            memmove( block->data, block->data + elem_size, before_index - elem_size );

            ret_ptr = block->data + before_index - elem_size;

            if( element )
                memcpy( ret_ptr, element, elem_size );
        }

        seq->total = total + 1;
    }

    __END__;

    return ret_ptr;
}


CV_IMPL void
cvSeqRemove( CvSeq *seq, int index )
{
    char *ptr;
    int elem_size;
    int block_size;
    CvSeqBlock *block;
    int delta_index;
    int total, front = 0;

    CV_FUNCNAME( "cvSeqRemove" );

    __BEGIN__;

    if( !seq )
        CV_ERROR( CV_StsNullPtr, "" );

    total = seq->total;

    index += index < 0 ? total : 0;
    index -= index >= total ? total : 0;

    if( (unsigned) index >= (unsigned) total )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );
    if( index == total - 1 )
    {
        cvSeqPop( seq, 0 );
    CV_CHECK()}
    else if( index == 0 )
    {
        cvSeqPopFront( seq, 0 );
    CV_CHECK()}
    else
    {
        block = seq->first;
        elem_size = seq->elem_size;
        delta_index = block->start_index;
        while( block->start_index - delta_index + block->count <= index )
        {
            block = block->next;
        }

        ptr = block->data + (index - block->start_index + delta_index) * elem_size;

        front = index < total >> 1;
        if( !front )
        {
            block_size = block->count * elem_size - (ptr - block->data);

            while( block != seq->first->prev )  /* while not the last block */
            {
                CvSeqBlock *next_block = block->next;

                memmove( ptr, ptr + elem_size, block_size - elem_size );
                memcpy( ptr + block_size - elem_size, next_block->data, elem_size );
                block = next_block;
                ptr = block->data;
                block_size = block->count * elem_size;
            }

            memmove( ptr, ptr + elem_size, block_size - elem_size );
            seq->ptr -= elem_size;
        }
        else
        {
            ptr += elem_size;
            block_size = ptr - block->data;

            while( block != seq->first )
            {
                CvSeqBlock *prev_block = block->prev;

                memmove( block->data + elem_size, block->data, block_size - elem_size );
                block_size = prev_block->count * elem_size;
                memcpy( block->data, prev_block->data + block_size - elem_size, elem_size );
                block = prev_block;
            }

            memmove( block->data + elem_size, block->data, block_size - elem_size );
            block->data += elem_size;
            block->start_index++;
        }

        seq->total = total - 1;
        if( --block->count == 0 )
        {
            icvFreeSequenceBlock( seq, front );
        }
    }

    __END__;
}


CV_IMPL void
cvSeqPushMulti( CvSeq *seq, void *_elements, int count )
{
    char *elements = (char *) _elements;

    CV_FUNCNAME( "cvSeqPushMulti" );

    __BEGIN__;

    if( !seq || (!elements && count > 0) )
        CV_ERROR( CV_StsNullPtr, "" );
    if( count < 0 )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    while( count > 0 )
    {
        int delta = (seq->block_max - seq->ptr) / seq->elem_size;

        delta = MIN( delta, count );
        if( delta > 0 )
        {
            seq->first->prev->count += delta;
            seq->total += delta;
            count -= delta;
            delta *= seq->elem_size;
            memcpy( seq->ptr, elements, delta );
            seq->ptr += delta;
            elements += delta;
        }

        if( count > 0 )
        {
            CV_CALL( icvGrowSequence( seq, 0 ));
        }
    }

    __END__;
}


CV_IMPL void
cvSeqPopMulti( CvSeq *seq, void *_elements, int count )
{
    char *elements = (char *) _elements;

    CV_FUNCNAME( "cvSeqPopMulti" );

    __BEGIN__;

    if( !seq )
        CV_ERROR( CV_StsNullPtr, "" );
    if( count < 0 )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    count = MIN( count, seq->total );
    if( elements )
        elements += count * seq->elem_size;

    while( count > 0 )
    {
        int delta = seq->first->prev->count;

        delta = MIN( delta, count );
        assert( delta > 0 );

        seq->first->prev->count -= delta;
        seq->total -= delta;
        count -= delta;
        delta *= seq->elem_size;
        seq->ptr -= delta;

        if( elements )
        {
            elements -= delta;
            memcpy( elements, seq->ptr, delta );
        }

        if( seq->first->prev->count == 0 )
            icvFreeSequenceBlock( seq, 0 );
    }

    __END__;
}


CV_IMPL void
cvClearSeq( CvSeq *seq )
{
    CV_FUNCNAME( "cvClearSeq" );

    __BEGIN__;

    if( !seq )
        CV_ERROR( CV_StsNullPtr, "" );
    cvSeqPopMulti( seq, 0, seq->total );

    __END__;
}


/****************************************************************************************\
*                                      Set implementation                                *
\****************************************************************************************/

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvCreateSet
//    Purpose:
//      Creates a set (see description of CvSet structure).
//    Context:
//    Parameters:
//      set_type       - type of set
//      header_size    - size of header in bytes (not less than sizeof(CvSet))
//      elem_size      - size of sequence elements in bytes
//                       (not less than 8 bytes and divisible by 4 bytes)
//      delta_elements - amount of elements, set reserves when there is no available
//                       elements in the rest of the sequence.
//                       if this parameter is 0, function chooses it automatically
//                       (usually, such that the whole block occupies 1K)
//      storage        - where the set will be placed.
//      set            - pointer to resultant set pointer.
//    Returns:
//      CV_OK or error code
//    Notes:
//      set can be treated as a simple sequence
//      when used for reading elements. CV_IS_SET_ELEM_EXISTS macro allows to
//      check - whether the current element belongs to the set or not.
//F*/
CV_IMPL CvSet *
cvCreateSet( int set_flags, int header_size, int elem_size, CvMemStorage * storage )
{
    CvSet *set = 0;

    CV_FUNCNAME( "cvCreateSet" );

    __BEGIN__;

    if( !storage )
        CV_ERROR( CV_StsNullPtr, "" );
    if( header_size < (int)sizeof( CvSet ) ||
        elem_size < (int)sizeof(void*)*2 ||
        (elem_size & (sizeof(void*)-1)) != 0 )
        CV_ERROR_FROM_STATUS( CV_BADSIZE_ERR );

    set = (CvSet *) cvCreateSeq( set_flags, header_size, elem_size, storage );

    __END__;

    return set;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvSetAdd
//    Purpose:
//      Adds new element to the set
//    Context:
//    Parameters:
//      set     - pointer to set
//      element - which is inserted into the set
//                (i.e. its content is copied into the set (except the first field)).
//                if <element> pointer is 0 then the new element is only allocated
//                but not initialized.
//      inserted_element - if not 0, the pointer to inserted element is returned
//                         via the parameter
//    Returns:
//      index of inserted element, negative number else.
//    Notes:
//F*/
CV_IMPL int
cvSetAdd( CvSet * set, CvSetElem * element, CvSetElem ** inserted_element )
{
    int elem_size, id = -1;
    CvMemBlock *free_elems;

    CV_FUNCNAME( "cvSetAdd" );

    __BEGIN__;

    if( !set )
        CV_ERROR( CV_StsNullPtr, "" );
    elem_size = set->elem_size;

    if( !(set->free_elems) )
    {
        int count = set->total;
        char *ptr;
        CV_CALL( icvGrowSequence( (CvSeq *) set, 0 ));

        set->free_elems = (CvMemBlock *) (ptr = set->ptr);
        for( ; ptr + elem_size <= set->block_max; ptr += elem_size )
        {
            /* set lowest bit of set elements to 1. This indicates free element */
            ((CvMemBlock *) ptr)->prev = (CvMemBlock *) (ptr + elem_size + 1);
            ((CvMemBlock *) ptr)->next = (CvMemBlock *) (count++);
        }
        ((CvMemBlock *) (ptr - elem_size))->prev = (CvMemBlock *) 1;
    }

    free_elems = set->free_elems;
    set->free_elems = (CvMemBlock *)((long)free_elems->prev & ~1);

    id = (int)(long)(free_elems->next);
    if( element )
    {
        memcpy( &(free_elems->next), element + 1, elem_size - sizeof( *element ));
    }
    free_elems->prev = 0;

    if( id >= set->total )
    {
        CvSeqBlock *last_block = set->first->prev;

        set->total = id + 1;
        assert( set->first->start_index == 0 && last_block->start_index <= id );
        last_block->count = id - last_block->start_index + 1;
        set->ptr = ((char *) free_elems) + elem_size;
    }

    if( inserted_element )
        *inserted_element = (CvSetElem *) free_elems;

    __END__;

    return id;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:  cvGetSetElem
//    Purpose:
//      Finds element in the set given its index
//    Context:
//    Parameters:
//      set   - pointer to set
//      index - index of searched element
//    Returns:
//      pointer to found element or 0.
//    Notes:
//      Function returns 0 if
//        0 pointer to set is passed, or
//        index is out of range, or
//        found element is marked as free
//F*/
CV_IMPL CvSetElem *
cvGetSetElem( CvSet * set, int index )
{
    CvSetElem *elem = 0;

    CV_FUNCNAME( "cvGetSetElem" );

    __BEGIN__;

    elem = (CvSetElem *) cvGetSeqElem( (CvSeq *) set, index, 0 );
    CV_CHECK();

    if( elem && !CV_IS_SET_ELEM_EXISTS( elem ))
        elem = 0;

    __END__;

    return elem;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvRemoveFromSetByPtr
//    Purpose:
//      Removes element from the set given its address
//    Context:
//    Parameters:
//      set  - where the element is removed from
//      elem - pointer to removed element
//    Returns:
//      CV_OK or error code.
//    Notes:
//F*/
CV_IMPL void
cvSetRemove( CvSet * set, int index )
{
    CvSetElem *elem;

    CV_FUNCNAME( "cvSetRemove" );

    __BEGIN__;

    elem = cvGetSetElem( set, index );

    if( elem )
    {
        CV_REMOVE_SET_ELEM( set, index, elem );
    }
    else if( !set )
    {
        CV_ERROR( CV_StsNullPtr, "" );
    }

    __END__;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvClearSet
//    Purpose:
//      Removes all the elements from the set
//    Context:
//    Parameters:
//      set - pointer to the set
//    Returns:
//      CV_OK or error code.
//    Notes:
//F*/
CV_IMPL void
cvClearSet( CvSet * set )
{
    CV_FUNCNAME( "cvClearSet" );

    __BEGIN__;

    cvClearSeq( (CvSeq *) set );
    CV_CHECK();

    set->free_elems = 0;

    __END__;
}


/****************************************************************************************\
*                                 Graph  implementation                                  *
\****************************************************************************************/

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:  cvCreateGraph
//    Purpose:
//      Creates a graph
//    Context:
//    Parameters:
//      graph_type     - type of the created graph
//      header_size    - size of header in bytes (not less than sizeof(CvGraph))
//      vtx_size       - size of graph vertices in bytes.
//      edge_size      - size of graph edges in bytes
//      storage        - where the graph will be placed.
//      graph          - pointer to resultant graph pointer.
//    Returns:
//      CV_OK or error code
//    Notes:
//F*/
CV_IMPL CvGraph *
cvCreateGraph( int graph_type, int header_size,
               int vtx_size, int edge_size, CvMemStorage * storage )
{
    CvGraph *graph = 0;
    CvSet *temp_graph = 0;
    CvSet *edges = 0;

    CV_FUNCNAME( "cvCleateGraph" );

    __BEGIN__;

    if( header_size < (int)sizeof( CvGraph ) ||
        edge_size < (int)sizeof( CvGraphEdge ) ||
        vtx_size < (int)sizeof( CvGraphVtx ))
        CV_ERROR_FROM_STATUS( CV_BADSIZE_ERR );

    temp_graph = cvCreateSet( graph_type, header_size, vtx_size, storage );
    CV_CHECK();

    edges = cvCreateSet( CV_SEQ_KIND_SET | CV_SEQ_ELTYPE_GRAPH_EDGE,
                         sizeof( CvSet ), edge_size, storage );
    CV_CHECK();

    graph = (CvGraph *) temp_graph;
    graph->edges = edges;

    __END__;

    return graph;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvClearGraph
//    Purpose:
//      Removes all the vertices and edges from the graph
//    Context:
//    Parameters:
//      graph - pointer to the graph
//    Returns:
//      CV_OK or error code.
//    Notes:
//F*/
CV_IMPL void
cvClearGraph( CvGraph * graph )
{
    CV_FUNCNAME( "cvClearGraph" );

    __BEGIN__;

    if( !graph )
        CV_ERROR( CV_StsNullPtr, "" );

    cvClearSet( graph->edges );
    cvClearSet( (CvSet *) graph );

    __END__;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvGraphAddVtx
//    Purpose:
//      Adds vertex to the graph
//    Context:
//    Parameters:
//      graph  - pointer to graph
//      vertex - added vertex. If not 0, it is copied into the vertices sequence
//               (besides work fields - index and pointer to the first edge
//               (which is set to 0))
//      inserted_vertex - if not 0, pointer to inserted graph vertex is
//                        returned via the pointer
//    Returns:
//      index of inserted vertex or negative number if error
//    Notes:
//F*/
CV_IMPL int
cvGraphAddVtx( CvGraph * graph, CvGraphVtx * _vertex, CvGraphVtx ** _inserted_vertex )
{
    CvGraphVtx *vertex = 0;
    int index = -1;

    CV_FUNCNAME( "cvGraphAddVtx" );

    __BEGIN__;

    if( !graph )
        CV_ERROR( CV_StsNullPtr, "" );

    CV_CALL( index = cvSetAdd( (CvSet *) graph, (CvSetElem *) _vertex, (CvSetElem **) & vertex ));
    if( _inserted_vertex )
        *_inserted_vertex = vertex;
    vertex->first = 0;

    __END__;

    return index;
}


CV_IMPL CvGraphEdge *
cvFindGraphEdgeByPtr( CvGraph * graph, CvGraphVtx * start_vtx, CvGraphVtx * end_vtx )
{
    CvGraphEdge *edge = 0;

    CV_FUNCNAME( "cvFindGraphEdgeByPtr" );

    __BEGIN__;

    if( !graph || !start_vtx || !end_vtx )
        CV_ERROR( CV_StsNullPtr, "" );

    if( start_vtx != end_vtx )
    {
        int ofs = 0;

        edge = start_vtx->first;

        if( CV_IS_GRAPH_ORIENTED( graph ))
        {
            for( ; edge; edge = edge->next[ofs] )
            {
                ofs = start_vtx == edge->vtx[1];
                assert( ofs == 1 || start_vtx == edge->vtx[0] );
                if( ofs == 0 && edge->vtx[1] == end_vtx )
                    break;
            }
        }
        else
        {
            for( ; edge; edge = edge->next[ofs] )
            {
                ofs = start_vtx == edge->vtx[1];
                assert( ofs == 1 || start_vtx == edge->vtx[0] );
                if( edge->vtx[ofs ^ 1] == end_vtx )
                    break;
            }
        }
    }

    __END__;

    return edge;
}


CV_IMPL void
cvGraphRemoveEdgeByPtr( CvGraph * graph, CvGraphVtx * start_vtx, CvGraphVtx * end_vtx )
{
    int i;
    CvGraphVtx *vtx[2];
    CvGraphEdge *prev = 0;
    CvGraphEdge *edge = 0;

    CV_FUNCNAME( "cvGraphRemoveEdgeByPtr" );

    __BEGIN__;

    if( !graph || !start_vtx || !end_vtx )
        CV_ERROR( CV_StsNullPtr, "" );

    if( start_vtx != end_vtx )
    {
        vtx[0] = start_vtx;
        vtx[1] = end_vtx;

        if( CV_IS_GRAPH_ORIENTED( graph ))
        {
            for( i = 0; i < 2; i++ )
            {
                int ofs = 0, prev_ofs = 0;

                for( prev = 0, edge = vtx[i]->first; edge; prev_ofs = ofs, prev = edge,
                     edge = edge->next[ofs] )
                {
                    ofs = vtx[i] == edge->vtx[1];
                    assert( ofs == 1 || vtx[i] == edge->vtx[0] );
                    if( ofs == i && edge->vtx[i ^ 1] == vtx[i ^ 1] )
                        break;
                }

                if( !edge )
                    CV_ERROR_FROM_STATUS( CV_NOTFOUND_ERR );

                if( prev )
                    prev->next[prev_ofs] = edge->next[ofs];
                else
                    vtx[i]->first = edge->next[ofs];
            }
        }
        else
        {
            for( i = 0; i < 2; i++ )
            {
                int ofs = 0, prev_ofs = 0;

                for( prev = 0, edge = vtx[i]->first; edge; prev_ofs = ofs, prev = edge,
                     edge = edge->next[ofs] )
                {
                    ofs = vtx[i] == edge->vtx[1];
                    assert( ofs == 1 || vtx[i] == edge->vtx[0] );
                    if( edge->vtx[ofs ^ 1] == vtx[i ^ 1] )
                        break;
                }

                if( !edge )
                    CV_ERROR_FROM_STATUS( CV_NOTFOUND_ERR );

                if( prev )
                    prev->next[prev_ofs] = edge->next[ofs];
                else
                    vtx[i]->first = edge->next[ofs];
            }
        }

        CV_REMOVE_SET_ELEM( graph->edges, 0, edge );
    }

    __END__;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvGraphRemoveVtx
//    Purpose:
//      Removes vertex from the graph given its index
//    Context:
//    Parameters:
//      graph - pointer to graph
//      index - index of removed vertex
//    Returns:
//      CV_OK or error code
//    Notes:
//F*/
CV_IMPL void
cvGraphRemoveVtx( CvGraph * graph, int index )
{
    CvGraphVtx *vtx = 0;

    CV_FUNCNAME( "cvGraphRemoveVtx" );

    __BEGIN__;

    if( !graph )
        CV_ERROR( CV_StsNullPtr, "" );

    vtx = cvGetGraphVtx( graph, index );
    if( vtx )
    {
        for( ;; )
        {
            CvGraphEdge *edge = vtx->first;

            if( !edge )
                break;
            cvGraphRemoveEdgeByPtr( graph, edge->vtx[0], edge->vtx[1] );
        }
        CV_REMOVE_SET_ELEM( graph, index, vtx );
    }

    __END__;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvGraphRemoveVtx
//    Purpose:
//      Removes vertex from the graph given its index
//    Context:
//    Parameters:
//      graph - pointer to graph
//      index - index of removed vertex
//    Returns:
//      CV_OK or error code
//    Notes:
//F*/
CV_IMPL void
cvGraphRemoveVtxByPtr( CvGraph * graph, CvGraphVtx * vtx )
{
    CV_FUNCNAME( "cvGraphRemoveVtxByPtr" );

    __BEGIN__;

    if( !graph || !vtx )
        CV_ERROR( CV_StsNullPtr, "" );

    for( ;; )
    {
        CvGraphEdge *edge = vtx->first;

        if( !edge )
            break;
        cvGraphRemoveEdgeByPtr( graph, edge->vtx[0], edge->vtx[1] );
    }
    CV_REMOVE_SET_ELEM( graph, 0, vtx );

    __END__;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvFindGraphEdge
//    Purpose:
//      Finds edge in the graph
//    Context:
//    Parameters:
//      graph     - pointer to graph
//      start_idx - index of starting (origin) vertex
//      end_idx - index of ending (destination) vertex
//    Returns:
//      CV_OK or error code
//    Notes:
//F*/
CV_IMPL CvGraphEdge *
cvFindGraphEdge( CvGraph * graph, int start_idx, int end_idx )
{
    CvGraphEdge *edge = 0;
    CvGraphVtx *start_vtx;
    CvGraphVtx *end_vtx;

    CV_FUNCNAME( "cvFindGraphEdge" );

    __BEGIN__;

    if( !graph )
        CV_ERROR( CV_StsNullPtr, "" );

    start_vtx = cvGetGraphVtx( graph, start_idx );
    end_vtx = cvGetGraphVtx( graph, end_idx );

    edge = cvFindGraphEdgeByPtr( graph, start_vtx, end_vtx );

    __END__;

    return edge;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:  cvGraphRemoveEdge
//    Purpose:
//      Removes edge from the graph
//    Context:
//    Parameters:
//      graph     - pointer to graph
//      start_idx - index of starting (origin) vertex
//      end_idx - index of ending (destination) vertex
//    Returns:
//      CV_OK or error code
//    Notes:
//F*/
CV_IMPL void
cvGraphRemoveEdge( CvGraph * graph, int start_idx, int end_idx )
{
    CvGraphVtx *start_vtx;
    CvGraphVtx *end_vtx;

    CV_FUNCNAME( "cvGraphRemoveEdge" );

    __BEGIN__;

    if( !graph )
        CV_ERROR( CV_StsNullPtr, "" );

    start_vtx = cvGetGraphVtx( graph, start_idx );
    end_vtx = cvGetGraphVtx( graph, end_idx );

    cvGraphRemoveEdgeByPtr( graph, start_vtx, end_vtx );

    __END__;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:  cvGraphAddEdge
//    Purpose:
//      Adds edge to the graph
//    Context:
//    Parameters:
//      graph   - pointer to graph
//      start_idx - index of starting (origin) vertex
//      end_idx - index of ending (destination) vertex
//      inserted_vertex - if not 0, pointer to inserted graph edge is
//                        returned via the parameter
//    Returns:
//      index of inserted edge or negative number if error
//    Notes:
//F*/
CV_IMPL int
cvGraphAddEdgeByPtr( CvGraph * graph,
                     CvGraphVtx * start_vtx, CvGraphVtx * end_vtx,
                     CvGraphEdge * _edge, CvGraphEdge ** _inserted_edge )
{
    CvGraphVtx *vtx[2];
    CvGraphEdge *edge;
    int result = -1;
    int i;

    CV_FUNCNAME( "cvGraphAddEdgeByPtr" );

    __BEGIN__;

    vtx[0] = start_vtx;
    vtx[1] = end_vtx;

    CV_CALL( edge = cvFindGraphEdgeByPtr( graph, vtx[0], vtx[1] ));

    if( edge )
    {
        result = 0;
        EXIT;
    }

    if( start_vtx == end_vtx )
        CV_ERROR( start_vtx ? CV_StsBadArg : CV_StsNullPtr, "" );

    CV_CALL( cvSetAdd( (CvSet*)(graph->edges), 0, (CvSetElem **)&edge ));

    for( i = 0; i < 2; i++ )
    {
        edge->vtx[i] = vtx[i];
        edge->next[i] = vtx[i]->first;
        vtx[i]->first = edge;
    }

    if( _edge )
        memcpy( edge + 1, _edge + 1, graph->edges->elem_size - sizeof( *edge ));
    if( _inserted_edge )
        *_inserted_edge = edge;

    result = 1;

    __END__;

    return result;
}


CV_IMPL int
cvGraphAddEdge( CvGraph * graph,
                int start_idx, int end_idx,
                CvGraphEdge * _edge, CvGraphEdge ** _inserted_edge )
{
    CvGraphVtx *start_vtx;
    CvGraphVtx *end_vtx;
    int result = -1;

    CV_FUNCNAME( "cvGraphAddEdge" );

    __BEGIN__;

    if( !graph )
        CV_ERROR( CV_StsNullPtr, "" );

    start_vtx = cvGetGraphVtx( graph, start_idx );
    end_vtx = cvGetGraphVtx( graph, end_idx );

    result = cvGraphAddEdgeByPtr( graph, start_vtx, end_vtx, _edge, _inserted_edge );

    __END__;

    return result;
}


CV_IMPL int
cvGraphVtxDegree( CvGraph * graph, int vtx_idx )
{
    CvGraphVtx *vertex;
    CvGraphEdge *edge;
    int count = -1;

    CV_FUNCNAME( "cvGraphVtxDegree" );

    __BEGIN__;

    if( !graph )
        CV_ERROR( CV_StsNullPtr, "" );

    vertex = cvGetGraphVtx( graph, vtx_idx );
    if( !vertex )
        CV_ERROR_FROM_STATUS( CV_NOTFOUND_ERR );

    for( edge = vertex->first, count = 0; edge; )
    {
        count++;
        edge = CV_NEXT_GRAPH_EDGE( edge, vertex );
    }

    __END__;

    return count;
}


CV_IMPL int
cvGraphVtxDegreeByPtr( CvGraph * graph, CvGraphVtx * vertex )
{
    CvGraphEdge *edge;
    int count = -1;

    CV_FUNCNAME( "cvGraphVtxDegreeByPtr" );

    __BEGIN__;

    if( !graph || !vertex )
        CV_ERROR( CV_StsNullPtr, "" );

    for( edge = vertex->first, count = 0; edge; )
    {
        count++;
        edge = CV_NEXT_GRAPH_EDGE( edge, vertex );
    }

    __END__;

    return count;
}


int icvSliceLength( CvSlice slice, CvSeq* seq )
{
    int total = seq->total;
    int length;
    if( slice.startIndex < 0 )
        slice.startIndex += total;
    if( slice.endIndex <= 0 )
        slice.endIndex += total;
    length = slice.endIndex - slice.startIndex;
    if( length < 0 ) length += total;
    if( length < 0 ) length += total;
    if( length > total ) length = total;

    return length;
};


/****************************************************************************************\
*                            Singly-connected list implementation                        *
\****************************************************************************************/

/*
  Singly-connected list, based on CvSet.
*/
CvSList*
icvCreateSList( int list_flags, int header_size, int elem_size, CvMemStorage* storage )
{
    CvSList* list = 0;
    
    CV_FUNCNAME("icvCreateSList");

    __BEGIN__;

    if( header_size < (int)sizeof(CvSList) )
        CV_ERROR_FROM_STATUS( CV_BADSIZE_ERR );

    CV_CALL( list = (CvSList*)cvCreateSet( list_flags, header_size, elem_size, storage ));

    __END__;

    return list;
}


CvSListNode*
icvSListGetNode( CvSList* list, int index, CvSListNode** _prevNode )
{
    CvSListNode* node = 0;
    CvSListNode* prevNode = 0;
    
    CV_FUNCNAME("icvSListGetNode");

    __BEGIN__;

    if( _prevNode )
        *_prevNode = 0;

    if( !list )
        CV_ERROR( CV_StsNullPtr, "" );

    if( (unsigned)index >= (unsigned)(list->nodes) )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    node = list->head;

    while( index-- )
    {
        assert( node );
        prevNode = node;
        node = node->next;
    }

    __END__;

    if( _prevNode )
        *_prevNode = prevNode;
    
    return node;
}


int
icvSListGetIndex( CvSList* list, CvSListNode* node, CvSListNode** _prevNode )
{
    CvSListNode* currNode = 0;
    CvSListNode* prevNode = 0;
    int index = 0;
    
    CV_FUNCNAME("icvSListGetIndex");

    __BEGIN__;

    if( _prevNode )
        *_prevNode = 0;

    if( !list || !node )
        CV_ERROR( CV_StsNullPtr, "" );

    currNode = list->head;

    while( currNode && currNode != node )
    {
        prevNode = currNode;
        currNode = currNode->next;
        index++;
    }

    if( !currNode )
        index = -1;

    __END__;

    if( _prevNode )
        *_prevNode = prevNode;
    
    return index;
}


void icvSListRemoveAfter( CvSList* list, CvSListNode* node )
{
    CvSListNode* removedNode = 0;
    
    CV_FUNCNAME("icvSListRemoveAfter");

    __BEGIN__;

    if( !list )
        CV_ERROR( CV_StsNullPtr, "" );

    if( !node )
        node = (CvSListNode*)(&(list->head));

    removedNode = node->next;

    if( removedNode )
    {
        node->next = removedNode->next;
        CV_REMOVE_SET_ELEM( (CvSet*)list, 0, removedNode );
        list->nodes--;
    }

    __END__;
}


CvSListNode*
icvSListInsertAfter( CvSList* list, CvSListNode* node, CvSListNode* newNode )
{
    CvSListNode* addedNode = 0;
    
    CV_FUNCNAME("icvSListInsertAfter");

    __BEGIN__;

    CV_CALL( cvSetAdd( (CvSet*)list, (CvSetElem*)newNode, (CvSetElem**)&addedNode ));

    assert( list && addedNode );
    
    if( !node )
        node = (CvSListNode*)&(list->head);

    addedNode->next = node->next;
    node->next = addedNode;
    list->nodes++;

    __END__;

    return node;
}


void
icvClearSList( CvSList* list )
{
    CV_FUNCNAME("icvClearSList");

    __BEGIN__;
    
    CV_CALL( cvClearSet( (CvSet*)list ));

    list->head = 0;
    list->nodes = 0;

    __END__;
}


/****************************************************************************************\
*                            Doubly-connected list implementation                        *
\****************************************************************************************/

/*
  Doubly-connected list, based on CvSet.
*/


CvList*
icvCreateList( int list_flags, int header_size, int elem_size, CvMemStorage* storage )
{
    CvList* list = 0;
    
    CV_FUNCNAME("icvCreateList");

    __BEGIN__;

    if( header_size < (int)sizeof(CvList) || elem_size < (int)sizeof(CvListNode) )
        CV_ERROR_FROM_STATUS( CV_BADSIZE_ERR );

    CV_CALL( list = (CvList*)cvCreateSet( list_flags, header_size, elem_size, storage ));

    __END__;

    return list;
}


CvListNode*
icvListGetNode( CvList* list, int index )
{
    CvListNode* node = 0;
    
    CV_FUNCNAME("icvListGetNode");

    __BEGIN__;

    if( !list )
        CV_ERROR( CV_StsNullPtr, "" );

    if( (unsigned)index >= (unsigned)(list->nodes) )
        CV_ERROR_FROM_STATUS( CV_BADRANGE_ERR );

    node = list->head;

    while( index-- )
    {
        assert( node );
        node = node->next;
    }

    __END__;
    
    return node;
}


int
icvListGetIndex( CvList* list, CvListNode* node )
{
    CvListNode* currNode = 0;
    int index = 0;
    
    CV_FUNCNAME("icvListGetIndex");

    __BEGIN__;

    if( !list || !node )
        CV_ERROR( CV_StsNullPtr, "" );

    currNode = list->head;

    while( currNode && currNode != node )
    {
        currNode = currNode->next;
        index++;
    }

    if( !currNode )
        index = -1;

    __END__;

    return index;
}


void
icvListRemoveAfter( CvList* list, CvListNode* node )
{
    CvListNode* removedNode;
    CvListNode* stubNode = node;
    
    CV_FUNCNAME("icvListRemoveAfter");

    __BEGIN__;

    if( !list )
        CV_ERROR( CV_StsNullPtr, "" );

    if( !node )
        stubNode = (CvListNode*)&(list->head);

    removedNode = stubNode->next;

    if( removedNode )
    {
        stubNode->next = removedNode->next;
        if( removedNode->next )
            removedNode->next->prev = node;
    }

    if( removedNode == list->tail )
        list->tail = node;

    list->nodes--;
    CV_REMOVE_SET_ELEM( (CvSet*)list, 0, removedNode );

    __END__;
}


void
icvListRemoveBefore( CvList* list, CvListNode* node )
{
    CvListNode* removedNode;
    CvListNode* stubNode = node;
    
    CV_FUNCNAME("icvListRemoveAfter");

    __BEGIN__;

    if( !list )
        CV_ERROR( CV_StsNullPtr, "" );

    if( !node )
        stubNode = (CvListNode*)&(list->head);

    removedNode = stubNode->prev;

    if( removedNode )
    {
        stubNode->prev = removedNode->prev;
        if( removedNode->prev )
            removedNode->prev->next = node;
    }

    if( removedNode == list->tail )
        list->tail = node;

    list->nodes--;
    CV_REMOVE_SET_ELEM( (CvSet*)list, 0, removedNode );

    __END__;
}


CvListNode*
icvListInsertAfter( CvList* list, CvListNode* node, CvListNode* newNode )
{
    CvListNode* addedNode = 0;
    CvListNode* stubNode = node;
    
    CV_FUNCNAME("icvListInsertAfter");

    __BEGIN__;

    CV_CALL( cvSetAdd( (CvSet*)list, (CvSetElem*)newNode, (CvSetElem**)&addedNode ));

    assert( list && addedNode );

    if( !node )
        stubNode = (CvListNode*)&(list->head);
    
    addedNode->next = stubNode->next;
    addedNode->prev = node;

    if( stubNode->next )
        addedNode->next->prev = addedNode;

    stubNode->next = addedNode;

    if( node == 0 )
        list->tail = addedNode;

    list->nodes++;

    __END__;

    return addedNode;
}


CvListNode*
icvListInsertBefore( CvList* list, CvListNode* node, CvListNode* newNode )
{
    CvListNode* addedNode = 0;
    CvListNode* stubNode = node;
    
    CV_FUNCNAME("icvListInsertBefore");

    __BEGIN__;

    CV_CALL( cvSetAdd( (CvSet*)list, (CvSetElem*)newNode, (CvSetElem**)&addedNode ));

    assert( list && addedNode );

    if( !node )
        stubNode = (CvListNode*)&(list->head);
    
    addedNode->prev = stubNode->prev;
    addedNode->next = node;

    if( stubNode->prev )
        addedNode->prev->next = addedNode;

    stubNode->prev = addedNode;

    if( node == 0 )
        list->head = addedNode;

    list->nodes++;

    __END__;

    return addedNode;
}


void
icvClearList( CvList* list )
{
    CV_FUNCNAME("icvClearList");

    __BEGIN__;

    CV_CALL( cvClearSet( (CvSet*)list ));
    list->head = list->tail = 0;
    list->nodes = 0;

    __END__;
}

/* End of file. */
