#include <node_api.h>
#include <string.h>
#include <tensorflow/c/c_api.h>

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

void Init(napi_env env, napi_value exports, napi_value module, void* priv)
{
    napi_status status;
    napi_property_descriptor desc =
        { "version", 0, Version, 0, 0, 0, napi_default, 0 };
    status = napi_define_properties(env, exports, 1, &desc);
}

NAPI_MODULE(addon, Init)
