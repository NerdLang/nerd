// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.10_A1_T3;
* @section: 15.5.4.10;
* @assertion: String.prototype.match (regexp);
* @description: Checking by using eval;
*/

match = String.prototype.match;

if (typeof toString === "undefined"){
    toString = Object.prototype.toString;
}

__class__ = toString();

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (match(eval("\"bj\""))[0] !== "bj") {
  $ERROR('#1: match = String.prototype.match; match(eval("\\"bj\\""))[0] === "bj". Actual: '+match(eval("\"bj\""))[0] );
}
//
//////////////////////////////////////////////////////////////////////////////
