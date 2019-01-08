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

module.exports = parseCLI;
function parseCLI(args)
{
  var result = {error: false, msg: "", cli:{}, stack: [], useless: []};
  var useless = [0, 1];
  var withArgs = ["--target", "--spec", "--compiler", "-o", "--options", "--tmp", "--engine", "--env", "--preset"];
  var noArgs = ["--debug", "--build", "--run", "--check", "--verbose", "-v", "--release", "--gen", "--conserve", "--version"];

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
        result.msg = "Missing argument for " + args[i];
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
    else result.stack.push(args[i]);
  }
  return result;
}
