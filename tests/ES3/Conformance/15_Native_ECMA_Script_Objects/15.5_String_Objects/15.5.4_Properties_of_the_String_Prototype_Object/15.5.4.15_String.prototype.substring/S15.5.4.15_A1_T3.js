// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.15_A1_T3;
* @section: 15.5.4.15;
* @assertion: String.prototype.substring (start, end);
* @description: Checking by using eval;
*/

substring = String.prototype.substring;

if (typeof toString === "undefined"){
    toString = Object.prototype.toString;
}

__class__ = toString();
__toggle = 1;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (substring(eval("\"1\""),{valueOf:function(){return "0x0007"}})!=="object") {
  $ERROR('#1: substring(eval("\\"1\\""),{valueOf:function(){return "0x0007"}})==="object". Actual: '+substring(eval("\"1\""),{valueOf:function(){return "0x0007"}}));
};
//
//////////////////////////////////////////////////////////////////////////////
