// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S8.4_A5;
 * @section: 8.4, 7.8.4;
 * @assertion: Zero "\0" not terminates the string(C string);
 * @description: Insert "\0" into string;
*/

// CHECK#1
if ("x\0y" === "x") {
  $ERROR('#1: "x\\0y" !== "x"');
}

// CHECK#2
if (!(("x\0a" < "x\0b") && ("x\0b" < "x\0c"))) {
  $ERROR('#2: (("x\\0a" < "x\\0b") && ("x\\0b" < "x\\0c")) === true');
}
