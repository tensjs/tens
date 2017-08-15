const tf = require('../');

const node1 = tf.constant(3, tf.float32);
const node2 = tf.constant(4.0); // defautl float32
// Tensor("Const:0", shape=[], dtype=float32) Tensor("Const_1:0", shape=[], dtype=float32)
console.log(node1, node2);
const sess = tf.Session();
console.log(sess.run([node1, node2])); // [3.0, 4.0]
const node3 = tf.add(node1, node2);
console.log(sess.run(node3)); // 7.0
