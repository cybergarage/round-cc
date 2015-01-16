/*****************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2012
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string>
#include <iostream>
#include <map>

#include <boost/algorithm/string.hpp>  

#include <stdlib.h>
#include <unistd.h>
#include <histedit.h>

#include <round/Round.h>
#include <round/ui/Console.h>

static const std::string ROUND_CERR_PREFIX = "Error : ";

namespace Roundd {
  typedef std::map<std::string,std::string> Commands;
  typedef std::map<std::string,std::string> Options;
}

static Round::Console::Client *gConsoleClient;

const char *prompt(EditLine *e) {
  return gConsoleClient->getPromptName();
}

void usage() {
  std::cout << "Usage: " << gConsoleClient->getProgramName() << " [-options] <command>" << std::endl;
  
  Roundd::Commands commands;
  commands["?"]                = "Prints this help message";
  commands["h <host address>"] = "Host address of a node in a cluster";
  commands["p <port number>"]  = "Port number of a node in a cluster";
  for (Roundd::Commands::iterator cmd=commands.begin(); cmd != commands.end(); cmd++) {
    std::string optionParam = cmd->first;
    std::string optionDesc = cmd->second;
    std::cout << "\t-" << optionParam << "\t\t" << optionDesc << std::endl;
  }
  
  Roundd::Options options;
  options["?"]                = "Prints this help message";
  options["h <host address>"] = "Host address of a node in a cluster";
  options["p <port number>"]  = "Port number of a node in a cluster";
  for (Roundd::Options::iterator option=options.begin(); option != options.end(); option++) {
    std::string optionParam = option->first;
    std::string optionDesc = option->second;
    std::cout << "\t-" << optionParam << "\t\t" << optionDesc << std::endl;
  }
}

int main(int argc, char *argv[])
{
  Round::Error error;
  
  // Setup Client
  
  gConsoleClient = new Round::Console::Client();
  if (!gConsoleClient) {
    std::cerr << ROUND_CERR_PREFIX << ROUNDCC_PRODUCT_NAME << " couldn't start" << std::endl;
    return EXIT_FAILURE;
  }
    
  gConsoleClient->setProgramNameFromArgument(argv[0]);

  // Boot Message
  
  std::string bootMessage;
  gConsoleClient->getBootMessage(bootMessage);
  std::cout << bootMessage << std::endl;

  // Parse command line options
  
  std::string nodeHost;
  int nodePort = 0;
  
  int ch;
  while ((ch = getopt(argc, argv, "h:p:?")) != -1) {
    switch (ch) {
      case 'h':
        {
          nodeHost = optarg;
        }
        break;
      case 'p':
        {
          nodePort = atoi(optarg);
        }
        break;
      case '?':
      default:
        {
          usage();
          exit(EXIT_SUCCESS);
        }
    }
  }
  argc -= optind;
  argv += optind;
  
  // Setup Client
  
  bool hasNodeParameters = false;
  if ((0 < nodeHost.length()) && (0 < nodePort)) {
    hasNodeParameters = true;
  }

  if (hasNodeParameters) {
    gConsoleClient->setFinderEnabled(false);

    /*
    Round::RemoteNode remoteNode(nodeHost, nodePort);
    Round::Cluster remoteCluster;
    Round::NodeGraph remoteNodeGraph;

    // Target Cluster
    if (!remoteNode.getCluster(&remoteCluster, &error)) {
      OutputRemoteNodeError(remoteNode);
      exit(EXIT_FAILURE);
    }
    std::string remoteClusterName = remoteCluster.getName();
    if (!gConsoleClient->addCluster(remoteClusterName)) {
      OutputRemoteNodeError(remoteNode);
      exit(EXIT_FAILURE);
    }
    if (!gConsoleClient->setTargetCluster(remoteClusterName)) {
      OutputRemoteNodeError(remoteNode);
      exit(EXIT_FAILURE);
    }
    
    // Target Node Graph
    Round::Cluster *targetCluster = gConsoleClient->getTargetCluster();
    if (!targetCluster) {
      OutputRemoteNodeError(remoteNode);
      exit(EXIT_FAILURE);
    }
    Round::NodeGraph *targetNodeGraph = targetCluster->getNodeGraph();
    if (!targetNodeGraph) {
      OutputRemoteNodeError(remoteNode);
      exit(EXIT_FAILURE);
    }
    if (!remoteNode.getNodeGraph(&remoteNodeGraph, &error)) {
      OutputRemoteNodeError(remoteNode);
      exit(EXIT_FAILURE);
    }
    if (!targetNodeGraph->set(remoteNodeGraph)) {
      OutputRemoteNodeError(remoteNode);
      exit(EXIT_FAILURE);
    }
     */
  }
  else {
    gConsoleClient->setFinderEnabled(true);
  }
  
  if (!gConsoleClient->start(&error)) {
    std::cout << "Couldn't start client" << std::endl;
    exit(EXIT_FAILURE);
  }
  
  // Initialize the EditLine
  
  EditLine *el = el_init(gConsoleClient->getProgramName(), stdin, stdout, stderr);
  el_set(el, EL_PROMPT, &prompt);
  el_set(el, EL_EDITOR, "vi");
  
  // Initialize the history
  
  HistEvent ev;
  History *inputHistory = history_init();
  history(inputHistory, &ev, H_SETSIZE, 1024);
  el_set(el, EL_HIST, history, inputHistory);

  while (true) {
    int readCount = 0;
    const char *inputLine = el_gets(el, &readCount);

    if (readCount <= 0)
        continue;
    if ((readCount == 1) && inputLine[0] == '\n')
        continue;

    history(inputHistory, &ev, H_ENTER, inputLine);

    std::string inputCommand = inputLine;
    boost::trim(inputCommand);

    Round::Error error;

    if (gConsoleClient->isConsoleCommand(inputCommand)) {
      std::cerr << "Unrecognized command '" << inputCommand << "'" << std::endl;
      continue;
    }

    if (gConsoleClient->isConsoleQuitCommand(inputCommand))
        break;

    Round::Console::Message msg;
    Round::Error err;
    if (gConsoleClient->execConsoleCommand(inputCommand, &msg, &err)) {
      if (0 < msg.length()) {
        std::cout << msg << std::endl;
      }
    }
    else {
      std::cerr << ROUND_CERR_PREFIX << err.getMessage() << "'" << std::endl;
    }
  }

  history_end(inputHistory);
  el_end(el);

  delete gConsoleClient;
    
  return EXIT_SUCCESS;
}
