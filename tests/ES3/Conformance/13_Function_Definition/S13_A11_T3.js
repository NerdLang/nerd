// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S13_A11_T3;
* @section: 13;
* @assertion: Since arguments property has attribute { DontDelete }, only its elements can be deleted;
* @description: Deleting arguments[i] and returning result of the operation;
*/

function __func(){
    was_del=false;
    for (i=0; i < arguments.length; i++)
       was_del= was_del || delete arguments[i];
    return was_del;
}

//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (!__func("A","B",1,2)) {
	$ERROR('#1: Since arguments property has attribute { DontDelete } elements of arguments can be deleted');
}
//
//////////////////////////////////////////////////////////////////////////////
