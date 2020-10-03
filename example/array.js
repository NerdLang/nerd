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

console.log("SLICE:");
console.log("_arr.slice(2):", _arr.slice(2));
console.log("_arr.slice(-1):", _arr.slice(-1));
console.log("_arr.slice(-10):", _arr.slice(-10));
console.log("_arr.slice(3, 6):", _arr.slice(3, 6));
console.log("_arr.slice(3, -6):", _arr.slice(3, -6));


console.log();
console.log("SPLICE:");
var _arr2 = [0,1,2,3,4,5,6,7,8,9]
console.log("_arr2.splice(1): return->", _arr2.splice(1), ", content->", _arr2);

var _arr3 = [0,1,2,3,4,5,6,7,8,9]
console.log("_arr3.splice(3, 40): return->", _arr3.splice(3, 40), ", content->", _arr3);

var _arr4 = [0,1,2,3,4,5,6,7,8,9]
console.log("_arr4.splice(8, 9, 'eight', 'nine', 10): return->", _arr4.splice(8, 9, 'eight', 'nine', 10), ", content->", _arr4);

console.log();

console.log("POP:");
_arr.pop();
console.log("_arr.length after pop(): " + _arr.length);

console.log("_arr.join(':'): " + _arr.join(':'));

var ArrInArr = [["Inception"]];
console.log(ArrInArr[0][0]);

ArrInArr[1] = [["Double Inception"]];
console.log(ArrInArr[1][0][0]);

Array.prototype.slice.call([0,1,2], 2);