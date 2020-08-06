// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.4.3_A1.1_T1;
 * @section: 15.4.3, 15.2.4.5;
 * @assertion: The value of the internal [[Prototype]] property of 
 * the Array constructor is the Function prototype object;
 * @description: Create new property of Function.prototype. When Array constructor has this property; 
*/

Function.prototype.myproperty = 1;

//CHECK#1
if (Array.myproperty !== 1) {
  $ERROR('#1: Function.prototype.myproperty = 1; Array.myproperty === 1. Actual: ' + (Array.myproperty));
}

//CHECK#2
if (Array.hasOwnProperty('myproperty') !== false) {
  $ERROR('#2: Function.prototype.myproperty = 1; Array.hasOwnProperty(\'myproperty\') === false. Actual: ' + (Array.hasOwnProperty('myproperty')));
}
