// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.17_A1_T6;
* @section: 15.5.4.17;
* @assertion: String.prototype.toLocaleLowerCase();
* @description: Call toLocaleLowerCase() function of Number.NEGATIVE_INFINITY;
*/

Number.prototype.toLocaleLowerCase = String.prototype.toLocaleLowerCase;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if ((Number.NEGATIVE_INFINITY).toLocaleLowerCase() !== "-infinity") {
  $ERROR('#1: Number.prototype.toLocaleLowerCase = String.prototype.toLocaleLowerCase; (Number.NEGATIVE_INFINITY).toLocaleLowerCase() === "-infinity". Actual: '+(Number.NEGATIVE_INFINITY).toLocaleLowerCase() );
}
//
//////////////////////////////////////////////////////////////////////////////
