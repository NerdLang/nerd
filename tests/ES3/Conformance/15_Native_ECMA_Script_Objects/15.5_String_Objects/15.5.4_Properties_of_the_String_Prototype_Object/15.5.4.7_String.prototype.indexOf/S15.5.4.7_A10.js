// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.7_A10;
* @section: 15.5.4.7;
* @assertion: The String.prototype.indexOf.length property has the attribute ReadOnly;
* @description: Checking if varying the String.prototype.indexOf.length property fails;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (!(String.prototype.indexOf.hasOwnProperty('length'))) {
  $FAIL('#1: String.prototype.indexOf.hasOwnProperty(\'length\') return true. Actual: '+String.prototype.indexOf.hasOwnProperty('length')); 
}
//
//////////////////////////////////////////////////////////////////////////////

__obj = String.prototype.indexOf.length;

String.prototype.indexOf.length = function(){return "shifted";};

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (String.prototype.indexOf.length !== __obj) {
  $ERROR('#2: __obj = String.prototype.indexOf.length; String.prototype.indexOf.length = function(){return "shifted";}; String.prototype.indexOf.length === __obj. Actual: '+String.prototype.indexOf.length ); 
}
//
//////////////////////////////////////////////////////////////////////////////
