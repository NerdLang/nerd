// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.9_A4;
 * @section: 7.9, 12.13;
 * @assertion: Check Throw Statement for automatic semicolon insertion;
 * @description: Try use Throw \n Expression construction; 
 * @negative   
*/

//CHECK#1
try {
  throw 
  1;
} catch(e) {  
}  
$ERROR('#1: Check throw statement for automatic semicolon insertion');
