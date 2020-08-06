// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.14_A1_T8;
* @section: 15.5.4.14;
* @assertion: String.prototype.split(separator, limit):
* i) can be transferred to other kinds of objects for use as a method.
* separator and limit can be any kinds of object since:
* ii) if separator is not RegExp ToString(separator) performs and
* iii) ToInteger(limit) performs;
* @description: Argument is void 0, and instance is String(object), object have overrided toString function;
*/

__obj = {toString:function(){}};

//since ToString(void 0) evaluates to "undefined" split(void 0) evaluates to split("undefined")
__split = String(__obj).split(void 0);

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (typeof __split !== "object") {
  $ERROR('#1: __obj = {toString:function(){}}; __split = String(__obj).split(void 0); typeof __split === "object". Actual: '+typeof __split );
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (__split.constructor !== Array) {
  $ERROR('#2: __obj = {toString:function(){}}; __split = String(__obj).split(void 0); __split.constructor === Array. Actual: '+__split.constructor );
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#3
if (__split.length !== 2) {
  $ERROR('#3: __obj = {toString:function(){}}; __split = String(__obj).split(void 0); __split.length === 2. Actual: '+__split.length );
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#4
if (__split[0] !== "") {
  $ERROR('#4: __obj = {toString:function(){}}; __split = String(__obj).split(void 0); __split[0] !== "". Actual: '+__split[0]);
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#5
if (__split[1] !== "") {
  $ERROR('#5: __obj = {toString:function(){}}; __split = String(__obj).split(void 0); __split[1] === "". Actual: '+__split[1] );
}
//
//////////////////////////////////////////////////////////////////////////////
