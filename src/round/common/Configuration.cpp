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

#include <fstream>
#include <sstream>

#include <round/common/Configuration.h>
#include <round/common/StringTokenizer.h>

const std::string Round::Configuration::PATH_DELIM = "/";

Round::Configuration::Configuration() {}

Round::Configuration::~Configuration() {
clear();
}

Round::Configuration::Configuration(const Configuration& config) {
set(config);
}

Round::Configuration &Round::Configuration::operator=(const Configuration &config) {
set(config);
  return (*this);
}

bool Round::Configuration::hasSection(const std::string &sectionName) const {
  return getSection(sectionName) ? true : false;
}

bool Round::Configuration::loadFromStream(std::istream &in) {
std::string section;
  std::string lineString;

  while (std::getline(in, lineString)) {
    if (lineString.size() <= 0)
      continue;
    if (lineString.find(";") == 0)
      continue;
    std::string key, value;
    size_t lineLen = strlen(lineString.c_str());
    char line[lineLen + 1];
    strcpy(line, lineString.c_str());
    if (lineString.find("[") == 0) {
      char *token = strtok(line, "[]");
      if (token)
        section = token;
    }
    else {
      char *token = strtok(line, " =");
      if (token)
        key = token;
      token = strtok(NULL, " =");
      if (token)
        value = token;
    }
    if ((section.length() <= 0) || (key.length() <= 0) || (value.length() <= 0))
      continue;
    set(section, key, value);
  }

  return true;
}

bool Round::Configuration::loadFromString(const std::string &string) {
std::stringstream ss;
  ss << string;
  return loadFromStream(ss);
}

bool Round::Configuration::loadFromFile(const std::string &filename) {
std::ifstream ifs;
  ifs.open(filename.c_str(), std::ifstream::in); 
  if (!ifs.is_open())
    return false;
  bool parseResult = loadFromStream(ifs);
  ifs.close();
  return parseResult; 
}

Round::Dictionary *Round::Configuration::getSection(const std::string &sectionName) const {
  Configuration::const_iterator section = find(sectionName);
  if (section == end())
    return NULL;
  return section->second;
}

bool Round::Configuration::set(const std::string &section, const std::string &key, const std::string &value) {
if ((section.length() <= 0) || (key.length() <= 0))
    return false;
  Round::Dictionary *sectionDir = getSection(section);
  if (!sectionDir) {
    Round::Dictionary *dict = new Dictionary();
    insert(std::make_pair(section, dict));
    sectionDir = getSection(section);
  }
  return sectionDir->set(key, value);
}

bool Round::Configuration::set(const Configuration &config) {
clear();

  for (Configuration::const_iterator section = config.begin(); section != config.end(); section++) {
    std::string key = section->first;
    Dictionary *dict = section->second;
    Dictionary *copyDict = new Dictionary();
    copyDict->set(dict);
    insert(std::make_pair(key, copyDict));
  }

  return true;
}

bool Round::Configuration::getString(const std::string &section, const std::string &key, std::string *value) const {
  if ((section.length() <= 0) || (key.length() <= 0))
    return false;

  Round::Dictionary *sectionDir = getSection(section);
  if (!sectionDir)
    return false;

  return sectionDir->get(key, value);
}

bool Round::Configuration::getStringByPath(const std::string &pathString, std::string *value) const {
  StringTokenizer tokenizer(pathString, PATH_DELIM);
  StringTokenList tokens;

  if (tokenizer.getTokens(&tokens) < 2)
    return false;

  std::string section = tokens[0];
  std::string key = tokens[1];

  return getString(section, key, value);
}

void Round::Configuration::clear()  {
  for (Configuration::iterator section = begin(); section != end(); section++) {
    Round::Dictionary *dict = section->second;
    if (dict)
      delete dict;
  }
  std::map<std::string, Dictionary*>::clear();
}


