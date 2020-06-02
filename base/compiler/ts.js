var ts = require("typescript");

function compileTS(_code, _file)
{
	var _program = ts.createProgram([_file], { noResolve: true, module: ts.ModuleKind.CommonJS, target: ts.ScriptTarget.ES2020 });
	const diagnostics = ts.getPreEmitDiagnostics(_program);

	for (var i = 0; i < diagnostics.length; i++ ) 
	{
		var message = diagnostics[i].messageText;
		var file = diagnostics[i].file;
		var filename = file.fileName;
		var error = diagnostics[i].code
		
		var lineAndChar = file.getLineAndCharacterOfPosition(
			diagnostics[i].start
		);

		var line = lineAndChar.line + 1;
		var character = lineAndChar.character + 1;

		console.log(`${_file}:${line}:${character} - error TS${error}: ${message}`);
	}

	if(diagnostics.length)
	{
		console.log();
		if(diagnostics.length == 1) console.log(`Found ${diagnostics.length} error`);
		else console.log(`Found ${diagnostics.length} errors`);
		console.log();
		process.exit(1);
	}

	else _code = ts.transpileModule(_code, { compilerOptions: { noResolve: true, module: ts.ModuleKind.CommonJS, target: ts.ScriptTarget.ES2020 } });;
	
	return _code.outputText;
}

module.exports = compileTS;
