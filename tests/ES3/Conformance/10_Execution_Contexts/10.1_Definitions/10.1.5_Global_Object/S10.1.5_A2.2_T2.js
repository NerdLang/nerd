// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S10.1.5_A2.2_T2;
 * @section: 10.1.5, 15.1;
 * @assertion: Global object properties have attributes { DontEnum };
 * @description: Function execution context - Function Properties;
*/

function test() {
  //CHECK#1
  for (var x in this) {
    if ( x === 'eval' ) {
      $ERROR("#1: 'eval' have attribute DontEnum");
    } else if ( x === 'parseInt' ) {
      $ERROR("#1: 'parseInt' have attribute DontEnum");
    } else if ( x === 'parseFloat' ) {
      $ERROR("#1: 'parseFloat' have attribute DontEnum");
    } else if ( x === 'isNaN' ) {
      $ERROR("#1: 'isNaN' have attribute DontEnum");
    } else if ( x === 'isFinite' ) {
      $ERROR("#1: 'isFinite' have attribute DontEnum");
    } else if ( x === 'decodeURI' ) {
      $ERROR("#1: 'decodeURI' have attribute DontEnum");
    } else if ( x === 'decodeURIComponent' ) {
      $ERROR("#1: 'decodeURIComponent' have attribute DontEnum");
    } else if ( x === 'encodeURI' ) {
      $ERROR("#1: 'encodeURI' have attribute DontEnum");
    } else if ( x === 'encodeURIComponent' ) {
      $ERROR("#1: 'encodeURIComponent' have attribute DontEnum");
    } 
  }
}

test();
