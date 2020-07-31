// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S11.4.3_D1.1;
 * @section: 11.4.3;
 * @assertion: Result of typeof from RegExp is "function"; 
*/

// CHECK#1
if (typeof RegExp !== "function") {
  $ERROR('#1: Result of typeof from RegExp is "function"');
}
