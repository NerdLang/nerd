// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.5_A1_T3;
 * @section: 15.9.5.5;
 * @assertion: The Date.prototype property "toLocaleString" has { DontEnum } attributes;
 * @description: Checking DontEnum attribute;
 */

if (Date.prototype.propertyIsEnumerable('toLocaleString')) {
  $ERROR('#1: The Date.prototype.toLocaleString property has the attribute DontEnum');
}

for(x in Date.prototype) {
  if(x === "toLocaleString") {
    $ERROR('#2: The Date.prototype.toLocaleString has the attribute DontEnum');
  }
}

