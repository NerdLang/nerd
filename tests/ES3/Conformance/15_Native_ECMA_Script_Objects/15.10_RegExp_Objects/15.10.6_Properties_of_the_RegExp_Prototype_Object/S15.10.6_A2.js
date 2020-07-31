// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.6_A2;
* @section: 15.10.6;
* @assertion: The value of the internal [[Class]] property of the RegExp prototype object is "Object";
* @description: Checking performs with toString function;
*/

RegExp.prototype.toString = Object.prototype.toString;

//CHECK#1
if (RegExp.prototype.toString() !== "[object " + "Object" + "]") {
	$ERROR('#1: RegExp.prototype.toString = Object.prototype.toString; RegExp.prototype.toString() === "[object " + "Object" + "]". Actual: ' + RegExp.prototype.toString());
}

