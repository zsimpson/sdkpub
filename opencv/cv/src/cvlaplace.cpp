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
#define BUFF_SIZE 8192
#include "_cv.h"

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:     CvlLaplace8uC1R
//    Purpose:  Calculating Laplasian on image
//    Context:
//    Parameters:
//              pSrc       - pointer to the source image ROI
//              SrcStep    - width of the full Src image in bytes
//              pDst       - pointer to the resultant image
//              DstStep  - width of resultant array in bytes
//              roi        - pointer to the roi structure
//              opSize     - parameter of operator size
//    Returns:  CV_NO_ERR if all ok or error code
//    Notes:
//F*/
#define BOUND(rbound,x) ((((x)<0)-1)&MIN((rbound),(x)))
#define SAT(x) MIN(MAX(x,-32768),32767)
/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:     CvlLaplace8uC1R
//    Purpose:  Calculating Laplasian on image
//    Context:
//    Parameters:
//              pSrc       - pointer to the source image ROI
//              SrcStep    - width of the full Src image in bytes
//              pDst       - pointer to the resultant image
//              DstStep  - width of resultant array in bytes
//              roi        - pointer to the roi structure
//              opSize     - parameter of operator size
//    Returns:  CV_NO_ERR if all ok or error code
//    Notes:
//F*/
IPCVAPI_IMPL( CvStatus, icvLaplace_8u16s_C1R, (const unsigned char *pSrc,
                                               int srcStep,
                                               short *pDest,
                                               int destStep,
                                               CvSize * curROI,
                                               _CvConvState * pConS, int stage) )
{
    int i,k,t,Len,Center,limitX,Temp;
    int** lines1;
    int** lines2;
    int* KerX;
    int* KerY;
    short* pDst;
    int* pDstI1;
    int* pDstI2;
    int obtain_rows=0;
    int ownstage = (stage)?stage:CV_START|CV_END;
    int* Tempp1;
    int* Tempp2;
    unsigned char* pS8u=(unsigned char*)pSrc;
    int ConvY1,ConvY2;
    int prelim1, prelim2,t0,t1,t2;

	Len = pConS->kerType>>3;
    lines1 = (int**)(pConS->lines);
    lines2 = (int**)(&(pConS->lines[Len]));
    Center = Len/2;
    KerX = (int*)pConS->KerX+Center;
    KerY = (int*)pConS->KerY+Center;
    pDst = pDest;
    limitX = (*curROI).width-1;
    pS8u=(unsigned char*)pSrc;
    t = 0;
    if(ownstage&CV_START)
    {
       for(i = 0; i < Center; i++)
       {
           prelim1 = KerX[0] * pS8u[i];
           prelim2 = KerY[0] * pS8u[i];
           for(k = 1; k <=Center; k++)
           {
               Temp = pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)];
               prelim1 += KerX[k] * Temp;
               prelim2 += KerY[k] * Temp; 
           }
           for(k = 0; k<=Center; k++)
           {
               lines1[k][i] = prelim1;
               lines2[k][i] = prelim2;
           }
       }

       for(; i <= limitX - Center; i++)
       {
            prelim1 = KerX[0] * pS8u[i];
            prelim2 = KerY[0] * pS8u[i];
            for(k = 1; k <=Center; k++)
            {
                Temp = pS8u[i + k]+pS8u[i - k];
                prelim1 += KerX[k] * Temp;
                prelim2 += KerY[k] * Temp; 
            }
            for(k = 0; k<=Center; k++)
            {
               lines1[k][i] = prelim1;
               lines2[k][i] = prelim2;
            }
        }
        for(; i <=limitX; i++)
        {
            prelim1 = KerX[0] * pS8u[i];
            prelim2 = KerY[0] * pS8u[i];
            for(k = 1; k <=Center; k++)
            {
                Temp = pS8u[BOUND(limitX,i + k)]+pS8u[i - k];
                prelim1 += KerX[k] * Temp;
                prelim2 += KerY[k] * Temp; 
            }
            for(k = 0; k<=Center; k++)
            {
               lines1[k][i] = prelim1;
               lines2[k][i] = prelim2;
            }
        }
        pConS->initialized=Center-1;
        pS8u += srcStep;
        curROI->height--;
    }
    while((curROI->height)&&(pConS->initialized))
    {
       pDstI1 = lines1[Len-1-pConS->initialized];
       pDstI2 = lines2[Len-1-pConS->initialized];
       for(i = 0; i < Center; i++)
       {
          prelim1 = KerX[0] * pS8u[i];
          prelim2 = KerY[0] * pS8u[i];
           for(k = 1; k <=Center; k++)
           {
               Temp = pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)];
               prelim1 += KerX[k] * Temp;
               prelim2 += KerY[k] * Temp; 
           }
           pDstI1[i] = prelim1;
           pDstI2[i] = prelim2; 
        }

        for(; i <= limitX-Center; i++)
        {
            prelim1 = KerX[0] * pS8u[i];
            prelim2 = KerY[0] * pS8u[i];
            for(k = 1; k <=Center; k++)
            {
                Temp = pS8u[i + k]+pS8u[i - k];
                prelim1 += KerX[k] * Temp;
                prelim2 += KerY[k] * Temp; 
            }
            pDstI1[i] = prelim1;
            pDstI2[i] = prelim2;
        }
        for(; i <= limitX; i++)
        {
            prelim1 = KerX[0] * pS8u[i];
            prelim2 = KerY[0] * pS8u[i];
            for(k = 1; k <=Center; k++)
            {
                Temp = pS8u[BOUND(limitX,i + k)]+pS8u[i - k];
                prelim1 += KerX[k] * Temp;
                prelim2 += KerY[k] * Temp; 
            }
            pDstI1[i] = prelim1;
            pDstI2[i] = prelim2;
        }
        pConS->initialized--;
        pS8u += srcStep;
        curROI->height--;
    }                
    
    /* main loop */
    pDst = pDest;
    for(t = 0;t < curROI->height;t++)
    {
        if(Len == 3)
        {
            prelim1 = pS8u[1] - pS8u[0];
            prelim2 = pS8u[1] + 3 *pS8u[0];
            pDst[0] = (short)(lines1[0][0]+lines2[0][0]+prelim1+prelim2+2*(lines1[1][0]-lines2[1][0]));
            lines1[0][0]=prelim1;
            lines2[0][0]=prelim2;
            for(i = 1; i < limitX; i++)
            {
                t1 = pS8u[i+1]+pS8u[i-1];
                t2 =  2 *pS8u[i];
                prelim1 = t1 - t2;
                prelim2 = t1 + t2;
                pDst[i] = (short)(lines1[0][i]+lines2[0][i]+prelim1+prelim2+2*(lines1[1][i]-lines2[1][i]));
                lines1[0][i]=prelim1;
                lines2[0][i]=prelim2;
            }
            prelim1 = pS8u[i-1] - pS8u[i];
            prelim2 = pS8u[i-1] + 3 *pS8u[i];
            pDst[i] = (short)(lines1[0][i]+lines2[0][i]+prelim1+prelim2+2*(lines1[1][i]-lines2[1][i]));
            lines1[0][i]=prelim1;
            lines2[0][i]=prelim2;
            
        }
        else if(Len == 5)
        {
            prelim1 = pS8u[2] - pS8u[0];
            prelim2 = pS8u[2] + 4*pS8u[1] + 11 *pS8u[0];
            pDst[0] = (short)(lines1[0][0]+lines2[0][0]+prelim1+prelim2+
                              4 * (lines1[1][0]+lines1[3][0])+  
                              6*lines1[2][0]-2 * lines2[2][0]);
            lines1[0][0]=prelim1;
            lines2[0][0]=prelim2;
            prelim1 = pS8u[3] - 2 *pS8u[1] + pS8u[0];
            prelim2 = pS8u[3]+5*pS8u[0] + 4*+pS8u[2] + 6 *pS8u[1];
            pDst[1] = (short)(lines1[0][1]+lines2[0][1]+prelim1+prelim2+
                              4 * (lines1[1][1]+lines1[3][1])+  
                              6*lines1[2][1]-2 * lines2[2][1]);
            lines1[0][1]=prelim1;
            lines2[0][1]=prelim2;

            for(i = 2; i < limitX-1; i++)
            {
                t0 = pS8u[i];
                t1 = pS8u[i+1]+pS8u[i-1];
                t2 = pS8u[i+2]+pS8u[i-2];
                prelim1 = t2 - 2*t0;
                prelim2 = t2+4*t1+6*t0;
                pDst[i] = (short)(lines1[0][i]+lines2[0][i]+prelim1+prelim2+
                              4 * (lines1[1][i]+lines1[3][i])+  
                              6*lines1[2][i]-2 * lines2[2][i]);
            
                lines1[0][i]=prelim1;
                lines2[0][i]=prelim2;
            }
            t0 = pS8u[i];
            t1 = pS8u[i+1]+pS8u[i-1];
            t2 = pS8u[i+1]+pS8u[i-2];
            prelim1 = t2 - 2*t0;
            prelim2 = t2+4*t1+6*t0;
            pDst[i] = (short)(lines1[0][i]+lines2[0][i]+prelim1+prelim2+
                              4 * (lines1[1][i]+lines1[3][i])+  
                              6*lines1[2][i]-2 * lines2[2][i]);
            
            lines1[0][i]=prelim1;
            lines2[0][i]=prelim2;
            i++;
            t0 = pS8u[i];
            t1 = pS8u[i]+pS8u[i-1];
            t2 = pS8u[i]+pS8u[i-2];
            prelim1 = t2 - 2*t0;
            prelim2 = t2+4*t1+6*t0;
            pDst[i] = (short)(lines1[0][i]+lines2[0][i]+prelim1+prelim2+
                              4 * (lines1[1][i]+lines1[3][i])+  
                              6*lines1[2][i]-2 * lines2[2][i]);
            
            lines1[0][i]=prelim1;
            lines2[0][i]=prelim2;            
        }
        else
        {
            for(i = 0; i < Center; i++)
            {
                prelim1 = KerX[0] * pS8u[i];
                prelim2 = KerY[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                    Temp = pS8u[i + k]+pS8u[BOUND(limitX,i - k)];
                    prelim1 += KerX[k] * Temp;
                    prelim2 += KerY[k] * Temp; 
                }
                ConvY1 = KerY[0]*lines1[Center][i];
                ConvY2 = KerX[0]*lines2[Center][i];
                for(k = 1; k < Center; k++)
                {
                    ConvY1 += KerY[k] *(lines1[Center+k][i]+lines1[Center-k][i]);
                    ConvY2 += KerX[k] *(lines2[Center+k][i]+lines2[Center-k][i]);
                }
                pDst[i] = (short)SAT(ConvY1 + KerY[k] *(prelim1 + lines1[Center-k][i])+
                              ConvY2 + KerX[k] *(prelim2 + lines2[Center-k][i]));
                lines1[0][i]=prelim1;
                lines2[0][i]=prelim2;
            }
            for(; i <= limitX - Center; i++)
            {
                prelim1 = KerX[0] * pS8u[i];
                prelim2 = KerY[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                    Temp = pS8u[i + k] + pS8u[i - k];
                    prelim1 += KerX[k] * Temp;
                    prelim2 += KerY[k] * Temp; 
                }
                ConvY1 = KerY[0]*lines1[Center][i];
                ConvY2 = KerX[0]*lines2[Center][i];
                for(k = 1; k < Center; k++)
                {
                    ConvY1 += KerY[k] *(lines1[Center+k][i]+lines1[Center-k][i]);
                    ConvY2 += KerX[k] *(lines2[Center+k][i]+lines2[Center-k][i]);
                }
                pDst[i] = (short)SAT(ConvY1 + KerY[k] *(prelim1 + lines1[Center-k][i])+
                              ConvY2 + KerX[k] *(prelim2 + lines2[Center-k][i]));
                lines1[0][i]=prelim1;
                lines2[0][i]=prelim2;
            }
            for(; i <= limitX; i++)
            {
                prelim1 = KerX[0] * pS8u[i];
                prelim2 = KerY[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                    Temp = pS8u[BOUND(limitX,i + k)]+pS8u[i - k];
                    prelim1 += KerX[k] * Temp;
                    prelim2 += KerY[k] * Temp; 
                }
                ConvY1 = KerY[0]*lines1[Center][i];
                ConvY2 = KerX[0]*lines2[Center][i];
                for(k = 1; k < Center; k++)
                {
                    ConvY1 += KerY[k] *(lines1[Center+k][i]+lines1[Center-k][i]);
                    ConvY2 += KerX[k] *(lines2[Center+k][i]+lines2[Center-k][i]);
                }
                pDst[i] = (short)SAT(ConvY1 + KerY[k] *(prelim1 + lines1[Center-k][i])+
                              ConvY2 + KerX[k] *(prelim2 + lines2[Center-k][i]));
                lines1[0][i]=prelim1;
                lines2[0][i]=prelim2;
            }
        }

        /* Rotating cyclic buffer */ 
        Tempp1 = lines1[0];
        Tempp2 = lines2[0];
        for(k = 0; k < Len-2; k++)
        {
            lines1[k]=lines1[k + 1];
            lines2[k]=lines2[k + 1];
        }
        lines1[Len-2] = Tempp1;
        lines2[Len-2] = Tempp2;
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
				memcpy(lines1[Len-2-t],lines1[Len-2-pConS->initialized],curROI->width*4);
				memcpy(lines2[Len-2-t],lines2[Len-2-pConS->initialized],curROI->width*4);
			}
		}
        memcpy(lines1[Len-1],lines1[Len-2], curROI->width*4);
        memcpy(lines2[Len-1],lines2[Len-2], curROI->width*4);
            
        for(t = 0; t < Fin; t++)
        {

            for(i = 0; i < curROI->width; i++)
            {
                ConvY1 = KerY[0]*lines1[Center][i];
                ConvY2 = KerX[0]*lines2[Center][i];
                for(k = 1; k <= Center; k++)
                {
                    ConvY1 += KerY[k] *(lines1[Center+k][i]+lines1[Center-k][i]);
                    ConvY2 += KerX[k] *(lines2[Center+k][i]+lines2[Center-k][i]);
                }
                pDst[i] = (short)SAT(ConvY1 + ConvY2);
                            
            }
            memcpy(lines1[0],lines1[Len-1], curROI->width*4);
            memcpy(lines2[0],lines2[Len-1], curROI->width*4);
            Tempp1 = lines1[0];
            Tempp2 = lines2[0];
            for(k = 0; k < Len-1; k++)
            {
                lines1[k]=lines1[k + 1];
                lines2[k]=lines2[k + 1];
            }
            lines1[Len-2] = Tempp1;
            lines2[Len-2] = Tempp2;
            
            pDst+=destStep/2;
            obtain_rows++;
        }
    }
    curROI->height=obtain_rows;    
    return CV_NO_ERR;
}

IPCVAPI_IMPL( CvStatus, icvLaplace_8s16s_C1R, (const char *pSrc,
                                               int srcStep,
                                               short *pDest,
                                               int destStep,
                                               CvSize * curROI,
                                               _CvConvState * pConS, int stage) )
{
int i,k,t,Len,Center,limitX,Temp;
    int** lines1;
    int** lines2;
    int* KerX;
    int* KerY;
    short* pDst;
    int* pDstI1;
    int* pDstI2;
    int obtain_rows=0;
    int ownstage = (stage)?stage:CV_START|CV_END;
    int* Tempp1;
    int* Tempp2;
    char* pS8u=(char*)pSrc;
    int ConvY1,ConvY2;
    int prelim1, prelim2,t0,t1,t2;
	Len = pConS->kerType>>3;
    lines1 = (int**)(pConS->lines);
    lines2 = (int**)(&(pConS->lines[Len]));
    Center = Len/2;
    KerX = (int*)pConS->KerX+Center;
    KerY = (int*)pConS->KerY+Center;
    pDst = pDest;
    limitX = (*curROI).width-1;
    t = 0;
    if(ownstage&CV_START)
    {
       for(i = 0; i < Center; i++)
       {
           prelim1 = KerX[0] * pS8u[i];
           prelim2 = KerY[0] * pS8u[i];
           for(k = 1; k <=Center; k++)
           {
               Temp = pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)];
               prelim1 += KerX[k] * Temp;
               prelim2 += KerY[k] * Temp; 
           }
           for(k = 0; k<=Center; k++)
           {
               lines1[k][i] = prelim1;
               lines2[k][i] = prelim2;
           }
       }

       for(; i <= limitX - Center; i++)
       {
            prelim1 = KerX[0] * pS8u[i];
            prelim2 = KerY[0] * pS8u[i];
            for(k = 1; k <=Center; k++)
            {
                Temp = pS8u[i + k]+pS8u[i - k];
                prelim1 += KerX[k] * Temp;
                prelim2 += KerY[k] * Temp; 
            }
            for(k = 0; k<=Center; k++)
            {
               lines1[k][i] = prelim1;
               lines2[k][i] = prelim2;
            }
        }
        for(; i <=limitX; i++)
        {
            prelim1 = KerX[0] * pS8u[i];
            prelim2 = KerY[0] * pS8u[i];
            for(k = 1; k <=Center; k++)
            {
                Temp = pS8u[BOUND(limitX,i + k)]+pS8u[i - k];
                prelim1 += KerX[k] * Temp;
                prelim2 += KerY[k] * Temp; 
            }
            for(k = 0; k<=Center; k++)
            {
               lines1[k][i] = prelim1;
               lines2[k][i] = prelim2;
            }
        }
        pConS->initialized=Center-1;
        pS8u += srcStep;
        curROI->height--;
    }
    while((curROI->height)&&(pConS->initialized))
    {
       pDstI1 = lines1[Len-1-pConS->initialized];
       pDstI2 = lines2[Len-1-pConS->initialized];
       for(i = 0; i < Center; i++)
       {
          prelim1 = KerX[0] * pS8u[i];
          prelim2 = KerY[0] * pS8u[i];
           for(k = 1; k <=Center; k++)
           {
               Temp = pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)];
               prelim1 += KerX[k] * Temp;
               prelim2 += KerY[k] * Temp; 
           }
           pDstI1[i] = prelim1;
           pDstI2[i] = prelim2; 
        }

        for(; i <= limitX-Center; i++)
        {
            prelim1 = KerX[0] * pS8u[i];
            prelim2 = KerY[0] * pS8u[i];
            for(k = 1; k <=Center; k++)
            {
                Temp = pS8u[i + k]+pS8u[i - k];
                prelim1 += KerX[k] * Temp;
                prelim2 += KerY[k] * Temp; 
            }
            pDstI1[i] = prelim1;
            pDstI2[i] = prelim2;
        }
        for(; i <= limitX; i++)
        {
            prelim1 = KerX[0] * pS8u[i];
            prelim2 = KerY[0] * pS8u[i];
            for(k = 1; k <=Center; k++)
            {
                Temp = pS8u[BOUND(limitX,i + k)]+pS8u[i - k];
                prelim1 += KerX[k] * Temp;
                prelim2 += KerY[k] * Temp; 
            }
            pDstI1[i] = prelim1;
            pDstI2[i] = prelim2;
        }
        pConS->initialized--;
        pS8u += srcStep;
        curROI->height--;
    }                
    
    /* main loop */
    pDst = pDest;
    for(t = 0;t < curROI->height;t++)
    {
        if(Len == 3)
        {
            prelim1 = pS8u[1] - pS8u[0];
            prelim2 = pS8u[1] + 3 *pS8u[0];
            pDst[0] = (short)(lines1[0][0]+lines2[0][0]+prelim1+prelim2+2*(lines1[1][0]-lines2[1][0]));
            lines1[0][0]=prelim1;
            lines2[0][0]=prelim2;
            for(i = 1; i < limitX; i++)
            {
                t1 = pS8u[i+1]+pS8u[i-1];
                t2 =  2 *pS8u[i];
                prelim1 = t1 - t2;
                prelim2 = t1 + t2;
                pDst[i] = (short)(lines1[0][i]+lines2[0][i]+prelim1+prelim2+2*(lines1[1][i]-lines2[1][i]));
                lines1[0][i]=prelim1;
                lines2[0][i]=prelim2;
            }
            prelim1 = pS8u[i-1] - pS8u[i];
            prelim2 = pS8u[i-1] + 3 *pS8u[i];
            pDst[i] = (short)(lines1[0][i]+lines2[0][i]+prelim1+prelim2+2*(lines1[1][i]-lines2[1][i]));
            lines1[0][i]=prelim1;
            lines2[0][i]=prelim2;
            
        }
        else if(Len == 5)
        {
            prelim1 = pS8u[2] - pS8u[0];
            prelim2 = pS8u[2] + 4*pS8u[1] + 11 *pS8u[0];
            pDst[0] = (short)(lines1[0][0]+lines2[0][0]+prelim1+prelim2+
                              4 * (lines1[1][0]+lines1[3][0])+  
                              6*lines1[2][0]-2 * lines2[2][0]);
            lines1[0][0]=prelim1;
            lines2[0][0]=prelim2;
            prelim1 = pS8u[3] - 2 *pS8u[1] + pS8u[0];
            prelim2 = pS8u[3]+5*pS8u[0] + 4*+pS8u[2] + 6 *pS8u[1];
            pDst[1] = (short)(lines1[0][1]+lines2[0][1]+prelim1+prelim2+
                              4 * (lines1[1][1]+lines1[3][1])+  
                              6*lines1[2][1]-2 * lines2[2][1]);
            lines1[0][1]=prelim1;
            lines2[0][1]=prelim2;

            for(i = 2; i < limitX-1; i++)
            {
                t0 = pS8u[i];
                t1 = pS8u[i+1]+pS8u[i-1];
                t2 = pS8u[i+2]+pS8u[i-2];
                prelim1 = t2 - 2*t0;
                prelim2 = t2+4*t1+6*t0;
                pDst[i] = (short)(lines1[0][i]+lines2[0][i]+prelim1+prelim2+
                              4 * (lines1[1][i]+lines1[3][i])+  
                              6*lines1[2][i]-2 * lines2[2][i]);
            
                lines1[0][i]=prelim1;
                lines2[0][i]=prelim2;
            }
            t0 = pS8u[i];
            t1 = pS8u[i+1]+pS8u[i-1];
            t2 = pS8u[i+1]+pS8u[i-2];
            prelim1 = t2 - 2*t0;
            prelim2 = t2+4*t1+6*t0;
            pDst[i] = (short)(lines1[0][i]+lines2[0][i]+prelim1+prelim2+
                              4 * (lines1[1][i]+lines1[3][i])+  
                              6*lines1[2][i]-2 * lines2[2][i]);
            
            lines1[0][i]=prelim1;
            lines2[0][i]=prelim2;
            i++;
            t0 = pS8u[i];
            t1 = pS8u[i]+pS8u[i-1];
            t2 = pS8u[i]+pS8u[i-2];
            prelim1 = t2 - 2*t0;
            prelim2 = t2+4*t1+6*t0;
            pDst[i] = (short)(lines1[0][i]+lines2[0][i]+prelim1+prelim2+
                              4 * (lines1[1][i]+lines1[3][i])+  
                              6*lines1[2][i]-2 * lines2[2][i]);
            
            lines1[0][i]=prelim1;
            lines2[0][i]=prelim2;            
        }
        else
        {
            for(i = 0; i < Center; i++)
            {
                prelim1 = KerX[0] * pS8u[i];
                prelim2 = KerY[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                    Temp = pS8u[i + k]+pS8u[BOUND(limitX,i - k)];
                    prelim1 += KerX[k] * Temp;
                    prelim2 += KerY[k] * Temp; 
                }
                ConvY1 = KerY[0]*lines1[Center][i];
                ConvY2 = KerX[0]*lines2[Center][i];
                for(k = 1; k < Center; k++)
                {
                    ConvY1 += KerY[k] *(lines1[Center+k][i]+lines1[Center-k][i]);
                    ConvY2 += KerX[k] *(lines2[Center+k][i]+lines2[Center-k][i]);
                }
                pDst[i] = (short)SAT(ConvY1 + KerY[k] *(prelim1 + lines1[Center-k][i])+
                              ConvY2 + KerX[k] *(prelim2 + lines2[Center-k][i]));
                lines1[0][i]=prelim1;
                lines2[0][i]=prelim2;
            }
            for(; i <= limitX - Center; i++)
            {
                prelim1 = KerX[0] * pS8u[i];
                prelim2 = KerY[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                    Temp = pS8u[i + k] + pS8u[i - k];
                    prelim1 += KerX[k] * Temp;
                    prelim2 += KerY[k] * Temp; 
                }
                ConvY1 = KerY[0]*lines1[Center][i];
                ConvY2 = KerX[0]*lines2[Center][i];
                for(k = 1; k < Center; k++)
                {
                    ConvY1 += KerY[k] *(lines1[Center+k][i]+lines1[Center-k][i]);
                    ConvY2 += KerX[k] *(lines2[Center+k][i]+lines2[Center-k][i]);
                }
                pDst[i] = (short)SAT(ConvY1 + KerY[k] *(prelim1 + lines1[Center-k][i])+
                              ConvY2 + KerX[k] *(prelim2 + lines2[Center-k][i]));
                lines1[0][i]=prelim1;
                lines2[0][i]=prelim2;
            }
            for(; i <= limitX; i++)
            {
                prelim1 = KerX[0] * pS8u[i];
                prelim2 = KerY[0] * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                    Temp = pS8u[BOUND(limitX,i + k)]+pS8u[i - k];
                    prelim1 += KerX[k] * Temp;
                    prelim2 += KerY[k] * Temp; 
                }
                ConvY1 = KerY[0]*lines1[Center][i];
                ConvY2 = KerX[0]*lines2[Center][i];
                for(k = 1; k < Center; k++)
                {
                    ConvY1 += KerY[k] *(lines1[Center+k][i]+lines1[Center-k][i]);
                    ConvY2 += KerX[k] *(lines2[Center+k][i]+lines2[Center-k][i]);
                }
                pDst[i] = (short)SAT(ConvY1 + KerY[k] *(prelim1 + lines1[Center-k][i])+
                              ConvY2 + KerX[k] *(prelim2 + lines2[Center-k][i]));
                lines1[0][i]=prelim1;
                lines2[0][i]=prelim2;
            }
        }

        /* Rotating cyclic buffer */ 
        Tempp1 = lines1[0];
        Tempp2 = lines2[0];
        for(k = 0; k < Len-2; k++)
        {
            lines1[k]=lines1[k + 1];
            lines2[k]=lines2[k + 1];
        }
        lines1[Len-2] = Tempp1;
        lines2[Len-2] = Tempp2;
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
				memcpy(lines1[Len-2-t],lines1[Len-2-pConS->initialized],curROI->width*4);
				memcpy(lines2[Len-2-t],lines2[Len-2-pConS->initialized],curROI->width*4);
			}
		}
        memcpy(lines1[Len-1],lines1[Len-2], curROI->width*4);
        memcpy(lines2[Len-1],lines2[Len-2], curROI->width*4);
            
        for(t = 0; t < Fin; t++)
        {

            for(i = 0; i < curROI->width; i++)
            {
                ConvY1 = KerY[0]*lines1[Center][i];
                ConvY2 = KerX[0]*lines2[Center][i];
                for(k = 1; k <= Center; k++)
                {
                    ConvY1 += KerY[k] *(lines1[Center+k][i]+lines1[Center-k][i]);
                    ConvY2 += KerX[k] *(lines2[Center+k][i]+lines2[Center-k][i]);
                }
                pDst[i] = (short)SAT(ConvY1 + ConvY2);
                            
            }
            memcpy(lines1[0],lines1[Len-1], curROI->width*4);
            memcpy(lines2[0],lines2[Len-1], curROI->width*4);
            Tempp1 = lines1[0];
            Tempp2 = lines2[0];
            for(k = 0; k < Len-1; k++)
            {
                lines1[k]=lines1[k + 1];
                lines2[k]=lines2[k + 1];
            }
            lines1[Len-2] = Tempp1;
            lines2[Len-2] = Tempp2;
            
            pDst+=destStep/2;
            obtain_rows++;
        }
    }
    curROI->height=obtain_rows;    
    return CV_NO_ERR;
}

IPCVAPI_IMPL( CvStatus, icvLaplace_32f_C1R, (const float *pSrc,
                                             int srcStep,
                                             float *pDest,
                                             int destStep,
                                             CvSize * curROI,
                                             _CvConvState * pConS, int stage) )
{
    /* Some Variables */
    int i, k, t;
    int Len = pConS->kerType >> 3;
    float **lines1 = (float **) (pConS->lines);
    float **lines2 = (float **) (&(pConS->lines[Len]));
    int Center = Len / 2;
    float *KerX = ((float *) pConS->KerX) + Center;
    float *KerY = ((float *) pConS->KerY) + Center;
    float *pDst = pDest;
    float *pDstI1;
    float *pDstI2;
    int limitX = curROI->width - 1;
    int obtain_rows = 0;
    int ownstage = (stage) ? stage : CV_START | CV_END;
    float Temp;
    float *Tempp1;
    float *Tempp2;
    float *pS8u = (float *) pSrc;
    float ConvY1, ConvY2;
    float prelim1, prelim2;

    t = 0;
    srcStep /= 4;
    destStep /= 4;
    if( ownstage & CV_START )
    {
        for( i = 0; i < Center; i++ )
        {
            prelim1 = KerX[0] * pS8u[i];
            prelim2 = KerY[0] * pS8u[i];
            for( k = 1; k <= Center; k++ )
            {
                Temp = pS8u[BOUND( limitX, i + k )] + pS8u[BOUND( limitX, i - k )];
                prelim1 += KerX[k] * Temp;
                prelim2 += KerY[k] * Temp;
            }
            for( k = 0; k <= Center; k++ )
            {
                lines1[k][i] = prelim1;
                lines2[k][i] = prelim2;
            }
        }

        for( i = Center; i < limitX - Center + 1; i++ )
        {
            prelim1 = KerX[0] * pS8u[i];
            prelim2 = KerY[0] * pS8u[i];
            for( k = 1; k <= Center; k++ )
            {
                Temp = pS8u[i + k] + pS8u[i - k];
                prelim1 += KerX[k] * Temp;
                prelim2 += KerY[k] * Temp;
            }
            for( k = 0; k <= Center; k++ )
            {
                lines1[k][i] = prelim1;
                lines2[k][i] = prelim2;
            }
        }
        for( i = limitX + 1 - Center; i < limitX + 1; i++ )
        {
            prelim1 = KerX[0] * pS8u[i];
            prelim2 = KerY[0] * pS8u[i];
            for( k = 1; k <= Center; k++ )
            {
                Temp = pS8u[BOUND( limitX, i + k )] + pS8u[i - k];
                prelim1 += KerX[k] * Temp;
                prelim2 += KerY[k] * Temp;
            }
            for( k = 0; k <= Center; k++ )
            {
                lines1[k][i] = prelim1;
                lines2[k][i] = prelim2;
            }
        }
        pConS->initialized = Center - 1;
        pS8u += srcStep;
        curROI->height--;
    }
    while( (curROI->height) && (pConS->initialized) )
    {
        pDstI1 = lines1[Len - 1 - pConS->initialized];
        pDstI2 = lines2[Len - 1 - pConS->initialized];
        for( i = 0; i < Center; i++ )
        {
            prelim1 = KerX[0] * pS8u[i];
            prelim2 = KerY[0] * pS8u[i];
            for( k = 1; k <= Center; k++ )
            {
                Temp = pS8u[BOUND( limitX, i + k )] + pS8u[BOUND( limitX, i - k )];
                prelim1 += KerX[k] * Temp;
                prelim2 += KerY[k] * Temp;
            }
            pDstI1[i] = prelim1;
            pDstI2[i] = prelim2;
        }

        for( i = Center; i < limitX - Center + 1; i++ )
        {
            prelim1 = KerX[0] * pS8u[i];
            prelim2 = KerY[0] * pS8u[i];
            for( k = 1; k <= Center; k++ )
            {
                Temp = pS8u[i + k] + pS8u[i - k];
                prelim1 += KerX[k] * Temp;
                prelim2 += KerY[k] * Temp;
            }
            pDstI1[i] = prelim1;
            pDstI2[i] = prelim2;
        }
        for( i = limitX + 1 - Center; i < limitX + 1; i++ )
        {
            prelim1 = KerX[0] * pS8u[i];
            prelim2 = KerY[0] * pS8u[i];
            for( k = 1; k <= Center; k++ )
            {
                Temp = pS8u[BOUND( limitX, i + k )] + pS8u[i - k];
                prelim1 += KerX[k] * Temp;
                prelim2 += KerY[k] * Temp;
            }
            pDstI1[i] = prelim1;
            pDstI2[i] = prelim2;
        }
        pConS->initialized--;
        pS8u += srcStep;
        curROI->height--;
    }

    /* main loop */
    pDst = pDest;
    for( t = 0; t < curROI->height; t++ )
    {
        if( Len == 3 )
        {
            prelim1 = pS8u[1] - pS8u[0];
            prelim2 = pS8u[1] + 3 * pS8u[0];
            pDst[0] =
                (lines1[0][0] + lines2[0][0] + prelim1 + prelim2 +
                 2 * (lines1[1][0] - lines2[1][0]));
            lines1[0][0] = prelim1;
            lines2[0][0] = prelim2;
            for( i = 1; i < limitX; i++ )
            {
                float t1 = pS8u[i + 1] + pS8u[i - 1];
                float t2 = 2 * pS8u[i];

                prelim1 = t1 - t2;
                prelim2 = t1 + t2;
                pDst[i] =
                    (lines1[0][i] + lines2[0][i] + prelim1 + prelim2 +
                     2 * (lines1[1][i] - lines2[1][i]));
                lines1[0][i] = prelim1;
                lines2[0][i] = prelim2;
            }
            prelim1 = pS8u[i - 1] - pS8u[i];
            prelim2 = pS8u[i - 1] + 3 * pS8u[i];
            pDst[i] =
                (lines1[0][i] + lines2[0][i] + prelim1 + prelim2 +
                 2 * (lines1[1][i] - lines2[1][i]));
            lines1[0][i] = prelim1;
            lines2[0][i] = prelim2;

        }
        else
        {
            for( i = 0; i < Center; i++ )
            {
                prelim1 = KerX[0] * pS8u[i];
                prelim2 = KerY[0] * pS8u[i];
                for( k = 1; k <= Center; k++ )
                {
                    Temp = pS8u[i + k] + pS8u[BOUND( limitX, i - k )];
                    prelim1 += KerX[k] * Temp;
                    prelim2 += KerY[k] * Temp;
                }
                ConvY1 = KerY[0] * lines1[Center][i];
                ConvY2 = KerX[0] * lines2[Center][i];
                for( k = 1; k < Center; k++ )
                {
                    ConvY1 += KerY[k] * (lines1[Center + k][i] + lines1[Center - k][i]);
                    ConvY2 += KerX[k] * (lines2[Center + k][i] + lines2[Center - k][i]);
                }
                pDst[i] = (ConvY1 + KerY[k] * (prelim1 + lines1[Center - k][i]) +
                           ConvY2 + KerX[k] * (prelim2 + lines2[Center - k][i]));
                lines1[0][i] = prelim1;
                lines2[0][i] = prelim2;
            }
            for( i = Center; i < limitX - Center + 1; i++ )
            {
                prelim1 = KerX[0] * pS8u[i];
                prelim2 = KerY[0] * pS8u[i];
                for( k = 1; k <= Center; k++ )
                {
                    Temp = pS8u[i + k] + pS8u[i - k];
                    prelim1 += KerX[k] * Temp;
                    prelim2 += KerY[k] * Temp;
                }
                ConvY1 = KerY[0] * lines1[Center][i];
                ConvY2 = KerX[0] * lines2[Center][i];
                for( k = 1; k < Center; k++ )
                {
                    ConvY1 += KerY[k] * (lines1[Center + k][i] + lines1[Center - k][i]);
                    ConvY2 += KerX[k] * (lines2[Center + k][i] + lines2[Center - k][i]);
                }
                pDst[i] = (ConvY1 + KerY[k] * (prelim1 + lines1[Center - k][i]) +
                           ConvY2 + KerX[k] * (prelim2 + lines2[Center - k][i]));
                lines1[0][i] = prelim1;
                lines2[0][i] = prelim2;
            }
            for( i = limitX + 1 - Center; i < limitX + 1; i++ )
            {
                prelim1 = KerX[0] * pS8u[i];
                prelim2 = KerY[0] * pS8u[i];
                for( k = 1; k <= Center; k++ )
                {
                    Temp = pS8u[BOUND( limitX, i + k )] + pS8u[i - k];
                    prelim1 += KerX[k] * Temp;
                    prelim2 += KerY[k] * Temp;
                }
                ConvY1 = KerY[0] * lines1[Center][i];
                ConvY2 = KerX[0] * lines2[Center][i];
                for( k = 1; k < Center; k++ )
                {
                    ConvY1 += KerY[k] * (lines1[Center + k][i] + lines1[Center - k][i]);
                    ConvY2 += KerX[k] * (lines2[Center + k][i] + lines2[Center - k][i]);
                }
                pDst[i] = (ConvY1 + KerY[k] * (prelim1 + lines1[Center - k][i]) +
                           ConvY2 + KerX[k] * (prelim2 + lines2[Center - k][i]));
                lines1[0][i] = prelim1;
                lines2[0][i] = prelim2;
            }
        }

        /* Rotating cyclic buffer */
        Tempp1 = lines1[0];
        Tempp2 = lines2[0];
        for( k = 0; k < Len - 2; k++ )
        {
            lines1[k] = lines1[k + 1];
            lines2[k] = lines2[k + 1];
        }
        lines1[Len - 2] = Tempp1;
        lines2[Len - 2] = Tempp2;
        obtain_rows++;
        pDst += destStep;
        pS8u += srcStep;
    }

    if( ownstage & CV_END )
    {
        memcpy( lines1[Len - 1], lines1[Len - 2], curROI->width * 4 );
        memcpy( lines2[Len - 1], lines2[Len - 2], curROI->width * 4 );

        for( t = 0; t < Center; t++ )
        {

            for( i = 0; i < curROI->width; i++ )
            {
                ConvY1 = KerY[0] * lines1[Center][i];
                ConvY2 = KerX[0] * lines2[Center][i];
                for( k = 1; k <= Center; k++ )
                {
                    ConvY1 += KerY[k] * (lines1[Center + k][i] + lines1[Center - k][i]);
                    ConvY2 += KerX[k] * (lines2[Center + k][i] + lines2[Center - k][i]);
                }
                pDst[i] = (ConvY1 + ConvY2);

            }
            memcpy( lines1[0], lines1[Len - 1], curROI->width * 4 );
            memcpy( lines2[0], lines2[Len - 1], curROI->width * 4 );
            Tempp1 = lines1[0];
            Tempp2 = lines2[0];
            for( k = 0; k < Len - 1; k++ )
            {
                lines1[k] = lines1[k + 1];
                lines2[k] = lines2[k + 1];
            }
            lines1[Len - 2] = Tempp1;
            lines2[Len - 2] = Tempp2;

            pDst += destStep;
            obtain_rows++;
        }
    }
    curROI->height = obtain_rows;
    return CV_NO_ERR;
}

/* End of File */
