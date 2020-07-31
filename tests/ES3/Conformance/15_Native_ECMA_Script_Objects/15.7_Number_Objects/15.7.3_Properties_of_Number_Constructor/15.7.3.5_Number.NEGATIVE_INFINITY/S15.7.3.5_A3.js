// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.7.3.5_A3;
 * @section: 15.7.3.5;
 * @assertion: Number.NEGATIVE_INFINITY is DontDelete;
 * @description: Checking if deleting Number.NEGATIVE_INFINITY fails;
*/

// CHECK#1
if (delete Number.NEGATIVE_INFINITY !== false) {
  $ERROR('#1: delete Number.NEGATIVE_INFINITY === false');
}
