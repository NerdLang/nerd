// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/** * @name: S7.3_A3.4_T1; * @section: 7.3, 7.4; * @assertion: Single line comments can not contain PARAGRAPH SEPARATOR (U+2029) inside; * @description: Insert PARAGRAPH SEPARATOR (\u2029) into single line comment; * @negative */// CHECK#1eval("// single line \u2029 comment");
