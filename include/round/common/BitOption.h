/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2014
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _FRACTALCC_BITOPTION_H_
#define _FRACTALCC_BITOPTION_H_

namespace Round {
  
class BitOption {
 public:
 public:
  enum Option {
    NONE = 0,
  };

 public:
  BitOption();
  virtual ~BitOption();

  void setOption(int key, bool value);
  bool getOption(int key) const;

private:

  int optionValue;
};

}

#endif
