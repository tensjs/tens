#include "tensor.h"
#include "../util/exception.h"

napi_ref Tensor::constructor;

Tensor::Tensor(Graph* graph, const char* op_type, const char* oper_name)
{
  TF_Graph* tf_graph = graph->GetTFGraph();

  this->graph = graph;
  this->tf_status = TF_NewStatus();
  this->tf_desc = TF_NewOperation(tf_graph, op_type, oper_name);

  //TF_Output output = { TF_Operation* oper, 0 };

  //TF_AddInput(this->tf_desc)
}

Operation::~Operation() {
  this->graph = nullptr;
  this->tf_desc = nullptr;
  this->tf_oper = nullptr;
  this->tf_status = nullptr;
  TF_DeleteStatus(this->tf_status);
}

napi_value Operation::Init(napi_env env) {
  napi_status status;
  napi_property_descriptor properties[] = {
    { "graph", 0, 0, Operation::GetGraph, 0, 0, napi_enumerable, 0 },
    { "finish", 0, Operation::Finish, 0, 0, 0, napi_enumerable, 0 }
  };

  size_t property_count = sizeof(properties) / sizeof(properties[0]);

  napi_value cons;
  status = napi_define_class(env, "Operation",
    Operation::New, nullptr, property_count, properties, &cons);
  assert(status == napi_ok);

  status = napi_create_reference(env, cons, 1, &constructor);
  assert(status == napi_ok);

  return cons;
}

napi_value Operation::New(napi_env env, napi_callback_info info)
{
  napi_status status;

  // Invoked as constructor: `new Operation(...)`
  size_t argc = 3;
  napi_value args[3];
  napi_value jsthis;
  status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
  assert(status == napi_ok);

  if (argc < 3) {
    Exception::ThrowError(env, "three arguments are needed!\n");
  }

  bool is_constructor;
  status = napi_is_construct_call(env, info, &is_constructor);
  assert(status == napi_ok);

  if (!is_constructor) {
    // Invoked as plain function `Operation(...)`, turn into construct call.
    return Operation::NewInstance(env, info);
  }

  Graph* graph;
  size_t str_len = 0;
  char oper_name[NAMING_STRING_SIZE];
  char op_type[NAMING_STRING_SIZE];

  napi_valuetype valuetype;
  status = napi_typeof(env, args[0], &valuetype);
  assert(status == napi_ok);

  if (valuetype != napi_undefined) {
    status = napi_unwrap(env, args[0], reinterpret_cast<void**>(&graph));
    assert(status == napi_ok);
  }

  status = napi_typeof(env, args[1], &valuetype);
  assert(status == napi_ok);

  if (valuetype != napi_undefined) {
    status = napi_get_value_string_utf8(env, args[1], op_type, NAMING_STRING_SIZE, &str_len);
    assert(status == napi_ok);
  }

  if (str_len >= NAMING_STRING_SIZE) {
    napi_throw_error(env, nullptr, "op_type string is too long!");
  }

  status = napi_typeof(env, args[2], &valuetype);
  assert(status == napi_ok);

  if (valuetype != napi_undefined) {
    status = napi_get_value_string_utf8(env, args[2], oper_name, NAMING_STRING_SIZE, &str_len);
    assert(status == napi_ok);
  }

  if (str_len >= NAMING_STRING_SIZE) {
    napi_throw_error(env, nullptr, "oper_name string is too long!");
  }

  Operation* obj = new Operation(graph, op_type, oper_name);

  status = napi_wrap(env, jsthis,
    reinterpret_cast<void*>(obj), Operation::Destructor, nullptr, nullptr);
  assert(status == napi_ok);

  return jsthis;
}

napi_value Operation::NewInstance(napi_env env, napi_callback_info info)
{
  napi_status status;

  size_t _argc = 3;
  napi_value args[3];
  status = napi_get_cb_info(env, info, &_argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  const size_t argc = 3;
  napi_value argv[argc] = {args[0], args[1], args[2]};

  napi_value cons;
  status = napi_get_reference_value(env, constructor, &cons);
  assert(status == napi_ok);

  napi_value instance;
  status = napi_new_instance(env, cons, argc, argv, &instance);
  assert(status == napi_ok);

  return instance;
}

void Operation::Destructor(napi_env env, void* instance_ptr, void* /*finalize_hint*/) {
  reinterpret_cast<Operation*>(instance_ptr)->~Operation();
}

napi_value Operation::GetGraph(napi_env env, napi_callback_info info) {
  napi_status status;

  napi_value jsthis;
  status = napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr);
  assert(status == napi_ok);

  Operation* oper;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&oper));
  assert(status == napi_ok);

  napi_value graph;
  status = napi_get_reference_value(env, oper->graph->GetNapiRef(), &graph);
  assert(status == napi_ok);

  return graph;
}

napi_value Operation::Finish(napi_env env, napi_callback_info info)
{
  napi_status status;

  napi_value jsthis;
  status = napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr);
  assert(status == napi_ok);

  Operation* oper;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&oper));
  assert(status == napi_ok);

  TF_Operation* tf_oper = TF_FinishOperation(oper->tf_desc, oper->tf_status);
  if (TF_GetCode(oper->tf_status) == TF_OK || oper == nullptr) {
    Exception::ThrowError(env, "finish operation failed!\n");
  }

  oper->tf_oper = tf_oper;

  return jsthis;
}
