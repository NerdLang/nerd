// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.16_A10;
* @section: 15.5.4.16;
* @assertion: The String.prototype.toLowerCase.length property has the attribute ReadOnly;
* @description: Checking if varying the String.prototype.toLowerCase.length property fails;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (!(String.prototype.toLowerCase.hasOwnProperty('length'))) {
  $FAIL('#1: String.prototype.toLowerCase.hasOwnProperty(\'length\') return true. Actual: '+String.prototype.toLowerCase.hasOwnProperty('length'));
}
//
//////////////////////////////////////////////////////////////////////////////

__obj = String.prototype.toLowerCase.length;

String.prototype.toLowerCase.length = function(){return "shifted";};

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (String.prototype.toLowerCase.length !== __obj) {
  $ERROR('#2: __obj = String.prototype.toLowerCase.length; String.prototype.toLowerCase.length = function(){return "shifted";}; String.prototype.toLowerCase.length === __obj. Actual: '+String.prototype.toLowerCase.length );
}
//
//////////////////////////////////////////////////////////////////////////////
