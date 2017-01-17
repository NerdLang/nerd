#!/usr/bin/env node

/*
 * This file is part of NectarJS
 * Copyright (c) 2017 Adrien THIERRY
 * http://nectarjs.com - http://seraum.com
 *
 * sources : https://github.com/seraum/nectarjs
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

var VERSION = "0.0.23";

var fs = require('fs');
var os = require('os');
var path = require('path');
var Zip = require('./extern/adm-zip/adm-zip.js');
var process = require('process');
var querystring = require('querystring');
var child_process = require('child_process');

var parseCLI = require('./base/cli/cliParser.js');
var coreHttp = require('./base/core/httpUtils.js');
var CURRENT = process.cwd();
var TARGET = require('./base/compiler/target.js');
var PLATFORM = os.platform();
var ARCH = os.arch();
var CONFIGPATH = os.homedir() + path.sep + ".nectar";
var CONFIGFILE = CONFIGPATH + "/" + "nectar.json";
CONFIG = {};
Init();
readConfig();

var CLI = parseCLI(process.argv);

if(CLI.error)
{
  console.log(CLI.msg);
  return;
}

var ACTION = "build";
if(CLI.cli["--help"] || CLI.cli["-h"]) ACTION = "help";
else if(CLI.cli["--version"] || CLI.cli["-v"]) ACTION = "version";
else if(CLI.cli["--setid"] || CLI.cli["--setkey"]) ACTION = "setconfig";
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
  try
  {
      fs.mkdirSync(CONFIGPATH);
  } catch (e){}
  try
  {
      var writeConfig = false;
      var config = "";
      config = fs.readFileSync(CONFIGFILE);
      config = JSON.parse(config)
  }
  catch (e)
  {
    writeConfig = true;
  }

  if(!config || writeConfig)
  {
    var defaultConfig = { id: "", key:""};
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

function showConfig()
{
  console.log("[*] Current config :");
  console.log("id  : " + CONFIG.id);
  console.log("key : " + CONFIG.key);
}

function setConfig()
{
  if(CLI.cli["--setid"]) CONFIG.id = CLI.cli["--setid"].argument;
  if(CLI.cli["--setkey"]) CONFIG.key = CLI.cli["--setkey"].argument;
  try
  {
    fs.writeFileSync(CONFIGFILE, JSON.stringify(CONFIG));
  } catch (e)
  {
      console.log(e);
  }
}

function reinitConfig()
{
  try
  {
    var defaultConfig = { id: "", key:""};
    fs.writeFileSync(CONFIGFILE, JSON.stringify(defaultConfig));
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
  console.log("LLVM      : " + obj.llvm);
  console.log("Preset    : " + obj.preset);
  console.log();
}

function Build(prepare)
{
  var llvm = false;
  if(CLI.cli["--llvm"]) llvm = true;

  var single = false;
  if(CLI.cli["--single"]) single = true;

  var target;
  if(CLI.cli["--target"] && CLI.cli["--target"].argument) target = CLI.cli["--target"].argument;

  var preset;
  if(CLI.cli["--preset"] && CLI.cli["--preset"].argument) preset = CLI.cli["--preset"].argument;

  if(!target)
  {
    switch(PLATFORM)
    {
      case "android":
      case "linux":
        if(ARCH == "x64") target = "linux-x86-64";
        else if(ARCH == "x32") target = "linux-x86-32";
        else if(ARCH == "arm") target = "linux-arm32v7";
        break;

      case "win32":
        if(ARCH == "x64") target = "win-x86-32";
        else if(ARCH == "x32") target = "win-x86-64";
        break;

      default:
        target = "null";
        break;
    }
  }

  if(!preset) preset = "speed";

  if(!CLI.stack || CLI.stack.length < 1)
  {
    console.log("[!] Missing file to compile or project.json path, 'nectar --help' if you need help");
    return;
  }
  else if(!target || TARGET.indexOf(target) < 0)
  {
    console.log("[!] Bad target\n");
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
        console.log("[!] Error : " + err.message);
        return;
      }
      else
      {
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
            console.log("[!] Error with project.json : " + e.message);
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
            var end = ".bin";
            if(PLATFORM == "win32") end = ".exe";
            to = tmp[tmp.length-1].split(".")[0] + end;
          }
	  projTo = to;
	
	  var main = fName.split(path.sep);
          main = main[main.length - 1]; 
          
	  var data = "";
          var fPath = "";
          if(single)
          {
            data = '{ "source" : "' + fileData.toString("base64") + '", "llvm":' + llvm + ', "version":"' + VERSION + '", "id":"' + CONFIG.id + '"}';
            fPath = "/compile/" + "single" + "/" + target + "/" + preset + "/";
          }
          else
          {
            var zipArray = fName.split(path.sep);

            var zipFolder = "";
            for(var i = 0; i < zipArray.length - 1; i++)
            {
              zipFolder += zipArray[i] + path.sep;
            }
            if(zipArray.length < 2)
            {
              var toZip = CURRENT.split(path.sep);
               zipFolder =  ".." + path.sep + toZip[toZip.length - 1] + path.sep;
            }

            if(fProject)
            {
              main = projectConf.main;
              to = projectConf.out;
              llvm = projectConf.llvm;
              target = projectConf.target;
              preset = projectConf.preset;
              Clean(true);
            }

            fs.writeFileSync(zipFolder + "project.json", '{"main": "' + main + '", "out": "'+ to + '", "llvm":' + llvm + ', "target":"' + target + '", "preset":"' + preset + '"}');
            to = zipFolder + to;
            var zip = new Zip();
            zip.addLocalFolder(zipFolder);
            var zipBuffer = Buffer.from(zip.toBuffer()).toString("base64");
            data = '{ "project" : "' + zipBuffer + '", "version":"' + VERSION + '", "id":"' + CONFIG.id + '"}';
            fPath = "/compile/" + "project" + "/";
          }

          var apiOption =
          {
            port: 8080,
            hostname: "api.nectarjs.com",
            method: "POST",
            path: fPath,
            data: data,
          };
	  
          function Compiled(data)
          {
            var result = JSON.parse(data);
            if(result.success == false)
            {
              console.log(result.message);
            }
            else
            {
              var bin;
              if (typeof Buffer.from === "function")
              {
                  bin = Buffer.from(result.data, 'base64');
              }
              else
              {
                  bin = new Buffer(result.data, 'base64');
              }

              fs.writeFile(to, bin, function(err, data)
              {
                if(err)
                {
                  console.log("[!] Error with " + to + " : " + err.message);
                }
                else
                {
                  if(CLI.cli["--verbose"])
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
                    console.log("LLVM      : " + llvm);
                    console.log("Preset    : " + preset);
                  }
                  if(CLI.cli["--run"])
                  {
                    if(PLATFORM == "win32")
                    {
                      console.log(child_process.execSync(to).toString());
                    }
                    else
                    {
                      child_process.execSync("chmod +x " + to);
                      console.log(child_process.execSync("." + path.sep + to).toString());
                    }
                  }
                }
              });
            }
          }
          if(!CLI.cli["--prepare"]) coreHttp.httpUtil.httpReq(apiOption, function(err){console.log("[!] Network error : " + err.message);}, Compiled)
          else
          {
	      var pObj = {main: main, out:projTo, target:target, llvm:llvm, preset:preset};
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

function Help()
{
  showVersion();
  console.log("\n[*] Compile :\nnectar [--target the-target] [--run] [--single] [--preset speed|size] [-o output] [--reinit] [--llvm] [--prepare] source.js|project.json\n");
  console.log("[*] configure :\nnectar [--setid id] [--setkey key]\n");
  console.log("[*] Show configuration :\nnectar --config\n");
  console.log("[*] Reinit configuration :\nnectar --reinit\n");
  console.log("[*] Clean project :\nnectar [--clean] [--purge] [path_to_project.json]\n");
  showTarget();
}
