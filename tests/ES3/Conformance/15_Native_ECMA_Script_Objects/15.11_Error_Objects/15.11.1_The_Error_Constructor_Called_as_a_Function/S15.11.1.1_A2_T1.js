// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.11.1.1_A2_T1;
* @section: 15.11.1.1, 16;
* @assertion: The [[Prototype]] property of the newly constructed object is set to the original Error prototype 
* object, the one that is the initial value of Error.prototype (15.11.3.1);
* @description: Checking prototype of the newly constructed Error object;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
var err1=Error('msg1');
if(!Error.prototype.isPrototypeOf(err1)){
  $ERROR('#1: var err1=Error(\'msg1\'); Error.prototype.isPrototypeOf(err1) return true. Actual: '+Error.prototype.isPrototypeOf(err1));
}
//
//////////////////////////////////////////////////////////////////////////////
