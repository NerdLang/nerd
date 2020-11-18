Nectar.createStruct("test", "a:std::string", "b", "c");

function Test()
{
	var testStruct = Nectar.initStruct("test");
	testStruct.NStruct("test").a = "Hello Struct!";
	console.log(testStruct.NStruct("test").a);
	return testStruct
}

var retStruct = Test();
retStruct.NStruct("test").a = "After return";
console.log(retStruct.NStruct("test").a);