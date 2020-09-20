/*
	testClass proposed by @wesley1989 on Discord to test classes implementation
*/
function something(a) {
  return a
}

class Test{
  constructor(a){
    if(a instanceof Test){
      //this not working
      a.map(something)
    }else{
      return undefined
    }
  }
  map(execFunc) {
    execFunc()
  }
  static map(execFunc) {
    execFunc()
  }

}
var t = new Test(null)
t.map(something)
Test.map(something)

var t2 = new Test(t)
console.log(t,t2);

