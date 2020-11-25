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

module.exports = parseCLI;
function parseCLI(args)
{
  var result = {error: false, msg: "", cli:{}, stack: [], useless: []};
  var useless = [0, 1];
  var withArgs = ["--tmp", "--target", "--spec", "--env", "--stack", "-o", "--preset", "--flash", "--compiler", "-c", "--build", "-b", "--option", "--register", "-r", "--setauthor", "--setid", "--setkey", "--setapi", "--setport", "--sethash", "--setsdk", "--setndk", "--setwin_inc_ucrt", "--setwin_lib_ucrt", "--setwin_lib_um", "--setxcode", "--profile", "-i", "--install", "--init-module", "--author"];
  var noArgs = ["--install_external", "--debug", "--conserve", "--generate", "--config", "--reinit", "--example", "--examples" , "--prepare", "--project", "--run", "--clean", "--purge", "--check", "--no-check", "--verbose", "-v", "--tips", "--version", "--help", "-h", "--release", "--no-undef-error", "--no-undef-warn", "--no-semi-error", "--no-semi-warn", "--no-fast-function", "--no-object-hashmap"];


  for(var i = 0; i < args.length; i++)
  {
    if( useless.indexOf(i) > -1 )
    {
     result.useless.push(args[i]);
    }
    else if( withArgs.indexOf(args[i]) > -1)
    {
      if(args[i+1])
      {
        result.cli[args[i]] =
        {
          state: true,
          argument: args[i+1],
        };
        i++;
      }
      else
      {
        result.error = true;
        result.msg = "[!] Missing argument for " + args[i];
        break;
      }
    }
    else if(noArgs.indexOf(args[i]) > -1)
    {
      result.cli[args[i]] =
      {
        state: true,
      };
    }
    else if(args[i].length > 0 && args[i][0] == "-")
    {
      if(withArgs.indexOf(args[i]) < 0 && noArgs.indexOf(args[i]) < 0)
      {
        result.error = true;
        result.msg = "[!] Unknown parameter : " + args[i];
        break;
      }
    }
    else result.stack.push(args[i]);
  }
  return result;
}
