// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.4.1_A3_T4;
* @section: 15.10.4.1;
* @assertion: let P be the empty string if pattern is undefined;
* @description: RegExp is new RegExp(undefined);
*/

__re = new RegExp(undefined);

//CHECK#1
if (__re.source !== "") {
  $ERROR('#1: __re = new RegExp(undefined); __re.source === "". Actual: '+ (__re.source));
}

//CHECK#2
if (__re.multiline !== false) {
  $ERROR('#2: __re = new RegExp(undefined); __re.multiline === false. Actual: ' + (__re.multiline));
}

//CHECK#3
if (__re.global !== false) {
  $ERROR('#3: __re = new RegExp(undefined); __re.global === false. Actual: ' + (__re.global));
}

//CHECK#4
if (__re.ignoreCase !== false) {
  $ERROR('#4: __re = new RegExp(undefined); __re.ignoreCase === false. Actual: ' + (__re.ignoreCase));
}
