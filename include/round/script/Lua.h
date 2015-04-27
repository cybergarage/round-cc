/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_SYSTEM_METHOD_LUA_H_
#define _ROUNDCC_SYSTEM_METHOD_LUA_H_

#include <round/core/Script.h>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace Round {

class LuaEngine : public ScriptEngine {
    
 public:
  
  static const std::string LANGUAGE;
  
 public:
  LuaEngine();
  ~LuaEngine();
  
  bool compile(const Script *script) const;
  bool run(const Script *script, const std::string &params, std::string *results, Error *error) const;
  bool run(const std::string &script, std::string *result, Error *error) const;

private:
  
  lua_State *luaState;
};
  
}

#endif
