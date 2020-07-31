// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.8_A1_T3;
* @section: 15.5.4.8;
* @assertion: String.prototype.lastIndexOf(searchString, position);
* @description: Checking by using eval;
*/

lastIndexOf = String.prototype.lastIndexOf;

var __obj__pos = {valueOf:function(){return 7;}};

if (typeof toString === "undefined"){
  toString = Object.prototype.toString;
}

__class__ = toString();

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (lastIndexOf(eval("\"[\""),__obj__pos)!= 0) {
  $ERROR('#1: lastIndexOf(eval("\\"[\\""),__obj__pos)== 0. Actual: '+lastIndexOf(eval("\"[\""),__obj__pos));
}
//
//////////////////////////////////////////////////////////////////////////////
