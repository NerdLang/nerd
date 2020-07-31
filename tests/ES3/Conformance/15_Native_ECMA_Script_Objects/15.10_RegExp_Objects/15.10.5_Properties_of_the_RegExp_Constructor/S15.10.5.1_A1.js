// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.5.1_A1;
* @section: 15.10.5.1;
* @assertion: The RegExp has property prototype;
* @description: Checking RegExp.prototype property;
*/

//CHECK#1
if (RegExp.hasOwnProperty('prototype') !== true) {
	$ERROR('#1: RegExp.hasOwnProperty(\'prototype\') === true');
}

