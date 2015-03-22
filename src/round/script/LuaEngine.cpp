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
  int loadingResult = luaL_loadstring(this->luaState, (const char *)scriptCode);
  lua_settop(this->luaState, 0);
  return (loadingResult == 0) ? true : false;;
}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

bool Round::LuaEngine::run(const Script *luaScript, const std::string &params, std::string *results, Error *error) const {
  if (luaL_loadstring(this->luaState, (const char *)luaScript->getCode()) != 0) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInternalError, error);
    return false;
  }
  
  lua_getglobal(this->luaState, luaScript->getName().c_str());
  lua_pushstring(this->luaState, params.c_str());

  if (lua_pcall(this->luaState, 1, 1, 0) != 0) {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInternalError, error);
    error->setMessage(lua_tostring(this->luaState, -1));
    lua_settop(this->luaState, 0);
    return false;
  }

  *results = lua_tostring(this->luaState, -1);
  lua_settop(this->luaState, 0);
  
  return true;
}

#endif
