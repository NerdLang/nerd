// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.4_A1_T10;
* @section: 15.5.4.4;
* @assertion: String.prototype.charAt(pos);
* @description: Call charAt() function with object argument;
*/

var __obj = {toString:function(){return 1;}}
var __str = "lego";

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
with(__str){
  if (charAt(__obj) !== "e") {
    $ERROR('#1: var __obj = {toString:function(){return 1;}}; var __str = "lego"; charAt(__obj) === "e". Actual: charAt(__obj) ==='+charAt(__obj) ); 
  }
}
//
//////////////////////////////////////////////////////////////////////////////
