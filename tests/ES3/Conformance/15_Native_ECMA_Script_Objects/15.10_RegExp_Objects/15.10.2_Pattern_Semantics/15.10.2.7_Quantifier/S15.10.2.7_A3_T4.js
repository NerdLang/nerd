// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.2.7_A3_T4;
* @section: 15.10.2.7;
* @assertion: The production QuantifierPrefix :: + evaluates by returning the two results 1 and \infty;
* @description: Execute /\s+java\s+/.test("java\n\nobject") and check results;
*/

__executed = /\s+java\s+/.test("java\n\nobject");

//CHECK#1
if (__executed) {
	$ERROR('#1: /\\s+java\\s+/.test("java\\n\\nobject") === false');
}

