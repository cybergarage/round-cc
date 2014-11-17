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

namespace JSONParam {
  
const char ID[] = "id";
const char STATUS[] = "status";
const char VER[] = "version";
const char NAME[] = "name";
const char CLUSTER[] = "cluster";
const char ADDR[] = "addr";
const char PORT[] = "port";
const char KEY[] = "id";
const char BEGIN_INDEX[] = "beginIndex";
const char END_INDEX[] = "endIndex";
const char OFFSET[] = "offset";
const char LIMIT[] = "limit";
const char COUNT[] = "count";

const char REPLICA[] = "_replica";
const char KEYONLY[] = "_idOnly";

inline bool IsOptionParameter(const std::string &param) {
  return (param.find_first_of("_") == 0)? true : false;
}

inline bool IsDataParameter(const std::string &param)  {
  return !IsOptionParameter(param);
}

}

}

}

#endif
