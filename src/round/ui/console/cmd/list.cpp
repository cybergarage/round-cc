/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <iostream>
#include <round/core/Node.h>
#include <round/ui/console/Command.h>

const std::string Round::Console::list::NAME = "list";

const std::string Round::Console::list::getDescription() const {
  return "Showq found cluster nodes";
}

bool Round::Console::list::exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const {
  const ClusterList *clusters = client->getClusters();
  
  size_t clusterCnt = 0;
  for (ClusterList::const_iterator cluster = clusters->begin(); cluster != clusters->end(); cluster++) {
    
    std::cout << "[" << clusterCnt << "] " << (*cluster)->getName() << std::endl;
    
    const NodeGraph *nodeGraph = (*cluster)->getNodeGraph();
    size_t nodeCnt = 0;
    for (NodeGraph::const_iterator nodeIt = nodeGraph->begin(); nodeIt != nodeGraph->end(); nodeIt++) {
      ConsistentHashNode *cnode = *nodeIt;
      Node *node = dynamic_cast<Node *>(cnode);
      if (!node)
        continue;
      std::string hash;
      node->getHashCode(&hash);
      std::string host;
      if (!node->getRequestAddress(&host, err))
        return false;
      int port;
      if (!node->getRequestPort(&port, err))
        return false;
      std::cout << TAB << "[" << nodeCnt << "] " << host << ":" << port << /*" (" << hash << ")" <<*/ std::endl;
      nodeCnt++;
    }
    
    clusterCnt++;
  }
  return true;
}
