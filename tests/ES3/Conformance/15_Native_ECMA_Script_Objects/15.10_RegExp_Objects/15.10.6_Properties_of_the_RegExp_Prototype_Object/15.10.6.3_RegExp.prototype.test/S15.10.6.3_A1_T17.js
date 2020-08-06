// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.6.3_A1_T17;
* @section: 15.10.6.3;
* @assertion: Equivalent to the expression RegExp.prototype.exec(string) != null;
* @description: RegExp is /ll|l/ and tested string is null;
*/

__re = /ll|l/;

//CHECK#0
if (__re.test(null) !== (__re.exec(null) !== null)) {
	$ERROR('#0: __re = /ll|l/; __re.test(null) === (__re.exec(null) !== null)');
}

