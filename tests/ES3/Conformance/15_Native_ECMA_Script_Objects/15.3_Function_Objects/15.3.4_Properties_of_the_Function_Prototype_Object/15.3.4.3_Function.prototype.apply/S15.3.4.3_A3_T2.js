// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3.4.3_A3_T2;
* @section: 15.3.4.3;
* @assertion: If thisArg is null or undefined, the called function is passed the global object as the this value;
* @description: Argument at apply function is null;
*/

Function("this.field=\"green\"").apply(null);

//CHECK#1
if (this["field"] !== "green") {
  $ERROR('#1: If thisArg is null or undefined, the called function is passed the global object as the this value');
}
