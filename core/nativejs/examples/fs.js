var fs = require("fs");

fs.writeFileSync("t.txt", "ok\n");
fs.appendFileSync("t.txt", "suite");
console.log(fs.readFileSync("t.txt"));
