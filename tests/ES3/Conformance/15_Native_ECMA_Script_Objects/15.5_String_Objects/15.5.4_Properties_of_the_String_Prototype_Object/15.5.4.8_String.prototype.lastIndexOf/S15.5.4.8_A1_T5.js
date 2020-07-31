// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.8_A1_T5;
* @section: 15.5.4.8;
* @assertion: String.prototype.lastIndexOf(searchString, position);
* @description: Call lastIndexOf(searchString, position) function with null argument of function object;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
//since ToString(null) evaluates to "null" lastIndexOf(null) evaluates to lastIndexOf("",0)
if (function(){return "gnullunazzgnull"}().lastIndexOf(null) !== 11) {
  $ERROR('#1: function(){return "gnullunazzgnull"}().lastIndexOf(null) === 11. Actual: '+function(){return "gnullunazzgnull"}().lastIndexOf(null) );
}
//
//////////////////////////////////////////////////////////////////////////////
