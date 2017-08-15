'use strict';

const OpDef = require('./opDef');
const DType = require('./dtype');

const { is } = require('./utils');

const isListParameter = arg => {
  if (arg.numberAttr) {
    return true;
  } else if (arg.typeListAttr) {
    return true;
  }
  return false;
};
class OpDefLibrary {
  constructor(ops) {
    this.ops = {};
    this.addOpList(ops);
  }
  addOp(op) {
    // TODO: 判断 op 是否是 op 类型
    this.ops[op.name] = new OpDef(op);
  }
  addOpList(ops) {
    // TODO: 判断 ops 是否是 oplist
    ops.forEach(op => {
      this.addOp(op);
    });
  }
  applyOp(opTypeName, name = '', keywords) {
    this.name = name || opTypeName;
    const opDef = this.ops[opTypeName];
    console.log(opDef);
    if (!opDef) {
      throw new Error(`Unrecognized Op name ${opTypeName}`);
    }
    const op = opDef.op;
    const defaultTypeAttr = {};
    const attrs = {};
    const inputs = [];
    const input_types = [];
    const args = op.inputArg.concat(op.outputArg);
    console.log(op.attr);
    for (const attr of op.attr) {
      if (attr.type !== 'type') continue;
      const key = attr.name;
      const defaultValue = attr.defaultValue;
      if (defaultValue) {
        defaultTypeAttr[key] = DType.asDtype(defaultValue.type);
      }
    }
    for (const input of op.inputArg) {
      const inputName = input.name;
      // 如果是 js 关键字，使用 xx_方式表示
      const values = keywords[inputName] || keywords[`${inputName}_`];
      if (!values) {
        throw new Error(`No argument for input ${inputName}`);
      }
      if (isListParameter(input)) {
        if (!is.array(values)) {
          throw new Error(`Expected list for ${inputName} argument to ${opTypeName} Op, not ${values}.`);
        }
        const dtype = '';
        const defaultDtype = '';
        if (input.type !== DType.values('DT_INVALID')) {
          dtype = input.type;
        } else if (input.numberAttr) {
          const typeAttr = input.typeAttr;
          if (attrs[typeAttr]) {
            dtype = attrs[typeAttr];
          } else {
            for (const value of values) {
              if (is.isTensor(value)) {
                dtype = value.dtype;
                break;
              }
            }
            if (!dtype && defaultTypeAttr[typeAttr]) {
              dtype = defaultTypeAttr[typeAttr];
            }
          }
        }
        if (!input.isRef && dtype) {
          dtype = DType.asDtype(dtype).baseType;
        }

      }
    }
  }
}

module.exports = OpDefLibrary;
