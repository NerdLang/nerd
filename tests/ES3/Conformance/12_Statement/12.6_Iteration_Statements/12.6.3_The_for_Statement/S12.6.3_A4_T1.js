// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.6.3_A4_T1;
* @section: 12.6.3;
* @assertion: "in"-expression is not allowed as a ExpressionNoIn in "for (ExpressionNoIn; FirstExpression; SecondExpression) Statement" IterationStatement;
* @description: Checking if execution of "for (a in arr;1;){}" fails;
* @negative;
*/

arr = [1,2,3,4,5];

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
for (a in arr;1;){
    break;
}
//
//////////////////////////////////////////////////////////////////////////////

