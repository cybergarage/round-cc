/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_JSON_H_
#define _ROUNDCC_JSON_H_

#include <string>
#include <vector>
#include <map>
#include <round/common/platform.h>
#include <round/common/Error.h>

namespace Round {

class JSONObject {
 public:
  enum {
    NIL = 0,
    STRING,
    INTEGER,
    REAL,
    BOOLEAN,
    ARRAY,
    DICTIONARY,
  };

 public:
  JSONObject();
  virtual ~JSONObject();

  virtual int getType() const = 0;
  virtual bool copy(JSONObject **newObj) const = 0;
  virtual const char *toJSONString(std::string *stringBuf) const = 0;
  
  bool isNull() const;
  bool isString() const;
  bool isInteger() const;
  bool isReal() const;
  bool isBoolean() const;
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
  bool set(const char *value);
  bool set(int value);
  bool set(bool value);
  bool set(long value);
  bool set(size_t value);
  bool set(double value);
  
  bool get(std::string *value) const;
  bool get(int *value) const;
  bool get(bool *value) const;
  bool get(long *value) const;
  bool get(size_t *value) const;
  bool get(double *value) const;
  
  virtual ~JSONString();
  int getType() const {return STRING;}

  bool copy(JSONObject **newObj) const;
  bool copy(JSONString **newObj) const {
    return copy((JSONObject **)newObj);
  }
  virtual const char *toJSONString(std::string *stringBuf) const;
};

class JSONNull : public JSONString {
 public:
  JSONNull();
  int getType() const {return NIL;}
  bool copy(JSONObject **newObj) const;
};
  
class JSONInteger : public JSONString {
 public:
  JSONInteger();
  JSONInteger(int value);

  int getType() const {return INTEGER;}
  bool copy(JSONObject **newObj) const;
  const char *toJSONString(std::string *stringBuf) const;
};

class JSONReal : public JSONString {
 public:
  JSONReal();
  JSONReal(double value);
    
  int getType() const {return REAL;}
  bool copy(JSONObject **newObj) const;
  const char *toJSONString(std::string *stringBuf) const;
};
  
class JSONBoolean : public JSONString {
  public:
    JSONBoolean();
    JSONBoolean(bool value);

  int getType() const {return BOOLEAN;}
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
  bool add(const JSONArray *jsonObj);

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
  bool add(const JSONDictionary *jsonObj);

  bool set(const std::string &key, JSONObject *value);
  bool get(const std::string &key, JSONObject **value) const;
  bool hasKey(const std::string &key) const;

  bool set(const std::string &key, const std::string &value);
  bool set(const std::string &key, const char *value);
  bool set(const std::string &key, int value);
  bool set(const std::string &key, bool value);
  bool set(const std::string &key, long value);
  bool set(const std::string &key, size_t value);
  bool set(const std::string &key, double value);

  bool get(const std::string &key, JSONDictionary **value) const;
  bool get(const std::string &key, JSONArray **value) const;
  bool get(const std::string &key, JSONString **value) const;
  bool get(const std::string &key, std::string *value) const;
  bool get(const std::string &key, int *value) const;
  bool get(const std::string &key, bool *value) const;
  bool get(const std::string &key, long *value) const;
  bool get(const std::string &key, size_t *value) const;
  bool get(const std::string &key, double *value) const;

  const char *get(const std::string &key, std::string *value, const std::string &defaultValue) const;
  std::size_t get(const std::string &key, std::size_t defaultValue) const;
  int get(const std::string &key, int defaultValue) const;
  long get(const std::string &key, long defaultValue) const;
  bool get(const std::string &key, bool defaultValue) const;

  JSONDictionary *getJSONDictionary(const std::string &key);
  JSONArray *getJSONArray(const std::string &key);
  
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
