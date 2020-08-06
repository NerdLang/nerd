// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.1.1.2_R4;
 * @section: 15.1.1.2, 11;
 * @description: The Infinity is not ReadOnly, check Operators that use ToNumber;   
*/

// CHECK#1
Infinity = true; 
Infinity++; 
if (Infinity !== 2) {
  $ERROR('#1: Infinity = true; Infinity++; Infinity === 2');
} 

// CHECK#2
Infinity = true; 
Infinity--; 
if (Infinity !== 0) {
  $ERROR('#2: Infinity = true; Infinity--; Infinity === 0');
} 

// CHECK#3
Infinity = true; 
++Infinity; 
if (Infinity !== 2) {
  $ERROR('#3: Infinity = true; ++Infinity; Infinity === 2');
} 

// CHECK#4
Infinity = true; 
--Infinity;
if (Infinity !== 0) {
  $ERROR('#4: Infinity = true; --Infinity; Infinity === 0');
} 

// CHECK#5
Infinity = true; 
+Infinity; 
if (Infinity !== true) {
  $ERROR('#5: Infinity = true; +Infinity; Infinity === true');

} 
// CHECK#6
Infinity = true; 
-Infinity;
if (Infinity !== true) {
  $ERROR('#6: Infinity = true; -Infinity; Infinity === true');
} 
// CHECK#7
Infinity = true; 
Infinity * 1;
if (Infinity !== true) {
  $ERROR('#7: Infinity = true; Infinity * 1; Infinity === true');
} 

// CHECK#8
Infinity = true; 
Infinity / 1;
if (Infinity !== true) {
  $ERROR('#8: Infinity = true; Infinity / 1; Infinity === true');
} 

// CHECK#9
Infinity = true; 
Infinity % 1;
if (Infinity !== true) {
  $ERROR('#9: Infinity = true; Infinity % 1; Infinity === true');
} 

// CHECK#10
Infinity = true; 
Infinity + 1;
if (Infinity !== true) {
  $ERROR('#10: Infinity = true; Infinity + 1; Infinity === true');
} 

// CHECK#11
Infinity = true; 
Infinity - 1;
if (Infinity !== true) {
  $ERROR('#11: Infinity = true; Infinity - 1; Infinity === true');
} 

// CHECK#12
Infinity = true; 
Infinity > 1;
if (Infinity !== true) {
  $ERROR('#12: Infinity = true; Infinity > 1; Infinity === true');
} 

// CHECK#13
Infinity = true; 
Infinity < 1;
if (Infinity !== true) {
  $ERROR('#13: Infinity = true; Infinity < 1; Infinity === true');
} 

// CHECK#14
Infinity = true; 
Infinity >= 1;
if (Infinity !== true) {
  $ERROR('#14: Infinity = true; Infinity >= 1; Infinity === true');
} 

// CHECK#15
Infinity = true; 
Infinity <= 1;
if (Infinity !== true) {
  $ERROR('#15: Infinity = true; Infinity <= 1; Infinity === true');
} 

// CHECK#16
Infinity = true; 
Infinity == true;
if (Infinity !== true) {
  $ERROR('#16: Infinity = true; Infinity == true; Infinity === true');
} 

// CHECK#17
Infinity = true; 
Infinity != 1;
if (Infinity !== true) {
  $ERROR('#17: Infinity = true; Infinity != 1; Infinity === true');
} 

// CHECK#18
Infinity = true; 
Infinity === true;
if (Infinity !== true) {
  $ERROR('#18: Infinity = true; Infinity === true; Infinity === true');
} 

// CHECK#19
Infinity = true; 
Infinity !== true;
if (Infinity !== true) {
  $ERROR('#19: Infinity = true; Infinity !== true; Infinity === true');
} 
