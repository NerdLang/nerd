// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.3_A7_T4;
 * @section: 7.3;
 * @assertion: Line Terminators between operators are allowed;
 * @description: Insert Line Terminator in var x=y/z;  
*/

// CHECK#1
var y=12;
var z=2;
var
x
=
y
/
z
;
if (x !== 6) {
  $ERROR('#1: var\\nx\\n=\\ny\\n/\\nz\\n; x === 6. Actual: ' + (x));
}
x=0;

// CHECK#2
var y=12;
var z=2;
var
x
=
y
/
z
;
if (x !== 6) {
  $ERROR('#2: var\\nx\\n=\\ny\\n/\\nz\\n; x === 6. Actual: ' + (x));
}
x=0;

