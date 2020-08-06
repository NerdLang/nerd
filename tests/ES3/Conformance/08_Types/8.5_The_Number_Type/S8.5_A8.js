// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S8.5_A8;
 * @section: 8.5, 7.8.3;
 * @assertion: Infinity is the same as +Infinity;
 * @description: Compare Infinity and +Infinity; 
*/

var p_inf=+Infinity;
var inf=Infinity;

///////////////////////////////////////////////////////
// 
if (p_inf!==inf){
  $ERROR('#1: Infinity is the same as +Infinity');
}
//
//////////////////////////////////////////////////////////
