// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3_A3_T5;
* @section: 15.3, 10.2.3;
* @assertion: Since when call is used for Function constructor themself new function instance creates 
* and then first argument(thisArg) should be ignored;
* @description: First argument is this, and this don`t have needed variable. Function return this.var_name;
*/

f=Function.call(this, "return this.planet;");
g=Function.call(this, "return this.color;");

//CHECK#1
if (f() !== undefined) {
  $ERROR('#2: ');
}

planet="mars";

//CHECK#2
if (f() !== "mars") {
  $ERROR('#2: ');
}

//CHECK#3
if (g() !== undefined) {
  $ERROR('#3: ');
}   

this.color="red";

//CHECK#4
if (g() !== "red") {
  $ERROR('#4: ');
}
