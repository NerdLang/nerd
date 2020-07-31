// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3_A2_T2;
* @section: 15.3, 10.2.3, 15.3.2.1;
* @assertion: Since applying the "call" method to Function constructor themself leads to creating a new function instance, the second argument must be a valid function body;
* @description: Checking if executing "Function.call(this, "var #x  = 1;")" fails;
*/

//CHECK#
try{
  Function.call(this, "var #x  = 1;");
} catch(e){
  if (!(e instanceof SyntaxError)) {
  	$ERROR('#1: function body must be valid');
  }
}    

