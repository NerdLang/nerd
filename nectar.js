#!/usr/bin/env node

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


var VALID_COMPILER = ["native"];

global.fs = require('fs');
global.os = require('os');
global.path = require('path');
global.process = require('process');
global.querystring = require('querystring');
global.child_process = require('child_process');
global.execSync = child_process.execSync;
global.extern = path.join(__dirname, "node_modules", "nectarjs_external");
global.NJS_ENV = {};

try 
 {
    require("strip-comments");
 }
 catch(e)
 {
   console.log("[*] First execution, installing core dependencies");
   process.chdir(__dirname);
  child_process.execSync("npm i");
  console.log("[+] Core dependencies installed, please launch your command again");
  process.exit(0);
 }


global.PACKAGE = require(path.join(__dirname, "package.json"));
global.VERSION = PACKAGE.version;
var CONFIGPATH = os.homedir() + path.sep + ".nectar";
var CONFIGFILE = CONFIGPATH + "/" + "nectar.json";
global.CONFIG = {};
Init();
readConfig();

var parseCLI = require('./base/cli/cliParser.js');
global.coreHttp = require('./base/util/httpUtils.js');
var getExt = require('./base/util/getExt.js');
var getTips = require('./base/util/getTips.js');
var Flash = require('./base/util/flash.js');
var installModule = require('./base/util/installModule.js');
var initModule = require('./base/util/initModule.js');
global.rmdir = require("./base/util/rmdir.js");
global.copyRecursiveSync = require("./base/util/copyRecursive.js");
global.copyDirSync = require("./base/util/copyDirSync.js");
global.Zip = require("./base/util/adm-zip/");
var CURRENT = process.cwd();
var TARGET = require('./base/compiler/target.js');
global.LINT = require("./base/util/lint.js");
global.compileTS = require("./base/compiler/ts.js");
global.PLATFORM = os.platform();
global.ARCH = os.arch();

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
if(CLI.cli["--install_external"]) ACTION = "installExternal";
else if(CLI.cli["--help"] || CLI.cli["-h"]) ACTION = "help";
else if(CLI.cli["--example"] || CLI.cli["--examples"]) ACTION = "example";
else if(CLI.cli["--version"] || CLI.cli["-v"]) ACTION = "version";
else if(CLI.cli["--install"] || CLI.cli["-i"]) ACTION = "install";
else if(CLI.cli["--init-module"]) ACTION = "initModule";
else if(CLI.cli["--project"]) ACTION = "showproject";
else if(CLI.cli["--clean"] || CLI.cli["--purge"]) ACTION = "clean";
else if(CLI.cli["--setauthor"] || CLI.cli["--setid"] || CLI.cli["--setkey"] || CLI.cli["--sethash"] || CLI.cli["--setsdk"] || CLI.cli["--setndk"] || CLI.cli["--setwin_inc_ucrt"] || CLI.cli["--setwin_lib_ucrt"] || CLI.cli["--setwin_lib_um"] || CLI.cli["--setapi"] || CLI.cli["--setport"] || CLI.cli["--setxcode"]) ACTION = "setconfig";
else if(CLI.cli["--config"]) ACTION = "showconfig";
else if(CLI.cli["--reinit"]) ACTION = "reinitconfig";

switch(ACTION)
{
  case "installExternal":
    installExternal();
  break;
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

  case "setconfig":
    setConfig();
    break;

  case "showconfig":
    showConfig();
    break;

  case "reinitconfig":
    reinitConfig();
    break;

  case "build":
    Build();
    break;

  case "install":
    Install();
    break;

  case "initModule":
    InitModule();
    break;

  case "clean":
    Clean();
    break;

  default:
    Help();
    break;
}

function installExternal()
{
  console.log("[*] Installing external dependencies...")
  process.chdir(NECTAR_PATH);
  execSync("npm r nectarjs_external");
  execSync("npm i nectarjs_external");
  console.log("[+] External dependencies installed")
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

function Init()
{
    if(!fs.existsSync(CONFIGPATH)) fs.mkdirSync(CONFIGPATH);
  try
  {
      var writeConfig = false;
      var config = "";
      config = fs.readFileSync(CONFIGFILE);
      config = JSON.parse(config)
      if(!config.version)
      {
        config.version = VERSION;
        config.port = 443;
        fs.writeFileSync(CONFIGFILE, JSON.stringify(config));
      }
  }
  catch (e)
  {
    writeConfig = true;
  }

  if(!config || writeConfig)
  {
    var defaultConfig = { author: os.userInfo().username, id: "", key:"", hash:"SHA256", api:"api.nectarjs.com", port:443, version: VERSION, sdk: "", ndk: "", win_inc_ucrt: "", win_lib_ucrt: "", win_lib_um: "", xcode: "/Applications/Xcode.app"};
    fs.writeFileSync(CONFIGFILE, JSON.stringify(defaultConfig));
  }
}

function readConfig()
{
  try
  {
    var tmp = fs.readFileSync(CONFIGFILE);
    CONFIG = JSON.parse(tmp);
  }
  catch (e)
  {
    Init();
    readConfig();
  }
}

function showConfig(str)
{
  console.log();
  if(str) console.log(str);
  else console.log("[*] Current config :");
  console.log("author   : " + CONFIG.author);
  console.log("id   : " + CONFIG.id);
  console.log("key  : " + CONFIG.key);
  console.log("hash : " + CONFIG.hash);
  console.log("api : " + CONFIG.api);
  console.log("port : " + CONFIG.port);
  console.log("version : " + VERSION);
  console.log("Android SDK : " + CONFIG.sdk);
  console.log("Android NDK : " + CONFIG.ndk);
  console.log("Windows Include UCRT : " + CONFIG.win_inc_ucrt);
  console.log("Android Lib UCRT : " + CONFIG.win_lib_ucrt);
  console.log("Android Lib UM : " + CONFIG.win_lib_um);
  console.log("iOS xCode : " + CONFIG.xcode);
  console.log();
}

function setConfig()
{
  try
  {
    if(CLI.cli["--setauthor"]) CONFIG.author = CLI.cli["--setauthor"].argument;
    if(CLI.cli["--setid"]) CONFIG.id = CLI.cli["--setid"].argument;
    if(CLI.cli["--setkey"]) CONFIG.key = CLI.cli["--setkey"].argument;
    if(CLI.cli["--setapi"]) CONFIG.api = CLI.cli["--setapi"].argument;
    if(CLI.cli["--setport"]) CONFIG.port = parseInt(CLI.cli["--setport"].argument);
    if(CLI.cli["--setsdk"]) CONFIG.sdk = CLI.cli["--setsdk"].argument.replace(/\\/g, "\\\\").replace(/:/g, "\\\:");
    if(CLI.cli["--setndk"]) CONFIG.ndk = CLI.cli["--setndk"].argument.replace(/\\/g, "\\\\").replace(/:/g, "\\\:");
    if(CLI.cli["--setwin_ucrt"]) CONFIG.win_ucrt = CLI.cli["--setwin_ucrt"].argument;
    if(CLI.cli["--setwin_inc_ucrt"]) CONFIG.win_inc_ucrt = CLI.cli["--setwin_inc_ucrt"].argument;
    if(CLI.cli["--setwin_lib_ucrt"]) CONFIG.win_lib_ucrt = CLI.cli["--setwin_lib_ucrt"].argument;
    if(CLI.cli["--setwin_lib_um"]) CONFIG.win_lib_um = CLI.cli["--setwin_lib_um"].argument;
    if(CLI.cli["--setxcode"]) CONFIG.xcode = CLI.cli["--setxcode"].argument;

    if(isNaN(CONFIG.port))
    {
      console.dir("[!] This port is not valid : '" + CLI.cli["--setport"].argument +"', please specify a number.");
      return;
    }

    if(CLI.cli["--sethash"])
    {
      var hash = CLI.cli["--sethash"].argument.toUpperCase();
      if(validHash.indexOf(hash) < 0)
      {
        console.dir("[!] Hash is not valid and won't be saved. Valid hash are : MD5, SHA256 ans SHA512");
      }
      else
      {
          CONFIG.hash = hash;
      }
    }

    fs.writeFileSync(CONFIGFILE, JSON.stringify(CONFIG));
  }
  catch (e)
  {
    console.log(e);
  }
}

function reinitConfig()
{
  try
  {
    var defaultConfig = { author: os.userInfo().username, id: "", key:"", hash:"SHA256", api:"api.nectarjs.com", "port":443, sdk: "", ndk: "", win_inc_ucrt: "", win_lib_ucrt: "", win_lib_um: "", xcode: "/Applications/Xcode.app"};
    fs.writeFileSync(CONFIGFILE, JSON.stringify(defaultConfig));
    readConfig();
    showConfig("[*] Config reinitialized :");
  } catch (e)
  {
      console.log(e);
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

  if(!preset) preset = "speed";
  COMPILER.preset = preset;
  
  if(!env) env = "std";

  if(env != "std" && env != "test")
  {
    var _external = false;
    try 
    {
      var _external = require("nectarjs_external")
    }
    catch(e)
    {
      
    }
    if(!_external)
    {
      console.log("You need to install the package nectarjs_external to use this environment: ");
      console.log("nectar --install_external");
      process.exit(0);
    }
  }
	var target;
  if(CLI.cli["--target"] && CLI.cli["--target"].argument) target = CLI.cli["--target"].argument;
	COMPILER.TARGET = target;

	var spec;
  if(CLI.cli["--spec"] && CLI.cli["--spec"].argument) spec = CLI.cli["--spec"].argument;
	COMPILER.SPEC = spec;

	var _tmp;
	if(CLI.cli["--tmp"] && CLI.cli["--tmp"].argument)
		_tmp = path.resolve(CLI.cli["--tmp"].argument);
	else {
		var _current = process.cwd();
		var _npath = path.join(_current, ".nectar");
		_tmp = path.join(_npath, Math.random().toString(36).substr(2, 5));
	}
	COMPILER.TMP_FOLDER = _tmp;

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
		if(COMPILER.ENV.init) COMPILER.ENV.init(COMPILER.TMP_FOLDER);
		else try { fs.mkdirSync(COMPILER.TMP_FOLDER); } catch(e){};

		/*** PREPARE SRC ***/
		var _libOut = COMPILER.TMP_FOLDER;
		if(COMPILER.ENV.prepare)
		{
			var _tmpLibOut = COMPILER.ENV.prepare(COMPILER.TMP_FOLDER);
			if(_tmpLibOut) _libOut = _tmpLibOut;
		}

		COMPILER.Prepare(_libOut);

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
		
		var _cout = path.join(COMPILER.TMP_FOLDER, path.basename(_in).slice(0, path.basename(_in).length - path.extname(_in).length) + ".cpp");

		_binoutput = COMPILER.Out(_binoutput);
	
		var projTo = "";
		var tmp = _in.split("/");

		projTo = _binoutput;
	
		var main = _in.split(path.sep);
		main = main[main.length - 1];

		var tips = "";

		if(!QUIET) console.log("[*] Generating source file");
	
		var _code = fs.readFileSync(path.resolve(_in)).toString();

		if(ext == "ts") _code = compileTS(_code, _in);
		COMPILER.Parse(_code);
    
		if(COMPILER.ENV.write)
		{
			COMPILER.ENV.write(COMPILER.MAIN, _cout);
		}
		else
		{
			if((!CLI.cli["--profile"]) || CLI.cli["--profile"].argument != "use")
			{
				fs.writeFileSync(_cout, COMPILER.MAIN);
			}
		}

		if(CLI.cli["--generate"])
		{
			if(!QUIET) console.log("[*] Source generated in " + path.dirname(_cout));
			process.exit(0);
		}

		if(!QUIET) console.log("[*] Compiling with preset: " + COMPILER.preset);
		try 
		{
			COMPILER.Compile(COMPILER.TMP_FOLDER, _cout);
		}
		catch(e)
		{
			console.log(e);
			console.log("[!] Compilation error");
			process.exit(1);
    }
    
    if(COMPILER.ENV.post) COMPILER.ENV.post();

    try 
		{
			fs.chmodSync(_binoutput, "755");
		}
		catch(e){}
		
		if(COMPILER.Package) COMPILER.Package();
		
		process.chdir(NECTAR_PATH);
		
		if(!CLI.cli["--conserve"])
		{
			var _current = process.cwd();
			process.chdir(_current);
			rmdir(COMPILER.TMP_FOLDER, function() {});
		}
		
		var verb = false;
		if(CLI.cli["--verbose"]) verb = true;
		
    var bin;
    try 
		{
      bin = fs.statSync(_binoutput);
		}
    catch(e){}
    
    if(COMPILER.ENV.clean && typeof COMPILER.ENV.clean == "function")
    {
      COMPILER.ENV.clean();
    }

		if(verb && bin)
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
      if(!COMPILER.ENV.run)
      {
        var _binexec = child_process.spawnSync(_binoutput, 
        [],
        {
		  detached: false,
          stdio: [process.stdin, process.stdout, process.stderr],
          cwd: process.cwd(),
          env: process.env
        });
        if(_binexec.error)
        {
          console.log(_binexec.error);
        }
      }
      else COMPILER.ENV.run();
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
  console.log("\n[*] Compile :\nnectar [--env std|node|arduino|wasm|android] [--target the-target] [--run] [--generate] [--conserve] [--reg 1000] [--preset speed|size] [-o output] [--tips] [--flash device] source.js|project.json\n");
  console.log("[*] Show project :\nnectar [--project] [project.json]\n");
  console.log("[*] Clean project :\nnectar [--clean] [--purge] [path_to_project.json]\n");
  console.log("[*] Copy example files :\nnectar --example\n");
  console.log("[*] Nectar version :\nnectar --version\n");
}

function Install()
{
	var _module = "";
	if(CLI.cli["--install"]) _module = CLI.cli["--install"].argument;
	else _module = CLI.cli["-i"].argument;
	installModule(_module);
}

function InitModule()
{
	var _module = CLI.cli["--init-module"].argument;
	var _author = "undefined";

	if(CLI.cli["--author"]) _name = CLI.cli["--author"].argument;

	initModule(_author, _module);
}