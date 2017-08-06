#ifndef TENSJS_C_CORE_OPERATION_H_
#define TENSJS_C_CORE_OPERATION_H_

#include <assert.h>
#include <node_api.h>
#include <tensorflow/c/c_api.h>

#define NAMING_STRING_SIZE 32

class Operation {
public:
  static napi_value Init(napi_env env);

private:
  explicit Operation(Graph* graph, const char* op_type, const char* oper_name); // constructor
  ~Operation(); // destructor

  static napi_value New(napi_env env, napi_callback_info info);
  static napi_value NewInstance(napi_env env, napi_callback_info info);
  static napi_value GetGraph(napi_env env, napi_callback_info info);
  static napi_value Finish(napi_env env, napi_callback_info info);
  static void Destructor(napi_env env, void* instance_ptr, void* /*finalize_hint*/);

  Graph* graph;
  TF_Status* tf_status;
  TF_Operation* tf_oper;
  TF_OperationDescription* tf_desc;

  static napi_ref constructor;
};

#endif  // TENSJS_C_CORE_OPERATION_H_
