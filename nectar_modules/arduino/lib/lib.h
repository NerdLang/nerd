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
 
__NJS_FFI_FUNCTION(__NJS_DELAY_MS, var v)
{ 
	while(v.get().i--) 
	{ 
		_delay_ms(1); 
	}
	return var();
};

__NJS_FFI_FUNCTION(__NJS_DELAY, var _value)
{ 
	__NJS_DELAY_MS(__NJS_Get_Int(_value));
	return var();
};

__NJS_FFI_FUNCTION(__NJS_DELAY_SECOND, var _value)
{ 
	__NJS_DELAY_MS(__NJS_Get_Int(_value) * 1000);
	return var();
};

__NJS_FFI_FUNCTION(__NJS_MILLIS)
{ 
	return var((unsigned int)millis());
};

__NJS_FFI_FUNCTION(__NJS_SECONDS)
{ 
	var((unsigned int)((millis() / (unsigned int)1000)));
};

__NJS_FFI_FUNCTION(__NJS_PIN_MODE, var _pin, var _mode)
{ 
	pinMode(__NJS_Get_Int(_pin), __NJS_Get_Int(_mode));
	return var();
};

__NJS_FFI_FUNCTION(__NJS_DIGITAL_WRITE, var _pin, var _mode)
{ 
	digitalWrite(__NJS_Get_Int(_pin), __NJS_Get_Int(_mode));
	return var();
};

#define arduino_HIGH var(HIGH)
#define arduino_LOW var(LOW)
#define arduino_INPUT var(INPUT)
#define arduino_OUTPUT var(OUTPUT)

