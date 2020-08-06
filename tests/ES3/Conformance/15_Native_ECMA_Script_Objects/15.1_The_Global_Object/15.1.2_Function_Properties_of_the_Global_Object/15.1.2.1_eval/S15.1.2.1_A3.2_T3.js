// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.1_A3.2_T3;
 * @section: 15.1.2.1, 12.3;
 * @assertion: If Result(3).type is normal and its completion value is empty, 
 * then return the value undefined; 
 * @description: Empty statement;
*/

//CHECK#1
if (eval(";") !== undefined) {
  $ERROR('#1: eval(";") === undefined. Actual: ' + (eval(";")));
}    
