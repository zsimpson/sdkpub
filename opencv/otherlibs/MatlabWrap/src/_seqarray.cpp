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

#include "qfrontend.h"

#include "seqarray.h"

using namespace CV::FrontEnd;
using namespace CV;

void CSeqArray::createSeqArray( mxArray *&mxArr, int len )
{
	const char *fieldnames[] = { 
		"data", 
		"rect",
		"type",
		"h_prev",
		"h_next",
		"v_prev",
		"v_next"
	};

	mxArr = mxCreateStructMatrix( len, (len > 0) ? 1 : 0,
		sizeof( fieldnames ) / sizeof( fieldnames[0] ),
		fieldnames );
}

void CSeqArray::getSeq( mxArray *mxArr, int idx, CvSeq *seq, CvSeqBlock *block )
{
	idx--;
	
	int nseq = mxGetNumberOfElements( mxArr ); // number of sequences
	if( idx < 0 || idx >= nseq )
	{
		ostringstream ostr;
		ostr << "Incorrect sequence number: " << idx + 1;
		throw_error( ostr.str() );
	}

	void *data = 0;
	int total  = 0;

	CvRect rect;
	
	int type  = 0;
	int flags  = 0;

	int h_prev = 0;
	int h_next = 0;

	int v_prev = 0;
	int v_next = 0;
	
	// check all fields
	
	// data
	mxArray *mxFdata = mxGetField( mxArr, idx, "data" );
	if( !mxFdata ||
		mxGetClassID( mxFdata ) != mxUINT32_CLASS ||
		mxGetNumberOfDimensions( mxFdata ) != 2 ||
		mxGetM( mxFdata ) != 2 )
	{
		ostringstream ostr;
		ostr << "Incorrect 'data' field in sequence: " << idx + 1
			 << ". It should be [2][n] uint32 array";
		throw_error( ostr.str() );
	}
	total = mxGetN( mxFdata );
	data = mxGetData( mxFdata );

	// rect
	mxArray *mxFrect = mxGetField( mxArr, idx, "rect" );
	if( !mxFrect ||
		!mxIsNumeric( mxFrect ) ||
		mxGetNumberOfDimensions( mxFrect ) != 2 ||
		mxGetM( mxFrect ) != 1 ||
		mxGetN( mxFrect ) != 4 )
	{
		ostringstream ostr;
		ostr << "Incorrect 'rect' field in sequence: " << idx + 1
			 << ". It should be [1][4] numeric array";
		throw_error( ostr.str() );
	}
	_getSimpleType( mxFrect, 0, (int *)&rect, 4 );

	// type
	mxArray *mxFtype = mxGetField( mxArr, idx, "type" );
	
	if( !mxFtype ||
		!mxIsNumeric( mxFtype ) ||
		mxGetNumberOfDimensions( mxFtype ) != 2 ||
		mxGetM( mxFtype ) != 1 ||
		mxGetN( mxFtype ) != 1 )
	{
		ostringstream ostr;
		ostr << "Incorrect 'type' field in sequence: " << idx + 1
			 << ". It should be [1][1] numeric array";
		throw_error( ostr.str() );
	}
	_getSimpleType( mxFtype, 0, (int *)&type, 1 );
	if( type )
	{
		flags |= CV_SEQ_FLAG_HOLE;
	}
	else
	{
		flags &= ~CV_SEQ_FLAG_HOLE;
	}
	
	
	// h_prev
	mxArray *mxFh_prev = mxGetField( mxArr, idx, "h_prev" );
	if( !mxFh_prev ||
		!mxIsNumeric( mxFh_prev ) ||
		mxGetNumberOfDimensions( mxFh_prev ) != 2 ||
		mxGetM( mxFh_prev ) != 1 ||
		mxGetN( mxFh_prev ) != 1 )
	{
		ostringstream ostr;
		ostr << "Incorrect 'h_prev' field in sequence: " << idx + 1
			 << ". It should be [1][1] numeric array";
		throw_error( ostr.str() );
	}
	_getSimpleType( mxFtype, 0, (int *)&h_prev, 1 );
	if( h_prev < 0 || h_prev > nseq )
	{
		ostringstream ostr;
		ostr << "Incorrect 'h_prev' field value: " << h_prev
			 << " in sequence: " << idx + 1;
		throw_error( ostr.str() );
	}

	// h_next
	mxArray *mxFh_next = mxGetField( mxArr, idx, "h_next" );
	if( !mxFh_next ||
		!mxIsNumeric( mxFh_next ) ||
		mxGetNumberOfDimensions( mxFh_next ) != 2 ||
		mxGetM( mxFh_next ) != 1 ||
		mxGetN( mxFh_next ) != 1 )
	{
		ostringstream ostr;
		ostr << "Incorrect 'h_next' field in sequence: " << idx + 1
			 << ". It should be [1] uint32 array";
		throw_error( ostr.str() );
	}
	_getSimpleType( mxFtype, 0, (int *)&h_next, 1 );
	if( h_next < 0 || h_next > nseq )
	{
		ostringstream ostr;
		ostr << "Incorrect 'h_next' field value: " << h_next
			 << " in sequence: " << idx + 1;
		throw_error( ostr.str() );
	}

	// v_prev
	mxArray *mxFv_prev = mxGetField( mxArr, idx, "v_prev" );
	if( !mxFv_prev ||
		!mxIsNumeric( mxFv_prev ) ||
		mxGetNumberOfDimensions( mxFv_prev ) != 2 ||
		mxGetM( mxFv_prev ) != 1 ||
		mxGetN( mxFv_prev ) != 1 )
	{
		ostringstream ostr;
		ostr << "Incorrect 'v_prev' field in sequence: " << idx + 1
			 << ". It should be [1][1] numeric array";
		throw_error( ostr.str() );
	}
	_getSimpleType( mxFtype, 0, (int *)&v_prev, 1 );
	if( v_prev < 0 || v_prev > nseq )
	{
		ostringstream ostr;
		ostr << "Incorrect 'v_prev' field value: " << v_prev
			 << " in sequence: " << idx + 1;
		throw_error( ostr.str() );
	}
	
	// v_next
	mxArray *mxFv_next = mxGetField( mxArr, idx, "v_next" );
	if( !mxFv_next ||
		!mxIsNumeric( mxFv_next ) ||
		mxGetNumberOfDimensions( mxFv_next ) != 2 ||
		mxGetM( mxFv_next ) != 1 ||
		mxGetN( mxFv_next ) != 1 )
	{
		ostringstream ostr;
		ostr << "Incorrect 'v_next' field in sequence: " << idx + 1
			 << ". It should be [1][1] numeric array";
		throw_error( ostr.str() );
	}
	_getSimpleType( mxFtype, 0, (int *)&v_next, 1 );
	if( v_next < 0 || v_next > nseq )
	{
		ostringstream ostr;
		ostr << "Incorrect 'v_next' field value: " << v_next
			 << " in sequence: " << idx + 1;
		throw_error( ostr.str() );
	}
	
	flags |= CV_SEQ_CONTOUR;
	cvMakeSeqHeaderForArray( flags, sizeof( CvContour ), sizeof( CvPoint ),
		(CvArr *)data, total, seq, block );
	memcpy( (void *)&((CvContour *)seq)->rect, (void *)rect, sizeof( CvRect ) );
}

void CSeqArray::putSeq( CvSeq *seq, mxArray *mxArr, int idx )
{
	idx--;
	// data
	mxArray *mxFdata = mxCreateNumericMatrix( 2, seq->total,
		mxUINT32_CLASS, 0 );
	cvCvtSeqToArray( seq, (CvArr *)mxGetData( mxFdata ) );
	mxSetField( mxArr, idx, "data", mxFdata );

	// rect
	mxArray *mxFrect = mxCreateNumericMatrix( 1, 4,
		mxUINT32_CLASS, 0 );
	memcpy( (void *)mxGetData( mxFrect ), &((CvContour *)seq)->rect,
		4 * sizeof(unsigned int) );
	mxSetField( mxArr, idx, "rect", mxFrect );

	// type
	mxArray *mxFtype = mxCreateNumericMatrix( 1, 1,
		mxUINT32_CLASS, 0 );
	*((uint *)(mxGetData( mxFtype ))) = ( CV_IS_SEQ_HOLE( seq ) ) ? 1 : 0;
	mxSetField( mxArr, idx, "type", mxFtype );

	// h_prev, h_next, v_prev, v_next
	mxArray *mxFh_prev = mxCreateNumericMatrix( 1, 1,
		mxUINT32_CLASS, 0 );
	mxArray *mxFh_next = mxCreateNumericMatrix( 1, 1,
		mxUINT32_CLASS, 0 );
	mxArray *mxFv_prev = mxCreateNumericMatrix( 1, 1,
		mxUINT32_CLASS, 0 );
	mxArray *mxFv_next = mxCreateNumericMatrix( 1, 1,
		mxUINT32_CLASS, 0 );
	
	*((uint *)(mxGetData( mxFh_prev ))) = 0;
	*((uint *)(mxGetData( mxFh_next ))) = 0;
	*((uint *)(mxGetData( mxFv_prev ))) = 0;
	*((uint *)(mxGetData( mxFv_next ))) = 0;

	mxSetField( mxArr, idx, "h_prev", mxFh_prev );
	mxSetField( mxArr, idx, "h_next", mxFh_next );
	mxSetField( mxArr, idx, "v_prev", mxFv_prev );
	mxSetField( mxArr, idx, "v_next", mxFv_next );
}

void CSeqArray::put( mxArray *&mxArr )
{
	mxDestroyArray( mxArr );

	createSeqArray( mxArr, num );
	
	if( num < 1 || !seq )
	{
		return;
	}
	
	int iprev_contour = 0, iparent = 0; // indexes of the previous and parent
	                                    // sequences (1 based)
	int icur = 0; // current index (1 based)

	CvSeq *src_seq = seq; // starting point
  
	// walk through seq tree and put each contour into mxArr with appropriate
	//   h_prev, h_next etc.
	while( src_seq != 0 )
    {
		icur++;
		if( icur > num )
		{
			ostringstream ostr;
			ostr << "Too many sequences. May be broken links.";
			throw_error( ostr.str() );
		}
		// put src_seq into StructArray[icur]
		putSeq( src_seq, mxArr, icur );

		FIELD_DATA( mxArr, icur, "v_prev", int ) = iparent;
		FIELD_DATA( mxArr, icur, "h_prev", int ) = iprev_contour;

        if( iprev_contour )
		{
			FIELD_DATA( mxArr, iprev_contour, "h_next", int ) = icur;
		}
        else if( iparent )
		{
			FIELD_DATA( mxArr, iparent, "v_next", int ) = icur;
		}
        iprev_contour = icur;

        if( src_seq->v_next )
        {
            assert( iprev_contour != 0 );
            iparent = iprev_contour;
            iprev_contour = 0;
            src_seq = src_seq->v_next;
        }
        else
        {
            while( src_seq->h_next == 0 )
            {
                src_seq = src_seq->v_prev;
                if( src_seq == 0 )
				{
                    break;
				}
                iprev_contour = iparent;
                if( iparent )
				{
                    //iparent = parent->v_prev;
					iparent = 
						FIELD_DATA( mxArr, iparent, "v_prev", int );
				}
            }
            if( src_seq )
			{
                src_seq = src_seq->h_next;
			}
		}
    }
	if( icur < num )
	{
		mxSetM( mxArr, icur );
		mxSetN( mxArr, (icur == 0) ? 0 : 1 );
	}
}

bool CSeqArray::get( mxArray *mxArr, int first, int maxLevel, int recursive )
{	
	int nseq = 0;
	int _m = mxGetM( mxArr );
	int _n = mxGetN( mxArr );

	if( mxGetClassID( mxArr ) != mxSTRUCT_CLASS ||
		mxGetNumberOfDimensions( mxArr ) != 2 )
	{
		ostringstream ostr;
		ostr << "Incorrect input structure array.";
		throw_error( ostr.str() );
	}

	if( _m == 0 && _n == 0 )
	{
		// struct array is empty
		return( false );
	}

	if( _m < 1 || _n != 1 )
	{
		ostringstream ostr;
		ostr << "Incorrect input structure array.";
		throw_error( ostr.str() );
	}

	nseq = _m;

	if( first < 1 || first > nseq )
	{
		ostringstream ostr;
		ostr << "Incorrect 'first' parameter.";
		throw_error( ostr.str() );
	}

	createArr( nseq );

	int icur = 0; // current index (1 based)

	CvSeq *prev_contour = 0, *parent = 0;

	CvSeq *cur = 0;

	int isrc_seq = first; // starting point

	int level = 1;

	int ih_next = 0;
  
	while( isrc_seq != 0 )
    {
		icur++;
		cur = (CvSeq *)(&seqArr[icur - 1]);
		getSeq( mxArr, isrc_seq, cur, &blockArr[icur - 1] );

		if( maxLevel < 0 && !recursive )
		{
			ih_next = FIELD_DATA( mxArr, isrc_seq, "h_next", int );
			if( ih_next > 0 )
			{
				FIELD_DATA( mxArr, isrc_seq, "h_next", int ) = 0;
			}
			maxLevel = -maxLevel;
		}
		
		cur->v_prev = parent;
		cur->h_prev = prev_contour;

		cur->v_next = 0;
		cur->h_next = 0;

		if( maxLevel == 0 && !recursive )
		{
			break;
		}

        if( prev_contour )
		{
			prev_contour->h_next = cur;
		}
        else if( parent )
		{
			parent->v_next = cur;
		}
        prev_contour = cur;

        if( FIELD_DATA( mxArr, isrc_seq, "v_next", int ) &&
			( level < maxLevel || recursive ) )
        {
            assert( prev_contour != 0 );
            parent = prev_contour;
            prev_contour = 0;
            isrc_seq = FIELD_DATA( mxArr, isrc_seq, "v_next", int );
			level++;
        }
        else
        {
            while( FIELD_DATA( mxArr, isrc_seq, "h_next", int ) == 0 )
            {
                isrc_seq = FIELD_DATA( mxArr, isrc_seq, "v_prev", int );
				level--;
				if( level == 0 && !recursive )
				{
					isrc_seq = 0;
				}
                if( isrc_seq == 0 )
				{
                    break;
				}
                prev_contour = parent;
                if( parent )
				{
                    parent = parent->v_prev;
				}
            }
            if( isrc_seq )
			{
                isrc_seq = FIELD_DATA( mxArr, isrc_seq, "h_next", int );
			}
		}
    }

	if( ih_next > 0 )
	{
		FIELD_DATA( mxArr, first, "h_next", int ) = ih_next;
	}

	seq = (CvSeq *)&seqArr[0];
	num = icur;

	return( true );
}
