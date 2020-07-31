// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.4.3.1_A3;
* @section: 15.4.3.1, 15.2.4.5;
* @assertion: The Array.prototype property has the attribute DontDelete;
* @description: Checking if deleting the Array.prototype property fails;
*/

//CHECK#1
if (Array.hasOwnProperty('prototype') !== true) {
	$FAIL('#1: Array.hasOwnProperty(\'prototype\') === true. Actual: ' + (Array.hasOwnProperty('prototype')));
}

delete Array.prototype;

//CHECK#2
if (Array.hasOwnProperty('prototype') !== true) {
	$ERROR('#2: delete Array.prototype; Array.hasOwnProperty(\'prototype\') === true. Actual: ' + (Array.hasOwnProperty('prototype')));
}

//CHECK#3
if (Array.prototype === undefined) {
  $ERROR('#3: delete Array.prototype; Array.prototype !== undefined');
}


