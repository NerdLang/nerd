// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.8.1_A1_T1;
 * @section: 7.8.1;
 * @assertion: Literal :: NullLiteral;
 * @description: Check null === null;   
*/

//CHECK#1
if (null !== null) {
  $ERROR('#1: null === null');
} 
