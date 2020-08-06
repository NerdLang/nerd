// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.3.1_A4;
* @section: 15.4.3.1;
* @assertion: The Array.prototype property has the attribute ReadOnly;
* @description: Checking if varying the Array.prototype property fails;
*/

//CHECK#1
x = Array.prototype;
Array.prototype = 1;
if (Array.prototype !== x) {
	$ERROR('#1: x = Array.prototype; Array.prototype = 1; Array.prototype === x. Actual: ' + (Array.prototype));
}

