class Greeter
{
	constructor(value)
	{
		this.name = value;
	}
	
	Say()
	{
		console.log("In Method Say");
	}
}

var g = new Greeter("NectarJS");

g.Say();