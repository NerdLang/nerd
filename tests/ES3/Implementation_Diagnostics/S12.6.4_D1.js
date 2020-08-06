// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S12.6.4_D1;
* @section: 12.6.4;
* @assertion: If new properties are added to the object being
* enumerated during enumeration, the newly added properties to be visited in the active
* enumeration;
*/

__obj={aa:1,ba:2,ca:3};
__source={sra:9,srb:8,src:7};

__accum="";

for (__key in __obj){
	
	__accum+=(__key+__obj[__key]);
	
	add2hash(__obj,__source);
	
}


//////////////////////////////////////////////////////////////////////////////
//CHECK#1
if (!(
(__accum.indexOf("aa1")!==-1)&&
(__accum.indexOf("ba2")!==-1)&&
(__accum.indexOf("ca3")!==-1)&&
(__accum.indexOf("sra9")!==-1)&&
(__accum.indexOf("srb8")!==-1)&&
(__accum.indexOf("src7")!==-1)
)) {
	$ERROR('#1: the newly added properties to be visited in the active enumeration');
}
//
//////////////////////////////////////////////////////////////////////////////

function add2hash(hash_map_target, hash_map_be_added){
    if (added) return;
	for (key in hash_map_be_added){
			hash_map_target[key] = hash_map_be_added[key];
	}
	var added = true;
}
