// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.37_A1_T2;
 * @section: 15.9.5.37;
 * @assertion: The Date.prototype property "setUTCDate" has { DontEnum } attributes;
 * @description: Checking absence of DontDelete attribute;
 */

if (delete Date.prototype.setUTCDate  === false) {
  $ERROR('#1: The Date.prototype.setUTCDate property has not the attributes DontDelete');
}

if (Date.prototype.hasOwnProperty('setUTCDate')) {
  $FAIL('#2: The Date.prototype.setUTCDate property has not the attributes DontDelete');
}

