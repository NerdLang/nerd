// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.8.2.11_A3;
 * @section: 15.8.2.11;
 * @assertion: +0 is considered to be larger than -0;
 * @description: Checking if Math.max(-0,+0) and Math.max(+0,-0) equals to +0;
 */
 
// CHECK#1
if (Math.max(-0, +0) !== +0)
{
	$ERROR("#1: 'Math.max(-0, +0) !== +0'");
}

// CHECK#1
if (Math.max(+0, -0) !== +0)
{
	$ERROR("#2: 'Math.max(+0, -0) !== +0'");
}
