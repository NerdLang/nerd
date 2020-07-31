// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.2.7_A1_T9;
* @section: 15.10.2.7;
* @assertion: The production QuantifierPrefix :: { DecimalDigits , DecimalDigits } evaluates as ...;
* @description: Execute /b{42,93}c/.exec("aaabbbbcccddeeeefffff") and check results;
*/

__executed = /b{42,93}c/.test("aaabbbbcccddeeeefffff");

//CHECK#1
if (__executed) {
	$ERROR('#1: /b{42,93}c/.test("aaabbbbcccddeeeefffff") === false');
}

