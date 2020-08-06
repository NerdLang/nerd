// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.12_A1_T3;
* @section: 15.5.4.12;
* @assertion: String.prototype.search (regexp);
* @description: Checking by using eval;
*/

search = String.prototype.search;

if (typeof toString === "undefined"){
    toString = Object.prototype.toString;
}

__class__ = toString();

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (search(eval("\"bj\"")) !== 2) {
  $ERROR('#1: search = String.prototype.search; search(eval("\\"bj\\"")) === 2. Actual: '+search(eval("\"bj\"")) );
}
//
//////////////////////////////////////////////////////////////////////////////
