// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S11.13.2_R2.3_T7;
 * @section: 11.13.2;
 * @description: Result is not ToInt32(Undefined) >> ToInt32(AssignmentExpression);
*/

//CHECK#1
try {  
  x >>= new String("-1");
  if (x === 0) {
    $ERROR('#1: Result is not ToInt32(Undefined) >> ToInt32(AssignmentExpression)');
  }  else {
    $ERROR('#1: x >>= new String("-1") throw ReferenceError');
  } 
}
catch (e) {
  if ((e instanceof ReferenceError) !== true) {
    $ERROR('#1: x >>= new String("-1") throw ReferenceError');  
  }
}
