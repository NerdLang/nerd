// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.18_A1_T13;
* @section: 15.5.4.18;
* @assertion: String.prototype.toUpperCase();
* @description: Override toString and valueOf functions, then call toUpperCase() function for this object;
*/

var __obj = {toString:function(){return {};},valueOf:function(){return 1;}}
__obj.toUpperCase = String.prototype.toUpperCase;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__obj.toUpperCase() !=="1") {
  $ERROR('#1: var __obj = {toString:function(){return {};},valueOf:function(){return 1;}}; __obj.toUpperCase = String.prototype.toUpperCase; __obj.toUpperCase() ==="1". Actual: '+__obj.toUpperCase() );
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (__obj.toUpperCase().length !== 1) {
  $ERROR('#2: var __obj = {toString:function(){return {};},valueOf:function(){return 1;}}; __obj.toUpperCase = String.prototype.toUpperCase; __obj.toUpperCase().length === 1. Actual: '+__obj.toUpperCase().length );
}
//
//////////////////////////////////////////////////////////////////////////////
