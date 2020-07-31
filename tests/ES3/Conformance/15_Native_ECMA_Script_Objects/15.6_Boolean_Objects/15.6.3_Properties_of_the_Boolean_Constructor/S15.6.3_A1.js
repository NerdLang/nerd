// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.6.3_A1;
 * @section: 15.6.3;
 * @assertion: The Boolean constructor has the property "prototype";
 * @description: Checking existence of the property "prototype";
 */

if(!Boolean.hasOwnProperty("prototype")){
  $ERROR('#1: The Boolean constructor has the property "prototype"');
}

