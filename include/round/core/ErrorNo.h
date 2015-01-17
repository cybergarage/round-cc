/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_ERRORNO_H_
#define _ROUNDCC_ERRORNO_H_

#include <round/common/Error.h>

namespace Round {

enum TabletErrors {
TabletErrorOperationFailed = -1001,
};

enum NodeErrors {
NodeErrorOperationFailed = TabletErrorOperationFailed,
NodeErrorCannotFindTablet = -2001,
NodeErrorReplicationFailed = -2002,
NodeErrorConfigurationFailure = -2003,
};

enum ClientErrors {
ClientErrorOperationFailed = NodeErrorOperationFailed,
ClientErrorReplicationFailed = NodeErrorReplicationFailed,
ClientErrorCannotFindNode = -3001,
};

enum CosoleClientErrors {
ConsoleClientErrorOperationFailed = NodeErrorOperationFailed,
ConsoleClientErrorShowTargetNotFound = -3101,
ConsoleClientErrorClusterNotFound = -3102,
};

enum ServerErrors {
ServerErrorCannotStartControlPoint = -4001,
ServerErrorCannotStartDevice = -4002,
ServerErrorCannotSearchDevice= -4003,
};

  
}

#endif
