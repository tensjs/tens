'use strict';

const { getAllOpList } = require('bindings')('tensorflow');

const { loadProto } = require('../lib/utils');

const opList = loadProto('tensorflow/core/framework/op_def.proto', 'OpList');

const ops = opList.decode(getAllOpList()).op;

ops.forEach(op => {
  if (op.name === 'Const' || op.name === 'Add') {
    console.log(op);
  }
});
