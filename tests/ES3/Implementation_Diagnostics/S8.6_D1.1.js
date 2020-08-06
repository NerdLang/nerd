// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S8.6_D1.1;
* @section: 8.6;
* @assertion: An Object may have up to 4096 properties;
* @description: Create 4096 properties of any Object; 
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
COUNT=4096;
var props={};
for (var i=0;i<COUNT;i++){
	props['prop'+i]=i;
}
var result = true;
for (var i=0;i<COUNT;i++){
  if (props['prop'+i] !==i ) result = false;
}
if (result !== true) {
  $ERROR('#1: An Object may have up to 4096 properties');
} 
//
//////////////////////////////////////////////////////////////////////////////
