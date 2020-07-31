// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.4.4.1_A2;
 * @section: 15.4.4.1, 15.2.4.7, 12.6.4;
 * @assertion: The constructor property of Array has the attribute DontEnum;
 * @description: Checking use propertyIsEnumerable, for-in;
*/


//CHECK#1
if (Array.propertyIsEnumerable('constructor') !== false) {
  $ERROR('#1: Array.propertyIsEnumerable(\'constructor\') === false. Actual: ' + (Array.propertyIsEnumerable('constructor')));
}

//CHECK#2
result = true;
for (p in Array){
  if (p === "constructor") {
    result = false;
  }  
}

if (result !== true) {
  $ERROR('#2: result = true; for (p in Array) { if (p === "constructor") result = false; }  result === true;');
}

