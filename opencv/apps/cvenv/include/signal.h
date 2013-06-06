/*  This header file is machine generated. 
Modify EiC/config/genstdio.c, or the target independent source 
files it reads, in order to modify this file.  Any 
direct modifications to this file will be lost. 
*/

#ifndef EiC_signal_H
#define EiC_signal_H

#pragma push_safeptr

#define SIGABRT	6
#define SIGINT	2
#define SIGILL	4
#define SIGFPE	8
#define SIGSEGV	11
#define SIGTERM	15

/* signal() args & returns */
typedef int  sig_atomic_t;
void (*signal(int sig, void (*func)(int a))) (int a);
int raise(int sig);
#define SIG_ERR       (void (*)(int)) -1
#define SIG_DFL       (void (*)(int)) 0
#define SIG_IGN       (void (*)(int)) 1

/* POSIX.1 STUFF */
#ifdef _POSIX_SOURCE
#define SA_NOCLDSTOP	1
#define SIGALRM	14
#define SIGCHLD	17
#define SIGHUP	1
#define SIGIOT	6
#define SIGKILL	9
#define SIGPIPE	13
#define SIGQUIT	3
#define SIGSTOP	19
#define SIGTSTP	20
#define SIGTTIN	21
#define SIGTTOU	22
#define SIGUSR1	10
#define SIGUSR2	12
#endif /* end  _POSIX_SOURCE */

#pragma pop_ptr

#endif    /* end EiC_signal_H */
