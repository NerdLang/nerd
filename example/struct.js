Nectar.createStruct("test", "a:string", "b:int", "c:double");

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

// access to non struct member fall back on hashmap
retStruct.NStruct("test").x = "Fallback";
console.log(retStruct.NStruct("test").x);