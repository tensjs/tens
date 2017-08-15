'use strict';

const tf = require('../');

test('graph', () => {
  const graph = new tf.Graph();
  expect(graph instanceof tf.Graph).toBe(true);
});
