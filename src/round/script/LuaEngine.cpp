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
#include <round/script/Lua.h>

#if defined(ROUND_SUPPORT_TCL)

const std::string Round::LuaEngine::LANGUAGE = "lua";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Round::LuaEngine::LuaEngine() : ScriptEngine(LANGUAGE) {
  this->luaState = luaL_newstate();
  luaL_openlibs(this->luaState);
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////

Round::LuaEngine::~LuaEngine() {
  lua_close(this->luaState);
}

////////////////////////////////////////////////
// compile
////////////////////////////////////////////////

bool Round::LuaEngine::compile(const Script *luaScript) const {
  const byte *scriptCode = luaScript->getCode();
  if (luaL_loadstring(this->luaState, (const char *)scriptCode) != 0)
    return false;
  return true;
}

////////////////////////////////////////////////
// getSourceCode
////////////////////////////////////////////////

bool Round::LuaEngine::getSourceCode(const Script *luaScript, const std::string &params, std::string *sourceCode) const {
  std::stringstream jsSource;
  
  jsSource << luaScript->getCode() << std::endl;
  
  std::string jsonParams = boost::algorithm::replace_all_copy(params, "\"", "\\\"");
  
  /*
  jsSource << "var jsonParams = \"" << jsonParams << "\";" << std::endl;
  jsSource << "var params = (0 < jsonParams.length) ? JSON.parse(jsonParams) : jsonParams;" << std::endl;
  
  jsSource << "var results = " << jsScript->getName() << "(params);" << std::endl;
  jsSource << "var jsonResults = JSON.stringify(results);" << std::endl;
  jsSource << "jsonResults;";
  */
  
  *sourceCode = jsSource.str();
  
  return true;
}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

bool Round::LuaEngine::run(const Script *luaScript, const std::string &params, std::string *results, Error *error) const {
  std::string luaSource;
  
  if (!getSourceCode(luaScript, params, &luaSource)) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInternalError, error);
    return false;
  }
  
  if (luaL_loadstring(this->luaState, luaSource.c_str()) != 0)
    return false;
  
  /*
  lua_getglobal(this->luaState, luaScript->getName());
  lua_pushnumber(this->luaState, 'A'); // 第 1 引数の値を積む
  lua_pushnumber(this->luaState, 5); // 第 2 引数
  */
  
  return true;
}

#endif
