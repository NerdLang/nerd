// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.2.4_A1.3_T1;
* @section: 11.2.4, 11.2.3, 10.1.8;
* @assertion: Arguments : (ArgumentList : ArgumentList,, AssignmentExpression) is a bad syntax;
* @description: incorrect syntax;
* @negative;
*/

function f_arg() {
}

f_arg(1,,2);
