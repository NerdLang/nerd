// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.39_A1_T3;
 * @section: 15.9.5.39;
 * @assertion: The Date.prototype property "setUTCMonth" has { DontEnum } attributes;
 * @description: Checking DontEnum attribute;
 */

if (Date.prototype.propertyIsEnumerable('setUTCMonth')) {
  $ERROR('#1: The Date.prototype.setUTCMonth property has the attribute DontEnum');
}

for(x in Date.prototype) {
  if(x === "setUTCMonth") {
    $ERROR('#2: The Date.prototype.setUTCMonth has the attribute DontEnum');
  }
}

