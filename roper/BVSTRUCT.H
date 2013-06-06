// BVStruct.h : Constants for CSMA and Basic in WinX/32
//
/////////////////////////////////////////////////////////////////////////////
//   This revision:  $Revision: 11 $
//   Last check-in   $Date: 1/23/97 6:21p $
//   Last changes by $Author: Maynard $
//   Changes:
/*   $Log: /WinX32 V2.0/INCLUDE/BVSTRUCT.H $
*  
*  11    1/23/97 6:21p Maynard
*  Remove include of platform.h and change newtypes.h to pitypes.h
*  
*  10    10/31/96 4:09p Dan
*  implementing 16/32 signed/unsigned int data/value types
*  
*  9     8/21/96 3:05p Dan
*  WIN32izing
*  re-defined a few conditioned out defines
*  
*  8     8/15/96 11:51a Maynard
*  Change pitypes.h to newtypes.h
*
*  3     8/07/96 6:27p Maynard
*
*/
/////////////////////////////////////////////////////////////////////////////
#ifndef  BVSTRUCT_H
#define  BVSTRUCT_H  1

#include "pitypes.h"   /*  XSMA definitions        */

/********  A L L O C A T I O N  R O U T I N E S  R E D E F I N E D  ********/

#undef malloc
#undef free
#undef allocate
#undef deallocate

#define R_BASIC 999
#define malloc(x) Xalloc(x,R_BASIC)
#define free(x)   Xfree(x)

#define allocate(x)   Xalloc(x,R_BASIC)
#define deallocate(x) Xfree(x)

/***************************************************************************/


#ifndef min
#define min(x,y) ((x)>(y) ? (y) : (x))
#endif

#ifndef max
#define max(x,y) ((x)>(y) ? (x) : (y))
#endif


/*********************************************************************
 *                                                                   *
 *                       CONSTANT DEFINITIONS                        *
 *                                                                   *
 *********************************************************************/

/*  special definitions  */
/*  for parser compatibility between CSMA & XSMA versions  */

#define DOUBLE_TYPE_AVAILABLE  1

#define ERROR_FILE_NAME "basic.err"

/*  Basic UserIO Files  */
#define MAX_USERIO_FILES     10

/* file i/o modes */
#define MODE_INPUT            1
#define MODE_CYCLIC_INPUT     2
#define MODE_OUTPUT           3
#define MODE_APPEND           4

#define MODE_OVERWRITE        5
#define MODE_INCREMENT        6

/* user file i/o modes */

#define MODE_TEXT_INPUT       7
#define MODE_BINARY_INPUT     8
#define MODE_TEXT_OUTPUT      9
#define MODE_BINARY_OUTPUT   10
#define MODE_TEXT_APPEND     11
#define MODE_BINARY_APPEND   12


/* symbol table entry types */
#define PIMB_VAR        1001
#define PIMB_LBEL       1002
#define PIMB_FUNCTION   1003
#define PIMB_CONSTANT   1004
#define PIMB_ERROR      1005

#define SYMBOL_NAME_SIZE   33

#define MAX_DIMENSIONS              5
#define MAX_FCN_ARGS               30
#define INIT_DIMENSIONS   {0,0,0,0,0}
#define MAX_SB_DIMENSION       65535L       /* max size of Spectrum Basic
                                               array element (see VALUE
                                               structure[dimensions] ) */
/*  value types  */
enum VALUE_TYPES
{
  FLOAT_TYPE = 0,           /* float 4-byte              */
  LONG_TYPE,                /* long integer 4-byte       */
  INT_TYPE,                 /* integer 2-byte            */ 
  UNINT_TYPE,               /* unsigned integer 2-byte   */
  CHAR_TYPE,                /* char (ascii) 1-byte       */
  DOUBLE_TYPE,              /* double 8-byte             */
  BYTE_TYPE,                /* byte 1-byte               */
  UNBYTE_TYPE,              /* unsigned byte 1-byte      */
  UNLONG_TYPE,              /* unsigned long 4-bytes     */
  FILESLOT_TYPE,            /* WinX FILESLOT structure   */
  XDATA_TYPE,               /* WinX DATA structure       */
  MATH_TYPE,                /* WinX MATHOBJECT structure */
  XCONTROLLER_TYPE,         /* WinX CONTROLLER structure */
  XWINDOW_TYPE,             /* WinX XWINDOW structure    */
  IMEXPORT_TYPE,            /* WinX IMEXPORT structure   */
  PHYPORT_TYPE,             /* WinX PHYPORT structure    */
  INT32_TYPE,               /* integer 4-byte            */
  UNINT32_TYPE,             /* unsigned integer 4-byte   */
/*  redefined types  */
  UNDEF_TYPE = -1,          /* undefined                 */
  INT16_TYPE = INT_TYPE,    /* integer 2-byte            */
  UNINT16_TYPE = UNINT_TYPE /* unsigned integer 2-byte   */
};

/********************************************************************
 *                                                                  *
 *                        TYPE DEFINITIONS                          *
 *                                                                  *
 ********************************************************************/

/* VALUE holds any value, a string, spectrum, scalar, etc.
   In the union of possible value types, entry vl must appear
   first for the compile time initialization, which initializes
   the first field of a union.  To initialize the entry vf a
   type cast must be used. */
// In general, try to use polymorphism instead of schemes like
// this except where *absolutely* necessary
// ---MLM---
typedef struct value {
  int value_type;                  /* CHAR_TYPE, INT_TYPE, LONG_TYPE,
                                      FLOAT_TYPE, UNINT_TYPE, DOUBLE_TYPE,
                                      BYTE_TYPE, UNBYTE_TYPE, UNLONG_TYPE,
                                      FILESLOT_TYPE, MATH_TYPE, XDATA_TYPE,
                                      XCONTROLLER_TYPE, XWINDOW_TYPE &
                                      IMEXPORT_TYPE, PHYPORT_TYPE          */
  SHORT conformant;                  /* TRUE if dimensions can be determined by assigned value */
  SHORT n_dims;                      /* number of dimensions          */
  WORD dimensions[MAX_DIMENSIONS];  /* dimension sizes -- [0] varies fastest   */
  union value_pointers
    {
    long   vl;    /* value if long     scalar      */
    double vd;    /* value if double   scalar      */
    float  vf;    /* value if float    scalar      */
    DWORD  vul;   /* value if unsigned scalar      */
    short  vi;    /* value if int      scalar      */
    WORD   vu;    /* value if unsigned scalar      */
    char   vc;    /* value if char     scalar      */
    BYTE   vub;   /* value if unsigned byte scalar */
    long   *pl;   /* ptr if long   array           */
    double *pd;   /* ptr if double array           */
    float  *pf;   /* ptr if float  array           */
    DWORD  *pul;  /* ptr if unsigned long array    */
    short  *pi;   /* ptr if int    array           */
    WORD   *pu;   /* ptr if WORD array     */
    char   *pc;   /* ptr if char   array           */
    BYTE   *pub;  /* ptr if unsigned byte array    */
    DWORD  * px;  /* ptr if WinView data type      */
    } v;
                                                                                                       
  union xsma_pointers
    {
    void *slotptr;              /* ptr to a FILESLOT object      */
    void *dataptr;              /* ptr to a WinView DATA structure */
    void *mathptr;              /* ptr to a ARITHOBJECT          */
    void *controllerptr;        /* ptr to a CONTROLLER object    */
    void *xwindowptr;           /* ptr to a XWINDOW object       */
    void *imexportptr;          /* ptr to a IMEXPORT object      */
    void *phyportptr;           /* ptr to a PHYPORT object       */
    } xsma;                      /* associated with this value    */
                                                                                                       
} VALUE;
                                                                                                       
#define SNULL (SYMBOL *)0
#define GSNULL (G_SYMBOL *)0

#define MAX_PARSER_BLOCK_SIZE   32768L

#define HASHSIZE  257

/* One node of a parse tree. */

/* One node of a parse tree. */
typedef struct parse_node
{
  SHORT node_sequence_number;          /* Sequence # of saved NODE  */
  SHORT node_type;                     /* parse node type           */
  struct parse_node *next_node;        /* pointer to next node      */
  struct parse_node *p1,*p2,*p3,*p4;   /* subnode pointers          */
  SHORT next_sequence_number;          /* next node sequence #      */
  SHORT p1_sequence_number;            /* p1 node sequence #        */
  SHORT p2_sequence_number;            /* p2 node sequence #        */
  SHORT p3_sequence_number;            /* p3 node sequence #        */
  SHORT p4_sequence_number;            /* p4 node sequence #        */
  union node_pointers
    {
    struct lSymbol * symbol_ptr;       /* ptr if VAR or LABEL       */
    VALUE  * value_ptr;                /* ptr if CONST              */
    SHORT fileio;                      /* type of fileio for OPEN   */
    } v;
  SHORT v_sequence_number;             /* sequence # of v-union     */
  SHORT lineno;                        /* BASIC line number of NODE */
} PARSE_NODE;

/*  Local Symbol Table Entry  */
typedef struct lSymbol
{
  SHORT symbol_sequence_number;        /* Sequence # of saved SYMBOL */
  SHORT symbol_type;                   /* LABEL or VAR               */
  SHORT defined;                       /* TRUE or FALSE              */
  char name[SYMBOL_NAME_SIZE];         /* symbol name                */
  union symbol_pointers
    {
    PARSE_NODE * pn_ptr;               /* parse node ptr if label    */
    VALUE      * value_ptr;            /* value ptr if not label     */
    } v;
  SHORT v_sequence_number;             /* sequence # of v-union      */
  struct lSymbol * next_entry;         /* pointer to next symbol     */
  SHORT hash_indx;                     /* HASH TABLE Index           */
} SYMBOL;

/*  Global Symbol Table Entry  */
typedef struct gSymbol
{
  int symbol_type;                     /* FUNCTION, DLL FUNCTION...  */
  int symbol_value;                    /* Function#....              */
  char name[SYMBOL_NAME_SIZE];         /* symbol name                */
  struct gSymbol * next_entry;         /* pointer to next symbol     */
} G_SYMBOL;

/*  saved BINARY PARSED NODES file HEADER  */

#define BINFILE_HEADER_VERSION  8  /*  Version # of current BINFILE HEADER  */
                                   /*  1 = Original Version                 */
                                   /*  2 = changed some of the DATA         */
                                   /*      ACQUISITION download functions   */
                                   /*      force a recompile                */
                                   /*  3 = Updated PARSER --> PARSER.DEF    */
                                   /*  4 = increased size of symbol name    */
                                   /*  5 = WinView V1.3 has arrived         */
                                   /*      BASIC ENHANCEMENT on Function    */
                                   /*      calling implemented -- please    */
                                   /*      see note in EVALFCNS.C           */
                                   /*  6 = WinView V1.4                     */
                                   /*  7 = WinView V1.5                     */
                                   /*  8 = WinView V1.6                     */

typedef struct bin_header
{
  char system[4];                 /*  system id --> CSMA, WinX         */
  SHORT  header_version;          /*  HEADER Version                   */
  SHORT  number_of_constants;     /*  number of CONSTANTS in file      */
  SHORT  number_of_parsed_nodes;  /*  number of NODES PARSER generated */
  SHORT  number_of_stored_nodes;  /*  number of NODES Stored in file   */
  SHORT  number_of_symbols;       /*  number of SYMBOLS in file        */
  SHORT  number_of_values;        /*  number of VALUES in file         */
  SHORT  number_of_value_arrays;  /*  number of VALUE ARRAYS in file   */
  SHORT  starting_node;           /*  sequence number of ROOT NODE     */
} BINFILE_HEADER;

#endif // BVSTRUCT_H

/************************  end of BVSTRUCT.H  ***********************/
