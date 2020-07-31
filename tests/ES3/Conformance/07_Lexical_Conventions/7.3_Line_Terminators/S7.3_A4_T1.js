// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/** * @name: S7.3_A4_T1; * @section: 7.3, 7.4; * @assertion: Single line comments can contain Line Terminator at the end of line; * @description: Insert LINE FEED (U+000A) into the end of single line comment; */// CHECK#1eval("// single line comment\u000A");// CHECK#2var x = 0;eval("// single line comment\u000A x = 1;");if (x !== 1) {  $ERROR('#1: var x = 0; eval("// single line comment\\u000A x = 1;"); x === 1. Actual: ' + (x));}
