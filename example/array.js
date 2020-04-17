var _loop = 100;
var _arr = [];

var _res = 0;

for(var i = 0; i < _loop; i++)
{
	_arr[i] = i;
}

for(var i = 0; i < _loop; i++)
{
	_res += _arr[i];
}

console.log(_res);