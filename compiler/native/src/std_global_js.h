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
 
namespace NectarCore::JS
{
	NectarCore::VAR setImmediate = __Nectar_Create_Var_Unscoped_Anon(
		NectarCore::VAR _fn;
		if (__Nectar_VARLENGTH > 0) _fn = __Nectar_VARARGS[0];
		NectarCore::Event::evQ.push_back(_fn);
		return NectarCore::Global::undefined;	
	);

	NectarCore::VAR setTimeout = __Nectar_Create_Var_Unscoped_Anon(
		NectarCore::VAR _fn;
		NectarCore::VAR _delay;
		if (__Nectar_VARLENGTH > 0) _fn = __Nectar_VARARGS[0];
		if (__Nectar_VARLENGTH > 1) _delay = __Nectar_VARARGS[1];
		
		NectarCore::Event::setTimer(_fn, (int)_delay, false);
		
		return NectarCore::Global::undefined;
	);

	NectarCore::VAR setInterval = __Nectar_Create_Var_Unscoped_Anon(
		NectarCore::VAR _fn;
		NectarCore::VAR _delay;
		if (__Nectar_VARLENGTH > 0) _fn = __Nectar_VARARGS[0];
		if (__Nectar_VARLENGTH > 1) _delay = __Nectar_VARARGS[1];
		
		NectarCore::Event::setTimer(_fn, (int)_delay, true);
		
		return NectarCore::Global::undefined;
	);
}