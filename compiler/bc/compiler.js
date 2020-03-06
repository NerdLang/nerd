/*
 * This file is part of NectarJS
 * Copyright (c) 2017-2020 Adrien THIERRY
 * http://nectarjs.com - https://www.linkedin.com/in/adrien-thierry-fr/
 *
 * sources : https://github.com/nectarjs/nectarjs/
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
 * develop commercial activities involving the NectarJS software without
 * disclosing the source code of your own applications. Visit http://seraum.com/
 * and feel free to contact us.
 *
 */

function Compiler()
{
	var _handler = this;
	
	this.OUT = "";
	this.OPTION = "";
	this.COMPILER = require(path.join(__dirname, "lib", "bytecode.js"));
	
	/*** METHODS ***/
	this.Parse = function(_code)
	{
		_handler.MAIN = _code;
	}
	
	this.Out = function(_name)
	{
		if(path.extname(_name) != ".bin") _handler.OUT = _name + ".bin";
		return _handler.OUT;
	}
	  
	this.Prepare = function(_folder)
	{

	};
	  
	this.Compile = function(_folder, _file)
	{
		if(path.extname(_handler.OUT) != ".bin") _handler.OUT += ".bin";
		fs.writeFileSync(_file, _handler.MAIN);
		_handler.COMPILER.compileFile({in: _file, out: _handler.OUT})		
	}
	/*** END METHODS ***/
	
}

module.exports = new Compiler();