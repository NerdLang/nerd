function _test()
{
	if(!this.a) this.a = 0;
	this.a++;
	return this;
}

var a = _test();
console.log(a);

var _this = {a: 10};
var b = _test.call(_this);
console.log(b);