// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.6.2_A15;
* @section: 12.6.2;
* @assertion: Block within a "while" Expression is not allowed;
* @description: Expression is "{0}";
* @negative;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#
while({1}){
   break ;
};
//
//////////////////////////////////////////////////////////////////////////////
