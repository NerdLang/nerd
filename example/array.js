var _loop = 100;
var _arr = [];
var _res = 0;

for(var i = 0; i < _loop; i++)
{
	_arr[i] = i;
}

for(var j = 0; j < _loop; j++)
{
	_res += _arr[j];
}

console.log(_res);