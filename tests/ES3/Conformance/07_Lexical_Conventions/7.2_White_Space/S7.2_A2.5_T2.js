// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.2_A2.5_T2;
 * @section: 7.2, 7.8.4;
 * @assertion: NO-BREAK SPACE (U+00A0) may occur within strings;
 * @description: Use real NO-BREAK SPACE;  
*/

//CHECK#1
if (" str ing " !== "\u00A0str\u00A0ing\u00A0") {
  $ERROR('#1: " str ing " === "\\u00A0str\\u00A0ing\\u00A0"');
}
