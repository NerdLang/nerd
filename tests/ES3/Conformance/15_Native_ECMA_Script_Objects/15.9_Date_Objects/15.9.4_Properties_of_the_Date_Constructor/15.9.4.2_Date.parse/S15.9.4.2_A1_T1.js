// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.4.2_A1_T1;
 * @section: 15.9.4.2;
 * @assertion: The Date property "parse" has { DontEnum } attributes;
 * @description: Checking absence of ReadOnly attribute;
 */

x = Date.parse;
if(x === 1)
  Date.parse = 2;
else
  Date.parse = 1;
if (Date.parse === x) {
  $ERROR('#1: The Date.parse has not the attribute ReadOnly');
}

