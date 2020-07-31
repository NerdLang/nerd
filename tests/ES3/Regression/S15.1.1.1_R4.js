// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.1.1_R4;
 * @section: 15.1.1.1, 11;
 * @description: The NaN is not ReadOnly, check Operators that use ToNumber;   
*/

// CHECK#1
NaN = true; 
NaN++; 
if (NaN !== 2) {
  $ERROR('#1: NaN = true; NaN++; NaN === 2');
} 

// CHECK#2
NaN = true; 
NaN--; 
if (NaN !== 0) {
  $ERROR('#2: NaN = true; NaN--; NaN === 0');
} 

// CHECK#3
NaN = true; 
++NaN; 
if (NaN !== 2) {
  $ERROR('#3: NaN = true; ++NaN; NaN === 2');
} 

// CHECK#4
NaN = true; 
--NaN;
if (NaN !== 0) {
  $ERROR('#4: NaN = true; --NaN; NaN === 0');
} 

// CHECK#5
NaN = true; 
+NaN; 
if (NaN !== true) {
  $ERROR('#5: NaN = true; +NaN; NaN === true');

} 
// CHECK#6
NaN = true; 
-NaN;
if (NaN !== true) {
  $ERROR('#6: NaN = true; -NaN; NaN === true');
} 
// CHECK#7
NaN = true; 
NaN * 1;
if (NaN !== true) {
  $ERROR('#7: NaN = true; NaN * 1; NaN === true');
} 

// CHECK#8
NaN = true; 
NaN / 1;
if (NaN !== true) {
  $ERROR('#8: NaN = true; NaN / 1; NaN === true');
} 

// CHECK#9
NaN = true; 
NaN % 1;
if (NaN !== true) {
  $ERROR('#9: NaN = true; NaN % 1; NaN === true');
} 

// CHECK#10
NaN = true; 
NaN + 1;
if (NaN !== true) {
  $ERROR('#10: NaN = true; NaN + 1; NaN === true');
} 

// CHECK#11
NaN = true; 
NaN - 1;
if (NaN !== true) {
  $ERROR('#11: NaN = true; NaN - 1; NaN === true');
} 

// CHECK#12
NaN = true; 
NaN > 1;
if (NaN !== true) {
  $ERROR('#12: NaN = true; NaN > 1; NaN === true');
} 

// CHECK#13
NaN = true; 
NaN < 1;
if (NaN !== true) {
  $ERROR('#13: NaN = true; NaN < 1; NaN === true');
} 

// CHECK#14
NaN = true; 
NaN >= 1;
if (NaN !== true) {
  $ERROR('#14: NaN = true; NaN >= 1; NaN === true');
} 

// CHECK#15
NaN = true; 
NaN <= 1;
if (NaN !== true) {
  $ERROR('#15: NaN = true; NaN <= 1; NaN === true');
} 

// CHECK#16
NaN = true; 
NaN == true;
if (NaN !== true) {
  $ERROR('#16: NaN = true; NaN == true; NaN === true');
} 

// CHECK#17
NaN = true; 
NaN != 1;
if (NaN !== true) {
  $ERROR('#17: NaN = true; NaN != 1; NaN === true');
} 

// CHECK#18
NaN = true; 
NaN === true;
if (NaN !== true) {
  $ERROR('#18: NaN = true; NaN === true; NaN === true');
} 

// CHECK#19
NaN = true; 
NaN !== true;
if (NaN !== true) {
  $ERROR('#19: NaN = true; NaN !== true; NaN === true');
} 
