var _loop = 10;
var _arr = [];
var _res = 0;

for(var i = 0; i < _loop; i++)
{
	_arr[i] = i;
	var a = 1;
	var b;
}

for(var j = 0; j < _loop; j++)
{
	_res += _arr[j];
}

console.log(_res);
console.log(_arr);
console.log("_arr.length: " + _arr.length);

console.log("_arr.slice(3, 6): ", _arr.slice(3, 6));
console.log("_arr.slice(3, -6): ", _arr.slice(3, -6));


_arr.pop();
console.log("_arr.length after pop(): " + _arr.length);

console.log("_arr.join(':'): " + _arr.join(':'));

var ArrInArr = [["Inception"]];
console.log(ArrInArr[0][0]);

ArrInArr[1] = [["Double Inception"]];
console.log(ArrInArr[1][0][0]);

Array.prototype.slice.call([0,1,2], 2);