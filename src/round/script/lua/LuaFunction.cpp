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

// FIXME : Update not to use the global variable
static Round::Node *gRoundLuaEngineLocalNode = NULL;

void round_lua_setlocalnode(Round::Node *node) {
  gRoundLuaEngineLocalNode = node;
}

Round::Node *round_lua_getlocalnode() {
  return gRoundLuaEngineLocalNode;
}

bool round_lua_haslocalnode() {
  return (gRoundLuaEngineLocalNode != NULL) ? true : false;
}

int round_lua_getnetworkstate(lua_State* L)
{
  std::string json = "";
  
  Round::LocalNode *node = dynamic_cast<Round::LocalNode *>(round_lua_getlocalnode());
  if (node) {
    Round::NodeResponse nodeRes;
    Round::SystemGetNetworkInfoResponse sysRes(&nodeRes);
    sysRes.setClusters(node);
    nodeRes.getResult(&json);
  }
  
  lua_pushstring(L, json.c_str());
  
  return 1;
}

int round_lua_getclusterstate(lua_State* L)
{
  std::string json = "";
  
  Round::LocalNode *node = dynamic_cast<Round::LocalNode *>(round_lua_getlocalnode());
  if (node) {
    Round::NodeResponse nodeRes;
    Round::SystemGetClusterInfoResponse sysRes(&nodeRes);
    sysRes.setCluster(node);
    nodeRes.getResult(&json);
  }
  
  lua_pushstring(L, json.c_str());
  
  return 1;
}

int round_lua_getnodestate(lua_State* L)
{
  std::string json = "";
  
  Round::LocalNode *node = dynamic_cast<Round::LocalNode *>(round_lua_getlocalnode());
  if (node) {
    Round::NodeResponse nodeRes;
    Round::SystemGetNodeInfoResponse sysRes(&nodeRes);
    sysRes.setNode(node);
    nodeRes.getResult(&json);
  }
  
  lua_pushstring(L, json.c_str());
  
  return 1;
}

int round_lua_setregistry(lua_State* L)
{
  Round::Node *node = round_lua_getlocalnode();
  std::string key = luaL_checkstring(L, 1);
  std::string val = luaL_checkstring(L, 2);

  bool isSuccess = false;
  if (!node && (0 < key.length())) {
    Round::Error err;
    isSuccess = node->setRegistry(key, val, &err);
  }

  lua_pushboolean(L, isSuccess);
  
  return 1;
}

int round_lua_getregistry(lua_State* L)
{
  std::string val = "";
  
  Round::Node *node = round_lua_getlocalnode();
  std::string key = luaL_checkstring(L, 1);
  if (!node && (0 < key.length())) {
    Round::Error err;
    node->getRegistry(key, &val, &err);
  }
  
  lua_pushstring(L, val.c_str());

  return 1;
}

int round_lua_postmethod(lua_State* L)
{
  return 1;
}
