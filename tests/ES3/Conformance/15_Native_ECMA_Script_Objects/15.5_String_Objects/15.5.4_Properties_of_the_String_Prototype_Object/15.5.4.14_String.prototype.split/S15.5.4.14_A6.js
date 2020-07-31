// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.14_A6;
* @section: 15.5.4.14, 13.2;
* @assertion: String.prototype.split has not prototype property;
* @description: Checking String.prototype.split.prototype;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (String.prototype.split.prototype !== undefined) {
  $ERROR('#1: String.prototype.split.prototype === undefined. Actual: '+String.prototype.split.prototype );
}
//
//////////////////////////////////////////////////////////////////////////////
