// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.7.1_A9;
* @section: 15.10.7.1;
* @assertion: The RegExp instance source property has the attribute DontDelete;
* @description: Checking if deleting the source property fails;
*/

__re = new RegExp;

//CHECK#0
if (__re.hasOwnProperty('source') !== true) {
	$FAIL('#0: __re = new RegExp; __re.hasOwnProperty(\'source\') === true');
}

//CHECK#1
if ((delete __re.source) !== false) {
	$ERROR('#1: __re = new RegExp; (delete __re.source) === false');
}

//CHECK#2
if (__re.hasOwnProperty('source') !== true) {
	$ERROR('#2: __re = new RegExp;delete __re.source === true; __re.hasOwnProperty(\'source\') === true');
}

