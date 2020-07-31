// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.2.7_A4_T8;
* @section: 15.10.2.7;
* @assertion: The production QuantifierPrefix :: * evaluates by returning the two results 0 and \infty;
* @description: Execute /["'][^"']*["']/.test('alice cries out: don\'t') and check results;
*/

__executed = /["'][^"']*["']/.test('alice cries out: don\'t');

//CHECK#1
if (__executed) {
	$ERROR('#1: /["\'][^"\']*["\']/.test(\'alice cries out: don\'t\') === false');
}

