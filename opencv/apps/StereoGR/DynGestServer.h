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
//M*/// DynGestServer.h: interface for the CDynGestServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DYNGESTSERVER_H__8C7A165D_57D3_4AB9_B764_08E5C86DFC3B__INCLUDED_)
#define AFX_DYNGESTSERVER_H__8C7A165D_57D3_4AB9_B764_08E5C86DFC3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CV.h"
#include "cvaux.h"
#include <vector>  
#include "FindHandCtl.h"

using namespace std;

//this is definition of class which will work with dynamic gestures,
// including accumulating data, training HMMs and recognition
class CDynGesture
{
public:
	BOOL LoadFromFile( const char* filename );
	void CreateHMM();
	int GetSeqNumber();

    CvEHMM* GetHMM() { return m_hmm; } 

    CDynGesture( int num_states, int num_mix );
    virtual ~CDynGesture();
    void AddSequence( float* vectors, int seq_size, int vect_size );
	BOOL AddParams( vector<_gr_pose>& input_vect );
    void Train();
    BOOL LoadHMM(const char* filename);
    BOOL SaveHMM(const char* filename);
    void  SetName( const char* name ) { m_name = name; }
    CString GetName() { return m_name; }

	void ExtractObservations();
    
    BOOL SaveParams(const char* path);
    BOOL LoadParams(const char* path);

    BOOL LoadSequence( const char* filename );
    void DestroyHMM();


protected:
    vector< vector<gr_pose> >  m_Params;
	enum { OT_VELOCITY, OT_VELOCITY_ORIENTATION }       m_obsType;

    vector<Cv1DObsInfo*> m_Sequences;
    CvEHMM*              m_hmm;
    CString              m_name;
    int                  m_vect_size;

    void CleanSequences();


public:
	void DeleteHMM();
	CvImgObsInfo** GetSequences();
    BOOL                 m_trained;

    int m_num_states;
    int m_num_mix; 

};
    

class CDynGestServer  
{
public:
	void DeleteHMMInfo();

    void CleanAll();

    BOOL SaveGestureBase( const char *filename );
	BOOL LoadGestureBase( const char* filename );
	int RecognizeDynGesture( CDynGesture* gesture, float* likelihood );
	void TrainAllGestures();
	CDynGestServer();
	virtual ~CDynGestServer();

    int GetNumGestures() { return m_gestures.size(); }
    CDynGesture* FindGesture( const char* name );
    CDynGesture* AddGesture( const char* name );
    BOOL AddGesture( CDynGesture* new_gest );
    BOOL RemoveGesture( const char* name );
    

    CDynGesture* GetGesture( int i ) { return m_gestures[i]; }   
    void SetHMMParams( int num_state, int num_mix );



protected:
	BOOL m_fullTrained;
    vector<CDynGesture*> m_gestures;
    int m_num_states;
    int m_num_mix;

    CString m_loaded_base;
        
};

#endif // !defined(AFX_DYNGESTSERVER_H__8C7A165D_57D3_4AB9_B764_08E5C86DFC3B__INCLUDED_)
