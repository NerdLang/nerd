var proc = require("child_process");

var e = proc.execSync("ps");
console.log(e);
console.log(e.length);
