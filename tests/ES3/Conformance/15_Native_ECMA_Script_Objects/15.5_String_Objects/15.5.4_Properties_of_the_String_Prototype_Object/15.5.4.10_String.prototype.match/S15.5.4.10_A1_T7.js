// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.10_A1_T7;
* @section: 15.5.4.10;
* @assertion: String.prototype.match (regexp);
* @description: Call match (regexp) function with undefined argument of string object;
*/

__matched = String("undefined").match(undefined);

__expected = RegExp(undefined).exec("undefined"); 

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__matched.length !== __expected.length) {
  $ERROR('#1: __matched = String("undefined").match(undefined); __expected = RegExp(undefined).exec("undefined"); __matched.length === __expected.length. Actual: '+__matched.length );
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (__matched.index !== __expected.index) {
  $ERROR('#2: __matched = String("undefined").match(undefined); __expected = RegExp(undefined).exec("undefined"); __matched.index === __expected.index. Actual: '+__matched.index );
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#3
if (__matched.input !== __expected.input) {
  $ERROR('#3: __matched = String("undefined").match(undefined); __expected = RegExp(undefined).exec("undefined"); __matched.input === __expected.input. Actual: '+__matched.input );
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#4
for(var index=0; index<__expected.length; index++) {
  if (__matched[index]!==__expected[index]) {
    $ERROR('#4.'+index+': __matched = String("undefined").match(undefined); __expected = RegExp(undefined).exec("undefined"); __matched['+index+']===__expected['+index+']. Actual: '+__matched[index]);
  }
}
//
//////////////////////////////////////////////////////////////////////////////
