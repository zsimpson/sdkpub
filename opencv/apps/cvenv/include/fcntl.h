/*  This header file is machine generated. 
Modify EiC/config/genstdio.c, or the target independent source 
files it reads, in order to modify this file.  Any 
direct modifications to this file will be lost. 
*/

#ifndef EiC_fcntl_H
#define EiC_fcntl_H

#pragma push_safeptr

#include <sys/types.h>
#include <sys/fcntl.h>

int open(const char *path, int access, ... /* mode_t mode */);
int creat(const char *path, mode_t amode);
int fcntl(int fd, int cmd, ... /* struct flock *flockptr*/);

#define O_BINARY      0
#define O_TEXT        0
#define FD_CLOEXEC	1
#define F_DUPFD	0
#define F_GETFD	1
#define F_GETFL	3
#define F_GETLK	5
#define F_SETFD	2
#define F_SETFL	4
#define F_SETLK	6
#define F_SETLKW	7
#define F_RDLCK	0
#define F_UNLCK	2
#define F_WRLCK	1
#define O_ACCMODE	3
#define O_APPEND	1024
#define O_CREAT	64
#define O_EXCL	128
#define O_NOCTTY	256
#define O_NONBLOCK	2048
#define O_RDONLY	0
#define O_RDWR	2
#define O_TRUNC	512
#define O_WRONLY	1

#pragma pop_ptr

#endif    /* end EiC_fcntl_H */
