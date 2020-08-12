/* 
    Example created by Richard https://github.com/raguayGuay
    on issue https://github.com/NectarJS/nectarjs/issues/79
*/

var fs = require("fs-std");
var process = require("process");

var inputFile = fs.readFileSync(process.argv[2]);
var output = {};
output.items = [];
inputFile = inputFile.toString().split("\n");

for(var i = 0; i < inputFile.length; i++) {

  if(inputFile[i] != "") {
    var subitem = {
          uid: inputFile[i],
          type: "",
          title: inputFile[i],
          subtitle: process.argv[3],
          arg: inputFile[i],
          autocomplete: inputFile[i],
          valid: true,
          icon: {
              type: "fileicon",
              path: "~/Desktop"
          }
      };
    output.items.push(subitem);
  }
}

console.log(JSON.stringify(output));