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
#include "SubdivMorpher.h"
#include <malloc.h>
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <math.h>

#define MAX_DIFFERENCE 20
#define COEFF_OCC 30
#define COEFF_MATCH 30
#define COEFF_MATCH_2 64
#define END_OF_PATH 1000000000

#define MAX3(xxx1,xxx2,xxx3) ( ( ( (xxx1) > (xxx2) ) && ( (xxx1) > xxx3 ) ) ? (xxx1) : ( ( (xxx2) > (xxx3) ) ? (xxx2) : (xxx3) ) )
#define MAX2(xxx1,xxx2) ( ( (xxx1) > (xxx2) ) ? (xxx1) : (xxx2) )
#define MIN3(xxx1,xxx2,xxx3) ( ( ( (xxx1) < (xxx2) ) && ( (xxx1) < xxx3 ) ) ? (xxx1) : ( ( (xxx2) < (xxx3) ) ? (xxx2) : (xxx3) ) )
#define MIN2(xxx1,xxx2) ( ( (xxx1) < (xxx2) ) ? (xxx1) : (xxx2) )

// This function allocates memory for FindFullCorr function
//      width               - width of image
//      height              - height of image
//      type                - type of memory for allocate ( the size of memory depends on it )
//      maxPixelDifference  - maximum value of pixel difference on two images
int* CCvPixelToPixelMorpher::corrAlloc( int width, int height, corrArrayType type, int maxPixelDifference )
{
    int* pointer;
    switch( type )
    {
    case CORR_ARRAY:
        {
            pointer = ( int* ) malloc( width * height * 2 * sizeof( int ) );
        }
        break;
    case NUM_CORR_ARRAY:
        {
            pointer = ( int* ) malloc( height * sizeof( int ) );
        }
        break;
    case CORR_EDGES:
        {
            int i;
            int width_1 = width - 1;

            pointer = ( int* ) malloc( width * 2 * sizeof( int ) );
            for( i = 0; i < width; i ++ ) {
                pointer[ i * 2 ]      = i - maxPixelDifference;
                pointer[ i * 2 + 1 ]  = i + maxPixelDifference;
            } // for( i = 0; i < width; i ++ )
            for( i = 0; i < width; i ++ ) {
                if( pointer[ i * 2 ] < 0 ) {
                    pointer[ i * 2 ]      = 0;
                }
                if( pointer[ i * 2 + 1 ] >= width ) {
                    pointer[ i * 2 + 1 ]  = width_1;
                }
            } // for( i = 0; i < width; i ++ )

        } // case CORR_EDGES:
        break;
    case CORR_TEMP:
        {
            pointer = ( int* ) malloc( width * width * 4 * sizeof( int ) );
        }
        break;
    default:
        {
            pointer = 0;
        }

    } // switch( type )

    return pointer;
} // corrAlloc

// This function searches correspondences for full image
//      _leftImage              - pointer to 3-channel left image
//      _leftLineStep           - size of one line on the left image in bytes
//      _rightImage             - pointer to 3-channel right image
//      _rightLineStep          - size of one line on the right image in bytes
//      _corrArray              - output integer array of correspondences ( size (width)X(height)X(2) ).
//                                each element of its array consists of two integer values, one of
//                                which represents number of pixel on the left image and the other
//                                corresponding to it point on the right image
//      _numCorrArray           - output array with numbers of finded correspondences on each line
//      width                   - width of images
//      height                  - height of images
//      maxPixelDifference      - maximum value of pixel difference on two images
void CCvPixelToPixelMorpher::FindFullCorr( unsigned char* _leftImage,
                   int _leftLineStep,
                   unsigned char* _rightImage,
                   int _rightLineStep,
                   int* _corrArray,
                   int* _numCorrArray,
                   int width,
                   int height,
                   int maxPixelDifference
                 )
{
    //int     width2 = width * width;
    //int     tempMemorySize = width2 * 4 * sizeof( int );
    int*    tempMemory;

    tempMemory  = corrAlloc( width, height, CORR_TEMP );

    int*    edges   = corrAlloc( width, height, CORR_EDGES, maxPixelDifference );

    int j;

    // lines cycle - processes each line
    for( j = 0; j < height; j ++ )
    {
        FindCorr( _leftImage + _leftLineStep * j,
                  _rightImage + _rightLineStep * j,
                  _corrArray + width * 2 * j,
                  _numCorrArray + j,
                  width,
                  edges,
                  tempMemory
                );
    } // for( j = 0; j < height; j ++ )

    free( edges );
    free( tempMemory );

} // FindFullCorr

// This function searches correspondence for one line only
//      _leftLine
void CCvPixelToPixelMorpher::FindCorr( unsigned char* _leftLine,
               unsigned char* _rightLine,
               int* _corrArray,
               int* numCorrArray,
               int width,
               int* edges,
               int* tempArray
             )
{
    int     width2      = width * width;
    int     width_1     = width - 1;
    int*    xArray      = tempArray;                // array, which shows the best previous point in path
    int*    yArray      = tempArray + width2;       // array, which shows the best previous point in path
    int*    costArray   = tempArray + width2 * 2;   // array of costs table
    int*    distArray   = tempArray + width2 * 3;   // array of distances between points on two images

    int blockSize = width2 * sizeof( int );
    memset( ( void* ) xArray, 0, blockSize );               // filling by zero
    memset( ( void* ) yArray, 0, blockSize );               // filling by zero
    memset( ( void* ) distArray, 0, blockSize );            // filling by zero

    int i;
    int j;
    int iTemp;
    int jTemp;

    int currCost;
    int bestHorCost;

    int srcOffset;
    int destOffset;
    int futureCost;

    // filling cost table by very big value ( initialization )
    for( j = 0; j < width; j ++ )
    {
        for( i = edges[ j * 2 ]; i <= edges[ j * 2 + 1 ]; i ++ )
        {
            costArray[ j * width + i ] = 2000000000;    // filling by very big value

        } // for( i = edges[ j * 2 ]; i < edges[ j * 2 + 1 ]; i ++ )

    } // for( j = 0; j < width; j ++ )

    // computing distances for all pairs of points ( between points on left image and on right image )
    for( j = 0; j < width; j ++ )
    {
        for( i = edges[ j * 2 ]; i <= edges[ j * 2 + 1 ]; i ++ )
        {
            distArray[ j * width + i ] = distance( _leftLine, _rightLine, width, j, i );

        } // for( i = edges[ j * 2 ]; i < edges[ j * 2 + 1 ]; i ++ )

    } // for( j = 0; j < width; j ++ )

    // filling left upper corner
    for( i = edges[ 0 ]; i <= edges[ 1 ]; i ++ )
    {
        // horizontal line
        xArray[ i ]             = END_OF_PATH;
        costArray[ i ]          = *( distArray + i );
        // vertical line
        xArray[ i * width ]     = END_OF_PATH;
        costArray[ i * width ]  = *( distArray + i * width );
    } // for( i = edges[ 0 ]; i <= edges[ 1 ]; i ++ )

    // normal dynamic programming
    for( j = 0; j < width_1; j ++ )
    {
        bestHorCost = costArray[ j * width + edges[ j * 2 ] ];
        //bestHorCost = 2000000000;
        for( i = edges[ j * 2 ]; i <= edges[ j * 2 + 1 ]; i ++ )
        {
            srcOffset   = j * width + i;
            currCost    = costArray[ srcOffset ];
            if( currCost - COEFF_MATCH < bestHorCost + COEFF_OCC )
            {
                bestHorCost = currCost;

                // filling the next horizontal line

                // first point
                if( i != width - 1 )
                {
                    destOffset  = j * width + ( i + width + 1 );
                    futureCost  = currCost + distArray[ destOffset ];
                    if( ( xArray[ srcOffset ] == i - 1 ) && ( yArray[ srcOffset ] == j - 1 ) ) {
                        futureCost -= COEFF_MATCH;
                    }
                    if( ( xArray[ srcOffset ] != i - 1 ) || ( yArray[ srcOffset ] != j - 1 ) ) {
                        futureCost -= COEFF_MATCH_2;
                    }
                    if( costArray[ destOffset ] >= futureCost ) {
                        costArray[ destOffset ]     = futureCost;
                        xArray[ destOffset ]        = i;
                        yArray[ destOffset ]        = j;
                    }
                }
                // residuary points ( if they exist )
                for( iTemp = i + 2; iTemp <= edges[ j * 2 + 3 ]; iTemp ++ )
                {
                    destOffset  = j * width + ( iTemp + width );
                    futureCost  = currCost + COEFF_OCC + distArray[ destOffset ];
                    if( costArray[ destOffset ] >= futureCost ) {
                        costArray[ destOffset ]     = futureCost;
                        xArray[ destOffset ]        = i;
                        yArray[ destOffset ]        = j;
                    }

                } // for( iTemp = i + 2; iTemp <= edges[ j * 2 + 3 ]; iTemp ++ )

            } // if( currCost - COEFF_MATCH < bestHorCost + COEFF_OCC )

            // filling the next vertical line
            if( i != width_1 )
            {
                for( jTemp = j + 2; jTemp <= edges[ i * 2 + 3 ]; jTemp ++ )
                {
                    destOffset  = jTemp * width + ( i + 1 );
                    futureCost  = currCost + COEFF_OCC + distArray[ destOffset ];
                    if( costArray[ destOffset ] >= futureCost ) {
                        costArray[ destOffset ]     = futureCost;
                        xArray[ destOffset ]        = i;
                        yArray[ destOffset ]        = j;
                    }
                } // for( jTemp = j + 2; jTemp <= edges[ i * 2 + 3 ]; jTemp ++ )

            } // if( i != width_1 )

        } // for( i = edges[ j * 2 ]; i <= edges[ j * 2 + 1 ]; i ++ )

    } // for( j = 1; j < width; j ++ )

    // constraction of back path

    // searching for best initial point in the low right corner
    jTemp   = width - 1;
    i       = jTemp;
    j       = jTemp;
    int bestCost = costArray[ j * width + i ];
    for( iTemp = edges[ width * 2 - 2 ]; iTemp < edges[ width * 2 - 1 ]; iTemp ++ )
    {
        if( costArray[ jTemp * width + iTemp ] < bestCost ) {
            i           = iTemp;
            j           = jTemp;
            bestCost    = costArray[ jTemp * width + iTemp ];
        }
    }
    iTemp   = width - 1;
    for( jTemp = edges[ width * 2 - 2 ]; jTemp < edges[ width * 2 - 1 ]; jTemp ++ )
    {
        if( costArray[ jTemp * width + iTemp ] < bestCost ) {
            i           = iTemp;
            j           = jTemp;
            bestCost    = costArray[ jTemp * width + iTemp ];
        }
    }

    // filling back path
    *( numCorrArray )  = 0;
    _corrArray[ *( numCorrArray ) ]     = j;
    ( *( numCorrArray ) ) ++;
    _corrArray[ *( numCorrArray ) ]     = i;
    ( *( numCorrArray ) ) ++;

    srcOffset   = j * width + i;
    while( xArray[ srcOffset ] != END_OF_PATH )
    {
        i   = xArray[ srcOffset ];
        j   = yArray[ srcOffset ];
        _corrArray[ *( numCorrArray ) ]     = j;
        ( *( numCorrArray ) ) ++;
        _corrArray[ *( numCorrArray ) ]     = i;
        ( *( numCorrArray ) ) ++;
        srcOffset   = j * width + i;
    } // while( xArray[ j * width + i ] != END_OF_PATH )

    *( numCorrArray ) /= 2;

} // FindCorr

// This function produces morphing of two images into one image, which includes morphed
// image or depth map
//      _leftImage              - pointer to left image
//      _leftLineStep           - size of line on left image in bytes
//      _rightImage             - pointer to right image
//      _rightLineStep          - size of line on right image in bytes
//      _resultImage            - pointer to result morphed image
//      _resultLineStep         - size of line on result image in bytes
//      _corrArray              - pointer to array with correspondences
//      _numCorrArray           - pointer to array with numbers correspondeces on each line
//      width                   - width of images
//      height                  - height of images
//      alpha                   - position of virtual camera ( 0 corresponds to left image, 1 - to right one )
//      imageNeed               - defines your wishes. if you want to see normal morphed image you have to set
//                                this parameter to morphNormalImage ( this is default value ), else if you want
//                                to see depth map you have to set this parameter to morphDepthMap and set the
//                                next parameter ( maxPixelDifference ) to real value
//      maxPixelDifference      - maximum value of pixel difference on two images
void CCvPixelToPixelMorpher::Morph( unsigned char* _leftImage,
            int _leftLineStep,
            unsigned char* _rightImage,
            int _rightLineStep,
            unsigned char* _resultImage,
            int _resultLineStep,
            int* _corrArray,
            int* _numCorrArray,
            int width,
            int height,
            float alpha,
            morphImageType imageNeed,
            int maxDifference
          )
{
    unsigned char* leftArray    = _leftImage;
    unsigned char* middleArray  = _resultImage;
    unsigned char* rightArray   = _rightImage;
    int leftLineSize            = _leftLineStep;
    int middleLineSize          = _resultLineStep;
    int rightLineSize           = _rightLineStep;

    int lineNumber;
    unsigned char* leftTemp;
    unsigned char* middleTemp;
    unsigned char* rightTemp;
    int leftPixel;
    int prevLeftPixel;
    int middlePixel;
    int prevMiddlePixel;
    int rightPixel;
    int prevRightPixel;
    int leftPixel3;
    int middlePixel3;
    int rightPixel3;
    int i;
    int j;
    int tempIndex;
    int* result;
    int number;
    float alpha1        = 1.0f - alpha;
    
    for( lineNumber = 0; lineNumber < height; lineNumber ++ )
    {
        leftTemp    = leftArray + leftLineSize * lineNumber;
        middleTemp  = middleArray + middleLineSize * lineNumber;
        rightTemp   = rightArray + rightLineSize * lineNumber;
        memset( ( void* )middleTemp, 0, middleLineSize );

        result = _corrArray + width * 2 * lineNumber;
        number = _numCorrArray[ lineNumber ];
        
        prevLeftPixel   = result[ number * 2 - 2 ];
        prevMiddlePixel = (int)( result[ number * 2 - 2 ] * alpha1 + result[ number * 2 - 1 ] * alpha );
        prevRightPixel  = result[ number * 2 - 1 ];
        for( i = number - 1; i >= 0; i -- )
        {
            leftPixel       = result[ i * 2 ];
            rightPixel      = result[ i * 2 + 1 ];
            middlePixel     = (int)( leftPixel * alpha1 + rightPixel * alpha );
            leftPixel3      = leftPixel * 3;
            middlePixel3    = middlePixel * 3;
            rightPixel3     = rightPixel * 3;
            
            if( imageNeed == morphDepthMap ) {
                int t   = leftPixel - rightPixel + maxDifference;
                t       = t < 0 ? -t : t;
                t       = t * 255 / maxDifference / 2;
                middleTemp[ middlePixel3 ]      = ( unsigned char )t;
                middleTemp[ middlePixel3 + 1 ]  = ( unsigned char )t;
                middleTemp[ middlePixel3 + 2 ]  = ( unsigned char )t;
            } // if( imageNeed == morphDepthMap )
            else
            {
                middleTemp[ middlePixel3 ] =
                    (unsigned char)( leftTemp[ leftPixel3 ] * alpha1 + rightTemp[ rightPixel3 ] * alpha );
                middleTemp[ middlePixel3 + 1 ] =
                    (unsigned char)( leftTemp[ leftPixel3 + 1 ] * alpha1 + rightTemp[ rightPixel3 + 1 ] * alpha );
                middleTemp[ middlePixel3 + 2 ] =
                    (unsigned char)( leftTemp[ leftPixel3 + 2 ] * alpha1 + rightTemp[ rightPixel3 + 2 ] * alpha );

                if( middlePixel - prevMiddlePixel > 1 ) // occlusion
                {
                    if( leftPixel - prevLeftPixel > 1 )
                    {
                        int LenSrc  = leftPixel - prevLeftPixel - 2;
                        int LenDest = middlePixel - prevMiddlePixel - 1;
                        for( j = prevMiddlePixel + 1; j < middlePixel; j ++ )
                        {
                            tempIndex   = prevLeftPixel + 1 + LenSrc * ( j - prevMiddlePixel - 1 ) / LenDest;
                            middleTemp[ j * 3 ]     = leftTemp[ tempIndex * 3 ];
                            middleTemp[ j * 3 + 1 ] = leftTemp[ tempIndex * 3 + 1 ];
                            middleTemp[ j * 3 + 2 ] = leftTemp[ tempIndex * 3 + 2 ];
                        }
                    } // if( leftPixel - prevLeftPixel > 1 )
                    else
                    {
                        int LenSrc  = rightPixel - prevRightPixel - 2;
                        int LenDest = middlePixel - prevMiddlePixel - 1;
                        for( j = prevMiddlePixel + 1; j < middlePixel; j ++ )
                        {
                            tempIndex   = prevRightPixel + 1 + LenSrc * ( j - prevMiddlePixel - 1 ) / LenDest;
                            middleTemp[ j * 3 ]     = rightTemp[ tempIndex * 3 ];
                            middleTemp[ j * 3 + 1 ] = rightTemp[ tempIndex * 3 + 1 ];
                            middleTemp[ j * 3 + 2 ] = rightTemp[ tempIndex * 3 + 2 ];
                        }
                    } // if( leftPixel - prevLeftPixel > 1 ) else
                    
                } // if( middlePixel - prevMiddlePixel > 1 )

            } // if( imageNeed == morphDepthMap ) else
            prevLeftPixel   = leftPixel;
            prevRightPixel  = rightPixel;
            prevMiddlePixel = middlePixel;
        } // for( i = number - 1; i >= 0; i -- )
        
    } // for( lineNumber = 0; lineNumber < LeftImage -> m_Raster -> GetHeight() )

} // Morph

// This function calculates color difference between two points ( one on the left image and one on the other )
//      _leftLine               - pointer to line on the left image
//      _rightLine              - pointer to line on the right image
//      lineSize                - width of line in points
//      x                       - index of interesting point on the left image
//      y                       - index of interesting point on the right image
int CCvPixelToPixelMorpher::distance( unsigned char* _leftLine,
                                      unsigned char* _rightLine,
                                      int lineSize,
                                      int x,
                                      int y
                                    )
{
    int IrMaxRed;
    int IrMinRed;
    int IrMaxGreen;
    int IrMinGreen;
    int IrMaxBlue;
    int IrMinBlue;

    int IlMaxRed;
    int IlMinRed;
    int IlMaxGreen;
    int IlMinGreen;
    int IlMaxBlue;
    int IlMinBlue;

    int DlRed;
    int DlGreen;
    int DlBlue;

    int DrRed;
    int DrGreen;
    int DrBlue;

    int DRed;
    int DGreen;
    int DBlue;

    int dist;

    int temp1;
    int temp2;


    int xState = 0;
    int yState = 0;
    int state;

    assert( lineSize > 0 );

    _Color* leftPixel       = ( _Color* )( _leftLine ) + x;
    _Color* rightPixel      = ( _Color* )( _rightLine ) + y;

    if( lineSize == 1 ) {
        DRed = leftPixel->red - rightPixel->red;
        DRed = MAX2( DRed, -DRed );
        DGreen = leftPixel->green - rightPixel->green;
        DGreen = MAX2( DGreen, -DGreen );
        DBlue = leftPixel->blue - rightPixel->blue;
        DBlue = MAX2( DBlue, -DBlue );
        return MAX3( DRed, DGreen, DBlue );
    }

    if( x == 0 ) {
        xState = -1;
    }
    else if( x == lineSize - 1 )
    {
        xState = 1;
    }

    if( y == 0 ) {
        yState = -1;
    }
    else if( y == lineSize - 1 )
    {
        yState = 1;
    }

    state = yState * 3 + xState;

    switch( state )
    {
    case 0: // xState = yState = 0
        {
            // Red
            temp1 = ( (leftPixel - 1)->red + leftPixel->red ) >> 1;
            temp2 = ( (leftPixel + 1)->red + leftPixel->red ) >> 1;
            IlMaxRed = MAX3( leftPixel->red, temp1, temp2 );
            IlMinRed = MIN3( leftPixel->red, temp1, temp2 );
            temp1 = ( (rightPixel - 1)->red + rightPixel->red ) >> 1;
            temp2 = ( (rightPixel + 1)->red + rightPixel->red ) >> 1;
            IrMaxRed = MAX3( rightPixel->red, temp1, temp2 );
            IrMinRed = MIN3( rightPixel->red, temp1, temp2 );
            // Green
            temp1 = ( (leftPixel - 1)->green + leftPixel->green ) >> 1;
            temp2 = ( (leftPixel + 1)->green + leftPixel->green ) >> 1;
            IlMaxGreen = MAX3( leftPixel->green, temp1, temp2 );
            IlMinGreen = MIN3( leftPixel->green, temp1, temp2 );
            temp1 = ( (rightPixel - 1)->green + rightPixel->green ) >> 1;
            temp2 = ( (rightPixel + 1)->green + rightPixel->green ) >> 1;
            IrMaxGreen = MAX3( rightPixel->green, temp1, temp2 );
            IrMinGreen = MIN3( rightPixel->green, temp1, temp2 );
            // Blue
            temp1 = ( (leftPixel - 1)->blue + leftPixel->blue ) >> 1;
            temp2 = ( (leftPixel + 1)->blue + leftPixel->blue ) >> 1;
            IlMaxBlue = MAX3( leftPixel->blue, temp1, temp2 );
            IlMinBlue = MIN3( leftPixel->blue, temp1, temp2 );
            temp1 = ( (rightPixel - 1)->blue + rightPixel->blue ) >> 1;
            temp2 = ( (rightPixel + 1)->blue + rightPixel->blue ) >> 1;
            IrMaxBlue = MAX3( rightPixel->blue, temp1, temp2 );
            IrMinBlue = MIN3( rightPixel->blue, temp1, temp2 );

            // Red
            temp1 = leftPixel->red - IrMaxRed;
            temp2 = IrMinRed - leftPixel->red;
            DlRed = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->red - IlMaxRed;
            temp2 = IlMinRed - rightPixel->red;
            DrRed = MAX3( 0, temp1, temp2 );
            // Green
            temp1 = leftPixel->green - IrMaxGreen;
            temp2 = IrMinGreen - leftPixel->green;
            DlGreen = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->green - IlMaxGreen;
            temp2 = IlMinGreen - rightPixel->green;
            DrGreen = MAX3( 0, temp1, temp2 );
            // Blue
            temp1 = leftPixel->blue - IrMaxBlue;
            temp2 = IrMinBlue - leftPixel->blue;
            DlBlue = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->blue - IlMaxBlue;
            temp2 = IlMinBlue - rightPixel->blue;
            DrBlue = MAX3( 0, temp1, temp2 );

        } // case 0
        break;
    case -1: // xState = -1, yState = 0
        {
            // Red
            temp2 = ( (leftPixel + 1)->red + leftPixel->red ) >> 1;
            IlMaxRed = MAX2( leftPixel->red, temp2 );
            IlMinRed = MIN2( leftPixel->red, temp2 );
            temp1 = ( (rightPixel - 1)->red + rightPixel->red ) >> 1;
            temp2 = ( (rightPixel + 1)->red + rightPixel->red ) >> 1;
            IrMaxRed = MAX3( rightPixel->red, temp1, temp2 );
            IrMinRed = MIN3( rightPixel->red, temp1, temp2 );
            // Green
            temp2 = ( (leftPixel + 1)->green + leftPixel->green ) >> 1;
            IlMaxGreen = MAX2( leftPixel->green, temp2 );
            IlMinGreen = MIN2( leftPixel->green, temp2 );
            temp1 = ( (rightPixel - 1)->green + rightPixel->green ) >> 1;
            temp2 = ( (rightPixel + 1)->green + rightPixel->green ) >> 1;
            IrMaxGreen = MAX3( rightPixel->green, temp1, temp2 );
            IrMinGreen = MIN3( rightPixel->green, temp1, temp2 );
            // Blue
            temp2 = ( (leftPixel + 1)->blue + leftPixel->blue ) >> 1;
            IlMaxBlue = MAX2( leftPixel->blue, temp2 );
            IlMinBlue = MIN2( leftPixel->blue, temp2 );
            temp1 = ( (rightPixel - 1)->blue + rightPixel->blue ) >> 1;
            temp2 = ( (rightPixel + 1)->blue + rightPixel->blue ) >> 1;
            IrMaxBlue = MAX3( rightPixel->blue, temp1, temp2 );
            IrMinBlue = MIN3( rightPixel->blue, temp1, temp2 );

            // Red
            temp1 = leftPixel->red - IrMaxRed;
            temp2 = IrMinRed - leftPixel->red;
            DlRed = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->red - IlMaxRed;
            temp2 = IlMinRed - rightPixel->red;
            DrRed = MAX3( 0, temp1, temp2 );
            // Green
            temp1 = leftPixel->green - IrMaxGreen;
            temp2 = IrMinGreen - leftPixel->green;
            DlGreen = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->green - IlMaxGreen;
            temp2 = IlMinGreen - rightPixel->green;
            DrGreen = MAX3( 0, temp1, temp2 );
            // Blue
            temp1 = leftPixel->blue - IrMaxBlue;
            temp2 = IrMinBlue - leftPixel->blue;
            DlBlue = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->blue - IlMaxBlue;
            temp2 = IlMinBlue - rightPixel->blue;
            DrBlue = MAX3( 0, temp1, temp2 );

        } // case -1
        break;
    case 1: // xState = 1, yState = 0
        {
            // Red
            temp1 = ( (leftPixel - 1)->red + leftPixel->red ) >> 1;
            IlMaxRed = MAX2( leftPixel->red, temp1 );
            IlMinRed = MIN2( leftPixel->red, temp1 );
            temp1 = ( (rightPixel - 1)->red + rightPixel->red ) >> 1;
            temp2 = ( (rightPixel + 1)->red + rightPixel->red ) >> 1;
            IrMaxRed = MAX3( rightPixel->red, temp1, temp2 );
            IrMinRed = MIN3( rightPixel->red, temp1, temp2 );
            // Green
            temp1 = ( (leftPixel - 1)->green + leftPixel->green ) >> 1;
            IlMaxGreen = MAX2( leftPixel->green, temp1 );
            IlMinGreen = MIN2( leftPixel->green, temp1 );
            temp1 = ( (rightPixel - 1)->green + rightPixel->green ) >> 1;
            temp2 = ( (rightPixel + 1)->green + rightPixel->green ) >> 1;
            IrMaxGreen = MAX3( rightPixel->green, temp1, temp2 );
            IrMinGreen = MIN3( rightPixel->green, temp1, temp2 );
            // Blue
            temp1 = ( (leftPixel - 1)->blue + leftPixel->blue ) >> 1;
            IlMaxBlue = MAX2( leftPixel->blue, temp1 );
            IlMinBlue = MIN2( leftPixel->blue, temp1 );
            temp1 = ( (rightPixel - 1)->blue + rightPixel->blue ) >> 1;
            temp2 = ( (rightPixel + 1)->blue + rightPixel->blue ) >> 1;
            IrMaxBlue = MAX3( rightPixel->blue, temp1, temp2 );
            IrMinBlue = MIN3( rightPixel->blue, temp1, temp2 );

            // Red
            temp1 = leftPixel->red - IrMaxRed;
            temp2 = IrMinRed - leftPixel->red;
            DlRed = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->red - IlMaxRed;
            temp2 = IlMinRed - rightPixel->red;
            DrRed = MAX3( 0, temp1, temp2 );
            // Green
            temp1 = leftPixel->green - IrMaxGreen;
            temp2 = IrMinGreen - leftPixel->green;
            DlGreen = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->green - IlMaxGreen;
            temp2 = IlMinGreen - rightPixel->green;
            DrGreen = MAX3( 0, temp1, temp2 );
            // Blue
            temp1 = leftPixel->blue - IrMaxBlue;
            temp2 = IrMinBlue - leftPixel->blue;
            DlBlue = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->blue - IlMaxBlue;
            temp2 = IlMinBlue - rightPixel->blue;
            DrBlue = MAX3( 0, temp1, temp2 );

        } // case 1
        break;
    case -3: // xState = 0, yState = -1
        {
            // Red
            temp1 = ( (leftPixel - 1)->red + leftPixel->red ) >> 1;
            temp2 = ( (leftPixel + 1)->red + leftPixel->red ) >> 1;
            IlMaxRed = MAX3( leftPixel->red, temp1, temp2 );
            IlMinRed = MIN3( leftPixel->red, temp1, temp2 );
            temp2 = ( (rightPixel + 1)->red + rightPixel->red ) >> 1;
            IrMaxRed = MAX2( rightPixel->red, temp2 );
            IrMinRed = MIN2( rightPixel->red, temp2 );
            // Green
            temp1 = ( (leftPixel - 1)->green + leftPixel->green ) >> 1;
            temp2 = ( (leftPixel + 1)->green + leftPixel->green ) >> 1;
            IlMaxGreen = MAX3( leftPixel->green, temp1, temp2 );
            IlMinGreen = MIN3( leftPixel->green, temp1, temp2 );
            temp2 = ( (rightPixel + 1)->green + rightPixel->green ) >> 1;
            IrMaxGreen = MAX2( rightPixel->green, temp2 );
            IrMinGreen = MIN2( rightPixel->green, temp2 );
            // Blue
            temp1 = ( (leftPixel - 1)->blue + leftPixel->blue ) >> 1;
            temp2 = ( (leftPixel + 1)->blue + leftPixel->blue ) >> 1;
            IlMaxBlue = MAX3( leftPixel->blue, temp1, temp2 );
            IlMinBlue = MIN3( leftPixel->blue, temp1, temp2 );
            temp2 = ( (rightPixel + 1)->blue + rightPixel->blue ) >> 1;
            IrMaxBlue = MAX2( rightPixel->blue, temp2 );
            IrMinBlue = MIN2( rightPixel->blue, temp2 );

            // Red
            temp1 = leftPixel->red - IrMaxRed;
            temp2 = IrMinRed - leftPixel->red;
            DlRed = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->red - IlMaxRed;
            temp2 = IlMinRed - rightPixel->red;
            DrRed = MAX3( 0, temp1, temp2 );
            // Green
            temp1 = leftPixel->green - IrMaxGreen;
            temp2 = IrMinGreen - leftPixel->green;
            DlGreen = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->green - IlMaxGreen;
            temp2 = IlMinGreen - rightPixel->green;
            DrGreen = MAX3( 0, temp1, temp2 );
            // Blue
            temp1 = leftPixel->blue - IrMaxBlue;
            temp2 = IrMinBlue - leftPixel->blue;
            DlBlue = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->blue - IlMaxBlue;
            temp2 = IlMinBlue - rightPixel->blue;
            DrBlue = MAX3( 0, temp1, temp2 );

        } // case -3
        break;
    case 3: // xState = 0, yState = 1
        {
            // Red
            temp1 = ( (leftPixel - 1)->red + leftPixel->red ) >> 1;
            temp2 = ( (leftPixel + 1)->red + leftPixel->red ) >> 1;
            IlMaxRed = MAX3( leftPixel->red, temp1, temp2 );
            IlMinRed = MIN3( leftPixel->red, temp1, temp2 );
            temp1 = ( (rightPixel - 1)->red + rightPixel->red ) >> 1;
            IrMaxRed = MAX2( rightPixel->red, temp1 );
            IrMinRed = MIN2( rightPixel->red, temp1 );
            // Green
            temp1 = ( (leftPixel - 1)->green + leftPixel->green ) >> 1;
            temp2 = ( (leftPixel + 1)->green + leftPixel->green ) >> 1;
            IlMaxGreen = MAX3( leftPixel->green, temp1, temp2 );
            IlMinGreen = MIN3( leftPixel->green, temp1, temp2 );
            temp1 = ( (rightPixel - 1)->green + rightPixel->green ) >> 1;
            IrMaxGreen = MAX2( rightPixel->green, temp1 );
            IrMinGreen = MIN2( rightPixel->green, temp1 );
            // Blue
            temp1 = ( (leftPixel - 1)->blue + leftPixel->blue ) >> 1;
            temp2 = ( (leftPixel + 1)->blue + leftPixel->blue ) >> 1;
            IlMaxBlue = MAX3( leftPixel->blue, temp1, temp2 );
            IlMinBlue = MIN3( leftPixel->blue, temp1, temp2 );
            temp1 = ( (rightPixel - 1)->blue + rightPixel->blue ) >> 1;
            IrMaxBlue = MAX2( rightPixel->blue, temp1 );
            IrMinBlue = MIN2( rightPixel->blue, temp1 );

            // Red
            temp1 = leftPixel->red - IrMaxRed;
            temp2 = IrMinRed - leftPixel->red;
            DlRed = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->red - IlMaxRed;
            temp2 = IlMinRed - rightPixel->red;
            DrRed = MAX3( 0, temp1, temp2 );
            // Green
            temp1 = leftPixel->green - IrMaxGreen;
            temp2 = IrMinGreen - leftPixel->green;
            DlGreen = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->green - IlMaxGreen;
            temp2 = IlMinGreen - rightPixel->green;
            DrGreen = MAX3( 0, temp1, temp2 );
            // Blue
            temp1 = leftPixel->blue - IrMaxBlue;
            temp2 = IrMinBlue - leftPixel->blue;
            DlBlue = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->blue - IlMaxBlue;
            temp2 = IlMinBlue - rightPixel->blue;
            DrBlue = MAX3( 0, temp1, temp2 );

        } // case 3
        break;
    case -2: // xState = 1, yState = -1
        {
            // Red
            temp1 = ( (leftPixel - 1)->red + leftPixel->red ) >> 1;
            IlMaxRed = MAX2( leftPixel->red, temp1 );
            IlMinRed = MIN2( leftPixel->red, temp1 );
            temp2 = ( (rightPixel + 1)->red + rightPixel->red ) >> 1;
            IrMaxRed = MAX2( rightPixel->red, temp2 );
            IrMinRed = MIN2( rightPixel->red, temp2 );
            // Green
            temp1 = ( (leftPixel - 1)->green + leftPixel->green ) >> 1;
            IlMaxGreen = MAX2( leftPixel->green, temp1 );
            IlMinGreen = MIN2( leftPixel->green, temp1 );
            temp2 = ( (rightPixel + 1)->green + rightPixel->green ) >> 1;
            IrMaxGreen = MAX2( rightPixel->green, temp2 );
            IrMinGreen = MIN2( rightPixel->green, temp2 );
            // Blue
            temp1 = ( (leftPixel - 1)->blue + leftPixel->blue ) >> 1;
            IlMaxBlue = MAX2( leftPixel->blue, temp1 );
            IlMinBlue = MIN2( leftPixel->blue, temp1 );
            temp2 = ( (rightPixel + 1)->blue + rightPixel->blue ) >> 1;
            IrMaxBlue = MAX2( rightPixel->blue, temp2 );
            IrMinBlue = MIN2( rightPixel->blue, temp2 );

            // Red
            temp1 = leftPixel->red - IrMaxRed;
            temp2 = IrMinRed - leftPixel->red;
            DlRed = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->red - IlMaxRed;
            temp2 = IlMinRed - rightPixel->red;
            DrRed = MAX3( 0, temp1, temp2 );
            // Green
            temp1 = leftPixel->green - IrMaxGreen;
            temp2 = IrMinGreen - leftPixel->green;
            DlGreen = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->green - IlMaxGreen;
            temp2 = IlMinGreen - rightPixel->green;
            DrGreen = MAX3( 0, temp1, temp2 );
            // Blue
            temp1 = leftPixel->blue - IrMaxBlue;
            temp2 = IrMinBlue - leftPixel->blue;
            DlBlue = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->blue - IlMaxBlue;
            temp2 = IlMinBlue - rightPixel->blue;
            DrBlue = MAX3( 0, temp1, temp2 );

        } // case -2
        break;
    case 2: // xState = -1, yState = 1
        {
            // Red
            temp2 = ( (leftPixel + 1)->red + leftPixel->red ) >> 1;
            IlMaxRed = MAX2( leftPixel->red, temp2 );
            IlMinRed = MIN2( leftPixel->red, temp2 );
            temp1 = ( (rightPixel - 1)->red + rightPixel->red ) >> 1;
            IrMaxRed = MAX2( rightPixel->red, temp1 );
            IrMinRed = MIN2( rightPixel->red, temp1 );
            // Green
            temp2 = ( (leftPixel + 1)->green + leftPixel->green ) >> 1;
            IlMaxGreen = MAX2( leftPixel->green, temp2 );
            IlMinGreen = MIN2( leftPixel->green, temp2 );
            temp1 = ( (rightPixel - 1)->green + rightPixel->green ) >> 1;
            IrMaxGreen = MAX2( rightPixel->green, temp1 );
            IrMinGreen = MIN2( rightPixel->green, temp1 );
            // Blue
            temp2 = ( (leftPixel + 1)->blue + leftPixel->blue ) >> 1;
            IlMaxBlue = MAX2( leftPixel->blue, temp2 );
            IlMinBlue = MIN2( leftPixel->blue, temp2 );
            temp1 = ( (rightPixel - 1)->blue + rightPixel->blue ) >> 1;
            IrMaxBlue = MAX2( rightPixel->blue, temp1 );
            IrMinBlue = MIN2( rightPixel->blue, temp1 );

            // Red
            temp1 = leftPixel->red - IrMaxRed;
            temp2 = IrMinRed - leftPixel->red;
            DlRed = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->red - IlMaxRed;
            temp2 = IlMinRed - rightPixel->red;
            DrRed = MAX3( 0, temp1, temp2 );
            // Green
            temp1 = leftPixel->green - IrMaxGreen;
            temp2 = IrMinGreen - leftPixel->green;
            DlGreen = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->green - IlMaxGreen;
            temp2 = IlMinGreen - rightPixel->green;
            DrGreen = MAX3( 0, temp1, temp2 );
            // Blue
            temp1 = leftPixel->blue - IrMaxBlue;
            temp2 = IrMinBlue - leftPixel->blue;
            DlBlue = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->blue - IlMaxBlue;
            temp2 = IlMinBlue - rightPixel->blue;
            DrBlue = MAX3( 0, temp1, temp2 );

        } // case 2
        break;
    case -4: // xState = -1, yState = -1
        {
            // Red
            temp2 = ( (leftPixel + 1)->red + leftPixel->red ) >> 1;
            IlMaxRed = MAX2( leftPixel->red, temp2 );
            IlMinRed = MIN2( leftPixel->red, temp2 );
            temp2 = ( (rightPixel + 1)->red + rightPixel->red ) >> 1;
            IrMaxRed = MAX2( rightPixel->red, temp2 );
            IrMinRed = MIN2( rightPixel->red, temp2 );
            // Green
            temp2 = ( (leftPixel + 1)->green + leftPixel->green ) >> 1;
            IlMaxGreen = MAX2( leftPixel->green, temp2 );
            IlMinGreen = MIN2( leftPixel->green, temp2 );
            temp2 = ( (rightPixel + 1)->green + rightPixel->green ) >> 1;
            IrMaxGreen = MAX2( rightPixel->green, temp2 );
            IrMinGreen = MIN2( rightPixel->green, temp2 );
            // Blue
            temp2 = ( (leftPixel + 1)->blue + leftPixel->blue ) >> 1;
            IlMaxBlue = MAX2( leftPixel->blue, temp2 );
            IlMinBlue = MIN2( leftPixel->blue, temp2 );
            temp2 = ( (rightPixel + 1)->blue + rightPixel->blue ) >> 1;
            IrMaxBlue = MAX2( rightPixel->blue, temp2 );
            IrMinBlue = MIN2( rightPixel->blue, temp2 );

            // Red
            temp1 = leftPixel->red - IrMaxRed;
            temp2 = IrMinRed - leftPixel->red;
            DlRed = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->red - IlMaxRed;
            temp2 = IlMinRed - rightPixel->red;
            DrRed = MAX3( 0, temp1, temp2 );
            // Green
            temp1 = leftPixel->green - IrMaxGreen;
            temp2 = IrMinGreen - leftPixel->green;
            DlGreen = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->green - IlMaxGreen;
            temp2 = IlMinGreen - rightPixel->green;
            DrGreen = MAX3( 0, temp1, temp2 );
            // Blue
            temp1 = leftPixel->blue - IrMaxBlue;
            temp2 = IrMinBlue - leftPixel->blue;
            DlBlue = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->blue - IlMaxBlue;
            temp2 = IlMinBlue - rightPixel->blue;
            DrBlue = MAX3( 0, temp1, temp2 );

        } // case -4
        break;
    case 4: // xState = 1, yState = 1
    default:
        {
            // Red
            temp1 = ( (leftPixel - 1)->red + leftPixel->red ) >> 1;
            IlMaxRed = MAX2( leftPixel->red, temp1 );
            IlMinRed = MIN2( leftPixel->red, temp1 );
            temp1 = ( (rightPixel - 1)->red + rightPixel->red ) >> 1;
            IrMaxRed = MAX2( rightPixel->red, temp1 );
            IrMinRed = MIN2( rightPixel->red, temp1 );
            // Green
            temp1 = ( (leftPixel - 1)->green + leftPixel->green ) >> 1;
            IlMaxGreen = MAX2( leftPixel->green, temp1 );
            IlMinGreen = MIN2( leftPixel->green, temp1 );
            temp1 = ( (rightPixel - 1)->green + rightPixel->green ) >> 1;
            IrMaxGreen = MAX2( rightPixel->green, temp1 );
            IrMinGreen = MIN2( rightPixel->green, temp1 );
            // Blue
            temp1 = ( (leftPixel - 1)->blue + leftPixel->blue ) >> 1;
            IlMaxBlue = MAX2( leftPixel->blue, temp1 );
            IlMinBlue = MIN2( leftPixel->blue, temp1 );
            temp1 = ( (rightPixel - 1)->blue + rightPixel->blue ) >> 1;
            IrMaxBlue = MAX2( rightPixel->blue, temp1 );
            IrMinBlue = MIN2( rightPixel->blue, temp1 );

            // Red
            temp1 = leftPixel->red - IrMaxRed;
            temp2 = IrMinRed - leftPixel->red;
            DlRed = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->red - IlMaxRed;
            temp2 = IlMinRed - rightPixel->red;
            DrRed = MAX3( 0, temp1, temp2 );
            // Green
            temp1 = leftPixel->green - IrMaxGreen;
            temp2 = IrMinGreen - leftPixel->green;
            DlGreen = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->green - IlMaxGreen;
            temp2 = IlMinGreen - rightPixel->green;
            DrGreen = MAX3( 0, temp1, temp2 );
            // Blue
            temp1 = leftPixel->blue - IrMaxBlue;
            temp2 = IrMinBlue - leftPixel->blue;
            DlBlue = MAX3( 0, temp1, temp2 );
            temp1 = rightPixel->blue - IlMaxBlue;
            temp2 = IlMinBlue - rightPixel->blue;
            DrBlue = MAX3( 0, temp1, temp2 );

        } // case 4
    } // switch( state )

    DRed = MIN2( DlRed, DrRed );
    DGreen = MIN2( DlGreen, DrGreen );
    DBlue = MIN2( DlBlue, DrBlue );
    //DRed = MAX2( DlRed, DrRed );
    //DGreen = MAX2( DlGreen, DrGreen );
    //DBlue = MAX2( DlBlue, DrBlue );

    dist = MAX3( DRed, DGreen, DBlue );
    //dist = ( DRed + DGreen + DBlue ) / 3;
    //dist = ( DRed + DGreen + DBlue ) + MAX3( DRed, DGreen, DBlue );
    //dist = DRed;

    return dist;
}

bool  CCvPixelToPixelMorpher::OnCalculateStereo()
{
    CvSize imageSizeLeft = GetImageSize( m_left_img ),
           imageSizeRight = GetImageSize( m_right_img );

    if( ( imageSizeLeft.width != imageSizeRight.width )
        || ( imageSizeLeft.height != imageSizeRight.height ) )
    {
        return false;
    }

    if( m_corr ) {
        free( m_corr );
        m_corr = NULL;
    }
    m_corr = corrAlloc( m_left_img -> width,
        m_left_img -> height,
        CORR_ARRAY );
    if( m_corrNum ) {
        free( m_corrNum );
        m_corrNum = NULL;
    }
    m_corrNum = corrAlloc( m_left_img -> width,
        m_right_img -> height,
        NUM_CORR_ARRAY );

    // Find correspondence for full image and store it to corr array
    FindFullCorr( ( unsigned char* )m_left_img -> imageData,
                  m_left_img -> widthStep,
                  ( unsigned char* )m_right_img -> imageData,
                  m_right_img -> widthStep,
                  m_corr,
                  m_corrNum,
                  m_left_img -> width,
                  m_left_img -> height,
                  m_maxPixelDifference
                );

    m_isStereoReady = true;

    return true;
}

bool  CCvPixelToPixelMorpher::OnCalculateVirtualImage()
{
    // Output image to ResultImage window
    Morph( ( unsigned char* )m_left_img -> imageData,
           m_left_img ->widthStep,
           ( unsigned char* )m_right_img -> imageData,
           m_right_img -> widthStep,
           ( unsigned char* )m_virtual_img -> imageData,
           m_virtual_img -> widthStep,
           m_corr,
           m_corrNum,
           m_left_img -> width,
           m_left_img -> height,
           m_pan );

    m_isVirtualImageReady = true;

    return true;
}

bool  CCvPixelToPixelMorpher::OnCalculateDisparity()
{
    Morph( ( unsigned char* )m_left_img -> imageData,
           m_left_img ->widthStep,
           ( unsigned char* )m_right_img -> imageData,
           m_right_img -> widthStep,
           ( unsigned char* )m_disparity_img -> imageData,
           m_disparity_img -> widthStep,
           m_corr,
           m_corrNum,
           m_left_img -> width,
           m_left_img -> height,
           m_pan,
           morphDepthMap,
           m_maxPixelDifference );

    return true;
}

bool  CCvPixelToPixelMorpher::OnCalculateDisparityImage()
{
    Morph( ( unsigned char* )m_left_img -> imageData,
           m_left_img ->widthStep,
           ( unsigned char* )m_right_img -> imageData,
           m_right_img -> widthStep,
           ( unsigned char* )m_disparity_img -> imageData,
           m_disparity_img -> widthStep,
           m_corr,
           m_corrNum,
           m_left_img -> width,
           m_left_img -> height,
           m_pan,
           morphDepthMap,
           m_maxPixelDifference );

    return true;
}

CCvPixelToPixelMorpher::CCvPixelToPixelMorpher()
{
    m_maxPixelDifference = MAX_DIFFERENCE;
    m_corr = m_corrNum = 0;
    m_isStereoReady = false;
    m_isVirtualImageReady = false;
    m_isDisparityReady = false;
    //m_isDisparityImageReady = false;
}
