// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.3.3.1_A1;
* @section: 15.3.3.1, 15.3.4;
* @assertion: The Function.prototype property has the attribute ReadOnly;
* @description: Checking if varying the Function.prototype property fails;
*/

obj = Function.prototype;
Function.prototype = function(){return "shifted";};

//CHECK#1
if (Function.prototype !== obj) {
  $ERROR('#1: the Function.prototype property has the attributes ReadOnly.');
}

//CHECK#2
try {
  if(Function.prototype()!==undefined){
   $ERROR('#2: the Function.prototype property has the attributes ReadOnly');
  }
} catch (e) {
  $ERROR('#2.1: the Function.prototype property has the attributes ReadOnly: '+e);
}
