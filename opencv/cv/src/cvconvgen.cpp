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

#include "_cv.h"

#if _MSC_VER >= 1200
#pragma optimize("",off)
#endif

#define BOUND(rbound,x) ((((x)<0)-1)&MIN((rbound),(x)))
#define SAT(x) MIN(MAX(x,-32768),32767)
/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    _ipcvSymSepConv8xC1R
//    Purpose:
//      Evaluate the convolution with predefined Kers
//
//    Context:
//    Parameters:
//      pConS       - stucture contains the convolution parameters                   
//      pSrc        - Pointer to the Src array
//      SrcStep     - Full width of Src in bytes
//      pDest       - Pointer to the destination array
//      DestStep    - Full width of Dest in bytes
//      strokes        - number of rows to process
//    Returns:
//      CV_NO_ERR if all Ok or error code
//    Notes:
//      function convolves the image with predefined Ker
//F*/
IPCVAPI_IMPL(CvStatus, icvSobel_8u16s_C1R, ( const unsigned char*          pSrc,
                                             int            srcStep,
                                             short*         pDest,
                                             int            destStep,
                                             CvSize*        curROI,
                                             _CvConvState*  pConS,
                                             int            stage ))
{
    int i,j,k,t,Center,limitX,LX,ConvY,ConvY1,ConvY2,ConvY3,ConvY4,
		prelim, prelim1, prelim2,prelim3, prelim4;
    short** lines;
    int Len;
	int* KerX;
    int* KerY;
    short* pDst = pDest;
    short* pDstI;
    int obtain_rows=0;
    int ownstage = (stage)?stage:CV_START|CV_END;
    short* Temp;
    unsigned char* pS8u;

   	lines= (short**)pConS->lines;
	Len = pConS->kerType>>3;
	Center = Len/2;
	KerX = (int*)(pConS->KerX+4*Center);
    KerY = (int*)(pConS->KerY+4*Center);
	pDst = pDest;
	limitX = curROI->width-1;
	LX = Center + ((curROI->width-2*Center)/8)*8;
	pS8u=(unsigned char*)pSrc;
	if(ownstage&CV_START)pConS->initialized =Len-1;
    t = 0;

    if(ownstage&CV_START)
    {  
        if(pConS->kerType&1)
        { 
            for(i = 0; i < Center; i++)
            {
                prelim = 0;
                for(k = 1; k <=Center; k++)
                {
                    prelim += KerX[k] *
                    (pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }

            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k]*
                    (pS8u[i + k] - pS8u[i - k]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim +=  KerX[k] *
                    (pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }
            
        }
        else
        {
            for(i = 0; i < Center; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <=Center; k++)
                {
                   prelim += KerX[k] *
                   (pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }

            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k]*
                    (pS8u[i + k] + pS8u[i - k]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                   prelim +=  KerX[k] *
                   (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }
            
        }
        pConS->initialized=Center-1;
        pS8u += srcStep;
        curROI->height--;
    }
 
    while((curROI->height)&&(pConS->initialized))
    { 
        pDstI = lines[Len-1-pConS->initialized];
        if(pConS->kerType&1)
        {
            for(i = 0; i < Center; i++)
            {
                prelim = 0;
                for(k = 1; k <=Center; k++)
                {
                    prelim +=  KerX[k] *
                    (pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)]);
                }
                pDstI[i] = (short)prelim;
            }
            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k]*
                    (pS8u[i + k] - pS8u[i - k]);
                }
                pDstI[i] = (short)prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k] *
                    (pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)]);
                }
                pDstI[i] = (short)prelim;
            }

        }
        else
        {
            for(i = 0; i < Center; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <=Center; k++)
                {
                    prelim +=  KerX[k] *
                    (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                }
                pDstI[i] = (short)prelim;
            }
            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k]*
                    (pS8u[i + k] + pS8u[i - k]);
                }
                pDstI[i] = (short)prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                   prelim += KerX[k] *
                   (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                }
                pDstI[i] = (short)prelim;
           }
        }
        pConS->initialized--;
        curROI->height--;
        pS8u += srcStep;
    }
    /* main loop */
    pDst = pDest;
    for(t = 0;t < curROI->height;t++)
    {
        pDstI = lines[0];
        switch(pConS->kerType)
        { 
        case 25:
            prelim = pS8u[1]-pS8u[0];
            pDst[0] = (short)(KerY[0]*lines[1][0]+lines[0][0] +prelim);
            pDstI[0]=(short)prelim;
            for(i = 1; i < LX; i+=4)
			{
                  
                prelim1 = pS8u[i+1]-pS8u[i-1];
                prelim2 = pS8u[i+2]-pS8u[i];
                prelim3 = pS8u[i+3]-pS8u[i+1];
                prelim4 = pS8u[i+4]-pS8u[i+2];

                pDst[i] = (short)(KerY[0]*lines[1][i]+lines[0][i] +prelim1);
                pDst[i+1] = (short)(KerY[0]*lines[1][i+1]+lines[0][i+1] +prelim2);
                pDst[i+2] = (short)(KerY[0]*lines[1][i+2]+lines[0][i+2] +prelim3);
                pDst[i+3] = (short)(KerY[0]*lines[1][i+3]+lines[0][i+3] +prelim4);

                pDstI[i]=(short)prelim1;
                pDstI[i+1]=(short)prelim2;
                pDstI[i+2]=(short)prelim3;
                pDstI[i+3]=(short)prelim4;
            
                
            
            }
            for(;i <= limitX; i++)
            {
                prelim = pS8u[BOUND(limitX,i+1)]-pS8u[i-1];
                pDst[i] = (short)(KerY[0]*lines[1][i]+lines[0][i] +prelim);
                pDstI[i]=(short)prelim;
            }
            break;
        case 26:
            prelim = (KerX[0]+1)*pS8u[0]+pS8u[1];
            pDst[0] = (short)(prelim - lines[0][0]);
            pDstI[0]=(short)prelim;
            for(i = 1; i < LX; i+=4)
            {
                prelim1 = KerX[0]*pS8u[i]+pS8u[i+1]+pS8u[i-1];
                prelim2 = KerX[0]*pS8u[i+1]+pS8u[i+2]+pS8u[i];
                prelim3 = KerX[0]*pS8u[i+2]+pS8u[i+3]+pS8u[i+1];
                prelim4 = KerX[0]*pS8u[i+3]+pS8u[i+4]+pS8u[i+2];
                pDst[i] = (short)(prelim1 -lines[0][i]);
                pDst[i+1] = (short)(prelim2-lines[0][i+1]);
                pDst[i+2] = (short)(prelim3-lines[0][i+2]);
                pDst[i+3] = (short)(prelim4-lines[0][i+3]);
                pDstI[i]=(short)prelim1;
                pDstI[i+1]=(short)prelim2;
                pDstI[i+2]=(short)prelim3;
                pDstI[i+3]=(short)prelim4;
                
                
            }
            for(;i <= limitX; i++)
            {
                prelim = KerX[0]*pS8u[i]+pS8u[BOUND(limitX,i+1)]+pS8u[i-1];
                pDst[i] = (short)(prelim - lines[0][i]);
                pDstI[i]= (short)prelim;
            }
            break;
        case 30:
            prelim = (KerX[0]+1)*pS8u[0]+pS8u[1];
            pDst[0] = (short)(lines[0][0] - prelim);
            pDstI[0]=(short)prelim;
            for(i = 1; i < LX; i+=4)
            {
                prelim1 = KerX[0]*pS8u[i]+pS8u[i+1]+pS8u[i-1];
                prelim2 = KerX[0]*pS8u[i+1]+pS8u[i+2]+pS8u[i];
                prelim3 = KerX[0]*pS8u[i+2]+pS8u[i+3]+pS8u[i+1];
                prelim4 = KerX[0]*pS8u[i+3]+pS8u[i+4]+pS8u[i+2];

                pDst[i] = (short)(lines[0][i] - prelim1);
                pDst[i+1] = (short)(lines[0][i+1]-prelim2);
                pDst[i+2] = (short)(lines[0][i+2]-prelim3);
                pDst[i+3] = (short)(lines[0][i+3]-prelim4);

                pDstI[i]=(short)prelim1;
                pDstI[i+1]=(short)prelim2;
                pDstI[i+2]=(short)prelim3;
                pDstI[i+3]=(short)prelim4;
                
                
            }
            for(;i <=limitX; i++)
            {
                prelim = KerX[0]*pS8u[i]+pS8u[BOUND(limitX,i+1)]+pS8u[i-1];
                pDst[i] = (short)(lines[0][i] - prelim);
                pDstI[i]=(short)prelim;
            }
            break;
        default: 
            if((pConS->kerType&3) == 3)
            {
                for(i = 0; i < Center; i++)
                {
                    prelim = 0;
                    ConvY =0;
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k]*(pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)];
                    pDst[i] = (short)SAT(ConvY + KerY[k] *(prelim - pDstI[i]));
                    pDstI[i]=(short)prelim;
                }
                for(i = Center; i < LX; i+=4)
                {
                    
                    prelim1 = 0;
                    prelim2 = 0;
                    prelim3 = 0;
                    prelim4 = 0;
                
                    ConvY1 = 0;
                    ConvY2 = 0;
                    ConvY3 = 0;
                    ConvY4 = 0;
                    
                    for(k = 1; k < Center; k++)
                    {
                        prelim1 +=KerX[k]*(pS8u[i + k] - pS8u[i - k]);
                        prelim2 +=KerX[k]*(pS8u[i + k + 1] - pS8u[i - k +1]);
                        prelim3 +=KerX[k]*(pS8u[i + k + 2] - pS8u[i - k + 2]);
                        prelim4 +=KerX[k]*(pS8u[i + k + 3] - pS8u[i - k + 3]);
                    
                        ConvY1 += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                        ConvY2 += KerY[k] *(lines[Center+k][i+1]-lines[Center-k][i+1]);
                        ConvY3 += KerY[k] *(lines[Center+k][i+2]-lines[Center-k][i+2]);
                        ConvY4 += KerY[k] *(lines[Center+k][i+3]-lines[Center-k][i+3]);
                    }
                    prelim1 += pS8u[i + k] - pS8u[i - k];
                    prelim2 += pS8u[i + k + 1] - pS8u[i - k + 1];
                    prelim3 += pS8u[i + k + 2] - pS8u[i - k + 2];
                    prelim4 += pS8u[i + k + 3] - pS8u[i - k + 3];

                    pDst[i] = (short)SAT(ConvY1 + KerY[k]*(prelim1-pDstI[i]));
                    pDst[i+1] = (short)SAT(ConvY2 + KerY[k]*(prelim2-pDstI[i+1]));
                    pDst[i+2] = (short)SAT(ConvY3 + KerY[k]*(prelim3-pDstI[i+2]));
                    pDst[i+3] = (short)SAT(ConvY4 + KerY[k]*(prelim4-pDstI[i+3]));

                    pDstI[i]=(short)prelim1;
                    pDstI[i+1]=(short)prelim2;
                    pDstI[i+2]=(short)prelim3;
                    pDstI[i+3]=(short)prelim4;
                   
                }
            
                for(;i <= limitX; i++)
                {
                    prelim = 0;
                    ConvY =0;
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k] *
                        (pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)];                    
                    pDst[i] = (short)SAT(ConvY + KerY[k] *(prelim - pDstI[i]));
                    pDstI[i]=(short)prelim;
                }
            }
            else if((pConS->kerType&3) == 2)
            {
                for(i = 0; i < Center; i++)
                {
                    prelim = KerX[0]*pS8u[i];
                    ConvY =0;
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k]*(pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)];
                    pDst[i] = (short)SAT(ConvY + KerY[k] *(prelim - pDstI[i]));
                    pDstI[i]=(short)prelim;
                }
                for(i = Center; i < LX; i+=4)
                {
                    prelim1 = KerX[0]*pS8u[i];
                    prelim2 = KerX[0]*pS8u[i+1];
                    prelim3 = KerX[0]*pS8u[i+2];
                    prelim4 = KerX[0]*pS8u[i+3];
                
                    ConvY1 = 0;
                    ConvY2 = 0;
                    ConvY3 = 0;
                    ConvY4 = 0;
                    
                    for(k = 1; k < Center; k++)
                    {
                        prelim1 +=KerX[k]*(pS8u[i + k] + pS8u[i - k]);
                        prelim2 +=KerX[k]*(pS8u[i + k + 1] + pS8u[i - k +1]);
                        prelim3 +=KerX[k]*(pS8u[i + k + 2] + pS8u[i - k + 2]);
                        prelim4 +=KerX[k]*(pS8u[i + k + 3] + pS8u[i - k + 3]);
                    
                        ConvY1 += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                        ConvY2 += KerY[k] *(lines[Center+k][i+1]-lines[Center-k][i+1]);
                        ConvY3 += KerY[k] *(lines[Center+k][i+2]-lines[Center-k][i+2]);
                        ConvY4 += KerY[k] *(lines[Center+k][i+3]-lines[Center-k][i+3]);
                    }
                    prelim1 += pS8u[i + k] + pS8u[i - k];
                    prelim2 += pS8u[i + k + 1] + pS8u[i - k + 1];
                    prelim3 += pS8u[i + k + 2] + pS8u[i - k + 2];
                    prelim4 += pS8u[i + k + 3] + pS8u[i - k + 3];

                    pDst[i] = (short)SAT(ConvY1 + KerY[k]*(prelim1-pDstI[i]));
                    pDst[i+1] = (short)SAT(ConvY2 + KerY[k]*(prelim2-pDstI[i+1]));
                    pDst[i+2] = (short)SAT(ConvY3 + KerY[k]*(prelim3-pDstI[i+2]));
                    pDst[i+3] = (short)SAT(ConvY4 + KerY[k]*(prelim4-pDstI[i+3]));

                    pDstI[i]=(short)prelim1;
                    pDstI[i+1]=(short)prelim2;
                    pDstI[i+2]=(short)prelim3;
                    pDstI[i+3]=(short)prelim4;
                   
                }
            
                for(;i <= limitX; i++)
                {
                    prelim = KerX[0]*pS8u[i];
                    ConvY =0;
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k] *
                        (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)];                    
                    pDst[i] = (short)SAT(ConvY + KerY[k] *(prelim - pDstI[i]));
                    pDstI[i]=(short)prelim;
                }
            }
            else if((pConS->kerType&3) == 1)
            {
                for(i = 0; i < Center; i++)
                {
                    prelim = 0;
                    ConvY =KerY[0]*lines[Center][i];
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k]*(pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] * (lines[Center+k][i]+lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)];
                    pDst[i] = (short)SAT(ConvY + prelim + pDstI[i]);
                    pDstI[i]=(short)prelim;
                }
                for(i = Center; i < LX; i+=4)
                {
                    
                    prelim1 = 0;
                    prelim2 = 0;
                    prelim3 = 0;
                    prelim4 = 0;
                
                    ConvY1 = KerY[0]*lines[Center][i];
                    ConvY2 = KerY[0]*lines[Center][i+1];
                    ConvY3 = KerY[0]*lines[Center][i+2];
                    ConvY4 = KerY[0]*lines[Center][i+3];
                    
                    for(k = 1; k < Center; k++)
                    {
                        prelim1 +=KerX[k]*(pS8u[i + k] - pS8u[i - k]);
                        prelim2 +=KerX[k]*(pS8u[i + k + 1] - pS8u[i - k +1]);
                        prelim3 +=KerX[k]*(pS8u[i + k + 2] - pS8u[i - k + 2]);
                        prelim4 +=KerX[k]*(pS8u[i + k + 3] - pS8u[i - k + 3]);
                    
                        ConvY1 += KerY[k] *(lines[Center+k][i]+lines[Center-k][i]);
                        ConvY2 += KerY[k] *(lines[Center+k][i+1]+lines[Center-k][i+1]);
                        ConvY3 += KerY[k] *(lines[Center+k][i+2]+lines[Center-k][i+2]);
                        ConvY4 += KerY[k] *(lines[Center+k][i+3]+lines[Center-k][i+3]);
                    }
                    prelim1 += pS8u[i + k] - pS8u[i - k];
                    prelim2 += pS8u[i + k + 1] - pS8u[i - k + 1];
                    prelim3 += pS8u[i + k + 2] - pS8u[i - k + 2];
                    prelim4 += pS8u[i + k + 3] - pS8u[i - k + 3];

                    pDst[i] = (short)SAT(ConvY1 + prelim1 + pDstI[i]);
                    pDst[i+1] = (short)SAT(ConvY2 + prelim2 + pDstI[i+1]);
                    pDst[i+2] = (short)SAT(ConvY3 + prelim3 + pDstI[i+2]);
                    pDst[i+3] = (short)SAT(ConvY4 + prelim4 + pDstI[i+3]);

                    pDstI[i]=(short)prelim1;
                    pDstI[i+1]=(short)prelim2;
                    pDstI[i+2]=(short)prelim3;
                    pDstI[i+3]=(short)prelim4;
                   
                }
            
                for(;i <= limitX; i++)
                {
                    prelim = 0;
                    ConvY =KerY[0]*lines[Center][i];
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k] *
                        (pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]+lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)];                    
                    pDst[i] = (short)SAT(ConvY + prelim + pDstI[i]);
                    pDstI[i]=(short)prelim;
                }
            }
            else
            {
                for(i = 0; i < Center; i++)
                {
                    prelim = KerX[0]*pS8u[i];
                    ConvY =KerY[0]*lines[Center][i];
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k]*(pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]+lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)];
                    pDst[i] = (short)SAT(ConvY + prelim + pDstI[i]);
                    pDstI[i]=(short)prelim;
                }
                for(i = Center; i < LX; i+=4)
                {
                    prelim1 = KerX[0]*pS8u[i];
                    prelim2 = KerX[0]*pS8u[i+1];
                    prelim3 = KerX[0]*pS8u[i+2];
                    prelim4 = KerX[0]*pS8u[i+3];
                
                    ConvY1 =KerY[0]*lines[Center][i];
                    ConvY2 =KerY[0]*lines[Center][i+1];
                    ConvY3 =KerY[0]*lines[Center][i+2];
                    ConvY4 =KerY[0]*lines[Center][i+3];
                    
                    for(k = 1; k < Center; k++)
                    {
                        prelim1 +=KerX[k]*(pS8u[i + k] + pS8u[i - k]);
                        prelim2 +=KerX[k]*(pS8u[i + k + 1] + pS8u[i - k +1]);
                        prelim3 +=KerX[k]*(pS8u[i + k + 2] + pS8u[i - k + 2]);
                        prelim4 +=KerX[k]*(pS8u[i + k + 3] + pS8u[i - k + 3]);
                    
                        ConvY1 += KerY[k] *(lines[Center+k][i]+lines[Center-k][i]);
                        ConvY2 += KerY[k] *(lines[Center+k][i+1]+lines[Center-k][i+1]);
                        ConvY3 += KerY[k] *(lines[Center+k][i+2]+lines[Center-k][i+2]);
                        ConvY4 += KerY[k] *(lines[Center+k][i+3]+lines[Center-k][i+3]);
                    }
                    prelim1 += pS8u[i + k] + pS8u[i - k];
                    prelim2 += pS8u[i + k + 1] + pS8u[i - k + 1];
                    prelim3 += pS8u[i + k + 2] + pS8u[i - k + 2];
                    prelim4 += pS8u[i + k + 3] + pS8u[i - k + 3];

                    pDst[i] = (short)SAT(ConvY1 + prelim1+pDstI[i]);
                    pDst[i+1] = (short)SAT(ConvY2 + prelim2+pDstI[i+1]);
                    pDst[i+2] = (short)SAT(ConvY3 + prelim3+pDstI[i+2]);
                    pDst[i+3] = (short)SAT(ConvY4 + prelim4+pDstI[i+3]);

                    pDstI[i]=(short)prelim1;
                    pDstI[i+1]=(short)prelim2;
                    pDstI[i+2]=(short)prelim3;
                    pDstI[i+3]=(short)prelim4;
                   
                }
            
                for(;i <= limitX; i++)
                {
                    prelim = KerX[0]*pS8u[i];
                    ConvY =KerY[0]*lines[Center][i];
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k] *
                        (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]+lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)];                    
                    pDst[i] = (short)SAT(ConvY + prelim + pDstI[i]);
                    pDstI[i]=(short)prelim;
                }
            }
            break;
            }
       
        /* Rotating cyclic buffer */ 
        Temp = lines[0];
        for(k = 0; k < Len-2; k++)
        {
           lines[k]=lines[k + 1];
        }
        lines[Len-2] = Temp;
        obtain_rows++;
        pDst+=destStep/2;
        pS8u += srcStep;

    }

    if(ownstage&CV_END)
    {
		int Fin = Center - pConS->initialized;
		if(pConS->initialized)
		{
			for(t = 0; t < pConS->initialized; t++)
			{
				memcpy(lines[Len-2-t],lines[Len-2-pConS->initialized],curROI->width*2);
			}
		}
        memcpy(lines[Len-1], lines[Len-2], curROI->width*2);
        for(t = 0; t < Fin; t++)
        {
            if(pConS->kerType&2)
            {
                for(i = 0; i < curROI->width; i++)
                {
            
                    ConvY = 0;
                    for(j = 1; j <= Center; j++)
                    {
                        ConvY += KerY[j] *(lines[Center+j][i]-lines[Center-j][i]);
                    }
                    pDst[i] = (short)SAT(ConvY);
                }
            }
            else
            {
                for(i = 0; i < curROI->width; i++)
                {
                    ConvY = KerY[0]*lines[Center][i];
                    for(j = 1; j <= Center; j++)
                    {
                        ConvY += KerY[j] *(lines[Center-j][i]+lines[Center+j][i]);
                    }
                    pDst[i] = (short)SAT(ConvY);
                }
            }
            memcpy(lines[0], lines[Len-1], curROI->width*2);
            Temp = lines[0];
            for(k = 0; k < Len-1; k++)
            {
                lines[k]=lines[k + 1];
            }
            lines[Len-1] = Temp;
            pDst+=destStep/2;
            obtain_rows++;
        }
    }

     

    curROI->height=obtain_rows;    
    return CV_NO_ERR;
}

IPCVAPI_IMPL(CvStatus, icvSobel_8s16s_C1R, ( const char*          pSrc,
								            int             srcStep,
                                            short*         pDest,
                                            int             destStep,
                                            CvSize*        curROI,
                                            _CvConvState*  pConS,
                                            int             stage ))
{
    	int i,j,k,t,Center,limitX,LX,ConvY,ConvY1,ConvY2,ConvY3,ConvY4,
	prelim, prelim1, prelim2,prelim3, prelim4;
    short** lines;
    int Len;
	int* KerX;
    int* KerY;
    short* pDst = pDest;
    short* pDstI;
    int obtain_rows=0;
    int ownstage = (stage)?stage:CV_START|CV_END;
    short* Temp;
    char* pS8u;

   	lines= (short**)pConS->lines;
	Len = pConS->kerType>>3;
	Center = Len/2;
	KerX = (int*)(pConS->KerX+4*Center);
    KerY = (int*)(pConS->KerY+4*Center);
	pDst = pDest;
	limitX = curROI->width-1;
	LX = Center + ((curROI->width-2*Center)/8)*8;
	pS8u=(char*)pSrc;
	if(ownstage&CV_START)pConS->initialized =Len-1;
    t = 0;

    if(ownstage&CV_START)
    {  
        if(pConS->kerType&1)
        { 
            for(i = 0; i < Center; i++)
            {
                prelim = 0;
                for(k = 1; k <=Center; k++)
                {
                    prelim += KerX[k] *
                    (pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }

            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k]*
                    (pS8u[i + k] - pS8u[i - k]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim +=  KerX[k] *
                    (pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }
            
        }
        else
        {
            for(i = 0; i < Center; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <=Center; k++)
                {
                   prelim += KerX[k] *
                   (pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }

            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k]*
                    (pS8u[i + k] + pS8u[i - k]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                   prelim +=  KerX[k] *
                   (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }
            
        }
        pConS->initialized=Center-1;
        pS8u += srcStep;
        curROI->height--;
    }
 
    while((curROI->height)&&(pConS->initialized))
    { 
        pDstI = lines[Len-1-pConS->initialized];
        if(pConS->kerType&1)
        {
            for(i = 0; i < Center; i++)
            {
                prelim = 0;
                for(k = 1; k <=Center; k++)
                {
                    prelim +=  KerX[k] *
                    (pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)]);
                }
                pDstI[i] = (short)prelim;
            }
            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k]*
                    (pS8u[i + k] - pS8u[i - k]);
                }
                pDstI[i] = (short)prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k] *
                    (pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)]);
                }
                pDstI[i] = (short)prelim;
            }

        }
        else
        {
            for(i = 0; i < Center; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <=Center; k++)
                {
                    prelim +=  KerX[k] *
                    (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                }
                pDstI[i] = (short)prelim;
            }
            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k]*
                    (pS8u[i + k] + pS8u[i - k]);
                }
                pDstI[i] = (short)prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                   prelim += KerX[k] *
                   (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                }
                pDstI[i] = (short)prelim;
           }
        }
        pConS->initialized--;
        curROI->height--;
        pS8u += srcStep;
    }
    /* main loop */
    pDst = pDest;
    for(t = 0;t < curROI->height;t++)
    {
        pDstI = lines[0];
        switch(pConS->kerType)
        { 
        case 25:
            prelim = pS8u[1]-pS8u[0];
            pDst[0] = (short)(KerY[0]*lines[1][0]+lines[0][0] +prelim);
            pDstI[0]=(short)prelim;
            for(i = 1; i < LX; i+=4)
			{
                  
                prelim1 = pS8u[i+1]-pS8u[i-1];
                prelim2 = pS8u[i+2]-pS8u[i];
                prelim3 = pS8u[i+3]-pS8u[i+1];
                prelim4 = pS8u[i+4]-pS8u[i+2];

                pDst[i] = (short)(KerY[0]*lines[1][i]+lines[0][i] +prelim1);
                pDst[i+1] = (short)(KerY[0]*lines[1][i+1]+lines[0][i+1] +prelim2);
                pDst[i+2] = (short)(KerY[0]*lines[1][i+2]+lines[0][i+2] +prelim3);
                pDst[i+3] = (short)(KerY[0]*lines[1][i+3]+lines[0][i+3] +prelim4);

                pDstI[i]=(short)prelim1;
                pDstI[i+1]=(short)prelim2;
                pDstI[i+2]=(short)prelim3;
                pDstI[i+3]=(short)prelim4;
            
                
            
            }
            for(;i <= limitX; i++)
            {
                prelim = pS8u[BOUND(limitX,i+1)]-pS8u[i-1];
                pDst[i] = (short)(KerY[0]*lines[1][i]+lines[0][i] +prelim);
                pDstI[i]=(short)prelim;
            }
            break;
        case 26:
            prelim = (KerX[0]+1)*pS8u[0]+pS8u[1];
            pDst[0] = (short)(prelim - lines[0][0]);
            pDstI[0]=(short)prelim;
            for(i = 1; i < LX; i+=4)
            {
                prelim1 = KerX[0]*pS8u[i]+pS8u[i+1]+pS8u[i-1];
                prelim2 = KerX[0]*pS8u[i+1]+pS8u[i+2]+pS8u[i];
                prelim3 = KerX[0]*pS8u[i+2]+pS8u[i+3]+pS8u[i+1];
                prelim4 = KerX[0]*pS8u[i+3]+pS8u[i+4]+pS8u[i+2];
                pDst[i] = (short)(prelim1 -lines[0][i]);
                pDst[i+1] = (short)(prelim2-lines[0][i+1]);
                pDst[i+2] = (short)(prelim3-lines[0][i+2]);
                pDst[i+3] = (short)(prelim4-lines[0][i+3]);
                pDstI[i]=(short)prelim1;
                pDstI[i+1]=(short)prelim2;
                pDstI[i+2]=(short)prelim3;
                pDstI[i+3]=(short)prelim4;
                
                
            }
            for(;i <= limitX; i++)
            {
                prelim = KerX[0]*pS8u[i]+pS8u[BOUND(limitX,i+1)]+pS8u[i-1];
                pDst[i] = (short)(prelim - lines[0][i]);
                pDstI[i]= (short)prelim;
            }
            break;
        case 30:
            prelim = (KerX[0]+1)*pS8u[0]+pS8u[1];
            pDst[0] = (short)(lines[0][0] - prelim);
            pDstI[0]=(short)prelim;
            for(i = 1; i < LX; i+=4)
            {
                prelim1 = KerX[0]*pS8u[i]+pS8u[i+1]+pS8u[i-1];
                prelim2 = KerX[0]*pS8u[i+1]+pS8u[i+2]+pS8u[i];
                prelim3 = KerX[0]*pS8u[i+2]+pS8u[i+3]+pS8u[i+1];
                prelim4 = KerX[0]*pS8u[i+3]+pS8u[i+4]+pS8u[i+2];

                pDst[i] = (short)(lines[0][i] - prelim1);
                pDst[i+1] = (short)(lines[0][i+1]-prelim2);
                pDst[i+2] = (short)(lines[0][i+2]-prelim3);
                pDst[i+3] = (short)(lines[0][i+3]-prelim4);

                pDstI[i]=(short)prelim1;
                pDstI[i+1]=(short)prelim2;
                pDstI[i+2]=(short)prelim3;
                pDstI[i+3]=(short)prelim4;
                
                
            }
            for(;i <=limitX; i++)
            {
                prelim = KerX[0]*pS8u[i]+pS8u[BOUND(limitX,i+1)]+pS8u[i-1];
                pDst[i] = (short)(lines[0][i] - prelim);
                pDstI[i]=(short)prelim;
            }
            break;
        default: 
            if((pConS->kerType&3) == 3)
            {
                for(i = 0; i < Center; i++)
                {
                    prelim = 0;
                    ConvY =0;
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k]*(pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)];
                    pDst[i] = (short)SAT(ConvY + KerY[k] *(prelim - pDstI[i]));
                    pDstI[i]=(short)prelim;
                }
                for(i = Center; i < LX; i+=4)
                {
                    
                    prelim1 = 0;
                    prelim2 = 0;
                    prelim3 = 0;
                    prelim4 = 0;
                
                    ConvY1 = 0;
                    ConvY2 = 0;
                    ConvY3 = 0;
                    ConvY4 = 0;
                    
                    for(k = 1; k < Center; k++)
                    {
                        prelim1 +=KerX[k]*(pS8u[i + k] - pS8u[i - k]);
                        prelim2 +=KerX[k]*(pS8u[i + k + 1] - pS8u[i - k +1]);
                        prelim3 +=KerX[k]*(pS8u[i + k + 2] - pS8u[i - k + 2]);
                        prelim4 +=KerX[k]*(pS8u[i + k + 3] - pS8u[i - k + 3]);
                    
                        ConvY1 += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                        ConvY2 += KerY[k] *(lines[Center+k][i+1]-lines[Center-k][i+1]);
                        ConvY3 += KerY[k] *(lines[Center+k][i+2]-lines[Center-k][i+2]);
                        ConvY4 += KerY[k] *(lines[Center+k][i+3]-lines[Center-k][i+3]);
                    }
                    prelim1 += pS8u[i + k] - pS8u[i - k];
                    prelim2 += pS8u[i + k + 1] - pS8u[i - k + 1];
                    prelim3 += pS8u[i + k + 2] - pS8u[i - k + 2];
                    prelim4 += pS8u[i + k + 3] - pS8u[i - k + 3];

                    pDst[i] = (short)SAT(ConvY1 + KerY[k]*(prelim1-pDstI[i]));
                    pDst[i+1] = (short)SAT(ConvY2 + KerY[k]*(prelim2-pDstI[i+1]));
                    pDst[i+2] = (short)SAT(ConvY3 + KerY[k]*(prelim3-pDstI[i+2]));
                    pDst[i+3] = (short)SAT(ConvY4 + KerY[k]*(prelim4-pDstI[i+3]));

                    pDstI[i]=(short)prelim1;
                    pDstI[i+1]=(short)prelim2;
                    pDstI[i+2]=(short)prelim3;
                    pDstI[i+3]=(short)prelim4;
                   
                }
            
                for(;i <= limitX; i++)
                {
                    prelim = 0;
                    ConvY =0;
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k] *
                        (pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)];                    
                    pDst[i] = (short)SAT(ConvY + KerY[k] *(prelim - pDstI[i]));
                    pDstI[i]=(short)prelim;
                }
            }
            else if((pConS->kerType&3) == 2)
            {
                for(i = 0; i < Center; i++)
                {
                    prelim = KerX[0]*pS8u[i];
                    ConvY =0;
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k]*(pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)];
                    pDst[i] = (short)SAT(ConvY + KerY[k] *(prelim - pDstI[i]));
                    pDstI[i]=(short)prelim;
                }
                for(i = Center; i < LX; i+=4)
                {
                    prelim1 = KerX[0]*pS8u[i];
                    prelim2 = KerX[0]*pS8u[i+1];
                    prelim3 = KerX[0]*pS8u[i+2];
                    prelim4 = KerX[0]*pS8u[i+3];
                
                    ConvY1 = 0;
                    ConvY2 = 0;
                    ConvY3 = 0;
                    ConvY4 = 0;
                    
                    for(k = 1; k < Center; k++)
                    {
                        prelim1 +=KerX[k]*(pS8u[i + k] + pS8u[i - k]);
                        prelim2 +=KerX[k]*(pS8u[i + k + 1] + pS8u[i - k +1]);
                        prelim3 +=KerX[k]*(pS8u[i + k + 2] + pS8u[i - k + 2]);
                        prelim4 +=KerX[k]*(pS8u[i + k + 3] + pS8u[i - k + 3]);
                    
                        ConvY1 += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                        ConvY2 += KerY[k] *(lines[Center+k][i+1]-lines[Center-k][i+1]);
                        ConvY3 += KerY[k] *(lines[Center+k][i+2]-lines[Center-k][i+2]);
                        ConvY4 += KerY[k] *(lines[Center+k][i+3]-lines[Center-k][i+3]);
                    }
                    prelim1 += pS8u[i + k] + pS8u[i - k];
                    prelim2 += pS8u[i + k + 1] + pS8u[i - k + 1];
                    prelim3 += pS8u[i + k + 2] + pS8u[i - k + 2];
                    prelim4 += pS8u[i + k + 3] + pS8u[i - k + 3];

                    pDst[i] = (short)SAT(ConvY1 + KerY[k]*(prelim1-pDstI[i]));
                    pDst[i+1] = (short)SAT(ConvY2 + KerY[k]*(prelim2-pDstI[i+1]));
                    pDst[i+2] = (short)SAT(ConvY3 + KerY[k]*(prelim3-pDstI[i+2]));
                    pDst[i+3] = (short)SAT(ConvY4 + KerY[k]*(prelim4-pDstI[i+3]));

                    pDstI[i]=(short)prelim1;
                    pDstI[i+1]=(short)prelim2;
                    pDstI[i+2]=(short)prelim3;
                    pDstI[i+3]=(short)prelim4;
                   
                }
            
                for(;i <= limitX; i++)
                {
                    prelim = KerX[0]*pS8u[i];
                    ConvY =0;
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k] *
                        (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)];                    
                    pDst[i] = (short)SAT(ConvY + KerY[k] *(prelim - pDstI[i]));
                    pDstI[i]=(short)prelim;
                }
            }
            else if((pConS->kerType&3) == 1)
            {
                for(i = 0; i < Center; i++)
                {
                    prelim = 0;
                    ConvY =KerY[0]*lines[Center][i];
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k]*(pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] * (lines[Center+k][i]+lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)];
                    pDst[i] = (short)SAT(ConvY + prelim + pDstI[i]);
                    pDstI[i]=(short)prelim;
                }
                for(i = Center; i < LX; i+=4)
                {
                    
                    prelim1 = 0;
                    prelim2 = 0;
                    prelim3 = 0;
                    prelim4 = 0;
                
                    ConvY1 = KerY[0]*lines[Center][i];
                    ConvY2 = KerY[0]*lines[Center][i+1];
                    ConvY3 = KerY[0]*lines[Center][i+2];
                    ConvY4 = KerY[0]*lines[Center][i+3];
                    
                    for(k = 1; k < Center; k++)
                    {
                        prelim1 +=KerX[k]*(pS8u[i + k] - pS8u[i - k]);
                        prelim2 +=KerX[k]*(pS8u[i + k + 1] - pS8u[i - k +1]);
                        prelim3 +=KerX[k]*(pS8u[i + k + 2] - pS8u[i - k + 2]);
                        prelim4 +=KerX[k]*(pS8u[i + k + 3] - pS8u[i - k + 3]);
                    
                        ConvY1 += KerY[k] *(lines[Center+k][i]+lines[Center-k][i]);
                        ConvY2 += KerY[k] *(lines[Center+k][i+1]+lines[Center-k][i+1]);
                        ConvY3 += KerY[k] *(lines[Center+k][i+2]+lines[Center-k][i+2]);
                        ConvY4 += KerY[k] *(lines[Center+k][i+3]+lines[Center-k][i+3]);
                    }
                    prelim1 += pS8u[i + k] - pS8u[i - k];
                    prelim2 += pS8u[i + k + 1] - pS8u[i - k + 1];
                    prelim3 += pS8u[i + k + 2] - pS8u[i - k + 2];
                    prelim4 += pS8u[i + k + 3] - pS8u[i - k + 3];

                    pDst[i] = (short)SAT(ConvY1 + prelim1 + pDstI[i]);
                    pDst[i+1] = (short)SAT(ConvY2 + prelim2 + pDstI[i+1]);
                    pDst[i+2] = (short)SAT(ConvY3 + prelim3 + pDstI[i+2]);
                    pDst[i+3] = (short)SAT(ConvY4 + prelim4 + pDstI[i+3]);

                    pDstI[i]=(short)prelim1;
                    pDstI[i+1]=(short)prelim2;
                    pDstI[i+2]=(short)prelim3;
                    pDstI[i+3]=(short)prelim4;
                   
                }
            
                for(;i <= limitX; i++)
                {
                    prelim = 0;
                    ConvY =KerY[0]*lines[Center][i];
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k] *
                        (pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]+lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)];                    
                    pDst[i] = (short)SAT(ConvY + prelim + pDstI[i]);
                    pDstI[i]=(short)prelim;
                }
            }
            else
            {
                for(i = 0; i < Center; i++)
                {
                    prelim = KerX[0]*pS8u[i];
                    ConvY =KerY[0]*lines[Center][i];
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k]*(pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]+lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)];
                    pDst[i] = (short)SAT(ConvY + prelim + pDstI[i]);
                    pDstI[i]=(short)prelim;
                }
                for(i = Center; i < LX; i+=4)
                {
                    prelim1 = KerX[0]*pS8u[i];
                    prelim2 = KerX[0]*pS8u[i+1];
                    prelim3 = KerX[0]*pS8u[i+2];
                    prelim4 = KerX[0]*pS8u[i+3];
                
                    ConvY1 =KerY[0]*lines[Center][i];
                    ConvY2 =KerY[0]*lines[Center][i+1];
                    ConvY3 =KerY[0]*lines[Center][i+2];
                    ConvY4 =KerY[0]*lines[Center][i+3];
                    
                    for(k = 1; k < Center; k++)
                    {
                        prelim1 +=KerX[k]*(pS8u[i + k] + pS8u[i - k]);
                        prelim2 +=KerX[k]*(pS8u[i + k + 1] + pS8u[i - k +1]);
                        prelim3 +=KerX[k]*(pS8u[i + k + 2] + pS8u[i - k + 2]);
                        prelim4 +=KerX[k]*(pS8u[i + k + 3] + pS8u[i - k + 3]);
                    
                        ConvY1 += KerY[k] *(lines[Center+k][i]+lines[Center-k][i]);
                        ConvY2 += KerY[k] *(lines[Center+k][i+1]+lines[Center-k][i+1]);
                        ConvY3 += KerY[k] *(lines[Center+k][i+2]+lines[Center-k][i+2]);
                        ConvY4 += KerY[k] *(lines[Center+k][i+3]+lines[Center-k][i+3]);
                    }
                    prelim1 += pS8u[i + k] + pS8u[i - k];
                    prelim2 += pS8u[i + k + 1] + pS8u[i - k + 1];
                    prelim3 += pS8u[i + k + 2] + pS8u[i - k + 2];
                    prelim4 += pS8u[i + k + 3] + pS8u[i - k + 3];

                    pDst[i] = (short)SAT(ConvY1 + prelim1+pDstI[i]);
                    pDst[i+1] = (short)SAT(ConvY2 + prelim2+pDstI[i+1]);
                    pDst[i+2] = (short)SAT(ConvY3 + prelim3+pDstI[i+2]);
                    pDst[i+3] = (short)SAT(ConvY4 + prelim4+pDstI[i+3]);

                    pDstI[i]=(short)prelim1;
                    pDstI[i+1]=(short)prelim2;
                    pDstI[i+2]=(short)prelim3;
                    pDstI[i+3]=(short)prelim4;
                   
                }
            
                for(;i <= limitX; i++)
                {
                    prelim = KerX[0]*pS8u[i];
                    ConvY =KerY[0]*lines[Center][i];
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k] *
                        (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]+lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)];                    
                    pDst[i] = (short)SAT(ConvY + prelim + pDstI[i]);
                    pDstI[i]=(short)prelim;
                }
            }
            break;
            }
       
        /* Rotating cyclic buffer */ 
        Temp = lines[0];
        for(k = 0; k < Len-2; k++)
        {
           lines[k]=lines[k + 1];
        }
        lines[Len-2] = Temp;
        obtain_rows++;
        pDst+=destStep/2;
        pS8u += srcStep;

    }

    if(ownstage&CV_END)
    {
		int Fin = Center - pConS->initialized;
		if(pConS->initialized)
		{
			for(t = 0; t < pConS->initialized; t++)
			{
				memcpy(lines[Len-2-t],lines[Len-2-pConS->initialized],curROI->width*2);
			}
		}
        memcpy(lines[Len-1], lines[Len-2], curROI->width*2);
        for(t = 0; t < Fin; t++)
        {
            if(pConS->kerType&2)
            {
                for(i = 0; i < curROI->width; i++)
                {
            
                    ConvY = 0;
                    for(j = 1; j <= Center; j++)
                    {
                        ConvY += KerY[j] *(lines[Center+j][i]-lines[Center-j][i]);
                    }
                    pDst[i] = (short)SAT(ConvY);
                }
            }
            else
            {
                for(i = 0; i < curROI->width; i++)
                {
                    ConvY = KerY[0]*lines[Center][i];
                    for(j = 1; j <= Center; j++)
                    {
                        ConvY += KerY[j] *(lines[Center-j][i]+lines[Center+j][i]);
                    }
                    pDst[i] = (short)SAT(ConvY);
                }
            }
            memcpy(lines[0], lines[Len-1], curROI->width*2);
            Temp = lines[0];
            for(k = 0; k < Len-1; k++)
            {
                lines[k]=lines[k + 1];
            }
            lines[Len-1] = Temp;
            pDst+=destStep/2;
            obtain_rows++;
        }
    }

     

    curROI->height=obtain_rows;    
    return CV_NO_ERR;
}


IPCVAPI_IMPL(CvStatus, icvSobel_32f_C1R, ( const float*   pSrc,
								          int             srcStep,
                                          float*         pDest,
                                          int             destStep,
                                          CvSize*       curROI,
                                          _CvConvState*  pConS,
                                          int             stage ))
{
    int i,j,k,t;
    float** lines;
    int Len;
	int Center;
    float* KerX;
    float* KerY;
    float* pDst;
    float* pDstI;
    int limitX;
    int LX;
    int obtain_rows= 0;
    int ownstage;
    float* Temp;
    float* pS8u=(float*)pSrc;
    float ConvY,ConvY1,ConvY2,ConvY3,ConvY4;
    float prelim, prelim1, prelim2,prelim3, prelim4;
    
	lines = (float**)pConS->lines;
    Len = pConS->kerType>>3;
	Center = Len/2;
    KerX = (float*)(pConS->KerX+4*Center);
    KerY = (float*)(pConS->KerY+4*Center);
    pDst = pDest;
    limitX = curROI->width-1;
    LX = Center + ((curROI->width-2*Center)/4)*4;
    ownstage = (stage)?stage:CV_START|CV_END;
    pS8u=(float*)pSrc;
    t = 0;
	if(ownstage&CV_START)pConS->initialized =Len-1;
    if(ownstage&CV_START)
    {
        if(pConS->kerType&1)
        {
            for(i = 0; i < Center; i++)
            {
                prelim = 0;
                for(k = 1; k <=Center; k++)
                {
                    prelim += KerX[k] *
                    (pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = prelim;
            }

            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k]*
                    (pS8u[i + k] - pS8u[i - k]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim +=  KerX[k] *
                    (pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = prelim;
            }
            
        }
        else
        {
            for(i = 0; i < Center; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <=Center; k++)
                {
                   prelim += KerX[k] *
                   (pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)]);
                }
                    for(k = 0; k<=Center; k++)lines[k][i] = prelim;
            }

            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k]*
                    (pS8u[i + k] + pS8u[i - k]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                   prelim +=  KerX[k] *
                   (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = prelim;
            }
            
        }
        pConS->initialized=Center-1;
        pS8u += srcStep/4;
        curROI->height--;
    }

    while((curROI->height)&&(pConS->initialized))
    {
        pDstI = lines[Len-1-pConS->initialized];
        if(pConS->kerType&1)
        {
            for(i = 0; i < Center; i++)
            {
                prelim = 0;
                for(k = 1; k <=Center; k++)
                {
                    prelim +=  KerX[k] *
                    (pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)]);
                }
                pDstI[i] = prelim;
            }
            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k]*
                    (pS8u[i + k] - pS8u[i - k]);
                }
                pDstI[i] = prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k] *
                    (pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)]);
                }
                pDstI[i] = prelim;
            }

        }
        else
        {
            for(i = 0; i < Center; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <=Center; k++)
                {
                    prelim +=  KerX[k] *
                    (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                }
                pDstI[i] = prelim;
            }
            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k]*
                    (pS8u[i + k] + pS8u[i - k]);
                }
                pDstI[i] = prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = KerX[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                   prelim += KerX[k] *
                   (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                }
                pDstI[i] = prelim;
           }
        }
        pConS->initialized--;
        curROI->height--;
        pS8u += srcStep/4;
    }
    /* main loop */
    pDst = pDest;
    for(t = 0;t < curROI->height;t++)
    {
        pDstI = lines[0];
        switch(pConS->kerType)
        {
            
        case 25:
            prelim = pS8u[1]-pS8u[0];
            pDst[0] = (KerY[0]*lines[1][0]+lines[0][0] +prelim);
            pDstI[0]=prelim;
            for(i = 1; i < LX; i+=4)
            {
                  
                prelim1 = pS8u[i+1]-pS8u[i-1];
                prelim2 = pS8u[i+2]-pS8u[i];
                prelim3 = pS8u[i+3]-pS8u[i+1];
                prelim4 = pS8u[i+4]-pS8u[i+2];

                pDst[i] = (KerY[0]*lines[1][i]+lines[0][i] +prelim1);
                pDst[i+1] = (KerY[0]*lines[1][i+1]+lines[0][i+1] +prelim2);
                pDst[i+2] = (KerY[0]*lines[1][i+2]+lines[0][i+2] +prelim3);
                pDst[i+3] = (KerY[0]*lines[1][i+3]+lines[0][i+3] +prelim4);

                pDstI[i]=prelim1;
                pDstI[i+1]=prelim2;
                pDstI[i+2]=prelim3;
                pDstI[i+3]=prelim4;
            
                
            
            }
            for(;i <= limitX; i++)
            {
                prelim = pS8u[BOUND(limitX,i+1)]-pS8u[i-1];
                pDst[i] = (KerY[0]*lines[1][i]+lines[0][i] +prelim);
                pDstI[i]=prelim;
            }
            break;
        case 26:
            prelim = (KerX[0]+1)*pS8u[0]+pS8u[1];
            pDst[0] = (prelim-lines[0][0]);
            pDstI[0]=prelim;
            for(i = 1; i < LX; i+=4)
            {
                prelim1 = KerX[0]*pS8u[i]+pS8u[i+1]+pS8u[i-1];
                prelim2 = KerX[0]*pS8u[i+1]+pS8u[i+2]+pS8u[i];
                prelim3 = KerX[0]*pS8u[i+2]+pS8u[i+3]+pS8u[i+1];
                prelim4 = KerX[0]*pS8u[i+3]+pS8u[i+4]+pS8u[i+2];
                pDst[i] = (prelim1 -lines[0][i]);
                pDst[i+1] = (prelim2-lines[0][i+1]);
                pDst[i+2] = (prelim3-lines[0][i+2]);
                pDst[i+3] = (prelim4-lines[0][i+3]);
                pDstI[i]=prelim1;
                pDstI[i+1]=prelim2;
                pDstI[i+2]=prelim3;
                pDstI[i+3]=prelim4;
                
                
            }
            for(;i <= limitX; i++)
            {
                prelim = KerX[0]*pS8u[i]+pS8u[BOUND(limitX,i+1)]+pS8u[i-1];
                pDst[i] = (prelim - lines[0][i]);
                pDstI[i]= prelim;
            }
            break;
        case 30:
            prelim = (KerX[0]+1)*pS8u[0]+pS8u[1];
            pDst[0] = (lines[0][0]-prelim);
            pDstI[0]=prelim;
            for(i = 1; i < LX; i+=4)
            {
                prelim1 = KerX[0]*pS8u[i]+pS8u[i+1]+pS8u[i-1];
                prelim2 = KerX[0]*pS8u[i+1]+pS8u[i+2]+pS8u[i];
                prelim3 = KerX[0]*pS8u[i+2]+pS8u[i+3]+pS8u[i+1];
                prelim4 = KerX[0]*pS8u[i+3]+pS8u[i+4]+pS8u[i+2];

                pDst[i] = (lines[0][i] - prelim1);
                pDst[i+1] = (lines[0][i+1]-prelim2);
                pDst[i+2] = (lines[0][i+2]-prelim3);
                pDst[i+3] = (lines[0][i+3]-prelim4);

                pDstI[i]=prelim1;
                pDstI[i+1]=prelim2;
                pDstI[i+2]=prelim3;
                pDstI[i+3]=prelim4;
                
                
            }
            for(;i <= limitX; i++)
            {
                prelim = KerX[0]*pS8u[i]+pS8u[BOUND(limitX,i+1)]+pS8u[i-1];
                pDst[i] = (lines[0][i] - prelim);
                pDstI[i]=prelim;
            }
            break;
        default: 
            if((pConS->kerType&3) == 3)
            {
                for(i = 0; i < Center; i++)
                {
                    prelim = 0;
                    ConvY =0;
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k]*(pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)];
                    pDst[i] = (ConvY + KerY[k] *(prelim - pDstI[i]));
                    pDstI[i]=prelim;
                }
                for(i = Center; i < LX; i+=4)
                {
                    
                    prelim1 = 0;
                    prelim2 = 0;
                    prelim3 = 0;
                    prelim4 = 0;
                
                    ConvY1 = 0;
                    ConvY2 = 0;
                    ConvY3 = 0;
                    ConvY4 = 0;
                    
                    for(k = 1; k < Center; k++)
                    {
                        prelim1 +=KerX[k]*(pS8u[i + k] - pS8u[i - k]);
                        prelim2 +=KerX[k]*(pS8u[i + k + 1] - pS8u[i - k +1]);
                        prelim3 +=KerX[k]*(pS8u[i + k + 2] - pS8u[i - k + 2]);
                        prelim4 +=KerX[k]*(pS8u[i + k + 3] - pS8u[i - k + 3]);
                    
                        ConvY1 += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                        ConvY2 += KerY[k] *(lines[Center+k][i+1]-lines[Center-k][i+1]);
                        ConvY3 += KerY[k] *(lines[Center+k][i+2]-lines[Center-k][i+2]);
                        ConvY4 += KerY[k] *(lines[Center+k][i+3]-lines[Center-k][i+3]);
                    }
                    prelim1 += pS8u[i + k] - pS8u[i - k];
                    prelim2 += pS8u[i + k + 1] - pS8u[i - k + 1];
                    prelim3 += pS8u[i + k + 2] - pS8u[i - k + 2];
                    prelim4 += pS8u[i + k + 3] - pS8u[i - k + 3];

                    pDst[i] = (ConvY1 + KerY[k]*(prelim1-pDstI[i]));
                    pDst[i+1] = (ConvY2 + KerY[k]*(prelim2-pDstI[i+1]));
                    pDst[i+2] = (ConvY3 + KerY[k]*(prelim3-pDstI[i+2]));
                    pDst[i+3] = (ConvY4 + KerY[k]*(prelim4-pDstI[i+3]));

                    pDstI[i]=prelim1;
                    pDstI[i+1]=prelim2;
                    pDstI[i+2]=prelim3;
                    pDstI[i+3]=prelim4;
                   
                }
            
                for(;i <= limitX; i++)
                {
                    prelim = 0;
                    ConvY =0;
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k] *
                        (pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)];                    
                    pDst[i] = (ConvY + KerY[k] *(prelim - pDstI[i]));
                    pDstI[i]=prelim;
                }
            }
            else if((pConS->kerType&3) == 2)
            {
                for(i = 0; i < Center; i++)
                {
                    prelim = KerX[0]*pS8u[i];
                    ConvY =0;
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k]*(pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)];
                    pDst[i] = (ConvY + KerY[k] *(prelim - pDstI[i]));
                    pDstI[i]=prelim;
                }
                for(i = Center; i < LX; i+=4)
                {
                    prelim1 = KerX[0]*pS8u[i];
                    prelim2 = KerX[0]*pS8u[i+1];
                    prelim3 = KerX[0]*pS8u[i+2];
                    prelim4 = KerX[0]*pS8u[i+3];
                
                    ConvY1 = 0;
                    ConvY2 = 0;
                    ConvY3 = 0;
                    ConvY4 = 0;
                    
                    for(k = 1; k < Center; k++)
                    {
                        prelim1 +=KerX[k]*(pS8u[i + k] + pS8u[i - k]);
                        prelim2 +=KerX[k]*(pS8u[i + k + 1] + pS8u[i - k +1]);
                        prelim3 +=KerX[k]*(pS8u[i + k + 2] + pS8u[i - k + 2]);
                        prelim4 +=KerX[k]*(pS8u[i + k + 3] + pS8u[i - k + 3]);
                    
                        ConvY1 += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                        ConvY2 += KerY[k] *(lines[Center+k][i+1]-lines[Center-k][i+1]);
                        ConvY3 += KerY[k] *(lines[Center+k][i+2]-lines[Center-k][i+2]);
                        ConvY4 += KerY[k] *(lines[Center+k][i+3]-lines[Center-k][i+3]);
                    }
                    prelim1 += pS8u[i + k] + pS8u[i - k];
                    prelim2 += pS8u[i + k + 1] + pS8u[i - k + 1];
                    prelim3 += pS8u[i + k + 2] + pS8u[i - k + 2];
                    prelim4 += pS8u[i + k + 3] + pS8u[i - k + 3];

                    pDst[i] = (ConvY1 + KerY[k]*(prelim1-pDstI[i]));
                    pDst[i+1] = (ConvY2 + KerY[k]*(prelim2-pDstI[i+1]));
                    pDst[i+2] = (ConvY3 + KerY[k]*(prelim3-pDstI[i+2]));
                    pDst[i+3] = (ConvY4 + KerY[k]*(prelim4-pDstI[i+3]));

                    pDstI[i]=prelim1;
                    pDstI[i+1]=prelim2;
                    pDstI[i+2]=prelim3;
                    pDstI[i+3]=prelim4;
                   
                }
            
                for(;i <= limitX; i++)
                {
                    prelim = KerX[0]*pS8u[i];
                    ConvY =0;
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k] *
                        (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]-lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)];                    
                    pDst[i] = (ConvY + KerY[k] *(prelim - pDstI[i]));
                    pDstI[i]=prelim;
                }
            }
            else if((pConS->kerType&3) == 1)
            {
                for(i = 0; i < Center; i++)
                {
                    prelim = 0;
                    ConvY =KerY[0]*lines[Center][i];
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k]*(pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] * (lines[Center+k][i]+lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)];
                    pDst[i] = (ConvY + prelim + pDstI[i]);
                    pDstI[i]=prelim;
                }
                for(i = Center; i < LX; i+=4)
                {
                    
                    prelim1 = 0;
                    prelim2 = 0;
                    prelim3 = 0;
                    prelim4 = 0;
                
                    ConvY1 = KerY[0]*lines[Center][i];
                    ConvY2 = KerY[0]*lines[Center][i+1];
                    ConvY3 = KerY[0]*lines[Center][i+2];
                    ConvY4 = KerY[0]*lines[Center][i+3];
                    
                    for(k = 1; k < Center; k++)
                    {
                        prelim1 +=KerX[k]*(pS8u[i + k] - pS8u[i - k]);
                        prelim2 +=KerX[k]*(pS8u[i + k + 1] - pS8u[i - k +1]);
                        prelim3 +=KerX[k]*(pS8u[i + k + 2] - pS8u[i - k + 2]);
                        prelim4 +=KerX[k]*(pS8u[i + k + 3] - pS8u[i - k + 3]);
                    
                        ConvY1 += KerY[k] *(lines[Center+k][i]+lines[Center-k][i]);
                        ConvY2 += KerY[k] *(lines[Center+k][i+1]+lines[Center-k][i+1]);
                        ConvY3 += KerY[k] *(lines[Center+k][i+2]+lines[Center-k][i+2]);
                        ConvY4 += KerY[k] *(lines[Center+k][i+3]+lines[Center-k][i+3]);
                    }
                    prelim1 += pS8u[i + k] - pS8u[i - k];
                    prelim2 += pS8u[i + k + 1] - pS8u[i - k + 1];
                    prelim3 += pS8u[i + k + 2] - pS8u[i - k + 2];
                    prelim4 += pS8u[i + k + 3] - pS8u[i - k + 3];

                    pDst[i] = (ConvY1 + prelim1 + pDstI[i]);
                    pDst[i+1] = (ConvY2 + prelim2 + pDstI[i+1]);
                    pDst[i+2] = (ConvY3 + prelim3 + pDstI[i+2]);
                    pDst[i+3] = (ConvY4 + prelim4 + pDstI[i+3]);

                    pDstI[i]=prelim1;
                    pDstI[i+1]=prelim2;
                    pDstI[i+2]=prelim3;
                    pDstI[i+3]=prelim4;
                   
                }
            
                for(;i <= limitX; i++)
                {
                    prelim = 0;
                    ConvY =KerY[0]*lines[Center][i];
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k] *
                        (pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]+lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)];                    
                    pDst[i] = (ConvY + prelim + pDstI[i]);
                    pDstI[i]=prelim;
                }
            }
            else
            {
                for(i = 0; i < Center; i++)
                {
                    prelim = KerX[0]*pS8u[i];
                    ConvY =KerY[0]*lines[Center][i];
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k]*(pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]+lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)];
                    pDst[i] = (ConvY + prelim + pDstI[i]);
                    pDstI[i]=prelim;
                }
                for(i = Center; i < LX; i+=4)
                {
                    prelim1 = KerX[0]*pS8u[i];
                    prelim2 = KerX[0]*pS8u[i+1];
                    prelim3 = KerX[0]*pS8u[i+2];
                    prelim4 = KerX[0]*pS8u[i+3];
                
                    ConvY1 =KerY[0]*lines[Center][i];
                    ConvY2 =KerY[0]*lines[Center][i+1];
                    ConvY3 =KerY[0]*lines[Center][i+2];
                    ConvY4 =KerY[0]*lines[Center][i+3];
                    
                    for(k = 1; k < Center; k++)
                    {
                        prelim1 +=KerX[k]*(pS8u[i + k] + pS8u[i - k]);
                        prelim2 +=KerX[k]*(pS8u[i + k + 1] + pS8u[i - k +1]);
                        prelim3 +=KerX[k]*(pS8u[i + k + 2] + pS8u[i - k + 2]);
                        prelim4 +=KerX[k]*(pS8u[i + k + 3] + pS8u[i - k + 3]);
                    
                        ConvY1 += KerY[k] *(lines[Center+k][i]+lines[Center-k][i]);
                        ConvY2 += KerY[k] *(lines[Center+k][i+1]+lines[Center-k][i+1]);
                        ConvY3 += KerY[k] *(lines[Center+k][i+2]+lines[Center-k][i+2]);
                        ConvY4 += KerY[k] *(lines[Center+k][i+3]+lines[Center-k][i+3]);
                    }
                    prelim1 += pS8u[i + k] + pS8u[i - k];
                    prelim2 += pS8u[i + k + 1] + pS8u[i - k + 1];
                    prelim3 += pS8u[i + k + 2] + pS8u[i - k + 2];
                    prelim4 += pS8u[i + k + 3] + pS8u[i - k + 3];

                    pDst[i] = (ConvY1 + prelim1+pDstI[i]);
                    pDst[i+1] = (ConvY2 + prelim2+pDstI[i+1]);
                    pDst[i+2] = (ConvY3 + prelim3+pDstI[i+2]);
                    pDst[i+3] = (ConvY4 + prelim4+pDstI[i+3]);

                    pDstI[i]=prelim1;
                    pDstI[i+1]=prelim2;
                    pDstI[i+2]=prelim3;
                    pDstI[i+3]=prelim4;
                   
                }
            
                for(;i <= limitX; i++)
                {
                    prelim = KerX[0]*pS8u[i];
                    ConvY =KerY[0]*lines[Center][i];
                    for(k = 1; k < Center; k++)
                    {
                        prelim += KerX[k] *
                        (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                        ConvY += KerY[k] *(lines[Center+k][i]+lines[Center-k][i]);
                    }
                    prelim += pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)];                    
                    pDst[i] = (ConvY + prelim + pDstI[i]);
                    pDstI[i]=prelim;
                }
            }
            break;
            }
       
        /* Rotating cyclic buffer */ 
        Temp = lines[0];
        for(k = 0; k < Len-2; k++)
        {
           lines[k]=lines[k + 1];
        }
        lines[Len-2] = Temp;
        obtain_rows++;
        pDst+=destStep/4;
        pS8u += srcStep/4;

    }

    if(ownstage&CV_END)
    {
        
        int Fin = Center - pConS->initialized;
		if(pConS->initialized)
		{
			for(t = 0; t < pConS->initialized; t++)
			{
				memcpy(lines[Len-2-t],lines[Len-2-pConS->initialized],curROI->width*4);
			}
		}
        memcpy(lines[Len-1], lines[Len-2], curROI->width*4);
        for(t = 0; t < Fin; t++)
        {
            if(pConS->kerType&2)
            {
                for(i = 0; i < curROI->width; i++)
                {
            
                    ConvY = 0;
                    for(j = 1; j <= Center; j++)
                    {
                        ConvY += KerY[j] *(lines[Center+j][i]-lines[Center-j][i]);
                    }
                    pDst[i] = (ConvY);
                }
            }
            else
            {
                for(i = 0; i < curROI->width; i++)
                {
                    ConvY = KerY[0]*lines[Center][i];
                    for(j = 1; j <= Center; j++)
                    {
                        ConvY += KerY[j] *(lines[Center-j][i]+lines[Center+j][i]);
                    }
                    pDst[i] = (ConvY);
                }
            }
            memcpy(lines[0], lines[Len-1], curROI->width*4);
            Temp = lines[0];
            for(k = 0; k < Len-1; k++)
            {
                lines[k]=lines[k + 1];
            }
            lines[Len-1] = Temp;
            pDst+=destStep/4;
            obtain_rows++;
        }
    }
	
    curROI->height=obtain_rows;    
    return CV_NO_ERR;
}

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    _cvSepConvSmall3_32f
//    Purpose:
//      Performs separable convolution given 3x3, 3x1 or 1x3 kernel
//    Context:
//    Parameters:
//      src        - source image ROI
//      src_step   - full width of source image (in bytes)
//      dst        - destination image ROI
//      dst_step   - full width of destination image (in bytes)
//      src_size   - size of source image ROI (width & height)
//      kx         - horizontal kernel - array of 3 numbers. anchor is in the middle.
//                   if NULL then only vertical covolution is applied.
//      ky         - vertical kernel - array of 3 numbers. anchor is in the middle.
//                   if NULL then only horizontal covolution is applied.
//      buffer     - temporary buffer. Used only if both kernels are not NULL.
//                   In the last case, it must be, at least,
//                   (src_size - 2)*sizeof(float) bytes.
//    Returns:
//      Nothing       
//    Notes:
//      Size of destination ROI is not passed into the function, because
//      it assumes dst ROI size:
//      = (src_size.width - 2, src_size.height - 2) if both kernels are used
//      = (src_size.width - 2, src_size.height)     if horizontal kernel != 0 only.
//      = (src_size.width, src_size.height - 2)     if vertical kernel != 0 only.
F*/
void icvSepConvSmall3_32f( float*  src, int src_step,
                           float*  dst, int dst_step,
                           CvSize src_size,
                           const float* kx, const float* ky,
                           float*  buffer )
{
    int  dst_width, buffer_step = 0;
    int  x, y;
    
    assert( src && dst && src_size.width > 2 && src_size.height > 2 &&
            (src_step & 3) == 0 && (dst_step & 3) == 0 &&
            (kx || ky) && (buffer || !kx || !ky));

    src_step >>= 2;
    dst_step >>= 2;

    dst_width = src_size.width - 2;

    if( !kx )
    {
        /* set vars, so that vertical convolution 
           will write results into destination ROI and
           horizontal convolution won't run */
        src_size.width = dst_width;
        buffer_step = dst_step;
        buffer = dst;
        dst_width = 0;
    }

    assert( src_step >= src_size.width && dst_step >= dst_width );
    
    src_size.height -= 3;
    if( !ky )
    {
        /* set vars, so that vertical convolution won't run and 
           horizontal convolution will write results into destination ROI and */
        src_size.height += 3;
        buffer_step = src_step;
        buffer = src;
        src_size.width = 0;
    }


    for( y = 0; y <= src_size.height; y++, src += src_step,
                                           dst += dst_step,
                                           buffer += buffer_step )
    {
        float* src2 = src + src_step;
        float* src3 = src + src_step*2;
        for( x = 0; x < src_size.width; x++ )
        {
            buffer[x] = (float)(ky[0]*src[x] + ky[1]*src2[x] + ky[2]*src3[x]);
        }

        for( x = 0; x < dst_width; x++ )
        {
            dst[x] = (float)(kx[0]*buffer[x] + kx[1]*buffer[x+1] + kx[2]*buffer[x+2]);
        }
    }
}

/* End of file. */
