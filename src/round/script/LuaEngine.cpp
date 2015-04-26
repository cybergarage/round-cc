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

#include <round/Const.h>
#include <round/common/encoding/Base64.h>
#include <round/core/Log.h>
#include <round/script/Lua.h>
#include <round/script/Lua.h>
#include <round/script/lua/LuaFunction.h>

#if defined(ROUND_SUPPORT_TCL)

const std::string Round::LuaEngine::LANGUAGE = "lua";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Round::LuaEngine::LuaEngine() : ScriptEngine(LANGUAGE) {
  this->luaState = luaL_newstate();

  luaL_openlibs(this->luaState);

  lua_register(this->luaState, ROUNDCC_SYSTEM_METHOD_GET_NETWORK_STATE, round_lua_getnetworkstate);
  lua_register(this->luaState, ROUNDCC_SYSTEM_METHOD_GET_CLUSTER_STATE, round_lua_getclusterstate);
  lua_register(this->luaState, ROUNDCC_SYSTEM_METHOD_GET_NODE_STATE, round_lua_getnodestate);
  lua_register(this->luaState, ROUNDCC_SYSTEM_METHOD_SET_REG, round_lua_setregistry);
  lua_register(this->luaState, ROUNDCC_SYSTEM_METHOD_GET_REG, round_lua_getregistry);
  lua_register(this->luaState, ROUNDCC_SCRIPT_POST_METHOD, round_lua_postmethod);
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
  lock();
  
  round_lua_setlocalnode(hasNode() ? getNode() : NULL);
  
  int nStack = lua_gettop(this->luaState);
  
  if (luaL_loadstring(this->luaState, (const char *)luaScript->getCode()) != 0) {
    nStack = lua_gettop(this->luaState);
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInternalError, error);
    error->setMessage(lua_tostring(this->luaState, -1));
    lua_pop(this->luaState, 1);
    nStack = lua_gettop(this->luaState);

    round_lua_setlocalnode(NULL);
    unlock();
    
    return false;
  }

  nStack = lua_gettop(this->luaState);
  
  if(lua_pcall(this->luaState, 0, 0, 0) != 0) {
    nStack = lua_gettop(this->luaState);
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInternalError, error);
    error->setMessage(lua_tostring(this->luaState, -1));
    lua_pop(this->luaState, 1);
    nStack = lua_gettop(this->luaState);
    
    round_lua_setlocalnode(NULL);
    unlock();
    
    return false;
  }
  
  nStack = lua_gettop(this->luaState);
  
  lua_getglobal(this->luaState, luaScript->getName().c_str());
  lua_pushstring(this->luaState, params.c_str());

  nStack = lua_gettop(this->luaState);
  
  int callResult = lua_pcall(this->luaState, 1, 1, 0);
  if (callResult == 0) {
    *results = lua_tostring(this->luaState, -1);
  }
  else {
    RPC::JSON::ErrorCodeToError(RPC::JSON::ErrorCodeInternalError, error);
    error->setMessage(lua_tostring(this->luaState, -1));
  }
  
  nStack = lua_gettop(this->luaState);
  
  lua_pop(this->luaState, 1);
  
  nStack = lua_gettop(this->luaState);
 
  round_lua_setlocalnode(NULL);
  unlock();

  return (callResult == 0) ? true : false;
}

#endif
