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
#include <round/ui/console/Command.h>

const std::string Round::Console::list::NAME = "list";

bool Round::Console::list::exec(Round::Console::Client *client, const Params *params, Message *msg, Error *err) const {
  const ClusterList *clusters = client->getClusters();

  size_t clusterCnt = 0;
  for (ClusterList::const_iterator cluster = clusters->begin(); cluster != clusters->end(); cluster++) {
    std::string clusterName = (*cluster)->getName();
    std::cout << "[" << clusterCnt << "] " << clusterName << std::endl;
    clusterCnt++;
  }
  return true;
}

const std::string Round::Console::list::getDescription() const {
  return "Showq found cluster nodes";
}
