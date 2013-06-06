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

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _SEQARRAY_H_
#define _SEQARRAY_H_

// returns mxArr[idx].fieldname (idx is 1 based)
#define FIELD_DATA( mxArr, idx, fieldname, type )\
	*(type *)(mxGetData( mxGetField( mxArr, idx - 1, fieldname ) ))

/*C/////////////////////////////////////////////////////////////////////////////
//  Name:        CSeqArray
//  Purpose:     wrapper for the set of sequences
//  Description:
//
//C*/
class CSeqArray
{
public:
	CvSeq *seq;
	CvMemStorage *storage;

	// {{ for getting sequences from MATLAB
	CvContour *seqArr;
	CvSeqBlock *blockArr;
	// }}
	
	int num; // number of sequences
	
	int headerSize; // size of seqences headers

	CSeqArray( int _headerSize = sizeof( CvContour ) ) : 
		seq( 0 ), storage( 0 ), headerSize( _headerSize ),
		num( 0 ), seqArr( 0 ), blockArr( 0 )
	{}

	~CSeqArray() { deallocate(); }

	void createStorage()
	{
		if( storage )
		{
			cvReleaseMemStorage( &storage );
			storage = 0;
		}
		storage = cvCreateMemStorage();
	}

	void createArr( int _num )
	{
		if( seqArr )
		{
			delete[] seqArr;
			seqArr = 0;
		}
		if( blockArr )
		{
			delete[] blockArr;
			blockArr = 0;
		}
		seqArr   = new CvContour[_num];
		blockArr = new CvSeqBlock[_num];
	}

	void deallocate()
	{
		if( storage )
		{
			cvReleaseMemStorage( &storage );
			storage = 0;
		}
		if( seqArr )
		{
			delete[] seqArr;
			seqArr = 0;
		}
		if( blockArr )
		{
			delete[] blockArr;
			blockArr = 0;
		}
	}

	/*F/////////////////////////////////////////////////////////////////////////
	//  Name:        get
	//  Purpose:     get sequences from MATLAB
	//  Parameters:
	//    mxArr      - input array
	//    first      - index in mxArr of start sequence (1 based)
	//    maxLevel   - same as in cvDrawContours
	//    recursive  - if 0 then maxLevel parameter is taken into acconut.
	//                 Otherwise all contours what may be accessed via links
	//                 are taken into account
	//  Returns:     true if at least one sequence was gotten
	//  Description: sequences are stored in seqArr and blockArr. Pointer to 
	//    start sequence is stored in seq. Number of obtained sequences is
	//    stored in num.
	//
	//F*/
	bool get( mxArray *mxArr, int first, int maxLevel,
			  int recursive );
	
	/*F/////////////////////////////////////////////////////////////////////////
	//  Name:        put
	//  Purpose:     put sequences into MATLAB
	//  Parameters:
	//    mxArr      - output array
	//  Returns:     none
	//  Description: put all sequences what may be accessed via links from seq
	//    into mxArr. num parameter should be initialized whith value great or 
	//    equal to number of sequences before call.
	//
	//F*/
	void put( mxArray *&mxArr ); // put into MATLAB

	operator CvSeq*()  { return(  seq ); }
	operator CvSeq**() { return( &seq ); }
	
	// create struct array
	void createSeqArray( mxArray *&mxArr, int len );
	
	// get sequence from mxArr[idx] into seq, block. idx is 1 based
	void getSeq( mxArray *mxArr, int idx, CvSeq *seq, CvSeqBlock *block );
	
	// put seqence seq into mxArr[idx]. idx is 1 based.
	void putSeq( CvSeq *seq, mxArray *mxArr, int idx );

private:
};


#endif /* _SEQARRAY_H_ */