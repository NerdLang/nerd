// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.7_A1_T3;
* @section: 15.5.4.7;
* @assertion: String.prototype.indexOf(searchString, position);
* @description: Checking by using eval;
*/

indexOf = String.prototype.indexOf;

var __obj__pos = {valueOf:function(){return 5;}};

if (typeof toString === "undefined"){
    toString = Object.prototype.toString;
}

__class__ = toString();

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (indexOf(eval("\"[\""),__obj__pos)!=-1) {
  $ERROR('#1: indexOf = String.prototype.indexOf; indexOf(eval("\\"[\\""),__obj__pos)==-1. Actual: indexOf(eval("\\"[\\""),__obj__pos)=='+indexOf(eval("\"[\""),__obj__pos)); 
}
//
//////////////////////////////////////////////////////////////////////////////
