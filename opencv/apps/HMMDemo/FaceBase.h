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
//M*/// FaceBase.h: interface for the CFaceBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACEBASE_H__76CC3F61_D0C7_4CF8_8479_84950282D632__INCLUDED_)
#define AFX_FACEBASE_H__76CC3F61_D0C7_4CF8_8479_84950282D632__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ContEHMM.h"   
#define TRAIN_ALL 1
#define TRAIN_UNTRAINED 2

class CPersonImage;
class CPerson;
class CFaceBase;
          
typedef  CList<CPersonImage*,CPersonImage*> CPersonImgList;
typedef CList<CPerson*,CPerson*> CPersonList;

class CFaceBase  
{
public:
	int RecognizeOtherBase(CFaceBase* other );
	int RecognizePerson(CImage& image, CRect roi, int* three_first );
    int RecognizeBatch(CStringList* image_list);

	void TrainAll( int flag );
	void TrainPerson( int index, bool loaded );
	CFaceBase();
	virtual ~CFaceBase();

    void     SetFileName( const CString& filename );
    const CString&  GetFileName() { return m_filename; }
    void     SetName( const CString& name );
    const CString&  GetName() { return m_basename; }
    bool     Load();
    void     Unload();
    bool     Save();
    CPerson* AddPerson( const char* name, const char* folder, bool import_data );
    void     RemovePerson( POSITION pos );
    CPersonList& GetPersonList() { return m_base; };
    void     SetImageSize( CSize size );
    CSize    GetImageSize() { return m_baseImgSize; };
    void     SetModified( bool modified = true ) { m_modified = modified; }
    bool     IsModified() { return m_modified; }
    void     Draw( int index, CImage& img, SIZE win_size, int y_pos,
                   SIZE pic_size, SIZE delta );
    CPerson* GetPerson( int index );
    CPerson* FindPersonByName( const CString& name );
    int      GetPersonIndex( CPerson* person );
    CImage&  GetTrainedImage() { return m_trained_image; }
    int      GetTrainedIndex() { return m_trained_index; }
    void     SetTrainedIndex( int index ) { m_trained_index = index; }
    void     UpdateTrainedImage();
    void     SetBaseView( CWnd* view ) { m_base_view = view; }
    CWnd*    GetBaseView() { return m_base_view; }
    void     DeleteHMMInfo();

    int  SetParams( //sampling params
                    CvSize dctSize, 
                    CvSize obsSize, 
                    CvSize delta,
                    //HMM params
                    int* states, int mix,
                    //image scaling params
                    BOOL use_width, int width,
                    BOOL use_height, int height,
                    BOOL suppress_intens,
                    BOOL leave_hmm_alive = FALSE);


    //hmm params 
    int m_stnum[32];
    int m_mixnum[128];
    
    CvSize m_delta;
    CvSize m_obsSize;
    CvSize m_dctSize;

    BOOL m_useWidth; 
    BOOL m_useHeight; 
    int m_scaleWidth; 
    int m_scaleHeight;

    BOOL m_suppress_intensity;

protected:
    CSize    m_baseImgSize;
    CString  m_filename;
    CString  m_basename;
    CPersonList m_base;
    bool     m_modified;
    int      m_trained_index;
    CImage   m_trained_image;
    CWnd*    m_base_view;

    bool     GetPersonFolder( const char* root_folder, int root_folder_len,
                              const char* person_folder, char* folder );
    void     GetPersonSubFolder( const char* folder, char* subfolder );
    void     GetRootFolder( char* root_folder, int* root_path_len );
};


class CPerson  
{
public:
	void ClearHMM();
	CContEHMM& GetHMM();
	CPerson( CFaceBase* parent );
    virtual ~CPerson();

    void     SetName( const CString& name );
    const CString& GetName() { return m_name; }
    void     SetFolder( const CString& folder );
    void     GenerateFileName( const char* base, char* filename );
    const CString& GetFolder() { return m_folder; }
    void     AddImage( const char* filename, CImage* import_image, CRect roi );
    void     RemoveImage( POSITION pos );
    void     MoveToTop( POSITION pos );
    bool     Load();
    void     Unload();
    bool     Save();
    void     LoadRest();
    void     UnloadRest();
    CPersonImgList& GetImgList() { return m_imgs; }
    void     SetModified( bool modified = true )
    {
        m_modified = modified;
        if( modified )
            m_trained = false;
    }
    bool     IsModified() { return m_modified; }
    CFaceBase*  GetParentBase() { return m_parent; }
    void     TrainHMM();
    bool     IsTrained() { return m_trained; };
    void     DeleteHMMInfo();


protected:
    CString  m_name;
    CString  m_folder;
    CPersonImgList  m_imgs;
    CContEHMM m_hmm;
    CFaceBase* m_parent;

    bool     m_trained;


    bool     m_modified;

    bool     GetPersonFullImageName( const char* root, int root_len,
                                     const char* image, char* full_image_name );
    void     ExtractPersonImageName( const char* full_image_name, char* image );
};


class CPersonImage
{
public:
    
    CPersonImage();
    virtual ~CPersonImage();
    bool     Save();
    bool     Load();
    void     Unload();
    void     SetFileName( const CString& filename );
    void     SetRoiInFile( CRect r );
    CRect    GetRoiInFile() { return m_roi_in_file; }
    const CString& GetFileName() { return m_filename; }
    void     SetModified( bool modified = true ) { m_modified = modified; }
    bool     IsModified() { return m_modified; }
    void     CalcRect( SIZE win_size, POINT pos, SIZE base_size,
                       CRect& src_rect, CRect& dst_rect );
    void     Draw( CImage& img, SIZE win_size, POINT pos, SIZE pic_size );
    CImage&  GetImage() { return m_img; }

protected:
    CString  m_filename;
    CImage   m_img;
    CRect    m_roi_in_file;
    bool     m_modified;
};

void ConvertNameToFolder( const char* name, char* folder );

#endif // !defined(AFX_FACEBASE_H__76CC3F61_D0C7_4CF8_8479_84950282D632__INCLUDED_)
