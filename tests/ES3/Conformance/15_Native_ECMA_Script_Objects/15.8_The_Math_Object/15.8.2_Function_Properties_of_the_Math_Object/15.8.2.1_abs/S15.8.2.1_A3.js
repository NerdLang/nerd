// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.8.2.1_A3;
 * @section: 15.8.2.1;
 * @assertion: If x is -Infinity, Math.abs(x) is +Infinity;
 * @description: Checking if Math.abs(-Infinity) equals to +Infinity;
 */
 
// CHECK#1
var x = -Infinity;
if (Math.abs(x) !== +Infinity)
{
	$ERROR("#1: 'var x=-Infinity; Math.abs(x) !== +Infinity'");
}
