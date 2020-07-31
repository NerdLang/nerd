// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.2.2_A7.2_T1;
 * @section: 15.1.2.2;
 * @assertion: Compute the mathematical integer value 
 * that is represented by Z in radix-R notation, using the
 * letters A-Z and a-z for digits with values 10 through 35. 
 * Compute the number value for Result(16);
 * @description: Complex test. Check algorithm;
*/

//CHECK#
R_digit1 = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"];
R_digit2 = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"];
for (i = 2; i <= 36; i++) {
  for (j = 0; j < 10; j++) {
    str = "";  
    num = 0;
    pow = 1;
    k0 = Math.max(2, i - j);
    for (k = k0; k <= i; k++) { 
      if (k % 2 === 0) {  
        str = str + R_digit1[k - 2];
      } else {  
        str = str + R_digit2[k - 2];
      }
      num = num + (i + (k0 - k) - 1) * pow;
      pow = pow * i;   
    }   
    if (parseInt(str, i) !== num) {
      $ERROR('#' + i + '.' + j + ' : ');      
    }
  }  
}  
