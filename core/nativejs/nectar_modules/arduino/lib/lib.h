/*
 * This file is part of NectarJS
 * Copyright (c) 2017-2018 Adrien THIERRY
 * http://nectarjs.com - https://www.linkedin.com/in/adrien-thierry-fr/
 *
 * sources : https://github.com/nectarjs/nectar_modules/
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

#include "Arduino.h"

static inline void __NJS_DELAY_MS(var v){ while(v.i--) { _delay_ms(1); }}

#define arduino_delay(_value) __NJS_DELAY_MS(__NJS_Get_Int(_value))
#define arduino_delay_second(_value) __NJS_DELAY_MS(__NJS_Get_Int(_value) * 1000)
#define arduino_delay_ms(_value) __NJS_DELAY_MS(__NJS_Get_Int(_value))
#define arduino_millis() var((unsigned int)millis())
#define arduino_seconds() var(UINT, (unsigned int)((millis() / (unsigned int)1000)))
#define arduino_HIGH __create_Number(HIGH)
#define arduino_LOW __create_Number(LOW)
#define arduino_INPUT __create_Number(INPUT)
#define arduino_OUTPUT __create_Number(OUTPUT)
#define arduino_pinMode(_pin, _mode) pinMode(__NJS_Get_Int(_pin), __NJS_Get_Int(_mode))
#define arduino_digitalWrite(_pin, _mode)  digitalWrite(__NJS_Get_Int(_pin), __NJS_Get_Int(_mode))
