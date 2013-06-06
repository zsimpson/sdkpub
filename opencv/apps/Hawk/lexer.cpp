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

#include  "stdafx.h"
#include  <stdio.h>
#include  <stdlib.h>
#include  <ctype.h>
#include  <string.h>

#include  "lexer.h"

typedef struct _HashEntry
{
    unsigned  hash;
    int       len;
    struct _HashEntry* next;
    const char* str;
}
HashEntry;

HashEntry   keyword_storage[100];

#define  HASHTABLE_SIZE   17
HashEntry*  keyword_table[HASHTABLE_SIZE];
static int  hash_init = 0;

const char* keywords[] = 
{
    "break",    "case",     "char",     "const",
    "continue", "default",  "do",       "double",
    "else",     "enum",     "extern",   "float",
    "for",      "goto",     "if",       "int",
    "long",     "register", "return",   "short",
    "signed",   "sizeof",   "static",   "struct",
    "switch",   "typedef",  "union",    "unsigned",
    "void",     "volatile", "while",    0
};


inline unsigned  calc_hash( const char* text, int len )
{
    int j, shift = 0;
    unsigned hash = len;
    for( j = 0; j < len; j++ )
    {
        shift += 11;
        if( shift >= 32 ) shift -= 32;
        hash ^= ((unsigned char*)text)[j] << shift;
    }
    return hash;
}


void InitLexer( Lexer* lexer, const char* text )
{
    lexer->text = text;
    lexer->pos = 0;

    if( !hash_init )
    {
        int  i;
        int  count[HASHTABLE_SIZE];
        memset( count, 0, sizeof(count));
        memset( keyword_table, 0, sizeof( keyword_table));

        for( i = 0; keywords[i] != 0; i++ )
        {
            int idx, len;
            keyword_storage[i].len = len = strlen( keywords[i] );
            keyword_storage[i].hash = calc_hash( keywords[i], len );
            keyword_storage[i].str = keywords[i];
            idx = keyword_storage[i].hash % HASHTABLE_SIZE; 
            keyword_storage[i].next = keyword_table[idx];
            keyword_table[idx] = keyword_storage + i;
            count[idx]++;
        }
        hash_init = 1;
    }
}


HashEntry* find_text( const char* str, int len )
{
    unsigned hash = calc_hash( str, len );
    int idx = hash % HASHTABLE_SIZE;
    HashEntry* entry = keyword_table[idx];

    while( entry )
    {
        if( entry->hash == hash &&
            entry->len == len &&
            !strncmp( entry->str, str, len )) break;
        entry = entry->next;
    }
    return entry;
}


void  GetToken( Lexer* lexer, Token* token )
{
    const char* text = lexer->text;
    int pos = lexer->pos;
    token->type = TOKEN_NORMAL;

    while( isspace(text[pos])) pos++;
    token->start = pos;

    switch( text[pos] )
    {
    case '/': pos++;
              switch( text[pos] )
              {
              case '/': /* end-line comment */
                  token->type = TOKEN_COMMENT;
                  ++pos; while( text[pos] != '\n' && text[pos] != '\0' ) pos++;
                  break;
              case '*':
                  token->type = TOKEN_COMMENT;
                  ++pos;
                  while( text[pos] != '\0' )
                  {
                      if( text[pos] == '*' && text[pos+1] == '/')
                      {
                          pos += 2;
                          break;
                      }
                      pos++;
                  }
                  break;
              }
              break;
    case '\0':  token->type = TOKEN_END;
                return; 

    case '\"':  token->type = TOKEN_STRING;
                pos++;
                for(;;)
                {
                    if( text[pos] == '\0' || text[pos] == '\"' || text[pos] == '\n' )
                        break;
                    if( text[pos] == '\\' )
                    {
                        pos += 2;
                        if( text[pos] == '\n' ) pos++;
                    }
                    else
                    {
                        pos++;
                    }
                }
                if( text[pos] == '\"') pos++;
                break;

    case '\'':  token->type = TOKEN_STRING;
                pos++;
                for(;;)
                {
                    if( text[pos] == '\0' || text[pos] == '\'' || text[pos] == '\n' )
                        break;
                    pos += text[pos] == '\\' ? 2 : 1;
                }
                if( text[pos] == '\'') pos++;
                break;
    default:
        if( isalpha( text[pos] ) || text[pos] == '_' )
        {
            pos++;
            while( isalnum( text[pos] ) || text[pos] == '_' ) pos++;

            if( find_text( text + token->start, pos - token->start ))
            {
                token->type = TOKEN_KEYWORD;
            }
        }
        else if( isdigit(text[pos]) || (text[pos] == '.' && isdigit(text[pos+1])))
        {
            int pos1 = pos;
            token->type = TOKEN_NUMBER;
            pos++; while( isalnum( text[pos])) pos++;
            if( (text[pos] == '+' || text[pos] == '-') && text[pos-1] == 'e')
            {
                while( isdigit(text[pos1]) || text[pos1] == '.') pos1++;
                if( pos1 == pos - 1 )
                {
                    pos++;
                    while( isdigit(text[pos])) pos++;
                }
            }
        }
        else 
        {
            pos++;
        }
    }

    lexer->pos = pos;
}
