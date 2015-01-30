/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <string>
#include <map>
#include <iostream>

#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <histedit.h>
#include <signal.h>

#include <round/Round.h>

typedef std::map<std::string,std::string> RounddOptionsDictionary;

void usage(char *argv[]) {
  std::string programName = argv[0];
  size_t lastPathIndex = programName.find_last_of("/");
  if (lastPathIndex != std::string::npos)
    programName = programName.substr((lastPathIndex + 1));
  
  std::cout << "Usage: " << programName << " [-options]" << std::endl;
  
  RounddOptionsDictionary options;

  options["f"] = "Runs in foreground mode";
  options["v"] = "Enables verbose output";
  options["h"] = "Prints this help message";
  options["p <port number>"] = "Runs HTTP server on given port";
  options["c <filename>"] = "Specifies a configuration file";
  
  for (RounddOptionsDictionary::iterator option=options.begin(); option != options.end(); option++) {
    std::string optionParam = option->first;
    std::string optionDesc = option->second;
    std::cout << "\t-" << optionParam << "\t\t" << optionDesc << std::endl;
  }
}

int main(int argc, char *argv[]) {
  std::string configFilename = "";
  bool deamonMode = true;
  bool verboseMode = false;
  bool hasPortParameter = false;
  int httpdPort = 0;//Round::Server::DEFAULT_HTTPD_PORT;

  int ch;
  while ((ch = getopt(argc, argv, "fhvp:c:")) != -1) {
    switch (ch) {
    case 'v':
      {
        verboseMode = true;
      }
      break;
    case 'f':
      {
        deamonMode = false;
      }
      break;
    case 'p':
      {
        hasPortParameter = true;
        httpdPort = atoi(optarg);
      }
      break;
    case 'c':
      {
        configFilename = optarg;
      }
      break;
    case 'h':
    case '?':
    default:
      {
        usage(argv);
        exit(EXIT_SUCCESS);
      }
    }
   }
  argc -= optind;
  argv += optind;

  if (deamonMode) {
    int pid = fork();
    if (pid < 0)
      exit(EXIT_FAILURE);
  
    if (0 < pid)
      exit(EXIT_SUCCESS);
 
    if (setsid() < 0)
      exit(EXIT_FAILURE);

    if ( chdir("/") < 0 ) {
      exit(EXIT_FAILURE);
    }
    
    umask(0);
  
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
  }
 
  Round::Error err;
  Round::Server *nodeServer = new Round::Server();
  
  if (0 < configFilename.length()) {
    if (nodeServer->loadConfigFromString(configFilename, &err))
      exit(EXIT_FAILURE);
  }

    /*
  if (hasPortParameter)
    nodeServer->setHttpdPort(httpdPort);
*/
    
  Round::Logger *nodeServerLogger = nodeServer->getLogger();
  nodeServerLogger->setLevel((verboseMode ? Round::LoggerLevel::TRACE : Round::LoggerLevel::INFO));

  if (deamonMode) {
    std::string logFilename;
    if (nodeServer->getLogFilename(&logFilename, &err)) {
      Round::LoggerFileTarget *fileTarget = new Round::LoggerStdFileTarget();
      if (fileTarget->open(logFilename)) {
        nodeServerLogger->addTarget(fileTarget);
      }
      else
        delete fileTarget;
    }
  }
  else {
    nodeServerLogger->addTarget(new Round::LoggerStdoutTarget());
    nodeServerLogger->addTarget(new Round::LoggerStderrTarget());
  }


  //RoundLogInfo("Starting fractald ..... ");

  if (nodeServer->start(&err) == false) {
    //Round::RoundLog(err);
    exit(EXIT_FAILURE);
  }
  
  RoundLogInfo("Done");

  sigset_t sigSet;
  if (sigfillset(&sigSet) != 0)
    exit(EXIT_FAILURE);

  bool isRunnging = true;
  
  while (isRunnging) {
    int sigNo;
    if (sigwait(&sigSet, &sigNo) != 0)
      break;
    switch (sigNo) {
    case SIGTERM:
    case SIGINT:
    case SIGKILL:
      {
        nodeServer->stop(&err);
        isRunnging = false;
      }
      break;
    case SIGHUP:
      {
        if (nodeServer->start(&err) == false) {
          Round::RoundLog(err);
          exit(EXIT_FAILURE);
        }
      }
      break;
    }
  }
    
  delete nodeServer;
  
  return EXIT_SUCCESS;
}
