/*
	Copyright (c) 2021 NerdLang - Adrien THIERRY and contributors

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/

module.exports = genRequire;
var fs = require("fs");
var CACHE = {};

function showModuleComment(_obj, _name)
{
	if(Array.isArray(_obj))
	{
		for(var l = 0; l < _obj.length; l++ )
		{
		  console.log("[*] " + _name + ": " + _obj[l]);
		}
	}
	else if(typeof(_obj) == "string")
	{
	   console.log("[*] " + _name + ": " + _obj);
	}
	else if(typeof(_obj) == "object")
	{
		var _platform;
		if(_obj[PLATFORM]) _platform = PLATFORM;
		else if(_obj["default"]) _platform = "default";
		
		if(_obj[_platform] && typeof(_obj[_platform]) == "object")
		{
			var currentCompiler =  COMPILER.COMPILER.split(" ")[0];
			var _compiler;
			if(_obj[_platform][currentCompiler]) _compiler = currentCompiler;
			else if(_obj[_platform]["default"]) _compiler = "default";
			
			if(_obj[_platform][_compiler]) showModuleComment(_obj[_platform][_compiler], _name);
		}
		else if(_obj[_platform]) showModuleComment(_obj[_platform], _name);
	}
}

function addModuleLib(_lib, modSource)
{
	if(Array.isArray(_lib))
	{
		for(var l = 0; l < _lib.length; l++ )
		{
		  COMPILER.LIBS += _lib[l].replace(/{__MODULE__}/g, path.resolve(modSource)).replace(/{__ARCH__}/g, os.arch()).replace(/{__EXTERN__}/g, extern) + " ";
		}
	}
	else if(typeof(_lib) == "string")
	{
	  COMPILER.LIBS += _lib.replace(/{__MODULE__}/g, modSource).replace(/{__ARCH__}/g, os.arch()).replace(/{__EXTERN__}/g, extern) + " ";
	}
	else if(typeof(_lib) == "object")
	{
		var _platform;
		if(_lib[PLATFORM]) _platform = PLATFORM;
		else if(_lib["default"]) _platform = "default";
		
		if(_lib[_platform] && Array.isArray(_lib[_platform]))
		{
			addModuleLib(_lib[_platform], modSource);
		}
		if(_lib[_platform] && typeof(_lib[_platform]) == "object")
		{
			var currentCompiler =  COMPILER.COMPILER.split(" ")[0];
			var _compiler;
			if(_lib[_platform][currentCompiler]) _compiler = currentCompiler;
			else if(_lib[_platform]["default"]) _compiler = "default";
			
			if(_lib[_platform][_compiler]) addModuleLib(_lib[_platform][_compiler], modSource);
		}
		else if(_lib[_platform]) addModuleLib(_lib[_platform], modSource);
	}
}

function genRequire(from, addSource, _env, _name)
{
	var modSource = "";
	var fileSource;
	
	if(COMPILER.DIR.length > 0)
	{
		from = COMPILER.DIR[COMPILER.DIR.length - 1];
	}
	if(addSource.indexOf(from) > -1)
	{
	  modSource = addSource;
	}
	else
	{
	  modSource = path.join(from + addSource);
	  
	}
	COMPILER.DIR.push(__dirname + "/");
	var trySource = [modSource, modSource + "/" + "index.ng", from + "nerd_modules/" + addSource + "/index.ng", NERD_PATH + "/nerd_modules/" + addSource + "/index.ng", modSource + ".ng", modSource, ];
	var newSrc = "";
	for(var i = 0; i < trySource.length; i++)
	{
	  try
	  {
		modSource = path.dirname(trySource[i]) + "/";
		newSrc = fs.readFileSync(trySource[i]).toString();
		
		if(CLI.cli["--env"] && CLI.cli["--env"].argument == "js" && addSource != "Module")
		{
			newSrc = `var module = require("Module");` + newSrc;
		}
		
		if(CACHE[addSource])
		{
			COMPILER.DIR.pop();
			return {add: false, module: CACHE[addSource], code: ""}
		}
		
		fileSource = trySource[i];
		
		var pkgPath = path.join(modSource, "package.json");
		var pkgObject;
		if(fs.existsSync(pkgPath))
		{
		  var pkg = fs.readFileSync(pkgPath);
		  try
		  {
			pkg = JSON.parse(pkg);
			pkgObject = pkg;
			if(pkg.nerd)
			{
			  if(pkg.nerd.message)
			  {
				  showModuleComment(pkg.nerd.message, pkg.name);
			  }
			  if(pkg.nerd.env)
			  {
				if(pkg.nerd.env.indexOf(COMPILER.ENV.name) < 0)
				{
				  console.error("Nerd:\n\n[!] module " + addSource + " doesn't support env : " + COMPILER.ENV.name + " only these : " + pkg.nerd.env);
				  process.exit(1);
				}
			  }

			  if(pkg.nerd.target)
			  {
				if(!COMPILER.TARGET)
				{
				  console.error("Nerd:\n\n[!] module " + addSource + " require one of these targets : " + pkg.nerd.target + ". None specified");
				  process.exit(1);
				}
				else if(pkg.nerd.target.indexOf(COMPILER.TARGET) < 0)
				{
				  console.error("Nerd:\n\n[!] module " + addSource + " require one of these targets : " + pkg.nerd.target + ". " + COMPILER.TARGET + " specified");
				  process.exit(1);
				}
			  }
			  /*
			  if(pkg.nerd.expose)
			  {
				COMPILER.EXPOSE = COMPILER.EXPOSE.concat(pkg.nerd.expose);
				COMPILER.GLOBAL = COMPILER.GLOBAL.concat(pkg.nerd.expose);
			  }
			  */

			  if(pkg.nerd.lib)
			  {
					addModuleLib(pkg.nerd.lib, modSource);
			  }

			}
		  }
		  catch(e)
		  {
			console.log("Nerd:\n[!] " + e + " -> " + pkgPath.split("/").splice(-3).join("/"))
		  }
		}

		break;
	  }
	  catch (e) {}
	}

	var ext = "nd";
	if(fileSource && fileSource.split)
	{
		var _Ext = fileSource.split(".");
		if(_Ext.length > 1) ext = _Ext[_Ext.length - 1];
		
		
		var _newEnv = createEnv(modSource);
		parseCode(newSrc, 0, _newEnv);
		parseAST(_newEnv);
		var _generated = generateCode(_newEnv);

		var reqFN = "__MODULE_" + Math.random().toString(36).substr(2, 10);
		addVar(reqFN, _env);
		//CACHE[addSource] = reqFN + "(" + _name + ")";
		CACHE[addSource] = reqFN + "(__NERD_THIS)";

		newSrc = "NerdCore::Global::var " + reqFN + " = NerdCore::VAR(NerdCore::Enum::Type::Function, new NerdCore::Type::function_t([&](NerdCore::VAR& __NERD_THIS, NerdCore::VAR* __NERD_VARARGS, int __NERD_VARLENGTH, void* __NERD_PTR = nullptr) mutable{\n";
		newSrc += _generated;
		newSrc += "return NerdCore::Global::null;\n}));";

		COMPILER.REQUIRE += newSrc + ";"
		COMPILER.DIR.pop();
		//return {add: true, module: reqFN + "(" + _name + ")", code: newSrc}
		return {add: true, module: reqFN + "(__NERD_THIS)", code: newSrc}
	}
	else
	{
		error("[!] module unknown: " + addSource);
	}

}