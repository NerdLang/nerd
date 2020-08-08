function classProto()
{
    this.hello = "Hello";
	function containedProto()
	{
		this.inside = "Inside containedProto";
	}
	this.inception = new containedProto();
}

var gretter = new classProto();

console.log(gretter.hello);
console.log(gretter.inception.inside);
