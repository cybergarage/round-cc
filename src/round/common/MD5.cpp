/******************************************************************
 *
 * Round for C++
 *
 * Copyright (C) Satoshi Konno 2014
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdio.h>
#include <string.h>
#include <round/common/MD5.h>

#if defined(__APPLE__)
#define COMMON_DIGEST_FOR_OPENSSL
#include <CommonCrypto/CommonDigest.h>
#define MD5FUNC CC_MD5
#else
#include <openssl/md5.h>
#define MD5FUNC MD5
#endif

const int Round::MD5::DIGEST_LENGTH = MD5_DIGEST_LENGTH;
const int Round::MD5::DIGEST_STRING_LENGTH = MD5_DIGEST_LENGTH * 2;

const char *Round::MD5::Hash(const std::string &string, std::string *buf) {
  unsigned char md5Digest[MD5_DIGEST_LENGTH];
  char md5DigestString[(MD5_DIGEST_LENGTH*2) + 1];

  ::MD5FUNC((const unsigned char *)string.c_str(), (int)strlen(string.c_str()), md5Digest);

  char hexString[3];
  for (int n = 0; n < MD5_DIGEST_LENGTH; n++) {
    snprintf(hexString, sizeof(hexString), "%02X", md5Digest[n]);
    md5DigestString[(n*2)+0] = hexString[0];
    md5DigestString[(n*2)+1] = hexString[1];
  }
  md5DigestString[sizeof(md5DigestString)-1] = '\0';

  *buf = md5DigestString;

  return buf->c_str();
}
