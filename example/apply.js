function test(arg)
{
	console.log(arg);
}

test("Direct call");
test.apply(null, ["Apply"]);

console.log("Math.min:", Math.min);
console.log("Math.min.apply(null, [4,5,6,1,9]):", Math.min.apply(null, [4,5,6,1,9]));