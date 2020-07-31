// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.26_A3_T2;
 * @section: 15.9.5.26;
 * @assertion: The Date.prototype.getTimezoneOffset property "length" has { ReadOnly, DontDelete, DontEnum } attributes;
 * @description: Checking DontDelete attribute;
 */

if (delete Date.prototype.getTimezoneOffset.length  !== false) {
  $ERROR('#1: The Date.prototype.getTimezoneOffset.length property has the attributes DontDelete');
}

if (!Date.prototype.getTimezoneOffset.hasOwnProperty('length')) {
  $FAIL('#2: The Date.prototype.getTimezoneOffset.length property has the attributes DontDelete');
}

