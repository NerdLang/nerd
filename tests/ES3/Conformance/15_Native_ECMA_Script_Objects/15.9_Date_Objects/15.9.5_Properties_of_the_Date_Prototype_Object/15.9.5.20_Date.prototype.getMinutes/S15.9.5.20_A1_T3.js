// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.20_A1_T3;
 * @section: 15.9.5.20;
 * @assertion: The Date.prototype property "getMinutes" has { DontEnum } attributes;
 * @description: Checking DontEnum attribute;
 */

if (Date.prototype.propertyIsEnumerable('getMinutes')) {
  $ERROR('#1: The Date.prototype.getMinutes property has the attribute DontEnum');
}

for(x in Date.prototype) {
  if(x === "getMinutes") {
    $ERROR('#2: The Date.prototype.getMinutes has the attribute DontEnum');
  }
}

