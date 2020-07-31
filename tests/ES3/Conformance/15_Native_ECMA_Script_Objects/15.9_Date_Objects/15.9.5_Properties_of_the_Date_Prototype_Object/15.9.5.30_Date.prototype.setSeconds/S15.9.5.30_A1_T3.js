// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.30_A1_T3;
 * @section: 15.9.5.30;
 * @assertion: The Date.prototype property "setSeconds" has { DontEnum } attributes;
 * @description: Checking DontEnum attribute;
 */

if (Date.prototype.propertyIsEnumerable('setSeconds')) {
  $ERROR('#1: The Date.prototype.setSeconds property has the attribute DontEnum');
}

for(x in Date.prototype) {
  if(x === "setSeconds") {
    $ERROR('#2: The Date.prototype.setSeconds has the attribute DontEnum');
  }
}

