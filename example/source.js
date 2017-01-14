
function fibonacci(n)
{
  if (n < 2)  return n;
  return fibonacci(n - 2) + fibonacci(n - 1);
}

console.log("BEFFORE FIBO");
console.log(fibonacci(5));
console.log("AFTER FIBO");

function fibonacci2(n)
{
  if (n <= 1)  return 1;
  return fibonacci2(n - 2) + fibonacci2(n - 1);
}


function fibonacci3(n)
{
  if (n < 2)  return n;
  return fibonacci2(n - 2) + fibonacci2(n - 1);
}

function testFn()
{

  var i = 0;
  switch(i)
  {
    case 0:
      console.log(3);
      break;
    default:
      console.log("LA");
      break;
  }

  console.log(i);
  i = "hello";
  console.log(i);
  return i;

}

testFn();
bla();
function bla()
{
  test();
  var m = 0;
  var n = "yo";
  console.log(n);
  n = m;
  console.log(n);
  m = n;
  m = "ok";
  console.log(m);
  return m;
}
bla();

var d;
d = "Null to string";
var c;
c = d;

echo(d, c);

function echo(a,b)
{
	console.log(a);
	console.log(b);
}

function TestArray()
{
   var ret = [1, "str", "OK", ["3-0", ["3-1-0", "a", "b", ["a", 1, [10, "a"]]]]];
   console.log(ret[3][0]);
   return ret;
}
var testResult = TestArray();
console.log("-------------");
console.log(testResult[0]);

function test()
{
  var a = 0;
  this.obj = "un obj";
  if(a == 1)
  {
    this.a = [1,{a:"ICI !"}];
    return a;
  }
  a = {a:[1,{a:"LA !"}]};



  this.a = {};
  this.a.b = "ok";
  console.log(this.a.b);
  this.a.b = {};
  this.a.b.c = "Youhou !";
  console.log(this.a.b.c);
  this.a.b.d = "DDDD";
  console.log(this.a.b.d);
  this.a.b.c = 1;
  console.log(this.a.b.c);

  this.array = [{a:"IN A"},"un",2];
  this.array = {};
  this.array.point = 1;
  logConsole(this.array.point);

  var array = [{a:"ok"}, 2];
  var a2 = [0,1,2,3,4, {cinq:"six"}];
  console.log(a2[5].cinq);

  var alpha = {};
  alpha.beta = {};
  alpha.beta.ceta = "in Ceta !"
  console.log(alpha.beta.ceta);

  this.y = 3;

  var aa = {name:"ok", b:{c:{g:"ok",h:"",i:""}, b:"hoho", d:{a:"a", b:1}}, color:"blue"};
  var ab = [0,1,2,["a","b","c","d",["mixed",1,"ok"]]]
  console.log(ab[3][0]);
  var bb = {a: "ok"};

  return a;
}

function blabla()
{
  var a = {b:true};
  console.log(a.b);
}

test();
blabla();

var alpha = "ok";
alpha = {b:"ha", c:"ho", d:{h:"ok"}};
alpha = {b:{}, c:[], d:"ok"};
alpha.b.a = "alpha";
var teta = "teta";
alpha.b.t = teta;
console.log(alpha.b.a);
console.log(alpha.b.t);
var array = 2;
array = [{a:"b"}];
console.log(array[0].a);


var adrien = {name: "Adrien", house:"toto", color:"blue", "age": 28};
var lucie = {name: "Lucie", appart:"Limoux", color:"rose,blanc,dorée", "age": 24};
var avelyne = {yo:"a", color:"youp", tarla:"ok"};

console.write("adrien.color : ");console.log(adrien.color);
console.write("lucie.name : ");console.log(lucie.name);
console.write("avelyne.yo : ");console.log(avelyne.yo);

var peopleArray = [adrien, lucie, avelyne];
console.write("peopleArray[0].name = "); console.log(peopleArray[0].name);
