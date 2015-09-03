###################################################################
#
# Round for C++
#
# Copyright (C) Satoshi Konno 2014
#
# This is licensed under BSD-style license, see file COPYING.
#
###################################################################

lib_LIBRARIES = libround++.a

AM_CPPFLAGS = \
        -I$(top_srcdir)/include \
        -I$(top_srcdir)/src

AUTOMAKE_OPTIONS = \
        subdir-objects

roundcc_sources = \
	../../src/round/Client.cpp \
	../../src/round/common/BitOption.cpp \
	../../src/round/common/Clock.cpp \
	../../src/round/common/Config.cpp \
	../../src/round/common/ConsistentHashGraph.cpp \
	../../src/round/common/ConsistentHashNode.cpp \
	../../src/round/common/ConsistentHashObject.cpp \
	../../src/round/common/Dictionary.cpp \
	../../src/round/common/DictionaryKeyList.cpp \
	../../src/round/common/digest/MD5.cpp \
	../../src/round/common/digest/SHA.cpp \
	../../src/round/common/DomainServerSocket.cpp \
	../../src/round/common/DomainSocket.cpp \
	../../src/round/common/encoding/Base64.cpp \
	../../src/round/common/encoding/URL.cpp \
	../../src/round/common/Error.cpp \
	../../src/round/common/HashObject.cpp \
	../../src/round/common/json/impl/JSONParserJansson.cpp \
	../../src/round/common/json/impl/JSONParserParse.cpp \
	../../src/round/common/json/JSONArray.cpp \
	../../src/round/common/json/JSONBoolean.cpp \
	../../src/round/common/json/JSONDictionary.cpp \
	../../src/round/common/json/JSONInterger.cpp \
	../../src/round/common/json/JSONNull.cpp \
	../../src/round/common/json/JSONObject.cpp \
	../../src/round/common/json/JSONParser.cpp \
	../../src/round/common/json/JSONReal.cpp \
	../../src/round/common/json/JSONString.cpp \
	../../src/round/common/Message.cpp \
	../../src/round/common/MessageManager.cpp \
	../../src/round/common/MessageQueue.cpp \
	../../src/round/common/Mutex.cpp \
	../../src/round/common/NotificationCenter.cpp \
	../../src/round/common/NotificationObserver.cpp \
	../../src/round/common/Properties.cpp \
	../../src/round/common/Random.cpp \
	../../src/round/common/rpc/RPC.cpp \
	../../src/round/common/rpc/RPCBatchRequest.cpp \
	../../src/round/common/rpc/RPCBatchResponse.cpp \
	../../src/round/common/rpc/RPCMessage.cpp \
	../../src/round/common/rpc/RPCParser.cpp \
	../../src/round/common/rpc/RPCRequest.cpp \
	../../src/round/common/rpc/RPCResponse.cpp \
	../../src/round/common/Semaphore.cpp \
	../../src/round/common/Settings.cpp \
	../../src/round/common/StringTokenizer.cpp \
	../../src/round/common/ThreadCore.cpp \
	../../src/round/common/ThreadList.cpp \
	../../src/round/common/ThreadManager.cpp \
	../../src/round/core/alias/Alias.cpp \
	../../src/round/core/alias/AliasManager.cpp \
	../../src/round/core/alias/AliasMap.cpp \
	../../src/round/core/ClientCore.cpp \
	../../src/round/core/Cluster.cpp \
	../../src/round/core/ClusterList.cpp \
	../../src/round/core/impl/HTTPUServer.cpp \
	../../src/round/core/impl/UPnPNodeFinder.cpp \
	../../src/round/core/impl/UPnPServerNode.cpp \
	../../src/round/core/local/LocalAliasManager.cpp \
	../../src/round/core/local/LocalConfig.cpp \
	../../src/round/core/local/LocalNativeMethodManager.cpp \
	../../src/round/core/local/LocalRegistry.cpp \
	../../src/round/core/local/LocalRouteManager.cpp \
	../../src/round/core/local/LocalScriptManager.cpp \
	../../src/round/core/local/LocalStaticMethodManager.cpp \
	../../src/round/core/local/LocalTriggerManager.cpp \
	../../src/round/core/local/LocalWorker.cpp \
	../../src/round/core/local/method/add_node.cpp \
	../../src/round/core/local/method/exec.cpp \
	../../src/round/core/local/method/get_cluster_state.cpp \
	../../src/round/core/local/method/get_network_state.cpp \
	../../src/round/core/local/method/get_node_config.cpp \
	../../src/round/core/local/method/get_node_state.cpp \
	../../src/round/core/local/method/get_registry.cpp \
	../../src/round/core/local/method/Method.cpp \
	../../src/round/core/local/method/MethodManager.cpp \
	../../src/round/core/local/method/MethodMap.cpp \
	../../src/round/core/local/method/post_job.cpp \
	../../src/round/core/local/method/remove_alias.cpp \
	../../src/round/core/local/method/remove_method.cpp \
	../../src/round/core/local/method/remove_node.cpp \
	../../src/round/core/local/method/remove_registry.cpp \
	../../src/round/core/local/method/remove_route.cpp \
	../../src/round/core/local/method/remove_timer.cpp \
	../../src/round/core/local/method/set_alias.cpp \
	../../src/round/core/local/method/set_method.cpp \
	../../src/round/core/local/method/set_registry.cpp \
	../../src/round/core/local/method/set_route.cpp \
	../../src/round/core/local/method/set_timer.cpp \
	../../src/round/core/local/method/system_method.cpp \
	../../src/round/core/local/method/SystemClusterInfoDict.cpp \
	../../src/round/core/local/method/SystemGetRegistryRequest.cpp \
	../../src/round/core/local/method/SystemGetRegistryResponse.cpp \
	../../src/round/core/local/method/SystemMethodRequest.cpp \
	../../src/round/core/local/method/SystemMethodResponse.cpp \
	../../src/round/core/local/method/SystemNodeInfoDict.cpp \
	../../src/round/core/local/method/SystemRemoveRegistryRequest.cpp \
	../../src/round/core/local/method/SystemSetRegistryRequest.cpp \
	../../src/round/core/LocalNode.cpp \
	../../src/round/core/Logger.cpp \
	../../src/round/core/Node.cpp \
	../../src/round/core/NodeCore.cpp \
	../../src/round/core/NodeFinder.cpp \
	../../src/round/core/NodeFinderNotification.cpp \
	../../src/round/core/NodeFinderObserver.cpp \
	../../src/round/core/NodeGraph.cpp \
	../../src/round/core/NodeList.cpp \
	../../src/round/core/NodeStatus.cpp \
	../../src/round/core/registry/Registry.cpp \
	../../src/round/core/registry/RegistryManager.cpp \
	../../src/round/core/registry/RegistryMap.cpp \
	../../src/round/core/RemoteNode.cpp \
	../../src/round/core/route/Route.cpp \
	../../src/round/core/route/RouteList.cpp \
	../../src/round/core/route/RouteManager.cpp \
	../../src/round/core/route/RouteMap.cpp \
	../../src/round/core/route/RouteObjects.cpp \
	../../src/round/core/rpc/NodeBatchRequest.cpp \
	../../src/round/core/rpc/NodeBatchResponse.cpp \
	../../src/round/core/rpc/NodeRequest.cpp \
	../../src/round/core/rpc/NodeResponse.cpp \
	../../src/round/core/rql/RQLRequest.cpp \
	../../src/round/core/script/Script.cpp \
	../../src/round/core/script/ScriptEngine.cpp \
	../../src/round/core/script/ScriptEngineMap.cpp \
	../../src/round/core/script/ScriptManager.cpp \
	../../src/round/core/script/ScriptMap.cpp \
	../../src/round/core/ServerNode.cpp \
	../../src/round/core/trigger/TimerTrigger.cpp \
	../../src/round/core/trigger/Trigger.cpp \
	../../src/round/core/trigger/TriggerManager.cpp \
	../../src/round/core/trigger/TriggerMap.cpp \
	../../src/round/Finder.cpp \
	../../src/round/script/JavaEngine.cpp \
	../../src/round/script/JavaScriptEngine.cpp \
	../../src/round/script/JavaScriptEngineSpiderMonkey.cpp \
	../../src/round/script/JavaScriptEngineV8.cpp \
	../../src/round/script/js/SpiderMonkeyFunction.cpp \
	../../src/round/script/lua/LuaFunction.cpp \
	../../src/round/script/LuaEngine.cpp \
	../../src/round/script/TclEngine.cpp \
	../../src/round/Server.cpp \
	../../src/round/ui/console/Client.cpp \
	../../src/round/ui/console/cmd/daemon.cpp \
	../../src/round/ui/console/cmd/exit.cpp \
	../../src/round/ui/console/cmd/help.cpp \
	../../src/round/ui/console/cmd/list.cpp \
	../../src/round/ui/console/cmd/method.cpp \
	../../src/round/ui/console/cmd/question.cpp \
	../../src/round/ui/console/cmd/quit.cpp \
	../../src/round/ui/console/cmd/rpm.cpp \
	../../src/round/ui/console/cmd/search.cpp \
	../../src/round/ui/console/cmd/shell.cpp \
	../../src/round/ui/console/cmd/update.cpp \
	../../src/round/ui/console/cmd/use.cpp \
	../../src/round/ui/console/cmd/verbose.cpp \
	../../src/round/ui/console/cmd/version.cpp \
	../../src/round/ui/console/Command.cpp \
	../../src/round/ui/console/Commands.cpp \
	../../src/round/ui/console/Input.cpp \
	../../src/round/ui/console/Options.cpp \
	../../src/round/ui/console/Program.cpp \
	../../src/round/ui/console/Server.cpp

libround___a_SOURCES = \
        $(roundcc_sources)
