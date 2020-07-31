// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.12_A6;
* @section: 15.5.4.12, 13.2;
* @assertion: String.prototype.search has not prototype property;
* @description: Checking String.prototype.search.prototype;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (String.prototype.search.prototype !== undefined) {
  $ERROR('#1: String.prototype.search.prototype === undefined. Actual: '+String.prototype.search.prototype );
}
//
//////////////////////////////////////////////////////////////////////////////
