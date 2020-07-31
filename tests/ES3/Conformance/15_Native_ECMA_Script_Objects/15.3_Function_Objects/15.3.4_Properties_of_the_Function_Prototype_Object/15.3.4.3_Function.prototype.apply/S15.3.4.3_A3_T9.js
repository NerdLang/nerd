// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3.4.3_A3_T9;
* @section: 15.3.4.3;
* @assertion: If thisArg is null or undefined, the called function is passed the global object as the this value;
* @description: Checking by using eval, argument at apply function is void 0;
*/

eval( " Function(\"this.feat=1\").apply(void 0) " );

//CHECK#1
if (this["feat"] !== 1) {
  $ERROR('#1: If thisArg is null or undefined, the called function is passed the global object as the this value');
}
