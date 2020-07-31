// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.4.15_A1_T14;
* @section: 15.5.4.15;
* @assertion: String.prototype.substring (start, end);
* @description: Used one argument, that is function(){}(). Instance is string;
*/


//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if ("report".substring(function(){}()) !== "report") {
  $ERROR('#1: "report".substring(function(){}()) === "report". Actual: '+"report".substring(function(){}()) );
}
//
//////////////////////////////////////////////////////////////////////////////
