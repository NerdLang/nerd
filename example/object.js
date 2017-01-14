var start = {msg:"[+] Started Object Example"};
console.log(start.msg);

var anObject = {a:"ok", b:{color:"blue", age:28}, array:["zero", 1, "two", "three"]};

console.log(anObject.a);

for(var i = 0; i < anObject.array.length; i++)
{
  console.log(anObject.array[i]);
}

var end = [{msg:"[!] Ended Object Example"}];
console.log(end[0].msg);
