// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.1.2_R1;
 * @section: 15.1.1.2, 9.3;
 * @description: The Infinity is not ReadOnly, check Number for resettability of result;
*/

// CHECK#1
Infinity = false;
Number();
if (Infinity !== false) {
  Infinity = false;
  Number();
  if (Infinity === false) {
    $ERROR('#1: Resettability of result');
  }
} 
