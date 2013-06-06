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

#include  <string.h>
#include  "hash.h"

#define  HASHTABLE_SIZE   2*MAP_SIZE

typedef struct _HashEntry
{
    unsigned  hash;
    int       len;
    struct _HashEntry* next;
    MapEntry* mapentry;
} HashEntry;

HashEntry   keyword_storage[MAP_SIZE];
HashEntry*  keyword_table[HASHTABLE_SIZE];
static int  hash_init = 0;

//-----------------------------------------------------------------------------
unsigned  calc_hash( const char* text, int len )
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


void  InitHashTable( MapEntry* pMap )
{
    if( !hash_init )
    {
        int  i;
        int  count[HASHTABLE_SIZE];

        memset( count, 0, sizeof(count));
        memset( keyword_table, 0, sizeof( keyword_table));

        for( i = 0; pMap[i].element != 0; i++ )
        {
            int idx, len;
            keyword_storage[i].len = len = strlen( pMap[i].element );
            keyword_storage[i].hash = calc_hash( pMap[i].element, len );
            //keyword_storage[i].mapentry->element = pMap[i].element;
			//keyword_storage[i].mapentry->image = pMap[i].image;
			keyword_storage[i].mapentry = pMap + i;
            idx = keyword_storage[i].hash % HASHTABLE_SIZE; 
            keyword_storage[i].next = keyword_table[idx];
            keyword_table[idx] = keyword_storage + i;
            count[idx]++;
        }
        hash_init = 1;
    }
}


MapEntry* FindMapEntry(const char* pccStr)
{
    int len;
	unsigned int hash;
	int idx;
	HashEntry* entry;

	len = strlen(pccStr);

	hash = calc_hash( pccStr, len );
    idx = hash % HASHTABLE_SIZE;
    entry = keyword_table[idx];

    while( entry )
    {
        if( entry->hash == hash &&
            entry->len == len &&
            !strncmp( entry->mapentry->element, pccStr, len )) break;
        entry = entry->next;
    }

    return (entry ? entry->mapentry : 0);
}
//-----------------------------------------------------------------------------