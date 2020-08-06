// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3_A3_T2;
* @section: 15.3;
* @assertion: Since when call is used for Function constructor themself new function instance creates 
* and then first argument(thisArg) should be ignored;
* @description: First argument is string and null;
*/

this.color="red";
name="mars";

f = Function.call("blablastring", "return this.color;");

//CHECK#1
if (f() !== "red") {
  $ERROR('#1: ');
}

g = Function.call(null, "return this.name;");

//CHECK#2
if (g() !== "mars") {
  $ERROR('#2: ');
}

