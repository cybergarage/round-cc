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

#if defined(ROUND_SUPPORT_LUA)

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
    if (sysRes.setClusters(node)) {
      nodeRes.getResult(&json);
    }
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
    if (sysRes.setCluster(node)) {
      nodeRes.getResult(&json);
    }
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
    if (sysRes.setNode(node)) {
        nodeRes.getResult(&json);
    }
  }
  
  lua_pushstring(L, json.c_str());
  
  return 1;
}

int round_lua_setregistry(lua_State* L)
{
  Round::Node *localNode = round_lua_getlocalnode();
  std::string key = luaL_checkstring(L, 1);
  std::string val = luaL_checkstring(L, 2);

  bool isSuccess = false;
  if (localNode && (0 < key.length())) {
    Round::Error err;
    isSuccess = localNode->setRegistry(key, val, &err);
  }

  lua_pushboolean(L, isSuccess);
  
  return 1;
}

int round_lua_getregistry(lua_State* L)
{
  bool isSuccess = false;
  std::string result = "";
  
  Round::Node *localNode = round_lua_getlocalnode();
  std::string key = luaL_checkstring(L, 1);
  if (localNode && (0 < key.length())) {
    Round::Error err;
    Round::Registry reg;
    isSuccess = localNode->getRegistry(key, &reg, &err);
    
    if (isSuccess) {
      Round::JSONDictionary jsonDict;
      reg.toJSONDictionary(&jsonDict);
      jsonDict.toJSONString(&result);
    }
  }
  
  lua_pushboolean(L, isSuccess);
  lua_pushstring(L, result.c_str());

  return 2;
}

int round_lua_removeregistry(lua_State* L)
{
  bool isSuccess = false;
  
  Round::Node *localNode = round_lua_getlocalnode();
  std::string key = luaL_checkstring(L, 1);
  if (localNode && (0 < key.length())) {
    Round::Error err;
    isSuccess = localNode->removeRegistry(key, &err);
  }
  
  lua_pushboolean(L, isSuccess);
  
  return 1;
}

int round_lua_postmethod(lua_State* L)
{
  bool isSuccess = false;
  std::string result;
  
  std::string method = luaL_checkstring(L, 1);
  std::string params = luaL_checkstring(L, 2);
  std::string dest = luaL_checkstring(L, 3);
  
  Round::Node *localNode = round_lua_getlocalnode();
  if (localNode) {
    Round::Error error;
    isSuccess = localNode->postMessage(dest, method, params, &result);
  }
  
  lua_pushboolean(L, isSuccess);
  lua_pushstring(L, result.c_str());
  
  return 2;
}

#endif
