// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.9.4_A2;
 * @section: 15.9.4;
 * @assertion: The Date constructor has the property "parse";
 * @description: Checking existence of the property "parse";
 */

if(!Date.hasOwnProperty("parse")){
  $ERROR('#1: The Date constructor has the property "parse"');
}

