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


#ifndef QERR_H
#define QERR_H

#include "qnamesp.h"


// ------------------------------------------------------------------
// Class CV::Error_Message
// This class sets up an error message object.  The object holds
// a message that will get printed if throw_error is called.
// Usage:
//      Error_Message errmsg;
//      errmsg("hello");
// Then later, if  "throw_error" called, the error handler will print
// 'hello' (until errmsg is destroyed).
  
class CV::Error_Message {
private:
  string s_;
  Error_Message* next_;
  static Error_Message* base_;
public:
  Error_Message();
  ~Error_Message();
  void set_string(const string& s1) { s_ = s1;}
  static void init_error_message_list();
  static void put_error_messages_into_stream(ostream& os);
};


// ------------------------------------------------------------------
// Class CV::Error_Task
// This class is holds a task to be executed if there is an error.
// This class is an abstract base class.

class CV::Error_Task {
private:
  Error_Task* next_;
  static Error_Task* base_;
  virtual void on_error_do(const string&) { };
public:
  Error_Task();
  virtual ~Error_Task();
  static void init_error_task_list();
  friend void CV::throw_error(const string& s);
};


// ------------------------------------------------------------------
// Class CV::Error
// This class is thrown by exceptions if exceptions enabled.

namespace CV {
  const int ERROR_BUF_LEN = 2000;
  void set_matlab_error_ostream(ostream* os);
}

class CV::Error {
private:

  char concatenated_error_messages_[ERROR_BUF_LEN];
  // Only throw_error can create this
  explicit Error(const string& msg);
public:
  Error(const Error& e);
  ~Error();
  const char* get_error_messages() { return concatenated_error_messages_; };
  friend void CV::throw_error(const string& s);
};

#endif
