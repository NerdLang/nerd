// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.4_A2.1;
 * @section: 15.1.2.4, 15.2.4.7, 12.6.4;
 * @assertion: The length property of isNaN has the attribute DontEnum;
 * @description: Checking use propertyIsEnumerable, for-in;
*/


//CHECK#1
if (isNaN.propertyIsEnumerable('length') !== false) {
  $ERROR('#1: isNaN.propertyIsEnumerable(\'length\') === false. Actual: ' + (isNaN.propertyIsEnumerable('length')));
}

//CHECK#2
result = true;
for (p in isNaN){
  if (p === "length") {
    result = false;
  }  
}

if (result !== true) {
  $ERROR('#2: result = true; for (p in isNaN) { if (p === "length") result = false; }  result === true;');
}
