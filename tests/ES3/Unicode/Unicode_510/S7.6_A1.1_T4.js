// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.6_A1.1_T4;
 * @section: 7.6;
 * @assertion: IdentifierStart :: UnicodeLetter (any character in the Unicode categories "Lu", "Ll", "Lt", "Lm", "Lo", "Nl");
 * @description: UnicodeLetter :: Modifier letter (Lm).
 * Complex test with eval;  
*/

//CHECK
Lm = [[0x02B0, 0x02C1], [0x02C6, 0x02D1], [0x02E0, 0x02E4], [0x02EC, 0x02EC], [0x02EE, 0x02EE], [0x0374, 0x0374], [0x037A, 0x037A], [0x0559, 0x0559], [0x0640, 0x0640], [0x06E5, 0x06E6], [0x07F4, 0x07F5], [0x07FA, 0x07FA], [0x0971, 0x0971], [0x0E46, 0x0E46], [0x0EC6, 0x0EC6], [0x10FC, 0x10FC], [0x17D7, 0x17D7], [0x1843, 0x1843], [0x1C78, 0x1C7D], [0x1D2C, 0x1D61], [0x1D78, 0x1D78], [0x1D9B, 0x1DBF], [0x2090, 0x2094], [0x2C7D, 0x2C7D], [0x2D6F, 0x2D6F], [0x2E2F, 0x2E2F], [0x3005, 0x3005], [0x3031, 0x3035], [0x303B, 0x303B], [0x309D, 0x309E], [0x30FC, 0x30FE], [0xA015, 0xA015], [0xA60C, 0xA60C], [0xA67F, 0xA67F], [0xA717, 0xA71F], [0xA770, 0xA770], [0xA788, 0xA788], [0xFF70, 0xFF70], [0xFF9E, 0xFF9F]];

errorCount = 0;
count = 0;
for (indexI = 0; indexI < Lm.length; indexI++) {
  for (indexJ = Lm[indexI][0]; indexJ <= Lm[indexI][1]; indexJ++) {
    try {
      var identifier = String.fromCharCode(indexJ);
      var hex = decimalToHexString(indexJ);
      eval("var " + identifier + "=1");
      if (eval(identifier + "===1") !== true) {
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
