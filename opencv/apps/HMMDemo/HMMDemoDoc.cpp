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
//M*/// HMMDemoDoc.cpp : implementation of the CHMMDemoDoc class
//

#include "stdafx.h"
#include "HMMDemo.h"
#include "InfoDialogs.h"
#include "HMMDemoDoc.h"
#include "ImageBaseView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHMMDemoDoc

IMPLEMENT_DYNCREATE(CHMMDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CHMMDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CHMMDemoDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHMMDemoDoc construction/destruction

CHMMDemoDoc::CHMMDemoDoc()
{
}

CHMMDemoDoc::~CHMMDemoDoc()
{
}

BOOL CHMMDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

    m_base.SetBaseView( GetImageBaseView() );
    m_base.SetFileName("untitled_base.txt");
    m_base.SetModified(false);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CHMMDemoDoc serialization

BOOL CHMMDemoDoc::OnOpenDocument(LPCTSTR path)
{
    bool result = false;
    
    int length = strlen( path );
    const char* tmp = path + length - 3;

    if( _stricmp(tmp,"bmp") == 0 || _stricmp(tmp,"jpg") == 0 || 
        _stricmp(tmp-1,"jpeg") == 0 )
    {
        CHMMDemoView* camera_view = GetCameraView();
        CCamera& camera = camera_view->Camera();

        if ( camera.IsRunning() ) camera.Stop();

        //load image from disk
        CImage& image = camera.GetFrame();
        image.Load( path, 1 );

        camera_view->Invalidate();
        camera_view->SetSelection(0); 
        
    }
    else if( _stricmp(tmp,"txt") == 0 )
    {   
        DeleteContents();
        SetModifiedFlag();  // dirty during de-serialize

        m_base.SetBaseView( GetImageBaseView() );

        {
            CWaitCursor wait;
            m_base.SetFileName( path );
            result = m_base.Load();
        }

        if( !result )
        {
            m_base.SetFileName("");
            AfxMessageBox("Failed to open database");
        }
        else
        {
            SetModifiedFlag(FALSE);     // start off with unmodified

            //try to read appropriate config file.
            //create cfg file name
            CString cfg_name = path;
            cfg_name.Replace( ".txt", "CFG.txt" );
            
            //reset parameters (HMM, Sampling etc.) for whole application
            CHMMDemoApp* app = (CHMMDemoApp*)AfxGetApp();
            app->LoadConfig( cfg_name, true );
        }
    }
    return  result;
}


BOOL CHMMDemoDoc::OnSaveDocument(LPCTSTR path)
{
    bool result = false;

    CWaitCursor wait;
    result = m_base.Save();

    if( !result )
    {
        AfxMessageBox("Failed to save database");
    }

    SetModifiedFlag(FALSE);     // start off with unmodified
    return  result;
}


/////////////////////////////////////////////////////////////////////////////
// CHMMDemoDoc commands

void CHMMDemoDoc::DeleteContents() 
{
    m_base.Unload();
    CDocument::DeleteContents();
}


CPerson* CHMMDemoDoc::AskPersonName()
{
    CPerson* person = 0;
    CPersonName dlg( m_base );

    if( dlg.DoModal() == IDOK )
    {
        CString name = dlg.GetPersonName();
        if( name.GetLength() != 0 )
        {
            person = m_base.FindPersonByName( name );
            if( !person )
            {
                person = m_base.AddPerson( name, 0, false );
                if( !person )
                {
                    AfxMessageBox("Can't create person folder\n");
                }
            }
        }
    }

    return person;
}

void  CHMMDemoDoc::AddObj( CImage& img, CRect roi, CStringList* otherImages )
{
    CImageBaseView* view = GetImageBaseView();

    if( view )
    {
        int new_person_index = 0;
        int index = view->GetPersonIndex();
        CPerson* person = 0;

        if( index < 0 ) // no person selected
        {
            person = AskPersonName();
            if( !person ) return;
            
            new_person_index = m_base.GetPersonIndex( person );
        }
        else
        {
            person = GetFaceBase().GetPerson(index);
            if( !person )
            {
                ASSERT( 0 );
                return;
            }
        }

        person->AddImage( 0, &img, roi );
        if( otherImages )
        {
            POSITION pos = otherImages->GetHeadPosition();
            //skip first image, bacause it have already beeb added 
            otherImages->GetNext( pos );

            while( pos )
            {
                CString path = otherImages->GetNext(pos);
                char drive[1024], dir[1024];
                _splitpath( path, drive, dir, 0, 0 );
                strcat( drive, dir );
                if( _stricmp( drive, person->GetFolder()) == 0 )
                {
                    person->AddImage( path, 0, CRect(0,0,0,0));
                }
                else
                {
                    CImage img;
                    img.Load( path, 0 );
                    person->AddImage( 0, &img, CRect(0,0,0,0));
                }
            }
        }
       
        if( index >= 0 )
            view->RefreshView();
        else
            view->SwitchMode( new_person_index, true );
    }
}

bool  CHMMDemoDoc::RemoveObj( int person_index, int active_index )
{
    bool removed = false;
    
    if( person_index >= 0 )
    {
        CPerson* person = m_base.GetPerson( person_index );
        if( person )
        {
            POSITION pos = person->GetImgList().FindIndex( active_index );
            if( pos )
            {
                int res = AfxMessageBox( "Remove image?", MB_YESNO );
                if( res == IDYES )
                {
                    person->RemoveImage( pos );
                    removed = true;
                    
                }
            }
        }
    }
    else
    {
        POSITION pos = m_base.GetPersonList().FindIndex( active_index );
        if( pos )
        {
            int res = AfxMessageBox( "Remove person from the base?\n"
                                     "(files will not be deleted physically)",
                                     MB_YESNO );
            if( res == IDYES )
            {
                m_base.RemovePerson( pos );
                removed = true;
            }
        }
    }

    return removed;
}

void CHMMDemoDoc::ChangeBaseParams()
{
    CBaseInfo dlg( m_base );

    if( dlg.DoModal() == IDOK )
    {
        m_base.SetName( dlg.GetBaseName());
        m_base.SetFileName( dlg.GetFileName());
        m_base.SetModified();
    }
}

void  CHMMDemoDoc::DeleteHMMInfo( int person_index )
{
    if( person_index >= 0 )
    {
        CPerson* person = m_base.GetPerson(person_index);
        if( person )
        {
            person->DeleteHMMInfo();
        }
    }
    else
    {
        m_base.DeleteHMMInfo();
    }
}

