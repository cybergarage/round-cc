/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_SYSTEM_METHOD_LUA_FUNCTION_H_
#define _ROUNDCC_SYSTEM_METHOD_LUA_FUNCTION_H_

#include <round/script/Lua.h>

#if defined(ROUND_SUPPORT_LUA)

int round_lua_getnetworkstate(lua_State* L);
int round_lua_getclusterstate(lua_State* L);
int round_lua_getnodestate(lua_State* L);
int round_lua_setregistry(lua_State* L);
int round_lua_getregistry(lua_State* L);
int round_lua_removeregistry(lua_State* L);
int round_lua_postmethod(lua_State* L);

void round_lua_setlocalnode(Round::Node *);
Round::Node *round_lua_getlocalnode();
bool round_lua_haslocalnode();

#endif

#endif
