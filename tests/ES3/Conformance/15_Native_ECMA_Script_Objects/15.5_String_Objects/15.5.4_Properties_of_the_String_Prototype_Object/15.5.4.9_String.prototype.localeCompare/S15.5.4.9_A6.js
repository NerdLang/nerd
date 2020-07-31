// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.9_A6;
* @section: 15.5.4.9, 13.2;
* @assertion: String.prototype.localeCompare has not prototype property;
* @description: Checking String.prototype.localeCompare.prototype;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (String.prototype.localeCompare.prototype !== undefined) {
  $ERROR('#1: String.prototype.localeCompare.prototype === undefined. Actual: '+String.prototype.localeCompare.prototype );
}
//
//////////////////////////////////////////////////////////////////////////////
