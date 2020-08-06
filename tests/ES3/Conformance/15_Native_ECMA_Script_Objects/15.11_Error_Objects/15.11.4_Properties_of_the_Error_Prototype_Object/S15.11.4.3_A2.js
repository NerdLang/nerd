// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.11.4.3_A2;
 * @section: 15.11.4.3, 16;
 * @assertion: The initial value of Error.prototype.message is "";
 * @description: Checking value of Error.prototype.message;
*/

//////////////////////////////////////////////////////////////////////////////
// CHECK#1
if (Error.prototype.message!=="") {
	$ERROR('#1: Error.prototype.message==="". Actual: '+Error.prototype.message);
}
//
//////////////////////////////////////////////////////////////////////////////
