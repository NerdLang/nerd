// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.12_A1_T3;
 * @section: 15.9.5.12;
 * @assertion: The Date.prototype property "getMonth" has { DontEnum } attributes;
 * @description: Checking DontEnum attribute;
 */

if (Date.prototype.propertyIsEnumerable('getMonth')) {
  $ERROR('#1: The Date.prototype.getMonth property has the attribute DontEnum');
}

for(x in Date.prototype) {
  if(x === "getMonth") {
    $ERROR('#2: The Date.prototype.getMonth has the attribute DontEnum');
  }
}

