// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.2_D2;
* @section: 15.5.2;
* @assertion: String constructor can't accept many arguments. When more than one is provided exception throws ;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
try {
	__str__instance = new String(1,2,3);
	$FAIL('#1: When more than one is provided exception throws');
} catch (e) {
	$PRINT(e);
}
//
//////////////////////////////////////////////////////////////////////////////

