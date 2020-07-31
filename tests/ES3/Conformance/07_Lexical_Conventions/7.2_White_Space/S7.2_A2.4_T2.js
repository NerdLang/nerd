// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.2_A2.4_T2;
 * @section: 7.2, 7.8.4;
 * @assertion: SPACE (U+0020) may occur within strings;
 * @description: Use real SPACE;  
*/

//CHECK#1
if (" str ing " !== "\u0020str\u0020ing\u0020") {
  $ERROR('#1: " str ing " === "\\u0020str\\u0020ing\\u0020"');
}
