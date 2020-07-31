// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.9.2_A1_T7;
 * @section: 7.9.2;
 * @assertion: Check examples for automatic semicolon insertion from the Standart;
 * @description: a=b+c \n (d+e).print() is a valid sentence in the ECMAScript grammar,
 * and automatic semicolon insertion not run;
*/

//CHECK#1
function c (a){
	return 2*a;
}

var a=1,b=2,d=4,e=5;

a=b+c
(d+e)

if (a !== 20) $ERROR('#1: Automatic semicolon insertion work wrong');
