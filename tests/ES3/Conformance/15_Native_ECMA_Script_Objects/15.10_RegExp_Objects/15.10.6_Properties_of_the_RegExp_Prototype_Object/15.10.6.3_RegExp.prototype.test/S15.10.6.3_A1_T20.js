// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.6.3_A1_T20;
* @section: 15.10.6.3;
* @assertion: Equivalent to the expression RegExp.prototype.exec(string) != null;
* @description: RegExp is /[a-f]d/ and tested string is x, where x is undefined;
*/

__re = /[a-f]d/;

//CHECK#0
if (__re.test(x) !== (__re.exec(x) !== null)) {
	$ERROR('#0: __re = /[a-f]d/; __re.test(x) === (__re.exec(x) !== null); var x;');
}

var x;
