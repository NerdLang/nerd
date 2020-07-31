// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.8.2.5_A18;
 * @section: 15.8.2.5;
 * @assertion: If y is +Infinity and x is finite, Math.atan2(y,x) is an implementation-dependent approximation to +PI/2;
 * @description: Checking if Math.atan2(y,x) is an approximation to +PI/2, where y is +Infinity and x is finite;
 */

$INCLUDE("math_precision.js");
$INCLUDE("math_isequal.js"); 
 
// CHECK#1
y = +Infinity;
x = new Array();
x[0] = 0.000000000000001;
x[1] = 1;
x[2] = 1.7976931348623157E308; //largest finite number
x[3] = -0.000000000000001;
x[4] = -1;
x[5] = -1.7976931348623157E308; //largest (by module) finite number 
 
xnum = 6;

for (i = 0; i < xnum; i++)
{
	if (!isEqual(Math.atan2(y,x[i]), (Math.PI)/2))
		$FAIL("#1: Math.abs(Math.atan2(" + y + ", " + x[i] + ") - (Math.PI/2)) >= " + prec);
}
