// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.6.4_A15;
* @section: 12.6.4;
* @assertion: Block within a "for-in" Expression is not allowed;
* @description: Using block within "for-in" Expression;
* @negative;
*/
var __arr=[1,2,3];

//////////////////////////////////////////////////////////////////////////////
//CHECK#
for(x in {__arr}){
   break ;
};
//
//////////////////////////////////////////////////////////////////////////////
