// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S7.9_A5.7_T1;
* @section: 7.9;
* @assertion: Since LineTerminator(LT) between Postfix Increment/Decrement Operator(I/DO) and operand is not allowed, two IO(just as two DO and their combination)
* between two references separated by [LT] after automatic semicolon insertion lead to syntax error;
* @description: Try use Variable1 \n ++ \n ++ \n Variable2 construction;
* @negative;
*/

var x=0, y=0;
z=
x
++
++
y
