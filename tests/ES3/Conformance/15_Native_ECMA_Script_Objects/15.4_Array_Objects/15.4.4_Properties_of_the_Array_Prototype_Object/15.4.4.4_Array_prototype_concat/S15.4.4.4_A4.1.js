// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.4_A4.1;
* @section: 15.4.4.4, 15.2.4.7, 12.6.4;
* @assertion: The length property of concat has the attribute DontEnum;
* @description: Checking use propertyIsEnumerable, for-in;
*/


//CHECK#1
if (Array.prototype.concat.propertyIsEnumerable('length') !== false) {
  $ERROR('#1: Array.prototype.concat.propertyIsEnumerable(\'length\') === false. Actual: ' + (Array.prototype.concat.propertyIsEnumerable('length')));
}

//CHECK#2
result = true;
for (p in Array.concat){
  if (p === "length") {
    result = false;
  }  
}

if (result !== true) {
  $ERROR('#2: result = true; for (p in Array.concat) { if (p === "length") result = false; }  result === true;');
}

