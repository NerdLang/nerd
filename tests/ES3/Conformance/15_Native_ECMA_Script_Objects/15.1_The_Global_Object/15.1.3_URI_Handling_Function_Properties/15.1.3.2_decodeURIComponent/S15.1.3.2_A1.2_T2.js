// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.3.2_A1.2_T2;
 * @section: 15.1.3.2;
 * @assertion: If B = string.charAt(k+1) + string.charAt(k+2) do not represent
 * hexadecimal digits, throw URIError;
 * @description: Complex tests;
*/

//CHECK
result = true;
var interval = [[0x00, 0x29], [0x40,0x40], [0x47, 0x60], [0x67, 0xFFFF]];
for (indexI = 0; indexI < interval.length; indexI++) {
  for (indexJ = interval[indexI][0]; indexJ <= interval[indexI][1]; indexJ++) {
    try {
      decodeURIComponent("%" + "1" + String.fromCharCode(indexJ));
      result = false;
    } catch (e) {   
      if ((e instanceof URIError) !== true) {
        result = false;
      }
    }      
  }  
}  

if (result !== true) {    
  $ERROR('#1: If string.charAt(k+2) does not represent hexadecimal digits, throw URIError');
}
