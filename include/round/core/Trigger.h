/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_TRIGGER_H_
#define _ROUNDCC_TRIGGER_H_

#include <string>
#include <map>

#include <round/common/Vector.h>

namespace Round {

  
class Trigger {
  
public:
  Trigger();
  Trigger(const std::string &name, const std::string &obj, const std::string &defaults);
  
  virtual ~Trigger();

  bool isValid();
  
  // Name
  
  bool setName(const std::string &value);
  bool getName(std::string *value) const;
  bool isName(const std::string &value) const;
  
  // Object
  
  bool setObject(const std::string &value);
  bool getObject(std::string *value) const;

  // Default parameters
  
  bool setDefaults(const std::string &value);
  bool getDefaults(std::string *value) const;

  bool equals(const Trigger *otherTrigger) const;
  
private:
  
  std::string  name;
  std::string  object;
  std::string  defaults;
};

class TriggerMap : public std::map<std::string, Trigger *> {
  
public:
  
  TriggerMap();
  ~TriggerMap();
  
  bool hasTrigger(const std::string &name) const;
  Trigger *findTrigger(const std::string &name) const ;
  bool getSourceObjects(const std::string &name, std::string *object) const ;
  
  bool addTrigger(Trigger *alias);
  bool setTrigger(Trigger *alias);
  bool removeTriggerByName(const std::string &name);
  
  
  void clear();
};

class TriggerManager : public TriggerMap {
    
 public:
  
  TriggerManager();
  virtual ~TriggerManager();

  void lock() {
    mutex.lock();
  }
  
  void unlock() {
    mutex.unlock();
  }
  
private:
  
  Mutex mutex;
};

}

#endif
