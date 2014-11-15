/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_JSONRESPONSE_H_
#define _ROUNDCC_JSONRESPONSE_H_

#include <uhttp/http/HTTPResponse.h>
#include <round/common/Dictionary.h>
#include <round/common/JSON.h>
#include <round/core/NodeStatus.h>

namespace Round {
class NodeGraph;
class TabletRecordList;
class TabletSpaceList;

class JSONResponseDictionary : public JSONDictionary {
 public:
  JSONResponseDictionary();
  ~JSONResponseDictionary();

  bool setGetResponse(const std::string &value);
  bool setNodeStatusResponse(const NodeStatus &nodeStatus);

  bool getGetResponse(std::string *value);
  bool getNodeStatusResponse(NodeStatus *nodeStatus);
};

class JSONResponseArray : public JSONArray {
 public:
  JSONResponseArray();
  ~JSONResponseArray();

  bool setNodeGraphResponse(const NodeGraph *nodeGraph);
  bool getNodeGraphResponse(NodeGraph *nodeGraph);
};

class JSONResponseParser : public JSONParser {
public:
  
  JSONResponseParser() {
  }

  JSONArray *createJSONArray() {
    return new JSONResponseArray();
  }

  JSONDictionary *createJSONDictionary() {
    return new JSONResponseDictionary();
  }
};

class JSONResponse : public uHTTP::HTTPResponse {
 public:
  JSONResponse();
  virtual ~JSONResponse();

  void setContent(const JSONObject &jsonObject);
  bool getJSONObject(JSONObject **jsonObject);
};

}

#endif
