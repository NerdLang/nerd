var t1 = performance.now();

var str = "";

for(var i = 0; i < 1000; i++)
{
	str += i;
}

var t2 = performance.now();

console.log(performance.timeOrigin);
console.log(t1);
console.log(t2);
console.log("Perf: " + (t2 - t1) + "ms");