/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_SCRIPT_H_
#define _ROUNDCC_SCRIPT_H_

#include <string>
#include <map>

#include <round/common/types.h>
#include <round/common/platform.h>
#include <round/common/Vector.h>
#include <round/common/Error.h>
#include <round/common/RPC.h>
#include <round/common/Mutex.h>
#include <round/common/JSON.h>

namespace Round {

class Script {
 public:
  static const int ENCODING_NONE;
  static const int ENCODING_BASE64;
  
 public:
  Script(const std::string &lang);
  Script(const std::string &lang, const std::string &name, const std::string &code);
  Script(const std::string &lang, const std::string &name, const byte *code, size_t codeLen);
  
  virtual ~Script();

  const std::string &getLanguage() const {
    return this->language;
  }
  
  bool isLanguage(const std::string &language) const {
    return (this->language.compare(language) == 0) ? true : false;
  }
  
  bool setName(const std::string &name) {
    this->name = name;
    return true;
  }
  
  const std::string &getName() const {
    return this->name;
  }
  
  const bool hasName() const {
    return (0 < this->name.length()) ? true : false;
  }
  
  bool setCode(const byte *code, size_t codeLen);
  bool setCode(const std::string code);

  bool isBinaryCode();
  
  const byte *getCode() const {
    return this->code;
  }
  
  const char *getStringCode() const {
    return (const char *)this->code;
  }
  
  size_t getCodeLength() const {
    return this->codeLen;
  }
  
  const bool hasCode() const {
    return (0 < this->codeLen) ? true : false;
  }

  bool setEncording(int encoding) {
    this->codeEncoding = encoding;
    return true;
  }
  
  const bool hasEncording() const {
    return (0 < this->codeEncoding) ? true : false;
  }
  
  int getEncording() const {
    return this->codeEncoding;
  }
  
  bool isEncoding(int encoding) const {
    return (this->codeEncoding == encoding) ? true : false;
  }
  
  bool isBase64Encoded() const {
    return isEncoding(ENCODING_BASE64);
  }
  
  bool isEncoded() const {
    return !isEncoding(ENCODING_NONE);
  }
  
  bool toJSONDictionary(JSONDictionary **jsonDict);

private:
  std::string language;
  std::string name;
  byte        *code;
  size_t      codeLen;
  int         codeEncoding;
};

class ScriptMap : public std::map<std::string, Script *> {
    
public:
    
  ScriptMap();
  virtual ~ScriptMap();
  
  bool hasScript(const std::string &name) const;
  const Script *getScript(const std::string &name) const;

  void clear();

  bool toJSONArray(JSONArray *jsonArray);
};

enum ScriptEngineStatus {
  ScriptEngineStatusOk          = 200,
  ScriptEngineStatusBadRequest  = 400,
};
  
class ScriptEngine {
    
public:
  ScriptEngine(const std::string &lang);
  virtual ~ScriptEngine();

  const std::string &getLanguage() const {
    return this->language;
  }
  
  virtual bool compile(const Script *script) const = 0;
  virtual bool run(const Script *script, const std::string &params, std::string *results, Error *error) const = 0;

  void lock() const {
    mutex.lock();
  }
  
  void unlock() const {
    mutex.unlock();
  }
  
private:
  
  std::string  language;
  mutable Mutex mutex;
};

class ScriptEngineMap : public std::map<std::string, ScriptEngine *> {
    
 public:
    
  ScriptEngineMap();
  virtual ~ScriptEngineMap();
  
  bool hasEngine(const std::string &lang) const;
  const ScriptEngine *getEngine(const std::string &lang) const;
    
  void clear();
};

class Node;
  
class ScriptManager {
    
 public:
  
  ScriptManager();
  virtual ~ScriptManager();
    
  bool setScript(const std::string &method, const std::string &lang, const std::string &script, int encodeType, Error *error);
  bool setScript(Script *script);
  
  bool hasScript(const std::string &name) const {
    return this->scripts.hasScript(name);
  }
  
  bool setEngine(ScriptEngine *engine);
  
  bool hasEngine(const std::string &lang) const {
    return this->engines.hasEngine(lang);
  }
  
  bool run(const std::string &name, const std::string &params, std::string *results, Error *error);
  
  bool toJSONArray(JSONArray *jsonArray, Error *error);

  void setNode(Node *node) {
    this->node = node;
  }

  Node *getNode() {
    return this->node;
  }

 private:

  bool removeScript(const std::string &method, const std::string &lang, Error *error);
  
  ScriptMap       scripts;
  ScriptEngineMap engines;
  Node            *node;
};

}

#endif
