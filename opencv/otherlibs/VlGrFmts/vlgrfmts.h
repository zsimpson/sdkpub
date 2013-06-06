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

#ifndef _VLGRFMTS_H_
#define _VLGRFMTS_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

/*
   find appropriate graphic format filter (reader)
   using first few bytes of the image file.
   Returns 0 or filter handle, which is passed to other functions
*/
DLL_API int  gr_fmt_find_filter( const char* file_name );

/* 
   read image header and return base image parameters: size and color information.
   returned color value (it is optional parameter) means:
        0 - grayscale image
        1 - color image
       -1 - image with palette
*/
DLL_API int  gr_fmt_read_header( int filter, int* width, int* height, int* color );

/*
   read image raster data (it has to be allocated by the caller).
   step means row width of the image (in bytes).
   color means desired color mode:
       0 - convert image data to grayscale
       1 - convert image data to color
*/
DLL_API int  gr_fmt_read_data( int filter, void* data, int step, int color );

/*
   Release filter. Must be called after image has been read.
*/
DLL_API int  gr_fmt_close_filter( int filter );

/*
   write raster data to file. step - row width of the image.
   color:
      0 - grayscale image is written.
          if the format doesn't support grayscale images directly
          then image with palette is written.
      1 - color image is written.
   format:
      only "bmp" (Windows Bitmap) is supported by now.
*/
DLL_API int  gr_fmt_write_image( void* data, int step, 
                                 int width, int height, int color,
                                 const char* filename, const char* format );

#ifdef __cplusplus
}
#endif


#endif/*_VLGRFMTS_H_*/

