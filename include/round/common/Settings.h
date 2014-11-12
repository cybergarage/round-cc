/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _FRACTALCC_SETTINGS_H_
#define _FRACTALCC_SETTINGS_H_

#include <round/common/Dictionary.h>

namespace Round {

class Settings : public Dictionary {
 public:
  Settings();
  ~Settings();

  bool parseFromFile(const std::string &filename);
};

}

#endif
