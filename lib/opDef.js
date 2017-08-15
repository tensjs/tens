'use strict';

module.exports = class OpDef {
  constructor(opDef) {
    // TODO:增加格式检查
    this.opDef = opDef;
  }
  get op() {
    return this.opDef;
  }
};
