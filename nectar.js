#!/usr/bin/env node
var VERSION = "0.0.10";

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

var CLI = parseCLI(process.argv);

if(CLI.error)
{
  console.log(CLI.msg);
  return;
}

var ACTION = "build";
if(CLI.cli["--help"] || CLI.cli["-h"]) ACTION = "help";
else if(CLI.cli['--version'] || CLI.cli["-v"]) ACTION = "version";


switch(ACTION)
{
  case "version":
    console.log("Nectar v" + VERSION);
    break;

  case "help":
    Help();
    break;

  case "build":
    Build(CLI);
    break;

  default:
    Help();
    break;
}

function Build()
{
  var target;
  var preset;
  if(CLI.cli["--target"] && CLI.cli["--target"].argument) target = CLI.cli["--target"].argument;
  if(CLI.cli["--preset"] && CLI.cli["--preset"].argument) preset = CLI.cli["--preset"].argument;

  if(!target)
  {
    switch(PLATFORM)
    {
      case "linux":
        if(ARCH == "x64") target = "linux-x86-32";
        else if(ARCH == "x32") target = "linux-x86-64";
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

    fs.readFile(fName, function(err, data)
    {
      if(err)
      {
        console.log("Error : " + err);
        return;
      }
      else
      {
          var zipFolder = fName.split(path.sep);
          var main = fName.split(path.sep);
          main = main[main.length - 1];
          zipFolder = zipFolder.slice(0, zipFolder.length - 1).join(path.sep) + path.sep;
          fs.writeFileSync(zipFolder + path.sep + "project.json", '{"main": "' + main + '", "target":"' + target + '", "preset":"' + preset + '"}');
          var zip = new Zip();
          zip.addLocalFolder(zipFolder);
          var zipBuffer = Buffer.from(zip.toBuffer()).toString("base64");

          var data = '{ "project" : "' + zipBuffer + '", "version":"' + VERSION + '"}';

          var apiOption =
          {
            port: 8080,
            hostname: "api.nectarjs.com",
            method: "POST",
            path: "/compile/" + "project" + "/",
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
  console.log("\nnectar [--target the_target] [--run] source.js\n");
  console.log("Targets :");
  for(var i = 0; i < TARGET.length; i++)
  {
    console.log("-> " + TARGET[i]);
  }
  console.log();
}
