// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.4.4_A4.5;
* @section: 15.4.4.4, 15.2.4.7, 12.6.4;
* @assertion: The concat property of Array has the attribute DontEnum;
* @description: Checking use propertyIsEnumerable, for-in;
*/


//CHECK#1
if (Array.propertyIsEnumerable('concat') !== false) {
  $ERROR('#1: Array.propertyIsEnumerable(\'concat\') === false. Actual: ' + (Array.propertyIsEnumerable('concat')));
}

//CHECK#2
result = true;
for (p in Array){
  if (p === "concat") {
    result = false;
  }  
}

if (result !== true) {
  $ERROR('#2: result = true; for (p in Array) { if (p === "concat") result = false; }  result === true;');
}

