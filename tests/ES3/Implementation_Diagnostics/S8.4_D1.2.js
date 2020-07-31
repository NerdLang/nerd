// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S8.4_D1.2;
 * @section: 8.4, 7.8.4;
 * @assertion: Some engines can implement array like access to string elemenths:
 * Positions are indexed with nonnegative integers;
*/

str='asdfghjkl';

////////////////////////////////////////////////////////////
// CHECK#1
if (str[0] !== 'a'){
  $ERROR('#1: str="asdfghjkl";str[0]==="a"');
}
//
/////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// CHECK#2
if (str[1] !== 's'){
  $ERROR('#2: str="asdfghjkl";str[1]==="s"');
}
//
/////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// CHECK#3
if (str[8] !== 'l'){
  $ERROR('#3: str="asdfghjkl";str[8]==="l"');
}
//
/////////////////////////////////////////////////////////////
