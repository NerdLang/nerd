// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.19_A9;
* @section: 15.5.4.19;
* @assertion: The String.prototype.toLocaleUpperCase.length property has the attribute DontDelete;
* @description: Checking if deleting the String.prototype.toLocaleUpperCase.length property fails;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#0
if (!(String.prototype.toLocaleUpperCase.hasOwnProperty('length'))) {
  $FAIL('#0: String.prototype.toLocaleUpperCase.hasOwnProperty(\'length\') return true. Actual: '+String.prototype.toLocaleUpperCase.hasOwnProperty('length'));
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (delete String.prototype.toLocaleUpperCase.length) {
  $ERROR('#1: delete String.prototype.toLocaleUpperCase.length return false');
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (!(String.prototype.toLocaleUpperCase.hasOwnProperty('length'))) {
  $FAIL('#2: delete String.prototype.toLocaleUpperCase.length; String.prototype.toLocaleUpperCase.hasOwnProperty(\'length\') return true. Actual: '+String.prototype.toLocaleUpperCase.hasOwnProperty('length'));
}
//
//////////////////////////////////////////////////////////////////////////////
