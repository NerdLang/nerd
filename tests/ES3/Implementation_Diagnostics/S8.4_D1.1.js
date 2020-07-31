// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S8.4_D1.1;
* @section: 8.4, 15.5, 7.8.4;
* @assertion: Engines implements array like access to string elemenths,
* when we call squre brackets operator char at position specified returns
*/

var __str = 'hail to robots!!!';
var str__='';
for (ind = 0; ind < 17; ind++){
	str__ += __str[ind];
}
if (str__ !== __str) {
  $ERROR('When we call squre brackets operator char at position specified returns');
}
