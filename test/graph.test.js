const tf = require('../');

/* eslint no-underscore-dangle: ["error", { "allow": ["__version"] }] */
test('graph', () => {
  const graph = tf.Graph();
  expect(true).toBe(true);
});
