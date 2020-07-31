// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.2_D1_T2;
* @section: 15.5.2;
* @assertion: String constructor can accept many arguments. But only the first will be accounted ;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
try {
	__str__instance = new String(null,"2",x);
} catch (e) {
	$FAIL('#1: String constructor can accept many arguments');
}
//
//////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (__str__instance != "null") {
	$ERROR('#2: But only the first will be accounted');
}
//
//////////////////////////////////////////////////////////////////////////////

var x;
