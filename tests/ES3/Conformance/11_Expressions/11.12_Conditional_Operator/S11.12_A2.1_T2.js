// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.12_A2.1_T2;
* @section: 11.12, 8.7.1;
* @assertion: Operator x ? y : z uses GetValue;
* @description: If GetBase(x) is null, throw ReferenceError;
*/

//CHECK#1
try {
  x ? true : false;
  $ERROR('#1.1: x ? true : false throw ReferenceError. Actual: ' + (x ? true : false));  
}
catch (e) {
  if ((e instanceof ReferenceError) !== true) {
    $ERROR('#1.2: x ? true : false throw ReferenceError. Actual: ' + (e));  
  }
}
