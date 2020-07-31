// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * @name: S15.10.2.11_A1_T2;
 * @section: 15.10.2.11;
 * @assertion: DecimalEscape :: DecimalIntegerLiteral [lookahead not in DecimalDigit];
 * @description: It is an error if n is greater than the total number of left capturing parentheses in the entire regular expression;
 * @negative;
*/

/\1/.exec("");
/\2/.exec("");
/\3/.exec("");
/\4/.exec("");
/\5/.exec("");
/\6/.exec("");
/\7/.exec("");
/\8/.exec("");
/\9/.exec("");
/\10/.exec("");
