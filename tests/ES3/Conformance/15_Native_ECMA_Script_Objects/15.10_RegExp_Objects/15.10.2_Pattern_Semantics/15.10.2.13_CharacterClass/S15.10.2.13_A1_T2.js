// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S15.10.2.13_A1_T2;
* @section: 15.10.2.13;
* @assertion: The production CharacterClass :: [ [lookahead \notin {^}] ClassRanges ] evaluates by evaluating ClassRanges to obtain a CharSet and returning that CharSet and the boolean false;
* @description: Execute /a[]/.test("\0a\0a") and check results;
*/

__executed = /a[]/.test("\0a\0a");;

//CHECK#1
if (__executed) {
	$ERROR('#1: /a[]/.test("\\0a\\0a") === false');
}

