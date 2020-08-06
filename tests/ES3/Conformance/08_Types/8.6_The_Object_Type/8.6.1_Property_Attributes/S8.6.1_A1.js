// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S8.6.1_A1;
 * @section: 8.6.1, 15.2.2, 15.8;
 * @assertion: A property can have attribute ReadOnly like E in Math;
 * @description: Try change Math.E property; 
*/

__e = Math.E;
Math.E=1;
if (Math.E !==__e){
  $ERROR('#1: __e = Math.E; Math.E=1; Math.E ===__e');
}
