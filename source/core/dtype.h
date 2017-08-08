#ifndef TENSJS_C_CORE_DTYPE_H_
#define TENSJS_C_CORE_DTYPE_H_

#include <assert.h>
#include <node_api.h>
#include <tensorflow/c/c_api.h>

#define NAMING_STRING_SIZE 32

typedef struct DataType {
  char name[NAMING_STRING_SIZE];
  TF_DataType value;
} DataType;

class Dtype {
public:
  static napi_value Init(napi_env env);

private:
  explicit Dtype(); // constructor
  ~Dtype();

  static napi_value New(napi_env env, napi_callback_info info);
  static napi_value NewInstance(napi_env env, napi_callback_info info);
  static void Destructor(napi_env env, void* instance_ptr, void* /*finalize_hint*/);

  // TF_DataType float; // TF_FLOAT
  // TF_DataType double; // TF_DOUBLE
  // TF_DataType int32; // TF_INT32
  // TF_DataType uint8; // TF_UINT8
  // TF_DataType int16; // TF_INT16
  // TF_DataType int8; // TF_INT8
  // TF_DataType string; // TF_STRING
  // TF_DataType complex64; // TF_COMPLEX64
  // TF_DataType complex; // TF_COMPLEX
  // TF_DataType int64; // TF_INT64
  // TF_DataType bool; // TF_BOOL
  // TF_DataType qint8; // TF_QINT8
  // TF_DataType quint8; // TF_QUINT8
  // TF_DataType qint32; // TF_QINT32
  // TF_DataType bfloat16; // TF_BFLOAT16
  // TF_DataType qint16; // TF_QINT16
  // TF_DataType quint16; // TF_QUINT16
  // TF_DataType uint16; // TF_UINT16
  // TF_DataType complex128; // TF_COMPLEX128
  // TF_DataType half; // TF_HALF
  // TF_DataType resource; // TF_RESOURCE

  napi_ref ref; // wrapper object ref

  static napi_ref constructor; // js constructor ref
  static Dtype* sgt_instance; // the singleton instance;
};

#endif  // TENSJS_C_CORE_DTYPE_H_
