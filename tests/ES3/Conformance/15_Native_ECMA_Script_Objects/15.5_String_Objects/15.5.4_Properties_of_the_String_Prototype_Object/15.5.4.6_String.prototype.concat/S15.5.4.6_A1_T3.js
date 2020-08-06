// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.6_A1_T3;
* @section: 15.5.4.6;
* @assertion: String.prototype.concat([,[...]]);
* @description: Use numbers and function object as arguments;
*/

concat = String.prototype.concat;

var __obj5 = {toString:function(){return 5;}};

if (typeof toString === "undefined"){
    toString = Object.prototype.toString;
}

__class__ = toString();

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (concat(1,2,3,4,__obj5)!=__class__+"12345") {
  $ERROR('#1: concat = String.prototype.concat; concat(1,2,3,4,__obj5)==__class__+"12345". Actual: concat(1,2,3,4,__obj5)=='+concat(1,2,3,4,__obj5)); 
}
//
//////////////////////////////////////////////////////////////////////////////
