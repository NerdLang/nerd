// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.6.3_A7_T2;
* @section: 12.6.3;
* @assertion: Only three expressions and two semicolons in "for" braces are allowed. 
* Appearing of for (ExpressionNoIn_opt ; Expression_opt ; Expression_opt; Expression_opt; Expression_opt;) statement leads to SyntaxError;
* @description: Checking if execution of "for(index=0; index<10; index+=4; index++; index--)" fails ;
* @negative;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
for(index=0; index<10; index+=4; index++; index--) ;
//
//////////////////////////////////////////////////////////////////////////////
