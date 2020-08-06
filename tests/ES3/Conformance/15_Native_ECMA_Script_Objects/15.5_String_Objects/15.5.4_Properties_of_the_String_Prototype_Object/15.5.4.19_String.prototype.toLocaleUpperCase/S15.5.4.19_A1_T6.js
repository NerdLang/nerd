// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.19_A1_T6;
* @section: 15.5.4.19;
* @assertion: String.prototype.toLocaleUpperCase();
* @description: Call toLocaleUpperCase() function of Number.NEGATIVE_INFINITY;
*/

Number.prototype.toLocaleUpperCase = String.prototype.toLocaleUpperCase;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if ((Number.NEGATIVE_INFINITY).toLocaleUpperCase() !== "-INFINITY") {
  $ERROR('#1: Number.prototype.toLocaleUpperCase = String.prototype.toLocaleUpperCase; (Number.NEGATIVE_INFINITY).toLocaleUpperCase() === "-INFINITY". Actual: '+(Number.NEGATIVE_INFINITY).toLocaleUpperCase() );
}
//
//////////////////////////////////////////////////////////////////////////////

