{
  "targets": [{
    "target_name": "tensorflow",
    "include_dirs": [
      "<!@(node -p \"require('node-addon-api').include\")",
      "tensorflow/include",
    ],
    "dependencies": [ "<!(node -p \"require('node-addon-api').gyp\")" ],
    "sources": [
      "cc/binding.cc"
    ],
    "cflags!": [ "-fno-exceptions" ],
    "cflags_cc!": [ "-fno-exceptions" ],
    "xcode_settings": {
      "CLANG_CXX_LIBRARY": "libc++",
      "MACOSX_DEPLOYMENT_TARGET": "10.12",
    },
    "libraries": [
      "-Wl,-rpath,$(PWD)/tensorflow/lib",
      "-L$(PWD)/tensorflow/lib",
      "-ltensorflow",
    ],
  }]
}
