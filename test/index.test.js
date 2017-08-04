const tf = require('../');
const pkg = require('../package.json');

/* eslint no-underscore-dangle: ["error", { "allow": ["__version"] }] */
test('index', () => {
  expect(tf.__version).toBe(pkg.tfVersion);
});
