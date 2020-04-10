var _loop = 1000000;
var _arr = __NJS_Create_Array();

var _res = 0;

for(var i = 0; i < _loop; i++)
{
	_arr[i] = i;
}

for(var i = 0; i < 10000; i++)
{
	_res += _arr[i];
}
_arr[1] = 1;
console.log(_arr[1]);