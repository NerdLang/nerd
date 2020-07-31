// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.4.1_A3.2;
* @section: 11.4.1;
* @assertion: If the property doesn't have the DontDelete attribute, return true;
* @description: Checking declared variable; 
*/

//CHECK#1
x = 1;
if (delete x !== true) {
  $ERROR('#1: x = 1; delete x === true');
}

//CHECK#2
function MyFunction(){};
MyFunction.prop = 1;
if (delete MyFunction.prop !== true) {
  $ERROR('#2: function MyFunction(){}; MyFunction.prop = 1; delete MyFunction.prop === true');
}

//CHECK#3
function MyFunction(){};
var MyObject = new MyFunction();
MyObject.prop = 1;
if (delete MyObject.prop !== true) {
  $ERROR('#3: function MyFunction(){}; var MyObject = new MyFunction(); MyFunction.prop = 1; delete MyObject.prop === true');
}
