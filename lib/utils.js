'use strict';

const path = require('path');
const protobuf = require('protobufjs');
const is = require('is-type-of');

const Tensor = require('./tensor');
const DType = require('./dtype');

is.isTensor = tensor => {
  return tensor.constructor === Tensor.prototype.constructor;
};

is.isDType = dtype => {
  return dtype.constructor === DType.prototype.constructor;
};

// See https://github.com/dcodeIO/protobuf.js/pull/849
protobuf.Root.prototype.resolvePath = function(_, protoPath) {
  if (path.isAbsolute(protoPath)) {
    return protoPath;
  }
  return path.join(__dirname, '../', protoPath);
};

/**
 * hack load proto file
 * @param {string} file proto file name
 * @return {*} proto buffer object
 */
const loadProto = file => protobuf.loadSync(path.join(__dirname, '../', file));

module.exports = { loadProto, is };
