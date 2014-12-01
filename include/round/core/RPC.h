/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDCC_RPC_H_
#define _ROUNDCC_RPC_H_

#include <string>
#include <map>

#include <round/common/Error.h>

namespace Round {

namespace RPC {

namespace JSON {

enum {
  DetailStatusParserError          = -32700,
  DetailStatusInvalidRequest       = -32600,
  DetailStatusMethodNotFound       = -32601,
  DetailStatusInvalidParams        = -32602,
  DetailStatusInternalError        = -32603,
  DetailStatusSpecificErrorMax     = -32000,
  DetailStatusSpecificErrorMin     = -32099,
};

namespace HTTP {
  int JSONDetailStatus2HTTPStatus(int jsonDetailStatus);
}

}
  
}
  
}

#endif
