// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S8.6.2.4_A1;
* @section: 8.6.2.4, 12.6.4;
* @assertion: When the [[HasProperty]] method of O is called with property name P and if O has a property with name P, return true;
* @description: Try find existent property of any Object;
*/

var __obj={fooProp:"fooooooo"};

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (!("fooProp" in __obj)) {
  $ERROR('#1: var __obj={fooProp:"fooooooo"}; "fooProp" in __obj');
}
//
//////////////////////////////////////////////////////////////////////////////
