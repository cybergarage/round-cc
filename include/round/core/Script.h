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

typedef std::string ScriptLang;
typedef std::string ScriptName;
typedef std::string ScriptContent;
typedef std::string ScriptParams;
typedef std::string ScriptResults;
  
class Script {

 public:
  Script(const ScriptLang &lang);
  Script(const ScriptLang &lang, const ScriptName &name, const ScriptContent &content);
  
  virtual ~Script();

  const ScriptLang &getLanguage() const {
    return this->language;
  }
  
  bool isLanguage(const ScriptLang &language) const {
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
  ScriptLang  language;
  ScriptName      name;
  ScriptContent   content;
};

class ScriptMap : public std::map<ScriptName, Script *> {
    
public:
    
  ScriptMap();
  virtual ~ScriptMap();
  
  bool hasScript(const ScriptName &name) const;
  const Script *getScript(const ScriptName &name) const;

  void clear();
};

enum JavaScriptEngineStatus {
  ScriptEngineStatusOk          = 200,
  ScriptEngineStatusBadRequest  = 400,
};

enum JavaScriptManagerDetailErrorStatus {
  ScriptManagerDetailStatusOk                   = 0,
  ScriptManagerDetailStatusParserError          = -32700,
  ScriptManagerDetailStatusInvalidRequest       = -32600,
  ScriptManagerDetailStatusMethodNotFound       = -32601,
  ScriptManagerDetailStatusInvalidParams        = -32602,
  ScriptManagerDetailStatusInternalError        = -32603,
  ScriptManagerDetailStatusSourceNotFound       = -32000,
  ScriptManagerDetailStatusScriptEngineNotFound = -32001,
  ScriptManagerDetailStatusCompileError         = -32002,
  ScriptManagerDetailStatusExecutionError       = -32003,
};
  
class ScriptEngine {
    
public:
  ScriptEngine(const ScriptLang &lang);
  virtual ~ScriptEngine();

  const ScriptLang &getLanguage() const {
    return this->language;
  }
  
  virtual bool run(const Script *script, const ScriptParams &params, ScriptResults *results, Error *error) const = 0;

private:
  
  ScriptLang  language;
};

class ScriptEngineMap : public std::map<ScriptLang, ScriptEngine *> {
    
 public:
    
  ScriptEngineMap();
  virtual ~ScriptEngineMap();
  
  bool hasEngine(const ScriptLang &lang) const;
  const ScriptEngine *getEngine(const ScriptLang &lang) const;
    
  void clear();
};

class ScriptManager {
    
 public:
  
  ScriptManager();
  virtual ~ScriptManager();
    
  bool setScript(Script *script);
  
  bool hasScript(const ScriptName &name) const {
    return this->scripts.hasScript(name);
  }
  
  bool setEngine(ScriptEngine *engine);
  
  bool hasEngine(const ScriptLang &lang) {
    return this->engines.hasEngine(lang);
  }
  
  bool run(const ScriptName &name, const ScriptParams &params, ScriptResults *results, Error *error);
  
 private:
    
  ScriptMap       scripts;
  ScriptEngineMap engines;
};

}

#endif
