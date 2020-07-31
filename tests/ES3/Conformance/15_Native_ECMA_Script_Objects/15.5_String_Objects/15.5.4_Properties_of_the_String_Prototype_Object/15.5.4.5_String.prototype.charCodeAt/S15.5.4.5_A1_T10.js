// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.5_A1_T10;
* @section: 15.5.4.5;
* @assertion: String.prototype.charCodeAt(pos);
* @description: Call charCodeAt() function with object argument;
*/

var __obj = {toString:function(){return 1;}}
var __str = "lego";

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
with(__str){
  if (charCodeAt(__obj) !== 0x65) {
    $ERROR('#1: var __obj = {toString:function(){return 1;}}; var __str = "lego"; charCodeAt(__obj) === 0x65. Actual: charCodeAt(__obj) ==='+charCodeAt(__obj) ); 
  }
}
//
//////////////////////////////////////////////////////////////////////////////
