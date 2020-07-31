// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.2.12_A1_T1;
* @section: 15.10.2.12, 7.2, 7.3;
* @assertion: The production CharacterClassEscape :: s evaluates by returning the set of characters 
* containing the characters that are on the right-hand side of the WhiteSpace (7.2) or LineTerminator (7.3) productions;
* @description: WhiteSpace without category Zs; 
*/

//CHECK#1
var arr = /\s/.exec("\u0009");
if ((arr === null) || (arr[0] !== "\u0009")) {
  $ERROR('#1: var arr = /\\s/.exec("\\u0009"); arr[0] === "\\u0009". Actual. ' + (arr && arr[0]));
}

//CHECK#2
var arr = /\s/.exec("\u000B");
if ((arr === null) || (arr[0] !== "\u000B")) {
  $ERROR('#2: var arr = /\\s/.exec("\\u000B"); arr[0] === "\\u000B". Actual. ' + (arr && arr[0]));
}  

//CHECK#3
var arr = /\s/.exec("\u000C");
if ((arr === null) || (arr[0] !== "\u000C")) {
  $ERROR('#3: var arr = /\\s/.exec("\\u000C"); arr[0] === "\\u000C". Actual. ' + (arr && arr[0]));
}    

//CHECK#4
var arr = /\s/.exec("\u0020");
if ((arr === null) || (arr[0] !== "\u0020")) {
  $ERROR('#4: var arr = /\\s/.exec("\\u0020"); arr[0] === "\\u0020". Actual. ' + (arr && arr[0]));
}  

//CHECK#5
var arr = /\s/.exec("\u00A0");
if ((arr === null) || (arr[0] !== "\u00A0")) {
  $ERROR('#5: var arr = /\\s/.exec("\\u00A0"); arr[0] === "\\u00A0". Actual. ' + (arr && arr[0]));
}  
