// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.1_A2.2_T1;
 * @section: 7.1;
 * @assertion: Since the format control character (Cf) are removed before processing regular expression literals,
 * one must use a Unicode escape sequence to include a Cf inside regular expression literal;
 * @description: Complex test, without eval;  
*/

//CHECK#1
Cf = [[0x06DD, 0x06DD], [0x070F, 0x070F], [0x180E, 0x180E], [0x200C, 0x200F], [0x202A, 0x202E], [0x2060, 0x2063], [0x206A, 0x206F], [0xFEFF, 0xFEFF], [0xFFF9, 0xFFFB]];

errorCount = 0;
count = 0;
for (indexI = 0; indexI < Cf.length; indexI++) {
  for (indexJ = Cf[indexI][0]; indexJ <= Cf[indexI][1]; indexJ++) {
    try {
      var format = String.fromCharCode(indexJ);
      var hex = decimalToHexString(indexJ);      
      var x = RegExp(format + "a" + format + "b" + format);         
      if (x.source.length !== 5) {
        $ERROR('#' + hex + ' ');
        errorCount++;        
      }                 
    } catch (e) {
      $ERROR('#' + hex + ' ');
      errorCount++;
    }
    count++;
  }
}

if (errorCount > 0) {  
  $ERROR('Total error: ' + errorCount + ' bad Unicode character in ' + count);
}

function decimalToHexString(n) {
  n = Number(n);
  var h = "";
  for (var i = 3; i >= 0; i--) {
    if (n >= Math.pow(16, i)) {
      var t = Math.floor(n / Math.pow(16, i));
      n -= t * Math.pow(16, i);
      if ( t >= 10 ) {
        if ( t == 10 ) { h += "A"; }
        if ( t == 11 ) { h += "B"; }
        if ( t == 12 ) { h += "C"; }
        if ( t == 13 ) { h += "D"; }
        if ( t == 14 ) { h += "E"; }
        if ( t == 15 ) { h += "F"; }
      } else {
        h += String(t);
      }
    } else {
      h += "0";
    }
  }
  return h;
}
