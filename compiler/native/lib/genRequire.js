/*
 * This file is part of NativeJS
 * Copyright (c) 2017-2020 Adrien THIERRY
 * http://nectarjs.com - https://www.linkedin.com/in/adrien-thierry-fr/
 *
 * sources : https://github.com/nectarjs/old_nativejs
 *
 * this program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * You can be released from the requirements of the license by purchasing
 * a commercial license. Buying such a license is mandatory as soon as you
 * develop commercial activities involving the FortressJS software without
 * disclosing the source code of your own applications. Visit http://seraum.com/
 * and feel free to contact us.
 *
 */
var genInclude = require("./genInclude.js");
module.exports = genRequire;
var fs = require("fs");

function genRequire(from, src)
{

  var seek = ["require('", "require(\""];

  for(var s in seek)
  {
    var index = -1;
    do
    {
      index = src.indexOf(seek[s], index);
      if(index > -1)
      {
        var target = index + seek[s].length;
        var search = true;
        while(search)
        {
          if(src[target] == "'" || src[target] == "\"")
          {
            var startVar = index + seek[s].length;
            var endVar = target;
            var addSource = src.substring(startVar, endVar);

            /*
			if(LIBS[addSource])
            {
              OPTIONS += " " + LIBS[addSource].option;
              INIT += LIBS[addSource].init;
            }
			*/

            var modSource = "";
            if(addSource.indexOf(COMPILER.PATH) > -1)
            {
              modSource = addSource;
            }
            else
            {
              modSource = path.join(from + addSource);
            }
            var trySource = [modSource, /*modSource + ".js",*/ modSource + "/" + "index.js", from + "nectar_modules/" + addSource + "/index.js", NECTAR_PATH + "/nectar_modules/" + addSource + "/index.js", from + "node_modules/" + addSource + "/index.js", NECTAR_PATH + "/node_modules/" + modSource + "/index.js" ];
            var newSrc = "";
            for(var i = 0; i < trySource.length; i++)
            {
              try
              {
                modSource = path.dirname(trySource[i]) + "/";
                newSrc = fs.readFileSync(trySource[i]).toString();
                LINT(newSrc, trySource[i]);
                
                var pkgPath = path.join(modSource, "package.json");

                if(fs.existsSync(pkgPath))
                {
                  var pkg = fs.readFileSync(pkgPath);
                  try
                  {
                    pkg = JSON.parse(pkg);

                    if(pkg.nectar)
                    {
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
                      }
                    }
                  }
                  catch(e)
                  {
                    console.log("NectarJS:\n\n[!] " + e + " -> " + pkgPath.split("/").splice(-3).join("/"))
                  }
                }
                break;
              }
              catch (e) {}
            }

            if(newSrc.length == 0)
          {
            console.log("[!] Require error : " + addSource);
            process.exit();
          }
            newSrc = genInclude(path.resolve(modSource) + "/", newSrc);

            if(NJS_ENV.name != "arduino")
            {

              var reqFN = "_" + Math.random().toString(36).substr(2, 10);

              var resultSource = src.substring(0, index) + reqFN + "()";

              newSrc = "function " + reqFN + "(){\nvar module = __NJS_Create_Object();\n" + newSrc;

              newSrc = newSrc.replace(/(module\.exports *= *.*)$/g, "$1;");

              resultSource += src.substring(index + seek[s].length + addSource.length + 2);
              newSrc += "return module.exports;\n}";
              newSrc = genRequire(modSource, newSrc);
              src = resultSource;


            }
            else
            {
              var resultSource = src.substring(0, index);
              resultSource += src.substring(index + seek[s].length + addSource.length + 2);
              src = resultSource;
            }
            COMPILER.REQUIRE += newSrc + ";";

            search = false;
          }
          target++;
          if(target > src.length) search = false;
        }
        index++;
      }
    }
    while(index > -1)
  }
  return src;
}
