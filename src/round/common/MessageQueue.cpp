/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <string.h>
#include <unistd.h>
#include <sys/msg.h>

#include <round/common/Message.h>

Round::MessageQueue::MessageQueue() {
}

Round::MessageQueue::~MessageQueue() {
}

bool Round::MessageQueue::pushMessage(const Message *message) {
  if (!message)
    return false;
  
  std::string jsonString;
  message->toJSONString(&jsonString);
  if (jsonString.length() <= 0)
    return false;
  
  this->mutex.lock();
  push(jsonString);
  this->mutex.unlock();

  return true;
}

bool Round::MessageQueue::popMessage(Message *message) {
  if (!message)
    return false;
  
  if (empty())
    return false;

  this->mutex.lock();
  
  std::string jsonString = front();
  pop();
  
  this->mutex.unlock();
  
  Round::JSONParser jsonParser;
  if (jsonParser.parse(jsonString) == false)
    return false;
   
  Round::JSONObject *jsonObject = jsonParser.getObject();
  if (jsonObject->isDictionary() == false)
    return false;
   
  message->set(static_cast<Round::JSONDictionary *>(jsonObject));

  return true;
}
