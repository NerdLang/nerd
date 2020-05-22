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

function arduino_delay(_value)
{ 
	delay(__NJS_Get_Int(_value));
}

function arduino_delaySecond(_value)
{ 
	delay(__NJS_Get_Int(_value) * 1000);
}

function arduino_pinMode(_pin, _mode)
{ 
	pinMode(__NJS_Get_Int(_pin), __NJS_Get_Int(_mode));
}

function arduino_digitalWrite(_pin, _mode)
{ 
	digitalWrite(__NJS_Get_Int(_pin), __NJS_Get_Int(_mode));
}

#define arduino_HIGH var(HIGH)
#define arduino_LOW var(LOW)
#define arduino_INPUT var(INPUT)
#define arduino_OUTPUT var(OUTPUT)
#define arduino_LED_BUILTIN var(LED_BUILTIN)
