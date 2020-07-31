// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.2.4.4_A1_T1;
* @section: 15.2.4.4;
* @assertion: The valueOf method returns its "this" value;
* @description: "this" value is a number;
*/

//CHECK#1
if (typeof Object.prototype.valueOf !== "function") {
  $ERROR('#1: valueOf method defined');
}

obj=new Object(1.1);

//CHECK#2
if (typeof obj.valueOf !== "function") {
  $ERROR('#2: valueOf method accessed');
}

//CHECK#3
if (obj.valueOf()!==1.1) {
  $ERROR('#3: The valueOf method returns its this value');
}

