// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.8.2.4_A5;
 * @section: 15.8.2.4;
 * @assertion: If x is -Infinity, Math.atan(x) is an implementation-dependent approximation to -PI/2;
 * @description: Checking if Math.atan(-Infinity) is an approximation to -PI/2;
 */

$INCLUDE("math_precision.js");
$INCLUDE("math_isequal.js"); 
 
// CHECK#1

var x = -Infinity;
if (!isEqual(Math.atan(x), -Math.PI/2))
{
	$ERROR("#1: '!isEqual(Math.atan(-Infinity), -Math.PI/2)'");
}
