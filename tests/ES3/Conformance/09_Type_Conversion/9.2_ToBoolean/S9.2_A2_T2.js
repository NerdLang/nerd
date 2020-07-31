// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S9.2_A2_T2; 
 * @section: 9.2, 11.4.9;
 * @assertion: Result of boolean conversion from null value is false;
 * @description: null convert to Boolean by implicit transformation;
*/

// CHECK#1
if (!(null) !== true) {
  $ERROR('#1: !(null) === true. Actual: ' + (!(null))); 
}
