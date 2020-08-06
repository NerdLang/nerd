// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.5.1_A3;
* @section: 15.10.5.1;
* @assertion: The RegExp.prototype property has the attribute DontDelete;
* @description: Checking if deleting the RegExp.prototype property fails;
*/

//CHECK#0
if (RegExp.hasOwnProperty('prototype') !== true) {
	$FAIL('#0: RegExp.hasOwnProperty(\'prototype\') === true');
}

//CHECK#1
if (delete RegExp.prototype !== false) {
  $ERROR('#1: delete RegExp.prototype === false');
}

//CHECK#2
if (RegExp.hasOwnProperty('prototype') !== true) {
	$ERROR('#2: delete RegExp.prototype; RegExp.hasOwnProperty(\'prototype\') === true');
}

