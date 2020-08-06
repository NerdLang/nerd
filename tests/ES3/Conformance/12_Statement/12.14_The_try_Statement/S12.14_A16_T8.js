// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S12.14_A16_T8;
 * @section: 12.14, 12.1;
 * @assertion: TryStatement: "try Block Catch" or "try Block Finally" or "try Block Catch Finally";
 * @description: Block: "{ StatementList }". Catch: "catch (Identifier ) Block". Checking if execution of "try{} catch(){finally{}" fails;
 * @negative
 */

// CHECK#1
try{}
catch(){
finally{}


