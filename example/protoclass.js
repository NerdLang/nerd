function Proto(a)
{
  this.obj = "un obj";
  if(a == 1)
  {
    this.a = [1,{a:"FROM THIS !"}];
    return a;
  }
  a = {a:[1,{a:"FROM A !"}]};
  //console.log(this.a[1].a);
  return a;
}

var b = Proto(2);
var c = new Proto(1);

console.log(b.a[1].a);
console.log(c.a[1].a);
