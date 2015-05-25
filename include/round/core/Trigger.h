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
#include <round/common/Thread.h>
#include <round/core/Node.h>

namespace Round {

class Trigger : public Thread<Node> {
  
public:
  Trigger();

  virtual ~Trigger();

  // Name
  
  bool setName(const std::string &value);
  bool getName(std::string *value) const;
  bool isName(const std::string &value) const;
  
  bool equals(const Trigger *other) const;

private:
  
  std::string  name;
};

class TimerTrigger : public Trigger {
public:
  TimerTrigger();
  TimerTrigger(const std::string &name, time_t duration, bool loop);
  ~TimerTrigger();

  bool setDuration(double value);
  double getDuration() const;
  
  bool setLoop(bool value);
  bool isLoop() const;
  
  void run();

private:
  bool init();
  bool update();

  double getCurrentTime();

private:
  double duration;
  bool loop;
  double lastExecutedTime;
};
  
class TriggerMap : public std::map<std::string, Trigger *> {
  
public:
  
  TriggerMap();
  ~TriggerMap();
  
  bool hasTrigger(const std::string &name) const;
  Trigger *findTrigger(const std::string &name) const ;
  
  bool addTrigger(Trigger *alias);
  bool setTrigger(Trigger *alias);
  bool removeTriggerByName(const std::string &name);
  
  void clear();
};

class TriggerManager : public TriggerMap {
    
 public:
  
  TriggerManager();
  virtual ~TriggerManager();

  bool start();
  bool stop();
  
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
