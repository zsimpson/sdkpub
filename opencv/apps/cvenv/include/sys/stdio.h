/*  This header file is machine generated. 
Modify EiC/config/genstdio.c, or the target independent source 
files it reads, in order to modify this file.  Any 
direct modifications to this file will be lost. 
*/

#define BUFSIZ	8192
#define EOF	-1
#define FILENAME_MAX	4095
#define FOPEN_MAX	256
#define L_tmpnam	20
#define TMP_MAX	238328
#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2
#define _IOFBF	0
#define _IOLBF	1
#define _IONBF	2
typedef int  fpos_t;

typedef struct { char dummy[148]; } FILE;

FILE * _get_stdin();
FILE * stdin = _get_stdin();
FILE * _get_stdout();
FILE * stdout = _get_stdout();
FILE * _get_stderr();
FILE * stderr = _get_stderr();
