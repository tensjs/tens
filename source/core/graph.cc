#include "graph.h"

napi_ref Graph::constructor;

Graph::Graph() : ref(nullptr) { this->tf_graph = TF_NewGraph(); }

Graph::~Graph() { TF_DeleteGraph(this->tf_graph); }

TF_Graph* Graph::GetTFGraph() { return this->tf_graph; }

napi_ref Graph::GetNapiRef() { return this->ref; }

napi_value Graph::Init(napi_env env) {
  napi_status status;

  napi_value cons;
  status = napi_define_class(env, "Graph", Graph::New, nullptr, 0, nullptr, &cons);
  assert(status == napi_ok);

  status = napi_create_reference(env, cons, 1, &constructor);
  assert(status == napi_ok);

  return cons;
}

napi_value Graph::New(napi_env env, napi_callback_info info)
{
  napi_status status;

  bool is_constructor;
  status = napi_is_construct_call(env, info, &is_constructor);
  assert(status == napi_ok);

  if (!is_constructor) {
    // Invoked as plain function `Graph(...)`, turn into construct call.
    return Graph::NewInstance(env, info);
  }

  // Invoked as constructor: `new Graph(...)`
  size_t argc = 1;
  napi_value args[1];
  napi_value jsthis;
  status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
  assert(status == napi_ok);

  Graph* obj = new Graph();

  status = napi_wrap(env, jsthis,
    reinterpret_cast<void*>(obj), Graph::Destructor, nullptr, &obj->ref);
  assert(status == napi_ok);

  return jsthis;
}

napi_value Graph::NewInstance(napi_env env, napi_callback_info info)
{
  napi_status status;

  size_t argc_ = 1;
  napi_value args[1];
  status = napi_get_cb_info(env, info, &argc_, args, nullptr, nullptr);
  assert(status == napi_ok);

  const size_t argc = 1;
  napi_value argv[argc] = {args[0]};

  napi_value cons;
  status = napi_get_reference_value(env, constructor, &cons);
  assert(status == napi_ok);

  napi_value instance;
  status = napi_new_instance(env, cons, argc, argv, &instance);
  assert(status == napi_ok);

  return instance;
}

void Graph::Destructor(napi_env env, void* instance_ptr, void* /*finalize_hint*/) {
  Graph* graph = reinterpret_cast<Graph*>(instance_ptr);

  napi_delete_reference(env, graph->ref);

  delete graph;
}
