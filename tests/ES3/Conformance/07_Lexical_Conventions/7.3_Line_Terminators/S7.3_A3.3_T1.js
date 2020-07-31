// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/** * @name: S7.3_A3.3_T1; * @section: 7.3, 7.4; * @assertion: Single line comments can not contain LINE SEPARATOR (U+2028) inside; * @description: Insert LINE SEPARATOR (\u2028) into single line comment; * @negative */// CHECK#1eval("// single line \u2028 comment");
