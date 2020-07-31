// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.4.2_A1_T3;
 * @section: 15.9.4.2;
 * @assertion: The Date property "parse" has { DontEnum } attributes;
 * @description: Checking DontEnum attribute;
 */

if (Date.propertyIsEnumerable('parse')) {
  $ERROR('#1: The Date.parse property has the attribute DontEnum');
}

for(x in Date) {
  if(x === "parse") {
    $ERROR('#2: The Date.parse has the attribute DontEnum');
  }
}

