#ifndef TENSJS_C_CORE_DTYPE_H_
#define TENSJS_C_CORE_DTYPE_H_

#include <assert.h>
#include <node_api.h>
#include <tensorflow/c/c_api.h>

#define NAMING_STRING_SIZE 32

namespace Dtype {

  typedef struct DataType {
    char name[NAMING_STRING_SIZE];
    TF_DataType value;
  } DataType;

  napi_value Init(napi_env env);

};

#endif  // TENSJS_C_CORE_DTYPE_H_
