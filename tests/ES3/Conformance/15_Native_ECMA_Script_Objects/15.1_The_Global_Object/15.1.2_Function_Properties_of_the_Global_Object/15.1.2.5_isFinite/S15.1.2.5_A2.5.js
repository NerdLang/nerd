// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.5_A2.5;
 * @section: 15.1.2.5, 15.2.4.7, 12.6.4;
 * @assertion: The isFinite property has the attribute DontEnum;
 * @description: Checking use propertyIsEnumerable, for-in;
*/


//CHECK#1
if (this.propertyIsEnumerable('isFinite') !== false) {
  $ERROR('#1: this.propertyIsEnumerable(\'isFinite\') === false. Actual: ' + (this.propertyIsEnumerable('isFinite')));
}

//CHECK#2
result = true;
for (p in this){
  if (p === "isFinite") {
    result = false;
  }  
}

if (result !== true) {
  $ERROR('#2: result = true; for (p in this) { if (p === "isFinite") result = false; }  result === true;');
}
