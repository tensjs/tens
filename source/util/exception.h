#ifndef TENSJS_C_UTIL_EXCEPTION_H_
#define TENSJS_C_UTIL_EXCEPTION_H_

// #define NAPI_EXCEPTION_HANDLE 1
#define STDIO_EXCEPTION_HANDLE 2
// #define LOG_EXCEPTION_HANDLE 3

#include <stdio.h>
#include <stdlib.h>
#include <node_api.h>

class Exception {
public:
  static void ThrowError(napi_env env, const char* msg, const char* code = nullptr);
  static void ThrowTypeError(napi_env env, const char* msg, const char* code = nullptr);

private:
  Exception(char* msg, char* code);
  ~Exception();

  char* msg;
  char* code;
};

#endif  // TENSJS_C_UTIL_EXCEPTION_H_
