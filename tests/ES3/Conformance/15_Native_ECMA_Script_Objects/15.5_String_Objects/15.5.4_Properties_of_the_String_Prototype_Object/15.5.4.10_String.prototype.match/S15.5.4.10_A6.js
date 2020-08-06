// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.10_A6;
* @section: 15.5.4.10, 13.2;
* @assertion: String.prototype.match has not prototype property;
* @description: Checking String.prototype.match.prototype;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (String.prototype.match.prototype !== undefined) {
  $ERROR('#1: String.prototype.match.prototype === undefined. Actual: '+String.prototype.match.prototype );
}
//
//////////////////////////////////////////////////////////////////////////////
