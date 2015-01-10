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
#include <round/common/encoding/Base64.h>

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

ssize_t Round::Base64::Encode(const byte *rawBytes, size_t rawByteLen, std::string *encodedStr) {
  BIO *b64 = BIO_new(BIO_f_base64());
  BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
  BIO *bmem = BIO_new(BIO_s_mem());
  b64 = BIO_push(b64, bmem);
  BIO_write(b64, rawBytes, rawByteLen);
  BIO_flush(b64);
  
  BUF_MEM *bufMem;
  BIO_get_mem_ptr(b64, &bufMem);
  size_t encodedSize = bufMem->length;
  *encodedStr = std::string(bufMem->data, encodedSize);
  
  BIO_free_all(b64);
  
  return encodedSize;
}

ssize_t Round::Base64::Decode(const std::string &encodedStr, byte **decordedBytes) {
  size_t encodedStrSize = encodedStr.length();
  
  size_t decordedSize = (double)(encodedStrSize) * (3.0/4.0);
  if ((1 <= encodedStr.length()) && (encodedStr[encodedStrSize-1] == '=')) {
    decordedSize--;
    if ((2 <= encodedStr.length()) && (encodedStr[encodedStrSize-2] == '=')) {
      decordedSize--;
    }
  }
  
  *decordedBytes = (byte *)malloc(decordedSize + 1);
  if (!*decordedBytes)
    return -1;
  
  BIO *b64 = BIO_new(BIO_f_base64());
  BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
  BIO *bmem = BIO_new_mem_buf((void *)encodedStr.c_str(), (int)encodedStrSize);
  b64 = BIO_push(b64, bmem);
  size_t readLen = BIO_read(b64, *decordedBytes, decordedSize);
  (*decordedBytes)[readLen] = '\0';
  BIO_free_all(b64);
  
  return readLen;
}
