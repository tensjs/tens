const tf = require('../');

/* eslint no-underscore-dangle: ["error", { "allow": ["__version"] }] */
test('operation', () => {
  const graph = tf.Graph();
  const oper = tf.Operation(graph, "Const", "const_op");
  oper.finish();

  expect(oper.graph === graph).toBe(true);
});
