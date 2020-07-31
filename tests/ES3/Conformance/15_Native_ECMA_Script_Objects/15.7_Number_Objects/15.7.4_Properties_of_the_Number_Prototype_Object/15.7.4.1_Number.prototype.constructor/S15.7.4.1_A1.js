// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.7.4.1_A1;
 * @section: 15.7.4.1;
 * @assertion: The initial value of Number.prototype.constructor is the 
 * built-in Number constructor;
 * @description: Compare Number.prototype.constructor with Number;
*/

//CHECK#1
if(Number.prototype.constructor !== Number){
  $ERROR('#1: Number.prototype.constructor === Number');
}

