// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.2_A3.3_T1;
 * @section: 7.2, 7.4;
 * @assertion: Single line comment can contain FORM FEED (U+000C);
 * @description: Use FORM FEED(\u000C);
 */

// CHECK#1
eval("//\u000C single line \u000C comment \u000C");

//CHECK#2
var x = 0;
eval("//\u000C single line \u000C comment \u000C x = 1;");
if (x !== 0) {
  $ERROR('#1: var x = 0; eval("//\\u000C single line \\u000C comment \\u000C x = 1;"); x === 0. Actual: ' + (x));
}
