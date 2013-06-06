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

#define __COLLECTION__
#include "time.h"

#define _CV_LINE_PUTSTARTPT 0x1
#define _CV_LINE_PUTENDPT   0x2

#define _MAX_BUFF_SIZE__  10

#define PI() (acos(-1))

/*****************************************************************************/
/*                          Secondaty function                               */
/*****************************************************************************/

double GetVald( double MaxVal, double Dispacement = 0. )
{
    ///////
    static double buff[ _MAX_BUFF_SIZE__ ];
    static bool   first = true;
    ///////
    bool   flag;
    double val = 0;
    int i;

    srand( (unsigned)time( NULL ) );

    srand( (unsigned)time( NULL ) );
    flag = true;
    while( flag )
    {
        val  = (double)rand() * MaxVal / RAND_MAX;
        val += Dispacement;

        if( first )
        {
            flag = false;
            first = false;
            for( i = 0 ; i < _MAX_BUFF_SIZE__ ; i++ )
            {
                buff[i] = static_cast<int>(val);
            }
        }
        else
        {
            flag = false;
            for( i = 0 ; i < _MAX_BUFF_SIZE__ ; i++ )
            {
                if( buff[i] == val ) flag = true;
            }
        }
    }

    for( i = _MAX_BUFF_SIZE__ - 1; i > 0 ; i-- )
    {
        buff[ i ] = buff[ i - 1 ];
    }

    buff[0] = static_cast<int>(val);
    return val;
} // double GetVald( double MaxVal, double Dispacement = 0. )

int GetVali( double MaxVal, double Dispacement = 0. )
{
    ////////
    static int buff[ _MAX_BUFF_SIZE__ ];
    static bool   first = true;
    static int    maxloop = 1000;
    ////////
    bool   flag;
    double val = 0;
    int i;

    srand( (unsigned)time( NULL ) );
    flag = true;
    int loop = maxloop;
    while( flag & ( loop != 0 ) )
    {
        loop--;
        val  = (  (double)rand() * MaxVal ) / (double)RAND_MAX;
        val += Dispacement;

        if( first )
        {
            flag = false;
            first = false;
            for( i = 0 ; i < _MAX_BUFF_SIZE__ ; i++ )
            {
                buff[i] = static_cast<int>(val);
            }
        }
        else
        {
            flag = false;
            for( i = 0 ; i < _MAX_BUFF_SIZE__ ; i++ )
            {
                if( buff[i] == static_cast<int>(val) ) flag = true;
            }
        }
    }

    for( i = _MAX_BUFF_SIZE__ - 1; i > 0 ; i-- )
    {
        buff[ i ] = buff[ i - 1 ];
    }

    buff[0] = static_cast<int>(val);

    return static_cast<int>(val);
} // GetVali( double MaxVal, double Dispacement = 0. )


bool CreateContour( CvSeq** ppSeq, int flags, 
                    CvMemStorage** ppStorage )
{
    ///////////////////////
    if( (ppSeq == NULL) || (ppStorage==NULL) )
    {
        return false;
    } // if( (ppSeq == NULL) || (ppStorage==NULL) || (pWriter==NULL) )

    ///////////////////////

    *ppSeq = cvCreateSeq( flags, sizeof(CvContour), sizeof(CvPoint), *ppStorage);
    if( *ppSeq == NULL )
    {
        return false;
    } // if( *ppSeq == NULL )

    return true;
} // CreateContour


void Line( CvPoint StartPt, CvPoint EndPt, CvSeq* Seq,
           int flags = _CV_LINE_PUTSTARTPT | _CV_LINE_PUTENDPT )
{
    //////////////// variables ///////////////
    CvPoint Pt;
    int dx = abs( StartPt.x - EndPt.x );
    int dy = abs( StartPt.y - EndPt.y );
    int sx = ( ( StartPt.x > EndPt.x ) ? -1 : 1 );
    int sy = ( ( StartPt.y > EndPt.y ) ? -1 : 1 );
    int x, y;
    int d, d1, d2;
    int i;

    ////////////// put start point //////////////////
    if( flags & _CV_LINE_PUTSTARTPT )
    {
        cvSeqPush( Seq, &StartPt );
    }

    /////////// drow line ///////////////////
    if( dy < dx )
    {
        d2 = 2*( dy - dx );
        d1 = 2*dy;
        d  = d1 - dx;
        
        for( x = StartPt.x, y = StartPt.y, i=1; i < dx ; i++ )
        {
            if( d > 0 )
            {
                d += d2;
                y += sy;
            } // if( d > 0 )
            else
            {
                d += d1;
            } // if( d > 0 ) else

            x += sx;
            Pt.x = x;
            Pt.y = y;
            cvSeqPush( Seq, &Pt );
        }
    } // if( dy < dx )
    else
    {
        d2 = 2*( dx - dy );
        d1 = 2*dx;
        d  = d1 - dy;

        for( y = StartPt.y, x = StartPt.x, i=1; i < dy ; i++ )
        {
            if( d > 0 )
            {
                d += d2;
                x += sx;
            } // if( d > 0 )
            else
            {
                d += d1;
            } // if( d > 0 ) else

            y += sy;
            Pt.x = x;
            Pt.y = y;
            cvSeqPush( Seq, &Pt );
        } // for( y = StartPt.y, x = StartPt.x, i=1; i < dy ; i++ )
    } // if( dy < dx ) else
    
    //////////////  put end point //////////////////
    if( flags & _CV_LINE_PUTENDPT )
    {
            cvSeqPush( Seq, &EndPt );
    } // if( flags & _CV_LINE_PUTENDPT )

    return;
} // Line

/*****************************************************************************/
/*****************************************************************************/
/***                          Collection                                   ***/
/*****************************************************************************/
/*****************************************************************************/

/****************************************************************/
/****************       PolyLine        *************************/
/****************************************************************/
CvSeq* PolyLine( CvMemStorage* Storage )
{
    ///////////////////////
    int Max_dY = 50;
    int Max_dX = 50;
    int Max_Piece = 100;
    //////
    CvPoint FirstPt,SecondPt;
    int x,y;
    int P;
    /////
    CvSeq*        Seq     = NULL;

    ///////////// create contour //////////
    if( !CreateContour( &Seq,CV_SEQ_POLYGON,&Storage) )
    {
        return NULL;
    }
    
    /////////////// initialising /////////
    P = GetVali( Max_Piece );

    FirstPt.x = FirstPt.y = 0;
    cvSeqPush( Seq, &FirstPt );

    ////////// make contour ////////////
    for( int i = 0 ; i < P ; i++ )
    {
        x = y = 0;
        while( ( x == 0 ) || ( y == 0 ) )
        {
            x = GetVali( Max_dX );
            y = GetVali( Max_dY );
        }

        SecondPt.x = FirstPt.x;
        SecondPt.y = FirstPt.y;
        FirstPt.x += x;
        FirstPt.y += y;
        Line( SecondPt,FirstPt,Seq,_CV_LINE_PUTENDPT);
    }
    
    //////////////////////////

    return Seq;
} // CvSeq* PolyLine()

/****************************************************************/
/****************        arc cos        *************************/
/****************************************************************/
CvSeq* arccos( CvMemStorage* Storage )
{
    /////
    int X_Mul_Max = 10;
    int Y_Mul_Max = 10;
    /////
    int Y_Mul = 1;
    int X_Mul = 1;
    double displacement = 0.1;
    double interval     = 10;
    double t, t_step;
    /////
    CvPoint FirstPt, SecondPt;
    /////
    CvSeq*        Seq     = NULL;

    ///////////// create contour //////////
    if( !CreateContour( &Seq,CV_SEQ_POLYGON,&Storage) )
    {
        return NULL;
    }

    /////////////// initialising /////////
    t_step = 0;
    while( t_step == 0. )
    {
        Y_Mul = GetVali( Y_Mul_Max ,1);
        X_Mul = GetVali( X_Mul_Max ,1);

        interval = GetVald( 2 * PI()  );
        displacement = GetVald( 2 * PI() - interval );

        t_step = (int)( interval * X_Mul );
        t_step = interval / t_step;
    }

    //////////// create contour //////////////////////////
    FirstPt.x = static_cast<int>( displacement * X_Mul );
    FirstPt.y = static_cast<int>( acos( displacement ) * Y_Mul );
    cvSeqPush( Seq, &FirstPt );

    for( t = displacement - PI() ; t < interval + displacement ; t += t_step )
    {
        SecondPt.x = FirstPt.x;
        SecondPt.y = FirstPt.y;

        FirstPt.x = static_cast<int>( t * X_Mul );
        FirstPt.y = static_cast<int>( acos( t ) * Y_Mul );

        Line( SecondPt,FirstPt,Seq,_CV_LINE_PUTENDPT);
    }

    return Seq;
} //CvSeq* arccos()

/****************************************************************/
/****************        arc tangent    *************************/
/****************************************************************/
CvSeq* arctan( CvMemStorage* Storage )
{
    /////
    int X_Mul_Max = 5;
    int Y_Mul_Max = 5;
    /////
    int Y_Mul = 1;
    int X_Mul = 1;
    double displacement = 0.1;
    double interval     = 0.1;
    double t, t_step;
    /////
    CvPoint FirstPt, SecondPt;
    /////
    CvSeq*        Seq     = NULL;

    ///////////// create contour //////////
    if( !CreateContour( &Seq,CV_SEQ_POLYGON,&Storage) )
    {
        return NULL;
    }

    /////////////// initialising /////////
    t_step = 0;
    while( t_step == 0. )
    {
        Y_Mul = GetVali( Y_Mul_Max ,1);
        X_Mul = GetVali( X_Mul_Max ,1);

        interval = GetVald( 2 * PI() -0.1, 0.1 );
        displacement = GetVald( 2 * PI() - interval - 0.1, 0.1);

        t_step = (int)( interval * X_Mul );
        t_step = interval / t_step;
    }

    //////////// create contour //////////////////////////
    FirstPt.x = static_cast<int>( displacement * X_Mul );
    FirstPt.y = static_cast<int>( atan( displacement ) * Y_Mul );
    cvSeqPush( Seq, &FirstPt );

    for( t = displacement - PI() ; t < interval + displacement ; t += t_step )
    {
        SecondPt.x = FirstPt.x;
        SecondPt.y = FirstPt.y;

        FirstPt.x = static_cast<int>( t * X_Mul );
        FirstPt.y = static_cast<int>( atan( t ) * Y_Mul );

        Line( SecondPt,FirstPt,Seq,_CV_LINE_PUTENDPT);
    }

    return Seq;
} // CvSeq* arctan()

/****************************************************************/
/****************   hyperbolic cosine   *************************/
/****************************************************************/
CvSeq* ch( CvMemStorage* Storage )
{
    /////
    int Max_Interval = 5;
    /////
    double displacement = 0.1;
    double interval     = 0.1;
    double t;
    /////
    CvPoint FirstPt, SecondPt;
    /////
    CvSeq*        Seq     = NULL;

    ///////////// create contour //////////
    if( !CreateContour( &Seq,CV_SEQ_POLYGON,&Storage) )
    {
        return NULL;
    }

    /////////////// initialising /////////

    interval = GetVald( 2 * Max_Interval );
    displacement = GetVald( 2 * Max_Interval - interval );

    //////////// create contour //////////////////////////
    FirstPt.x = static_cast<int>( displacement  );
    FirstPt.y = static_cast<int>( cosh( displacement )  );
    cvSeqPush( Seq, &FirstPt );

    for( t = displacement - Max_Interval; t < interval + displacement ; t++ )
    {
        SecondPt.x = FirstPt.x;
        SecondPt.y = FirstPt.y;

        FirstPt.x = static_cast<int>( t  );
        FirstPt.y = static_cast<int>( cosh( t )  );

        Line( SecondPt,FirstPt,Seq,_CV_LINE_PUTENDPT);
    }

    return Seq;
} // CvSeq* ch()


/****************************************************************/
/****************           exp         *************************/
/****************************************************************/
CvSeq* Exp( CvMemStorage* Storage )
{
    /////
    int X_Mul_Max = 5;
    int Y_Mul_Max = 5;
    int Max_Interval = 1;
    /////
    int Y_Mul = 1;
    int X_Mul = 1;
    double displacement = 0.1;
    double interval     = 0.1;
    double t, t_step;
    /////
    CvPoint FirstPt, SecondPt;
    /////
    CvSeq*        Seq     = NULL;

    ///////////// create contour //////////
    if( !CreateContour( &Seq,CV_SEQ_POLYGON,&Storage) )
    {
        return NULL;
    }

    /////////////// initialising /////////
    t_step = 0;
    while( t_step == 0. )
    {
        Y_Mul = GetVali( Y_Mul_Max ,1);
        X_Mul = GetVali( X_Mul_Max ,1);

        interval = GetVald( 2 * Max_Interval );
        displacement = GetVald( 2 * Max_Interval - interval );

        t_step = (int)( interval * X_Mul );
        t_step = interval / t_step;
    }

    //////////// create contour //////////////////////////
    FirstPt.x = static_cast<int>( displacement * X_Mul );
    FirstPt.y = static_cast<int>( exp( displacement ) * Y_Mul );
    cvSeqPush( Seq, &FirstPt );

    for( t = displacement - Max_Interval ; t < interval + displacement ; t += t_step )
    {
        SecondPt.x = FirstPt.x;
        SecondPt.y = FirstPt.y;

        FirstPt.x = static_cast<int>( t * X_Mul );
        FirstPt.y = static_cast<int>( exp( t ) * Y_Mul );

        Line( SecondPt,FirstPt,Seq,_CV_LINE_PUTENDPT);
    }

    return Seq;
} // CvSeq* Exp()

/****************************************************************/
/****************           floor       *************************/
/****************************************************************/
CvSeq* Floor( CvMemStorage* Storage )
{
    /////
    int X_Mul_Max = 5;
    int Y_Mul_Max = 5;
    int Max_Interval = 10;
    /////
    int Y_Mul = 1;
    int X_Mul = 1;
    double displacement = 0.1;
    double interval     = 0.1;
    double t, t_step;
    /////
    CvPoint FirstPt, SecondPt;
    /////
    CvSeq*        Seq     = NULL;

    ///////////// create contour //////////
    if( !CreateContour( &Seq,CV_SEQ_POLYGON,&Storage) )
    {
        return NULL;
    }

    /////////////// initialising /////////
    t_step = 0;
    while( t_step == 0. )
    {
        Y_Mul = GetVali( Y_Mul_Max ,1);
        X_Mul = GetVali( X_Mul_Max ,1);

        interval = GetVald( 2 * Max_Interval );
        displacement = GetVald( 2 * Max_Interval - interval );

        t_step = (int)( interval * X_Mul );
        t_step = interval / t_step;
    }

    //////////// create contour //////////////////////////
    FirstPt.x = static_cast<int>( displacement * X_Mul );
    FirstPt.y = static_cast<int>( floor( displacement ) * Y_Mul );
    cvSeqPush( Seq, &FirstPt );

    for( t = displacement - Max_Interval ; t < interval + displacement ; t += t_step )
    {
        SecondPt.x = FirstPt.x;
        SecondPt.y = FirstPt.y;

        FirstPt.x = static_cast<int>( t * X_Mul );
        FirstPt.y = static_cast<int>( floor( t ) * Y_Mul );

        Line( SecondPt,FirstPt,Seq,_CV_LINE_PUTENDPT);
    }

    return Seq;
} // CvSeq* Floor()

/****************************************************************/
/****************           log         *************************/
/****************************************************************/
CvSeq* Log( CvMemStorage* Storage )
{
    /////
    int X_Mul_Max = 10;
    int Y_Mul_Max = 10;
    int Max_Interval = 6;
    /////
    int Y_Mul = 3;
    int X_Mul = 3;
    double displacement = 2;
    double interval     = 1;
    double t, t_step;
    /////
    CvPoint FirstPt, SecondPt;
    /////
    CvSeq*        Seq     = NULL;

    ///////////// create contour //////////
    if( !CreateContour( &Seq,CV_SEQ_POLYGON, &Storage) )
    {
        return NULL;
    }

    /////////////// initialising /////////
    t_step = 0;
    while( ( t_step == 0.) || ( displacement == 0. ) )
    {
        Y_Mul = GetVali( Y_Mul_Max ,1);
        X_Mul = GetVali( X_Mul_Max ,1);

        interval = GetVald( Max_Interval );
        displacement = GetVald( Max_Interval - interval );

        t_step = (int)( interval * X_Mul );
        t_step = interval / t_step;
    }

    //////////// create contour //////////////////////////
    FirstPt.x = static_cast<int>( displacement * X_Mul );
    FirstPt.y = static_cast<int>( floor( displacement ) * Y_Mul );
    cvSeqPush( Seq, &FirstPt );

    for( t = displacement ; t < interval + displacement ; t += t_step )
    {
        SecondPt.x = FirstPt.x;
        SecondPt.y = FirstPt.y;

        FirstPt.x = static_cast<int>( t * X_Mul );
        FirstPt.y = static_cast<int>( log( t ) * Y_Mul );

        Line( SecondPt,FirstPt,Seq,_CV_LINE_PUTENDPT);
    }

    return Seq;
} // CvSeq* Log()

/****************************************************************/
/****************           Pow         *************************/
/****************************************************************/
CvSeq* Pow( CvMemStorage* Storage )
{
    /////
    int X_Mul_Max = 5;
    int Y_Mul_Max = 5;
    int Max_Interval = 10;
    int Max_Coeff   = 3;
    /////
    int Y_Mul = 1;
    int X_Mul = 1;
    double Coeff        = 1;
    double displacement = 1;
    double interval     = 5;
    double t, t_step;
    /////
    CvPoint FirstPt, SecondPt;
    /////
    CvSeq*        Seq     = NULL;

    ///////////// create contour //////////
    if( !CreateContour( &Seq,CV_SEQ_POLYGON,&Storage) )
    {
        return NULL;
    }

    /////////////// initialising /////////
    t_step = 0;
    while( t_step == 0. )
    {
        Y_Mul = GetVali( Y_Mul_Max ,1);
        X_Mul = GetVali( X_Mul_Max ,1);
        Coeff = GetVald(  Max_Coeff );
        interval = GetVald( Max_Interval );
        displacement = GetVald( Max_Interval - interval );

        t_step = (int)( interval * X_Mul );
        t_step = interval / t_step;
    }

    //////////// create contour //////////////////////////
    FirstPt.x = static_cast<int>( displacement * X_Mul );
    FirstPt.y = static_cast<int>( pow( displacement , Coeff ) * Y_Mul );
    cvSeqPush( Seq, &FirstPt );

    for( t = displacement ; t < interval + displacement ; t += t_step )
    {
        SecondPt.x = FirstPt.x;
        SecondPt.y = FirstPt.y;

        FirstPt.x = static_cast<int>( t * X_Mul );
        FirstPt.y = static_cast<int>( pow( t , Coeff ) * Y_Mul );

        Line( SecondPt,FirstPt,Seq,_CV_LINE_PUTENDPT);
    }

    return Seq;
} // CvSeq* Pow()


/****************************************************************/
/****************           Sin         *************************/
/****************************************************************/
CvSeq* Sin( CvMemStorage* Storage )
{
    /////
    int X_Mul_Max = 5;
    int Y_Mul_Max = 5;
    int Max_Interval = 10;
    /////
    int Y_Mul = 1;
    int X_Mul = 1;
    double displacement = 0.5;
    double interval     = 3;
    double t, t_step;
    /////
    CvPoint FirstPt, SecondPt;
    /////
    CvSeq*        Seq     = NULL;

    ///////////// create contour //////////
    if( !CreateContour( &Seq,CV_SEQ_POLYGON,&Storage) )
    {
        return NULL;
    }

    /////////////// initialising /////////
    t_step = 0;
    while( t_step == 0. )
    {
        Y_Mul = GetVali( Y_Mul_Max ,1);
        X_Mul = GetVali( X_Mul_Max ,1);
        interval = GetVald( Max_Interval );
        displacement = GetVald( Max_Interval - interval );

        t_step = (int)( interval * X_Mul );
        t_step = interval / t_step;
    }

    //////////// create contour //////////////////////////
    FirstPt.x = static_cast<int>( displacement * X_Mul );
    FirstPt.y = static_cast<int>( sin( displacement ) * Y_Mul );
    cvSeqPush( Seq, &FirstPt );

    for( t = displacement ; t < interval + displacement ; t += t_step )
    {
        SecondPt.x = FirstPt.x;
        SecondPt.y = FirstPt.y;

        FirstPt.x = static_cast<int>( t * X_Mul );
        FirstPt.y = static_cast<int>( sin( t ) * Y_Mul );

        Line( SecondPt,FirstPt,Seq,_CV_LINE_PUTENDPT);
    }

    return Seq;
} // CvSeq* Sin()


/****************************************************************/
/****************          Polinom      *************************/
/****************************************************************/
double Pol( double x, double* Coeff, int Max_Power )
{
    double val;

    if( Coeff == NULL )
    {
        assert( false );
        return 0;
    }

    val  = 0;
    for( int i = Max_Power -1 ; i >= 0 ; i-- )
    {
        val *= x;
        val += Coeff[i];
    }

    return val;
} // double Pol( double x, double* Coeff, int Amount )

CvSeq* Polimon( CvMemStorage* Storage )
{
    /////
    int X_Mul_Max = 5;
    int Y_Mul_Max = 5;
    int Max_Interval = 5;
    int Max_Power   = 4;
    int Max_Coeff   = 6;
    //////
    int Power = 0;
    double* Coeff = NULL;
    /////
    int Y_Mul = 1;
    int X_Mul = 1;
    double displacement = 1;
    double interval     = 6;
    double t, t_step;
    /////
    CvPoint FirstPt, SecondPt;
    /////
    CvSeq*        Seq     = NULL;

    ///////////// create contour //////////
    if( !CreateContour( &Seq,CV_SEQ_POLYGON,&Storage) )
    {
        return NULL;
    }

    /////////////// initialising /////////
    Power = GetVali( Max_Power - 1, 1 );

    /////////////// allocating memory ///////////
    Coeff = new double[ Power ];
    if( Coeff == NULL )
    {
        return NULL;
    }
   
    /////////////// initialising /////////
    for( int i = 0 ; i < Power ; i++ )
    {
        Coeff[i] = GetVald( Max_Coeff );
    }

    /////////////// initialising /////////
    t_step = 0;
    while( t_step == 0. )
    {
        Y_Mul = GetVali( Y_Mul_Max ,1);
        X_Mul = GetVali( X_Mul_Max ,1);
        interval = GetVald( Max_Interval );
        displacement = GetVald( Max_Interval - interval );

        t_step = (int)( interval * X_Mul );
        t_step = interval / t_step;
    }

    //////////// create contour //////////////////////////
    FirstPt.x = static_cast<int>( displacement * X_Mul );
    FirstPt.y = static_cast<int>( Pol( displacement, Coeff, Power ) * Y_Mul );
    cvSeqPush( Seq, &FirstPt );

    for( t = displacement ; t < interval + displacement ; t += t_step )
    {
        SecondPt.x = FirstPt.x;
        SecondPt.y = FirstPt.y;

        FirstPt.x = static_cast<int>( t * X_Mul );
        FirstPt.y = static_cast<int>( Pol( t, Coeff, Power ) * Y_Mul );

        Line( SecondPt,FirstPt,Seq,_CV_LINE_PUTENDPT);
    }
    
    delete[] Coeff;
    return Seq;
} // CvSeq* Polimon()


/****************************************************************/
/****************         Ellips        *************************/
/****************************************************************/
CvSeq* Ellips( CvMemStorage* Storage )
{
    /////
    int X_Mul_Max = 8;
    int Y_Mul_Max = 8;
    /////
    int Y_Mul = 2;
    int X_Mul = 2;
    double t, t_step;
    /////
    CvPoint FirstPt, SecondPt;
    /////
    CvSeq*        Seq     = NULL;

    ///////////// create contour //////////
    if( !CreateContour( &Seq,CV_SEQ_POLYGON,&Storage) )
    {
        return NULL;
    }

    /////////////// initialising /////////
    t_step = 0;
    while( t_step == 0. )
    {
        Y_Mul = GetVali( Y_Mul_Max ,1);
        X_Mul = GetVali( X_Mul_Max ,1);

        t_step = 1. / ( X_Mul * Y_Mul );
    }

    //////////// create contour //////////////////////////
    FirstPt.x = static_cast<int>( X_Mul );
    FirstPt.y = static_cast<int>( 0 );
    cvSeqPush( Seq, &FirstPt );

    for( t = 0 ; t < 2 * PI() ; t += t_step )
    {
        SecondPt.x = FirstPt.x;
        SecondPt.y = FirstPt.y;

        FirstPt.x = static_cast<int>( cos( t ) * X_Mul );
        FirstPt.y = static_cast<int>( sin( t ) * Y_Mul );

        Line( SecondPt,FirstPt,Seq,_CV_LINE_PUTENDPT);
    }

    return Seq;
} // CvSeq* Ellips()

/****************************************************************/
/****************  folium of descartes  *************************/
/****************************************************************/
CvSeq* FoliumOfDescartes( CvMemStorage* Storage )
{
    /////
    int X_Mul_Max = 5;
    int Y_Mul_Max = 5;
    int Max_Interval = 10;
    int Max_A  = 5;
    /////
    int Y_Mul = 2;
    int X_Mul = 2;
    double a;
    double displacement = 1;
    double interval     = 5;
    double t, t_step;
    double d;
    /////
    CvPoint FirstPt, SecondPt;
    /////
    CvSeq*        Seq     = NULL;

    ///////////// create contour //////////
    if( !CreateContour( &Seq,CV_SEQ_POLYGON,&Storage) )
    {
        return NULL;
    }

    /////////////// initialising /////////
    a = GetVald( Max_A -0.1 , 0.1 );
    t_step = 0;
    while( ( t_step == 0. ) || ( displacement == -1. ) )
    {
        Y_Mul = GetVali( Y_Mul_Max ,1);
        X_Mul = GetVali( X_Mul_Max ,1);
        interval = GetVald( Max_Interval );                                                                                                                                                                                                                        
        displacement = GetVald( Max_Interval - interval );

        t_step = interval / 500;
    }

    //////////// create contour //////////////////////////
    d = 1 + pow( displacement,3 );
    FirstPt.x = static_cast<int>( X_Mul * (3*a*displacement) / d  );
    FirstPt.y = static_cast<int>( Y_Mul * (3*a*pow(displacement,2) )/ d   );
    cvSeqPush( Seq, &FirstPt );

    for( t = displacement ; t < interval + displacement ; t += t_step )
    {
        if( t == -1 ) continue;

        SecondPt.x = FirstPt.x;
        SecondPt.y = FirstPt.y;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
        d = 1 + pow( t,3 );
        FirstPt.x = static_cast<int>( X_Mul * (3*a*t) / d  );
        FirstPt.y = static_cast<int>( Y_Mul * (3*a*pow(t,2) )/ d   );

        Line( SecondPt,FirstPt,Seq,_CV_LINE_PUTENDPT);
    }
    
    return Seq;
} // CvSeq* FoliumOfDescartes()


/****************************************************************/
/****************       epicycloid      *************************/
/****************************************************************/
CvSeq* Epicycloid( CvMemStorage* Storage )
{
    /////
    int X_Mul_Max = 1;
    int Y_Mul_Max = 1;
    int Max_Interval = 10;
    int Max_A  = 5;
    int Max_B  = 5;
    int Max_L  = 5;
    /////
    int Y_Mul = 2;
    int X_Mul = 2;
    double a = 0,b,l;
    double displacement = 1;
    double interval     = 5;
    double t, t_step;
    double d;
    /////
    CvPoint FirstPt, SecondPt;
    /////
    CvSeq*        Seq     = NULL;

    ///////////// create contour //////////
    if( !CreateContour( &Seq,CV_SEQ_POLYGON,&Storage) )
    {
        return NULL;
    }

    /////////////// initialising /////////
    b = GetVald( Max_B -0.1 , 0.1 );
    l = GetVald( Max_L -0.1 , 0.1 );
    t_step = 0;
    while( ( t_step == 0. ) || ( a == 0. ) )
    {
        Y_Mul = GetVali( Y_Mul_Max ,1);
        X_Mul = GetVali( X_Mul_Max ,1);
        interval = GetVald( Max_Interval );                                                                                                                                                                                                                        
        displacement = GetVald( Max_Interval - interval );

        a = GetVald( Max_A -0.1 , 0.1 );
        t_step = interval / 500;
    }

    //////////// create contour //////////////////////////
    d = a + b;
    FirstPt.x = static_cast<int>( X_Mul * ( d * cos(displacement) - l*a*cos(d*displacement/a)  ) );
    FirstPt.y = static_cast<int>( Y_Mul * ( d * sin(displacement) - l*a*sin(d*displacement/a)  ) );
    cvSeqPush( Seq, &FirstPt );

    for( t = displacement ; t < interval + displacement ; t += t_step )
    {

        SecondPt.x = FirstPt.x;
        SecondPt.y = FirstPt.y;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
        d = a + b;
        FirstPt.x = static_cast<int>( X_Mul * ( d * cos(t) - l*a*cos(d*t/a) ) );
        FirstPt.y = static_cast<int>( Y_Mul * ( d * sin(t) - l*a*sin(d*t/a) ) );

        Line( SecondPt,FirstPt,Seq,_CV_LINE_PUTENDPT);
    }
    
    return Seq;
} // CvSeq* Epicycloid()

/****************************************************************/
/****************       hypocycloid      *************************/
/****************************************************************/
CvSeq* Hypocycloid( CvMemStorage* Storage )
{
    /////
    int X_Mul_Max = 5;
    int Y_Mul_Max = 5;
    int Max_Interval = 5;
    int Max_A  = 5;
    int Max_B  = 5;
    int Max_L  = 5;
    /////
    int Y_Mul = 1;
    int X_Mul = 1;
    double a = 0,b,l;
    double displacement = 0.1;
    double interval     = 0.1;
    double t, t_step;
    double d;
    /////
    CvPoint FirstPt, SecondPt;
    /////
    CvSeq*        Seq     = NULL;

    ///////////// create contour //////////
    if( !CreateContour( &Seq,CV_SEQ_POLYGON,&Storage) )
    {
        return NULL;
    }

    /////////////// initialising /////////
    b = GetVald( Max_B -0.1 , 0.1 );
    l = GetVald( Max_L -0.1 , 0.1 );
    t_step = 0;
    while( ( t_step == 0. ) || ( a == 0. ) )
    {
        Y_Mul = GetVali( Y_Mul_Max ,1);
        X_Mul = GetVali( X_Mul_Max ,1);
        interval = GetVald( Max_Interval );                                                                                                                                                                                                                        
        displacement = GetVald( Max_Interval - interval );

        a = GetVald( Max_A -0.1 , 0.1 );
        t_step = interval / 500;
    }

    //////////// create contour //////////////////////////
    d = a - b;
    FirstPt.x = static_cast<int>( X_Mul * ( d * cos(displacement) - l*a*cos(d*displacement/a)  ) );
    FirstPt.y = static_cast<int>( Y_Mul * ( d * sin(displacement) - l*a*sin(d*displacement/a)  ) );
    cvSeqPush( Seq, &FirstPt );

    for( t = displacement ; t < interval + displacement ; t += t_step )
    {

        SecondPt.x = FirstPt.x;
        SecondPt.y = FirstPt.y;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
        d = a - b;
        FirstPt.x = static_cast<int>( X_Mul * ( d * cos(t) - l*a*cos(d*t/a) ) );
        FirstPt.y = static_cast<int>( Y_Mul * ( d * sin(t) - l*a*sin(d*t/a) ) );

        Line( SecondPt,FirstPt,Seq,_CV_LINE_PUTENDPT);
    }
    
    return Seq;
} // CvSeq* Hypocycloid()


/****************************************************************/
/****************           ___         *************************/
/****************************************************************/
CvSeq* ___( CvMemStorage* Storage )
{
    /////
    int Max_Time = 30;
    int Max_Amplitude  = 5;
    /////
    int t;
    /////
    CvPoint FirstPt, SecondPt;
    /////
    CvSeq*        Seq     = NULL;

    ///////////// create contour //////////
    if( !CreateContour( &Seq,CV_SEQ_POLYGON,&Storage) )
    {
        return NULL;
    }

    /////////////// initialising /////////


    //////////// create contour //////////////////////////
    FirstPt.x = 0;
    FirstPt.y = GetVali( 2 * Max_Amplitude, -Max_Amplitude );
    cvSeqPush( Seq, &FirstPt );

    for( t = 0 ; t < Max_Time ; t++ )
    {

        SecondPt.x = FirstPt.x;
        SecondPt.y = FirstPt.y;

        FirstPt.x = t;

        if( GetVali( 1000 ) < 500 ) 
        {
            cvSeqPush( Seq, &FirstPt );
        }
        else
        {

            FirstPt.y += GetVali( 2 * Max_Amplitude, -Max_Amplitude );
            Line( SecondPt,FirstPt,Seq,_CV_LINE_PUTENDPT);
        }
        
    }
    
    return Seq;
} //
/*****************************************************************************/
/*****************************************************************************/
/***                          Contour table                                ***/
/*****************************************************************************/
/*****************************************************************************/
Contour Contours[] =
{
    PolyLine, 
    arccos,   
    arctan,   
    ch,       
    Exp,      
    Floor,    
    Log,    
    Pow,    
    Sin,    
    Polimon,
    Ellips,    
    FoliumOfDescartes, 
    Epicycloid,  
    Hypocycloid,
    ___,      
    NULL
};

/* End of file. */
