/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1998-2000 Intel Corporation. All Rights Reserved.
//
//
*M*/


#ifdef __USERNAME__
#define GETNAME(name)   #name
#define GETNAME2(name)  GETNAME(name)

#define DLLNAME(px) GETNAME2(CUSTNAME)##GETNAME(px)
#endif /* __USERNAME__ */

/***********************************************************/
/* Only copy the function prototype of all the             */
/* functions you want from the release inlcude files       */
/***********************************************************/
#ifdef __USERLIST__
   IPLAPI(IplImage*, iplCreateImageJaehne,( int depth, int width, int height ))
   IPLAPI(const IPLLibVersion*, iplGetLibVersion,( void ))
   IPLAPI(void, iplAddS,(IplImage* src, IplImage* dst, int value ))
   IPLAPI(void, iplDeallocate,( IplImage* img, int flags ))
#endif /* __USERLIST__ */
