/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <sstream>
#include <boost/algorithm/string/replace.hpp>

#include <round/common/encoding/Base64.h>
#include <round/core/Log.h>
#include <round/script/Tcl.h>

#if defined(ROUND_SUPPORT_TCL)

const std::string Round::TclEngine::LANGUAGE = "tcl";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Round::TclEngine::TclEngine() : ScriptEngine(LANGUAGE) {
  /*
  this->interp = Tcl_CreateInterp();
   */
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////

Round::TclEngine::~TclEngine() {
}

////////////////////////////////////////////////
// compile
////////////////////////////////////////////////

bool Round::TclEngine::compile(const Script *script) const {
  return true;
}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

bool Round::TclEngine::run(const Script *tclScript, const std::string &params, std::string *results, Error *error) const {
  return false;
}

bool Round::TclEngine::run(const std::string &script, std::string *result, Error *error) const {
  return false;
}

#endif
