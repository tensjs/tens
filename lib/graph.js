'use strict';

const Tensor = require('./tensor');

module.exports = class Graph {
  constructor() {
    this.opList = [];
  }
  createOp(opType, inputs, dataTypes, options) {
    this.opList.push({ opType, inputs, dataTypes, options });
    return new Tensor(options.name || opType);
  }
};
