// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.6.3_D1_T1;
* @section: 15.10.6.3;
* @assertion: RegeExp.prototype.test calling does not change lastIndex property;
*/

__re = /ab|cd/g;

__string = "zz  zz  ab  zz  zz";

__re.test(__string);

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (__re.lastIndex!==0) {
	$ERROR('#1: RegeExp.prototype.test calling does not change lastIndex property');
}
//
//////////////////////////////////////////////////////////////////////////////
