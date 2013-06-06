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
//M*/#ifndef __VEL_UTILS_H__
#define __VEL_UTILS_H__

#define BEGIN_MESSAGE_MAP(DialogName)                  \
  LRESULT CALLBACK DialogName##_DlgProc(HWND hwnd,     \
                                        UINT uMsg,     \
                                        WPARAM wParam, \
                                        LPARAM lParam){

#define END_MESSAGE_MAP \
  return FALSE; }

#define ON_MSG(message,fn) \
  if ((uMsg) == (message)) \
    return (BOOL)HANDLE_##message((hwnd), (wParam), (lParam), (fn));

#define ON_BN_CLICKED(id,fn) \
  if ((uMsg)         == WM_COMMAND && \
      HIWORD(wParam) == BN_CLICKED && \
      LOWORD(wParam) == (id)) { (fn)(); return TRUE; }

// Slider macros
#define Slider_GetLineSize(hwnd)                SendMessage(hwnd, TBM_GETLINESIZE, 0, 0l)
#define Slider_SetLineSize(hwnd,nSize)          SendMessage(hwnd, TBM_SETLINESIZE, 0, nSize)
#define Slider_GetPageSize(hwnd)                SendMessage(hwnd, TBM_GETPAGESIZE, 0, 0l)
#define Slider_SetPageSize(hwnd,nSize)          SendMessage(hwnd, TBM_SETPAGESIZE, 0, nSize)
#define Slider_GetRangeMin(hwnd)                SendMessage(hwnd, TBM_GETRANGEMIN, 0, 0l)
#define Slider_GetRangeMax(hwnd)                SendMessage(hwnd, TBM_GETRANGEMAX, 0, 0l)
#define Slider_GetRange(hwnd,pnMin,pnMax)                 \
  (*(pnMin) =  SendMessage(hwnd, TBM_GETRANGEMIN, 0, 0l), \
   *(pnMin) =  SendMessage(hwnd, TBM_GETRANGEMAX, 0, 0l))

#define Slider_SetRangeMin(hwnd,nMin,bRedraw)   SendMessage(hwnd, TBM_SETRANGEMIN, bRedraw, nMin)
#define Slider_SetRangeMax(hwnd,nMax,bRedraw)   SendMessage(hwnd, TBM_SETRANGEMAX, bRedraw, nMax)
#define Slider_SetRange(hwnd,nMin,nMax,bRedraw) SendMessage(hwnd, TBM_SETRANGE, bRedraw, MAKELONG(nMin,nMax))
#define Slider_ClearSel(hwnd,bRedraw)           SendMessage(hwnd, TBM_CLEARSEL, bRedraw, 0l)
#define Slider_GetChannelRect(hwnd,lprc)        SendMessage(hwnd, TBM_GETCHANNELRECT, 0, (LPARAM)lprc)
#define Slider_GetThumbRect(hwnd,lprc)          SendMessage(hwnd, TBM_GETTHUMBRECT, 0, (LPARAM)lprc)
#define Slider_GetPos(hwnd)                     SendMessage(hwnd, TBM_GETPOS, 0, 0l)
#define Slider_SetPos(hwnd,nPos)                SendMessage(hwnd, TBM_SETPOS, TRUE, nPos)
#define Slider_VerifyPos(hwnd)                  SendMessage(hwnd, TBM_SETPOS, FALSE, 0L)
#define Slider_ClearTics(hwnd,bRedraw)          SendMessage(hwnd, TBM_CLEARTICS, bRedraw, 0l)
#define Slider_GetNumTics(hwnd)                 SendMessage(hwnd, TBM_GETNUMTICS, 0, 0l)
#define Slider_GetTicArray(hwnd)                ((DWORD*)SendMessage(hwnd, TBM_GETPTICS, 0, 0l))
#define Slider_GetTic(hwnd,nTic)                SendMessage(hwnd, TBM_GETTIC, nTic, 0L)
#define Slider_GetTicPos(hwnd,nTic)             SendMessage(hwnd, TBM_GETTICPOS, nTic, 0L)
#define Slider_SetTic(hwnd,nTic)                SendMessage(hwnd, TBM_SETTIC, 0, nTic))
#define Slider_SetTicFreq(hwnd,nFreq)           SendMessage(hwnd, TBM_SETTICFREQ, nFreq, 0L)

// Spin macros
#define Spin_GetAccel(hwnd, nAccel,pAccel)      ((UINT) LOWORD(SendMessage(hwnd, UDM_GETACCEL, nAccel, (LPARAM)pAccel)))
#define Spin_GetBase(hwnd)                      ((UINT) LOWORD(SendMessage(hwnd, UDM_GETBASE, 0, 0l)))
#define Spin_GetBuddy(hwnd)                     ((HWND) SendMessage(hwnd, UDM_GETBUDDY, 0, 0l))
#define Spin_GetPos(hwnd)                       ((int)  SendMessage(hwnd, UDM_GETPOS, 0, 0l))
#define Spin_GetRange(hwnd)                     ((DWORD)SendMessage(hwnd, UDM_GETRANGE, 0, 0l))
#define Spin_SetAccel(hwnd,nAccel,pAccel)       SendMessage(hwnd, UDM_SETACCEL, nAccel, (LPARAM)pAccel))
#define Spin_SetBase(nBase)                     SendMessage(hwnd, UDM_SETBASE, nBase, 0L))
#define Spin_SetBuddy(hwndBuddy)                SendMessage(hwnd, UDM_SETBUDDY, hwndBuddy, 0L))
#define Spin_SetPos(hwnd, nPos)                 SendMessage(hwnd, UDM_SETPOS, 0, MAKELPARAM(nPos, 0))
#define Spin_SetRange(hwnd, nLower,nUpper)      SendMessage(hwnd, UDM_SETRANGE, 0, MAKELPARAM(nUpper, nLower))

#endif