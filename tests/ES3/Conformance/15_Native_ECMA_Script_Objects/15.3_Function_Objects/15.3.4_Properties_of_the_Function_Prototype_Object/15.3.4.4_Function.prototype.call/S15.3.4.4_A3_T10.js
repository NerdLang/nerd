// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3.4.4_A3_T10;
* @section: 15.3.4.4;
* @assertion: If thisArg is null or undefined, the called function is passed the global object as the this value;
* @description: Checking by using eval, no any arguments at call function;
*/

eval(" (function(){this.feat=1}).call()");

//CHECK#1
if (this["feat"] !== 1) {
  $ERROR('#1: If thisArg is null or undefined, the called function is passed the global object as the this value');
}
