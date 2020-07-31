// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S7.6_A2.2_T2;
 * @section: 7.6;
 * @assertion: IdentifierPart :: UnicodeCombiningMark (any character in the Unicode categories "Mn", "Mc");
 * @description: UnicodeCombiningMark :: Combining spacing mark (Mc).
 * Complex test with eval;
*/

//CHECK
Mc = [[0x0903, 0x0903], [0x093E, 0x0940], [0x0949, 0x094C], [0x0982, 0x0983], [0x09BE, 0x09C0], [0x09C7, 0x09C8], [0x09CB, 0x09CC], [0x09D7, 0x09D7], [0x0A3E, 0x0A40], [0x0A83, 0x0A83], [0x0ABE, 0x0AC0], [0x0AC9, 0x0AC9], [0x0ACB, 0x0ACC], [0x0B02, 0x0B03], [0x0B3E, 0x0B3E], [0x0B40, 0x0B40], [0x0B47, 0x0B48], [0x0B4B, 0x0B4C], [0x0B57, 0x0B57], [0x0B83, 0x0B83], [0x0BBE, 0x0BBF], [0x0BC1, 0x0BC2], [0x0BC6, 0x0BC8], [0x0BCA, 0x0BCC], [0x0BD7, 0x0BD7], [0x0C01, 0x0C03], [0x0C41, 0x0C44], [0x0C82, 0x0C83], [0x0CBE, 0x0CBE], [0x0CC0, 0x0CC4], [0x0CC7, 0x0CC8], [0x0CCA, 0x0CCB], [0x0CD5, 0x0CD6], [0x0D02, 0x0D03], [0x0D3E, 0x0D40], [0x0D46, 0x0D48], [0x0D4A, 0x0D4C], [0x0D57, 0x0D57], [0x0F3E, 0x0F3F], [0x0F7F, 0x0F7F]];

errorCount = 0;
count = 0;
for (indexI = 0; indexI < Mc.length; indexI++) {
  for (indexJ = Mc[indexI][0]; indexJ <= Mc[indexI][1]; indexJ++) {
    try {
      var identifier = "$" + String.fromCharCode(indexJ);
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
