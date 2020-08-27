function Mul(_num, _x)
{
	this.i = _num * _x;
}

var m = new Mul(10, 3);

console.dir(m.constructor);
