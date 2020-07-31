// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.4.1_A5_T3;
* @section: 15.10.4.1;
* @assertion: If F contains any character other than 'g', 'i', or 'm', or if it contains the same one more than once, then throw a SyntaxError exception;
* @description: Checking by using eval, try to use eval("\"migg\"") as F;
*/

//CHECK#1
try {
	$ERROR('#1.1: new RegExp("",eval("\\"migr\\"")) throw SyntaxError. Actual: ' + (new RegExp("",eval("\"migr\""))));
} catch (e) {
	if ((e instanceof SyntaxError) !== true) {
		$ERROR('#1.2: new RegExp("",eval("\\"migr\\"")) throw SyntaxError. Actual: ' + (e));
	}
}

