hoistedFunc();

var hoistedVar = "Hello !";

hoistedFunc();

function hoistedFunc()
{
    console.log(hoistedVar);
}

function some(param) {
  if (param) {
    var a = 1;
  }
  return a;
}

console.log("some():", some());
console.log("some(1):", some(1));