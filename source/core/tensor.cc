#include "tensor.h"
#include "../util/exception.h"

napi_ref Tensor::constructor;

Tensor::Tensor(TF_DataType type, const int64_t* dims, int num_dims, void* data, size_t len) {
  // void (*deallocator)(void* data, size_t len, void* arg)
  this->tf_tensor = TF_NewTensor(type, dims,
    num_dims, data, len, &Deallocate, nullptr /* void* deallocator_arg */);
}

Tensor::~Tensor() { }

napi_value Tensor::Init(napi_env env) {
  napi_status status;

  napi_value cons;
  status = napi_define_class(env, "Tensor",
    Tensor::New, nullptr, 0, nullptr, &cons);
  assert(status == napi_ok);

  status = napi_create_reference(env, cons, 1, &constructor);
  assert(status == napi_ok);

  return cons;
}

napi_value Tensor::New(napi_env env, napi_callback_info info)
{
  napi_status status;

  // Invoked as constructor: `new Tensor(...)`
  size_t argc = 5;
  napi_value args[5];
  napi_value jsthis;
  status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
  assert(status == napi_ok);

  if (argc < 5) {
    Exception::ThrowError(env, "5 arguments are needed!\n");
  }

  bool is_constructor;
  status = napi_is_construct_call(env, info, &is_constructor);
  assert(status == napi_ok);

  if (!is_constructor) {
    // Invoked as plain function `Operation(...)`, turn into construct call.
    return Tensor::NewInstance(env, info);
  }

  napi_valuetype valuetype;
  for (size_t i = 0; i < argc; i ++) {
    status = napi_typeof(env, args[0], &valuetype);
    assert(status == napi_ok && valuetype != napi_undefined);
  }

  TF_DataType type;
  status = napi_get_value_int32(env, args[0], (int *)&type);
  assert(status == napi_ok);

  int64_t dims;
  status = napi_get_value_int64(env, args[1], &dims);
  assert(status == napi_ok);

  int num_dims;
  // #ifdef __x86_64__
  // status = napi_get_value_int64(env, args[2], &num_dims);
  // #else // __i386__
  status = napi_get_value_int32(env, args[2], &num_dims);
  // #endif
  assert(status == napi_ok);

  size_t len = 0;
  status = napi_get_value_uint32(env, args[4], (uint32_t *)&len);
  assert(status == napi_ok);

  void* data = (void *)malloc(sizeof(char) * len);
  status = napi_get_buffer_info(env, args[3], &data, &len);
  assert(status == napi_ok);

  Tensor* tensor = new Tensor(type, &dims, num_dims, data, len);

  status = napi_wrap(env, jsthis,
    reinterpret_cast<void*>(tensor), Tensor::Destructor, nullptr, nullptr);
  assert(status == napi_ok);

  return jsthis;
}

napi_value Tensor::NewInstance(napi_env env, napi_callback_info info)
{
  napi_status status;

  size_t _argc = 5;
  napi_value args[5];
  status = napi_get_cb_info(env, info, &_argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  const size_t argc = 5;
  napi_value argv[argc] = {args[0], args[1], args[2], args[3], args[4]};

  napi_value cons;
  status = napi_get_reference_value(env, constructor, &cons);
  assert(status == napi_ok);

  napi_value instance;
  status = napi_new_instance(env, cons, argc, argv, &instance);
  assert(status == napi_ok);

  return instance;
}

void Tensor::Destructor(napi_env env, void* instance_ptr, void* /*finalize_hint*/) {
  reinterpret_cast<Tensor*>(instance_ptr)->~Tensor();
}

void Tensor::Deallocate(void* data, size_t len, void* arg)
{
  // TODO dealloate the tensor data
}
