const tf = require('bindings')('tensorflow');

module.exports = {
  __version: tf.version(),
};
