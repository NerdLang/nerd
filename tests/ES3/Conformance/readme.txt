1. All tests must have .js extension.

2. Naming of *.js files is subject to a following rule: 

   * First symbols referred to standard item. Number of Chapter, 
     section, subsection with the dots between and prefix "S".
   * Then "_" symbol appears.
   * Then number of assertion with prefix "A".
   * Then "_" symbol appears.
   * Then number of test with prefix "T".

3. Every test should provide additional information about itself. 
   This information is placed in comments and is divided into several special 
   sections. Every special section has a name. Syntax of defining special 
   information in .js comments is: "@" symbol first, section name, and value(s) 
   after colon till the semicolon appear. Number of values divided by comma symbol. 
   Then end of line should be typed. Available common sections are:

   @name - same as file name without extension.
   @section - links to paragraphs of ECMAScript standard this test belongs to.  
      Paragraphs must be separated by comma. Typical paragraph consist of numbers 
      separated by dots, example is: 11.3.1 (which corresponds to paragraph named 
      "Postfix Increment Operator" in ECMAScript standard). First paragraph in 
      @section means main paragraph for which this test is denoted to, others are 
      paragraphs which are also significant for the test to pass.
   @assertion - an assertion which is tested by this test.
   @description - provide information about test (optional tag).
   @negative - signals that test must failed(like incorrect syntax tests for exam).

   Other sections (which are not described here) are stored as java Properties.

   Example: 
   /**
    * @name: S11.3.1_A1.1_T1;
    * @section: 11.3.1, 11.6.3, 7.3;
    * @assertion: Line Terminator between LeftHandSideExpression and ++ are not allowed;
    * @description: Check Line Feed;
    * @negative
   */
