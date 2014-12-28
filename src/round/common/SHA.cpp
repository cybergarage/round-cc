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
#define SHA256FUNC CC_SHA256
#else
#include <openssl/sha.h>
#define SHA1FUNC SHA1
#define SHA256FUNC SHA256
#endif

#include <round/common/SHA.h>

////////////////////////////////////////
// SHA1
////////////////////////////////////////

const int Round::SHA1::DIGEST_LENGTH = SHA_DIGEST_LENGTH;
const int Round::SHA1::DIGEST_STRING_LENGTH = SHA_DIGEST_LENGTH * 2;

const char *Round::SHA1::Hash(const std::string &string, std::string *buf) {
unsigned char shaDigest[SHA_DIGEST_LENGTH];
  char shaDigestString[(SHA_DIGEST_LENGTH*2) + 1];

  ::SHA1FUNC((unsigned const char *)string.c_str(), (int)strlen(string.c_str()), shaDigest);

  char hexString[3];
  for (int n = 0; n < SHA_DIGEST_LENGTH; n++) {
    snprintf(hexString, sizeof(hexString), "%02X", shaDigest[n]);
    shaDigestString[(n*2)+0] = hexString[0];
    shaDigestString[(n*2)+1] = hexString[1];
  }
  shaDigestString[sizeof(shaDigestString)-1] = '\0';

  *buf = shaDigestString;

  return buf->c_str();
}

////////////////////////////////////////
// SHA256
////////////////////////////////////////

const int Round::SHA256::DIGEST_LENGTH = SHA256_DIGEST_LENGTH;
const int Round::SHA256::DIGEST_STRING_LENGTH = SHA256_DIGEST_LENGTH * 2;

const char *Round::SHA256::Hash(const std::string &string, std::string *buf) {
  unsigned char shaDigest[SHA256_DIGEST_LENGTH];
  char shaDigestString[(SHA256_DIGEST_LENGTH*2) + 1];
  
  ::SHA256FUNC((unsigned const char *)string.c_str(), (int)strlen(string.c_str()), shaDigest);
  
  char hexString[3];
  for (int n = 0; n < SHA256_DIGEST_LENGTH; n++) {
    snprintf(hexString, sizeof(hexString), "%02X", shaDigest[n]);
    shaDigestString[(n*2)+0] = hexString[0];
    shaDigestString[(n*2)+1] = hexString[1];
  }
  shaDigestString[sizeof(shaDigestString)-1] = '\0';
  
  *buf = shaDigestString;
  
  return buf->c_str();
}
