// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.11.2_A3_T3;
* @section: 11.11.2;
* @assertion: If ToBoolean(x) is false, return y;
* @description: Type(x) and Type(y) vary between primitive string and String object;
*/

//CHECK#1
if (("" || "1") !== "1") {
  $ERROR('#1: ("" || "1") === "1"');
}

//CHECK#2
var y = new String("1");
if (("" || y) !== y) {
  $ERROR('#2: (var y = new String("1"); "" || y) === y');
}
