// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.14_A1_T2;
 * @section: 15.9.5.14;
 * @assertion: The Date.prototype property "getDate" has { DontEnum } attributes;
 * @description: Checking absence of DontDelete attribute;
 */

if (delete Date.prototype.getDate  === false) {
  $ERROR('#1: The Date.prototype.getDate property has not the attributes DontDelete');
}

if (Date.prototype.hasOwnProperty('getDate')) {
  $FAIL('#2: The Date.prototype.getDate property has not the attributes DontDelete');
}

