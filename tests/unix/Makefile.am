###################################################################
#
# Round for C++
#
# Copyright (C) Satoshi Konno 2014
#
# This is licensed under BSD-style license, see file COPYING.
#
###################################################################

noinst_PROGRAMS = roundtest

AM_CPPFLAGS = \
        -I$(top_srcdir)/include -I../ \
        -I$(top_srcdir)/src \
        @XML_CFLAGS@

AUTOMAKE_OPTIONS = \
	subdir-objects

roundtest_SOURCES = \
	..//common/Base64Test.cpp \
	..//common/BitOptionTest.cpp \
	..//common/ClockTest.cpp \
	..//common/ConfigTest.cpp \
	..//common/ConsistentHashTest.cpp \
	..//common/DictionaryTest.cpp \
	..//common/DomainSocketTest.cpp \
	..//common/ErrorTest.cpp \
	..//common/HashObjectTest.cpp \
	..//common/HashTest.cpp \
	..//common/JSONParserTest.cpp \
	..//common/JSONRPCParserTest.cpp \
	..//common/JSONTest.cpp \
	..//common/MessageTest.cpp \
	..//common/MutexTest.cpp \
	..//common/NotificationTest.cpp \
	..//common/PropertiesTest.cpp \
	..//common/RandomTest.cpp \
	..//common/rpc/RPCMessageTest.cpp \
	..//common/rpc/RPCMethodTest.cpp \
	..//common/rpc/RPCTest.cpp \
	..//common/SemaphoreTest.cpp \
	..//common/StringTokenizerTest.cpp \
	..//common/ThreadTest.cpp \
	..//common/URLTest.cpp \
	..//common/VectorTest.cpp \
	..//core/AliasTest.cpp \
	..//core/ClientCoreTest.cpp \
	..//core/ClientTest.cpp \
	..//core/ClusterListTest.cpp \
	..//core/ClusterTest.cpp \
	..//core/ConsoleTest.cpp \
	..//core/LocalNodeTest.cpp \
	..//core/NodeFinderTest.cpp \
	..//core/NodeGraphTest.cpp \
	..//core/NodeListTest.cpp \
	..//core/NodeResponseTest.cpp \
	..//core/NodeReuestTest.cpp \
	..//core/NodeStatusTest.cpp \
	..//core/NodeTest.cpp \
	..//core/NodeTestController.cpp \
	..//core/RegistryTest.cpp \
	..//core/RemoteNodeTest.cpp \
	..//core/RouteTest.cpp \
	..//core/RQLTest.cpp \
	..//core/ScriptManagerTest.cpp \
	..//core/ScriptTest.cpp \
	..//core/ScriptTestController.cpp \
	..//core/ServerNodeTest.cpp \
	..//core/ServerTest.cpp \
	..//core/TriggerTest.cpp \
	..//RoundTestMain.cpp \
	..//script/JavaScriptTest.cpp \
	..//script/JavaTest.cpp \
	..//script/LuaTest.cpp

roundtest_LDADD = \
        ../../lib/unix/libround++.a \
	-lmupnp++ \
	-luhttp++ \
        @LUA_LIBS@ \
        @XML_LIBS@
