var fs = require("fs");

fs.writeFileSync("test.njs", "Some content");
fs.appendFileSync("test.njs", "- We add something");
var text = fs.readFileSync("test.njs");
console.log("Text : " + text + " | Size : " + text.length);
fs.unlinkSync("test.njs");
