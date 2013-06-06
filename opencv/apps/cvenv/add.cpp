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

#include "assert.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "malloc.h"
#include "eic.h"
#include "typemod.h"
#include "global.h"
#include "func.h"
#include "symbol.h"
#include "error.h"

#undef malloc
#undef realloc
#undef free

#ifdef WIN32
typedef __int64 int64;
#else
typedef long long int64;
#endif

typedef struct
{
    symentry_t* sym;
    void*       addr;
} called_type;

typedef struct
{
    void* callcode;
    symentry_t* sym;
} callback_t;

typedef val_t(*f_t)();
typedef int64(*call_t)();

static int get_uweic_type(type_expr* type) 
{
    struct_t* s;
#define _TYPE_CASE(x)   case t_##x: return sizeof(x)
#define _TYPE_UCASE(x)   case t_##x: case t_u##x: return sizeof(x)

    switch(type->obj)
    {
        _TYPE_UCASE(char);
        _TYPE_UCASE(short);
        _TYPE_UCASE(int);
        _TYPE_UCASE(long);
#ifdef WIN32
        _TYPE_CASE(enum);
#else
        case t_enum:
        return sizeof( int );
#endif
        _TYPE_CASE(float);
        _TYPE_CASE(double);

    case t_pointer:
        return sizeof(void*);

    case t_struct:
    case t_union:
        s = (struct_t*)(type->u.inf);
        return s->tsize;

    case t_void:
    case t_var:
        return 0;
        
    default:
        assert(0);
        return -1;
    }

#undef _TYPE_UCASE
#undef _TYPE_CASE
}

static int get_size_arg_buffer( symentry_t* sym )
{
    type_expr* ret_type = sym->type->nxt;
    int        arg_num  = ((func_t*)sym->type->u.inf)->Num;
    parm_t*    arg_type = ((func_t*)sym->type->u.inf)->parm;
    int size = 0;
    
    /* check for return type is no 1, 2, 4 or 8 bytes long */
    switch( get_uweic_type( ret_type ) )
    {
    case 0:
    case 1:
    case 2:
    case 4:
    case 8:
        break;
    default:
        size += sizeof( void* );
    }
    for( int i = 0; i < arg_num; i++ )
        size += (get_uweic_type( arg_type[i].type ) + 3) & ~3;
    return size;
}

#pragma warning(disable:4716)
static float get_float(void)
{
}

static double get_double(void)
{
}
#pragma warning(default:4716)

static int callback_num = 0;
static callback_t* callback = (callback_t*)malloc( 10 );
static callback_t* current_call = 0;

static double set_double(double a)
{
    a = a + 0;
    return a;
}

typedef void(*set_double_t)(double);

set_double_t set_dbl = (set_double_t)set_double;

#ifndef WIN32
int64 unicall( int first )
#else
int64 unicall( void* addr_ret, int first )
#endif
{
    assert( current_call );
    assert( current_call->sym );
    if( !current_call )
        return 0;

    symentry_t* sym = current_call->sym;
    
#ifdef WIN32
    /* support __stdcall function */
    assert( addr_ret );
    char* r = (char*)*(&addr_ret - 1);
    if( (*(unsigned short*)addr_ret) == 0xc481 || (*(unsigned short*)addr_ret) == 0xc483 )
        /* __cdecl function */
        *(unsigned short*)(r + 1) = 0;
    else /* __stdcall function */
        *(unsigned short*)(r + 1) = (unsigned short)get_size_arg_buffer( sym );
#endif

    type_expr* ret_type = sym->type->nxt;
    int arg_num = ((func_t*)sym->type->u.inf)->Num;
    parm_t* parm = ((func_t*)sym->type->u.inf)->parm;
    code_t* cb = ((func_t*)sym->type->u.inf)->callBack;

    int first_arg = 0;
    void* ret_data = 0;

    /* allocate buffer for return value if return value is structure or union */
    if( ret_type->obj == t_struct || ret_type->obj == t_union )
    {
        ret_data = alloca( get_uweic_type( ret_type ) );
        *(void**)(&(cb->inst[cb->nextinst - 5 - 2 * 0].val)) = ret_data;
        first_arg = 1;
    }

    char* buf = (char*)&first;

    /* if sizeof(return value) not ... then first argument is pointer to data */
    switch( get_uweic_type( ret_type ) )
    {
    case 0:
    case 1:
    case 2:
    case 4:
    case 8:
        break;
    default:
        buf += sizeof( void* );
    }

    for( int i = 0; i < arg_num; i++ )
    {
        switch( parm[i].type->obj )
        {
        case t_struct:
        case t_union:
            *(void**)(&(cb->inst[cb->nextinst - 5 - 2 * (first_arg + i)].val)) = buf;
            break;
        default:
            *(double*)(&(cb->inst[cb->nextinst - 5 - 2 * (first_arg + i)].val)) = *(double*)buf;
        }
        buf += (get_uweic_type( parm[i].type ) + 3) & ~3;
    }

    EiC_callBack(cb);

    switch( get_uweic_type( ret_type ) )
    {
    case 0:
        break;
    case 1:
    case 2:
    case 4:
    case 8:
        if( ret_type->obj == t_float || ret_type->obj == t_double )
        {
            set_dbl( EiC_ReturnValue( double ) );
        }
        else if( ret_type->obj == t_struct || ret_type->obj == t_union )
        {
            return *EiC_ReturnValue( int64* );
        }
        else
            return EiC_ReturnValue( int64 );
        break;
    default:
        memcpy( &first, ret_data, get_uweic_type( ret_type ) );
        return (int64)first;
    }
}

static void* add_callback( symentry_t* sym )
{
    int i;
    for( i = 0; i < callback_num; i++ )
        if( sym == callback[i].sym )
            return callback[i].callcode;
    callback = (callback_t*)realloc( callback, sizeof( callback_t ) * (callback_num + 1) );
    callback[callback_num].sym = sym;
    char* code = (char*)(callback[callback_num].callcode = malloc( 32 ));

    code[0] = (unsigned char)0xc7;                     // mov current_sym, pointer
    code[1] = (unsigned char)0x05;
    *(void**)(code + 2) = &current_call;
    *(callback_t**)(code + 2 + 4) = callback + callback_num;
#ifndef WIN32
    code[2 + 4 + 4] = (unsigned char)0xe9;             // jmp uniwrap
#else
    code[2 + 4 + 4] = (unsigned char)0xe8;             // call uniwrap
#endif
    int offset = (int)unicall - ((int)code + 15);
    *(int*)(code + 2 + 4 + 4 + 1) = offset;
#ifdef WIN32
    code[2 + 4 + 4 + 1 + 4] = (unsigned char)0xc2;     // ret 0
    code[2 + 4 + 4 + 1 + 5] = 0;
    code[2 + 4 + 4 + 1 + 6] = 0;
    code[2 + 4 + 4 + 1 + 7] = 0;
    code[2 + 4 + 4 + 1 + 8] = 0;
#endif
/*  unix                                      windows
    __asm{                                    __asm{
        mov current_sym, 12345678h;                mov current_sym, 12345678h;
        jmp unicall                                call unicall;
    }                                              ret 0;  // this value may be changed if __stdcall
*/
    callback_num++;
    return code;
}

static called_type* current_func = 0;

val_t uniwrap()
{
    assert( current_func );
    assert( current_func->addr );
    assert( current_func->sym );

    called_type* func = current_func;

    void* f = func->addr;

    type_expr* ret_type = func->sym->type->nxt;
    int        arg_num  = ((func_t*)func->sym->type->u.inf)->Num;
    parm_t*    arg_type = ((func_t*)func->sym->type->u.inf)->parm;

    int size = get_size_arg_buffer( func->sym );
    int first_arg = 0;
    
    /* if return type is structure or union first argument is pointer to result */
    if( ret_type->obj == t_struct || ret_type->obj == t_union )
        first_arg = 1;
    
    /* calculating size of stack */
    int i;
    int64 intbuf;
    char* buffer = (char*)alloca( size );
    char* buf = buffer;
    void* ret_data;
    val_t ret_val;

    /* if sizeof(result) not 1, 2, 4 or 8 alloc memory to save result */
    /* set pointer ret_data to result data */
    switch( get_uweic_type( ret_type ) )
    {
    case 0:
    case 1:
    case 2:
    case 4:
    case 8:
        ret_data = &intbuf;
        break;
    default:
        *(void**)buf = malloc( get_uweic_type( ret_type ) );
        buf += sizeof( void* );
        ret_data = *(void**)buffer;
    }

    /* copy parameters values to stack es:esp */
    for( i = 0; i < arg_num; i++ )
    {
        switch( arg_type[i].type->obj )
        {
        case t_union:
        case t_struct:
            memcpy( buf,
                    arg(first_arg + i, getargs(), ptr_t).p,
                    (get_uweic_type( arg_type[i].type ) + 3) & ~3 );
            buf += (get_uweic_type( arg_type[i].type ) + 3) & ~3;
            break;
        case t_pointer:
            printf("pointer\n");
            {
                void* data = &arg(first_arg + i, getargs(), ptr_t).p;
                int   size = get_uweic_type( arg_type[i].type );
                printf("size = %d value = %d\n", size, data ? *(int*)data : 0);
            }
            if( arg_type[i].type->nxt && arg_type[i].type->nxt->obj == t_funcdec )
            {
                printf("callback\n");
                /* this is callback parameter, need special translation */
                void* cb = arg(first_arg + i, getargs(), ptr_t).p;
                symentry_t* sym = EiC_lookup_by_callback( 1, cb );
                if( sym )
                {
                    void* call = add_callback( sym );
                    *(void**)buf = call;
                    buf += sizeof(call);
                    break;
                }
                else assert( 0 );
            }
        default:
            {
                void* data = &arg(first_arg + i, getargs(), ptr_t).p;
                memcpy( buf, data,
                        (get_uweic_type( arg_type[i].type ) + 3) & ~3 );
                buf += (get_uweic_type( arg_type[i].type ) + 3) & ~3;
            }
        }
    }
#ifndef WIN32
    intbuf = ((call_t)f)();
#else
    __asm
    {
        call dword ptr [f]
        mov dword ptr intbuf, eax
        mov dword ptr intbuf + 4, edx
    }
#endif

    if( ret_type->obj == t_float )
    {
        *(float*)&intbuf = get_float();
    }
    else     if( ret_type->obj == t_double )
    {
        *(double*)&intbuf = get_double();
    }

    switch( ret_type->obj )
    {
    case t_struct:
    case t_union:
        memcpy( arg( 0, getargs(), ptr_t).p, ret_data, get_uweic_type( ret_type ) );
        ret_val.p.sp = ret_val.p.p = arg( 0, getargs(), ptr_t).p;
        ret_val.p.ep = (char*)ret_val.p.p + get_uweic_type( ret_type );
        break;
    default:
        memcpy( &ret_val, ret_data, get_uweic_type( ret_type ) );
        break;
    }

    switch( get_uweic_type( ret_type ) )
    {
    case 0:
    case 1:
    case 2:
    case 4:
    case 8:
        break;
    default:
        free(*(void**)buffer);
    }

    return ret_val;
}

int AddExternFunction( void* addr, char* name )
{
    symentry_t* sym = (symentry_t*)EiC_lookup(1, name);
    if( !sym )
        return -1;

    char* wrap = (char*)malloc( 16 + sizeof(called_type) );

    called_type* func_desc = (called_type*)(wrap + 16);
    func_desc->addr = addr;
    func_desc->sym  = sym;

    wrap[0] = (unsigned char)0xc7;                     // mov cuurrent_sym, pointer
    wrap[1] = (unsigned char)0x05;
    *(void**)(wrap + 2) = &current_func;
    *(called_type**)(wrap + 2 + 4) = func_desc;
    /* in windows system we need support __stdcall function */

    wrap[2 + 4 + 4] = (unsigned char)0xe9;             // jmp uniwrap
    int offset = (int)uniwrap - ((int)wrap + 15);
    *(int*)(wrap + 2 + 4 + 4 + 1) = offset;

/*
    __asm{
        mov current_sym, 12345678h;
        call uniwrap;
        ret 0;
    }
*/
    EiC_add_builtinfunc(name, (f_t)wrap);
    return 0;
}

