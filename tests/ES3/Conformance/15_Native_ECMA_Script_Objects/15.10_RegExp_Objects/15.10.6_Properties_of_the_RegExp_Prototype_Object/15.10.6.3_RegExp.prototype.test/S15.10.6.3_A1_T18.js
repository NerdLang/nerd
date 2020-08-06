// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.6.3_A1_T18;
* @section: 15.10.6.3;
* @assertion: Equivalent to the expression RegExp.prototype.exec(string) != null;
* @description: RegExp is /nd|ne/ and tested string is undefined;
*/

__re = /nd|ne/;

//CHECK#0
if (__re.test(undefined) !== (__re.exec(undefined) !== null)) {
	$ERROR('#0: __re = /nd|ne/; __re.test(undefined) === (__re.exec(undefined) !== null)');
}

