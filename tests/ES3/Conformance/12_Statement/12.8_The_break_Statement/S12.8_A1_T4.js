// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.8_A1_T4;
* @section: 12.8;
* @assertion: Appearing of break without an IterationStatement leads to syntax error;
* @description: Checking if break Identifier with no loop, placed into a  block, fails;
* @negative;
*/

LABEL : x=3.14;

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
{
    var x=1;
    break LABEL;
    var y=2;
}
//
//////////////////////////////////////////////////////////////////////////////
