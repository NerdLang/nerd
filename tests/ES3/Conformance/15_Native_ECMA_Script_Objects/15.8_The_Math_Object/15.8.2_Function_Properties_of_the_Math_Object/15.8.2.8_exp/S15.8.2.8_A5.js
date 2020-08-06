// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.8.2.8_A5;
 * @section: 15.8.2.8;
 * @assertion: If x is -Infinity, Math.exp(x) is +0;
 * @description: Checking if Math.exp(-Infinity) is +0;
 */
 
// CHECK#1
var x = -Infinity;
if (Math.exp(x) !== +0)
{
	$ERROR("#1: 'var x = -Infinity; Math.exp(x) !== +0'");
}
