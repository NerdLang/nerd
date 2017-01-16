#!/usr/bin/env node
var VERSION = "0.0.15";

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
else if(CLI.cli["--config"]) ACTION = "showconfig";
else if(CLI.cli["--reinit"]) ACTION = "reinitconfig";

switch(ACTION)
{
  case "version":
    console.log("Nectar v" + VERSION);
    break;

  case "help":
    Help();
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
    Build(CLI);
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
  console.log("Current config :");
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

function Build()
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
    console.log("Missing file to compile");
    return;
  }
  else if(!target || TARGET.indexOf(target) < 0)
  {
    console.log("\nBad target");
    Help();
    return;
  }
  else
  {
    var fName = CLI.stack[CLI.stack.length - 1];

    fs.readFile(fName, function(err, fileData)
    {
      if(err)
      {
        console.log("Error : " + err);
        return;
      }
      else
      {
          var data = "";
          var fPath = "";
          if(single)
          {
            data = '{ "source" : "' + fileData.toString("base64") + '", "llvm":' + llvm + ', "version":"' + VERSION + '", "id":"' + CONFIG.id + '", "key":"' + CONFIG.key + '"}';
            fPath = "/compile/" + "single" + "/" + target + "/" + preset + "/";
          }
          else
          {
            var zipArray = fName.split(path.sep);
            var main = fName.split(path.sep);
            main = main[main.length - 1];
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
            fs.writeFileSync(zipFolder + "project.json", '{"main": "' + main + '", "llvm":' + llvm + ', "target":"' + target + '", "preset":"' + preset + '"}');
            var zip = new Zip();
            zip.addLocalFolder(zipFolder);
            var zipBuffer = Buffer.from(zip.toBuffer()).toString("base64");
            data = '{ "project" : "' + zipBuffer + '", "version":"' + VERSION + '", "id":"' + CONFIG.id + '", "key":"' + CONFIG.key + '"}';
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
              var tmp = fName.split("/");
              var to = "";
              if(CLI.cli["-o"])
              {
                to = CLI.cli["-o"].argument;
              }
              else
              {
                var end = ".bin";
                if(PLATFORM == "win32") end = ".exe";
                to = tmp[tmp.length-1].split(".")[0] + end;
              }
              fs.writeFile(to, bin, function(err, data)
              {
                if(err)
                {
                  console.log(err);
                }
                else
                {
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
          coreHttp.httpUtil.httpReq(apiOption, function(err){console.log(err);}, Compiled)
      }
    });
  }
}

function Help()
{
  console.log("\nnectar [--target the-target] [--run] [--single] [--preset speed|size] [-o output] [--setid id] [--setkey key] [--config] [--reinit] [--llvm] source.js\n");
  console.log("Targets :");
  for(var i = 0; i < TARGET.length; i++)
  {
    console.log("-> " + TARGET[i]);
  }
  console.log();
}
