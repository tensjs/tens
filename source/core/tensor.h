#ifndef TENSJS_C_CORE_TENSOR_H_
#define TENSJS_C_CORE_TENSOR_H_

#include <assert.h>
#include <node_api.h>
#include <tensorflow/c/c_api.h>

#define NAMING_STRING_SIZE 32

class Tensor {
public:
  static napi_value Init(napi_env env);

private:
  explicit Tensor(TF_DataType type, const int64_t* dims, int num_dims, void* data, size_t len); // constructor
  ~Tensor(); // destructor

  static napi_value New(napi_env env, napi_callback_info info);
  static napi_value NewInstance(napi_env env, napi_callback_info info);
  static void Destructor(napi_env env, void* instance_ptr, void* /*finalize_hint*/);
  static void Deallocate(void* data, size_t len, void* arg);

  TF_Tensor* tf_tensor;

  static napi_ref constructor;
};

#endif  // TENSJS_C_CORE_TENSOR_H_
