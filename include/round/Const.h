/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_CONST_H_
#define _ROUNDCC_CONST_H_

#define ROUNDCC_RPC_HTTP_ENDPOINT "/rpc"
#define ROUNDCC_RPC_HTTP_CONTENT_TYPE "application/json"
#define ROUNDCC_NODE_STATUS_UNKNOWN 0
#define ROUNDCC_NODE_STATUS_STOP 1
#define ROUNDCC_NODE_STATUS_ACTIVATING 2
#define ROUNDCC_NODE_STATUS_ACTIVE 3
#define ROUNDCC_NODE_STATUS_TERMINATING 4
#define ROUNDCC_NODE_STATUS_PROMICE 5
#define ROUNDCC_SYSTEM_METHOD_POST_JOB "post_job"
#define ROUNDCC_SYSTEM_METHOD_SET_METHOD "set_method"
#define ROUNDCC_SYSTEM_METHOD_SET_ALIAS "set_alias"
#define ROUNDCC_SYSTEM_METHOD_SET_ROUTE "set_route"
#define ROUNDCC_SYSTEM_METHOD_SET_TIMER "set_timer"
#define ROUNDCC_SYSTEM_METHOD_ADD_NODE "add_node"
#define ROUNDCC_SYSTEM_METHOD_REMOVE_METHOD "remove_method"
#define ROUNDCC_SYSTEM_METHOD_REMOVE_ALIAS "remove_alias"
#define ROUNDCC_SYSTEM_METHOD_REMOVE_ROUTE "remove_route"
#define ROUNDCC_SYSTEM_METHOD_REMOVE_TIMER "remove_timer"
#define ROUNDCC_SYSTEM_METHOD_REMOVE_NODE "remove_node"
#define ROUNDCC_SYSTEM_METHOD_ECHO "_echo"
#define ROUNDCC_SYSTEM_METHOD_GET_NETWORK_STATE "get_network_state"
#define ROUNDCC_SYSTEM_METHOD_GET_CLUSTER_STATE "get_cluster_state"
#define ROUNDCC_SYSTEM_METHOD_SET_REGISTRY "set_registry"
#define ROUNDCC_SYSTEM_METHOD_GET_REGISTRY "get_registry"
#define ROUNDCC_SYSTEM_METHOD_REMOVE_REGISTRY "remove_registry"
#define ROUNDCC_SYSTEM_METHOD_GET_NODE_STATE "get_node_state"
#define ROUNDCC_SYSTEM_METHOD_GET_NODE_CONFIG "get_node_config"
#define ROUNDCC_SYSTEM_METHOD_PARAM_NAME "name"
#define ROUNDCC_SYSTEM_METHOD_PARAM_LANGUAGE "language"
#define ROUNDCC_SYSTEM_METHOD_PARAM_CODE "code"
#define ROUNDCC_SYSTEM_METHOD_PARAM_ENCODE "encode"
#define ROUNDCC_SYSTEM_METHOD_PARAM_BASE64 "base64"
#define ROUNDCC_SYSTEM_METHOD_PARAM_SRC "src"
#define ROUNDCC_SYSTEM_METHOD_PARAM_DEST "dest"
#define ROUNDCC_SYSTEM_METHOD_PARAM_TYPE "type"
#define ROUNDCC_SYSTEM_METHOD_PARAM_COND "cond"
#define ROUNDCC_SYSTEM_METHOD_PARAM_ADDR "addr"
#define ROUNDCC_SYSTEM_METHOD_PARAM_PORT "port"
#define ROUNDCC_SYSTEM_METHOD_PARAM_HASH "hash"
#define ROUNDCC_SYSTEM_METHOD_PARAM_VERSION "version"
#define ROUNDCC_SYSTEM_METHOD_PARAM_NODES "nodes"
#define ROUNDCC_SYSTEM_METHOD_PARAM_CLUSTER "cluster"
#define ROUNDCC_SYSTEM_METHOD_PARAM_CLUSTERS "clusters"
#define ROUNDCC_SYSTEM_METHOD_PARAM_STATE "state"
#define ROUNDCC_SYSTEM_METHOD_PARAM_METHOD "method"
#define ROUNDCC_SYSTEM_METHOD_PARAM_DEFAULTS "defaults"
#define ROUNDCC_SYSTEM_METHOD_ADD_NODE_CMD "/usr/local/bin/roundd"
#define ROUNDCC_SYSTEM_METHOD_REMOVE_NODE_DELAY_MSEC 5000
#define ROUNDCC_SYSTEM_METHOD_DEST_ALL_NODE "*"
#define ROUNDCC_SYSTEM_METHOD_DEST_ONE_NODE "?"
#define ROUNDCC_SCRIPT_POST_METHOD "post_method"
#define ROUNDCC_SCRIPT_PRINT_METHOD "print"
#define ROUNDCC_SCRIPT_SEARCH_METHOD "search"
#define ROUNDCC_SCRIPT_SEARCH_METHOD_WAIT_MSEC 5000
#define ROUNDCC_MESSAGE_SEARCHING "Searching"
#define ROUNDCC_MESSAGE_DONE "Done"

#endif
