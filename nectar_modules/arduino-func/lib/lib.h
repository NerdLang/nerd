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

function arduino_delay(_value)
{ 
	delay(__Nectar_Get_Int(_value));
}

function arduino_delaySecond(_value)
{ 
	delay(__Nectar_Get_Int(_value) * 1000);
}

function arduino_pinMode(_pin, _mode)
{ 
	pinMode(__Nectar_Get_Int(_pin), __Nectar_Get_Int(_mode));
}

function arduino_digitalWrite(_pin, _mode)
{ 
	digitalWrite(__Nectar_Get_Int(_pin), __Nectar_Get_Int(_mode));
}

#define arduino_HIGH var(HIGH)
#define arduino_LOW var(LOW)
#define arduino_INPUT var(INPUT)
#define arduino_OUTPUT var(OUTPUT)
#define arduino_LED_BUILTIN var(LED_BUILTIN)
