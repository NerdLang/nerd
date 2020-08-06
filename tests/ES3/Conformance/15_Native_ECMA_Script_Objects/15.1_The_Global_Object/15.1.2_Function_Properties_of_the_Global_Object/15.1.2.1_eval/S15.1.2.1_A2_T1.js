// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.1_A2_T1;
 * @section: 15.1.2.1, 16;
 * @assertion: If the parse fails, throw a SyntaxError exception (but see also clause 16);
 * @description: Checking if execution of "eval("x = 1; x\u000A++"), catch SyntaxError" passes; 
*/

//CHECK#1
try {
  eval("x = 1; x\u000A++");
  $ERROR('#1.1: eval("x = 1; x\\u000A++") must throw a SyntaxError. Actual: ' + (eval("x = 1; x\u000A++")));
} catch (e) {
  if ((e instanceof SyntaxError) !== true) {
    $ERROR('#1.2: eval("x = 1; x\\u000A++") must throw a SyntaxError. Actual: ' + (e));
  }  
}   
