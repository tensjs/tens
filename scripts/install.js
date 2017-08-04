/**
 * node scripts install
 * download tensorflow
 */

const pkg = require('../package.json');
const os = require('os');
const urllib = require('urllib');
const compressing = require('compressing');
const path = require('path');

const type = 'cpu';// TODO: support other type

const prefix = 'https://storage.googleapis.com/tensorflow/libtensorflow';
const libtensorflow = `${prefix}/libtensorflow-${type}-${os.platform()}-x86_64-${pkg.tfVersion}.tar.gz`;
const libtensorflowProto = `${prefix}/libtensorflow_proto-${pkg.tfVersion}.zip`;

// download libtensorflow_proto
urllib.request(libtensorflowProto, {
  streaming: true,
  followRedirect: true,
})
  .then(result => compressing.zip.uncompress(result.res, path.join(__dirname, '..')))
  .then(() => console.log('libtensorflow_proto is downloaded'))
  .catch(console.error);

// download libtensorflow
urllib.request(libtensorflow, {
  streaming: true,
  followRedirect: true,
})
  .then(result => compressing.tgz.uncompress(result.res, path.join(__dirname, '../tensorflow')))
  .then(() => console.log('libtensorflow is downloaded'))
  .catch(console.error);
