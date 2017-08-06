const os = require("os");
const path = require('path');
const protobuf = require('protobufjs');
const tf = require('bindings')('tensorflow');

const root = protobuf.Root.fromJSON(require("../op_def.json"));

const OpListMessage = root.lookupType('OpList');
const oplist = OpListMessage.decode(tf._getAllOpList()).op;

console.log(oplist);
