#!/usr/bin/env node

/*
 * This file is part of NectarJS
 * Copyright (c) 2019 Adrien THIERRY
 * http://nectarjs.com - https://nectrium.com
 *
 * sources : https://github.com/nectarjs/nectarjs
 *
 * NectarJS
 * Copyright (C) 2019 Adrien THIERRY - Necrium
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

var VERSION = "0.2.0";

var DEFAULT_COMPILER = "g++";

var fs = require('fs');
var os = require('os');
var path = require('path');
var Zip = require('./extern/adm-zip/adm-zip.js');
var process = require('process');
var querystring = require('querystring');
var child_process = require('child_process');

var parseCLI = require('./base/cli/cliParser.js');
var coreHttp = require('./base/util/httpUtils.js');
var getExt = require('./base/util/getExt.js');
var getTips = require('./base/util/getTips.js');
var Flash = require('./base/util/flash.js');
var Crypto = require('./base/util/cryptoUtil.js')
var CURRENT = process.cwd();
var TARGET = require('./base/compiler/target.js');
var PLATFORM = os.platform();
var ARCH = os.arch();
var CONFIGPATH = os.homedir() + path.sep + ".nectar";
var CONFIGFILE = CONFIGPATH + "/" + "nectar.json";
CONFIG = {};
Init();
readConfig();

var validHash = ["MD5", "SHA256", "SHA512"];

var CLI = parseCLI(process.argv);

if(CLI.error)
{
  console.log(CLI.msg);
  return;
}

var ACTION = "build";
if(CLI.cli["--help"] || CLI.cli["-h"]) ACTION = "help";
else if(CLI.cli["--example"] || CLI.cli["--examples"]) ACTION = "example";
else if(CLI.cli["--version"] || CLI.cli["-v"]) ACTION = "version";
else if(CLI.cli["--setid"] || CLI.cli["--setkey"] || CLI.cli["--sethash"] || CLI.cli["--setapi"] || CLI.cli["--setport"]) ACTION = "setconfig";
else if(CLI.cli["--project"]) ACTION = "showproject";
else if(CLI.cli["--config"]) ACTION = "showconfig";
else if(CLI.cli["--reinit"]) ACTION = "reinitconfig";
else if(CLI.cli["--clean"] || CLI.cli["--purge"]) ACTION = "clean";

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
    var defaultConfig = { id: "", key:"", "hash":"SHA256", "api":"api.nectarjs.com", "port":443, "version": VERSION};
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
  console.log("id   : " + CONFIG.id);
  console.log("key  : " + CONFIG.key);
  console.log("hash : " + CONFIG.hash);
  console.log("api : " + CONFIG.api);
  console.log("port : " + CONFIG.port);
  console.log("version : " + VERSION);
  console.log();
}

function setConfig()
{
  try
  {
    if(CLI.cli["--setid"]) CONFIG.id = CLI.cli["--setid"].argument;
    if(CLI.cli["--setkey"]) CONFIG.key = CLI.cli["--setkey"].argument;
    if(CLI.cli["--setapi"]) CONFIG.api = CLI.cli["--setapi"].argument;
    if(CLI.cli["--setport"]) CONFIG.port = parseInt(CLI.cli["--setport"].argument);

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
    var defaultConfig = { id: "", key:"", hash:"SHA256", "api":"api.nectarjs.com", "port":443};
    fs.writeFileSync(CONFIGFILE, JSON.stringify(defaultConfig));
    readConfig();
    showConfig("[*] Config reinitialized :");
  } catch (e)
  {
      console.log(e);
  }
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
  if(!CONFIG.id || !CONFIG.key || CONFIG.id.length == 0 || CONFIG.key.length == 0)
  {
    console.dir("[!] Please set your id and your key before build (see nectar --help)");
    return;
  }

  if(CLI.cli["--compiler"] && CLI.cli["--compiler"].argument) DEFAULT_COMPILER = CLI.cli["--compiler"].argument;

  var single = false;
  if(CLI.cli["--single"]) single = true;

  var target;
  if(CLI.cli["--target"] && CLI.cli["--target"].argument) target = CLI.cli["--target"].argument;

  var preset;
  if(CLI.cli["--preset"] && CLI.cli["--preset"].argument) preset = CLI.cli["--preset"].argument;

  var env;
  if(CLI.cli["--env"] && CLI.cli["--env"].argument) env = CLI.cli["--env"].argument;

  if(!target)
  {
    switch(PLATFORM)
    {
      case "darwin":
        target = "mac-osx";
      break;
      case "android":
      case "linux":
        if(ARCH == "x64") target = "linux-x86-64";
        else if(ARCH == "x32") target = "linux-x86-32";
        else if(ARCH == "arm") target = "linux-arm32v7";
        break;

      case "win32":
        if(ARCH == "x64") target = "win-x86-64";
        else if(ARCH == "x32") target = "win-x86-32";
        break;

      default:
        target = "null";
        break;
    }
  }

  if(!preset) preset = "speed";
  if(!env) env = "std";

  if(!CLI.stack || CLI.stack.length < 1)
  {
    console.error("[!] Missing file to compile or project.json path, 'nectar --help' if you need help");
    return;
  }
  else if(!target || TARGET.indexOf(target) < 0)
  {
    console.error("[!] Bad target\n");
    showTarget();
    return;
  }
  else
  {
    var fName = CLI.stack[CLI.stack.length - 1];

    fs.readFile(fName, function(err, fileData)
    {
      if(err)
      {
        console.error("[!] Error : " + err.message);
        return;
      }
      else
      {

        /* CHECKING */
        Check(fName);
        /* END CHECKING */

        var ext = "js";
        var _Ext = fName.split(".");
        if(_Ext.length > 1) ext = _Ext[_Ext.length - 1];

        var fProject = false;
        var prjectConf = {};
        if(path.basename(fName) == "project.json")
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

          var to = "";
          var projTo = "";
          var tmp = fName.split("/");
          if(fProject)
	         {
	            to = projectConf.out;
    	     }
          else if(CLI.cli["-o"])
          {
            to = CLI.cli["-o"].argument;
          }
          else
          {
            var end = getExt(target);
            to = tmp[tmp.length-1].split(".")[0] + end;
          }

         projTo = to;

	       var main = fName.split(path.sep);
          main = main[main.length - 1];

	        var data = "";
          var fPath = "";
          var tips = "";
          if(single && CLI.cli["--caas"])
          {
            var jsSource = fileData.toString("base64");
            if(!CONFIG.hash || validHash.indexOf(CONFIG.hash) < 0)
            {
              console.dir("[!] Hash is not valid, please set valid one : nectar --sethash MD5|SHA256|SHA512");
              return;
            }
            var signature = Crypto.returnHash(CONFIG.hash, jsSource);
            data = '{ "source" : "' + Crypto.encrypt(jsSource, CONFIG.key) + '", "ext": "' + ext + '", "env": "' + env + '", "version":"' + VERSION + '", "id":"' + CONFIG.id + '", "signature": "' + signature + '"}';
            fPath = "/compile/" + "single" + "/" + target + "/" + preset + "/";
            tips = getTips(target, to);
          }
          else if(CLI.cli["--caas"])
          {
            var zipArray = fName.split(path.sep);
            var zipFolder = "";
            for(var i = 0; i < zipArray.length - 1; i++)
            {
              zipFolder += zipArray[i] + path.sep;
            }
			var admZipPath = zipFolder;
            if(true || zipArray.length < 2)
            {
              var toZip = CURRENT.split(path.sep);

      	      if(PLATFORM == "win32")
      	      {
      	         zipFolder = ".." + path.sep + toZip[toZip.length - 1] + path.sep;
      	      }
      	      else zipFolder =  ".." + path.sep + toZip[toZip.length - 1] + path.sep;
            }

            if(fProject)
            {
              main = projectConf.main;
              to = projectConf.out;
              target = projectConf.target;
              preset = projectConf.preset;
              env = projectConf.env;
              Clean(true);
            }
            tips = getTips(target, to);

            fs.writeFileSync(zipFolder + "project.json", '{"main": "' + main + '", "out": "'+ to + '", "target":"' + target + '", "preset":"' + preset + '", "env": "' + env + '"}');

            var zip = new Zip();
            if(admZipPath.length == 0)
            {
              admZipPath = process.cwd();
            }
            zip.addLocalFolder(admZipPath, "./");
      			var E = zip.getEntries();
      			for(var e in E)
      			{
      				E[e].entryName = path.basename(E[e].entryName);
      			}
            var zipBuffer = Buffer.from(zip.toBuffer()).toString("base64");

            if(!CONFIG.hash || validHash.indexOf(CONFIG.hash) < 0)
            {
              console.dir("[!] Hash is not valid, please set valid one : nectar --sethash MD5|SHA256|SHA512");
              return;
            }

            var signature = Crypto.returnHash(CONFIG.hash, zipBuffer);

            zipBuffer = Crypto.encrypt(zip.toBuffer().toString("base64"), CONFIG.key);
            data = '{ "project" : "' + zipBuffer + '", "version":"' + VERSION + '", "id":"' + CONFIG.id + '", "signature": "' + signature + '"}';
            fPath = "/compile/" + "project" + "/" + target + "/" + preset + "/";
          }

          var apiOption =
          {
            port: CONFIG.port,
            hostname: CONFIG.api,
            method: "POST",
            path: fPath,
            data: data,
          };

          function Compiled(data)
          {
            var result;
            try
            {
              result = JSON.parse(data);
            }
            catch(e)
            {
              console.error("[!] Unexpected network error");
              process.exit(1);
            }

            if(!result.success)
            {
              if(result.message) console.error(result.message);
              else console.error("[!] Unexpected network error");
              process.exit(1);
            }
            else
            {

              var bin = Crypto.decrypt(result.data, CONFIG.key);

              if (typeof Buffer.from === "function")
              {
                  bin = Buffer.from(bin, 'base64');
              }
              else
              {
                  bin = new Buffer(bin, 'base64');
              }


              fs.writeFile(to, bin, function(err, data)
              {
                if(err)
                {
                  console.error("[!] Error with " + to + " : " + err.message);
                }
                else
                {
                  var verb = false;
                  if(CLI.cli["--verbose"]) verb = true;

                  fs.chmodSync(to, "755");
                  if(verb)
                  {
                    console.log("[+] Compilation done\n");
                    console.log("[*] Informations :\n");
                    var size = "Size      : ";
                    if(bin.length < 1000) size += bin.length + " o";
                    else if(bin.length < 1000000) size += (bin.length / 1000) + " ko";
                    else size += (bin.length / 1000000) + " mo";
                    console.log(size);
                    console.log("Main file : " + main);
                    console.log("Output    : " + projTo);
                    console.log("Target    : " + target);
                    console.log("Preset    : " + preset);
                  }
                  if(CLI.cli["--tips"] && tips && tips.length > 0) console.log("\n" + tips + "\n");

                  if(CLI.cli["--flash"]) Flash(to, CLI.cli["--flash"].argument, target, verb);

                  if(CLI.cli["--run"])
                  {
                    if(PLATFORM == "win32")
                    {
                      console.log(child_process.execSync(to).toString());
                    }
                    else
                    {
                      var before = "";
                      if(to[0] && to[0] != "/") before = "." + path.sep;
                      child_process.execFile(before + to, function(error, stdout, stderr)
                    {
                      if(error) console.error(error);
                      if(stderr) console.error(stderr);
                      if(stdout) console.log(stdout);
                    });
                    }
                  }
                }
              });
            }
          }
          if(!CLI.cli["--prepare"] && CLI.cli["--caas"])
          {
            var httpHandler;
            if(CONFIG.port == 443) httpHandler = coreHttp.httpsUtil;
            else httpHandler = coreHttp.httpUtil;
             httpHandler.httpReq(apiOption, function(err){console.log("[!] Network error : " + err.message);}, Compiled)
          }
          else if(!CLI.cli["--prepare"])
          {
			  var _current = path.dirname(path.resolve(process.argv[1]));
			  var _native = path.join(_current, "core", "nativejs");
			  var _to = path.resolve(to);
			  var _fullPathCompile = path.resolve(fName);
			  console.log(child_process.execSync("cd " + _native + " && ./njs " + _fullPathCompile + " --compiler " + DEFAULT_COMPILER + " -o " + _to));
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
  console.log("NectarJS Client v" + VERSION);
}

function showTarget()
{
  console.log("[*] Available targets :");
  for(var i = 0; i < TARGET.length; i++)
  {
    console.log("-> " + TARGET[i]);
  }
  console.log();
}

function Check(file)
{
  if(file.split('.').pop() != "js") return;

  if(CLI.cli["--check"]) process.exit();
}

function Help()
{
  showVersion();
  console.log("\n[*] Compile :\nnectar [--target the-target] [--run] [--single] [--preset speed|size] [-o output] [--reinit] [--prepare] [--tips] source.js|project.json\n");
  console.log("[*] configure :\nnectar [--setid id] [--setkey key] [--sethash MD5|SHA256|SHA512]\n");
  console.log("[*] Show configuration :\nnectar --config\n");
  console.log("[*] Reinit configuration :\nnectar --reinit\n");
  console.log("[*] Show project :\nnectar [--project] [project.json]\n");
  console.log("[*] Clean project :\nnectar [--clean] [--purge] [path_to_project.json]\n");
  console.log("[*] Copy example files :\nnectar --example\n");
  console.log("[*] Nectar version :\nnectar --version\n");
  showTarget();
}
