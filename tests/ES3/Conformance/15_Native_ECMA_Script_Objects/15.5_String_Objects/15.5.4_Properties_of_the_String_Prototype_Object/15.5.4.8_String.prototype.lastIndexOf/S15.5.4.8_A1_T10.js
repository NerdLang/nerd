// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.8_A1_T10;
* @section: 15.5.4.8;
* @assertion: String.prototype.lastIndexOf(searchString, position);
* @description: Call lastIndexOf(searchString, position) function with object arguments;
*/

var __obj = {toString:function(){return "\u0041B";}}
var __obj2 = {valueOf:function(){return NaN;}}
var __str = "ABB\u0041BABAB";

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
with(__str){
  if (lastIndexOf(__obj, __obj2) !== 7) {
    $ERROR('#1: var x; var __obj = {toString:function(){return "\u0041B";}}; var __obj2 = {valueOf:function(){return NaN;}}; var __str = "ABB\u0041BABAB";lastIndexOf(__obj, __obj2) === 7. Actual: '+lastIndexOf(__obj, __obj2) );
  }
}
//
//////////////////////////////////////////////////////////////////////////////

var x;
