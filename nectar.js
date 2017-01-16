#!/usr/bin/env node
var VERSION = "0.0.20";

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
else if(CLI.cli["--clean"] || CLI.cli["--purge"]) ACTION = "clean";

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
    console.dir(e.message);
  }
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
    console.log("Missing file to compile, 'nectar --help' if you need help");
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
            console.log("project.json : " + e.message);
            return;
          }
        }
          var to = "";
          var tmp = fName.split("/");
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

                  console.log(to + " -> " + err.message);
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
          if(!CLI.cli["--prepare"]) coreHttp.httpUtil.httpReq(apiOption, function(err){console.log(err);}, Compiled)
      }
    });
  }
}

function Help()
{
  console.log("Nectar v" + VERSION);
  console.log("\nnectar [--target the-target] [--run] [--single] [--preset speed|size] [-o output] [--reinit] [--llvm] source.js|project.json\n");
  console.log("configure :\nnectar [--setid id] [--setkey key]\n")
  console.log("Show configuration :\nnectar --config\n")
  console.log("Reinit configuration :\nnectar --reinit\n")
  console.log("Clean project :\nnectar [--clean] [--purge]\n")
  console.log("Available targets :");
  for(var i = 0; i < TARGET.length; i++)
  {
    console.log("-> " + TARGET[i]);
  }
  console.log();
}
