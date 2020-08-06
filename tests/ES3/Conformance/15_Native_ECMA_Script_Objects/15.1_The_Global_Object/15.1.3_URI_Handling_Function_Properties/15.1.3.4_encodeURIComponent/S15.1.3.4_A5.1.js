// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.3.4_A5.1;
 * @section: 15.1.3.4, 15.2.4.7, 12.6.4;
 * @assertion: The length property of encodeURIComponent has the attribute DontEnum;
 * @description: Checking use propertyIsEnumerable, for-in;
*/


//CHECK#1
if (encodeURIComponent.propertyIsEnumerable('length') !== false) {
  $ERROR('#1: encodeURIComponent.propertyIsEnumerable(\'length\') === false. Actual: ' + (encodeURIComponent.propertyIsEnumerable('length')));
}

//CHECK#2
result = true;
for (p in encodeURIComponent){
  if (p === "length") {
    result = false;
  }  
}

if (result !== true) {
  $ERROR('#2: result = true; for (p in encodeURIComponent) { if (p === "length") result = false; }  result === true;');
}
