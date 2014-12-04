/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_HTTP_H_
#define _ROUNDCC_HTTP_H_

#include <string>
#include <round/common/JSON.h>

namespace Round {
  
namespace HTTP {
const char POST[] = "POST";
const char GET[] = "GET";
const char PUT[] = "PUT";
const char DELETE[] = "DELETE";

const char DELIM[] = "/";

const char MIMETYPE_JSON[] = "application/json";

namespace URI {
const char VER[] = "/";
const char CLUSTER[] = "/";
const char NAME[] = "/";
const char DOCUMENT[] = "/doc/";

const char CONFIG[] = "/conf/";

const char STATUS[] = "/stats/";
const char STATUS_NODE[] = "/stats/node";
const char STATUS_NODEGRAPH[] = "/stats/nodegraph";
const char STATUS_DOCUMENTS[] = "/stats/docs";

const char SYSTEM[] = "/sys/";

}

}

}

#endif
