#include "exception.h"

Exception::Exception(char* msg, char* code)
{
  this->msg = msg;
  this->code = code;
}

Exception::~Exception() { this->msg = nullptr; this->code = nullptr; }

void Exception::ThrowError(napi_env env, const char* msg, const char* code)
{
  #ifdef NAPI_EXCEPTION_HANDLE

  napi_status status;
  status = napi_throw_error(env, code, msg);
  assert(status == napi_ok);

  #elif STDIO_EXCEPTION_HANDLE

  printf("Error(%s): %s\n", code, msg);
  exit(-1);

  #endif
}

void Exception::ThrowTypeError(napi_env env, const char* msg, const char* code)
{
  #ifdef NAPI_EXCEPTION_HANDLE

  napi_status status;
  status = napi_throw_type_error(env, code, msg);
  assert(status == napi_ok);

  #elif STDIO_EXCEPTION_HANDLE

  printf("Type Error(%s): %s\n", code, msg);
  exit(-1);

  #endif
}
