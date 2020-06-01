var data = '{"one": 1, "two": "2"}';
console.log("data: " + data);

data = JSON.parse(data);

console.log("data.one: " + data.one + ":" + typeof data.one);
console.log("data.two: " + data.two + ":" + typeof data.two);
