// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.8.2.13_A8;
 * @section: 15.8.2.13;
 * @assertion: If abs(x)==1 and y is -Infinity, Math.pow(x,y) is NaN;
 * @description: Checking if Math.pow(x,y) is NaN, where abs(x)==1 and y is -Infinity;
 */
 
// CHECK#1

y = -Infinity;
x = new Array();
x[0] = -1;
x[1] = 1
xnum = 2;

for (i = 0; i < xnum; i++)
{
	if (!isNaN(Math.pow(x[i],y)))
	{
		$FAIL("#1: isNaN(Math.pow(" + x[i] + ", " + y + ")) === false");
	}
}
