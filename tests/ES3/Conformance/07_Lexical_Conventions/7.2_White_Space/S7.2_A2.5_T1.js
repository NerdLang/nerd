// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.2_A2.5_T1;
 * @section: 7.2, 7.8.4;
 * @assertion: NO-BREAK SPACE (U+00A0) may occur within strings;
 * @description: Use NO-BREAK SPACE(\u00A0);
*/

// CHECK#1
if (eval("'\u00A0str\u00A0ing\u00A0'") !== "\u00A0str\u00A0ing\u00A0") {
  $ERROR('#1: eval("\'\\u00A0str\\u00A0ing\\u00A0\'") === "\\u00A0str\\u00A0ing\\u00A0"');
}
