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
 
#include "mbed.h"

DigitalOut __NJS_STM32_led1(LED1);
DigitalOut __NJS_STM32_led2(LED2);

void __NJS_STM32_ledState(var _led, var _state)
{
  int _power = __NJS_Get_Int(_state);
  if(_power > 1) _power = 1;
  if(__NJS_Get_Int(_led) == 1)
  {
    __NJS_STM32_led1 = _power;
  }
  else if(__NJS_Get_Int(_led) == 2)
  {
    __NJS_STM32_led2 = _power;
  }
}

void __NJS_STM32_ledBlink(var _led)
{
  if(__NJS_Get_Int(_led) == 1)
  {
    __NJS_STM32_led1 = !__NJS_STM32_led1;
  }
  else if(__NJS_Get_Int(_led) == 2)
  {
    __NJS_STM32_led2 = !__NJS_STM32_led2;
  }
}
