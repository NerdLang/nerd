function test(_one, _two)
{
    if(_two) __NJS_Log_Console(_two);
    else if(_one) __NJS_Log_Console(_one);
    else __NJS_Log_Console("undefined");
}

test();
test("First Arg");
test("First Arg", "Second Arg");

