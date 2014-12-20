/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_JSON_H_
#define _ROUNDCC_JSON_H_

#include <string>
#include <vector>
#include <map>
#include <round/common/Error.h>
#include <round/common/Dictionary.h>

//#define USE_ROUND_JSON_PARSER_JANSSON 1

namespace Round {

class JSONObject {
 public:
  enum {
    STRING = 0,
    ARRAY,
    DICTIONARY,
  };

 public:
  JSONObject();
  virtual ~JSONObject();

  virtual int getType() const = 0;
  virtual bool copy(JSONObject **newObj) const = 0;
  virtual const char *toJSONString(std::string *stringBuf) const = 0;
  
  bool isString() const;
  bool isArray() const;
  bool isDictionary() const;

  bool equals(const JSONObject *object) const;
};

class JSONString : public std::string, public JSONObject {
  
public:
  
  JSONString();
  JSONString(const std::string &value);

  bool set(const JSONString *jsonObj);
  bool set(const std::string &value);

  virtual ~JSONString();
  int getType() const {return STRING;}

  bool copy(JSONObject **newObj) const;
  bool copy(JSONString **newObj) const {
    return copy((JSONObject **)newObj);
  }
  const char *toJSONString(std::string *stringBuf) const;
};

class JSONArray : public JSONObject, public std::vector<JSONObject *> {
  
public:
  
  JSONArray();
  virtual ~JSONArray();

  int getType() const {return ARRAY;}
  bool copy(JSONObject **newObj) const;
  bool copy(JSONArray **newObj) const {
    return copy((JSONObject **)newObj);
  }
  const char *toJSONString(std::string *stringBuf) const;

  bool set(const JSONArray *jsonObj);

  void add(JSONObject *value);
  void add(const std::string &value);

  JSONObject *getObject(size_t n) const ;
  bool getString(size_t n, std::string *value) const ;
  bool getInteger(size_t n, int *value) const ;

  void clear();
};

class JSONDictionary : public JSONObject, public std::map<std::string, JSONObject *> {
  
public:
  
  JSONDictionary();  
  virtual ~JSONDictionary();
  
  int getType() const {return DICTIONARY;}
  bool copy(JSONObject **newObj) const;
  bool copy(JSONDictionary **newObj) const {
    return copy((JSONObject **)newObj);
  }
  const char *toJSONString(std::string *stringBuf) const;

  bool set(const JSONDictionary *jsonObj);

  bool set(const std::string &key, JSONObject *value);
  bool get(const std::string &key, JSONObject **value) const;
  bool hasKey(const std::string &key) const;

  bool set(const std::string &key, const std::string &value);
  bool set(const std::string &key, const char *value);
  bool set(const std::string &key, size_t value);
  bool set(const std::string &key, int value);
  bool set(const std::string &key, long value);
  bool set(const std::string &key, bool value);

  bool get(const std::string &key, std::string *value) const;

  bool get(const std::string &key, size_t *value) const;
  bool get(const std::string &key, int *value) const;
  bool get(const std::string &key, long *value) const;
  bool get(const std::string &key, bool *value) const;

  const char *get(const std::string &key, std::string *value, const std::string &defaultValue) const;
  std::size_t get(const std::string &key, std::size_t defaultValue) const;
  int get(const std::string &key, int defaultValue) const;
  long get(const std::string &key, long defaultValue) const;
  bool get(const std::string &key, bool defaultValue) const;

  bool remove(const std::string &key);

  void clear();
};

class JSONParser {
  
public:
  
  JSONParser();
  virtual ~JSONParser();

  bool parse(const std::string &jsonString, Error *error);
  bool parse(const std::string &jsonString, JSONObject **jsonObject, Error *error);

  JSONObject *getRootObject() const {
    return this->rootObject;
  }

  JSONObject *popRootObject();
  
  virtual JSONString *createJSONString(const std::string &value) {
    return new JSONString(value);
  }

  virtual JSONArray *createJSONArray() {
    return new JSONArray();
  }

  virtual JSONDictionary *createJSONDictionary() {
    return new JSONDictionary();
  }

  void clear();

private:

  JSONObject *rootObject;
};

}

#endif
