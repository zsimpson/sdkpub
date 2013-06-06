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

#ifndef __CVCAMAVI_H__
#define __CVCAMAVI_H__


#include <string>
using namespace std ;


/////////////////////////////////////////////////////////////////////////////////////////
template <class T> class SafePointer
{
    protected:
        T* m_pointer;
        
    public:
        SafePointer() : m_pointer(0) {};
        SafePointer(T* pointer) {m_pointer = pointer;};
        SafePointer(const SafePointer& p) 
        {
            m_pointer = p.m_pointer;
            if(m_pointer)
            {
                m_pointer->AddRef();
            }
        };
        ~SafePointer() 
        {
            if(m_pointer) 
            {
                m_pointer->Release();
                m_pointer = NULL;
            }//if(m_pointer)
            
        };
        
        T* value() {return m_pointer;};
        T* operator ->() {return m_pointer;};
        T** operator &() 
        {
            if(m_pointer) 
            {
                m_pointer->Release();
                m_pointer = NULL;
            }//if(m_pointer)
            
            return &m_pointer;
        };
        void operator =(T* pointer) 
        {
            if(m_pointer) m_pointer->Release();
            m_pointer = pointer;
        };
        int is_valid() {return int(m_pointer);};
};
/////////////////////////////////////////////////////////////////////////////////////////
class cvcamUseCom
{
public:
    cvcamUseCom()
    {
        CoInitialize(0);
    }
    
    ~cvcamUseCom()
    {
        CoUninitialize();;
    }
};
/////////////////////////////////////////////////////////////////////////////////////////
class HrExeption
{
public:
    HRESULT hr;
    int occasion;
};
/////////////////////////////////////////////////////////////////////////////////////////
class SafeHr
{
public:
    SafeHr():
      m_occasion(0)
      {
      }
    
      HRESULT operator=(HRESULT res)
    {
        ++m_occasion;       
        
        if (FAILED(res)) 
        {
            HrExeption excpt;
            excpt.hr = res;
            excpt.occasion = m_occasion;
            throw excpt;

        }

        return res;
    }
protected:
    int m_occasion;

};
/////////////////////////////////////////////////////////////////////////////////////////

class cvcamSourceFile
{
public:
	HRESULT WaitForCompletion();
				
	HRESULT SetWindow(const HWND window);
    cvcamSourceFile(const char* file = NULL, void (*callback)(void*) = NULL);
    
    //Media controlling methods
    HRESULT Start();
    HRESULT Stop();
    HRESULT Pause();
    HRESULT Resume();

    //Property settings
    HRESULT SetCallBack(void (*callback)(void*));
    HRESULT SetWidth(const int width);
    HRESULT SetHeight(const int height);
    bool IsRunning();
    bool IsValid;

    //Seeking methods
    HRESULT SetTimeFormat(const int format);
    HRESULT GetDuration(LONGLONG *pDuration);
    HRESULT GetCurrentPosition(LONGLONG *pCurrent);
    HRESULT SetPosition(LONGLONG *pCurrent);
        
    
    
    
    
protected:
	HWND m_hWnd;

    //Initialise/Release COM
    cvcamUseCom Iusecom;

    //DirectShow Interfaces
    SafePointer<IGraphBuilder>   m_pGraph;
    SafePointer<IMediaControl>   m_pMediaControl;
    SafePointer<IMediaEventEx>   m_pEvent;
    SafePointer<IVideoWindow>    m_pVideoWindow;
    SafePointer<IPin>            m_pPin;
    SafePointer<IBasicVideo>     m_pBasicVideo;
    SafePointer<IBaseFilter>     m_pSFilter;
    SafePointer<IProxyTransform> m_pProxyTrans;
    SafePointer<IPin>            m_pSourceOut;  
    SafePointer<IPin>            m_pProxyIn;
    SafePointer<IPin>            m_pProxyOut;
    SafePointer<IEnumPins>       m_pEnumPins;
    SafePointer<IBaseFilter>     m_pProxyBase;
    SafePointer<IMediaSeeking>   m_pMediaSeeking;

    //Data
    string m_file;
    void (*m_pcallback)(void*);
    int m_width;
    int m_height;
    SafeHr m_hr;
private:
};

/////////////////////////////////////////////////////////////////////////////////////////
#define MAX_AVIS 100
#define AVIS_START 1000
typedef unsigned int uint;
class cvcamAVIs
{
public:
    cvcamAVIs()
    {
       memset(files,0,MAX_AVIS);
    };
    
    uint AddSource( char* path, void (*callback)(void*) )
    {
        cvcamSourceFile* tmp = new cvcamSourceFile(path, callback);

        if (!tmp) 
            return -1;
        if(!tmp->IsValid)
            return -1;
        
        uint i=0;
        
        while (files[i])
            i++;
        if(i>= MAX_AVIS)
            return (uint)-1;

        files[i] = tmp;

        return i+AVIS_START;
            
        
        
    }
    bool ReleaseSource(uint source)
    {
        source -= AVIS_START;
        
        if (files[source]) 
        {
            delete files[source];
            files[source] = NULL;
            return true;
        }

        return false;
    
    }
    cvcamSourceFile* operator[](uint source)
    {
        source -= AVIS_START;

        if(source>=0 && source<MAX_AVIS)
            return files[source];
        
        return NULL;
    
    }

    ~cvcamAVIs()
    {
        for(uint i = AVIS_START; i < AVIS_START+MAX_AVIS; i++)
            ReleaseSource(i);
    }
protected:
    cvcamSourceFile* files[MAX_AVIS];
    
private:
};
/////////////////////////////////////////////////////////////////////////////////////////
extern HINSTANCE DLLhinst;


#endif //__CVCAMAVI_H__
