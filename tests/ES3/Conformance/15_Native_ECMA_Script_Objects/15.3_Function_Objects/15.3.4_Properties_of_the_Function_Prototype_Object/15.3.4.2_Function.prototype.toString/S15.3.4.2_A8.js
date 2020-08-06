// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3.4.2_A8;
* @section: 15.3.4.2;
* @assertion: The Function.prototype.toString.length property has the attribute DontEnum;
* @description: Checking if enumerating the Function.prototype.toString.length property fails;
*/

//CHECK#0
if (!(Function.prototype.toString.hasOwnProperty('length'))) {
  $FAIL('#0: the Function.prototype.toString has length property.');
}


// CHECK#1
if (Function.prototype.toString.propertyIsEnumerable('length')) {
  $ERROR('#1: the Function.prototype.toString.length property has the attributes DontEnum');
}

// CHECK#2
for (p in Function.prototype.toString){
  if (p==="length")
      $ERROR('#2: the Function.prototype.toString.length property has the attributes DontEnum');
}
