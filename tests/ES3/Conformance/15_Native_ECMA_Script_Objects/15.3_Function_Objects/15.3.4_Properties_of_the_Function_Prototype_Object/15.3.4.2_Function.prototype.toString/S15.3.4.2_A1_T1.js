// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3.4.2_A1_T1;
* @section: 15.3.4.2;
* @assertion: An implementation-dependent representation of the function is returned. This representation has the syntax of a FunctionDeclaration;
* @description: For testing use Function.prototype.toString() function;
*/

f = function(x) {
  return x*x;
}

//CHECK#1
if (eval(f.toString())(10) !== f(10)) {
  $ERROR('#1: An implementation-dependent representation of the function is returned. This representation has the syntax of a FunctionDeclaration');
}
