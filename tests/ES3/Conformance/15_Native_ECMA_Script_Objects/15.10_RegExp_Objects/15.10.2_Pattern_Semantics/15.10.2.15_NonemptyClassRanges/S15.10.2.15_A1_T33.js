// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.2.15_A1_T33;
* @section: 15.10.2.15;
* @assertion: The internal helper function CharacterRange takes two CharSet parameters A and B and performs the 
* following: 
* If A does not contain exactly one character or B does not contain exactly one character then throw 
* a SyntaxError exception;
* @description: Checking if execution of "/[d-G\t]/.exec("a")" leads to throwing the correct exception;
*/

//CHECK#1
try {
  $ERROR('#1.1: /[d-G\\t]/.exec("a") throw SyntaxError. Actual: ' + (/[d-G\t]/.exec("a")));
} catch (e) {
  if((e instanceof SyntaxError) !== true){
    $ERROR('#1.2: /[d-G\\t]/.exec("a") throw SyntaxError. Actual: ' + (e));
  }
}

