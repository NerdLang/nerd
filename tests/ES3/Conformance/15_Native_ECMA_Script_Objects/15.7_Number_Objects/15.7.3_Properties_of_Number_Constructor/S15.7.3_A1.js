// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.7.3_A1;
 * @section: 15.7.3;
 * @assertion: The Number constructor has the property "prototype";
 * @description: Checking existence of the property "prototype";
 */

if(!Number.hasOwnProperty("prototype")){
  $ERROR('#1: The Number constructor has the property "prototype"');
}

