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

global.fs = require("fs");
global.os = require("os");
global.path = require("path");
global.process = require("process");
global.child_process = require("child_process");
global.execSync = global.child_process.execSync;

global.PACKAGE = JSON.parse(global.fs.readFileSync(global.path.join(__dirname, "package.json")));
global.VERSION = global.PACKAGE.version;

global.extern = global.path.join(__dirname, "external");

var parseCLI = require("./base/cli/cliParser.js");
var getExt = require("./base/util/getExt.js");
var getTips = require("./base/util/getTips.js");
var Flash = require("./base/util/flash.js");
global.copyRecursiveSync = require("./base/util/copyRecursive.js");
global.copyDirSync = require("./base/util/copyDirSync.js");

var CURRENT = global.process.cwd();
var TARGET = require("./base/compiler/target.js");


global.PLATFORM = os.platform();
global.ARCH = os.arch();

global.COMPILER = {};
global.NERD_PATH = __dirname;
var DEFAULT_COMPILER = "native";

global.CLI = parseCLI(process.argv);

if(global.CLI.error)
{
  console.log(global.CLI.msg);
  return 1;
}
require("./lib/env.js");
global.parseCode = require("./lib/parser.js");
global.verifyFlow = require("./lib/verify.js");

global.CONFIGPATH = process.env.XDG_CONFIG_HOME ? (process.env.XDG_CONFIG_HOME + path.sep + "nerd") : (global.os.homedir() + path.sep + ".nerd");
global.CONFIGFILE = global.CONFIGPATH + path.sep + "nerd.json";
global.CONFIG = {};


var ACTION = "build";
if(global.CLI.cli["--help"] || global.CLI.cli["-h"]) ACTION = "help";
else if(global.CLI.cli["--example"] || global.CLI.cli["--examples"]) ACTION = "example";
else if(global.CLI.cli["--version"] || global.CLI.cli["-v"]) ACTION = "version";
else if(global.CLI.cli["--project"]) ACTION = "showproject";
else if(global.CLI.cli["--clean"] || global.CLI.cli["--purge"]) ACTION = "clean";
else if(global.CLI.cli["--setauthor"] || global.CLI.cli["--setid"] || global.CLI.cli["--setkey"] || global.CLI.cli["--sethash"] || global.CLI.cli["--setsdk"] || global.CLI.cli["--setndk"] || global.CLI.cli["--setwin_inc_ucrt"] || global.CLI.cli["--setwin_lib_ucrt"] || global.CLI.cli["--setwin_lib_um"] || global.CLI.cli["--setapi"] || global.CLI.cli["--setport"] || global.CLI.cli["--setxcode"]) ACTION = "setconfig";
else if(global.CLI.cli["--config"]) ACTION = "showconfig";
else if(global.CLI.cli["--reinit"]) ACTION = "reinitconfig";


var getExampleFiles = function(dir, list)
{
	if(!list)
	{
		list = [];
	}

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

var copyExample = function()
{
  var folder = ["c"];
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

var Init = function()
{
    if(!fs.existsSync(CONFIGPATH)) fs.mkdirSync(CONFIGPATH);
  try
  {
      var writeConfig = false;
      var config = "";
      config = fs.readFileSync(CONFIGFILE);
      config = JSON.parse(config);
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
    var defaultConfig = { author: os.userInfo().username, id: "", key:"", hash:"SHA256", api:"api.nerdlang.com", port:443, version: VERSION, sdk: "", ndk: "", win_inc_ucrt: "", win_lib_ucrt: "", win_lib_um: "", xcode: "/Applications/Xcode.app"};
    fs.writeFileSync(CONFIGFILE, JSON.stringify(defaultConfig));
  }
}

var readConfig = function()
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

var showConfig = function(str)
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

var setConfig = function()
{
  try
  {
    if(global.CLI.cli["--setauthor"]) CONFIG.author = global.CLI.cli["--setauthor"].argument;
    if(global.CLI.cli["--setid"]) CONFIG.id = global.CLI.cli["--setid"].argument;
    if(global.CLI.cli["--setkey"]) CONFIG.key = global.CLI.cli["--setkey"].argument;
    if(global.CLI.cli["--setapi"]) CONFIG.api = global.CLI.cli["--setapi"].argument;
    if(global.CLI.cli["--setport"]) CONFIG.port = parseInt(global.CLI.cli["--setport"].argument);
    //if(global.CLI.cli["--setsdk"]) CONFIG.sdk = global.CLI.cli["--setsdk"].argument.replace(/\\/g, "\\\\").replace(/:/g, "\\\:"); // for android 
    //if(global.CLI.cli["--setndk"]) CONFIG.ndk = global.CLI.cli["--setndk"].argument.replace(/\\/g, "\\\\").replace(/:/g, "\\\:"); // for android
    if(global.CLI.cli["--setwin_ucrt"]) CONFIG.win_ucrt = global.CLI.cli["--setwin_ucrt"].argument;
    if(global.CLI.cli["--setwin_inc_ucrt"]) CONFIG.win_inc_ucrt = global.CLI.cli["--setwin_inc_ucrt"].argument;
    if(global.CLI.cli["--setwin_lib_ucrt"]) CONFIG.win_lib_ucrt = global.CLI.cli["--setwin_lib_ucrt"].argument;
    if(global.CLI.cli["--setwin_lib_um"]) CONFIG.win_lib_um = global.CLI.cli["--setwin_lib_um"].argument;
    if(global.CLI.cli["--setxcode"]) CONFIG.xcode = global.CLI.cli["--setxcode"].argument;

	/*
    if(isNaN(CONFIG.port))
    {
      console.dir("[!] This port is not valid : '" + global.CLI.cli["--setport"].argument +"', please specify a number.");
      return;
    }
	*/

    if(global.CLI.cli["--sethash"])
    {
      var hash = global.CLI.cli["--sethash"].argument.toUpperCase();
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

var reinitConfig = function()
{
  try
  {
    var defaultConfig = { author: os.userInfo().username, id: "", key:"", hash:"SHA256", api:"api.nerdlang.com", "port":443, sdk: "", ndk: "", win_inc_ucrt: "", win_lib_ucrt: "", win_lib_um: "", xcode: "/Applications/Xcode.app"};
    fs.writeFileSync(CONFIGFILE, JSON.stringify(defaultConfig));
    readConfig();
    showConfig("[*] Config reinitialized :");
  } catch (e)
  {
      console.log(e);
  }
}

var showProject = function()
{
  var project = "project.json";
  if(global.CLI.stack && global.CLI.stack.length > 0)
  {
    project = global.CLI.stack[global.CLI.stack.length - 1];
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

var Clean = function(purge)
{
  var project = "project.json";
  if(global.CLI.stack && global.CLI.stack.length > 0)
  {
    project = global.CLI.stack[global.CLI.stack.length - 1];
  }
  try
  {
    var pConf = fs.readFileSync(project);
    var jConf = JSON.parse(pConf);
    if(jConf.main)
    {
      if( (global.CLI.cli["--purge"] || purge) && jConf.out)
      {
        var outFile = jConf.out;
        if(jConf.out[0] != path.sep)
        {
          outFile = path.join(path.dirname(project), jConf.out);
        }
        try{fs.unlinkSync(outFile);}catch(e){}
      }
    }
    try
	{
		fs.unlinkSync(project);
	}catch(e){}
  }
  catch (e)
  {
    console.dir("[!] Error : " + e.message);
  }
}

var printProject = function(obj)
{
  console.log();
  console.log("[*] Project configuration :\n");
  console.log("Main file : " + obj.main);
  console.log("Output    : " + obj.out);
  console.log("Target    : " + obj.target);
  console.log("Preset    : " + obj.preset);
  console.log();
}

var Build = function(prepare)
{ 
	global.DEBUG = false;
	if(global.CLI.cli["--debug"])
	{
		global.DEBUG = true;
	}
  if(global.CLI.cli["--build"]) DEFAULT_COMPILER = global.CLI.cli["--build"].argument;
  else if(global.CLI.cli["-b"]) DEFAULT_COMPILER = global.CLI.cli["-b"].argument;
  
  COMPILER = require(path.join(__dirname, "compiler", DEFAULT_COMPILER, "compiler.js"));
  
  if(global.CLI.cli["--compiler"] && global.CLI.cli["--compiler"].argument) COMPILER.COMPILER = global.CLI.cli["--compiler"].argument;
  else if(global.CLI.cli["-c"] && global.CLI.cli["-c"].argument) COMPILER.COMPILER = global.CLI.cli["-c"].argument;

  var preset;
  if(global.CLI.cli["--preset"] && global.CLI.cli["--preset"].argument) preset = global.CLI.cli["--preset"].argument;

  var env;
  if(global.CLI.cli["--env"] && global.CLI.cli["--env"].argument) env = global.CLI.cli["--env"].argument;

  if(!preset) preset = "speed";
  COMPILER.preset = preset;
  
  if(!env) env = "std";

	var target;
  if(global.CLI.cli["--target"] && global.CLI.cli["--target"].argument) target = global.CLI.cli["--target"].argument;
	COMPILER.TARGET = target;

	var spec;
  if(global.CLI.cli["--spec"] && global.CLI.cli["--spec"].argument) spec = global.CLI.cli["--spec"].argument;
	COMPILER.SPEC = spec;

	var _tmp;
	if(global.CLI.cli["--tmp"] && global.CLI.cli["--tmp"].argument)
		_tmp = path.resolve(global.CLI.cli["--tmp"].argument);
	else {
		var _current = process.cwd();
		var _npath = path.join(_current, ".nerd");
		_tmp = path.join(_npath, Math.random().toString(36).substr(2, 5));
	}
	COMPILER.TMP_FOLDER = _tmp;

  if(!global.CLI.stack || global.CLI.stack.length < 1)
  {
    console.error("[!] Missing file to compile or project.json path, 'nerd --help' if you need help");
    return;
  }
  else
  {
	var QUIET = false;
    var _in = global.CLI.stack[0];
	var main;
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

        Check(_in);
		
        var ext = "ng";
        var _Ext = _in.split(".");
        if(_Ext.length > 1) ext = _Ext[_Ext.length - 1];

		/*** CREATE COMPIL ENV ***/
		var _current = process.cwd();
		var _npath = path.join(_current, ".nerd");
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
		
		if(global.CLI.cli["-o"])
		{
			_binoutput = global.CLI.cli["-o"].argument;
		}
		else if(global.CLI.cli["--out"])
		{
			_binoutput = global.CLI.cli["--out"].argument;
		}
		
		_binoutput = path.join(process.cwd(), _binoutput);
		
		var _cout = path.join(COMPILER.TMP_FOLDER, path.basename(_in).slice(0, path.basename(_in).length - path.extname(_in).length) + ".cpp");

		_binoutput = COMPILER.Out(_binoutput);
	
		var projTo = "";
		var tmp = _in.split("/");

		projTo = _binoutput;
	
		main = _in.split(path.sep);
		main = main[main.length - 1];

		var tips = "";

		if(!QUIET) console.log("[*] Generating source file");
	
		var _code = fs.readFileSync(path.resolve(_in)).toString();

		global.array_of_code = _code.split(os.EOL);
		_code = COMPILER.Parse(_code, _in);
    
		if(COMPILER.ENV.write)
		{
			COMPILER.ENV.write(COMPILER.MAIN, _cout);
		}
		else
		{
			if((!global.CLI.cli["--profile"]) || global.CLI.cli["--profile"].argument != "use")
			{
				fs.writeFileSync(_cout, COMPILER.MAIN);
			}
		}

		if(global.CLI.cli["--generate"])
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
		
		process.chdir(NERD_PATH);
		
		if(!global.CLI.cli["--conserve"])
		{
			var _current = process.cwd();
			process.chdir(_current);
			fs.rmSync(COMPILER.TMP_FOLDER, {recursive: true});
		}
		
		var verb = false;
		if(global.CLI.cli["--verbose"]) verb = true;
		
    var bin;
    try 
		{
      bin = fs.statSync(_binoutput);
		}
    catch(e){}
    
    if(COMPILER.ENV.clean && typeof(COMPILER.ENV.clean) == "function")
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
		
		if(global.CLI.cli["--tips"] && tips && tips.length > 0) console.log("\n" + tips + "\n");

		if(global.CLI.cli["--flash"]) Flash(projTo, global.CLI.cli["--flash"].argument, target, verb);
		
		if(global.CLI.cli["--run"])
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
		  if(!global.CLI.cli["--prepare"])
          {
			  var _current = path.dirname(path.resolve(process.argv[1]));
			  var _native = path.join(_current, "core", "nativejs");
			  var _to = path.resolve(projTo);
			  var _fullPathCompile = path.resolve(main);
		  }
          else
          {
	           var pObj = { main: main, out:projTo, target:target, preset:preset };
	            printProject(pObj);
          }
      }
    });
  }
}

var showVersion = function()
{
  console.log("Nerd v" + VERSION);
}

var Check = function(file)
{
  if(file.split(".").pop() != "js") return;

  if(global.CLI.cli["--check"]) process.exit();
}

var Help = function()
{
  showVersion();
  console.log("\n[*] Compile :\nnerd [--env std|node|arduino|wasm|android] [--target the-target] [--run] [--reg 1000] [--preset speed|size] [-o output] [--tips] [--flash device] source.js|project.json\n");
  console.log("[*] Show project :\nnerd [--project] [project.json]\n");
  console.log("[*] Clean project :\nnerd [--clean] [--purge] [path_to_project.json]\n");
  console.log("[*] Copy example files :\nnerd --example\n");
  console.log("[*] Nerd version :\nnerd --version\n");
}


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

  case "clean":
    Clean();
    break;

  default:
    Help();
    break;
}
