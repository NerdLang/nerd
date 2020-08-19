/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
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
