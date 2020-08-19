/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
function __NJS_DELAY_MS(_value)
{ 
	delay(__NJS_Get_Int(_value)); // to fix
}

function __NJS_DELAY(_value)
{ 
	delay(__NJS_Get_Int(_value));
}

function __NJS_DELAY_SECOND(_value)
{
	delay(__NJS_Get_Int(_value) * 1000);
}

function __NJS_PIN_MODE( _pin, _mode)
{ 
	pinMode(__NJS_Get_Int(_pin), __NJS_Get_Int(_mode));
}

function __NJS_DIGITAL_WRITE( _pin, _mode)
{ 
	digitalWrite(__NJS_Get_Int(_pin), __NJS_Get_Int(_mode));
}

#define arduino_HIGH var(HIGH)
#define arduino_LOW var(LOW)
#define arduino_INPUT var(INPUT)
#define arduino_OUTPUT var(OUTPUT)
#define arduino_LED_BUILTIN var(LED_BUILTIN)
