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
IPCVAPI_IMPL(CvStatus, icvScharr_8u16s_C1R, ( const unsigned char*          pSrc,
                                              int            srcStep,
                                              short*         pDest,
                                              int            destStep,
                                              CvSize*        curROI,
                                              CvConvState*  pConS,
                                              int            stage ))
{
    int i,j,k,t,Center,limitX,LX,ConvY,
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
	Len = 3;
	Center = 1;
	KerX = (int*)(pConS->KerX+4);
    KerY = (int*)(pConS->KerY+4);
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
                    prelim += (pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }

            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim += (pS8u[i + k] - pS8u[i - k]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim += (pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }
            
        }
        else
        {
            for(i = 0; i < Center; i++)
            {
                prelim = 10 * pS8u[i];
                for(k = 1; k <=Center; k++)
                {
                   prelim += 3*
                   (pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }

            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = 10 * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k]*
                    (pS8u[i + k] + pS8u[i - k]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = 10 * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                   prelim +=  3 *
                   (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }
            
        }
        pConS->initialized=Center-1;
        pS8u += srcStep;
        curROI->height--;
    }
     
    /* main loop */
    pDst = pDest;
    for(t = 0;t < curROI->height;t++)
    {
        pDstI = lines[0];
        if(pConS->kerType&1)
		{
            prelim = pS8u[1]-pS8u[0];
            pDst[0] = (short)(10*lines[1][0]+3*(lines[0][0] +prelim));
            pDstI[0]=(short)prelim;
            for(i = 1; i < LX; i+=4)
			{
                  
                prelim1 = pS8u[i+1]-pS8u[i-1];
                prelim2 = pS8u[i+2]-pS8u[i];
                prelim3 = pS8u[i+3]-pS8u[i+1];
                prelim4 = pS8u[i+4]-pS8u[i+2];

                pDst[i] = (short)(10*lines[1][i]+3*(lines[0][i] +prelim1));
                pDst[i+1] = (short)(10*lines[1][i+1]+3*(lines[0][i+1] +prelim2));
                pDst[i+2] = (short)(10*lines[1][i+2]+3*(lines[0][i+2] +prelim3));
                pDst[i+3] = (short)(10*lines[1][i+3]+3*(lines[0][i+3] +prelim4));

                pDstI[i]=(short)prelim1;
                pDstI[i+1]=(short)prelim2;
                pDstI[i+2]=(short)prelim3;
                pDstI[i+3]=(short)prelim4;
                
            }
            for(;i <= limitX; i++)
            {
                prelim = pS8u[BOUND(limitX,i+1)]-pS8u[i-1];
                pDst[i] = (short)(10*lines[1][i]+3*(lines[0][i] +prelim));
                pDstI[i]=(short)prelim;
            }
		}

        else
		{
			if(pConS->kerType&2)
			{
				prelim = 13*pS8u[0]+3*pS8u[1];
				pDst[0] = (short)(lines[0][0] - prelim);
				pDstI[0]=(short)prelim;
				for(i = 1; i < LX; i+=4)
				{
					prelim1 = 10*pS8u[i]+3*(pS8u[i+1]+pS8u[i-1]);
					prelim2 = 10*pS8u[i+1]+3*(pS8u[i+2]+pS8u[i]);
					prelim3 = 10*pS8u[i+2]+3*(pS8u[i+3]+pS8u[i+1]);
					prelim4 = 10*pS8u[i+3]+3*(pS8u[i+4]+pS8u[i+2]);
					pDst[i] = (short)(lines[0][i] - prelim1);
					pDst[i+1] = (short)(lines[0][i+1]-prelim2);
					pDst[i+2] = (short)(lines[0][i+2]-prelim3);
					pDst[i+3] = (short)(lines[0][i+3]-prelim4);
					pDstI[i]=(short)prelim1;
					pDstI[i+1]=(short)prelim2;
					pDstI[i+2]=(short)prelim3;
					pDstI[i+3]=(short)prelim4;
				}
				for(;i <= limitX; i++)
				{
					prelim = 10*pS8u[i]+3*(pS8u[BOUND(limitX,i+1)]+pS8u[i-1]);
					pDst[i] = (short)(lines[0][i] - prelim);
					pDstI[i]= (short)prelim;
				}
			}
			else
			{
				prelim = 13*pS8u[0]+3*pS8u[1];
				pDst[0] = (short)(prelim - lines[0][0]);
				pDstI[0]=(short)prelim;
				for(i = 1; i < LX; i+=4)
				{
					prelim1 = 10*pS8u[i]+3*(pS8u[i+1]+pS8u[i-1]);
					prelim2 = 10*pS8u[i+1]+3*(pS8u[i+2]+pS8u[i]);
					prelim3 = 10*pS8u[i+2]+3*(pS8u[i+3]+pS8u[i+1]);
					prelim4 = 10*pS8u[i+3]+3*(pS8u[i+4]+pS8u[i+2]);
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
					prelim = 10*pS8u[i]+3*(pS8u[BOUND(limitX,i+1)]+pS8u[i-1]);
					pDst[i] = (short)(prelim - lines[0][i]);
					pDstI[i]= (short)prelim;
				}
			}
            
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
            if(!(pConS->kerType&1))
            {
                for(i = 0; i < curROI->width; i++)
                {
            
                    ConvY = 0;
                    for(j = 1; j <= Center; j++)
                    {
                        ConvY += KerY[j]*(lines[Center+j][i]-lines[Center-j][i]);
                    }
                    pDst[i] = (short)SAT(ConvY);
                }
            }
            else
            {
                for(i = 0; i < curROI->width; i++)
                {
                    ConvY = 10*lines[Center][i];
                    for(j = 1; j <= Center; j++)
                    {
                        ConvY += 3 *(lines[Center-j][i]+lines[Center+j][i]);
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

IPCVAPI_IMPL(CvStatus, icvScharr_8s16s_C1R, ( const char*          pSrc,
                                           int            srcStep,
                                           short*         pDest,
                                           int            destStep,
                                           CvSize*        curROI,
                                           CvConvState*  pConS,
                                           int            stage ))
{
    int i,j,k,t,Center,limitX,LX,ConvY,
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
	Len = 3;
	Center = 1;
	KerX = (int*)(pConS->KerX+4);
    KerY = (int*)(pConS->KerY+4);
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
                    prelim += (pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }

            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim += (pS8u[i + k] - pS8u[i - k]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim += (pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }
            
        }
        else
        {
            for(i = 0; i < Center; i++)
            {
                prelim = 10 * pS8u[i];
                for(k = 1; k <=Center; k++)
                {
                   prelim += 3*
                   (pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }

            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = 10 * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k]*
                    (pS8u[i + k] + pS8u[i - k]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = 10 * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                   prelim +=  3 *
                   (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (short)prelim;
            }
            
        }
        pConS->initialized=Center-1;
        pS8u += srcStep;
        curROI->height--;
    }
     
    /* main loop */
    pDst = pDest;
    for(t = 0;t < curROI->height;t++)
    {
        pDstI = lines[0];
        if(pConS->kerType&1)
		{
            prelim = pS8u[1]-pS8u[0];
            pDst[0] = (short)(10*lines[1][0]+3*(lines[0][0] +prelim));
            pDstI[0]=(short)prelim;
            for(i = 1; i < LX; i+=4)
			{
                  
                prelim1 = pS8u[i+1]-pS8u[i-1];
                prelim2 = pS8u[i+2]-pS8u[i];
                prelim3 = pS8u[i+3]-pS8u[i+1];
                prelim4 = pS8u[i+4]-pS8u[i+2];

                pDst[i] = (short)(10*lines[1][i]+3*(lines[0][i] +prelim1));
                pDst[i+1] = (short)(10*lines[1][i+1]+3*(lines[0][i+1] +prelim2));
                pDst[i+2] = (short)(10*lines[1][i+2]+3*(lines[0][i+2] +prelim3));
                pDst[i+3] = (short)(10*lines[1][i+3]+3*(lines[0][i+3] +prelim4));

                pDstI[i]=(short)prelim1;
                pDstI[i+1]=(short)prelim2;
                pDstI[i+2]=(short)prelim3;
                pDstI[i+3]=(short)prelim4;
                
            }
            for(;i <= limitX; i++)
            {
                prelim = pS8u[BOUND(limitX,i+1)]-pS8u[i-1];
                pDst[i] = (short)(10*lines[1][i]+3*(lines[0][i] +prelim));
                pDstI[i]=(short)prelim;
            }
		}

        else
		{
			if(pConS->kerType&2)
			{
				prelim = 13*pS8u[0]+3*pS8u[1];
				pDst[0] = (short)(lines[0][0] - prelim);
				pDstI[0]=(short)prelim;
				for(i = 1; i < LX; i+=4)
				{
					prelim1 = 10*pS8u[i]+3*(pS8u[i+1]+pS8u[i-1]);
					prelim2 = 10*pS8u[i+1]+3*(pS8u[i+2]+pS8u[i]);
					prelim3 = 10*pS8u[i+2]+3*(pS8u[i+3]+pS8u[i+1]);
					prelim4 = 10*pS8u[i+3]+3*(pS8u[i+4]+pS8u[i+2]);
					pDst[i] = (short)(lines[0][i] - prelim1);
					pDst[i+1] = (short)(lines[0][i+1]-prelim2);
					pDst[i+2] = (short)(lines[0][i+2]-prelim3);
					pDst[i+3] = (short)(lines[0][i+3]-prelim4);
					pDstI[i]=(short)prelim1;
					pDstI[i+1]=(short)prelim2;
					pDstI[i+2]=(short)prelim3;
					pDstI[i+3]=(short)prelim4;
				}
				for(;i <= limitX; i++)
				{
					prelim = 10*pS8u[i]+3*(pS8u[BOUND(limitX,i+1)]+pS8u[i-1]);
					pDst[i] = (short)(lines[0][i] - prelim);
					pDstI[i]= (short)prelim;
				}
			}
			else
			{
				prelim = 13*pS8u[0]+3*pS8u[1];
				pDst[0] = (short)(prelim - lines[0][0]);
				pDstI[0]=(short)prelim;
				for(i = 1; i < LX; i+=4)
				{
					prelim1 = 10*pS8u[i]+3*(pS8u[i+1]+pS8u[i-1]);
					prelim2 = 10*pS8u[i+1]+3*(pS8u[i+2]+pS8u[i]);
					prelim3 = 10*pS8u[i+2]+3*(pS8u[i+3]+pS8u[i+1]);
					prelim4 = 10*pS8u[i+3]+3*(pS8u[i+4]+pS8u[i+2]);
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
					prelim = 10*pS8u[i]+3*(pS8u[BOUND(limitX,i+1)]+pS8u[i-1]);
					pDst[i] = (short)(prelim - lines[0][i]);
					pDstI[i]= (short)prelim;
				}
			}
            
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
            if(!(pConS->kerType&1))
            {
                for(i = 0; i < curROI->width; i++)
                {
            
                    ConvY = 0;
                    for(j = 1; j <= Center; j++)
                    {
                        ConvY += KerY[j]*(lines[Center+j][i]-lines[Center-j][i]);
                    }
                    pDst[i] = (short)SAT(ConvY);
                }
            }
            else
            {
                for(i = 0; i < curROI->width; i++)
                {
                    ConvY = 10*lines[Center][i];
                    for(j = 1; j <= Center; j++)
                    {
                        ConvY += 3 *(lines[Center-j][i]+lines[Center+j][i]);
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


IPCVAPI_IMPL(CvStatus, icvScharr_32f_C1R, ( const float*          pSrc,
                                        int            srcStep,
                                        float*         pDest,
                                        int            destStep,
                                        CvSize*        curROI,
                                        CvConvState*  pConS,
                                        int            stage ))
{
    int i,j,k,t,Center,limitX,LX;
	float ConvY, prelim, prelim1, prelim2,prelim3, prelim4;
    float** lines;
    int Len;
	float* KerX;
    float* KerY;
    float* pDst = pDest;
    float* pDstI;
    int obtain_rows=0;
    int ownstage = (stage)?stage:CV_START|CV_END;
    float* Temp;
    float* pS8u;

   	lines= (float**)pConS->lines;
	Len = 3;
	Center = 1;
	KerX = (float*)(pConS->KerX+4);
    KerY = (float*)(pConS->KerY+4);
	pDst = pDest;
	limitX = curROI->width-1;
	LX = Center + ((curROI->width-2*Center)/8)*8;
	pS8u=(float*)pSrc;
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
                    prelim += (pS8u[BOUND(limitX,i + k)]-pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (float)prelim;
            }

            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim += (pS8u[i + k] - pS8u[i - k]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (float)prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = 0;
                for(k = 1; k <= Center; k++)
                {
                    prelim += (pS8u[BOUND(limitX,i + k)] - pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (float)prelim;
            }
            
        }
        else
        {
            for(i = 0; i < Center; i++)
            {
                prelim = 10 * pS8u[i];
                for(k = 1; k <=Center; k++)
                {
                   prelim += 3*
                   (pS8u[BOUND(limitX,i + k)]+pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (float)prelim;
            }

            for(i = Center; i < limitX - Center + 1; i++)
            {
                prelim = 10 * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                    prelim += KerX[k]*
                    (pS8u[i + k] + pS8u[i - k]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (float)prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim = 10 * pS8u[i];
                for(k = 1; k <= Center; k++)
                {
                   prelim +=  3 *
                   (pS8u[BOUND(limitX,i + k)] + pS8u[BOUND(limitX,i - k)]);
                }
                for(k = 0; k<=Center; k++)lines[k][i] = (float)prelim;
            }
            
        }
        pConS->initialized=Center-1;
        pS8u += srcStep/4;
        curROI->height--;
    }
     
    /* main loop */
    pDst = pDest;
    for(t = 0;t < curROI->height;t++)
    {
        pDstI = lines[0];
        if(pConS->kerType&1)
		{
            prelim = pS8u[1]-pS8u[0];
            pDst[0] = (float)(10*lines[1][0]+3*(lines[0][0] +prelim));
            pDstI[0]=(float)prelim;
            for(i = 1; i < LX; i+=4)
			{
                  
                prelim1 = pS8u[i+1]-pS8u[i-1];
                prelim2 = pS8u[i+2]-pS8u[i];
                prelim3 = pS8u[i+3]-pS8u[i+1];
                prelim4 = pS8u[i+4]-pS8u[i+2];

                pDst[i] = (float)(10*lines[1][i]+3*(lines[0][i] +prelim1));
                pDst[i+1] = (float)(10*lines[1][i+1]+3*(lines[0][i+1] +prelim2));
                pDst[i+2] = (float)(10*lines[1][i+2]+3*(lines[0][i+2] +prelim3));
                pDst[i+3] = (float)(10*lines[1][i+3]+3*(lines[0][i+3] +prelim4));

                pDstI[i]=(float)prelim1;
                pDstI[i+1]=(float)prelim2;
                pDstI[i+2]=(float)prelim3;
                pDstI[i+3]=(float)prelim4;
                
            }
            for(;i <= limitX; i++)
            {
                prelim = pS8u[BOUND(limitX,i+1)]-pS8u[i-1];
                pDst[i] = (float)(10*lines[1][i]+3*(lines[0][i] +prelim));
                pDstI[i]=(float)prelim;
            }
		}

        else
		{
			if(pConS->kerType&2)
			{
				prelim = 13*pS8u[0]+3*pS8u[1];
				pDst[0] = (float)(lines[0][0] - prelim);
				pDstI[0]=(float)prelim;
				for(i = 1; i < LX; i+=4)
				{
					prelim1 = 10*pS8u[i]+3*(pS8u[i+1]+pS8u[i-1]);
					prelim2 = 10*pS8u[i+1]+3*(pS8u[i+2]+pS8u[i]);
					prelim3 = 10*pS8u[i+2]+3*(pS8u[i+3]+pS8u[i+1]);
					prelim4 = 10*pS8u[i+3]+3*(pS8u[i+4]+pS8u[i+2]);
					pDst[i] = (float)(lines[0][i] - prelim1);
					pDst[i+1] = (float)(lines[0][i+1]-prelim2);
					pDst[i+2] = (float)(lines[0][i+2]-prelim3);
					pDst[i+3] = (float)(lines[0][i+3]-prelim4);
					pDstI[i]=(float)prelim1;
					pDstI[i+1]=(float)prelim2;
					pDstI[i+2]=(float)prelim3;
					pDstI[i+3]=(float)prelim4;
				}
				for(;i <= limitX; i++)
				{
					prelim = 10*pS8u[i]+3*(pS8u[BOUND(limitX,i+1)]+pS8u[i-1]);
					pDst[i] = (float)(lines[0][i] - prelim);
					pDstI[i]= (float)prelim;
				}
			}
			else
			{
				prelim = 13*pS8u[0]+3*pS8u[1];
				pDst[0] = (float)(prelim - lines[0][0]);
				pDstI[0]=(float)prelim;
				for(i = 1; i < LX; i+=4)
				{
					prelim1 = 10*pS8u[i]+3*(pS8u[i+1]+pS8u[i-1]);
					prelim2 = 10*pS8u[i+1]+3*(pS8u[i+2]+pS8u[i]);
					prelim3 = 10*pS8u[i+2]+3*(pS8u[i+3]+pS8u[i+1]);
					prelim4 = 10*pS8u[i+3]+3*(pS8u[i+4]+pS8u[i+2]);
					pDst[i] = (float)(prelim1 -lines[0][i]);
					pDst[i+1] = (float)(prelim2-lines[0][i+1]);
					pDst[i+2] = (float)(prelim3-lines[0][i+2]);
					pDst[i+3] = (float)(prelim4-lines[0][i+3]);
					pDstI[i]=(float)prelim1;
					pDstI[i+1]=(float)prelim2;
					pDstI[i+2]=(float)prelim3;
					pDstI[i+3]=(float)prelim4;
				}
				for(;i <= limitX; i++)
				{
					prelim = 10*pS8u[i]+3*(pS8u[BOUND(limitX,i+1)]+pS8u[i-1]);
					pDst[i] = (float)(prelim - lines[0][i]);
					pDstI[i]= (float)prelim;
				}
			}
            
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
            if(!(pConS->kerType&1))
            {
                for(i = 0; i < curROI->width; i++)
                {
            
                    ConvY = 0;
                    for(j = 1; j <= Center; j++)
                    {
                        ConvY += KerY[j]*(lines[Center+j][i]-lines[Center-j][i]);
                    }
                    pDst[i] = (float)SAT(ConvY);
                }
            }
            else
            {
                for(i = 0; i < curROI->width; i++)
                {
                    ConvY = 10*lines[Center][i];
                    for(j = 1; j <= Center; j++)
                    {
                        ConvY += 3 *(lines[Center-j][i]+lines[Center+j][i]);
                    }
                    pDst[i] = (float)SAT(ConvY);
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


