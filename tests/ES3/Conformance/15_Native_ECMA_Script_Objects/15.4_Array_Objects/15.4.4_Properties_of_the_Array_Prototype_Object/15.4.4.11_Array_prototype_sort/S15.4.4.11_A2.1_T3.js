// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.4.4.11_A2.1_T3;
 * @section: 15.4.4.11;
 * @assertion: 
 * If ToString([[Get]] ToString(j)) < ToString([[Get]] ToString(k)), return -1.
 * If ToString([[Get]] ToString(j)) > ToString([[Get]] ToString(k)), return 1; 
 * return -1
 * @description: Checking ToString operator; 
*/

var obj = {valueOf: function() {return 1}, toString: function() {return -2}};
alphabetR = [undefined, 2, 1, "X", -1, "a", true, obj, NaN, Infinity]; 
 alphabet = [-1, obj, 1, 2, Infinity, NaN, "X", "a", true, undefined];
 
//CHECK#1
alphabetR.sort();
result = true;
for (i = 0; i < 10; i++) {
  if (!(isNaN(alphabetR[i]) && isNaN(alphabet[i]))) { 
    if (alphabetR[i] !== alphabet[i]) result = false;
  }  
}

if (result !== true) {
  $ERROR('#1: Check ToString operator');
}
