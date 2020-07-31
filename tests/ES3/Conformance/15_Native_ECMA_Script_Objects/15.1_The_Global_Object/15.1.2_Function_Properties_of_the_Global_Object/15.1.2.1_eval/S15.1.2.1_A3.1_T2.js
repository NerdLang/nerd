// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.1_A3.1_T2;
 * @section: 15.1.2.1, 12.4;
 * @assertion: If Result(3).type is normal and its completion value is a value V, 
 * then return the value V;
 * @description: Expression statement. Eval return object value;  
*/

//CHECK#1
var x = {};
if (eval("y = x") !== x) {
  $ERROR('#1: var x = {}; eval("y = x") === x. Actual: ' + (eval("y = x")));
}    
