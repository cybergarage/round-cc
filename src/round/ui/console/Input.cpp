/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/algorithm/string.hpp>
#include <round/ui/Console.h>

Round::Console::Input::Input() {
}

Round::Console::Input::Input(const std::string &inputLine) {
  parse(inputLine);
}

bool Round::Console::Input::parse(const std::string &inputLine) {
  clear();
  
  size_t lastExtraIndex = inputLine.find_last_not_of(" \n");
  std::string lowerInputLine = (lastExtraIndex == std::string::npos) ? inputLine : (std::string(inputLine, 0, (lastExtraIndex + 1)));
  std::transform(lowerInputLine.begin(), lowerInputLine.end(), lowerInputLine.begin(), ::tolower);
  
  typedef std::vector<std::string> Inputs;
  Inputs inputs;
  boost::algorithm::split(inputs, lowerInputLine, boost::is_space());

  Inputs::iterator inputIt = inputs.begin();
  if (inputIt == inputs.end())
    return true;
  this->cmd = *inputIt;
  
  inputIt++;
  while (inputIt != inputs.end()) {
    if ((*inputIt).length() <= 0) {
      inputIt++;
      continue;
    }
    this->params.addParam(*inputIt);
    inputIt++;
  }
  
  return true;
}

void Round::Console::Input::clear() {
  this->line = "";
  this->cmd = "";
  this->params.clear();
}
