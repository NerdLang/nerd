// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.6_A6;
* @section: 15.5.4.6, 13.2;
* @assertion: String.prototype.concat has not prototype property;
* @description: Checking String.prototype.concat.prototype;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (String.prototype.concat.prototype !== undefined) {
  $ERROR('#1: String.prototype.concat.prototype === undefined. Actual: '+String.prototype.concat.prototype ); 
}
//
//////////////////////////////////////////////////////////////////////////////
