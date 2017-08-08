#include "dtype.h"

napi_ref Dtype::constructor;
Dtype* Dtype::sgt_instance;

Dtype::Dtype() : ref(nullptr) { }

Dtype::~Dtype() { }

napi_value Dtype::Init(napi_env env) {
  napi_status status;

  DataType data_types[] = {
    { "float", TF_FLOAT },
    { "double", TF_DOUBLE },
    { "int32", TF_INT32 },
    { "uint8", TF_UINT8 },
    { "int16", TF_INT16 },
    { "int8", TF_INT8 },
    { "string", TF_STRING },
    { "complex64", TF_COMPLEX64 },
    { "complex", TF_COMPLEX },
    { "int64", TF_INT64 },
    { "bool", TF_BOOL },
    { "qint8", TF_QINT8 },
    { "quint8", TF_QUINT8 },
    { "qint32", TF_QINT32 },
    { "bfloat16", TF_BFLOAT16 },
    { "qint16", TF_QINT16 },
    { "quint16", TF_QUINT16 },
    { "uint16", TF_UINT16 },
    { "complex128", TF_COMPLEX128 },
    { "half", TF_HALF },
    { "resource", TF_RESOURCE }
  };

  napi_value obj;
  status = napi_create_object(env, &obj);
  assert(status == napi_ok);

  size_t type_count = sizeof(data_types) / sizeof(data_types[0]);
  napi_property_descriptor properties[type_count];

  napi_value value;
  for (size_t i = 0; i < type_count; i++) {
    status = napi_create_number(env, data_types[i].value, &value);
    assert(status == napi_ok);

    properties[i] = { data_types[i].name, 0, 0, 0, 0, value, napi_enumerable, 0 };
  }

  status = napi_define_properties(env, obj, type_count, properties);

  return obj;
}

napi_value Dtype::New(napi_env env, napi_callback_info info)
{
  napi_status status;

  bool is_constructor;
  status = napi_is_construct_call(env, info, &is_constructor);
  assert(status == napi_ok);

  if (!is_constructor) {
    // Invoked as plain function `Dtype(...)`, turn into construct call.
    return Dtype::NewInstance(env, info);
  }

  // Invoked as constructor: `new Dtype(...)`
  napi_value jsthis;
  status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
  assert(status == napi_ok);

  Dtype* obj = sgt_instance;
  if (sgt_instance == nullptr) {
    obj = new Dtype();
  }

  status = napi_wrap(env, jsthis,
    reinterpret_cast<void*>(obj), Dtype::Destructor, nullptr, &obj->ref);
  assert(status == napi_ok);

  return jsthis;
}

napi_value Dtype::NewInstance(napi_env env, napi_callback_info info)
{
  napi_status status;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, nullptr);
  assert(status == napi_ok);

  napi_value cons;
  status = napi_get_reference_value(env, constructor, &cons);
  assert(status == napi_ok);

  napi_value instance;
  status = napi_new_instance(env, cons, 0, nullptr, &instance);
  assert(status == napi_ok);

  return instance;
}

void Dtype::Destructor(napi_env env, void* instance_ptr, void* /*finalize_hint*/) {
  Dtype* dtype = reinterpret_cast<Dtype*>(instance_ptr);
  napi_delete_reference(env, dtype->ref);
  dtype->~Dtype();
}
