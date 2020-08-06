// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S14_D4_T2;
* @section: 14;
* @assertion: Function declaration may be inside of try-catch block ;
*/

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (typeof __sleep !== "function") {
	$FAIL('#1: Test fails badly');
}
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
try{
    __sleep();
    $ERROR('#2: Function declaration may be inside of try-catch block');
} catch(e){
    $PRINT("#2 passed "+e.message);
}
//
//////////////////////////////////////////////////////////////////////////////

try {
	;
} catch (e) {
    function __sleep(){
        return CHUNK;
    }
}


CHUNK="zzz...";

//////////////////////////////////////////////////////////////////////////////
//CHECK#3
try{
    if (__sleep()!=="zzz...") {
    	$ERROR('#3: Function declaration may be inside of try-catch block');
    }
} catch(e){
    $ERROR('#3.1: Function declaration may be inside of try-catch block');
}
//
//////////////////////////////////////////////////////////////////////////////
