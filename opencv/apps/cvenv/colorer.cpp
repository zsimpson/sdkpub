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

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "colorer.h"

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

///////////////////////////////////////////////////////////////////////////////
//parser
//

int GetTokenFromPos(int pos, Token* tokens, int num)
{
    int i;
    for(i = 1; i < num; i++)
        if(pos < tokens[i].start) return i -1;
    return i - 1;
}

int SetMap(char* map, Token* tokens, int num)
{
    tokens->start = 0;
    for(int i = 0; i < num - 1; i++)
        for(int j = 0; j < tokens[i + 1].start - tokens[i].start; j++)
            map[tokens[i].start + j] = (char)tokens[i].type;
    map[tokens[max(0, num - 1)].start] = TOKEN_END;
    return 0;
}

static char* old_text = 0;
static char* old_map = 0;

int ParseTextBegin(ClientData, Tcl_Interp *interp,
              int, char**)
{
    Token tokens__[MAX_TOKNS] = { TOKEN_END, 0 };
    Token* tokens_ = tokens__;
    int num = 0;
    int max_num = MAX_TOKNS;

    Tcl_Eval(interp, "$CVEnv::curframe get 1.0 end");

    if(old_text) delete old_text;
    if(old_map) delete old_map;

    int len = strlen(interp->result);
    if(!len) return 0;
    old_text = new char[len + 1];
    assert(old_text);
    old_map  = new char[len + 1];
    assert(old_map);

    strcpy(old_text, interp->result);

    Lexer lexer;
    Token token;
    Token prev_token = { TOKEN_END, 0 };

    InitLexer( &lexer, old_text );
    lexer.pos = 0;

    for(num = 0;;)
    {
        GetToken( &lexer, &token );
        if( token.type != prev_token.type )
        {
            tokens_[num] = token;
            prev_token = token;
            num++;
            if(num >= max_num)
            {
                max_num *= 2;
                Token* tokens_tmp = new Token[max_num];
                assert(tokens_tmp);
                for(int i = 0; i < num; i++) tokens_tmp[i] = tokens_[i];
                if(tokens_ != tokens__) delete tokens_;
                tokens_ = tokens_tmp;
            }
        }
        if( token.type == TOKEN_END ) break;
    }

    SetMap(old_map, tokens_, num);

    assert(*old_map <= TOKEN_END);

    if(tokens_ != tokens__) delete tokens_;
    return 0;
}


int ParseTextEnd(ClientData, Tcl_Interp *interp,
              int, char**)
{
    Token tokens__[MAX_TOKNS] = { TOKEN_END, 0 };
    Token* tokens_ = tokens__;
    int num = 0;
    int max_num = MAX_TOKNS;
    
    Tcl_Eval(interp, "$CVEnv::curframe get 1.0 end");

    int len = strlen(interp->result);
    if(!len) return 0;
    char* text = new char[len + 1];
    assert(text);
    char* map  = new char[len + 1];
    assert(map);

    strcpy(text, interp->result);

    if(old_text && !strcmp(text, old_text)) goto end;

    {
    if(!old_text) {old_text = new char[1]; *old_text = 0;}
    if(!old_map) {old_map = new char[1]; *old_map = TOKEN_END;}

    assert(*old_map <= TOKEN_END);

    Lexer lexer;
    Token* tokens = tokens_;
    Token token;
    Token prev_token = { TOKEN_END, 0 };

    InitLexer( &lexer, text );
    lexer.pos = 0;

    for(num = 0;;)
    {
        GetToken( &lexer, &token );
        if( token.type != prev_token.type )
        {
            tokens_[num] = token;
            prev_token = token;
            num++;
            if(num >= max_num)
            {
                max_num *= 2;
                Token* tokens_tmp = new Token[max_num];
                assert(tokens_tmp);
                for(int i = 0; i < num; i++) tokens_tmp[i] = tokens_[i];
                if(tokens_ != tokens__) delete tokens_;
                tokens_ = tokens_tmp;
            }
        }
        if( token.type == TOKEN_END ) break;
    }

    assert(*old_map <= TOKEN_END);

    int len = strlen(text);
    int old_len = strlen(old_text);

    SetMap(map, tokens_, num);
    // finding first & last changed tokens
    int first;
    int last;
    for(first = 0; map[first] == old_map[first]; first++);
    for(last = len - 1; map[last] == old_map[max(0, last + (old_len - len))]; last--);

    if(first > last) swap(first, last);

    int first_t = GetTokenFromPos(first, tokens_, num);
    int last_t = GetTokenFromPos(last, tokens_, num);

    if(first == len)
        goto end2;

    char command[1000];

    char* normal  = new char[len * strlen("\"0.0 + 0000000 chars\" \"0.0 + 0000000 chars\" ")];
    char* comment = new char[len * strlen("\"0.0 + 0000000 chars\" \"0.0 + 0000000 chars\" ")];
    char* strng  = new char[len * strlen("\"0.0 + 0000000 chars\" \"0.0 + 0000000 chars\" ")];
    char* keyword = new char[len * strlen("\"0.0 + 0000000 chars\" \"0.0 + 0000000 chars\" ")];
    char* number  = new char[len * strlen("\"0.0 + 0000000 chars\" \"0.0 + 0000000 chars\" ")];

    assert( normal && comment && strng && keyword && number );
    strcpy( normal, "$CVEnv::curframe tag add normal " );
    strcpy( comment, "$CVEnv::curframe tag add comment " );
    strcpy( strng, "$CVEnv::curframe tag add string " );
    strcpy( keyword, "$CVEnv::curframe tag add keyword " );
    strcpy( number, "$CVEnv::curframe tag add number " );

    sprintf(command, "ClearColors %d %d $CVEnv::curframe", first, last);
    Tcl_Eval(interp, command);
    assert(*interp->result == 0);

    tokens = tokens_;
    for( int t = first_t; t <=last_t; t++ )
    {
        char pos[60];
        sprintf(pos, "\"0.0 + %d chars\" \"0.0 + %d chars\" ", tokens[t].start, tokens[t + 1].start);
        switch(tokens[t].type)
        {
        case TOKEN_COMMENT:
            strcat(comment, pos);
            break;
        case TOKEN_STRING:
            strcat(strng, pos);
            break;
        case TOKEN_KEYWORD:
            strcat(keyword, pos);
            break;
        case TOKEN_NUMBER:
            strcat(number, pos);
            break;
        case TOKEN_END:
            goto end2;
            break;
        default:
            strcat(normal, pos);
            break;
        }
    }
    if(strlen(normal) > 34)
    {
        Tcl_Eval(interp, normal);
        assert(*interp->result == 0);
    }
    if(strlen(comment) > 34)
    {
        Tcl_Eval(interp, comment);
        assert(*interp->result == 0);
    }
    if(strlen(strng) > 34)
    {
        Tcl_Eval(interp, strng);
        assert(*interp->result == 0);
    }
    if(strlen(number) > 34)
    {
        Tcl_Eval(interp, number);
        assert(*interp->result == 0);
    }
    if(strlen(keyword) > 34)
    {
        Tcl_Eval(interp, keyword);
        assert(*interp->result == 0);
    }

    delete normal;
    delete comment;
    delete strng;
    delete keyword;
    delete number;
    }
end2:
    if(old_map) delete old_map;
    old_map = map;
end:
    if(old_text) delete old_text;
    old_text = text;
    if(tokens_ != tokens__) delete tokens_;
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// color's function
//

bool LoadColors(Tcl_Interp *pinterp, const char* colorsfile)
{
    int code = Tcl_EvalFile(pinterp, (char*)colorsfile);
    if (code != TCL_OK)
                    return false;

    return true;
}

bool SaveColors(Tcl_Interp *pinterp, const char* colorsfile)
{
    FILE* pfile  = fopen(colorsfile, "w");
    if (pfile == NULL) 
        return false;

    fprintf( pfile, "# Custom Colors\n");
    fprintf( pfile, "set ::EditorTextbg ");
    fprintf( pfile, "%s\n",Tcl_GetVar(pinterp, "EditorTextbg", TCL_GLOBAL_ONLY));
    fprintf( pfile, "set ::EditorTextfg ");
    fprintf( pfile, "%s\n",Tcl_GetVar(pinterp, "EditorTextfg", TCL_GLOBAL_ONLY));
    fprintf( pfile, "set ::EditorStringfg ");
    fprintf( pfile, "%s\n",Tcl_GetVar(pinterp, "EditorStringfg", TCL_GLOBAL_ONLY));
    fprintf( pfile, "set ::EditorNumberfg ");
    fprintf( pfile, "%s\n",Tcl_GetVar(pinterp, "EditorNumberfg", TCL_GLOBAL_ONLY));
    fprintf( pfile, "set ::EditorCommentfg ");
    fprintf( pfile, "%s\n",Tcl_GetVar(pinterp, "EditorCommentfg", TCL_GLOBAL_ONLY));
    fprintf( pfile, "set ::EditorKeywordfg ");
    fprintf( pfile, "%s\n",Tcl_GetVar(pinterp, "EditorKeywordfg", TCL_GLOBAL_ONLY));
    fprintf( pfile, "set ::EditorSelectbg ");
    fprintf( pfile, "%s\n",Tcl_GetVar(pinterp, "EditorSelectbg", TCL_GLOBAL_ONLY));
    fprintf( pfile, "set ::EditorSelectfg ");
    fprintf( pfile, "%s\n",Tcl_GetVar(pinterp, "EditorSelectfg", TCL_GLOBAL_ONLY));
    fprintf( pfile, "set ::EditorCursorbg ");
    fprintf( pfile, "%s\n",Tcl_GetVar(pinterp, "EditorCursorbg", TCL_GLOBAL_ONLY));

    fprintf( pfile, "# Custom Fonts\n");
    fprintf( pfile, "set ::EditorTextfont \"");
    fprintf( pfile, "%s\"\n",Tcl_GetVar(pinterp, "EditorTextfont", TCL_GLOBAL_ONLY));
    fprintf( pfile, "set ::EditorStringfont \"");
    fprintf( pfile, "%s\"\n",Tcl_GetVar(pinterp, "EditorStringfont", TCL_GLOBAL_ONLY));
    fprintf( pfile, "set ::EditorNumberfont \"");
    fprintf( pfile, "%s\"\n",Tcl_GetVar(pinterp, "EditorNumberfont", TCL_GLOBAL_ONLY));
    fprintf( pfile, "set ::EditorCommentfont \"");
    fprintf( pfile, "%s\"\n",Tcl_GetVar(pinterp, "EditorCommentfont", TCL_GLOBAL_ONLY));
    fprintf( pfile, "set ::EditorKeywordfont \"");
    fprintf( pfile, "%s\"\n",Tcl_GetVar(pinterp, "EditorKeywordfont", TCL_GLOBAL_ONLY));

    fclose(pfile);
    
    return true;
}
