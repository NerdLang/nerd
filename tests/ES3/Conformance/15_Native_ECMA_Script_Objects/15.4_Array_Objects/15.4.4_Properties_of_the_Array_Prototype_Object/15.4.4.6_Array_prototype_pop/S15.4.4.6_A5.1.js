// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.6_A5.1;
* @section: 15.4.4.6, 15.2.4.7, 12.6.4;
* @assertion: The length property of pop has the attribute DontEnum;
* @description: Checking use propertyIsEnumerable, for-in;
*/


//CHECK#1
if (Array.prototype.pop.propertyIsEnumerable('length') !== false) {
  $ERROR('#1: Array.prototype.pop.propertyIsEnumerable(\'length\') === false. Actual: ' + (Array.prototype.pop.propertyIsEnumerable('length')));
}

//CHECK#2
result = true;
for (p in Array.pop){
  if (p === "length") {
    result = false;
  }  
}

if (result !== true) {
  $ERROR('#2: result = true; for (p in Array.pop) { if (p === "length") result = false; }  result === true;');
}

