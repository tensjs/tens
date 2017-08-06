const tf = require('bindings')('tensorflow');

module.exports = {
  Graph: tf.Graph,
  Operation: tf.Operation,
  __version: tf.version(),
};
