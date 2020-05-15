class Greeter
{
	constructor(value)
	{
		this.name = value;
	}
	
	Say()
	{
		console.log("Hello " + this.name);
	}
}

var g = new Greeter("NectarJS");

g.Say();