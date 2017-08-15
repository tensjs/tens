'use strict';

const tf = require('../');

test('operation', () => {
  const graph = tf.Graph();
  const oper = tf.Operation(graph, 'Const', 'c');
  oper.finish();

  expect(oper.graph === graph).toBe(true);
});
