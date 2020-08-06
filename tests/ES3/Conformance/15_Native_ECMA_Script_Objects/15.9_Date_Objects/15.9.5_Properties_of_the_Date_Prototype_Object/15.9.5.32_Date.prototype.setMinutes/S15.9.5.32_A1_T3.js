// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.32_A1_T3;
 * @section: 15.9.5.32;
 * @assertion: The Date.prototype property "setMinutes" has { DontEnum } attributes;
 * @description: Checking DontEnum attribute;
 */

if (Date.prototype.propertyIsEnumerable('setMinutes')) {
  $ERROR('#1: The Date.prototype.setMinutes property has the attribute DontEnum');
}

for(x in Date.prototype) {
  if(x === "setMinutes") {
    $ERROR('#2: The Date.prototype.setMinutes has the attribute DontEnum');
  }
}

