/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_SCRIPT_LUA_FUNCTION_H_
#define _ROUNDCC_SCRIPT_LUA_FUNCTION_H_

#include <round/script/Lua.h>

int round_lua_get_network_state(lua_State* L);
int round_lua_get_cluster_state(lua_State* L);
int round_lua_get_node_state(lua_State* L);
int round_lua_set_reg(lua_State* L);
int round_lua_get_reg(lua_State* L);
int round_lua_post_method(lua_State* L);

#endif
