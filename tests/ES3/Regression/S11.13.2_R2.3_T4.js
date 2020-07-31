// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S11.13.2_R2.3_T4;
 * @section: 11.13.2;
 * @description: Result is not ToNumber(Undefined) + ToNumber(AssignmentExpression);
*/

//CHECK#1
try {  
  x += new String("-1");
  if (isNaN(x) === true) {
    $ERROR('#1: Result is not ToNumber32(Undefined) + ToNumber32(AssignmentExpression)');
  }  else {
    $ERROR('#1: x += new String("-1") throw ReferenceError');
  } 
}
catch (e) {
  if ((e instanceof ReferenceError) !== true) {
    $ERROR('#1: x += new String("-1") throw ReferenceError');  
  }
}
