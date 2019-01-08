
/*
var fs = require("fs");

fs.writeFileSync("test.njs", "Some content");
fs.appendFileSync("test.njs", "- We add something");
var text = fs.readFileSync("test.njs");
console.log("Text : " + text + " | Size : " + text.length);
fs.unlinkSync("test.njs");

/*

var a = ["zero", "one", "two", "three", "four", "...", 6, 7, 8, 9, "End"];
for(var i = 0; i < 11; i++)
{
console.log(i);
console.log(a[i]);
}
console.log(a.length);

/*

var fs = require("fs");

fs.writeFileSync("test.njs", "Some content");
fs.appendFileSync("test.njs", "- We add something");
console.log(fs.readFileSync("test.njs"));
fs.unlinkSync("test.njs");

/*

function fibonacci(n)
{
  if (n < 2)  return n;
  return fibonacci(n - 2) + fibonacci(n - 1);
}

//console.log(fibonacci(40));
console.log(fibonacci(10));
/*
var led = require("smt32-led");
*/
/*
require("arduino-simple-lcd");

const msg = "Salut Mick !";

function setup()
{
  arduino_LiquidCrystal(8, 9, 4, 5, 6, 7); // set singleton for LiquidCrystal
  arduino_beginLCD(16, 2); // Begin LCD on 16 x 2 screen
  arduino_printLCD(msg);
}

function loop()
{
  arduino_setCursorLCD(0, 1); // put the cursor in left on the second line
  arduino_printLCD("T:" + arduino_seconds() + "s ->" + typeof arduino_millis()); // print number of seconds since arduino start
  arduino_delay(1000); // wait for 1 second
}



const PIN_LED = 10;



function setup()
{
  arduino_pinMode(PIN_LED, arduino_HIGH);
}

function loop()
{
  arduino_digitalWrite(PIN_LED, arduino_HIGH);
  arduino_delay(500);
  arduino_digitalWrite(PIN_LED, arduino_LOW);
  arduino_delay(100);
}

/*
var b = 9;
var a = 3;
console.log(a); console.log(b);

var http = require("http");
var _srv = http.server.createServer("127.0.0.1", 8080);
_srv.listen();

var aa = {};
aa.b = function(){ return "Yeah !";};
console.log(aa.b());

var ab = {};
ab.b = "ok";
console.log(ab.b);

var _str = "ok";
console.log(_str.length);

function cb(){console.log("IN CB");}
function BLa(_cb)
{
  _cb();
}
BLa(cb);




/*

var CB = function(_str)
{
  console.log(_str);
}

var test = function(_cb, _str)
{
  _cb(_str);
}

test(CB, "CB");
//test(console.log);
//test(cb);
//console.log("ok")
//_srv.listen(test);
/*
var fs = require("fs");
var _text = fs.readFileSync("file.txt");
console.log(_text);
//*/
/*
var child_process = Require("child_process");
var _result = child_process.execSync("ps");
console.log(_result);
//*/

/*
function fibonacci(n)
{
  if (n < 2)  return n;
  return fibonacci(n - 2) + fibonacci(n - 1);
}


console.log(fibonacci(45));

/*
global.ok = "ok";

function test()
{
  console.log(ok);
}
test();
*/
/*
var a = [1,2,3]
console.log(a[1]);
*/
/*
function ok(a)
{
  function bla()
  {
    __NJS_Log_Console(a);
    return a;
  }
  bla();
  return a;
}
ok("ok");
*/
/*

var a = { b: "ok"};
var b = console.log(a.b);
console.log(b);
b = "blabla";
console.log(b);
/*
console.log(a.b());
/*
function a()
{
  return "ok";
}
__NJS_Log_Console(a());

/*
var _main = {test:"blablabla", "a":{b:{c:1}}};

var _t = _main.a.b.c++;

__NJS_Log_Console("t :" + _t + " -> main : " + _main.a.b.c);
*/


/*
var _bool = 1==1;
console.log(2*2);
if(_bool) console.log("ok");

var a = [1,2,["b", "c", "d"]];
var g = a[2];
var c = g[0];
console.log(g[3]);

var bb = "abcde"
console.log(bb[1]);


var aa = "test";
console.log(aa+1);

for(var i = 0; i < 5 ; i++)
{
  console.log("ok -> " + i);
}

var j = 5;
while(j>0)
{
  console.log("while -> " + j);
  j--;
}

function Block(x,y)
{
  function nested()
  {
    function nest2()
    {
      console.log(x);
      return "";
    }
    nest2();
    return "0";
  }
  nested();
  return "";
}
Block("b",20);
*/
/*
var obj = {};
a = "ok";
var b = 3+true;
var cc = 100;
var d = "42";
var fuck = "FUCK";
var e = parseInt(d);
console.log("test" + e);
console.log(1 + e);
console.log(typeof e);
console.log(typeof d);
console.log(typeof cc);
console.log(b);
/*
console.log(a);
console.log(b);
console.log(c);
console.log(d);
console.log(__njs_typeof(d));
console.log(e);
console.log(__njs_typeof(e));

function test()
{
  function bla(){return fuck;}
  return bla();
}

var _ret = test();
console.log("RET");
console.log(_ret);

var z = {};
console.log(z);
*/
