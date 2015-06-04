/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <string.h>
#include <sstream>

#include <round/core/local/method/SystemMethod.h>
#include <round/core/Trigger.h>

const std::string Round::set_timer::NAME   = ROUNDCC_SYSTEM_METHOD_SET_TIMER;
const std::string Round::set_timer::TIMER_NAME = ROUNDCC_SYSTEM_METHOD_PARAM_NAME;
const std::string Round::set_timer::TIMER_DURATION = ROUNDCC_SYSTEM_METHOD_PARAM_DURATION;
const std::string Round::set_timer::TIMER_LOOP = ROUNDCC_SYSTEM_METHOD_PARAM_LOOP;

Round::set_timer::set_timer() : system_method(NAME) {
}

Round::set_timer::~set_timer() {
}

bool Round::set_timer::exec(LocalNode *node, const NodeRequest *nodeReq, NodeResponse *nodeRes) const {
  std::string params;
  if (!nodeReq->getParams(&params))
    return false;
  
  JSONParser jsonParser;
  Error error;
  if (!jsonParser.parse(params, &error))
    return false;
  
  JSONDictionary *paramDict = dynamic_cast<JSONDictionary *>(jsonParser.getRootObject());
  if (!paramDict)
    return false;
  
  // Essential Parameters
  
  std::string name;
  if (!paramDict->get(TIMER_NAME, &name))
    return false;
  
  double duration;
  if (!paramDict->get(TIMER_DURATION, &duration))
    return false;
  
  if ((name.length() <= 0))
    return false;
  
  // Optional Parameters
  
  bool loop = false;
  if (paramDict->hasKey(TIMER_LOOP)) {
    paramDict->get(TIMER_LOOP, &loop);
  }
  
  TimerTrigger *timer = new TimerTrigger();
  if (!timer)
    return false;
  
  timer->setDuration(duration);
  timer->setLoop(loop);

  if (!node->setTrigger(timer)) {
    delete timer;
    return false;
  }
  
  return true;
}
