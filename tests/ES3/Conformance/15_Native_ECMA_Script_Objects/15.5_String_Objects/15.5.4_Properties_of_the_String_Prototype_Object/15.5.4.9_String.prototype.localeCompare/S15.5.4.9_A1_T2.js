// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.9_A1_T2;
* @section: 15.5.4.9;
* @assertion: String.prototype.localeCompare(that);
* @description: Call string_1.localeCompare(string_2) is equal -string_2.localeCompare(string_1);
*/

//CHECK#1
var str1 = "h";
var str2 = "H";
if (str1.localeCompare(str2)!==-str2.localeCompare(str1)){
  $ERROR('#1.1: var str1 = "h"; var str2 = "H"; str1.localeCompare(str2)===-str2.localeCompare(str1). Actual: '+str1.localeCompare(str2));
}
