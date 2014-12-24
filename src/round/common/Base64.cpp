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
#include <math.h>
#include <round/common/Base64.h>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#if defined(__APPLE__)
#define COMMON_DIGEST_FOR_OPENSSL
#include <CommonCrypto/CommonDigest.h>
#define MD5FUNC CC_MD5
#else
#include <openssl/md5.h>
#define MD5FUNC MD5
#endif

ssize_t Round::Base64::Encode(const char *rawBytes, std::string *encodedStr) {
  size_t rawByteSize = strlen(rawBytes);

  size_t encodedSize = 4.0 * ceil((double)(rawByteSize)/3.0);
  char *outChars = (char *)malloc(encodedSize + 1);
  if (!outChars)
    return -1;
  
  BIO *b64 = BIO_new(BIO_f_base64());
  BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
  BIO *bio = BIO_new_mem_buf(outChars, encodedSize);
  BIO_push(b64, bio);
  BIO_write(b64, rawBytes, rawByteSize);
  BIO_flush(b64);
  BIO_free_all(b64);
  
  outChars[encodedSize] = '\0';
  *encodedStr = outChars;
  free(outChars);

  return encodedSize;
}

ssize_t Round::Base64::Decode(const std::string &encodedStr, char **decordedBytes) {
  size_t encodedStrSize = encodedStr.length();
  
  size_t decordedSize = (double)(encodedStrSize) * (3.0/4.0);
  if ((1 <= encodedStr.length()) && (encodedStr[encodedStrSize-1] == '=')) {
    decordedSize--;
    if ((2 <= encodedStr.length()) && (encodedStr[encodedStrSize-2] == '=')) {
      decordedSize--;
    }
  }
  
  *decordedBytes = (char *)malloc(decordedSize + 1);
  if (!*decordedBytes)
    return -1;
  
  BIO *b64 = BIO_new(BIO_f_base64());
  BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
  BIO *bio = BIO_new_mem_buf(decordedBytes, decordedSize);
  bio = BIO_push(b64, bio);
  size_t readLen = BIO_read(b64, (char *)encodedStr.c_str(), encodedStrSize);
  (*decordedBytes)[readLen] = '\0';
  BIO_free_all(b64);
  
  return readLen;
}
