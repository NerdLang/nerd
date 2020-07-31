// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.11_A3_T3;
 * @section: 15.9.5.11;
 * @assertion: The Date.prototype.getUTCFullYear property "length" has { ReadOnly, DontDelete, DontEnum } attributes;
 * @description: Checking DontEnum attribute;
 */

if (Date.prototype.getUTCFullYear.propertyIsEnumerable('length')) {
  $ERROR('#1: The Date.prototype.getUTCFullYear.length property has the attribute DontEnum');
}

for(x in Date.prototype.getUTCFullYear) {
  if(x === "length") {
    $ERROR('#2: The Date.prototype.getUTCFullYear.length has the attribute DontEnum');
  }
}

