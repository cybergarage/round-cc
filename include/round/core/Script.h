/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_SCRIPT_H_
#define _ROUNDCC_SCRIPT_H_

#include <string>
#include <map>

#include <round/common/Error.h>

namespace Round {

typedef std::string ScriptLanguage;
typedef std::string ScriptName;
typedef std::string ScriptContent;
typedef std::string ScriptParams;
typedef std::string ScriptResults;
  
class Script {

 public:
  Script(const ScriptLanguage &lang);
  Script(const ScriptName &name, const ScriptContent &content);
  
  virtual ~Script();

  const ScriptLanguage &getLanguage() const {
    return this->language;
  }
  
  bool isLanguage(const ScriptLanguage &language) const {
    return (this->language.compare(language) == 0) ? true : false;
  }
  
  bool setName(const ScriptName &name) {
    this->name = name;
    return true;
  }
  
  const ScriptName &getName() const {
    return this->name;
  }
  
  const bool hasName() const {
    return (0 < this->name.length()) ? true : false;
  }
  
  bool setContent(const ScriptContent &content) {
    this->content = content;
    return true;
  }
  
  const ScriptContent &getContent() const {
    return this->content;
  }
  
  const bool hasContent() const {
    return (0 < this->content.length()) ? true : false;
  }
  
 private:
  ScriptLanguage  language;
  ScriptName      name;
  ScriptContent   content;
};

class ScriptMap : public std::map<std::string, Script *> {
    
public:
    
  ScriptMap();
  virtual ~ScriptMap();
  bool hasScript(const ScriptName &name);
  Script *getScript(const ScriptName &name);

  void clear();
};

enum JavaScriptEngineStatus {
  ScriptEngineStatusOk          = 200,
  ScriptEngineStatusBadRequest  = 400,
};

enum JavaScriptEngineDetailStatus {
  ScriptEngineDetailStatusOk              = 0,
  ScriptEngineDetailStatusParserError     = -32700,
  ScriptEngineDetailStatusInvalidRequest  = -32600,
  ScriptEngineDetailStatusMethodNotFound  = -32601,
  ScriptEngineDetailStatusInvalidParams   = -32602,
  ScriptEngineDetailStatusInternalError   = -32603,
  ScriptEngineDetailStatusSourceNotFound  = -32000,
  ScriptEngineDetailStatusCompileError    = -32001,
  ScriptEngineDetailStatusExecutionError  = -32002,
};
  
class ScriptEngine {
    
public:
  ScriptEngine();
  virtual ~ScriptEngine();

  bool setScript(Script *script);
  
  bool hasScript(const ScriptName &name) {
    return this->scripts.hasScript(name);
  }
  
  bool run(const ScriptName &name, const ScriptParams &params, ScriptResults *results, Error *error);
  
  virtual bool run(const Script *script, const ScriptParams &params, ScriptResults *results, Error *error) = 0;

private:
  
  ScriptMap scripts;
};

}

#endif
