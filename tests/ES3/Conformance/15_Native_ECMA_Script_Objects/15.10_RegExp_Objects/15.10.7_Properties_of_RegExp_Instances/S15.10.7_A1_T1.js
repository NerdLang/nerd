// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.7_A1_T1;
* @section: 15.10.7;
* @assertion: RegExp instance has not [[call]] property;
* @description: Checking if call of RegExp instance fails;
*/

//CHECK#1
try {
	$ERROR('#1.1: /[^a]*/() throw TypeError. Actual: ' + (/[^a]*/()));
} catch (e) {
	if ((e instanceof TypeError) !== true) {
		$ERROR('#1.2: /[^a]*/() throw TypeError. Actual: ' + (e));
	}
}

