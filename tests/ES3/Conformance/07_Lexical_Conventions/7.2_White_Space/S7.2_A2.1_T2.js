// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.2_A2.1_T2;
 * @section: 7.2, 7.8.4;
 * @assertion: HORIZONTAL TAB (U+0009) may occur within strings;
 * @description: Use real HORIZONTAL TAB;  
*/

//CHECK#1
if ("	str	ing	" !== "\u0009str\u0009ing\u0009") {
  $ERROR('#1: "	str	ing	" === "\\u0009str\\u0009ing\\u0009"');
}
