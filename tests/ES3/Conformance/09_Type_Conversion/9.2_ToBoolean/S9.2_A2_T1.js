// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S9.2_A2_T1; 
 * @section: 9.2, 15.6.1;
 * @assertion: Result of boolean conversion from null value is false;
 * @description: null convert to Boolean by explicit transformation;
*/

// CHECK#1
if (Boolean(null) !== false) {
  $ERROR('#1: Boolean(null) === false. Actual: ' + (Boolean(null))); 
}
