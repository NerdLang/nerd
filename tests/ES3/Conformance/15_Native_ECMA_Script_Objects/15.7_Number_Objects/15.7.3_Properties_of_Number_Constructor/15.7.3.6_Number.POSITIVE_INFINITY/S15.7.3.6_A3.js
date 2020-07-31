// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.7.3.6_A3;
 * @section: 15.7.3.6;
 * @assertion: Number.POSITIVE_INFINITY is DontDelete;
 * @description: Checking if deleting Number.POSITIVE_INFINITY fails;
*/

// CHECK#1
if (delete Number.POSITIVE_INFINITY !== false) {
  $ERROR('#1: delete Number.POSITIVE_INFINITY === false');
}
