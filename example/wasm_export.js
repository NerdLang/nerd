var WASM = require("WASM");

// function proto for binding : string(string)
function callFromJS(_data)
{
	if(!_data) WASM.run("document.write('<h1>No Data</h1>');");
	else WASM.run("document.write('<h1>" + _data + "</h1>');");
	return "Executed from WASM";
}

// bind function to be executed in Browser env with Module.callNectar(_functionName, _data);
WASM.bind("callFromJS", callFromJS);

// Fire a JS function to know when env is set up, see wasm.html
WASM.run("WasmLoaded();");