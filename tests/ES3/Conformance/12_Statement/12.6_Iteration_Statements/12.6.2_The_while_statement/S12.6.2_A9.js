// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.6.2_A9;
* @section: 12.6.2;
* @assertion: "while" Statement is evaluated without syntax checks;
* @description: Throwing system exception inside "while" loop;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
try {
	while(x!=1) {
	    var x = 1; 
	    abaracadabara;
	};
	$ERROR('#1: "abbracadabra" lead to throwing exception');

} catch (e) {}

if (x !== 1) {
	$ERROR('#1.1: while statement evaluates as is, without syntax checks');
}
//
//////////////////////////////////////////////////////////////////////////////
