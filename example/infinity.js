// Big number issues #81
// Reported by https://github.com/hikarine3

var x = Infinity;
console.log(x);

let num = 1.0;
for(let i=1;i<=100;i++){
	num *=i;
	console.log(num);
}
