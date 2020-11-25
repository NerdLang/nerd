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
 
namespace Nectar::Global
{	
	using var = Nectar::VAR;
	using let = Nectar::VAR;
	Nectar::VAR undefined = Nectar::VAR(new Nectar::Class::Undefined());
	Nectar::VAR null = __Nectar_Create_Null();
	Nectar::VAR Infinity = std::numeric_limits<double>::infinity();
	Nectar::VAR NaN = std::numeric_limits<double>::quiet_NaN();
}