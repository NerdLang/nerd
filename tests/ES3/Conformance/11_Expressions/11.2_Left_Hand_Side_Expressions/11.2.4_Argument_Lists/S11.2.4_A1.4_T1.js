// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
* @name: S11.2.4_A1.4_T1;
* @section: 11.2.4, 11.2.3, 10.1.8;
* @assertion: Arguments : (ArgumentList : ArgumentList, AssignmentExpression);
* @description: Return an internal list whose length is one greater than the 
* length of ArgumentList and whose items are the items of ArgumentList, in order, 
* followed at the end by GetValue(AssignmentExpression), which is the last item of 
* the new list;
*/

function f_arg() {
}

//CHECK#1
f_arg(x=1,x);
