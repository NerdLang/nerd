// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.7.2.1_A4;
 * @section: 15.7.2.1;
 * @assertion: The [[Class]] property of the newly constructed object 
 * is set to "Number";
 * @description: For testing toString function is used;
*/

delete Number.prototype.toString;

var obj = new Number();

//CHECK#1
if (obj.toString() !== "[object Number]") {
  $ERROR('#1: The [[Class]] property of the newly constructed object is set to "Number"');
}
