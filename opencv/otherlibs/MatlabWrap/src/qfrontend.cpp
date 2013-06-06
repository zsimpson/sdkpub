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

#include "qfrontend.h"
#include "string.h"

#include "ipl.h"

namespace {

  using namespace CV;
  using namespace CV::FrontEnd;
  using std::streambuf;

#ifndef OLD_STYLE_STREAMBUF
  using std::char_traits;
  typedef char_traits<char> char_traits_char;
  int local_eof() {
    return char_traits_char::eof();
  }
#else
  int local_eof() {
    return EOF;
  }
#endif

  const int STREAMBUF_BUFLEN = 255;

  class MatlabStreambuf: public streambuf {
  private:
    void put_buffer();
    void put_char(int);
    char my_buffer[STREAMBUF_BUFLEN];
    int buffer_next;
  protected:
    int overflow(int);
    int underflow() { return 0; }
    int sync();
  public:
    MatlabStreambuf();
    ~MatlabStreambuf();
  };
  
  MatlabStreambuf::MatlabStreambuf(): streambuf() {
    setp(0,0);
    setg(0,0,0);
    buffer_next = 0;
  }
  
  MatlabStreambuf::~MatlabStreambuf() {
    sync();
  }
  
  int MatlabStreambuf::overflow(int c) {
    put_buffer();
    if (c != local_eof())
      if (pbase() == epptr())
        put_char(c);
      else 
        sputc(c);
      return 0;
  }

  int MatlabStreambuf::sync() {
    put_buffer();
    my_buffer[buffer_next] = 0;
    mexPrintf("%s", my_buffer);
    buffer_next = 0;
    return 0;
  }
  
  void MatlabStreambuf::put_char(int c) {
    my_buffer[buffer_next++] = c;
    if (buffer_next == STREAMBUF_BUFLEN - 1 || c == '\n' || c == 0) {
      my_buffer[buffer_next] = 0;
      mexPrintf("%s", my_buffer);
      buffer_next = 0;
    }
  }

  void MatlabStreambuf::put_buffer() {
    ptrdiff_t len = pptr() - pbase();
    if (len != 0) {
      if (buffer_next + len + 2 > STREAMBUF_BUFLEN) {
	if (buffer_next > 0) {
	  my_buffer[buffer_next] = 0;
	  mexPrintf("%s", my_buffer);
	  buffer_next = 0;
	}
	char* buf1 = new char[len + 1];
	for (int j = 0; j < len; ++j)
	  buf1[j] = pbase()[j];
	buf1[len] = 0;
	mexPrintf("%s", buf1);
	delete[] buf1;
      }
      else {
	for (int j = 0; j < len; j++)
	  my_buffer[buffer_next++] = pbase()[j];
      }
    }
    setp(pbase(), epptr());
  }
  
  void default_tol_errmsg1() {
    mexPrintf("An error has occurred accessing global variable GM_DEFAULT_TOL\n");
    mexPrintf("This error may indicate that initialization routine 'startup.m' was not executed.\n");
    mexPrintf("Please read the 'readme' file shipped with CV for more information about startup.m.\n");
  }
}

//-----------------------------------------------------------------------------

CV::FrontEnd::InterpOStream::InterpOStream(Interpreter&) :
sb_(0), os_(0) {
	sb_ = new MatlabStreambuf;
	os_ = new CV::ostream(sb_);
}

CV::FrontEnd::InterpOStream::~InterpOStream() {
	if (os_) delete os_;
	if (sb_) delete sb_;
}

//-----------------------------------------------------------------------------

void
CV::FrontEnd::verify_image(mxArray* phs_[] ,int narg, const char* routine_name,
		int &mrows, int &ncols, int &channels, int &depth, mxClassID &cls, void** data) {
	
	int dim = mxGetNumberOfDimensions(phs_[narg]);
	mrows = mxGetM(phs_[narg]);
	ncols = mxGetN(phs_[narg]);
	
	if (dim == 3)
	{
		ncols /= 3; channels = 3;
	} else if (dim == 2)
	{
		channels = 1;
	} else
	{
		ostringstream ostr;
		ostr << routine_name << " must have image (i.e. [h][w][3] or [h][w] array of numbers) in " 
			<< narg << " argument";
		throw_error(ostr.str());
	}
	
	if ( !mxIsNumeric(phs_[narg]) )
	{
		ostringstream ostr;
		ostr << routine_name << " must have image (i.e. [h][w][3] or [h][w] array of numbers) in " 
			<< narg << " argument";
		throw_error(ostr.str());
	}
	
	if ( mxIsComplex(phs_[narg]) ) {
		ostringstream ostr;
		ostr << routine_name << " must have image (i.e. [h][w][3] or [h][w] array of noncomplex numbers) in " 
			<< narg << " argument";
		throw_error(ostr.str());
	}
	
	if ( mxIsDouble(phs_[narg]) ) 
		depth = 64;
	else if ( mxIsSingle(phs_[narg]) )
		depth = 32;
	else if ( mxIsInt8(phs_[narg]) ) 
		depth = IPL_DEPTH_8S;
	else if ( mxIsUint8(phs_[narg]) ) 
		depth = IPL_DEPTH_8U;
	else if ( mxIsInt16(phs_[narg]) )
		depth = IPL_DEPTH_16S;
	else if ( mxIsUint16(phs_[narg]) )
		depth = IPL_DEPTH_16U;
	else if ( mxIsInt32(phs_[narg]) ) 
		depth = IPL_DEPTH_32S;
	else if ( mxIsUint32(phs_[narg]) )
		depth = IPL_DEPTH_32S;
	
	cls =  mxGetClassID(phs_[narg]);
	*data = (void*)mxGetPr(phs_[narg]);
	
	return;
}

void
CV::FrontEnd::verify_numeric(mxArray* phs_[], int narg, const char* routine_name,
										 int mrows, int ncols) {
	int _mrows,_ncols;
	
	if ( !mxIsNumeric(phs_[narg]) )
	{
		ostringstream ostr;
		ostr << routine_name << " must have a numeric array in " 
			<< narg << " argument";
		throw_error(ostr.str());
	}
	
	_mrows = mxGetM(phs_[narg]);
	_ncols = mxGetN(phs_[narg]);
	
	if (_mrows != mrows || _ncols != ncols)
	{
		ostringstream ostr;
		ostr << routine_name << " must have a numeric array in " 
			<< narg << " argument with " << mrows << " rows and " << ncols <<" colomns";
		throw_error(ostr.str());
	}
	
	return;
}

int
CV::FrontEnd::verify_numeric_array(mxArray* phs_[], int narg, const char* routine_name) {
	
	if ( !mxIsNumeric(phs_[narg]) )
	{
		ostringstream ostr;
		ostr << routine_name << " must have a numeric array in " 
			<< narg << " argument";
		throw_error(ostr.str());
	}
	
	return mxGetNumberOfElements(phs_[narg]);
}

//-----------------------------------------------------------------------------

CV::string CV::FrontEnd::get_string(const mxArray *mxArr) {
	int l = mxGetN(mxArr);
	char* buf = new char[l + 2];
	mxGetString(mxArr, buf, l + 1);
	string s(buf);
	delete[] buf;
	return s;
}


//-----------------------------------------------------------------------------    
    
/*CV::FrontEnd::ArgValType::ArgValType(int nrhs, const mxArray** prhs) {
  nrhs_ = nrhs;
  prhs_ = prhs;
}*/

/*CV::FrontEnd::ArgValType::~ArgValType() {
}*/

/*void 
CV::FrontEnd::ArgValType::verify_nargin(int nargin) const {
	if (nrhs_ !=  nargin) 
	{
		ostringstream ostr;
		ostr << "Routine expected " << nargin << " argument";
		if (nargin != 1)
			ostr << "s";
		throw_error(ostr.str());
	}
}

void 
CV::FrontEnd::ArgValType::verify_nargin_min(int narginmin, 
												const char* routine_name) const {
	if (nrhs_ <  narginmin) 
	{
		ostringstream ostr;
		ostr << routine_name << " expected not less than" << narginmin << " argument";
		if (narginmin != 1)
			ostr << "s";
		throw_error(ostr.str());
	}
}

void 
CV::FrontEnd::ArgValType::verify_nargin(int narginmin, 
                                         int narginmax, 
                                         const char* routine_name) const {
  if (nrhs_ < narginmin || nrhs_ > narginmax) {
    ostringstream ostr;
    if (narginmin == narginmax) {
      ostr << "Routine expected " << narginmin << " argument";
      if (narginmin != 1)
        ostr << "s";
    }
    else  {
      ostr << "Routine expected " << narginmin << " to " << narginmax << " arguments";
    }
    ostr << " but " << nrhs_ << " were given";
    throw_error(ostr.str());
  }
}

int CV::FrontEnd::ArgValType::nargin() const {
  return nrhs_;
}
*/
// ----------------------------- Verifying functions ----------------------------------//
/*
void 
CV::FrontEnd::ArgValType::verify_string(int narg, 
											const char* routine_name) const {
	if ( !mxIsChar(prhs_[narg]) )
	{
		ostringstream ostr;
		ostr << routine_name << " must have string in " << narg << " argument";
		throw_error(ostr.str());
	}

	return;
}

void
CV::FrontEnd::ArgValType::verify_image(int narg, const char* routine_name,
	int &mrows, int &ncols, int &channels, int &depth, mxClassID &cls, void** data) const {
	
	int dim = mxGetNumberOfDimensions(prhs_[narg]);
	mrows = mxGetM(prhs_[narg]);
	ncols = mxGetN(prhs_[narg]);
		
	if (dim == 3)
	{
		ncols /= 3; channels = 3;
	} else if (dim == 2)
	{
		channels = 1;
	} else
	{
		ostringstream ostr;
		ostr << routine_name << " must have image (i.e. [h][w][3] or [h][w] array of numbers) in " 
			<< narg << " argument";
		throw_error(ostr.str());
	}
	
	if ( !mxIsNumeric(prhs_[narg]) )
	{
		ostringstream ostr;
		ostr << routine_name << " must have image (i.e. [h][w][3] or [h][w] array of numbers) in " 
			<< narg << " argument";
		throw_error(ostr.str());
	}
	
	if ( mxIsComplex(prhs_[narg]) ) {
		ostringstream ostr;
		ostr << routine_name << " must have image (i.e. [h][w][3] or [h][w] array of noncomplex numbers) in " 
			<< narg << " argument";
		throw_error(ostr.str());
	}
	
	if ( mxIsDouble(prhs_[narg]) ) 
		depth = 64;
	else if ( mxIsSingle(prhs_[narg]) )
		depth = 32;
	else if ( mxIsInt8(prhs_[narg]) ) 
		depth = IPL_DEPTH_8S;
	else if ( mxIsUint8(prhs_[narg]) ) 
		depth = IPL_DEPTH_8U;
	else if ( mxIsInt16(prhs_[narg]) )
		depth = IPL_DEPTH_16S;
	else if ( mxIsUint16(prhs_[narg]) )
		depth = IPL_DEPTH_16U;
	else if ( mxIsInt32(prhs_[narg]) ) 
		depth = IPL_DEPTH_32S;
	else if ( mxIsUint32(prhs_[narg]) )
		depth = IPL_DEPTH_32S;

	cls =  mxGetClassID(prhs_[narg]);
	*data = (void*)mxGetPr(prhs_[narg]);
	
	return;
}

void
CV::FrontEnd::ArgValType::verify_numeric(int narg, const char* routine_name,
									   int mrows, int ncols) const {
	int _mrows,_ncols;

	if ( !mxIsNumeric(prhs_[narg]) )
	{
		ostringstream ostr;
		ostr << routine_name << " must have a numeric array in " 
			<< narg << " argument";
		throw_error(ostr.str());
	}

	_mrows = mxGetM(prhs_[narg]);
	_ncols = mxGetN(prhs_[narg]);

	if (_mrows != mrows || _ncols != ncols)
	{
		ostringstream ostr;
		ostr << routine_name << " must have a numeric array in " 
			<< narg << " argument with " << mrows << " rows and " << ncols <<" colomns";
		throw_error(ostr.str());
	}

	return;
}

int
CV::FrontEnd::ArgValType::verify_numeric_array(int narg, const char* routine_name) const {
	int _mrows,_ncols;
	
	if ( !mxIsNumeric(prhs_[narg]) )
	{
		ostringstream ostr;
		ostr << routine_name << " must have a numeric array in " 
			<< narg << " argument";
		throw_error(ostr.str());
	}
	
	return mxGetNumberOfElements(prhs_[narg]);
}
*/

// ----------------------------- Getting functions -------------------------------------//
/*
int 
CV::FrontEnd::ArgValType::get_numeric(int narg, int num) const {
		
	if ( mxIsInt32(prhs_[narg]) || mxIsUint32(prhs_[narg]))
	{
		return ((int*)mxGetData(prhs_[narg]))[num];
	} else if (mxIsDouble(prhs_[narg]))
	{
		return static_cast<int>(((double*)mxGetData(prhs_[narg]))[num]);
	} else if (mxIsInt8(prhs_[narg]) || mxIsUint8(prhs_[narg]))
	{
		return static_cast<int>(((char*)mxGetData(prhs_[narg]))[num]);
	} else if (mxIsInt16(prhs_[narg]) || mxIsUint16(prhs_[narg]))
	{
		return static_cast<int>(((short*)mxGetData(prhs_[narg]))[num]);
	} else if (mxIsSingle(prhs_[narg]))
	{
		return static_cast<int>(((float*)mxGetData(prhs_[narg]))[num]);
	}

	throw_error("Function get_numeric failed");
	return -1;
}

template <class T>
void
CV::FrontEnd::ArgValType::get_numeric_array(int narg, int num, T* array) const {

	if ( mxIsInt32(prhs_[narg]) || mxIsUint32(prhs_[narg]))
	{
		for (int i = 0; i < num; i++)
			((T*)array)[i] = static_cast<T>(((int*)mxGetData(prhs_[narg]))[i]);
		return;
	} else if (mxIsDouble(prhs_[narg]))
	{
		for (int i = 0; i < num; i++)
			((T*)array)[i] = static_cast<T>(((double*)mxGetData(prhs_[narg]))[i]);
		return;
	} else if (mxIsInt8(prhs_[narg]) || mxIsUint8(prhs_[narg]))
	{
		for (int i = 0; i < num; i++)
			((T*)array)[i] = static_cast<T>(((char*)mxGetData(prhs_[narg]))[i]);
		return;
	} else if (mxIsInt16(prhs_[narg]) || mxIsUint16(prhs_[narg]))
	{ 
		for (int i = 0; i < num; i++)
			((T*)array)[i] = static_cast<T>(((short*)mxGetData(prhs_[narg]))[i]);
		return;
	} else if (mxIsSingle(prhs_[narg]))
	{
		for (int i = 0; i < num; i++)
			((T*)array)[i] =  static_cast<T>(((float*)mxGetData(prhs_[narg]))[i]);
		return;
	}
	
	throw_error("Function get_numeric_array failed");
	return;
}

char
CV::FrontEnd::ArgValType::get_char(int narg, int num) const {

	char * ch = mxArrayToString(prhs_[narg]);
	return ch[num];
}
*/

/*int 
CV::FrontEnd::ArgValType::get_int(int argidx) const {
#ifdef RANGECHECK
  if (argidx < 0 || argidx >= nrhs_)
    throw_error("Argidx range error 2");
#endif
  if (!mxIsDouble(prhs_[argidx]) || mxIsSparse(prhs_[argidx])
      || mxGetM(prhs_[argidx]) * mxGetN(prhs_[argidx]) != 1) {
    ostringstream os;
    os << "Argument #" << argidx << " is supposed to be an integer";
    throw_error(os.str());
  }
  double returnvald = *mxGetPr(prhs_[argidx]);
  int returnval = static_cast<int>(returnvald);
  if (returnvald != static_cast<double>(returnval)) {
    ostringstream os;
    os << "Argument #" << argidx << " is supposed to be an integer";
    throw_error(os.str());
  }
  return returnval;
}


double 
CV::FrontEnd::ArgValType::get_double(int argidx) const {
#ifdef RANGECHECK
  if (argidx < 0 || argidx >= nrhs_)
    throw_error("Argidx range error 2");
#endif
  if (!mxIsDouble(prhs_[argidx]) || mxIsSparse(prhs_[argidx])
      || mxGetM(prhs_[argidx]) * mxGetN(prhs_[argidx]) != 1) {
    ostringstream os;
    os << "Argument #" << argidx << " is supposed to be a scalar";
    throw_error(os.str());
  }
  return *mxGetPr(prhs_[argidx]);
}


CV::Object_Type_Code 
CV::FrontEnd::ArgValType::determine_argument_type(int argidx) const {
#ifdef RANGECHECK
  if (argidx < 0 || argidx >= nrhs_)
    throw_error("Argidx range error 4b");
#endif  
  return get_obj_type(prhs_[argidx]);
}


bool
CV::FrontEnd::ArgValType::get_bool(int argidx) const {
  return get_int(argidx) != 0;
}*/

/*#ifndef BUG_IN_USING
using CV::vector;
#endif*/


/*CV::FrontEnd::ReturnValType::ReturnValType(int nlhs, mxArray** plhs) {
  nlhs_ = nlhs;
  plhs_ = plhs;
}

CV::FrontEnd::ReturnValType::~ReturnValType() {
}

void 
CV::FrontEnd::ReturnValType::verify_nargout(int nargoutmin, 
                                             int nargoutmax, 
                                             const char* routine_name) {
  if (nlhs_ < nargoutmin || nlhs_ > nargoutmax) {
    ostringstream os;
    os << "Wrong number of output arguments to " << routine_name 
       << "; expected " << nargoutmin << " to " << nargoutmax;
    throw_error(os.str());
  }
  if (nlhs_ == 0 && nargoutmax > 0)
    nlhs_ = 1;
}

void 
CV::FrontEnd::ReturnValType::verify_nargout(int nargin) const {
	if (nlhs_ !=  nargin) 
	{
		ostringstream ostr;
		ostr << "Routine expected " << nargin << " argument";
		if (nargin != 1)
			ostr << "s";
		throw_error(ostr.str());
	}
}

void CV::FrontEnd::ReturnValType::checkarg_(int idx) {
  if (idx < 0 || idx >= nlhs_) 
    throw_error("returnval put called for index out of range");
}


int CV::FrontEnd::ReturnValType::nargout() const {
  return nlhs_;
}

void
CV::FrontEnd::ReturnValType::verify_image(int narg, const char* routine_name,
	int &mrows, int &ncols, int &channels, int &depth, mxClassID &cls, void** data) const {
	
	int dim = mxGetNumberOfDimensions(plhs_[narg]);
	mrows = mxGetM(plhs_[narg]);
	ncols = mxGetN(plhs_[narg]);
	
	if (dim == 3)
	{
		ncols /= 3; channels = 3;
	} else if (dim == 2)
	{
		channels = 1;
	} else
	{
		ostringstream ostr;
		ostr << routine_name << " must have image (i.e. [h][w][3] or [h][w] array of numbers) in " 
			<< narg << " argument";
		throw_error(ostr.str());
	}
	
	if ( !mxIsNumeric(plhs_[narg]) )
	{
		ostringstream ostr;
		ostr << routine_name << " must have image (i.e. [h][w][3] or [h][w] array of numbers) in " 
			<< narg << " argument";
		throw_error(ostr.str());
	}
	
	if ( mxIsComplex(plhs_[narg]) ) {
		ostringstream ostr;
		ostr << routine_name << " must have image (i.e. [h][w][3] or [h][w] array of noncomplex numbers) in " 
			<< narg << " argument";
		throw_error(ostr.str());
	}
	
	if ( mxIsDouble(plhs_[narg]) ) 
		depth = 64;
	else if ( mxIsSingle(plhs_[narg]) )
		depth = 32;
	else if ( mxIsInt8(plhs_[narg]) ) 
		depth = IPL_DEPTH_8S;
	else if ( mxIsUint8(plhs_[narg]) ) 
		depth = IPL_DEPTH_8U;
	else if ( mxIsInt16(plhs_[narg]) )
		depth = IPL_DEPTH_16S;
	else if ( mxIsUint16(plhs_[narg]) )
		depth = IPL_DEPTH_16U;
	else if ( mxIsInt32(plhs_[narg]) ) 
		depth = IPL_DEPTH_32S;
	else if ( mxIsUint32(plhs_[narg]) )
		depth = IPL_DEPTH_32S;
	
	cls =  mxGetClassID(plhs_[narg]);
	*data = (void*)mxGetPr(plhs_[narg]);
	
	return;
}


void 
CV::FrontEnd::ReturnValType::put_double(int argidx, double val) {
#ifdef DEBUGGING
  checkarg_(argidx);
#endif
  plhs_[argidx] = mxCreateDoubleMatrix(1, 1, mxREAL);
  *mxGetPr(plhs_[argidx]) = val;
}

void 
CV::FrontEnd::ReturnValType::put_int(int argidx, int val) {
#ifdef DEBUGGING
  checkarg_(argidx);
#endif
  plhs_[argidx] = mxCreateDoubleMatrix(1, 1, mxREAL);
  *mxGetPr(plhs_[argidx]) = static_cast<double>(val);
}

void 
CV::FrontEnd::ReturnValType::put_string(int argidx, const string& s) {
#ifdef DEBUGGING
  checkarg_(argidx);
#endif
  int nr = s.length();
  plhs_[argidx] = mxCreateString(s.c_str());
}
*/


/*
// ------------------------------------------------------------------
// default_tol
// get the default tolerance from global variable gm_default_tol
// ------------------------------------------------------------------

double CV::FrontEnd::default_tol(Interpreter&) {
  const mxArray* gm_default_tola = 
    mexGetArrayPtr("GM_DEFAULT_TOL", "global");
  if (!gm_default_tola) {
    default_tol_errmsg1();
    throw_error("GM_DEFAULT_TOL global variable absent");
  }
  if (!mxIsDouble(gm_default_tola) || mxIsSparse(gm_default_tola)
      || mxGetPi(gm_default_tola) ||
      mxGetM(gm_default_tola) * mxGetN(gm_default_tola) != 1) {
    default_tol_errmsg1();
    throw_error("GM_DEFAULT_TOL global variable wrong type");
  }
  double x = *mxGetPr(gm_default_tola);
  if (x <= 0 || x > 1) {
    default_tol_errmsg1();
    throw_error("GM_DEFAULT_TOL out of range");
  }
  return x;
}*/
