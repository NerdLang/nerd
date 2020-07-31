// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.2_A2.6_T1;
 * @section: 7.2, 7.8.4;
 * @assertion: Any other Unicode "space separator" (category "Zs") within strings;
 * @description: Complex test;
*/

//CHECK#1
Zs = [[0x1680, 0x1680], [0x180E, 0x180E], [0x2000, 0x200A], [0x202F, 0x202F], [0x205F, 0x205F], [0x3000, 0x3000]];

errorCount = 0;
count = 0;
for (indexI = 0; indexI < Zs.length; indexI++) {
  for (indexJ = Zs[indexI][0]; indexJ <= Zs[indexI][1]; indexJ++) {
    try {
      var format = String.fromCharCode(indexJ);
      var hex = decimalToHexString(indexJ);
      var x = "str" + format + "ing";
      if (x !== "str" + format + "ing") {
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
