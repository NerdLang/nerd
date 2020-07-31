// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.5_A01_T1;
 * @section: 15.9.5;
 * @assertion: The Date.prototype has the property "constructor";
 * @description: The Date.prototype has the property "constructor";
 */

if(Date.prototype.hasOwnProperty("constructor") !== true){
  $ERROR('#1: The Date.prototype has the property "constructor"');
}

