/*
 * This file is part of NectarCPP
 * Copyright (c) 2020 - 2020 Adrien THIERRY
 * https://nectar-lang.org - https://seraum.com/
 *
 * sources : https://github.com/nectar-lang/NectarCPP
 * 
 * NectarCPP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarCPP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarCPP.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
namespace Nectar::JS
{
	Nectar::VAR setImmediate = __Nectar_Create_Var_Unscoped_Anon(
		Nectar::VAR _fn;
		if (__Nectar_VARLENGTH > 0) _fn = __Nectar_VARARGS[0];
		Nectar::Event::evQ.push_back(_fn);
		return Nectar::Global::undefined;	
	);

	Nectar::VAR setTimeout = __Nectar_Create_Var_Unscoped_Anon(
		Nectar::VAR _fn;
		Nectar::VAR _delay;
		if (__Nectar_VARLENGTH > 0) _fn = __Nectar_VARARGS[0];
		if (__Nectar_VARLENGTH > 1) _delay = __Nectar_VARARGS[1];
		
		Nectar::Event::setTimer(_fn, (int)_delay, false);
		
		return Nectar::Global::undefined;
	);

	Nectar::VAR setInterval = __Nectar_Create_Var_Unscoped_Anon(
		Nectar::VAR _fn;
		Nectar::VAR _delay;
		if (__Nectar_VARLENGTH > 0) _fn = __Nectar_VARARGS[0];
		if (__Nectar_VARLENGTH > 1) _delay = __Nectar_VARARGS[1];
		
		Nectar::Event::setTimer(_fn, (int)_delay, true);
		
		return Nectar::Global::undefined;
	);
}