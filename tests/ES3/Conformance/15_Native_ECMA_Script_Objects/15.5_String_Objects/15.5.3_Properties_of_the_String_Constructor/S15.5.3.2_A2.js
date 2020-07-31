// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.5.3.2_A2;
* @section: 15.5.3.2;
* @assertion: String.fromCharCode () returns empty string;
* @description: Call String.fromCharCode();
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (String.fromCharCode() !== "") {
  $ERROR('#1: String.fromCharCode () returns empty string. Actual: '+String.fromCharCode());
}
//
//////////////////////////////////////////////////////////////////////////////

