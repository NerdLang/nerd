// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.23_A1_T3;
 * @section: 15.9.5.23;
 * @assertion: The Date.prototype property "getUTCSeconds" has { DontEnum } attributes;
 * @description: Checking DontEnum attribute;
 */

if (Date.prototype.propertyIsEnumerable('getUTCSeconds')) {
  $ERROR('#1: The Date.prototype.getUTCSeconds property has the attribute DontEnum');
}

for(x in Date.prototype) {
  if(x === "getUTCSeconds") {
    $ERROR('#2: The Date.prototype.getUTCSeconds has the attribute DontEnum');
  }
}

