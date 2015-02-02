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
static const std::string ROUND_UNKNOWN_COMMAND_MSG = "Unrecognized command ";

static Round::Console::Client *gConsoleClient;

const char *prompt(EditLine *e) {
  return gConsoleClient->getPromptName();
}

bool exec_console_command(Round::Console::Client &client, const Round::Console::Input &input) {
  Round::Console::Message msg;
  Round::Error err;
  
  if (client.execConsoleCommand(input, &msg, &err)) {
    if (0 < msg.length()) {
      std::cout << msg << std::endl;
    }
    return true;
  }

  std::string errMsg = err.getDetailMessage();
  if (0 < errMsg.length()) {
    std::cerr << ROUND_CERR_PREFIX << errMsg << "'" << std::endl;
  }
  
  return false;
}

bool exec_rpc_command(Round::Console::Client &client, const Round::Console::Input &input) {
  Round::Console::Message msg;
  Round::Error err;
  
  if (client.execRPCCommand(input, &msg, &err)) {
    if (0 < msg.length()) {
      std::cout << msg << std::endl;
    }
    return true;
  }
  
  std::string errMsg = err.getDetailMessage();
  if (errMsg.length() <= 0) {
    errMsg = err.getMessage();
  }
  if (0 < errMsg.length()) {
    std::cerr << ROUND_CERR_PREFIX << errMsg << "'" << std::endl;
  }
  
  return false;
}

int main(int argc, char *argv[])
{
  Round::Error error;
  
  // Setup Client
  
  Round::Console::Client client;
  gConsoleClient = &client;
  client.setFirstArgument(argv[0]);

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
          client.usage();
          exit(EXIT_SUCCESS);
        }
    }
  }
  argc -= optind;
  argv += optind;
  
  // Check command
  
  if (argc <= 0) {
    client.usage();
    exit(EXIT_FAILURE);
  }

  std::string firstArg = argv[0];
  
  // Start Client
  
  if (!client.start(&error)) {
    exit(EXIT_FAILURE);
  }
  
  // Execute command
  
  if (!client.isShellCommand(firstArg)) {
    Round::Console::Input input;
    input.cmd = firstArg;
    for (int n=1; n<argc; n++) {
      input.params.addParam(argv[n]);
    }
    
    if (exec_console_command(client, input))
      exit(EXIT_SUCCESS);
    
    exit(EXIT_FAILURE);
  }
  
  // Boot Message
  
  std::string bootMessage;
  client.getBootMessage(bootMessage);
  std::cout << bootMessage << std::endl;
  
  // Initialize the EditLine
  
  EditLine *el = el_init(client.getProgramName(), stdin, stdout, stderr);
  el_set(el, EL_PROMPT, &prompt);
  el_set(el, EL_EDITOR, "vi");
  
  // Initialize the history
  
  HistEvent ev;
  History *inputHistory = history_init();
  history(inputHistory, &ev, H_SETSIZE, 1024);
  el_set(el, EL_HIST, history, inputHistory);

  Round::Console::Input input;
  
  while (true) {
    int readCount = 0;
    std::string inputLine = el_gets(el, &readCount);

    if (readCount <= 0)
        continue;

    if ((readCount == 1) && inputLine[0] == '\n')
        continue;

    boost::trim(inputLine);
    history(inputHistory, &ev, H_ENTER, inputLine.c_str());

    input.parse(inputLine);

    if (client.isQuitCommand(input))
      break;
    
    if (client.isRPCCommand(input)) {
      exec_rpc_command(client, input);
      continue;
    }
    
    if (!client.isConsoleCommand(input)) {
      std::cerr << ROUND_UNKNOWN_COMMAND_MSG << " '" << inputLine << "'" << std::endl;
      continue;
    }

    exec_console_command(client, input);
  }

  history_end(inputHistory);
  el_end(el);
  
  return EXIT_SUCCESS;
}
