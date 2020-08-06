// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.10.2.12_A1_T6;
 * @section: 15.10.2.12, 7.2, 7.3;
 * @assertion: The production CharacterClassEscape :: s evaluates by returning the set of characters 
 * containing the characters that are on the right-hand side of the WhiteSpace (7.2) or LineTerminator (7.3) productions; 
 * @description: Complex test;
*/

//CHECK#1
var regexp_s = /\s/;
Zs = [[0x1680, 0x1680], [0x180E, 0x180E], [0x2000, 0x200A], [0x202F, 0x202F], [0x205F, 0x205F], [0x3000, 0x3000]];

errorCount = 0;
count = 0;
for (indexI = 0; indexI < Zs.length; indexI++) {
  for (indexJ = Zs[indexI][0]; indexJ <= Zs[indexI][1]; indexJ++) {
    var str = String.fromCharCode(indexJ);	
    var arr = regexp_s.exec(str);
    if ((arr === null) || (arr[0] !== str)) {
      var hex = decimalToHexString(indexJ);
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
