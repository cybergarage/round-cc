/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#include <stdlib.h>
#include <sstream>
#include <round/common/BitOption.h>

Round::BitOption::BitOption() {
this->optionValue = NONE;
}

Round::BitOption::~BitOption() {}

void Round::BitOption::setOption(int key, bool value)  {
  if (value)
    this->optionValue |= key;
  else 
    this->optionValue &= ~key;
}

bool Round::BitOption::getOption(int key) const {
  return (this->optionValue & key);
}
