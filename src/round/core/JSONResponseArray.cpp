/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <iostream>
#include <round/core/HTTP.h>
#include <round/core/JSONResponse.h>
#include <round/core/RemoteNode.h>
#include <round/core/NodeGraph.h>

Round::JSONResponseArray::JSONResponseArray() {
}

Round::JSONResponseArray::~JSONResponseArray() {
}

bool Round::JSONResponseArray::setNodeGraphResponse(const NodeGraph *nodeGraph) {
for (NodeGraph::const_iterator content = nodeGraph->begin(); content != nodeGraph->end(); content++) {
    Node *node = static_cast<Node *>(*content);
    JSONDictionary *jsonDir = new JSONDictionary();
    jsonDir->set(HTTP::JSONParam::ADDR, node->getRequestAddress());
    jsonDir->set(HTTP::JSONParam::PORT, node->getRequestPort());
    add(jsonDir);
  }
  return true;
}

bool Round::JSONResponseArray::getNodeGraphResponse(NodeGraph *nodeGraph) {
for (JSONArray::const_iterator obj = begin(); obj != end(); obj++) {
    if (!(*obj)->isDictionary())
      continue;
    JSONDictionary *jsonDir = dynamic_cast<JSONDictionary *>(*obj);
    if (!jsonDir)
      continue;
    std::string addr;
    if (jsonDir->get(HTTP::JSONParam::ADDR, &addr))
      continue;
    int port;
    if (jsonDir->get(HTTP::JSONParam::PORT, &port))
      continue;
    RemoteNode *remoteNode = new RemoteNode(addr, port);
    nodeGraph->addNode(remoteNode);
  }

  return true;
}
