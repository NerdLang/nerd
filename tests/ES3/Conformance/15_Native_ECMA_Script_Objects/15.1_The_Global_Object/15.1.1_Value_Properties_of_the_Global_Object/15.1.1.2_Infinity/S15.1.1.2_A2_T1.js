// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.1.2_A2_T1;
 * @section: 15.1.1.2, 15.5.1, 15.6.1, 15.7.1;
 * @assertion: The Infinity is not ReadOnly;
 * @description: Checking Boolean, Number, String Functions; 
*/

// CHECK#1
Infinity = 0;
if (Boolean(Infinity) !== false) {
	$ERROR('#1: Infinity = 0; Boolean(Infinity) === false. Actual: ' + (Boolean(Infinity))); 
}

// CHECK#2
Infinity = false;
if (Number(Infinity) !== 0) {
	$ERROR('#2: Infinity = false; Number(Infinity) === 0. Actual: ' + (Number(Infinity))); 
}

// CHECK#3
Infinity = 0;
if (String(Infinity) !== "0") {
	$ERROR('#3: Infinity = 0; String(Infinity) === "0". Actual: ' + (String(Infinity))); 
}

