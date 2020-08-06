// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.2.3_A1_T7;
* @section: 15.10.2.3;
* @assertion: The | regular expression operator separates two alternatives. 
* The pattern first tries to match the left Alternative (followed by the sequel of the regular expression).
* If it fails, it tries to match the right Disjunction (followed by the sequel of the regular expression);
* @description: Execute /ab|cd|ef/.test("AEKFCD") and check results;
*/

__executed = /ab|cd|ef/.test("AEKFCD");

//CHECK#1
if (__executed) {
	$ERROR('#1: /ab|cd|ef/.test("AEKFCD") === false');
}

