
hoistedFunc();

var hoistedVar = "Hello !";

hoistedFunc();

function hoistedFunc()
{
    console.log(hoistedVar);
}