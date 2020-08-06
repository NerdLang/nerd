// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.1.1_A3.1;
 * @section: 15.1.1.1, 11.4.1;
 * @assertion: The NaN is DontDelete;
 * @description: Use delete;
*/

// CHECK#1
if (delete NaN !== false) {
	$ERROR('#1: delete NaN === false. Actual: ' + (delete NaN)); 	
}
