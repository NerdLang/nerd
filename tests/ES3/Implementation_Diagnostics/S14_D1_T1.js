// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S14_D1_T1;
* @section: 14;
* @assertion: Function declaration may be in unreacheable fragment of program;
*/

THERE = "I'm there";
HERE = "I'm here";

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
try{
    if (__func() !== THERE) {
    	$ERROR('#1: Function declaration may be in unreacheable fragment of program');
    }
} catch(e){
    $ERROR('#1.1: '+e.message);
}
//
//////////////////////////////////////////////////////////////////////////////

if (true){
    function __func(){return HERE;};
} else {
    function __func(){return THERE;};
};

//////////////////////////////////////////////////////////////////////////////
//CHECK#2
if (__func() !== THERE) {
	$ERROR('#2: Function declaration may be in unreacheable fragment of program');
}
//
//////////////////////////////////////////////////////////////////////////////
