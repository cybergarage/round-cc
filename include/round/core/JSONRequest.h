/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_JSONREQUEST_H_
#define _ROUNDCC_JSONREQUEST_H_

#include <uhttp/http/HTTPRequest.h>
#include <round/common/JSON.h>
#include <round/core/HTTP.h>

namespace Round {
class JSONRequest : public uHTTP::HTTPRequest {
 public:
  JSONRequest();
  virtual ~JSONRequest();

  bool setContent(const JSONObject *jsonObject);
  bool setContent(const JSONObject &jsonObject);
};

class TabletRecordHashKeyRange;

class JSONRequestDictionary : public JSONDictionary {
 public:
  JSONRequestDictionary();
  ~JSONRequestDictionary();
};

}

#endif
