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
 
namespace NectarCore::Global
{	
	using var = NectarCore::VAR;
	using let = NectarCore::VAR;
	extern NectarCore::VAR undefined;
	extern NectarCore::VAR null;
	extern NectarCore::VAR Infinity;
	extern NectarCore::VAR NaN;
	
	template <typename T>
	NectarCore::VAR __Nectar_InitVar(T _init)
	{
		return NectarCore::VAR(_init);
	}
}