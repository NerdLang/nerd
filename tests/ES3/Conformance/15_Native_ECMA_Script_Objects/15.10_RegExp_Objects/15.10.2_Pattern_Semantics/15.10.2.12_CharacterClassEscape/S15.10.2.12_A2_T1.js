// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.2.12_A2_T1;
* @section: 15.10.2.12, 7.2, 7.3;
* @assertion: The production CharacterClassEscape :: S evaluates by returning 
* the set of all characters not included in the set returned by 
* CharacterClassEscape :: s;
* @description: WhiteSpace without category Zs; 
*/

//CHECK#1
var arr = /\S/.exec("\u0009");
if (arr !== null) {
  $ERROR('#1: var arr = /\\S/.exec("\\u0009"); arr[0] === "\\u0009". Actual. ' + (arr && arr[0]));
}

//CHECK#2
var arr = /\S/.exec("\u000B");
if (arr !== null) {
  $ERROR('#2: var arr = /\\S/.exec("\\u000B"); arr[0] === "\\u000B". Actual. ' + (arr && arr[0]));
}  

//CHECK#3
var arr = /\S/.exec("\u000C");
if (arr !== null) {
  $ERROR('#3: var arr = /\\S/.exec("\\u000C"); arr[0] === "\\u000C". Actual. ' + (arr && arr[0]));
}    

//CHECK#4
var arr = /\S/.exec("\u0020");
if (arr !== null) {
  $ERROR('#4: var arr = /\\S/.exec("\\u0020"); arr[0] === "\\u0020". Actual. ' + (arr && arr[0]));
}  

//CHECK#5
var arr = /\S/.exec("\u00A0");
if (arr !== null) {
  $ERROR('#5: var arr = /\\S/.exec("\\u00A0"); arr[0] === "\\u00A0". Actual. ' + (arr && arr[0]));
}  
