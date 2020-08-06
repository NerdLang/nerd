// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.7.3.4_A3;
 * @section: 15.7.3.4;
 * @assertion: Number.NaN is DontDelete;
 * @description: Checking if deleting Number.NaN fails;
*/

// CHECK#1
if (delete Number.NaN !== false) {
  $ERROR('#1: delete Number.NaN === false');
}
