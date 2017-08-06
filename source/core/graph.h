#ifndef TENSJS_C_CORE_GRAPH_H_
#define TENSJS_C_CORE_GRAPH_H_

#include <assert.h>
#include <node_api.h>
#include <tensorflow/c/c_api.h>

class Graph {
public:
  TF_Graph* GetTFGraph();
  napi_ref GetNapiRef();

  static napi_value Init(napi_env env);

private:
  explicit Graph(); // constructor
  ~Graph(); // destructor

  static napi_value New(napi_env env, napi_callback_info info);
  static napi_value NewInstance(napi_env env, napi_callback_info info);
  static void Destructor(napi_env env, void* nativeObject, void* /*finalize_hint*/);

  napi_ref ref;
  TF_Graph* tf_graph;

  static napi_ref constructor;
};

#endif  // TENSJS_C_CORE_GRAPH_H_
