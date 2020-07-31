// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.27_A1_T2;
 * @section: 15.9.5.27;
 * @assertion: The Date.prototype property "setTime" has { DontEnum } attributes;
 * @description: Checking absence of DontDelete attribute;
 */

if (delete Date.prototype.setTime  === false) {
  $ERROR('#1: The Date.prototype.setTime property has not the attributes DontDelete');
}

if (Date.prototype.hasOwnProperty('setTime')) {
  $FAIL('#2: The Date.prototype.setTime property has not the attributes DontDelete');
}

