// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.37_A1_T3;
 * @section: 15.9.5.37;
 * @assertion: The Date.prototype property "setUTCDate" has { DontEnum } attributes;
 * @description: Checking DontEnum attribute;
 */

if (Date.prototype.propertyIsEnumerable('setUTCDate')) {
  $ERROR('#1: The Date.prototype.setUTCDate property has the attribute DontEnum');
}

for(x in Date.prototype) {
  if(x === "setUTCDate") {
    $ERROR('#2: The Date.prototype.setUTCDate has the attribute DontEnum');
  }
}

