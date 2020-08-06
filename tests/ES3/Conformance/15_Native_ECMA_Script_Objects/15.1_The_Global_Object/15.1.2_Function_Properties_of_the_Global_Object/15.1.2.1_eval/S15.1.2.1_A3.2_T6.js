// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.1_A3.2_T6;
 * @section: 15.1.2.1, 12.6.1;
 * @assertion: If Result(3).type is normal and its completion value is empty, 
 * then return the value undefined; 
 * @description: do-while statement;
*/

//CHECK#1
if (eval("do ; while(false)") !== undefined) {
  $ERROR('#1: eval("do ; while(false)") === undefined. Actual: ' + (eval("do ; while(false)")));
}    
