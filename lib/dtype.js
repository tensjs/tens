'use strict';
const { dataType } = require('./proto');
const { is } = require('./utils');
const { valuesById, values } = dataType;
const internTable = {};

const complex64 = values.DT_COMPLEX64;
const complex128 = values.DT_COMPLEX128;
const float = values.DT_FLOAT;
const float64 = values.DT_DOUBLE;
const bool = values.DT_BOOL;

class DType {
  constructor(id) {
    id = parseInt(id, 10);
    if (!this.valuesById(id) || this.values('DT_INVALID')) {
      throw new Error(`type_enum is not a valid DataType:${id}`);
    }
    this.id = id;
  }
  static valuesById(id) {
    return valuesById[id];
  }
  static values(value) {
    return values[value];
  }
  static asDtype(dtype) {
    if (is.isDType(dtype)) {
      return dtype;
    }
    if (internTable[dtype]) {
      return internTable[dtype];
    }
    if (this.values[dtype] && internTable[this.values[dtype]]) {
      return internTable[this.values[dtype]];
    }
    return null;
  }
  get _isRefDtype() {
    return this.id > 100;
  }
  get _asRef() {
    if (this._isRefDtype()) {
      return this;
    }
    return internTable[this.id + 100];
  }
  get baseDtype() {
    if (this._isRefDtype()) {
      return internTable[this.id - 100];
    }
    return this;
  }
  get realDtype() {
    const base = this.baseDtype;
    if (base === complex64) {
      return internTable[float];
    } else if (base === complex128) {
      return internTable[float64];
    }
    return this;
  }
  get asDatatypeEnum() {
    return this.id;
  }
  get isBool() {
    return this.baseDtype === bool;
  }
}

Object.keys(valuesById).forEach(id => {
  internTable[id] = new DType(id);
});


module.exports = DType;
