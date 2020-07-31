// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.4.1_A2_T1;
* @section: 15.10.4.1;
* @assertion: If pattern is an object R whose [[Class]] property is "RegExp" and flags is not undefined, then throw a TypeError exception;
* @description: Checking if execution of "new RegExp(pattern, "i")", where the pattern is "/\u0042/i", fails;
*/

//CHECK#1
try {
	$ERROR('#1.1: new RegExp(/\\u0042/i, "i") throw TypeError. Actual: ' + (new RegExp(/\u0042/i, "i"))); 
} catch (e) {
	if ((e instanceof TypeError) !== true) {
		$ERROR('#1.2: new RegExp(/\\u0042/i, "i") throw TypeError. Actual: ' + (e));
	}
}

