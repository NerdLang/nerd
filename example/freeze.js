var a = {value: "Frozen" };

Object.freeze(a);

a.value = "Let it go";

console.log(a.value);