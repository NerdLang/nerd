// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5.19_A2_T1;
 * @section: 15.9.5.19;
 * @assertion: The "length" property of the "getUTCHours" is 0;
 * @description: The "length" property of the "getUTCHours" is 0;
 */

if(Date.prototype.getUTCHours.hasOwnProperty("length") !== true){
  $ERROR('#1: The getUTCHours has a "length" property');
}

if(Date.prototype.getUTCHours.length !== 0){
  $ERROR('#2: The "length" property of the getUTCHours is 0');
}

