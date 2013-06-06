/*  This header file is machine generated. 
Modify EiC/config/genstdio.c, or the target independent source 
files it reads, in order to modify this file.  Any 
direct modifications to this file will be lost. 
*/

#ifndef EiC_limits_H
#define EiC_limits_H

#pragma push_safeptr

#define CHAR_BIT	8
#define MB_LEN_MAX	6
#define UCHAR_MAX	255
#define USHRT_MAX	65535
#define UINT_MAX	4294967295
#define CHAR_MAX	127
#define SCHAR_MAX	127
#define SHRT_MAX	32767
#define INT_MAX	2147483647
#define CHAR_MIN	 (-CHAR_MAX-1)
#define SCHAR_MIN	 (-SCHAR_MAX-1)
#define SHRT_MIN	 (-SHRT_MAX-1)
#define INT_MIN	 (-INT_MAX-1)
#define LONG_MIN	 (-LONG_MAX-1)
#define LONG_MAX	 2147483647
#define ULONG_MAX	 4294967295

/* POSIX.1 STUFF */
#ifdef _POSIX_SOURCE
#define ARG_MAX	131072
#define CHILD_MAX	999
#define LINK_MAX	127
#define MAX_CANON	255
#define MAX_INPUT	255
#define NAME_MAX	255
#define NGROUPS_MAX	32
#define OPEN_MAX	256
#define PIPE_BUF	4096
#define SSIZE_MAX	2147483647
#define TZNAME_MAX	3
#define _POSIX_ARG_MAX	4096
#define _POSIX_CHILD_MAX	6
#define _POSIX_LINK_MAX	8
#define _POSIX_MAX_CANON	255
#define _POSIX_MAX_INPUT	255
#define _POSIX_NAME_MAX	14
#define _POSIX_NGROUPS_MAX	0
#define _POSIX_OPEN_MAX	16
#define _POSIX_PATH_MAX	255
#define _POSIX_PIPE_BUF	512
#define _POSIX_SSIZE_MAX	32767
#define _POSIX_STREAM_MAX	8
#define _POSIX_TZNAME_MAX	3
#endif /* end  _POSIX_SOURCE */

#pragma pop_ptr

#endif    /* end EiC_limits_H */
