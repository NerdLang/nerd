// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.33_A1_T3;
 * @section: 15.9.5.33;
 * @assertion: The Date.prototype property "setUTCMinutes" has { DontEnum } attributes;
 * @description: Checking DontEnum attribute;
 */

if (Date.prototype.propertyIsEnumerable('setUTCMinutes')) {
  $ERROR('#1: The Date.prototype.setUTCMinutes property has the attribute DontEnum');
}

for(x in Date.prototype) {
  if(x === "setUTCMinutes") {
    $ERROR('#2: The Date.prototype.setUTCMinutes has the attribute DontEnum');
  }
}

