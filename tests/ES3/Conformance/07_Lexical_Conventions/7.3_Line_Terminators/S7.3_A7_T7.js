// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.3_A7_T7;
 * @section: 7.3;
 * @assertion: Line Terminators between operators are allowed;
 * @description: Insert Line Terminator in var x=y<<z;  
*/

// CHECK#1
var y=2;
var z=3;
var
x
=
y
<<
z
;
if (x !== 16) {
  $ERROR('#1: var\\nx\\n=\\ny\\n<<\\nz\\n; x === 16. Actual: ' + (x));
}
x=0;

// CHECK#2
var y=2;
var z=3;
var
x
=
y
<<
z
;
if (x !== 16) {
  $ERROR('#2: var\\nx\\n=\\ny\\n<<\\nz\\n; x ===16 ');
}
x=0;

