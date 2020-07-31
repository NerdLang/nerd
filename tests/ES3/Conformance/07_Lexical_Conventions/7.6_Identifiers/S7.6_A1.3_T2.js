// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.6_A1.3_T2;
 * @section: 7.6;
 * @assertion: IdentifierStart :: _; 
 * @description: The _ as unicode character \u005F;  
*/

//CHECK#1
var \u005F = 1;
if (_ !== 1) {
  $ERROR('#1: var \\u005F = 1; _ === 1. Actual: ' + (_));
}
