// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.1.3_A2_T2;
 * @section: 15.1.1.3, 11.4.3;
 * @assertion: The undefined is not ReadOnly;
 * @description: Checking typeof Operator; 
*/

// CHECK#1
undefined = true;
if (typeof(undefined) !== "boolean") { 
	$ERROR('#1: undefined = true; typeof(undefined) === "boolean". Actual: ' + (typeof(undefined)));	
}
