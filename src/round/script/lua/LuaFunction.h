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

int round_lua_getnetworkstate(lua_State* L);
int round_lua_getclusterstate(lua_State* L);
int round_lua_getnodestate(lua_State* L);
int round_lua_setregistry(lua_State* L);
int round_lua_getregistry(lua_State* L);
int round_lua_postmethod(lua_State* L);

void round_lua_setlocalnode(Round::Node *);
Round::Node *round_lua_getlocalnode();

#endif
