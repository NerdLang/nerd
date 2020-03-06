/*
 * This file is part of NectarJS
 * Copyright (c) 2020 Adrien THIERRY
 * http://nectarjs.com - https://nectrium.com
 *
 * sources : https://github.com/nectarjs/nectarjs
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

var NODE =
{
  name: "node",
  base: "std.cpp",
  cli: "__COMPILER__ -I extern/libuv/include/ -I extern/nodeuv-uri/ -I extern/http-parser/ -I extern/nodeuv-uri/ -luv extern/http-parser/http_parser.c __OPTION__ __IN__ -o __OUT__",
  compiler: "g++-8.1",
  stdlib: ["console", "process"],
  check: "node.json",
}

module.exports = NODE;
