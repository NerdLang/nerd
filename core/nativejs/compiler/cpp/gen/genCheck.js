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

function genCheck(_dir)
{
  var checkRules = path.join("./check", NJS_ENV.check);
  var _rules = fs.readFileSync(checkRules);
  try
  {
    _rules = JSON.parse(_rules);
  }
  catch(e){}
  for(var _e in EXPOSE)
  {
    _rules.globals[EXPOSE[_e]] = false;
  }
  _rules = JSON.stringify(_rules);
  FINAL_CHECK = path.join(_dir, NJS_ENV.check);
  fs.writeFileSync(FINAL_CHECK, _rules);
}

module.exports = genCheck;
