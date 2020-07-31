// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.7_A4_T1;
* @section: 12.7;
* @assertion: When "continue Identifier" is evaluated (continue, empty, Identifier) is returned;
* @description: Simple using continue Identifier construction; 
*/

LABEL_OUT : var x=0, y=0;

LABEL_DO_LOOP : do {
    LABEL_IN : x++;
    if(x===10)break;
    continue LABEL_DO_LOOP;
    LABEL_IN_2 : y++;
    
    function IN_DO_FUNC(){}
} while(0);

LABEL_ANOTHER_LOOP : do {
    ;
} while(0);

function OUT_FUNC(){}

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if ((x!==1)&&(y!==0)) {
	$ERROR('#1: x===1 and y === 0. Actual:  x==='+x+' and y ==='+y);
}
//
//////////////////////////////////////////////////////////////////////////////
