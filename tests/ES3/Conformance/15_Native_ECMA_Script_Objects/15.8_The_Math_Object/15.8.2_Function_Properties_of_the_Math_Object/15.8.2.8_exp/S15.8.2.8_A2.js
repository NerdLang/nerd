// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.8.2.8_A2;
 * @section: 15.8.2.8;
 * @assertion: If x is +0, Math.exp(x) is 1;
 * @description: Checking if Math.exp(+0) is 1;
 */
 
// CHECK#1
var x = +0;
if (Math.exp(x) !== 1)
{
	$ERROR("#1: 'var x = +0; Math.exp(x) !== 1'");
}
