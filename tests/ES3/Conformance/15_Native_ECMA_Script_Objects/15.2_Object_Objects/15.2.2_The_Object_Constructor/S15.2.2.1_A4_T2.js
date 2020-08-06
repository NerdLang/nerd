// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.2.2.1_A4_T2;
* @section: 15.2.2.1, 8.6;
* @assertion: When the Object constructor is called with one argument value and 
* the type of value is Boolean, return ToObject(boolean);
* @description: Argument value is "false";
*/


var bool = false;

//CHECK#1
if (typeof bool  !== 'boolean') {
  $FAIL('#1: false is NOT a boolean');
}

var n_obj = new Object(bool);

//CHECK#2
if (n_obj.constructor !== Boolean) {
  $ERROR('#2: When the Object constructor is called with Boolean argument return ToObject(boolean)');
}

//CHECK#3
if (typeof n_obj !== 'object') {
  $ERROR('#3: When the Object constructor is called with Boolean argument return ToObject(boolean)');
}

//CHECK#4
if ( n_obj != bool) {
  $ERROR('#4: When the Object constructor is called with Boolean argument return ToObject(boolean)');
}

//CHECK#5
if ( n_obj === bool) {
  $ERROR('#5: When the Object constructor is called with Boolean argument return ToObject(boolean)');
}
