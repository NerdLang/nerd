// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.2_A4.3_T2;
 * @section: 7.2, 7.4;
 * @assertion: Multi line comment can contain FORM FEED (U+000C);
 * @description: Use real FORM FEED;
 */

/*CHECK#1*/
var x = 0;
/*multilinecommentx = 1;*/
if (x !== 0) {
  $ERROR('#1: var x = 0; /*multilinecommentx = 1;*/ x === 0. Actual: ' + (x));
}
