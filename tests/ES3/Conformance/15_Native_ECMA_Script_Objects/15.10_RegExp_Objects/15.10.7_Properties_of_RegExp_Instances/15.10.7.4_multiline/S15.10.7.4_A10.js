// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.7.4_A10;
* @section: 15.10.7.4;
* @assertion: The RegExp instance multiline property has the attribute ReadOnly;
* @description: Checking if varying the multiline property fails;
*/

__re = /\n/;

//CHECK#1
if (__re.hasOwnProperty('multiline') !== true) {
  $FAIL('#1: __re = /\\n/; __re.hasOwnProperty(\'multiline\') === true');
}

__obj = __re.multiline;

__re.multiline = "shifted";

//CHECK#2
if (__re.multiline !== __obj) {
  $ERROR('#2: __re = /\\n/; __obj = __re.multiline; __re.multiline = "shifted"; __re.multiline === __obj. Actual: ' + (__re.multiline));
}

