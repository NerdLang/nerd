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

function genGlobal()
{
  var G_DEFINED = [];
  for(var g in GLOBAL_VAR)
  {
    if(G_DEFINED.indexOf(GLOBAL_VAR[g].left.property.name) < 0)
    {
      GLOBAL_GEN += "static var " + GLOBAL_VAR[g].left.property.name + " = var(UNDEFINED, 0);";
      G_DEFINED.push(GLOBAL_VAR[g].left.property.name);
    }
  }
}
module.exports = genGlobal;
