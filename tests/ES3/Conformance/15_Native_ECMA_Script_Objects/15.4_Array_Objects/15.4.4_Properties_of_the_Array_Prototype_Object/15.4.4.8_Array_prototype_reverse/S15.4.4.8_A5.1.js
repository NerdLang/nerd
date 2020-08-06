// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.8_A5.1;
* @section: 15.4.4.8, 15.2.4.7, 12.6.4;
* @assertion: The length property of reverse has the attribute DontEnum;
* @description: Checking use propertyIsEnumerable, for-in;
*/


//CHECK#1
if (Array.prototype.reverse.propertyIsEnumerable('length') !== false) {
  $ERROR('#1: Array.prototype.reverse.propertyIsEnumerable(\'length\') === false. Actual: ' + (Array.prototype.reverse.propertyIsEnumerable('length')));
}

//CHECK#2
result = true;
for (p in Array.reverse){
  if (p === "length") {
    result = false;
  }  
}

if (result !== true) {
  $ERROR('#2: result = true; for (p in Array.reverse) { if (p === "length") result = false; }  result === true;');
}

