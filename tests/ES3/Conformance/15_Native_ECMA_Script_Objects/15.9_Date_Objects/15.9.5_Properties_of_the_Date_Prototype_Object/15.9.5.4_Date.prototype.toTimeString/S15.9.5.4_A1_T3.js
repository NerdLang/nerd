// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.4_A1_T3;
 * @section: 15.9.5.4;
 * @assertion: The Date.prototype property "toTimeString" has { DontEnum } attributes;
 * @description: Checking DontEnum attribute;
 */

if (Date.prototype.propertyIsEnumerable('toTimeString')) {
  $ERROR('#1: The Date.prototype.toTimeString property has the attribute DontEnum');
}

for(x in Date.prototype) {
  if(x === "toTimeString") {
    $ERROR('#2: The Date.prototype.toTimeString has the attribute DontEnum');
  }
}

