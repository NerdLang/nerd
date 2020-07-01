/*
 * This file is part of NativeJS
 * Copyright (c) 2017-2018 Adrien THIERRY
 * http://nectarjs.com - https://www.linkedin.com/in/adrien-thierry-fr/
 *
 * sources : https://github.com/nectarjs/old_nativejs
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
 * develop commercial activities involving the FortressJS software without
 * disclosing the source code of your own applications. Visit http://seraum.com/
 * and feel free to contact us.
 *
 */

 #include <iostream>
 #include <functional>
 #include <string>
 #include <string.h>
 #include <cstring>
 #include <stdio.h>
 #include <stdlib.h>
 #include <sstream>
 #include <vector>
 #include <memory>
 #include "mbed.h"
 #include "njs.h"


using namespace std;
using namespace NECTAR;

 var __NJS_ENV = "stm32";
 var __NJS_PLATFORM = "{{__PLATFORM__}}";
 
 {INCLUDE}
 
 {DECL}

int main()
{
  {INIT}

	{CODE}
	return 0;
}
