// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.19_A10;
* @section: 15.5.4.19;
* @assertion: The String.prototype.toLocaleUpperCase.length property has the attribute ReadOnly;
* @description: Checking if varying the String.prototype.toLocaleUpperCase.length property fails;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (!(String.prototype.toLocaleUpperCase.hasOwnProperty('length'))) {
  $FAIL('#1: String.prototype.toLocaleUpperCase.hasOwnProperty(\'length\') return true. Actual: '+String.prototype.toLocaleUpperCase.hasOwnProperty('length'));
}
//
//////////////////////////////////////////////////////////////////////////////

__obj = String.prototype.toLocaleUpperCase.length;

String.prototype.toLocaleUpperCase.length = function(){return "shifted";};

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (String.prototype.toLocaleUpperCase.length !== __obj) {
  $ERROR('#2: __obj = String.prototype.toLocaleUpperCase.length; String.prototype.toLocaleUpperCase.length = function(){return "shifted";}; String.prototype.toLocaleUpperCase.length === __obj. Actual: '+String.prototype.toLocaleUpperCase.length );
}
//
//////////////////////////////////////////////////////////////////////////////
