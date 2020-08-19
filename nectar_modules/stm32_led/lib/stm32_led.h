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
