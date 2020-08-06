// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.1_A1_T16;
* @section: 15.10.1;
* @assertion: RegExp syntax errors must be caught when matcher(s) compiles;
* @description: Tested RegExp is "x{0,1}{1,}";
*/

//CHECK#1
try {
	$ERROR('#1.1: new RegExp("x{0,1}{1,}") throw SyntaxError. Actual: ' + (new RegExp("x{0,1}{1,}")));
} catch (e) {
	if ((e instanceof SyntaxError) !== true) {
		$ERROR('#1.2: new RegExp("x{0,1}{1,}") throw SyntaxError. Actual: ' + (e));
	}
}

