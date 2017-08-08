#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <node_api.h>
#include <tensorflow/c/c_api.h>

#include "core/dtype.h"
#include "core/graph.h"
#include "core/operation.h"

napi_value Version(napi_env env, napi_callback_info info)
{
  napi_status status;
  napi_value result;
  const char *version = TF_Version();
  size_t len = strlen(version);
  status = napi_create_string_utf8(env, version, len, &result);
  if (status != napi_ok)
  {
    napi_throw_type_error(env, nullptr, "get version error");
  }
  return result;
}

napi_value GetAllOpList(napi_env env, napi_callback_info info)
{
  napi_status status;
  napi_value result;

  TF_Buffer* buff = TF_GetAllOpList();

  void *output = (void *)malloc(buff->length);
  status = napi_create_buffer_copy(env, buff->length, buff->data, &output, &result);
  if (status != napi_ok)
  {
    napi_throw_error(env, nullptr, "get op list error");
  }

  // TODO free(output);

  return result;
}

void Init(napi_env env, napi_value exports, napi_value module, void* priv)
{
  napi_status status;

  napi_value fn;

  // {function} exports.version
  status =  napi_create_function(env, NULL, Version, NULL, &fn);
  assert(status == napi_ok);

  status = napi_set_named_property(env, exports, "version", fn);
  assert(status == napi_ok);

  // {function} exports._getAllOpList
  status =  napi_create_function(env, NULL, GetAllOpList, NULL, &fn);
  assert(status == napi_ok);

  status = napi_set_named_property(env, exports, "_getAllOpList", fn);
  assert(status == napi_ok);

  // {object} exports.dtype
  // napi_value dtype_cons = Dtype::Init(env);
  // status = napi_set_named_property(env, exports, "Dtype", dtype_cons);
  // assert(status == napi_ok);

  // {class} exports.Graph
  napi_value graph_cons = Graph::Init(env);
  status = napi_set_named_property(env, exports, "Graph", graph_cons);
  assert(status == napi_ok);

  // {class} exports.Operation
  napi_value oper_cons = Operation::Init(env);
  status = napi_set_named_property(env, exports, "Operation", oper_cons);
  assert(status == napi_ok);
}

NAPI_MODULE(addon, Init)
