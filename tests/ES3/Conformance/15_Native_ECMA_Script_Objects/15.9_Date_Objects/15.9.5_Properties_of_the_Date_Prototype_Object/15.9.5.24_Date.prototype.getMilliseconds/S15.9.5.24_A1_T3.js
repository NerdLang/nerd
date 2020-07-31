// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.24_A1_T3;
 * @section: 15.9.5.24;
 * @assertion: The Date.prototype property "getMilliseconds" has { DontEnum } attributes;
 * @description: Checking DontEnum attribute;
 */

if (Date.prototype.propertyIsEnumerable('getMilliseconds')) {
  $ERROR('#1: The Date.prototype.getMilliseconds property has the attribute DontEnum');
}

for(x in Date.prototype) {
  if(x === "getMilliseconds") {
    $ERROR('#2: The Date.prototype.getMilliseconds has the attribute DontEnum');
  }
}

