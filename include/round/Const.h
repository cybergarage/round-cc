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

namespace Round {

#define ROUNDCC_PRODUCT_NAME "round"
#define ROUNDCC_MODULE_NAME "round"
#define ROUNDCC_SYSTEM_TRIGGER_TIMER_PRECISION 0.1
#define ROUNDCC_ENDL "\n"
#define ROUNDCC_MD5_DIGEST_LENGTH 16
#define ROUNDCC_MD5_DIGEST_STRING_LENGTH 32
#define ROUNDCC_SHA_DIGEST_LENGTH 20
#define ROUNDCC_SHA_DIGEST_STRING_LENGTH 40
#define ROUNDCC_SHA256_DIGEST_LENGTH 32
#define ROUNDCC_SHA256_DIGEST_STRING_LENGTH 64
#define ROUNDCC_NODE_DIGEST_LENGTH 64
#define ROUNDCC_UPNP_DEVICE_TYPE "urn:cybergarage-org:device:round:1"
#define ROUNDCC_UPNP_SERVICE_TYPE "urn:cybergarage-org:service:round:1"
#define ROUNDCC_UPNP_ACTION_GETPRODUCTINFO "GetProductInfo"
#define ROUNDCC_UPNP_ACTION_GETCONNECTIONINFO "GetConnectionInfo"
#define ROUNDCC_RPC_HTTP_ENDPOINT "/rpc"
#define ROUNDCC_RPC_HTTP_CONTENT_TYPE "application/json-rpc"
#define ROUNDCC_RPC_HTTP_STATUS_CODE_OK 200 
#define ROUNDCC_RPC_HTTP_STATUS_CODE_MOVED_PERMANENTLY 301 
#define ROUNDCC_RPC_HTTP_STATUS_CODE_BAD_REQUEST 400 
#define ROUNDCC_RPC_HTTP_STATUS_CODE_NOT_FOUND 404 
#define ROUNDCC_RPC_HTTP_STATUS_CODE_NOT_ACCEPTABLE 406 
#define ROUNDCC_RPC_HTTP_STATUS_CODE_INTERNAL_SERVER_ERROR 500
#define ROUNDCC_NODE_STATUS_UNKNOWN 0
#define ROUNDCC_NODE_STATUS_STOP 1
#define ROUNDCC_NODE_STATUS_ACTIVATING 2
#define ROUNDCC_NODE_STATUS_ACTIVE 3
#define ROUNDCC_NODE_STATUS_TERMINATING 4
#define ROUNDCC_NODE_STATUS_PROMICE 5
#define ROUNDCC_ENCODING_NODE 0
#define ROUNDCC_ENCODING_BASE64 1
#define ROUNDCC_JSON_RPC_JSONRPC "jsonrpc"
#define ROUNDCC_JSON_RPC_METHOD "method"
#define ROUNDCC_JSON_RPC_PARAMS "params"
#define ROUNDCC_JSON_RPC_ID "id"
#define ROUNDCC_JSON_RPC_DEST "dest"
#define ROUNDCC_JSON_RPC_TS "ts"
#define ROUNDCC_JSON_RPC_RESULT "result"
#define ROUNDCC_JSON_RPC_ERROR "error"
#define ROUNDCC_JSON_RPC_CODE "code"
#define ROUNDCC_JSON_RPC_MESSAGE "message"
#define ROUNDCC_JSON_RPC_VERSION "2.0"
#define ROUNDCC_JSON_RPC_REQUEST_TIMEOUT_SEC 60
#define ROUNDCC_SYSTEM_METHOD_POST_JOB "post_job"
#define ROUNDCC_SYSTEM_METHOD_POST_METHOD "post_method"
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
#define ROUNDCC_SYSTEM_METHOD_PARAM_ID "id"
#define ROUNDCC_SYSTEM_METHOD_PARAM_NAME "name"
#define ROUNDCC_SYSTEM_METHOD_PARAM_LANGUAGE "lang"
#define ROUNDCC_SYSTEM_METHOD_PARAM_CODE "code"
#define ROUNDCC_SYSTEM_METHOD_PARAM_ENCODE "enc"
#define ROUNDCC_SYSTEM_METHOD_PARAM_BASE64 "base64"
#define ROUNDCC_SYSTEM_METHOD_PARAM_KEY "key"
#define ROUNDCC_SYSTEM_METHOD_PARAM_VALUE "val"
#define ROUNDCC_SYSTEM_METHOD_PARAM_TS "ts"
#define ROUNDCC_SYSTEM_METHOD_PARAM_LTS "lts"
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
#define ROUNDCC_SYSTEM_METHOD_PARAM_START_TIME "start_time"
#define ROUNDCC_SYSTEM_METHOD_PARAM_STOP_TIME "stop_time"
#define ROUNDCC_SYSTEM_METHOD_PARAM_DURATION "duration"
#define ROUNDCC_SYSTEM_METHOD_PARAM_LOOP "loop"
#define ROUNDCC_SYSTEM_METHOD_ADD_NODE_CMD "/usr/local/bin/roundd"
#define ROUNDCC_SYSTEM_METHOD_REMOVE_NODE_DELAY_MSEC 5000
#define ROUNDCC_SYSTEM_METHOD_DEST_ALL_NODE "*"
#define ROUNDCC_SYSTEM_METHOD_DEST_ANY_NODE "?"
#define ROUNDCC_SYSTEM_METHOD_DEST_LOCAL_NODE "."
#define ROUNDCC_SCRIPT_LANGUAGE_JS "js"
#define ROUNDCC_SCRIPT_LANGUAGE_RUBY "ruby"
#define ROUNDCC_SCRIPT_LANGUAGE_LUA "lua"
#define ROUNDCC_SCRIPT_LANGUAGE_PYTHON "python"
#define ROUNDCC_SCRIPT_LANGUAGE_JAVA "java"
#define ROUNDCC_SCRIPT_POST_METHOD "post_method"
#define ROUNDCC_SCRIPT_PRINT_METHOD "print"
#define ROUNDCC_SCRIPT_SEARCH_METHOD "search"
#define ROUNDCC_SCRIPT_SEARCH_METHOD_WAIT_MSEC 5000

#define ROUNDCC_RPC_ERROR_CODE_UNKNOWN 0
#define ROUNDCC_RPC_ERROR_CODE_PARSER_ERROR -32700
#define ROUNDCC_RPC_ERROR_CODE_INVALID_REQUEST -32600
#define ROUNDCC_RPC_ERROR_CODE_METHOD_NOT_FOUND -32601
#define ROUNDCC_RPC_ERROR_CODE_INVALID_PARAMS -32602
#define ROUNDCC_RPC_ERROR_CODE_INTERNAL_ERROR -32603
#define ROUNDCC_RPC_ERROR_CODE_BAD_DESTINATION -32000
#define ROUNDCC_RPC_ERROR_CODE_MOVED_PERMANENTLY -32001
#define ROUNDCC_RPC_ERROR_CODE_CONDITION_FAILED -32010
#define ROUNDCC_RPC_ERROR_CODE_SCRIPT_ENGINE_INTERNAL_ERROR -32020
#define ROUNDCC_RPC_ERROR_CODE_SCRIPT_ENGINE_NOT_FOUND -32021
#define ROUNDCC_RPC_ERROR_CODE_SCRIPT_COMPILE_ERROR -32022
#define ROUNDCC_RPC_ERROR_CODE_SCRIPT_RUNTIME_ERROR -32023
#define ROUNDCC_RPC_ERROR_CODE_SERVER_ERROR_MAX -32000
#define ROUNDCC_RPC_ERROR_CODE_SERVER_ERROR_MIN -32099

#define ROUNDCC_RPC_ERROR_CODE_UNKNOWN_MSG  "Unknown Error"
#define ROUNDCC_RPC_ERROR_CODE_PARSER_ERROR_MSG  "Parse error"
#define ROUNDCC_RPC_ERROR_CODE_INVALID_REQUEST_MSG  "Invalid Request"
#define ROUNDCC_RPC_ERROR_CODE_METHOD_NOT_FOUND_MSG  "Method not found"
#define ROUNDCC_RPC_ERROR_CODE_INVALID_PARAMS_MSG  "Invalid params"
#define ROUNDCC_RPC_ERROR_CODE_INTERNAL_ERROR_MSG  "Internal error"
#define ROUNDCC_RPC_ERROR_CODE_BAD_DESTINATION_MSG  "Bad Destination"
#define ROUNDCC_RPC_ERROR_CODE_MOVED_PERMANENTLY_MSG  "Moved Permanently"
#define ROUNDCC_RPC_ERROR_CODE_CONDITION_FAILED_MSG  "Condition Failed"
#define ROUNDCC_RPC_ERROR_CODE_SCRIPT_ENGINE_INTERNAL_ERROR_MSG  "Script Engine Internal Error"
#define ROUNDCC_RPC_ERROR_CODE_SCRIPT_ENGINE_NOT_FOUND_MSG  "Script Engine Not Found"
#define ROUNDCC_RPC_ERROR_CODE_SCRIPT_COMPILE_ERROR_MSG  "Script Compile Error"
#define ROUNDCC_RPC_ERROR_CODE_SCRIPT_RUNTIME_ERROR_MSG  "Script Runtime Error"
#define ROUNDCC_MESSAGE_SEARCHING "Searching"
#define ROUNDCC_MESSAGE_DONE "Done"

}

#endif
