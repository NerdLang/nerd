// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S12.11_A3_T4;
 * @section: 12.11;
 * @assertion: Syntax constructions of switch statement;
 * @description: Using "case" that has no Expresson after it. "CaseClause: case Expression : [StatementList]";
 * @negative;
*/

function SwitchTest(value){
  var result = 0;
  
  switch(value) {
    case:
      result += 2;
    default:
      result += 32;
      break;
  }
  
  return result;
}

var x = SwitchTest(0);
