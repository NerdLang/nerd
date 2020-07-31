// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S13.2_D1.1;
 * @section: 13.2;
 * @assertion: Create a new native ECMAScript object, not joined the already exists object that was created 
 * by an earlier call to this section's algorithm, and if that call to this section's algorithm was given 
 * a FunctionBody that equated to the FunctionBody given now; 
*/

function A(){
  function B(x) { return x*x; }
  return B;
}

var f1 = A();
var f2 = A();

//CHECK#1
if (f1 == f2) {
  $ERROR('#1: Create a new native ECMAScript object, not joined the already exists object');
} else {
  if (f1 === f2) {
    $ERROR('#1: Create a new native ECMAScript object, not joined the already exists object');
  }
}
