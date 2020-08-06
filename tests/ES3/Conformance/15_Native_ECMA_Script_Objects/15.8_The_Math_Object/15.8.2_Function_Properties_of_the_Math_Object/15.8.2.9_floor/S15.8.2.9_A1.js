// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.8.2.9_A1;
 * @section: 15.8.2.9;
 * @assertion: If x is NaN, Math.floor(x) is NaN;
 * @description: Checking if Math.floor(NaN) is NaN;
 */
 
// CHECK#1
var x = NaN;
if (!isNaN(Math.floor(x)))
{
	$ERROR("#1: 'var x=NaN; isNaN(Math.floor(x)) === false'");
}
