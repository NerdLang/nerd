// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S8.6.2_A5_T1;
* @section: 8.6.2, 13.1, 13.2;
* @assertion: [[Call]] executes code associated with the object;
* @description: Call function-property of object, property defined
*  as screen = {touch:function(){count++}};
*/

this.count=0;

screen = {touch:function(){count++}};
//////////////////////////////////////////////////////////////////////////////
//CHECK#1
screen.touch();
if (count !==1) {
  $ERROR('#1: this.count=0; screen = {touch:function(){count++}}; screen.touch(); count === 1. Actual: ' + (count));
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
screen['touch']();
if (count !==2) {
  $ERROR('#2: this.count=0; screen = {touch:function(){count++}}; screen.touch(); screen[\'touch\'](); count === 2. Actual: ' + (count));
}
//
//////////////////////////////////////////////////////////////////////////////
