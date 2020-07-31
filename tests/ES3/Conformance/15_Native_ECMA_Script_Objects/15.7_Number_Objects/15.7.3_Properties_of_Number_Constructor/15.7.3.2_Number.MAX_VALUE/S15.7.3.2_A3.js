// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.7.3.2_A3;
 * @section: 15.7.3.2;
 * @assertion: Number.MAX_VALUE is DontDelete;
 * @description: Checking if deleting Number.MAX_VALUE fails;
*/

// CHECK#1
if (delete Number.MAX_VALUE !== false) {
  $ERROR('#1: delete Number.MAX_VALUE === false');
}
