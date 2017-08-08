const path = require('path');
const protobuf = require('protobufjs');
const tf = require('bindings')('tensorflow');

// eslint-disable-next-line import/no-dynamic-require
const json = require(path.join(__dirname, '../op_def.json'));
const root = protobuf.Root.fromJSON(json);

const OpListMessage = root.lookupType('OpList');

// eslint-disable-next-line no-underscore-dangle
const oplist = OpListMessage.decode(tf._getAllOpList()).op;

console.log(oplist);

const opFiltered = oplist
  .filter(opDef => opDef.name === 'Const')
  .map((opDef) => {
    console.log(opDef);
    return opDef;
    // console.log(opDef.inputArg)
    // console.log(opDef.outputArg)
    // console.log(opDef.attr)
  });

console.log(opFiltered.length);
