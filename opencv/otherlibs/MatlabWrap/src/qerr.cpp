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

#include "qerr.h"

extern "C" {
#include "mex.h"
}

#ifdef USE_MEX_MALLOC
#include <new>

void* operator new(std::size_t size) {
  void* ptr = mxMalloc(size);
  if (size > 0 && ptr == 0)
    mexErrMsgTxt("Out of memory");
  return ptr;
}

void  operator delete(void* ptr) {
  mxFree(ptr);
}

void* operator new[](std::size_t size)  {
  void* ptr = mxMalloc(size);
  if (size > 0 && ptr == 0)
    mexErrMsgTxt("Out of memory");
  return ptr;
}
  
  
void operator delete[](void* ptr)  {
  mxFree(ptr);
}

#endif


CV::Error_Message* CV::Error_Message::base_ = 0;

namespace {
  CV::ostream* matlab_error_ostream = 0;
}

namespace CV {
    void set_matlab_error_ostream(ostream* os) {
      matlab_error_ostream = os;
    }
}


// This could cause a memory leak if things go wrong, but
// if things go right the base will always be zero anyway
// when this is called.

void
CV::Error_Message::init_error_message_list() {
 base_ = 0;
}


CV::Error_Message::Error_Message() {
  Error_Message* curr = base_;
  Error_Message** pointer_to_curr = &base_;
  while (curr != 0) {
    pointer_to_curr = &(curr -> next_);
    curr = curr -> next_;
  }
  *pointer_to_curr = this;
  this -> next_ = 0;
}


CV::Error_Message::~Error_Message() {
  Error_Message* curr = base_;
  Error_Message** pointer_to_curr = &base_;
  while (curr != 0 && curr != this) {
    pointer_to_curr = &(curr -> next_);
    curr = curr -> next_;
  }
  if (curr == this) {
    *pointer_to_curr = this -> next_;
  }
}

void
CV::Error_Message::put_error_messages_into_stream(ostream& os) {
  Error_Message* curr = base_;
  while (curr != 0) {
    os << (curr -> s_) << '\n';
    curr = curr -> next_;
  }
}

CV::Error_Task* CV::Error_Task::base_;

void
CV::Error_Task::init_error_task_list() {
 base_ = 0;
}


CV::Error_Task::Error_Task() {
  Error_Task* curr = base_;
  Error_Task** pointer_to_curr = &base_;
  while (curr != 0) {
    pointer_to_curr = &(curr -> next_);
    curr = curr -> next_;
  }
  *pointer_to_curr = this;
  this -> next_ = 0;
}


CV::Error_Task::~Error_Task() {
  Error_Task* curr = base_;
  Error_Task** pointer_to_curr = &base_;
  while (curr != 0 && curr != this) {
    pointer_to_curr = &(curr -> next_);
    curr = curr -> next_;
  }
  if (curr == this) {
    *pointer_to_curr = this -> next_;
  }
}


CV::Error::Error(const string& msg) {
  ostringstream ostr;
  ostr << msg << '\n';
  Error_Message::put_error_messages_into_stream(ostr);
  string s = ostr.str();
  int l = s.length();
  if (l >= ERROR_BUF_LEN) {
    l = ERROR_BUF_LEN - 1;
  }
  for (int i = 0; i < l; ++i)
    concatenated_error_messages_[i] = s[i];
  concatenated_error_messages_[l] = 0;
}


CV::Error::Error(const Error& other) {
  for (int i = 0; i < ERROR_BUF_LEN; ++i) {
    concatenated_error_messages_[i] = other.concatenated_error_messages_[i];
    if (concatenated_error_messages_[i] == 0) break;
  }
}

CV::Error::~Error() {
}


void CV::throw_error(const string& msg) {

  Error_Task* curr = Error_Task::base_;
  while (curr != 0) {
    curr -> on_error_do(msg);
    curr = curr -> next_;
  }
  if (matlab_error_ostream) {
    CV::Error_Message::put_error_messages_into_stream(*matlab_error_ostream);
#ifndef EXCEPTIONS_ENABLED
    delete matlab_error_ostream;
#endif
  }

#ifdef EXCEPTIONS_ENABLED
  Error e(msg);
  throw e;
#else

  int l = msg.length();
  char* buf = static_cast<char*>(mxMalloc(l + 1));
  msg.copy(buf, l);
  buf[l] = 0;
  mexErrMsgTxt(buf);

#endif
}
