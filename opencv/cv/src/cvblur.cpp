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


#define BOUND(rbound,x) ((((x)<0)-1)&MIN((rbound),(x)))

IPCVAPI_IMPL( CvStatus, icvBlur_8u16s_C1R, (const unsigned char *pSrc,
                                            int srcStep,
                                            short *pDest,
                                            int destStep,
                                            CvSize * curROI, _CvConvState * pConS, int stage) )
{
    /* Some Variables */
    int i,k,t,Len,Center,limitX,obtain_rows=0;
    int** lines;
    int* Current;
    short* pDst;
    int* pDstI;
    int ownstage = (stage)?stage:CV_START|CV_END;
    int* Temp;
    unsigned char* pS8u;
    int prelim;
		
	lines = (int**)pConS->lines;
    Len = pConS->kerType>>3;
	Center = Len/2;
    Current = (int*)lines[Len];
    pDst = pDest;
    limitX = curROI->width-1;
    
    pS8u=(unsigned char*)pSrc;
    t = 0;
    if(ownstage&CV_START)pConS->initialized =Len-1;
     
    if(pConS->initialized)
    {
        if(ownstage&CV_START)
        {

            prelim = (Center+1)*pS8u[0];
            for(k = 1; k <=Center; k++)
            {
                 prelim += pS8u[k];
            }
            Current[0] = (Center+1)*prelim;
            lines[0][0] = 0;
            for(k = 1; k<=Center+1; k++)lines[k][0] = prelim;
            for(i = 1; i <= Center; i++)
            {
                prelim += pS8u[i + Center]-pS8u[0];
                Current[i] = (Center+1)*prelim;
                lines[0][i] = 0;
                for(k = 1; k<=Center+1; k++)lines[k][i] = prelim;
            }
            
            for(i = Center+1; i < limitX - Center + 1; i++)
            {                                        
                prelim += (pS8u[i + Center] - pS8u[i - Center-1]);
                Current[i] = (Center+1)*prelim;
                lines[0][i] = 0;
                for(k = 1; k<=Center+1; k++)lines[k][i] = prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim +=  (pS8u[limitX] - pS8u[i - Center-1]);
                Current[i] = (Center+1)*prelim;
                lines[0][i] = 0;
                for(k = 1; k<=Center+1; k++)lines[k][i] = prelim;
            }
            
        
            pConS->initialized=Center-1;
            pS8u += srcStep;
            curROI->height--;
        }

        while((curROI->height)&&(pConS->initialized))
        {
            pDstI = lines[Len-pConS->initialized];
            prelim = (Center+1)*pS8u[0];
            for(k = 1; k <=Center; k++)
            {
                 prelim += pS8u[k];
            }
            Current[0]+=prelim;
            pDstI[0] = prelim;
            for(i = 1; i <= Center; i++)
            {
                prelim += pS8u[i + Center]-pS8u[0];
                Current[i]+=prelim;
                pDstI[i] = prelim;
            }
            
            for(i = Center+1; i < limitX - Center + 1; i++)
            {
                prelim += (pS8u[i + Center] - pS8u[i - Center-1]);
                Current[i]+=prelim;
                pDstI[i] = prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                   prelim +=  (pS8u[limitX] - pS8u[i - Center-1]);
                   Current[i]+=prelim;
                   pDstI[i] = prelim; 
            }
                pConS->initialized--;
                curROI->height--;
                pS8u += srcStep;
        }
    }
    /* main loop */
    pDst = pDest;
    for(t = 0;t < curROI->height; t++)
    {
        prelim = (Center+1)*pS8u[0];
        for(k = 1; k <=Center; k++)
        {
            prelim += pS8u[k];
        }
        pDst[0] = (short)(Current[0] = Current[0] + prelim - lines[0][0]);
        lines[0][0]=prelim;
        
        for(i = 1; i <= Center; i++)
        {
            prelim += pS8u[i + Center]-pS8u[0];
            pDst[i] = (short)(Current[i] = Current[i] + prelim - lines[0][i]);
            lines[0][i]=prelim;
        }
        for(i = Center+1; i < limitX - Center + 1; i++)
        {
            prelim += (pS8u[i + Center]-pS8u[i - Center-1]);
            pDst[i] = (short)(Current[i] = Current[i]+prelim - lines[0][i]);
            lines[0][i]=prelim;
        }
        for(i = limitX + 1 - Center; i < limitX + 1; i++)
        {
            prelim += pS8u[limitX]-pS8u[i-Center-1];
            pDst[i] = (short)(Current[i] = Current[i]+prelim - lines[0][i]);
            lines[0][i]=prelim;
        }

        /* Rotating cyclic buffer */ 
        Temp = lines[0];
        for(k = 0; k < Len-1; k++)
        {
           lines[k]=lines[k + 1];
        }
        lines[Len-1] = Temp;
        obtain_rows++;
        pDst+=destStep/2;
        pS8u+=srcStep;
    }

    if(ownstage&CV_END)
    {
		int Fin = Center - pConS->initialized;
		if(pConS->initialized)
		{
			for(t = 0; t < pConS->initialized; t++)
			{
				for(i = 0; i < curROI->width; i++)
				{
					lines[Len-1-t][i]=lines[Len-1-pConS->initialized][i];
					Current[i] += lines[Len-1-pConS->initialized][i];
				}

			}
		}

        for(t = 0; t < Fin; t++)
        {
            for(i = 0; i < curROI->width; i++)
            {
                pDst[i] =(short)(Current[i] = Current[i]+ lines[Len-1][i]- lines[0][i]);
                lines[0][i]=lines[Len-1][i];
            }
             /* Rotating cyclic buffer  */
            Temp = lines[0];
            for(k = 0; k < Len-1; k++)
            {
                lines[k]=lines[k + 1];
            }
            lines[Len-1] = Temp;
            obtain_rows++;
            pDst+=destStep/2;
       }
    }
    curROI->height=obtain_rows;    
    return CV_NO_ERR;
}


IPCVAPI_IMPL( CvStatus, icvBlur_8s16s_C1R, (const char *pSrc,
                                            int srcStep,
                                            short *pDest,
                                            int destStep,
                                            CvSize * curROI, _CvConvState * pConS, int stage) )
{
     int i,k,t,Len,Center,limitX,obtain_rows=0;
    int** lines;
    int* Current;
    short* pDst;
    int* pDstI;
    int ownstage = (stage)?stage:CV_START|CV_END;
    int* Temp;
    char* pS8u;
    int prelim;
		
	
	lines = (int**)pConS->lines;
    Len = pConS->kerType>>3;
	Center = Len/2;
    Current = (int*)lines[Len];
    pDst = pDest;
    limitX = curROI->width-1;
    
    pS8u=(char*)pSrc;
    t = 0;
    if(ownstage&CV_START)pConS->initialized =Len-1;
     
    if(pConS->initialized)
    {
        if(ownstage&CV_START)
        {

            prelim = (Center+1)*pS8u[0];
            for(k = 1; k <=Center; k++)
            {
                 prelim += pS8u[k];
            }
            Current[0] = (Center+1)*prelim;
            lines[0][0] = 0;
            for(k = 1; k<=Center+1; k++)lines[k][0] = prelim;
            for(i = 1; i <= Center; i++)
            {
                prelim += pS8u[i + Center]-pS8u[0];
                Current[i] = (Center+1)*prelim;
                lines[0][i] = 0;
                for(k = 1; k<=Center+1; k++)lines[k][i] = prelim;
            }
            
            for(i = Center+1; i < limitX - Center + 1; i++)
            {                                        
                prelim += (pS8u[i + Center] - pS8u[i - Center-1]);
                Current[i] = (Center+1)*prelim;
                lines[0][i] = 0;
                for(k = 1; k<=Center+1; k++)lines[k][i] = prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim +=  (pS8u[limitX] - pS8u[i - Center-1]);
                Current[i] = (Center+1)*prelim;
                lines[0][i] = 0;
                for(k = 1; k<=Center+1; k++)lines[k][i] = prelim;
            }
            
        
            pConS->initialized=Center-1;
            pS8u += srcStep;
            curROI->height--;
        }

        while((curROI->height)&&(pConS->initialized))
        {
            pDstI = lines[Len-pConS->initialized];
            prelim = (Center+1)*pS8u[0];
            for(k = 1; k <=Center; k++)
            {
                 prelim += pS8u[k];
            }
            Current[0]+=prelim;
            pDstI[0] = prelim;
            for(i = 1; i <= Center; i++)
            {
                prelim += pS8u[i + Center]-pS8u[0];
                Current[i]+=prelim;
                pDstI[i] = prelim;
            }
            
            for(i = Center+1; i < limitX - Center + 1; i++)
            {
                prelim += (pS8u[i + Center] - pS8u[i - Center-1]);
                Current[i]+=prelim;
                pDstI[i] = prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                   prelim +=  (pS8u[limitX] - pS8u[i - Center-1]);
                   Current[i]+=prelim;
                   pDstI[i] = prelim; 
            }
                pConS->initialized--;
                curROI->height--;
                pS8u += srcStep;
        }
    }
    /* main loop */
    pDst = pDest;
    for(t = 0;t < curROI->height; t++)
    {
        prelim = (Center+1)*pS8u[0];
        for(k = 1; k <=Center; k++)
        {
            prelim += pS8u[k];
        }
        pDst[0] = (short)(Current[0] = Current[0] + prelim - lines[0][0]);
        lines[0][0]=prelim;
        
        for(i = 1; i <= Center; i++)
        {
            prelim += pS8u[i + Center]-pS8u[0];
            pDst[i] = (short)(Current[i] = Current[i] + prelim - lines[0][i]);
            lines[0][i]=prelim;
        }
        for(i = Center+1; i < limitX - Center + 1; i++)
        {
            prelim += (pS8u[i + Center]-pS8u[i - Center-1]);
            pDst[i] = (short)(Current[i] = Current[i]+prelim - lines[0][i]);
            lines[0][i]=prelim;
        }
        for(i = limitX + 1 - Center; i < limitX + 1; i++)
        {
            prelim += pS8u[limitX]-pS8u[i-Center-1];
            pDst[i] = (short)(Current[i] = Current[i]+prelim - lines[0][i]);
            lines[0][i]=prelim;
        }

        /* Rotating cyclic buffer */ 
        Temp = lines[0];
        for(k = 0; k < Len-1; k++)
        {
           lines[k]=lines[k + 1];
        }
        lines[Len-1] = Temp;
        obtain_rows++;
        pDst+=destStep/2;
        pS8u+=srcStep;
    }

    if(ownstage&CV_END)
    {
		int Fin = Center - pConS->initialized;
		if(pConS->initialized)
		{
			for(t = 0; t < pConS->initialized; t++)
			{
				for(i = 0; i < curROI->width; i++)
				{
					lines[Len-1-t][i]=lines[Len-1-pConS->initialized][i];
					Current[i] += lines[Len-1-pConS->initialized][i];
				}

			}
		}

        for(t = 0; t < Fin; t++)
        {
            for(i = 0; i < curROI->width; i++)
            {
                pDst[i] =(short)(Current[i] = Current[i]+ lines[Len-1][i]- lines[0][i]);
                lines[0][i]=lines[Len-1][i];
            }
             /* Rotating cyclic buffer  */
            Temp = lines[0];
            for(k = 0; k < Len-1; k++)
            {
                lines[k]=lines[k + 1];
            }
            lines[Len-1] = Temp;
            obtain_rows++;
            pDst+=destStep/2;
       }
    }
    curROI->height=obtain_rows;    
    return CV_NO_ERR;
}


IPCVAPI_IMPL( CvStatus, icvBlur_32f_C1R, (const float *pSrc,
                                          int srcStep,
                                          float *pDest,
                                          int destStep,
                                          CvSize * curROI, _CvConvState * pConS, int stage) )
{
    /* Some Variables */
    int i,k,t,Len,Center,limitX;
    float** lines;
    float* Current;
    float* pDst;
    float* pDstI;
    int obtain_rows=0;
    int ownstage = (stage)?stage:CV_START|CV_END;
    float* Temp;
    float* pS8u;
    float prelim;

	
	lines = (float**)pConS->lines;
    Len = pConS->kerType>>3;
	Center = Len/2;
    Current = lines[Len];
    pDst = pDest;
    limitX = curROI->width-1;
    pS8u=(float*)pSrc;
    t = 0;
    if(ownstage&CV_START)pConS->initialized =Len-1;

    if(pConS->initialized)
    {
        if(ownstage&CV_START)
        {

            prelim = (Center+1)*pS8u[0];
            for(k = 1; k <=Center; k++)
            {
                 prelim += pS8u[k];
            }
            Current[0] = (Center+1)*prelim;
            lines[0][0] = 0;
            for(k = 1; k<=Center+1; k++)((float*)lines[k])[0] = prelim;
            for(i = 1; i <= Center; i++)
            {
                prelim += pS8u[i + Center]-pS8u[0];
                Current[i] = (Center+1)*prelim;
                lines[0][i] = 0;
                for(k = 1; k<=Center+1; k++)lines[k][i] = prelim;
            }
            
            for(i = Center+1; i < limitX - Center + 1; i++)
            {                                        
                prelim += (pS8u[i + Center] - pS8u[i - Center-1]);
                Current[i] = (Center+1)*prelim;
                lines[0][i] = 0;
                for(k = 1; k<=Center+1; k++)lines[k][i] = prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                prelim +=  (pS8u[limitX] - pS8u[i - Center-1]);
                Current[i] = (Center+1)*prelim;
                lines[0][i] = 0;
                for(k = 1; k<=Center+1; k++)((float*)lines[k])[i] = prelim;
            }
            
        
            pConS->initialized=Center-1;
            pS8u += srcStep/4;
            curROI->height--;
        }

        while((curROI->height)&&(pConS->initialized))
        {
            pDstI = lines[Len-pConS->initialized];
            prelim = (Center+1)*pS8u[0];
            for(k = 1; k <=Center; k++)
            {
                 prelim += pS8u[k];
            }
            Current[0]+=prelim;
            pDstI[0] = prelim;
            for(i = 1; i <= Center; i++)
            {
                prelim += pS8u[i + Center]-pS8u[0];
                Current[i]+=prelim;
                pDstI[i] = prelim;
            }
            
            for(i = Center+1; i < limitX - Center + 1; i++)
            {
                prelim += (pS8u[i + Center] - pS8u[i - Center-1]);
                Current[i]+=prelim;
                pDstI[i] = prelim;
            }
            for(i = limitX + 1 - Center; i < limitX + 1; i++)
            {
                   prelim +=  (pS8u[limitX] - pS8u[i - Center-1]);
                   Current[i]+=prelim;
                   pDstI[i] = prelim; 
            }
                pConS->initialized--;
                curROI->height--;
                pS8u += srcStep/4;
        }
    }
    /* main loop */
    pDst = pDest;
    for(t = 0;t < curROI->height; t++)
    {
        prelim = (Center+1)*pS8u[0];
        for(k = 1; k <=Center; k++)
        {
            prelim += pS8u[k];
        }
        pDst[0] = Current[0] = Current[0] + prelim - ((float*)lines[0])[0];
        lines[0][0]=prelim;
        
        for(i = 1; i <= Center; i++)
        {
            prelim += pS8u[i + Center]-pS8u[0];
            pDst[i] = Current[i] = Current[i] + prelim - lines[0][i];
            lines[0][i]=prelim;
        }
        for(i = Center+1; i < limitX - Center + 1; i++)
        {
            prelim += (pS8u[i + Center]-pS8u[i - Center-1]);
            pDst[i] = Current[i] = Current[i]+prelim - lines[0][i];
            lines[0][i]=prelim;
        }
        for(i = limitX + 1 - Center; i < limitX + 1; i++)
        {
            prelim += pS8u[limitX]-pS8u[i-Center-1];
            pDst[i] = Current[i] = Current[i]+prelim - lines[0][i];
            lines[0][i]=prelim;
        }

        /* Rotating cyclic buffer */ 
        Temp = lines[0];
        for(k = 0; k < Len-1; k++)
        {
           lines[k]=lines[k + 1];
        }
        lines[Len-1] = Temp;
        obtain_rows++;
        pDst+=destStep/4;
        pS8u+=srcStep/4;
    }

    if(ownstage&CV_END)
    {
		int Fin = Center - pConS->initialized;
		if(pConS->initialized)
		{
			for(t = 0; t < pConS->initialized; t++)
			{
				for(i = 0; i < curROI->width; i++)
				{
					lines[Len-1-t][i]=lines[Len-1-pConS->initialized][i];
					Current[i] += lines[Len-1-pConS->initialized][i];
				}

			}
		}
        for(t = 0; t < Fin; t++)
        {
            for(i = 0; i < curROI->width; i++)
            {
                pDst[i] =Current[i] = Current[i]+ lines[Len-1][i]- lines[0][i];
                lines[0][i]=lines[Len-1][i];
            }
             /* Rotating cyclic buffer */ 
            Temp = lines[0];
            for(k = 0; k < Len-1; k++)
            {
                lines[k]=lines[k + 1];
            }
            lines[Len-1] = Temp;
            obtain_rows++;
            pDst+=destStep/4;
       }
    }
    curROI->height=obtain_rows;    
    return CV_NO_ERR;
}
