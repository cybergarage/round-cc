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
#include <round/common/RPC.h>

namespace Round {

typedef std::string ScriptLang;
typedef std::string ScriptName;
typedef std::string ScriptCode;
typedef std::string ScriptParams;
typedef std::string ScriptResults;
  
class Script {

 public:
  Script(const ScriptLang &lang);
  Script(const ScriptLang &lang, const ScriptName &name, const ScriptCode &content);
  
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
  
  bool setCode(const ScriptCode &content) {
    this->code = content;
    return true;
  }
  
  const ScriptCode &getCode() const {
    return this->code;
  }
  
  const bool hasCode() const {
    return (0 < this->code.length()) ? true : false;
  }
  
 private:
  ScriptLang language;
  ScriptName name;
  ScriptCode code;
};

class ScriptMap : public std::map<ScriptName, Script *> {
    
public:
    
  ScriptMap();
  virtual ~ScriptMap();
  
  bool hasScript(const ScriptName &name) const;
  const Script *getScript(const ScriptName &name) const;

  void clear();
};

enum ScriptEngineStatus {
  ScriptEngineStatusOk          = 200,
  ScriptEngineStatusBadRequest  = 400,
};

enum ScriptManagerDetailErrorStatus {
  ScriptManagerErrorCodeOk                        = 0,
  ScriptManagerErrorCodeParserError               = RPC::JSON::ErrorCodeParserError,
  ScriptManagerErrorCodeInvalidRequest            = RPC::JSON::ErrorCodeInvalidRequest,
  ScriptManagerErrorCodeMethodNotFound            = RPC::JSON::ErrorCodeMethodNotFound,
  ScriptManagerErrorCodeInvalidParams             = RPC::JSON::ErrorCodeInvalidParams,
  ScriptManagerErrorCodeInternalError             = RPC::JSON::ErrorCodeInternalError,
  ScriptManagerErrorCodeScriptEngineInternalError = -32000,
  ScriptManagerErrorCodeScriptEngineNotFound      = -32001,
  ScriptManagerErrorCodeCompileError              = -32002,
  ScriptManagerErrorCodeRuntimeError              = -32003,
};
  
class ScriptEngine {
    
public:
  ScriptEngine(const ScriptLang &lang);
  virtual ~ScriptEngine();

  const ScriptLang &getLanguage() const {
    return this->language;
  }
  
  virtual bool compile(const Script *script) const = 0;
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
    
  bool setScript(const ScriptName &method, const ScriptLang &lang, const ScriptCode &script, Error *error);
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

  bool removeScript(const ScriptName &method, const ScriptLang &lang, Error *error);
  
  ScriptMap       scripts;
  ScriptEngineMap engines;
};

}

#endif
