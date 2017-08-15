'use strict';

const tf = require('bindings')('tensorflow');
const Graph = require('./lib/graph');
const OpDefLibrary = require('./lib/opDefLibrary');
const { opList, dataType } = require('./lib/proto');
console.log(dataType);
return;
const ops = opList.decode(tf.getAllOpList()).op;

const opDefLibrary = new OpDefLibrary(ops);
const inTopK = (predictions, targets) => {
  opDefLibrary.applyOp('InTopK', 'inTopK', { predictions, targets });
};
inTopK(2, 3);
module.exports = {
  __version: tf.version(),
};
