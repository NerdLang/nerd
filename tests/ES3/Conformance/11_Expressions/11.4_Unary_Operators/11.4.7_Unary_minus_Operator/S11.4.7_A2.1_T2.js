// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.4.7_A2.1_T2;
* @section: 11.4.7;
* @assertion: Operator -x uses GetValue;
* @description: If GetBase(x) is null, throw ReferenceError;
*/

//CHECK#1
try {
  -x;
  $ERROR('#1.1: -x throw ReferenceError. Actual: ' + (-x));  
}
catch (e) {
  if ((e instanceof ReferenceError) !== true) {
    $ERROR('#1.2: -x throw ReferenceError. Actual: ' + (e));  
  }
}

