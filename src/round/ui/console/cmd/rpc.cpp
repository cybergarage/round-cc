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

#include <round/Round.h>
#include <round/ui/console/Command.h>

const std::string Round::Console::rpc::NAME = "method(<obj>, <params>)";
const std::string Round::Console::rpc::PARAM_BEGIN = "(";
const std::string Round::Console::rpc::PARAM_END = ")";
const std::string Round::Console::rpc::PARAM_SEP = ",";

const std::string Round::Console::rpc::getDescription() const {
  return "Execute RPC method";
}

const std::string Round::Console::rpc::getOptionDescription() const {
  return "";
}

bool Round::Console::rpc::exec(Round::Console::Client *client, const Input *input, Message *msg, Error *err) const {
  std::cout << "RPC : " << input->line << std::endl;
  
  size_t paramBeginIdx = input->line.find_first_of(PARAM_BEGIN);
  size_t paramSepIdx = std::string::npos;
  size_t paramEndIdx = std::string::npos;
  if (paramBeginIdx != std::string::npos) {
    paramSepIdx = input->line.find_first_of(PARAM_SEP, paramBeginIdx);
    if (paramSepIdx != std::string::npos) {
      paramEndIdx = input->line.find_first_of(PARAM_END, paramSepIdx);
    }
  }
  
  if (paramEndIdx == std::string::npos) {
    err->setMessage(input->line);
    return false;
  }

  std::string method = input->line.substr(0, paramBeginIdx);
  std::string object = input->line.substr((paramBeginIdx+1), (paramSepIdx - paramBeginIdx - 1));
  std::string params = input->line.substr((paramSepIdx+1), (paramEndIdx - paramSepIdx - 1));

  boost::trim(method);
  boost::trim(object);
  boost::trim(params);

  std::cout << "method : '" << method << "'" << std::endl;
  std::cout << "object : '" << object << "'" << std::endl;
  std::cout << "params : '" << params << "'" << std::endl;

  return true;
}
