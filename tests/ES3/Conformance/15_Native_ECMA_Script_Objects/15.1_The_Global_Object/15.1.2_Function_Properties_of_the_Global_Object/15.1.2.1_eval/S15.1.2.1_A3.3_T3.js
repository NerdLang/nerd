// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.1_A3.3_T3;
 * @section: 15.1.2.1, 12.9;
 * @assertion: If Result(3).type is not normal, then Result(3).type must be throw.
 * Throw Result(3).value as an exception; 
 * @description: Return statement;
*/

//CHECK#1
try {
  eval("return;");
  $ERROR('#1.1: return must throw SyntaxError. Actual: ' + (eval("return;")));
} catch(e) {
  if ((e instanceof SyntaxError) !== true) {
    $ERROR('#1.2: return must throw SyntaxError. Actual: ' + (e));
  }  
}

//CHECK#2
try {
  function f() {
       eval("return;");
  }
  f();      
  $ERROR('#2.1: return must throw SyntaxError. Actual: ' + (f()));
} catch(e) {
  if ((e instanceof SyntaxError) !== true) {
    $ERROR('#2.2: return must throw SyntaxError. Actual: ' + (e));
  }  
}      
