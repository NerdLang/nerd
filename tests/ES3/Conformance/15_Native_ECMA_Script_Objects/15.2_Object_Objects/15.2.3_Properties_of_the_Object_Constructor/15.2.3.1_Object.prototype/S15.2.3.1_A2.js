// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.2.3.1_A2;
* @section: 15.2.3.1, 15.2.4;
* @assertion: The Object.prototype property has the attribute DontEnum;
* @description: Checking if enumerating "Object.prototype" property fails;
*/

// CHECK#1
if (Object.propertyIsEnumerable('prototype')) {
  $ERROR('#1: the Object.prototype property has the attributes DontEnum');
}

// CHECK#2
cout=0;

for (p in Object){
  if (p==="prototype") cout++;
}

if (cout !== 0) {
  $ERROR('#2: the Object.prototype property has the attributes DontEnum');
}
