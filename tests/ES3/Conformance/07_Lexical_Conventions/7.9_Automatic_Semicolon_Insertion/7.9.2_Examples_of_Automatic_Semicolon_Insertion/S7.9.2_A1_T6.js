// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.9.2_A1_T6;
 * @section: 7.9.2;
 * @assertion: Check examples for automatic semicolon insertion from the Standart;
 * @description: if(a>b) \n else c=d is not a valid sentence in the ECMAScript grammar;
 * @negative;   
*/

//CHECK#1
var a=1,b=2,c=3,d;
if(a>b)
else c=d
