#!/usr/bin/env node
// TODO : add babel visitors for missing parts

/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


var VALID_COMPILER = ["native"];

global.fs = require('fs');
global.os = require('os');
global.path = require('path');
global.process = require('process');
global.querystring = require('querystring');
global.child_process = require('child_process');
global.execSync = child_process.execSync;
global.extern = path.join(__dirname, "extern");

global.PACKAGE = require(path.join(__dirname, "package.json"));
global.VERSION = PACKAGE.version;

global.NJS_ENV = {};

var parseCLI = require('./base/cli/cliParser.js');
var coreHttp = require('./base/util/httpUtils.js');
var getExt = require('./base/util/getExt.js');
var getTips = require('./base/util/getTips.js');
var Flash = require('./base/util/flash.js');
global.rmdir = require("./base/util/rmdir.js");
var CURRENT = process.cwd();
var TARGET = require('./base/compiler/target.js');
global.LINT = require("./base/util/lint.js");
var PLATFORM = os.platform();
var ARCH = os.arch();

global.COMPILER = {};
global.NECTAR_PATH = __dirname;
var DEFAULT_COMPILER = "native";

global.CLI = parseCLI(process.argv);

if(CLI.error)
{
  console.log(CLI.msg);
  return;
}

var ACTION = "build";
if(CLI.cli["--help"] || CLI.cli["-h"]) ACTION = "help";
else if(CLI.cli["--example"] || CLI.cli["--examples"]) ACTION = "example";
else if(CLI.cli["--version"] || CLI.cli["-v"]) ACTION = "version";
else if(CLI.cli["--project"]) ACTION = "showproject";
else if(CLI.cli["--clean"] || CLI.cli["--purge"]) ACTION = "clean";
else if(CLI.cli["--installEMSDK"]) ACTION = "installEMSDK";

switch(ACTION)
{
  case "version":
    showVersion();
    break;

  case "help":
    Help();
    break;

  case "example":
    copyExample();
    break;

  case "showproject":
    showProject();
    break;

  case "build":
    Build();
    break;

  case "clean":
    Clean();
    break;
  
  case "installEMSDK":
    require(path.join(NECTAR_PATH, "base", "util", "installEmsdk.js"))();
    break;

  default:
    Help();
    break;
}

function getExampleFiles (dir, list)
{
    list = list || [];
    var files = fs.readdirSync(dir);
    for (var i in files)
    {
        var name = dir + path.sep + files[i];
        if (fs.statSync(name).isDirectory())
        {
            getExampleFiles(name, list);
        }
        else
        {
            list.push(name);
        }
    }
    return list;
}

function copyExample()
{
  var folder = ["c"];
  var list = getExampleFiles(path.join(__dirname, "example"));
  for(var l in list)
  {
    var name = list[l].split(path.sep);
    if(name[name.length - 2] && folder.indexOf(name[name.length - 2]) > -1)
    {
      try
      {
        fs.mkdirSync(name[name.length - 2]);
      }catch(e){}
      name = name[name.length - 2] + "/" + name[name.length - 1];
    }
    else name = name[name.length - 1];
    var content = fs.readFileSync(list[l]);
    fs.writeFileSync(name, content);
    console.log("[+] Copy of " + name + " done");
  }
}

function showProject()
{
  var project = "project.json";
  if(CLI.stack && CLI.stack.length > 0)
  {
    project = CLI.stack[CLI.stack.length - 1];
  }
  try
  {
    var pConf = fs.readFileSync(project);
    var jConf = JSON.parse(pConf);
    printProject(jConf);
  }
  catch (e)
  {
    console.dir("[!] Error : " + e.message);
  }

}

function Clean(purge)
{
  var project = "project.json";
  if(CLI.stack && CLI.stack.length > 0)
  {
    project = CLI.stack[CLI.stack.length - 1];
  }
  try
  {
    var pConf = fs.readFileSync(project);
    var jConf = JSON.parse(pConf);
    if(jConf.main)
    {
      if( (CLI.cli["--purge"] || purge) && jConf.out)
      {
        var outFile = jConf.out;
        if(jConf.out[0] != path.sep)
        {
          outFile = path.join(path.dirname(project), jConf.out);
        }
        try{fs.unlinkSync(outFile);}catch(e){}
      }
    }
    try{fs.unlinkSync(project)}catch(e){}
  }
  catch (e)
  {
    console.dir("[!] Error : " + e.message);
  }
}

function printProject(obj)
{
  console.log();
  console.log("[*] Project configuration :\n");
  console.log("Main file : " + obj.main);
  console.log("Output    : " + obj.out);
  console.log("Target    : " + obj.target);
  console.log("Preset    : " + obj.preset);
  console.log();
}

function Build(prepare)
{ 
  if(CLI.cli["--build"]) DEFAULT_COMPILER = CLI.cli["--build"].argument;
  else if(CLI.cli["-b"]) DEFAULT_COMPILER = CLI.cli["-b"].argument;
  
  COMPILER = require(path.join(__dirname, "compiler", DEFAULT_COMPILER, "compiler.js"));
  
  if(CLI.cli["--compiler"] && CLI.cli["--compiler"].argument) COMPILER.COMPILER = CLI.cli["--compiler"].argument;
  else if(CLI.cli["-c"] && CLI.cli["-c"].argument) COMPILER.COMPILER = CLI.cli["-c"].argument;

  var preset;
  if(CLI.cli["--preset"] && CLI.cli["--preset"].argument) preset = CLI.cli["--preset"].argument;

  var env;
  if(CLI.cli["--env"] && CLI.cli["--env"].argument) env = CLI.cli["--env"].argument;

  if(!preset) preset = "none";
  COMPILER.preset = preset;
  
  if(!env) env = "std";

	var target;
  if(CLI.cli["--target"] && CLI.cli["--target"].argument) target = CLI.cli["--target"].argument;
	COMPILER.TARGET = target;
	
	var spec;
  if(CLI.cli["--spec"] && CLI.cli["--spec"].argument) spec = CLI.cli["--spec"].argument;
	COMPILER.SPEC = spec;

  if(!CLI.stack || CLI.stack.length < 1)
  {
    console.error("[!] Missing file to compile or project.json path, 'nectar --help' if you need help");
    return;
  }
  else
  {
	var QUIET = false;
    var _in = CLI.stack[0];
    COMPILER.IN = _in;
    fs.readFile(_in, function(err, fileData)
    {
      if(err)
      {
        console.error("[!] Error : " + err.message);
        return;
      }
      else
      {

        /* CHECKING */
        Check(_in);
        /* END CHECKING */

        var ext = "js";
        var _Ext = _in.split(".");
        if(_Ext.length > 1) ext = _Ext[_Ext.length - 1];

		/*** CREATE COMPIL ENV ***/
		var _current = process.cwd();
		var _npath = path.join(_current, ".nectar");
		try { fs.mkdirSync(_npath); } catch(e){};
		var _tmp = path.join(_npath, Math.random().toString(36).substr(2, 5));
		try { fs.mkdirSync(_tmp); } catch(e){};
		
		/*** PREPARE SRC ***/
		COMPILER.Prepare(_tmp);

        var fProject = false;
        var prjectConf = {};
        if(path.basename(_in) == "project.json")
        {
          try
          {
              projectConf = JSON.parse(fileData);
              fProject = true;
              single = false;
          }
          catch (e)
          {
            console.error("[!] Error with project.json : " + e.message);
            return;
          }
        }

		/*** GET FILES NAME ***/
		var _binoutput = "";
		if(fProject)
		{
			_binoutput = projectConf.out;
		}
		else _binoutput = path.basename(_in).slice(0, path.basename(_in).length - path.extname(_in).length);
		
		if(CLI.cli["-o"])
		{
			_binoutput = CLI.cli["-o"].argument;
		}
		else if(CLI.cli["--out"])
		{
			_binoutput = CLI.cli["--out"].argument;
		}
		
		_binoutput = path.join(process.cwd(), _binoutput)
		
		var _cout = path.join(_tmp, path.basename(_in).slice(0, path.basename(_in).length - path.extname(_in).length) + ".cpp");
		
		_binoutput = COMPILER.Out(_binoutput);
	
		var projTo = "";
		var tmp = _in.split("/");

		projTo = _binoutput;
	
		var main = _in.split(path.sep);
		main = main[main.length - 1];

		var tips = "";

		if(!QUIET) console.log("[*] Generating source file");
	
		var _code = fs.readFileSync(path.resolve(_in)).toString();
		COMPILER.Parse(_code);
		fs.writeFileSync(_cout, COMPILER.MAIN);
	
		var _args = [_in, "-o", _cout];

		if(!QUIET) console.log("[*] Compiling");
		try 
		{
			COMPILER.Compile(_tmp, _cout);
			fs.chmodSync(_binoutput, "755");
		}
		catch(e)
		{
			console.log("[!] Compilation error");
			console.log(e);
			process.exit(1);
		}
		
		if(!CLI.cli["--conserve"])
		{
			process.chdir(_current);
			rmdir(_tmp, function() {});
		}
		
		var verb = false;
		if(CLI.cli["--verbose"]) verb = true;
		
		var bin = fs.statSync(_binoutput);
		
		if(verb)
		{
			console.log("[+] Compilation done\n");
			console.log("[*] Informations :\n");
			var size = "Size      : ";
			if(bin.size < 1000) size += bin.size + " o";
			else if(bin.size < 1000000) size += (bin.size / 1000) + " ko";
			else size += (bin.size / 1000000) + " mo";
			console.log(size);
			console.log("Main file : " + main);
			console.log("Output    : " + projTo);
			console.log("Preset    : " + preset);
		}
		
		if(CLI.cli["--tips"] && tips && tips.length > 0) console.log("\n" + tips + "\n");

		if(CLI.cli["--flash"]) Flash(projTo, CLI.cli["--flash"].argument, target, verb);
		
		if(CLI.cli["--run"])
		{
			console.log();
			console.log("[*] Executing " + _binoutput);
			var _binexec = child_process.spawnSync(_binoutput, 
			[],
			{
				stdio: [process.stdin, process.stdout, process.stderr],
				cwd: process.cwd(),
				env: process.env
			});
			if(_binexec.error)
			{
				console.log(_binexec.error);
			}
		}	
		  if(!CLI.cli["--prepare"])
          {
			  var _current = path.dirname(path.resolve(process.argv[1]));
			  var _native = path.join(_current, "core", "nativejs");
			  var _to = path.resolve(projTo);
			  var _fullPathCompile = path.resolve(main);
		  }
          else
          {
	           var pObj = {main: main, out:projTo, target:target, preset:preset};
	            printProject(pObj);
          }
      }
    });
  }
}

function showVersion()
{
  console.log("NectarJS v" + VERSION);
}

function Check(file)
{
  if(file.split('.').pop() != "js") return;

  if(CLI.cli["--check"]) process.exit();
}

function Help()
{
  showVersion();
  console.log("\n[*] Compile :\nnectar [--env std|node|arduino|wasm] [--target the-target] [--run] [--reg 1000] [--preset speed|size] [-o output] [--tips] [--flash device] source.js|project.json\n");
  console.log("[*] Show project :\nnectar [--project] [project.json]\n");
  console.log("[*] Clean project :\nnectar [--clean] [--purge] [path_to_project.json]\n");
  console.log("[*] Copy example files :\nnectar --example\n");
  console.log("[*] Nectar version :\nnectar --version\n");
}
