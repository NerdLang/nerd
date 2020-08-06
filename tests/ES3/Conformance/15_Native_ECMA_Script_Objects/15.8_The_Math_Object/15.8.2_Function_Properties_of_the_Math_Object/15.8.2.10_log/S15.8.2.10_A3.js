// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.8.2.10_A3;
 * @section: 15.8.2.10;
 * @assertion: If x is +0 or -0, Math.log(x) is -Infinity;
 * @description: Checking if Math.log(+0) and Math.log(-0) equals to -Infinity;
 */
 
// CHECK#1
var x = +0;
if (Math.log(x) !== -Infinity)
{
	$ERROR("#1: 'var x=+0; Math.log(x) !== -Infinity'");
}

// CHECK#2
var x = -0;
if (Math.log(x) !== -Infinity)
{
	$ERROR("#1: 'var x=-0; Math.log(x) !== -Infinity'");
}
