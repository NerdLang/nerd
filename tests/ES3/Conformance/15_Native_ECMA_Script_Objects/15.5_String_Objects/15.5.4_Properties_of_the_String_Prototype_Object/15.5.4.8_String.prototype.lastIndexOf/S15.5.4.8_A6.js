// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.8_A6;
* @section: 15.5.4.8, 13.2;
* @assertion: String.prototype.lastIndexOf has not prototype property;
* @description: Checking String.prototype.lastIndexOf.prototype;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (String.prototype.lastIndexOf.prototype !== undefined) {
  $ERROR('#1: String.prototype.lastIndexOf.prototype === undefined. Actual: '+String.prototype.lastIndexOf.prototype );
}
//
//////////////////////////////////////////////////////////////////////////////
