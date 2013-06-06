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

#ifndef QFRONTEND_H
#define QFRONTEND_H

#include "qnamesp.h"
#include "wrmacro.h"

extern "C" {
#include "mex.h"
}


namespace CV {
  namespace FrontEnd {
    using namespace CV;

    // This is the front end interpreter.
    class Interpreter {
    };

	// This class defines an ostream that prints out to the
    // interpreter.
	class InterpOStream {
    private:
		std::streambuf* sb_;
		ostream* os_;
    public:
		InterpOStream(Interpreter&);
		~InterpOStream();
		ostream& ostrm() {return *os_;}
    };
    double default_tol(Interpreter&);
    
	// This class holds the argument list to CV routines.
    /*class ArgValType {
    public:
      int nrhs_;
      const mxArray** prhs_;

      ArgValType(const ArgValType&) { }
      void operator=(const ArgValType&) { }
    public:

      // These member functions  are for processing the argument list.
      // For example, get_string gets a string argument, where the
      // specific argument number is argidx.

      string get_string(int argidx) const;
      int get_int(int argidx) const;
      double get_double(int argidx) const;
      bool get_bool(int argidx) const;
      //vector<double> get_vector_double(int argidx) const;
      //vector<string> get_vector_string(int argidx) const;
	  int get_numeric(int narg, int num) const;
	  template <class T>
	  void get_numeric_array(int narg, int num, T* array) const;
	  char get_char(int narg, int num) const;
      Object_Type_Code determine_argument_type(int argidx) const;
      void verify_nargin(int narginmin, int narginmax, const char* routine_name) const;
	  void verify_nargin(int nargin) const ;
	  void verify_nargin_min(int narginmin, const char* routine_name) const;
	  void verify_string(int narg, const char* routine_name) const;
	  //void verify_image(int narg, const char* routine_name,
	  //  int &mrows, int &ncols, int &orig_size, int &channels, int &depth, void** data) const;
	  void verify_image(int narg, const char* routine_name,
		  int &mrows, int &ncols, int &channels, int &depth, mxClassID &cls, void** data) const;
	  void verify_numeric(int narg, const char* routine_name, int mrows, int ncols) const;
	  //Object_Type_Code verify_numeric_or_char(int narg, const char* routine_name, int mrows, int ncols) const;
	  int  CV::FrontEnd::ArgValType::verify_numeric_array(int narg, const char* routine_names) const;
	  int nargin() const;
      ArgValType(int nrhs, const mxArray** prhs);
      ~ArgValType();
    };*/

    // This class holds the returnvalues from CV functions.

    /*class ReturnValType {
    public:
      int nlhs_;
      mxArray** plhs_;

      void checkarg_(int idx);
      ReturnValType(const ReturnValType&) { }
      void operator=(const ReturnValType&) { }
    public:
      void verify_nargout(int nargoutmin, int nargoutmax, const char* routine_name);
	  void verify_nargout(int nargin) const;
      int nargout() const;

      // These functions store computed quantities in the return
      // value list.
      void put_double(int argidx, double data);
      void put_string(int argidx, const string& s);
      void put_int(int argidx, int val);
      //void put_intvector(int argidx, vector<int>& data);
      //void put_doublevector(int argidx, vector<double>& data);
	  void verify_image(int narg, const char* routine_name,
			  int &mrows, int &ncols, int &channels, int &depth, mxClassID &cls, void** data) const;
      ReturnValType(int nlhs, mxArray** plhs);
      ~ReturnValType();
    };*/

	void verify_image(mxArray* phs[], int narg, const char* routine_name,
		int &mrows, int &ncols, int &channels, int &depth, mxClassID &cls, void** data);
	void verify_numeric(mxArray* phs[], int narg, const char* routine_name,
		int mrows, int ncols);
	int verify_numeric_array(mxArray* phs[], int narg, const char* routine_names);
	string get_string(const mxArray *mxArr);

	template <class T>
	void put_numeric_array(mxArray *mxArr, int num, CArr<T> array) {
		
		if ( mxIsInt32(mxArr) || mxIsUint32(mxArr))
		{
			for (int i = 0; i < num; i++)
				((int*)mxGetData(mxArr))[i] = static_cast<int>(array[i]);
			return;
		} else if (mxIsDouble(mxArr))
		{
			//for (int i = 0; i < num; i++)
			//	((double*)mxGetData(mxArr))[i] = static_cast<double>(array[i]);
			mxSetData(mxArr, array);
			return;
		} else if (mxIsInt8(mxArr) || mxIsUint8(mxArr))
		{
			for (int i = 0; i < num; i++)
				((char*)mxGetData(mxArr))[i] = static_cast<char>(array[i]);
			return;
		} else if (mxIsInt16(mxArr) || mxIsUint16(mxArr))
		{ 
			for (int i = 0; i < num; i++)
				((short*)mxGetData(mxArr))[i] = static_cast<short>(array[i]);
			return;
		} else if (mxIsSingle(mxArr))
		{
			for (int i = 0; i < num; i++)
				((float*)mxGetData(mxArr))[i] = static_cast<float>(array[i]);
			return;
		}
		
		throw_error("Function put_numeric_array failed: unknown type of matlab data.");
		return;
	}
	
	template <class T>
	T get_numeric(const mxArray *mxArr, int num) {
		
		if ( mxIsInt32(mxArr) || mxIsUint32(mxArr))
		{
			return static_cast<T>(((int*)mxGetData(mxArr))[num]);;
		} else if (mxIsDouble(mxArr))
		{
			return static_cast<T>(((double*)mxGetData(mxArr))[num]);
		} else if (mxIsInt8(mxArr) || mxIsUint8(mxArr))
		{
			return static_cast<T>(((char*)mxGetData(mxArr))[num]);
		} else if (mxIsInt16(mxArr) || mxIsUint16(mxArr))
		{
			return static_cast<T>(((short*)mxGetData(mxArr))[num]);
		} else if (mxIsSingle(mxArr))
		{
			return static_cast<T>(((float*)mxGetData(mxArr))[num]);
		}
		
		throw_error("Function get_numeric failed");
		return static_cast<T>(-1);
	}

	template <class T>
	void get_numeric_array(const mxArray *mxArr, int num, T* array) {
		
		if ( mxIsInt32(mxArr) || mxIsUint32(mxArr))
		{
			for (int i = 0; i < num; i++)
				((T*)array)[i] = static_cast<T>(((int*)mxGetData(mxArr))[i]);
			return;
		} else if (mxIsDouble(mxArr))
		{
			for (int i = 0; i < num; i++)
				((T*)array)[i] = static_cast<T>(((double*)mxGetData(mxArr))[i]);
			return;
		} else if (mxIsInt8(mxArr) || mxIsUint8(mxArr))
		{
			for (int i = 0; i < num; i++)
				((T*)array)[i] = static_cast<T>(((char*)mxGetData(mxArr))[i]);
			return;
		} else if (mxIsInt16(mxArr) || mxIsUint16(mxArr))
		{ 
			for (int i = 0; i < num; i++)
				((T*)array)[i] = static_cast<T>(((short*)mxGetData(mxArr))[i]);
			return;
		} else if (mxIsSingle(mxArr))
		{
			for (int i = 0; i < num; i++)
				((T*)array)[i] =  static_cast<T>(((float*)mxGetData(mxArr))[i]);
			return;
		}
		
		throw_error("Function get_numeric_array failed: unknown type of matlab data.");
		return;
	}

	/*template <class T>
	void put_numeric_array(const mxArray *mxArr, int num, T* array) {
		
		if ( mxIsInt32(mxArr) || mxIsUint32(mxArr))
		{
			for (int i = 0; i < num; i++)
				((int*)mxGetData(mxArr))[i] = static_cast<int>(array[i]);
			return;
		} else if (mxIsDouble(mxArr))
		{
			for (int i = 0; i < num; i++)
				((double*)mxGetData(mxArr))[i] = static_cast<double>(array[i]);
			return;
		} else if (mxIsInt8(mxArr) || mxIsUint8(mxArr))
		{
			for (int i = 0; i < num; i++)
				((char*)mxGetData(mxArr))[i] = static_cast<char>(array[i]);
			return;
		} else if (mxIsInt16(mxArr) || mxIsUint16(mxArr))
		{ 
			for (int i = 0; i < num; i++)
				((short*)mxGetData(mxArr))[i] = static_cast<short>(array[i]);
			return;
		} else if (mxIsSingle(mxArr))
		{
			for (int i = 0; i < num; i++)
				((float*)mxGetData(mxArr))[i] = static_cast<float>(array[i]);
			return;
		}
		
		throw_error("Function put_numeric_array failed: unknown type of matlab data.");
		return;
	}*/

  }
}

#endif

