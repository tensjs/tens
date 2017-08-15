'use strict';

const { loadProto } = require('./utils');

const opDef = loadProto('tensorflow/core/framework/op_def.proto');
const types = loadProto('tensorflow/core/framework/types.proto');
module.exports = {
  opList: opDef.lookupType('OpList'),
  OpDef: opDef.lookupType('OpDef'),
  dataType: types.lookupEnum('DataType'),
};
