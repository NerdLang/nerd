var WASM = require("WASM");

// function proto for binding : string(string)
function callFromJS(_data)
{
	if(!_data) WASM.run("document.write('<h1>No Data</h1>');");
	else WASM.run("document.write('<h1>" + _data + "</h1>');");
	return "Executed from WASM";
}

function callIntOp(_i)
{
	return _i * 2;
}

// bind function to be executed in Browser env with Module.callNectar(_functionName, _data);
WASM.bind("callFromJS", callFromJS);
WASM.bind("callIntOp", callIntOp);

// Fire a JS function to know when env is set up, see wasm.html
WASM.run("WasmLoaded();");