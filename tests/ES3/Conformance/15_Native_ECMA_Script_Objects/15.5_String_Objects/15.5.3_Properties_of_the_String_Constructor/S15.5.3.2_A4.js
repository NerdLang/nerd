// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.3.2_A4;
* @section: 15.5.3.2;
* @assertion: String.fromCharCode has not [[construct]] method;
* @description: Checking if creating "new String.fromCharCode" fails;
*/

__fcc__func = String.fromCharCode;

delete String.fromCharCode;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
try {
  var __obj = new __fcc__func(65,66,66,65);
  $FAIL('#1: __fcc__func = String.fromCharCode; var __obj = new __fcc__func(65,66,66,65) lead to throwing exception');
} catch (e) {}
//
//////////////////////////////////////////////////////////////////////////////
