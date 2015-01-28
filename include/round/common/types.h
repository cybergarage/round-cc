/******************************************************************
*
* Round for C++
*
* Copyright (C) Satoshi Konno 2015
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _ROUNDCC_TYPES_H_
#define _ROUNDCC_TYPES_H_

#include <round/common/platform.h>

#if !defined(byte)
typedef unsigned char byte;
#endif

#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201103L)) || defined(__APPLE__)
#define HAVE_STD_SHRAEDPTR 1
#define round_shared_ptr std::shared_ptr
#endif
#if !defined(HAVE_STD_SHRAEDPTR)
#include <boost/shared_ptr.hpp>
#define round_shared_ptr boost::shared_ptr
#endif

#endif
