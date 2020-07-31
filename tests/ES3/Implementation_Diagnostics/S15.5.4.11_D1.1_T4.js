// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.11_D1.1_T4;
* @section: 15.5.4.11;
* @assertion: String.prototype.replace (searchValue, replaceValue) accepts only two arguments;
* @negative;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
__2 = "1".replace("1","2",null, x);
if (__2 !== "2") {
	$ERROR('#1: String.prototype.replace (searchValue, replaceValue) accepts only two arguments');
}
//
//////////////////////////////////////////////////////////////////////////////

var x;
