// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.18_A6;
* @section: 15.5.4.18, 13.2;
* @assertion: String.prototype.toUpperCase has not prototype property;
* @description: Checking String.prototype.toUpperCase.prototype;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (String.prototype.toUpperCase.prototype !== undefined) {
  $ERROR('#1: String.prototype.toUpperCase.prototype === undefined. Actual: '+String.prototype.toUpperCase.prototype );
}
//
//////////////////////////////////////////////////////////////////////////////
