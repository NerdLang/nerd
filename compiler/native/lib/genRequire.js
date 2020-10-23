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

var genInclude = require("./genInclude.js");
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
	else if(typeof _obj == "string")
	{
	   console.log("[*] " + _name + ": " + _obj);
	}
	else if(typeof _obj == "object")
	{
		var _platform;
		if(_obj[PLATFORM]) _platform = PLATFORM;
		else if(_obj["default"]) _platform = "default";
		
		if(_obj[_platform] && typeof _obj[_platform] == "object")
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
		  COMPILER.LIBS += _lib[l].replace("__MODULE__", modSource).replace(/{__ARCH__}/g, os.arch()).replace(/{__EXTERN__}/g, extern) + " ";
		}
	}
	else if(typeof _lib == "string")
	{
	  COMPILER.LIBS += _lib.replace("__MODULE__", modSource).replace(/{__ARCH__}/g, os.arch()) + " ";
	}
	else if(typeof _lib == "object")
	{
		var _platform;
		if(_lib[PLATFORM]) _platform = PLATFORM;
		else if(_lib["default"]) _platform = "default";
		
		if(_lib[_platform] && typeof _lib[_platform] == "object")
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

function genRequire(from, src)
{
  // strip comments
  src = strip(src);
  src = genPackage(from, src);
  var _SEARCH = new RegExp(/ *require\(['"](.*?)['"]\)/);
  var seek = ["require('", "require(\""];

  var _match = src.match(_SEARCH);

  while(_match)
  {
    var addSource = _match[1];
	
	if(CACHE[addSource])
	{
		src = src.replace(_SEARCH, CACHE[addSource]);
		var _match = src.match(_SEARCH);
	}
	else 
	{
	
		var modSource = "";
		var fileSource;
		if(addSource.indexOf(COMPILER.PATH) > -1)
		{
		  modSource = addSource;
		}
		else
		{
		  modSource = path.join(from + addSource);
		}
		var trySource = [modSource, modSource + "/" + "index.js", from + "nectar_modules/" + addSource + "/index.js", NECTAR_PATH + "/nectar_modules/" + addSource + "/index.js", from + "node_modules/" + addSource + "/index.js", NECTAR_PATH + "/node_modules/" + modSource + "/index.js", modSource + ".js",
						modSource, modSource + "/" + "index.ts", from + "nectar_modules/" + addSource + "/index.ts", NECTAR_PATH + "/nectar_modules/" + addSource + "/index.ts", from + "node_modules/" + addSource + "/index.ts", NECTAR_PATH + "/node_modules/" + modSource + "/index.ts", modSource + ".ts"];
		var newSrc = "";
		for(var i = 0; i < trySource.length; i++)
		{
		  try
		  {
			modSource = path.dirname(trySource[i]) + "/";
			newSrc = fs.readFileSync(trySource[i]).toString();
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
				if(pkg.nectar)
				{
					if(pkg.nectar.comment)
				  {
					  showModuleComment(pkg.nectar.comment, pkg.name);
				  }
				  if(pkg.nectar.env)
				  {
					if(pkg.nectar.env.indexOf(COMPILER.ENV.name) < 0)
					{
					  console.error("NectarJS:\n\n[!] module " + addSource + " doesn't support env : " + COMPILER.ENV.name + " only these : " + pkg.nectar.env);
					  process.exit(1);
					}
				  }

				  if(pkg.nectar.target)
				  {
					if(!COMPILER.TARGET)
					{
					  console.error("NectarJS:\n\n[!] module " + addSource + " require one of these targets : " + pkg.nectar.target + ". None specified");
					  process.exit(1);
					}
					else if(pkg.nectar.target.indexOf(COMPILER.TARGET) < 0)
					{
					  console.error("NectarJS:\n\n[!] module " + addSource + " require one of these targets : " + pkg.nectar.target + ". " + COMPILER.TARGET + " specified");
					  process.exit(1);
					}
				  }

				  if(pkg.nectar.expose)
				  {
					COMPILER.EXPOSE = COMPILER.EXPOSE.concat(pkg.nectar.expose);
					COMPILER.GLOBAL = COMPILER.GLOBAL.concat(pkg.nectar.expose);
				  }

				  if(pkg.nectar.lib)
				  {
						addModuleLib(pkg.nectar.lib, modSource);
				  }

				}
			  }
			  catch(e)
			  {
				console.log("NectarJS:\n\n[!] " + e + " -> " + pkgPath.split("/").splice(-3).join("/"))
			  }
			}

			// EXPOSE VAR
			var _expose = {};
			if(pkgObject && pkgObject.nectar && pkgObject.nectar.expose) _expose = pkgObject.nectar.expose;

			// READ ONLY VAR
			if(pkgObject && pkgObject.nectar && pkgObject.nectar.read_only) COMPILER.READ_ONLY = COMPILER.READ_ONLY.concat(pkgObject.nectar.read_only);
			
			if(!CLI.cli["--no-check"]) LINT(newSrc, trySource[i], _expose);

			break;
		  }
		  catch (e) {}
		}

		if(newSrc.length == 0)
		{
		console.log("[!] Warning : index file of module " + addSource + " seems empty");
		}

		var ext = "js";
		if(fileSource && fileSource.split)
		{
			var _Ext = fileSource.split(".");
			if(_Ext.length > 1) ext = _Ext[_Ext.length - 1];
			
			if(ext == "ts") newSrc = compileTS(newSrc, fileSource);
			
			newSrc = genInclude(path.resolve(modSource) + "/", newSrc);


			var reqFN = "__MODULE_" + Math.random().toString(36).substr(2, 10);
			COMPILER.ENV.check.globals[reqFN] = false;
			CACHE[addSource] = reqFN + "()";

			src = src.replace(_SEARCH, reqFN + "()");

			newSrc = "function " + reqFN + "(){\nvar module = __NJS_Create_Object();\n" + newSrc;
			newSrc = newSrc.replace(/(module\.exports *= *.*)$/g, "$1;");
			newSrc += "return module.exports;\n}";
			newSrc = genRequire(modSource, newSrc);

			COMPILER.REQUIRE += newSrc + ";";
		}
		else src = src.replace(_SEARCH, "");

		var _match = src.match(_SEARCH);
	}
  }
  return src;
}
