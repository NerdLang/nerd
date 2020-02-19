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
 
LiquidCrystal lcd(12,11, 4, 5, 6, 7);

#define arduino_LiquidCrystal(_rs, _en, _d4, _d5, _d6, _d7) lcd = LiquidCrystal(__NJS_Get_Int(_rs), __NJS_Get_Int(_en), __NJS_Get_Int(_d4), __NJS_Get_Int(_d5), __NJS_Get_Int(_d6), __NJS_Get_Int(_d7));
#define arduino_beginLCD(_x, _y) lcd.begin(__NJS_Get_Int(_x), __NJS_Get_Int(_y))
#define arduino_setCursorLCD(_x, _y) lcd.setCursor(__NJS_Get_Int(_x), __NJS_Get_Int(_y))
#define arduino_clearLCD() lcd.clear()

var arduino_printLCD(var _content)
{
  if(_content.type == NUMBER)
  {
    lcd.print(__NJS_Get_Int(_content));
  }
  else
  {
    lcd.print(__NJS_Get_String(_content));
  }
  return var(UNDEFINED, 0);
}
