// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S8.6_A4_T1;
 * @section: 8.6, 8.6.1, 15.2.2, 12.6.4;
 * @assertion: An Object is an unordered collection of properties;
 * @description: Simple using a few custom properties;
*/

///////////////////////////////////////////////////////
// CHECK#1
obj = {bar:true, some:1, foo:"a"};

count=0;

for (property in obj)	count++;

if (count !== 3){
  $ERROR('#1: obj = {bar:true, some:1, foo:"a"}; count=0; for (property in obj) count++; count === 3. Actual: ' + (count));
}
//
////////////////////////////////////////////////////////

///////////////////////////////////////////////////////
// CHECK#2
obj_ = {bar:true};
obj_.some = 1;
obj_.foo = "a";

count=0;

for (property in obj_) count++;

if (count !== 3){
  $ERROR('#2: obj_ = {bar:true}; obj_.some = 1; obj_.foo = "a"; count=0; for (property in obj_) count++; count === 3. Actual: ' + (count));
}
//
////////////////////////////////////////////////////////

///////////////////////////////////////////////////////
// CHECK#3
obj__ = new Object();
obj__.bar = true;
obj__.some = 1;
obj__.foo = "a";

count=0;

for (property in obj__)	count++;

if (count !== 3){
  $ERROR('#3: obj__ = new Object(); obj__.bar = true; obj__.some = 1; obj__.foo = "a"; for (property in obj__)  count++; count === 3. Actual: ' + (count));
}
//
////////////////////////////////////////////////////////
