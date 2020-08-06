// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.28_A2_T1;
 * @section: 15.9.5.28;
 * @assertion: The "length" property of the "setMilliseconds" is 1;
 * @description: The "length" property of the "setMilliseconds" is 1;
 */

if(Date.prototype.setMilliseconds.hasOwnProperty("length") !== true){
  $ERROR('#1: The setMilliseconds has a "length" property');
}

if(Date.prototype.setMilliseconds.length !== 1){
  $ERROR('#2: The "length" property of the setMilliseconds is 1');
}

