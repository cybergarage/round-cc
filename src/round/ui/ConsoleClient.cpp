/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/algorithm/string.hpp>
#include <vector>
#include <string>

#include <round/ui/ConsoleClient.h>

const std::string Round::ConsoleClient::QUIT = "quit";
const std::string Round::ConsoleClient::EXIT = "exit";
const std::string Round::ConsoleClient::SHOW = "show";
const std::string Round::ConsoleClient::SEARCH = "search";
const std::string Round::ConsoleClient::USE = "use";
const std::string Round::ConsoleClient::CLUSTERS = "clusters";
const std::string Round::ConsoleClient::NODES = "nodes";

Round::ConsoleClient::ConsoleClient() {
}

Round::ConsoleClient::~ConsoleClient() {
}

void Round::ConsoleClient::setProgramNameFromArgument(const std::string &argValue)
{
  this->promptName = argValue;
  size_t lastPathIndex = this->promptName.find_last_of("/");
  if (lastPathIndex != std::string::npos)
    this->promptName = this->promptName.substr((lastPathIndex + 1));
  this->promptName = this->promptName;
  this->promptName.append("> ");
}

struct fractalcc_tocapital {
  bool isFirstChar;
  fractalcc_tocapital(){
    isFirstChar = true;
  }
  int operator()(int c) {
    if (isFirstChar) {
      isFirstChar = false;
      return toupper(c);
    }
    return tolower(c);
  }
};

const char *Round::ConsoleClient::getBootMessage(std::string &buffer)
{
  std::stringstream bootMsg;
  //bootMsg << FRACTALCC_PRODUCT_NAME << " " << FRACTALCC_VERSION;
  buffer = bootMsg.str();

  std::transform(buffer.begin(), buffer.end(), buffer.begin(), fractalcc_tocapital());

  return buffer.c_str();
}

const char *Round::ConsoleClient::getProgramName()
{
  return promptName.c_str();
}

const char *Round::ConsoleClient::getPromptName()
{
  return promptName.c_str();
}

bool Round::ConsoleClient::isCommand(const std::string &command, const std::string &inputLine) {
  size_t lastExtraIndex = inputLine.find_last_not_of(" \n");
  std::string lowerInputLine = (lastExtraIndex == std::string::npos) ? inputLine : (std::string(inputLine, 0, (lastExtraIndex + 1)));
  std::transform(lowerInputLine.begin(), lowerInputLine.end(), lowerInputLine.begin(), ::tolower);
  return (lowerInputLine.find_first_of(command) == 0) ? true : false;
}

bool Round::ConsoleClient::isQuitCommand(const std::string &inputLine) {
  if (isCommand(QUIT, inputLine))
    return true;
  return isCommand(EXIT, inputLine);
}

bool Round::ConsoleClient::isQueryCommand(const std::string &inputLine) {
  return !isConsoleCommand(inputLine);
}

bool Round::ConsoleClient::show(const std::vector<std::string> &commands, Error *error) {
  if (commands.size() < 2) {
    /*
    Cluster *targetCluster = getTargetCluster();
    ClusterList *clusters = getClusters();
    for (ClusterList::iterator cluster = clusters->begin(); cluster != clusters->end(); cluster++) {
      std::string prefix = "  ";
      if (targetCluster) {
        if (targetCluster->equals(*cluster))
          prefix = "* ";
      }
      std::cout << prefix << (*cluster)->getName() << std::endl;
      
      NodeGraph *nodeGraph = (*cluster)->getNodeGraph();
      size_t nodeCount = nodeGraph->size();
      for (size_t n=0; n<nodeCount; n++) {
        Node *node = nodeGraph->getNode(n);
        std::cout << "  [" << (n+1) << "] " << node->getRequestAddress() << ":" << node->getRequestPort() << std::endl;
      }
    }
     */
    return true;
  }
  
  std::string target = commands[1];
  
  if (target.compare(CLUSTERS) == 0) {
    /*
    Cluster *targetCluster = getTargetCluster();
    ClusterList *clusters = getClusters();
    for (ClusterList::iterator cluster = clusters->begin(); cluster != clusters->end(); cluster++) {
      std::string prefix = "  ";
      if (targetCluster) {
        if (targetCluster->equals(*cluster))
          prefix = "* ";
      }
      std::cout << prefix << (*cluster)->getName() << std::endl;
    }
    return true;
  }
  else if (target.compare(NODES) == 0) {
    Cluster *targetCluster = getTargetCluster();
    if (targetCluster) {
      NodeGraph *nodeGraph = targetCluster->getNodeGraph();
      size_t nodeCount = nodeGraph->size();
      for (size_t n=0; n<nodeCount; n++) {
        Node *node = nodeGraph->getNode(n);
        std::cout << "[" << (n+1) << "] " << node->getRequestAddress() << ":" << node->getRequestPort() << std::endl;
      }
    }
    return true;
     */
  }
  
  return false;
}

bool Round::ConsoleClient::use(const std::vector<std::string> &commands, Error *error) {
  /*
  if (commands.size() < 2) {
    error->setCode(ConsoleClientErrorClusterNotFound);
  }
    return false;
  
  std::string target = commands[1];
  
  if (!setTargetCluster(target)) {
    error->setCode(ConsoleClientErrorClusterNotFound);
  }
   */
  
  
  
  return false;
}

bool Round::ConsoleClient::exec(const std::string &command, Error *error) {
  std::string lowerCommand = command;
  std::transform(lowerCommand.begin(), lowerCommand.end(), lowerCommand.begin(), ::tolower);
  std::vector<std::string> commands;
  boost::algorithm::split(commands, command, boost::is_any_of(" "));

  if (commands.size() <= 0) {
    //error->setCode(ConsoleClientErrorOperationFailed);
    return false;
  }
  
  std::string operationCommand = commands[0];

  if (isShowCommand(operationCommand)) {
    return show(commands, error);
  }
  
  if (isUseCommand(operationCommand)) {
    return use(commands, error);
  }
  
  if (isSearchCommand(operationCommand)) {
    return Client::search(error);
  }
  
  //error->setCode(ConsoleClientErrorOperationFailed);
  
  return false;
}
