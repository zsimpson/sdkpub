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
//M*/#include <stdlib.h>
#include <varargs.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>

#include <eic.h>
#ifdef malloc /* This macros is defined in eic.h */
#undef malloc
#endif /* malloc */
#ifdef realloc
#undef realloc
#endif /* realloc */
#ifdef free
#undef free
#endif /* free */

#ifdef WIN32
#undef WIN32
#include <highgui.h>
#define WIN32
#else
#include <highgui.h>
#endif

#include "hawkwrap.h"

static jmp_buf* highgui_mark = NULL;
static errlevel_t highgui_errlevel = unsafe;


static val_t eic_destroy_window(void)
{
	val_t v;

	v.ival = destroy_window((char*)arg(0,getargs(),ptr_t).p);

	return v;
}

static val_t eic_create_image(void)
{
	val_t v;

	v.p.ep = v.p.sp = v.p.p = create_image(arg(0,getargs(),int),
		arg(1,getargs(),int));

	return v;
}

static val_t eic_destroy_image(void)
{
	val_t v;

	v.ival = destroy_image(arg(0,getargs(),ptr_t).p);

	return v;
}

static val_t eic_attach_image(void)
{
	val_t v;

	v.ival = attach_image((char*)arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_load_bitmap(void)
{
	val_t v;

    char* name = strdup((char*)arg(0,getargs(),ptr_t).p);
	v.p.ep = v.p.sp = v.p.p = load_bitmap((char*)arg(0,getargs(),ptr_t).p);
    if(!v.p.p && highgui_errlevel == safe)
    {
        char str[1024];
        sprintf(str, "The bitmap %s has not been found. \nAborting the execution.", name);
        WRAP_THROW_MESSAGE(highgui_mark, str)
    }

    free(name);
	return v;
}

static val_t eic_save_bitmap(void)
{
	val_t v;

	v.ival = save_bitmap((char*)arg(0,getargs(),ptr_t).p, 
                        arg(1,getargs(),ptr_t).p);

	return v;
}

static val_t eic_named_window(void)
{
	val_t v;

	v.ival = named_window((char*)arg(0,getargs(),ptr_t).p,
		arg(1,getargs(),unsigned long));

	return v;
}

static val_t eic_wait_key(void)
{
	val_t v;

	v.ival = wait_key((char*)arg(0,getargs(),ptr_t).p);

	return v;
}

static val_t eic_wait_key_ex(void)
{
	val_t v;

	v.ival = wait_key_ex(
        (char*)arg(0,getargs(),ptr_t).p,
        arg(1, getargs(), int));

	return v;
}

int trackbar_count = 0;
int *trackbars = NULL;
void (**trackbar_notifies)(int) = NULL;

void trackbar_notify(int val)
{
    int i;

    // Find the trackbar
    for(i = 0; i < trackbar_count; i++)
    {
        if(trackbars[i] == val)
        {
            break;
        }
    }
    if(i >= trackbar_count)
    {
        return;
    }

    setArg(0, (code_t*)trackbar_notifies[i], int, val);
    EiC_callBack(trackbar_notifies[i]);
}

static val_t eic_create_trackbar(void)
{
	val_t v;
    void* pnotify = arg(4,getargs(),ptr_t).p;
	v.ival = create_trackbar((const char*)arg(0,getargs(),ptr_t).p,
        (const char*)arg(1,getargs(),ptr_t).p,
        (int*)arg(2,getargs(),ptr_t).p,
        arg(3,getargs(),int),
        pnotify ? trackbar_notify : NULL);
    trackbar_count++;
    trackbars = (int*)realloc(trackbars, trackbar_count*sizeof(int));
    trackbar_notifies = (void(**)(int))realloc(trackbar_notifies, trackbar_count*sizeof(char*));

    trackbars[trackbar_count - 1] = v.ival;
    trackbar_notifies[trackbar_count - 1] = (void(*)(int))pnotify;

	return v;
}

static val_t eic_create_toolbar(void)
{
	val_t v;

	v.ival = create_toolbar((char*)arg(0,getargs(),ptr_t).p/*,
		arg(1,getargs(),int)*/);

	return v;
}

static val_t eic_show_iplimage(void)
{
    val_t v;

    show_iplimage((char*)arg(0, getargs(), ptr_t).p, 
                  (IPLIMAGE)arg(1, getargs(), ptr_t).p);

    return v;
}

static val_t eic_load_iplimage(void)
{
    val_t v;

    char* name = (char*)arg(0, getargs(), ptr_t).p;
    v.p.p = load_iplimage(name);
    if(!v.p.p && highgui_errlevel == safe)
    {
        char str[1024];
        sprintf(str, "The bitmap %s has not been found. \nAborting the execution.", name);
        WRAP_THROW_MESSAGE(highgui_mark, str)
    }

    return v;
}

static val_t eic_save_iplimage(void)
{
    val_t v;

    v.ival = save_iplimage((char*)arg(0, getargs(), ptr_t).p,
        (IPLIMAGE)arg(1, getargs(), ptr_t).p);

    return v;
}

/**********************************/

void module_highguiwrap()
{
	EiC_add_builtinfunc("cvvDestroyWindow",eic_destroy_window);
//	EiC_add_builtinfunc("create_image",eic_create_image);
//	EiC_add_builtinfunc("destroy_image",eic_destroy_image);
//	EiC_add_builtinfunc("attach_image",eic_attach_image);
//	EiC_add_builtinfunc("load_bitmap",eic_load_bitmap);
//	EiC_add_builtinfunc("save_bitmap",eic_save_bitmap);
	EiC_add_builtinfunc("cvvNamedWindow",eic_named_window);
	EiC_add_builtinfunc("cvvWaitKey",eic_wait_key);
	EiC_add_builtinfunc("cvvWaitKeyEx",eic_wait_key_ex);
    EiC_add_builtinfunc("cvvCreateTrackbar",eic_create_trackbar); 
    EiC_add_builtinfunc("cvvCreateSlider",eic_create_trackbar); 
    EiC_add_builtinfunc("create_toolbar",eic_create_toolbar);

    EiC_add_builtinfunc("cvvShowImage",eic_show_iplimage);
	EiC_add_builtinfunc("cvvLoadImage",eic_load_iplimage);
	EiC_add_builtinfunc("cvvSaveImage",eic_save_iplimage);
}

void set_highgui_mark(jmp_buf* mark)
{
    highgui_mark = mark;
}

void set_highgui_errlevel(errlevel_t level)
{
    highgui_errlevel = level;
}
/**********************************/

