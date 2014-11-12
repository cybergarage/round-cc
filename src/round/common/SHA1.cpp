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

#if defined(__APPLE__)
#define COMMON_DIGEST_FOR_OPENSSL
#include <CommonCrypto/CommonDigest.h>
#define SHA1FUNC CC_SHA1
#else
#include <openssl/sha.h>
#define SHA1FUNC SHA1
#endif

#include <round/common/SHA1.h>

const int Round::SHA1::DIGEST_LENGTH = SHA_DIGEST_LENGTH;

const char *Round::SHA1::hash(const std::string &string, std::string *buf) {
unsigned char shaDigest[SHA_DIGEST_LENGTH];
  char sha5DigestString[(SHA_DIGEST_LENGTH*2) + 1];

  ::SHA1FUNC((unsigned const char *)string.c_str(), (int)strlen(string.c_str()), shaDigest);

  char hexString[3];
  for (int n = 0; n < SHA_DIGEST_LENGTH; n++) {
    snprintf(hexString, sizeof(hexString), "%02X", shaDigest[n]);
    sha5DigestString[(n*2)+0] = hexString[0];
    sha5DigestString[(n*2)+1] = hexString[1];
  }
  sha5DigestString[sizeof(sha5DigestString)-1] = '\0';

  *buf = sha5DigestString;

  return buf->c_str();
}
