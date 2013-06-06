/*=============================================================================
        File: matrix.cpp
     Purpose:       
    Revision: $Id: matrix_complex.cpp,v 1.3 2002/05/24 17:08:34 philosophil Exp $
  Created by: Philippe Lavoie          (3 Oct, 1996)
 Modified by: 

 Copyright notice:
          Copyright (C) 1996-1998 Philippe Lavoie
 
	  This library is free software; you can redistribute it and/or
	  modify it under the terms of the GNU Library General Public
	  License as published by the Free Software Foundation; either
	  version 2 of the License, or (at your option) any later version.
 
	  This library is distributed in the hope that it will be useful,
	  but WITHOUT ANY WARRANTY; without even the implied warranty of
	  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	  Library General Public License for more details.
 
	  You should have received a copy of the GNU Library General Public
	  License along with this library; if not, write to the Free
	  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
=============================================================================*/

#include "matrix.cpp"

namespace PLib {

  template<> double Matrix<NComplex>::norm(void){
    int i,j ;
    double sumR, sumI, maxsum;
    int init=0 ;
    NComplex *ptr ;
    ptr = m-1 ;
    maxsum = -1 ; // shuts up the warning messages
    for(i=0;i<rows();++i){
      sumR = 0.0 ;
      sumI = 0.0 ;
      for ( j = 0; j < cols(); ++j) {
	sumR += real(*ptr)*real(*ptr) ;
	sumI += imag(*ptr)*imag(*ptr) ;
      }
      if(init)
	maxsum = (maxsum>(sumR+sumI)) ? maxsum : (sumR+sumI);
      else{
	maxsum = (sumR+sumI) ;
	init = 1;
	}
      ++ptr ;
    }
    return sqrt(maxsum);
  }
  
  template <>
    Matrix<NComplex>  operator*(const double d,
			       const Matrix<NComplex> &a)
    {
      int i, size=a.rows()*a.cols() ;
      Matrix<NComplex> b(a.rows(),a.cols());
      
      NComplex *bptr,*aptr ;
      bptr = b.m - 1 ;
      aptr = a.m - 1 ;
      for (i = size; i > 0 ; --i)
	*(++bptr) = (NComplex)(d * (*(++aptr))) ;
      return b;
      
    }
  
  template <>
    Matrix<NComplex>  operator*(const NComplex &d,
			       const Matrix<NComplex> &a)
    {
      int i, size=a.rows()*a.cols() ;
      Matrix<NComplex> b(a.rows(),a.cols());
      
      NComplex *bptr,*aptr ;
      bptr = b.m - 1 ;
      aptr = a.m - 1 ;
      for (i = size; i > 0 ; --i)
	*(++bptr) = d * *(++aptr) ;
      return b;
    }
  
  
  template <>
    Matrix<NComplex> Matrix<NComplex>::herm() const
    {
      int i, j, r = cols(), c = rows();
      Matrix<NComplex> adj(r,c);
      
      for (i = 0; i < r; ++i)
        for (j = 0; j < c; ++j)
	      adj.elem(i,j) = conj(elem(j,i)) ;
  
      return adj;    
    }
  
  
#ifdef NO_IMPLICIT_TEMPLATES

// Complex instantation

  template class Matrix<NComplex> ;
  
  template Matrix<NComplex> operator+(const Matrix<NComplex>&,const Matrix<NComplex>&);
  template Matrix<NComplex> operator-(const Matrix<NComplex>&,const Matrix<NComplex>&);
  template Matrix<NComplex> operator*(const Matrix<NComplex>&,const Matrix<NComplex>&);
  template Vector<NComplex> operator*(const Matrix<NComplex>&,const Vector<NComplex>&);
  template int operator==(const Matrix<NComplex>&,const Matrix<NComplex>&);
  // template int operator!=(const Matrix<NComplex>&,const Matrix<NComplex>&);
  template Matrix<NComplex> comm(const Matrix<NComplex>&,const Matrix<NComplex>&);


#endif

}
