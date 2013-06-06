#include "ipl.h"
#include <stdio.h>

/// dump 8U image data
void dump8u( const IplImage* img, const char* title ) {
   int x, y;
   uchar *p;
   if( !img || !img->imageData || !title || IPL_DEPTH_8U != img->depth ) return;

   p = (uchar*)img->imageData;
   printf( title );
   for( y=0; y<img->height; ++y ) {
      for( x=0; x<img->width; ++x ) printf("%4d", p[x] );
      printf("\n");
      p += img->widthStep;
   }
}

int main( void )
{
   const int W = 16, H = 5;
   IplImage *img = NULL;
   __try {
      /// print IPLib version number
      printf("\n%s %s\n", iplGetLibVersion()->Name, iplGetLibVersion()->Version );
      /// create image and check result
      img = iplCreateImageJaehne( IPL_DEPTH_8U, W, H );
      if( !img ) return -1;
      /// dump data, add 10, and dump data again
      dump8u( img, "\nsource :\n" );
      iplAddS( img, img, 10 );
      dump8u( img, "\nsource + 10, note some saturated values :\n" );
   }
   __finally {
      iplDeallocate( img, IPL_IMAGE_ALL );
   }
   return 0;
}
