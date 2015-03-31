/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/script/lua/LuaFunction.h>
#include <round/core/local/method/SystemMethod.h>

int round_lua_get_network_state(lua_State* L)
{
  return 1;
}

int round_lua_get_cluster_state(lua_State* L)
{
  return 1;
}

int round_lua_get_node_state(lua_State* L)
{
  return 1;
}

int round_lua_set_reg(lua_State* L)
{
  const char *key = luaL_checkstring(L, 1);
  const char *val = luaL_checkstring(L, 2);
  //lua_pushlightuserdata
  bool isSuccess = false;
  
  lua_pushboolean(L, isSuccess);
  
  return 1;
}

int round_lua_get_reg(lua_State* L)
{
  std::string val = "";
  
  std::string key = luaL_checkstring(L, 1);
  if (0 < key.length()) {
    
  }
  
  lua_pushstring(L, val.c_str());

  return 1;
}

int round_lua_post_method(lua_State* L)
{
  return 1;
}
