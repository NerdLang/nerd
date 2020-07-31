// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.8_A4_T2;
* @section: 15.5.4.8;
* @assertion: when String.prototype.lastIndexOf(searchString, position) is called first Call ToString, giving it the this value as its argument. 
* Then Call ToString(searchString) and Call ToNumber(position);
* @description: Override toString and valueOf functions, second toString throw exception;
*/

var __obj = {toString:function(){return "\u0041B";}}
var __obj2 = {valueOf:function(){return {};},toString:function(){throw "intointeger";}}
var __str = new String("ABB\u0041BABAB");

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
with(__str){
    try {
      var x = lastIndexOf(__obj, __obj2);
      $FAIL('#1: var x = lastIndexOf(__obj, __obj2) lead to throwing exception');
    } catch (e) {
      if (e!=="intointeger") {
        $ERROR('#1.1: Exception === "intointeger". Actual: '+e);
      }
    }
}
//
//////////////////////////////////////////////////////////////////////////////
