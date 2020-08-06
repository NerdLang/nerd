// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.8.2.12_A1;
 * @section: 15.8.2.12;
 * @assertion: If no arguments are given, Math.min() is +Infinity;
 * @description: Checking if Math.min() equals to +Infinity;
 */
 
// CHECK#1
if (Math.min() != +Infinity)
{
	$ERROR("#1: 'Math.min() != +Infinity'");
}
