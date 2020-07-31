// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S8.4_D2.7;
 * @section: 8.4, 15.5, 7.8.4;
 * @assertion: Engines implements array like access to string elemenths,
 * If index of element must is equal to -1 an length of string returns;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
str='asdfghjkl';

if (str[-1] !== 9) {
  $ERROR('#1: If index of element must is equal to -1 an length of string returns');
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
str='';

if (str[-1] !== 0) {
  $ERROR('#2: If index of element must is equal to -1 an length of string returns');
}
//
//////////////////////////////////////////////////////////////////////////////
