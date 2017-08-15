'use strict';

module.exports = class Tensor {
  constructor(name) {
    this.name = name;
    this.shape = [ 2, 2, 3 ];
    this.dtype = 'int32';
  }
};
