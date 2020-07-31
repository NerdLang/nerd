// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.4.1_A4;
* @section: 11.4.1;
* @assertion: "Delete" operator removes property, which is reference to the object, not the object;
* @description: Checking two reference by one object;
*/

//CHECK#1
obj = new Object();
ref = obj;
delete ref;
if (typeof obj !== "object") {
  $ERROR('#1: obj = new Object(); ref = obj; delete ref; typeof obj === "object". Actual: ' + (typeof obj));
}

