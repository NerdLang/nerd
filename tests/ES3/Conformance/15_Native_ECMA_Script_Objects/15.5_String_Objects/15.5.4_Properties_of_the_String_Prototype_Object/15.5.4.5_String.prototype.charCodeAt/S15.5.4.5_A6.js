// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.5_A6;
* @section: 15.5.4.5, 13.2;
* @assertion: String.prototype.charCodeAt has not prototype property;
* @description: Checking String.prototype.charCodeAt.prototype;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (String.prototype.charCodeAt.prototype !== undefined) {
  $ERROR('#1: String.prototype.charCodeAt.prototype === undefined. Actual: '+String.prototype.charCodeAt.prototype ); 
}
//
//////////////////////////////////////////////////////////////////////////////
