/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_SYSTEM_METHOD_TCL_H_
#define _ROUNDCC_SYSTEM_METHOD_TCL_H_

#include <round/core/Script.h>

#if defined(ROUND_SUPPORT_TCL)

#if defined(HAVE_TCL_TCL_H)
#include <tcl/tcl.h>
#else
#include <tcl.h>
#endif

namespace Round {

class TclEngine : public ScriptEngine {
    
 public:
  
  static const std::string LANGUAGE;
  
 public:
  TclEngine();
  
  ~TclEngine();
  
  bool compile(const Script *script) const;
  bool run(const Script *script, const std::string &params, std::string *results, Error *error) const;

private:
  struct Tcl_Interp *interp;
};
  
}

#endif

#endif
