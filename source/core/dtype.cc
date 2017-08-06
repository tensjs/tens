#include "dtype.h"

Dtype::DataType data_types[] = {
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

napi_value Dtype::Init(napi_env env) {
  napi_status status;

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
