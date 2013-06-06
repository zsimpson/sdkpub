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

#include "cvtest.h"
#include "cv.hpp"

#ifdef WIN32

static char* funcName  = "Constructors/Destructors and all other functions";
static char* testName  = "CvTree class";
static char* testClass = "Algorithm";

template <class Val, class Idx> static int check_balance( _CvTreeNode<Val,Idx>* root )
{
    if( root == 0 ) return 0;

    int left = check_balance( root->link[0] );
    int right = check_balance( root->link[1] );

    if( left < 0 || right < 0 ) return -1;

    switch( left - right )
    {
    case 0:
        if( root->balance != _CvTreeNode<Val,Idx>::center )
        {
            trsWrite( ATS_CON | ATS_LST,
                      "Wrong balance: act: %d   exp:2\n",
                      root->balance );
            return -1;
        }
        break;
    case 1:
        if( root->balance != _CvTreeNode<Val,Idx>::left )
        {
            trsWrite( ATS_CON | ATS_LST,
                      "Wrong balance: act: %d   exp:0\n",
                      root->balance );
            return -1;
        }
        break;
    case -1:
        if( root->balance != _CvTreeNode<Val,Idx>::right )
        {
            trsWrite( ATS_CON | ATS_LST,
                      "Wrong balance: act: %d   exp:1\n",
                      root->balance );
            return -1;
        }
        break;
    default:
            trsWrite( ATS_CON | ATS_LST,
                      "Wrong balance\n" );
            return -1;
    }

    return 1 + (left > right ? left : right);
}

template <class Val, class Idx> static int check_direct( _CvTreeNode<Val,Idx>* root )
{
    if( root == 0 ) return TRS_OK;

    int res = TRS_OK;

    if( root->link[_CvTreeNode<Val,Idx>::left] != 0 )
    {
        if( root->link[_CvTreeNode<Val,Idx>::left]->idx > root->idx )
        {
            trsWrite( ATS_CON | ATS_LST,
                "Wrong direct: act: left,  exp: right, %d\n",
                (int)root->idx );
            res = TRS_FAIL;
        }
        if( root->link[_CvTreeNode<Val,Idx>::left]->idx == root->idx )
        {
            trsWrite( ATS_CON | ATS_LST,
                "Wrong direct: act: left,  exp: no_branch, %d\n",
                (int)root->idx );
            res = TRS_FAIL;
        }
        if( root->link[_CvTreeNode<Val,Idx>::left]->link[_CvTreeNode<Val,Idx>::up] != root )
        {
            trsWrite( ATS_CON | ATS_LST, "Wrong link (left branch), %d\n", (int)root->idx );
            res = TRS_FAIL;
        }
    }

    if( root->link[_CvTreeNode<Val,Idx>::right] != 0 )
    {
        if( root->link[_CvTreeNode<Val,Idx>::right]->idx < root->idx )
        {
            trsWrite( ATS_CON | ATS_LST,
                "Wrong direct: act: right,  exp: left, %d\n",
                (int)root->idx );
            res = TRS_FAIL;
        }
        if( root->link[_CvTreeNode<Val,Idx>::right]->idx == root->idx )
        {
            trsWrite( ATS_CON | ATS_LST,
                "Wrong direct: act: right,  exp: no_branch, %d\n",
                (int)root->idx );
            res = TRS_FAIL;
        }

        if( root->link[_CvTreeNode<Val,Idx>::right]->link[_CvTreeNode<Val,Idx>::up] != root)
        {
            trsWrite( ATS_CON | ATS_LST,
                "Wrong link (right branch), %d\n",
                (int)root->idx );
            res = TRS_FAIL;
        }
    }

    if( res != TRS_OK ) return res;

    if( check_direct( root->link[_CvTreeNode<Val,Idx>::left] ) != TRS_OK ||
        check_direct( root->link[_CvTreeNode<Val,Idx>::right] ) != TRS_OK )
        return TRS_FAIL;
    else return TRS_OK;
}


/****************************************************************************************\
*                                 Main Test function                                     *
\****************************************************************************************/
const int hsize = 1023;

template <class Val, class Idx> static int foaCvTree( Val, Idx )
{
    CvTree<Val, Idx> tree;
    int res = TRS_OK;

    /* Check adding new node (operator[]) */
    for( Idx i = 0; i < hsize; i++ )
    {
        Idx num = (Idx)atsInitRandom( 0, hsize );
        tree[num] = (Val)i;
        if( check_direct( tree.get_root() ) != TRS_OK ||
            check_balance( tree.get_root() ) < 0 )
        {
            return trsResult( TRS_FAIL, "Error adding new node" );
        }
    }

    /* Check getting node */
    for( i = 0; i < hsize; i++ ) tree[i] = (Val)i;

    for( i = 0; i < hsize; i++ ) if( tree[i] != (Val)i )
    {
        trsWrite( ATS_CON | ATS_LST, "error operator[] (get node)\n" );
        res = TRS_FAIL;
        break;
    }
    for( i = 0; i < hsize; i++ ) if( tree.query(i) != (Val)i )
    {
        trsWrite( ATS_CON | ATS_LST, "error query() function\n" );
        res = TRS_FAIL;
        break;
    }

    tree.clear();
    for( i = 0; i < hsize; i++ ) tree[i] = (Val)i;

    for( i = 0; i < hsize; i++ )
    {
        Idx num = (Idx)atsInitRandom( 0, hsize );
        tree.remove( num );
        if( check_direct( tree.get_root() ) != TRS_OK ||
            check_balance( tree.get_root() ) < 0 )
        {
            return trsResult( TRS_FAIL, "Error removing node" );
        }
        if( tree.query( num ) != 0 )
        {
            trsWrite( ATS_CON | ATS_LST, "Error remove() function (not null) \n" );
            res = TRS_FAIL;
        }
    }

    for( i = 0; i < hsize / 2; i++ )
    {
        tree.remove( i );
        if( check_direct( tree.get_root() ) != TRS_OK ||
            check_balance( tree.get_root() ) < 0 )
        {
            return trsResult( TRS_FAIL, "Error removing node" );
        }
        if( tree.query( i ) != 0 )
        {
            trsWrite( ATS_CON | ATS_LST, "Error remove() function (not null) \n" );
            res = TRS_FAIL;
        }
    }

    for( i = hsize; i > hsize / 2 - 1; i-- )
    {
        tree.remove( i );
        if( check_direct( tree.get_root() ) != TRS_OK ||
            check_balance( tree.get_root() ) < 0 )
        {
            return trsResult( TRS_FAIL, "Error removing node" );
        }
        if( tree.query( i ) != 0 )
        {
            trsWrite( ATS_CON | ATS_LST, "Error remove() function (not null) \n" );
            res = TRS_FAIL;
        }
    }

    tree.clear();

    for( i = 0; i < hsize; i++ ) tree[i] = (Val)(i + 1);
    CvTree<Val, Idx>::iterator iterator = tree.begin();
    if( *iterator != 1 )
    {
        trsWrite( ATS_CON | ATS_LST, "Wrong begin() function (bad val)\n");
        res = TRS_FAIL;
    }
    if( iterator.get_idx() != 0 )
    {
        trsWrite( ATS_CON | ATS_LST, "Wrong begin() function (bad idx)\n");
        res = TRS_FAIL;
    }

    iterator = tree.end();
    if( *iterator != hsize )
    {
        trsWrite( ATS_CON | ATS_LST, "Wrong end() function (bad val)\n");
        res = TRS_FAIL;
    }
    if( iterator.get_idx() != hsize - 1 )
    {
        trsWrite( ATS_CON | ATS_LST, "Wrong end() function (bad idx)\n");
        res = TRS_FAIL;
    }

    CvTree<Val, Idx> empty;
    empty = tree;

    CvTree<Val, Idx>::iterator beg1 = empty.begin();
    CvTree<Val, Idx>::iterator beg2 = tree.begin();
    CvTree<Val, Idx>::iterator end = tree.begin();

    while( beg2 != end )
    {
        if( *beg2 != *beg1 )
        {
            res = TRS_FAIL;
            trsWrite( ATS_CON | ATS_LST, "Wrong operator= (bad value)\n" );
            break;
        }
        if( beg2.get_idx() != beg1.get_idx() )
        {
            res = TRS_FAIL;
            trsWrite( ATS_CON | ATS_LST, "Wrong operator= (bad idx)\n" );
            break;
        }
        beg1++;
        beg2++;
    }
    if( *beg2 != *beg1 )
    {
        res = TRS_FAIL;
        trsWrite( ATS_CON | ATS_LST, "Wrong operator= (bad value)\n" );
    }
    if( beg2.get_idx() != beg1.get_idx() )
    {
        res = TRS_FAIL;
        trsWrite( ATS_CON | ATS_LST, "Wrong operator= (bad idx)\n" );
    }

    return res;
}


#define INT   0
#define FLOAT 1
#define SHORT 2

static int foaCvTreeType( void* param )
{
    int Param = (int)param;
    switch (Param)
    {
    case INT:
        return foaCvTree( (int) 1, (int)2 );
    case FLOAT:
        return foaCvTree( (float) 1, (int)2 );
    case SHORT:
        return foaCvTree( (short) 1, (int)2 );
    default:
        return trsResult( TRS_FAIL, "Wrong parameter" );
    }
}

void InitATree()
{
    trsRegArg( funcName, testName, testClass, foaCvTreeType, INT   );
    trsRegArg( funcName, testName, testClass, foaCvTreeType, FLOAT );
    trsRegArg( funcName, testName, testClass, foaCvTreeType, SHORT );
    return;
}
#else
void InitATree()
{
}
#endif /* WIN32 */

/* End of file. */
