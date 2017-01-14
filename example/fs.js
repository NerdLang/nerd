require("MAIN_PATH/base/libjs/fs.js");


var test = "./test.txt";
fs.writeFileSync(test, "A text !");
console.log(fs.readFileSync(test));
fs.unlinkSync(test);
