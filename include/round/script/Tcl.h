/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_SCRIPT_TCL_H_
#define _ROUNDCC_SCRIPT_TCL_H_

#include <round/core/Script.h>

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
  bool run(const std::string &source, std::string *results, Error *error) const;

private:
  struct Tcl_Interp *interp;
};
  
}

#endif
