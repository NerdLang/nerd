function test(v)
{
  this.a = 1;
  return 1;
}
function bench()
{
  var j = 0;
  var i = 1000000;

  while(i--)
  {
    var a = {b:"ok", c:2};
    a.b = "a";
    a.c = 10;
    j = j + test(a);
  }
  console.log(j);
  var b;
  return b;
}

bench();
var aString = "MyString";
console.log(aString.length);
