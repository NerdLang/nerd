// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.8.2.15_A3;
 * @section: 15.8.2.15;
 * @assertion: If x is -0, Math.round(x) is -0;
 * @description: Checking if Math.round(x) equals to -0, where x is -0;
 */
 
// CHECK#1
var x = -0;
if (Math.round(x) !== -0)
{
	$ERROR("#1: 'var x=-0; Math.round(x) !== -0'");
}
