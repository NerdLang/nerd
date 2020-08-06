// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.11.4_A2;
* @section: 15.11.4, 16;
* @assertion: The value of the internal [[Class]] property of Error prototype object is "Error";
* @description: Getting the value of the internal [[Class]] property using Error.prototype.toString() function; 
*/

Error.prototype.toString=Object.prototype.toString;
__tostr = Error.prototype.toString();

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__tostr !== "[object Error]") {
	$ERROR('#1: Error.prototype.toString=Object.prototype.toString; __tostr = Error.prototype.toString(); __tostr === "[object Error]". Actual: '+__tostr );
}
//
//////////////////////////////////////////////////////////////////////////////
