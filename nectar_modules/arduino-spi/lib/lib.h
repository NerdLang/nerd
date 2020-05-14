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
 #include "SPI.h"

 __NJS_FFI_FUNCTION(__NJS_BEGIN_TRANSACTION, __NJS_VAR _v1, __NJS_VAR _v2, __NJS_VAR _v3)
{ 
	SPI.beginTransaction(SPISettings(__NJS_Get_Int(_v1), __NJS_Get_Int(_v2), __NJS_Get_Int(_v3)));
	return __NJS_VAR();
};
 
 __NJS_FFI_FUNCTION(__NJS_END_TRANSACTION, __NJS_VAR _v1, __NJS_VAR _v2, __NJS_VAR _v3)
{ 
	return __NJS_VAR();
};

 __NJS_FFI_FUNCTION(__NJS_TRANSFER, __NJS_VAR _v1, __NJS_VAR _v2, __NJS_VAR _v3)
{ 
	return __NJS_VAR();
};